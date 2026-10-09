#!/usr/bin/env python3
"""Interactive helper for matching one BK9E function in C.

  show  MODULE SYMBOL             target disassembly, relocations, Ghidra view
  try   MODULE SYMBOL SOURCE.c    compile, bind externals, diff against target
  stage MODULE SYMBOL SOURCE.c --name N --behavior B ...
                                  verify and queue a match for `merge`
  merge                           append every staged match to matches.json

Externals are bound from their names: `func_0201a2b4`, `data_ov022_020b1c00`,
or any name ending in `_<8 hex digits>` (e.g. `Actor_Update_0208a2fc`).
Names already used by matches.json or dsd symbols are also accepted.
"""

from __future__ import annotations

import argparse
import difflib
import functools
import io
import json
import os
import re
import shutil
import stat
import sys
import tempfile
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compile_match as cm  # noqa: E402
import khrecoded as kh  # noqa: E402

ROOT = kh.ROOT
PENDING = ROOT / "build" / "pending"
SNAPSHOTS = ROOT / "build" / "registered"  # verified copies of registered sources
DECOMP = ROOT / "build" / "ghidra" / "decomp"
RELOC_LINE = re.compile(r"^from:0x([0-9a-f]+) kind:(\S+) to:0x([0-9a-f]+) module:(\S+)", re.I)
FUNCTION_LINE = re.compile(r"^(\S+) kind:function\((arm|thumb),size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", re.I)
ADDRESS_SUFFIX = re.compile(r"(?:^|_|Ram)([0-9a-fA-F]{8})$")
REQUIRED = ("name", "behavior", "evidence", "uncertainty", "domain", "origin", "understanding")


def config_dir(module: str) -> Path:
    base = kh.DSD_CONFIG.parent
    return base if module == "arm9" else base / module if module in ("itcm", "dtcm") else base / "overlays" / module


_inv = None


def inventory() -> dict:
    global _inv
    if _inv is None:
        inv = kh.inventory()
        for module, data in inv.items():
            if module == "arm7":
                continue
            data["modes"] = {}
            for line in (config_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
                m = FUNCTION_LINE.match(line)
                if m:
                    data["modes"][m.group(1)] = m.group(2)
        _inv = inv  # publish only once complete; worker threads share it
    return _inv


def resolve_function(module: str, symbol: str) -> tuple[str, dict]:
    data = inventory()[module]
    if symbol in data["symbols"]:
        return symbol, data["symbols"][symbol]
    wanted = int(symbol, 16) if re.fullmatch(r"(0x)?[0-9a-fA-F]+", symbol) else None
    for name, info in data["symbols"].items():
        if info["address"] == wanted:
            return name, info
    raise SystemExit(f"Unknown function {module}:{symbol}")


@functools.lru_cache(maxsize=None)
def thumb_addresses() -> set[int]:
    result = set()
    for module, data in inventory().items():
        if module == "arm7":
            continue
        for name, info in data["symbols"].items():
            if data["modes"].get(name) == "thumb":
                result.add(info["address"])
    return result


@functools.lru_cache(maxsize=None)
def known_names() -> dict[str, int]:
    names: dict[str, set[int]] = {}
    for module, data in inventory().items():
        for name, info in data["symbols"].items():
            names.setdefault(name, set()).add(info["address"])
    for m in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]:
        info = inventory()[m["module"]]["symbols"].get(m["symbol"])
        if info:
            names.setdefault(m["name"], set()).add(info["address"])
            names.setdefault(m["source_symbol"], set()).add(info["address"])
    for name, address in RUNTIME_HELPERS.items():
        names.setdefault(name, set()).add(address)
    return {name: next(iter(v)) for name, v in names.items() if len(v) == 1}


# Compiler runtime calls emitted for `/`, `%` and 64-bit arithmetic.
RUNTIME_HELPERS = {
    "_s32_div_f": 0x02023DBC,
    "_u32_div_f": 0x02023FC8,
    "_ll_mul": 0x02023D9C,
    "_ll_udiv": 0x02023D54,
    "_ll_sdiv": 0x02023BA4,
    "__strtoul": 0x02022128,
    # Single-precision soft-float helpers, identified from their code.
    "_fadd": 0x020245E8,
    "_fsub": 0x02024818,
    "_fmul": 0x02024408,
    "_fdiv": 0x02024A9C,
    "_fflt": 0x02023A98,
    "_ffltu": 0x02023AE0,
    "_ffix": 0x020241AC,
    "_ffixu": 0x020241E0,
    "_feq": 0x02023934,
    "_fgeq": 0x020237B8,
    "_fgr": 0x02023814,
    "_fleq": 0x02023870,
    "_fls": 0x020238D8,
    "_f2d": 0x0202399C,
    "_ll_sto_f": 0x02023B28,
    "_ll_sfrom_f": 0x02023A20,
    # Double-precision compare and convert helpers.
    "_dflt": 0x0202363C,
    "_dleq": 0x02023714,
}


@functools.lru_cache(maxsize=None)
def function_modes() -> dict[str, dict[int, str]]:
    return {module: {info["address"]: data["modes"][symbol]
                     for symbol, info in data["symbols"].items() if symbol in data.get("modes", {})}
            for module, data in inventory().items()}


@functools.lru_cache(maxsize=None)
def target_modes(module: str, start: int, stop: int) -> dict[int, frozenset[str]]:
    """Keep overlay identity when resolving calls and function pointers."""
    modes: dict[int, set[str]] = {}
    functions = function_modes()
    call_modes = {"arm_call": "arm", "arm_call_thumb": "thumb",
                  "thumb_call": "thumb", "thumb_call_arm": "arm"}
    for line in (config_dir(module) / "relocs.txt").read_text(encoding="utf-8").splitlines():
        relocation = RELOC_LINE.match(line)
        if not relocation or not start <= int(relocation[1], 16) < stop:
            continue
        address, kind, destination = int(relocation[3], 16), relocation[2], relocation[4]
        if kind in call_modes:
            modes.setdefault(address, set()).add(call_modes[kind])
            continue
        overlays = re.fullmatch(r"overlays?\(([0-9,]+)\)", destination)
        modules = ([f"ov{int(n):03}" for n in overlays[1].split(",")] if overlays else
                   ["arm9" if destination == "main" else destination])
        for owner in modules:
            mode = functions.get(owner, {}).get(address)
            if mode:
                modes.setdefault(address, set()).add(mode)
    return {address: frozenset(values) for address, values in modes.items()}


def bind(name: str, thumbs: set[int], names: dict[str, int], *, module: str | None = None,
         referenced_modes: dict[int, frozenset[str]] | None = None) -> int | None:
    m = ADDRESS_SUFFIX.search(name)
    address = int(m.group(1), 16) if m else names.get(name)
    if address is None:
        return None
    if address & 1 or re.match(r"_*data_(?:ov\d{3}_)?[0-9a-fA-F]{8}$", name):
        return address
    if module is not None:
        functions = function_modes()
        explicit = re.search(r"(?:^|_)(ov\d{3}|arm9|itcm|dtcm)_", name)
        if explicit:
            mode = functions.get(explicit[1], {}).get(address)
            return address | (mode == "thumb")
        candidates = (referenced_modes or {}).get(address)
        if candidates is None:
            # Core addresses do not overlap overlays. Overlay-local names have priority.
            mode = functions.get(module, {}).get(address)
            if mode is not None:
                candidates = frozenset([mode])
            else:
                candidates = frozenset(values[address] for values in functions.values() if address in values)
        if len(candidates) > 1:
            return None  # An unqualified overlay alias needs an explicit target name.
        return address | (candidates == frozenset(["thumb"]))
    return address | 1 if address in thumbs else address


def undefined_symbols(obj: bytes, function_name: str) -> list[str]:
    from elftools.elf.elffile import ELFFile

    elf = ELFFile(io.BytesIO(obj))
    symtab = elf.get_section_by_name(".symtab")
    fn = [s for s in symtab.get_symbol_by_name(function_name) or [] if s["st_info"]["type"] == "STT_FUNC"]
    if len(fn) != 1:
        raise SystemExit(f"Source must define exactly one function named {function_name}")
    index, start, size = fn[0]["st_shndx"], fn[0]["st_value"] & ~1, fn[0]["st_size"]
    used = []
    for section in elf.iter_sections():
        if section["sh_type"] == "SHT_RELA" and section["sh_info"] == index:
            for r in section.iter_relocations():
                if start <= r["r_offset"] < start + size:
                    sym = symtab.get_symbol(r["r_info_sym"])
                    outside = sym["st_shndx"] == "SHN_UNDEF" or (
                        sym["st_shndx"] != index and isinstance(sym["st_shndx"], int)
                        and sym["st_info"]["type"] == "STT_FUNC")
                    if outside and sym.name not in used:
                        used.append(sym.name)
    return used


def compile_candidate(module: str, symbol: str, source: Path, compiler: str, mode: str | None,
                      source_symbol: str | None, language: str = "c") -> tuple[bytes | None, dict, str]:
    """Compile and link a candidate; returns (bytes, entry, error)."""
    name, info = resolve_function(module, symbol)
    mode = mode or inventory()[module]["modes"][name]
    source = source.resolve()
    if not source.is_relative_to(ROOT / "src"):
        raise SystemExit("Put the candidate under src/ (e.g. src/<module>/<area>/<Name>_<addr>.c)")
    source_symbol = source_symbol or source.stem
    entry = {"source": source.relative_to(ROOT).as_posix(), "source_symbol": source_symbol,
             "compiler": compiler, "mode": mode, "bindings": {}}
    if language != "c":
        entry["language"] = language
    thumbs, names = thumb_addresses(), known_names()
    with tempfile.TemporaryDirectory(prefix="try-", dir=ROOT / "build") as temp:
        out = Path(temp) / "out.bin"
        try:
            cm.compile_entry(entry, info["address"], out)
            return out.read_bytes(), entry, ""
        except RuntimeError as error:
            message = str(error)
        obj = out.with_suffix(".o")
        if not obj.exists():
            return None, entry, message
        missing = []
        object_bytes = obj.read_bytes()
        for ext in undefined_symbols(object_bytes, source_symbol):
            value = bind(ext, thumbs, names, module=module,
                         referenced_modes=target_modes(module, info["address"], info["address"] + info["size"]))
            if value is None:
                missing.append(ext)
            else:
                entry["bindings"][ext] = hex(value)
        if missing:
            return None, entry, "Cannot bind externals (add an _<address> suffix): " + ", ".join(missing)
        try:
            bindings = {name: int(value, 16) for name, value in entry["bindings"].items()}
            return cm.link_function(object_bytes, source_symbol, info["address"], bindings), entry, ""
        except RuntimeError as error:
            return None, entry, str(error)


def target_bytes(module: str, symbol: str) -> tuple[str, dict, bytes]:
    name, info = resolve_function(module, symbol)
    data = inventory()[module]
    offset = info["address"] - data["base"]
    return name, info, data["binary"].read_bytes()[offset:offset + info["size"]]


def disassemble(code: bytes, address: int, mode: str) -> list[tuple[int, str]]:
    import capstone

    md = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB if mode == "thumb" else capstone.CS_MODE_ARM)
    step = 2 if mode == "thumb" else 4
    lines, offset = [], 0
    while offset < len(code):
        insn = next(md.disasm(code[offset:offset + 4], address + offset), None)
        if insn is None:
            word = code[offset:offset + step]
            lines.append((offset, f".word 0x{int.from_bytes(word, 'little'):0{step * 2}x}"))
            offset += step
        else:
            lines.append((offset, f"{insn.mnemonic} {insn.op_str}".strip()))
            offset += insn.size
    return lines


def relocations(module: str, start: int, stop: int) -> dict[int, str]:
    names = {}
    for mod, data in inventory().items():
        for name, info in data["symbols"].items():
            names.setdefault(info["address"], name)
    result = {}
    for line in (config_dir(module) / "relocs.txt").read_text(encoding="utf-8").splitlines():
        m = RELOC_LINE.match(line)
        if m and start <= int(m.group(1), 16) < stop:
            to = int(m.group(3), 16)
            result[int(m.group(1), 16) - start] = f"{m.group(2)} -> {names.get(to, hex(to))} [{m.group(4)}]"
    return result


def cmd_show(args) -> None:
    name, info, code = target_bytes(args.module, args.symbol)
    mode = inventory()[args.module]["modes"][name]
    print(f"{args.module}:{name} @ 0x{info['address']:08x}, {info['size']} bytes, {mode}")
    relocs = relocations(args.module, info["address"], info["address"] + info["size"])
    for offset, text in disassemble(code, info["address"], mode):
        note = relocs.get(offset, "")
        print(f"  {offset:04x}: {text:<40} {('; ' + note) if note else ''}")
    # Callees and globals that already have matched C: reuse their names and struct types.
    matched = {}
    for m in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]:
        address = inventory()[m["module"]]["symbols"][m["symbol"]]["address"]
        matched.setdefault(address, []).append(m)
    targets = sorted({int(re.search(r"0x([0-9a-f]+)|_([0-9a-f]{8}) ", n + " ").group(0).strip().split("_")[-1], 16)
                      for n in relocs.values() if re.search(r"0x([0-9a-f]+)|_([0-9a-f]{8}) ", n + " ")})
    known = [(a, m) for a in targets for m in matched.get(a, [])[:1]]
    if known:
        print("\nAlready matched callees (reuse their names/types):")
        for address, m in known:
            print(f"  0x{address:08x} {m['name']} -> {m['source_symbol']} in {m['source']}")
    similar_path = ROOT / "build" / "days_port" / "similar.json"
    if similar_path.exists():
        import days_port
        for hit in json.loads(similar_path.read_text(encoding="utf-8")).get(f"{args.module}:{name}", []):
            print(f"\nSimilar KH Days C (score {hit['score']}, {hit['days_size']} bytes): "
                  f"{days_port.DAYS / hit['days_source']} :: {hit['days_name']}")
    exact = ROOT / "build" / "ghidra_auto" / args.module / f"{name}.c"
    near = ROOT / "build" / "ghidra_auto" / "near" / args.module / f"{name}.c"
    if exact.exists():
        print(f"\nGhidra C that ALREADY MATCHES byte-exact: {exact.relative_to(ROOT)} — copy it, give it clean "
              f"names/types, `try` (both compilers if needed), stage.")
    elif near.exists():
        print(f"\nCompilable Ghidra C with the right size (only a few instructions differ): "
              f"{near.relative_to(ROOT)} — copy it, rename, and fix the differing slots.")
    decomp = DECOMP / args.module / f"{name}.c"
    if decomp.exists():
        print(f"\nGhidra view ({decomp.relative_to(ROOT)}):\n" + decomp.read_text(encoding="utf-8"))


def diff_report(target: bytes, actual: bytes, address: int, mode: str, relocs: dict[int, str]) -> str:
    want = disassemble(target, address, mode)
    got = disassemble(actual, address, mode)
    if len(target) == len(actual):
        bad = [o for o in range(0, len(target), 2 if mode == "thumb" else 4)
               if target[o:o + 4] != actual[o:o + 4]]
        lines = []
        gmap = dict(got)
        ends = [o for o, _ in want[1:]] + [len(target)]
        for (offset, text), end in zip(want, ends):
            mark = "  " if target[offset:end] == actual[offset:end] else "!!"
            other = gmap.get(offset, "")
            lines.append(f"{mark} {offset:04x}: {text:<38} | {other:<38} {relocs.get(offset, '')}")
        return f"same size; {len(bad)} differing slots\n" + "\n".join(lines)
    matcher = difflib.SequenceMatcher(a=[t for _, t in want], b=[t for _, t in got], autojunk=False)
    lines = [f"size differs: target {len(target)} vs compiled {len(actual)}"]
    for tag, a0, a1, b0, b1 in matcher.get_opcodes():
        if tag == "equal":
            lines += [f"   {want[i][0]:04x}: {want[i][1]}" for i in range(a0, a1)]
        else:
            lines += [f"-  {want[i][0]:04x}: {want[i][1]}" for i in range(a0, a1)]
            lines += [f"+  {got[i][0]:04x}: {got[i][1]}" for i in range(b0, b1)]
    return "\n".join(lines)


def cmd_try(args) -> int:
    name, info, target = target_bytes(args.module, args.symbol)
    mode = args.mode or inventory()[args.module]["modes"][name]
    actual, entry, error = compile_candidate(args.module, name, Path(args.source), args.compiler, mode,
                                             args.source_symbol)
    if actual is None:
        print("ERROR:", error)
        return 2
    if actual == target:
        print(f"MATCH {args.module}:{name} ({len(target)} bytes) bindings={json.dumps(entry['bindings'])}")
        return 0
    relocs = relocations(args.module, info["address"], info["address"] + info["size"])
    print(diff_report(target, actual, info["address"], mode, relocs))
    print("NO MATCH")
    return 1


GHIDRA_NAME = re.compile(r"\b(?:[a-z]{1,5}Var\d+|param_\d+|local_[0-9a-fA-F]+|(?:in|unaff|extraout)_\w+|"
                         r"(?:DAT|FUN|PTR|LAB|SUB)_[0-9a-fA-F]+|[a-z]*Stack_[0-9a-fA-F]+|undefined\d?)\b")


def style_problems(text: str) -> list[str]:
    """Readable names and at most one short comment per source."""
    comments = re.findall(r"/\*.*?\*/|//[^\n]*", text, flags=re.S)
    code = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    problems = [f"decompiler-style name `{m}`" for m in sorted(set(GHIDRA_NAME.findall(code)))]
    if len(comments) > 1:
        problems.append(f"{len(comments)} comments (at most one allowed)")
    problems += [f"comment too long ({len(re.findall(r'[A-Za-z0-9]+', c))} words, max 12)"
                 for c in comments if len(re.findall(r"[A-Za-z0-9]+", c)) > 12]
    return problems


def cmd_stage(args) -> int:
    source_path = Path(args.source).as_posix()
    if any(part in source_path for part in (".port_scratch", "scratch", "tmp", "/_w", "_wip")):
        print("ERROR: stage from src/<module>/<domain>/, not a scratch folder (scratch files are not committed).")
        return 1
    problems = style_problems(Path(args.source).read_text(encoding="utf-8"))
    if problems:
        print("ERROR: fix style before staging: " + "; ".join(problems))
        return 1
    name, info, target = target_bytes(args.module, args.symbol)
    mode = args.mode or inventory()[args.module]["modes"][name]
    actual, entry, error = compile_candidate(args.module, name, Path(args.source), args.compiler, mode,
                                             args.source_symbol)
    if actual != target:
        print("ERROR: candidate does not match; run `try` first.", error)
        return 1
    record = {"module": args.module, "symbol": name, "name": args.name, "language": "c",
              "source": entry["source"], "source_symbol": entry["source_symbol"],
              "compiler": args.compiler, "mode": mode, "bindings": entry["bindings"],
              "behavior": args.behavior, "evidence": args.evidence or
              f"Rebuilt C matches all {len(target)} bytes including relocations.",
              "uncertainty": args.uncertainty, "domain": args.domain, "origin": args.origin,
              "understanding": args.understanding}
    if args.provenance:
        record["provenance"] = json.loads(args.provenance)
    record["source_text"] = Path(args.source).read_text(encoding="utf-8")  # exactly what was verified
    PENDING.mkdir(parents=True, exist_ok=True)
    (PENDING / f"{args.module}__{name}.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    print(f"STAGED {args.module}:{name}")
    return 0


def snapshot_path(entry: dict) -> Path:
    return SNAPSHOTS / f"{entry['module']}__{entry['symbol']}{Path(entry['source']).suffix}"


def write_source(path: Path, data: bytes) -> None:
    """Write a registered source and mark it read-only so parallel agents leave it alone."""
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists():
        os.chmod(path, stat.S_IWRITE | stat.S_IREAD)
    path.write_bytes(data)
    os.chmod(path, stat.S_IREAD)


def uncommitted_paths() -> set[str] | None:
    """Repo-relative paths with uncommitted changes, or None when git is unavailable."""
    import subprocess
    try:
        out = subprocess.run(["git", "status", "--porcelain", "-z", "--untracked-files=all"], cwd=ROOT,
                             capture_output=True, check=True).stdout.decode("utf-8", "replace")
    except (OSError, subprocess.CalledProcessError):
        return None
    return {item[3:] for item in out.split("\0") if len(item) > 3}


def cmd_merge(_args) -> int:
    """Register staged matches. Serialized by a lock; fragments are removed only after
    matches.json is written; registered sources are restored from verified snapshots."""
    PENDING.mkdir(parents=True, exist_ok=True)
    lock = PENDING / ".merge.lock"
    try:
        handle = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
    except FileExistsError:
        if time.time() - lock.stat().st_mtime < 1800:
            print("Another merge is running; skipped")
            return 1
        lock.unlink()
        handle = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
    try:
        return merge_locked()
    finally:
        os.close(handle)
        lock.unlink()


def merge_locked() -> int:
    path = ROOT / "matches.json"
    manifest = json.loads(path.read_text(encoding="utf-8"))
    by_key = {(m["module"], m["symbol"]): m for m in manifest["matches"]}
    inv = inventory()
    SNAPSHOTS.mkdir(parents=True, exist_ok=True)
    for entry in manifest["matches"]:  # entries registered before snapshots existed
        source, snapshot = ROOT / entry["source"], snapshot_path(entry)
        if not snapshot.exists() and source.exists():
            shutil.copyfile(source, snapshot)
    accepted, refused = [], []
    for fragment in sorted(PENDING.glob("*.json")):
        try:
            record = json.loads(fragment.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            continue
        text = record.pop("source_text", None)
        key = (record["module"], record["symbol"])
        source = ROOT / record["source"]
        if text is not None and (not source.exists() or source.read_text(encoding="utf-8") != text):
            write_source(source, text.encode("utf-8"))
        info = inv[key[0]]["symbols"][key[1]]
        start, stop = info["address"], info["address"] + info["size"]
        ok = source.exists() and all(isinstance(record.get(f), str) and record[f].strip() for f in REQUIRED)
        for other in manifest["matches"]:
            if other["module"] == key[0] and (other["module"], other["symbol"]) != key:
                o = inv[other["module"]]["symbols"][other["symbol"]]
                if start < o["address"] + o["size"] and o["address"] < stop:
                    ok = False
                    break
        if ok:
            _, _, target = target_bytes(*key)
            with tempfile.TemporaryDirectory(prefix="merge-", dir=ROOT / "build") as temp:
                try:
                    cm.compile_entry(record, start, Path(temp) / "o.bin")
                    ok = (Path(temp) / "o.bin").read_bytes() == target
                except RuntimeError:
                    ok = False
        if not ok:
            refused.append(fragment)
            continue
        if key in by_key:  # a verified re-stage replaces the earlier entry
            manifest["matches"].remove(by_key[key])
        manifest["matches"].append(record)
        by_key[key] = record
        shutil.copyfile(source, snapshot_path(record))
        accepted.append(fragment)
    restored = 0
    dirty = uncommitted_paths()
    for entry in manifest["matches"]:  # undo later edits, renames and deletions
        source, snapshot = ROOT / entry["source"], snapshot_path(entry)
        if dirty is not None and snapshot.exists() and source.exists() and entry["source"] not in dirty \
                and source.read_bytes() != snapshot.read_bytes():
            shutil.copyfile(source, snapshot)  # committed upstream edit wins
        elif snapshot.exists() and (not source.exists() or source.read_bytes() != snapshot.read_bytes()):
            write_source(source, snapshot.read_bytes())
            restored += 1
        elif source.exists() and os.access(source, os.W_OK):
            os.chmod(source, stat.S_IREAD)
    temp_path = path.with_suffix(".json.tmp")
    temp_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    for attempt in range(20):  # Windows refuses the swap while a reader holds matches.json
        try:
            os.replace(temp_path, path)
            break
        except PermissionError:
            if attempt == 19:
                raise
            time.sleep(0.5)
    for fragment in accepted:
        fragment.unlink()
    for fragment in refused:
        fragment.replace(fragment.with_suffix(".rejected"))
    print(f"Merged {len(accepted)} staged matches; rejected {len(refused)}; restored {restored} edited sources")
    return 0


def cmd_batch(args) -> int:
    """Print the still-open functions of one batch (skips anything matched or staged)."""
    lines = json.loads((ROOT / args.file).read_text(encoding="utf-8"))[args.index]
    matched = {(m["module"], m["symbol"]) for m in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]}
    for line in lines:
        module, symbol = line.split()[:2]
        if (module, symbol) not in matched and not (PENDING / f"{module}__{symbol}.json").exists():
            print(line)
    return 0


def cmd_verify(args) -> int:
    """Rebuild every registered match in parallel; with --repair, restore broken sources from
    the last commit (or drop the entry) so progress verification passes."""
    import subprocess
    from concurrent.futures import ThreadPoolExecutor

    manifest = json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))
    inventory()

    def check(entry: dict) -> str | None:
        name, info, target = target_bytes(entry["module"], entry["symbol"])
        with tempfile.TemporaryDirectory(prefix="verify-", dir=ROOT / "build") as temp:
            try:
                cm.compile_entry(entry, info["address"], Path(temp) / "o.bin")
                return None if (Path(temp) / "o.bin").read_bytes() == target else "bytes differ"
            except (RuntimeError, OSError) as error:
                return str(error).strip().splitlines()[-1][:160] if str(error).strip() else "error"

    with ThreadPoolExecutor(args.jobs) as pool:
        problems = [(e, p) for e, p in zip(manifest["matches"], pool.map(check, manifest["matches"])) if p]
    print(f"{len(manifest['matches']) - len(problems)} verified, {len(problems)} broken")
    for entry, problem in problems:
        print(f"  {entry['module']}:{entry['symbol']} {entry['source']}: {problem}")
    if not args.repair or not problems:
        return 1 if problems else 0
    dropped = 0
    for entry, _ in problems:
        committed = subprocess.run(["git", "show", f"HEAD:{entry['source']}"], cwd=ROOT, capture_output=True)
        if committed.returncode == 0:
            write_source(ROOT / entry["source"], committed.stdout.replace(b"\r\n", b"\n"))
            if check(entry) is None:
                shutil.copyfile(ROOT / entry["source"], snapshot_path(entry))
                continue
        manifest["matches"].remove(entry)
        dropped += 1
    (ROOT / "matches.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"Repaired {len(problems) - dropped} from the last commit; dropped {dropped}")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    show = sub.add_parser("show")
    show.add_argument("module")
    show.add_argument("symbol")
    for command in ("try", "stage"):
        p = sub.add_parser(command)
        p.add_argument("module")
        p.add_argument("symbol")
        p.add_argument("source")
        p.add_argument("--compiler", default="mwccarm-4.0-1036", choices=sorted(cm.compiler_config()["variants"]))
        p.add_argument("--mode", choices=("arm", "thumb"))
        p.add_argument("--source-symbol", help="function name in the source (default: file stem)")
        if command == "stage":
            p.add_argument("--name", required=True)
            p.add_argument("--behavior", required=True)
            p.add_argument("--evidence")
            p.add_argument("--uncertainty", default="Callers not yet reviewed; role inferred from code only.")
            p.add_argument("--domain", default="unclassified_helpers")
            p.add_argument("--origin", default="independent C reconstruction")
            p.add_argument("--understanding", default="unknown", choices=("gameplay", "subsystem", "unknown"))
            p.add_argument("--provenance", help="JSON object when adapted from another project")
    sub.add_parser("merge")
    batch = sub.add_parser("batch")
    batch.add_argument("file")
    batch.add_argument("index", type=int)
    verify = sub.add_parser("verify")
    verify.add_argument("--repair", action="store_true")
    verify.add_argument("--jobs", type=int, default=16)
    args = parser.parse_args()
    return {"show": cmd_show, "try": cmd_try, "stage": cmd_stage, "merge": cmd_merge,
            "verify": cmd_verify, "batch": cmd_batch}[args.command](args) or 0


if __name__ == "__main__":
    raise SystemExit(main())
