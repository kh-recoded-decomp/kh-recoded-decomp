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
import io
import json
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compile_match as cm  # noqa: E402
import khrecoded as kh  # noqa: E402

ROOT = kh.ROOT
PENDING = ROOT / "build" / "pending"
DECOMP = ROOT / "build" / "ghidra" / "decomp"
RELOC_LINE = re.compile(r"^from:0x([0-9a-f]+) kind:(\S+) to:0x([0-9a-f]+) module:(\S+)", re.I)
FUNCTION_LINE = re.compile(r"^(\S+) kind:function\((arm|thumb),size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", re.I)
ADDRESS_SUFFIX = re.compile(r"(?:^|_)([0-9a-fA-F]{8})$")
REQUIRED = ("name", "behavior", "evidence", "uncertainty", "domain", "origin", "understanding")


def config_dir(module: str) -> Path:
    base = kh.DSD_CONFIG.parent
    return base if module == "arm9" else base / module if module in ("itcm", "dtcm") else base / "overlays" / module


_inv = None


def inventory() -> dict:
    global _inv
    if _inv is None:
        _inv = kh.inventory()
        for module, data in _inv.items():
            if module == "arm7":
                continue
            data["modes"] = {}
            for line in (config_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
                m = FUNCTION_LINE.match(line)
                if m:
                    data["modes"][m.group(1)] = m.group(2)
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


def thumb_addresses() -> set[int]:
    result = set()
    for module, data in inventory().items():
        if module == "arm7":
            continue
        for name, info in data["symbols"].items():
            if data["modes"].get(name) == "thumb":
                result.add(info["address"])
    return result


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
    return {name: next(iter(v)) for name, v in names.items() if len(v) == 1}


def bind(name: str, thumbs: set[int], names: dict[str, int]) -> int | None:
    m = ADDRESS_SUFFIX.search(name)
    address = int(m.group(1), 16) if m else names.get(name)
    if address is None:
        return None
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
                    if sym["st_shndx"] == "SHN_UNDEF" and sym.name not in used:
                        used.append(sym.name)
    return used


def compile_candidate(module: str, symbol: str, source: Path, compiler: str, mode: str | None,
                      source_symbol: str | None) -> tuple[bytes | None, dict, str]:
    """Compile and link a candidate; returns (bytes, entry, error)."""
    name, info = resolve_function(module, symbol)
    mode = mode or inventory()[module]["modes"][name]
    source = source.resolve()
    if not source.is_relative_to(ROOT / "src"):
        raise SystemExit("Put the candidate under src/ (e.g. src/<module>/<area>/<Name>_<addr>.c)")
    source_symbol = source_symbol or source.stem
    entry = {"source": source.relative_to(ROOT).as_posix(), "source_symbol": source_symbol,
             "compiler": compiler, "mode": mode, "bindings": {}}
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
        for ext in undefined_symbols(obj.read_bytes(), source_symbol):
            value = bind(ext, thumbs, names)
            if value is None:
                missing.append(ext)
            else:
                entry["bindings"][ext] = hex(value)
        if missing:
            return None, entry, "Cannot bind externals (add an _<address> suffix): " + ", ".join(missing)
        try:
            cm.compile_entry(entry, info["address"], out)
            return out.read_bytes(), entry, ""
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
    similar_path = ROOT / "build" / "days_port" / "similar.json"
    if similar_path.exists():
        import days_port
        for hit in json.loads(similar_path.read_text(encoding="utf-8")).get(f"{args.module}:{name}", []):
            print(f"\nSimilar KH Days C (score {hit['score']}, {hit['days_size']} bytes): "
                  f"{days_port.DAYS / hit['days_source']} :: {hit['days_name']}")
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
        wmap, gmap = dict(want), dict(got)
        for offset, text in want:
            mark = "  " if all(target[i] == actual[i] for i in range(offset, min(offset + 4, len(target)))) else "!!"
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


def cmd_stage(args) -> int:
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
    PENDING.mkdir(parents=True, exist_ok=True)
    (PENDING / f"{args.module}__{name}.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    print(f"STAGED {args.module}:{name}")
    return 0


def cmd_merge(_args) -> int:
    path = ROOT / "matches.json"
    manifest = json.loads(path.read_text(encoding="utf-8"))
    claimed = {(m["module"], m["symbol"]) for m in manifest["matches"]}
    inv = inventory()
    spans = {}
    for m in manifest["matches"]:
        i = inv[m["module"]]["symbols"][m["symbol"]]
        spans.setdefault(m["module"], []).append((i["address"], i["address"] + i["size"]))
    added = rejected = 0
    for fragment in sorted(PENDING.glob("*.json")) if PENDING.exists() else []:
        record = json.loads(fragment.read_text(encoding="utf-8"))
        key = (record["module"], record["symbol"])
        info = inv[record["module"]]["symbols"][record["symbol"]]
        start, stop = info["address"], info["address"] + info["size"]
        ok = key not in claimed and all(isinstance(record.get(f), str) and record[f].strip() for f in REQUIRED)
        ok = ok and not any(start < b and a < stop for a, b in spans.get(record["module"], []))
        if ok:
            name, _, target = target_bytes(*key)
            with tempfile.TemporaryDirectory(prefix="merge-", dir=ROOT / "build") as temp:
                try:
                    cm.compile_entry(record, start, Path(temp) / "o.bin")
                    ok = (Path(temp) / "o.bin").read_bytes() == target
                except RuntimeError:
                    ok = False
        if ok:
            manifest["matches"].append(record)
            claimed.add(key)
            spans.setdefault(record["module"], []).append((start, stop))
            added += 1
            fragment.unlink()
        else:
            rejected += 1
            fragment.rename(fragment.with_suffix(".rejected"))
    path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"Merged {added} staged matches; rejected {rejected}")
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
    args = parser.parse_args()
    return {"show": cmd_show, "try": cmd_try, "stage": cmd_stage, "merge": cmd_merge}[args.command](args) or 0


if __name__ == "__main__":
    raise SystemExit(main())
