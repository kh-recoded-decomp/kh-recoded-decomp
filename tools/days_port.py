#!/usr/bin/env python3
"""Port functions shared with the CC0 Kingdom Hearts 358/2 Days decompilation.

Re:coded reuses the Days engine and the same Nitro middleware. The method:

1. compile   Build every Days C file with both pinned compilers (no ROM needed).
2. scan      Compare each compiled Days function with every BK9E function of the
             same size. Relocated words (calls, pointers) are masked; all other
             bytes must be identical. Each relocation is then solved against the
             BK9E instruction, giving the Re:coded address of every callee/global.
3. port      Write a Re:coded source (comments stripped, Days addresses renamed
             to Re:coded ones), rebuild it with compile_match, and register it in
             matches.json only if all bytes match.

Set KHDAYS_ROOT to the Days checkout (default ../decomp-references/khdays-decomp).
"""

from __future__ import annotations

import argparse
import io
import json
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compile_match as cm  # noqa: E402
import khrecoded as kh  # noqa: E402

ROOT = kh.ROOT
DAYS = Path(os.environ.get("KHDAYS_ROOT", ROOT.parent / "decomp-references" / "khdays-decomp"))
WORK = ROOT / "build" / "days_port"
VARIANTS = ("mwccarm-4.0-1036", "mwccarm-3.0-139")
FUNCTION_LINE = re.compile(r"^(\S+) kind:function\((arm|thumb),size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", re.I)
ADDRESS_NAME = re.compile(r"^(?:func|data|sub|FUN|DAT)_(?:ov\d+_)?[0-9a-fA-F]{7,8}$")
PROJECT = "Yokimitsuro/khdays-decomp"
R_ABS32, R_PC24, R_THM_CALL = 2, 1, 10


def days_revision() -> str:
    return subprocess.run(["git", "rev-parse", "HEAD"], cwd=DAYS, capture_output=True,
                          text=True, check=True).stdout.strip()


def days_sources() -> list[Path]:
    return sorted(p for top in ("src", "libs") for p in (DAYS / top).rglob("*.c"))


def days_thumb_names() -> set[str]:
    names = set()
    for path in (DAYS / "config").rglob("symbols.txt"):
        for line in path.read_text(encoding="utf-8").splitlines():
            m = FUNCTION_LINE.match(line)
            if m and m.group(2) == "thumb":
                names.add(m.group(1))
    return names


# --------------------------------------------------------------------------- compile

def compiler_command(variant: str, source: Path, obj: Path, thumb: bool) -> list[str]:
    config = cm.compiler_config()
    exe = ROOT / config["variants"][variant]["executable"]
    flags = list(config["flags"]) + ["-i", str(DAYS / "include")] + (["-thumb"] if thumb else [])
    return [str(exe), *flags, "-o", str(obj), str(source)]


def read_functions(obj: bytes) -> list[dict]:
    """Every sized function in .text with its bytes, mode and relocations."""
    from elftools.elf.elffile import ELFFile

    elf = ELFFile(io.BytesIO(obj))
    symtab = elf.get_section_by_name(".symtab")
    text_index = next((i for i, s in enumerate(elf.iter_sections()) if s.name == ".text"), None)
    if symtab is None or text_index is None:
        return []
    text = elf.get_section(text_index).data()
    mapping = sorted((s["st_value"], s.name) for s in symtab.iter_symbols()
                     if s.name in ("$a", "$t", "$d") and s["st_shndx"] == text_index)
    relocs = []
    for section in elf.iter_sections():
        if section["sh_type"] == "SHT_RELA" and section["sh_info"] == text_index:
            for r in section.iter_relocations():
                sym = symtab.get_symbol(r["r_info_sym"])
                shndx = sym["st_shndx"]
                where = ("undef" if shndx == "SHN_UNDEF" else "text" if shndx == text_index
                         else elf.get_section(shndx).name if isinstance(shndx, int) else str(shndx))
                value = sym["st_value"]
                if (where == "text" and sym["st_info"]["type"] == "STT_FUNC"
                        and not sym.name.startswith("$")):
                    marks = [name for offset, name in mapping if offset <= (value & ~1)]
                    if marks and marks[-1] == "$t":
                        value |= 1
                relocs.append((r["r_offset"], r["r_info_type"], sym.name, r["r_addend"], where,
                               value))
    functions = []
    for s in symtab.iter_symbols():
        if (s["st_info"]["type"] != "STT_FUNC" or s["st_shndx"] != text_index or not s["st_size"]
                or s.name.startswith("$")):
            continue
        start, size = s["st_value"] & ~1, s["st_size"]
        marks = [name for value, name in mapping if value <= start]
        mode = "thumb" if marks and marks[-1] == "$t" else "arm"
        own = [[o - start, t, n, a, w, v] for o, t, n, a, w, v in relocs if start <= o < start + size]
        functions.append({"name": s.name, "global": s["st_info"]["bind"] == "STB_GLOBAL",
                          "offset": start, "mode": mode, "hex": text[start:start + size].hex(),
                          "relocs": own})
    return functions


def compile_one(args: tuple[str, Path, set[str], Path, bool]) -> dict:
    variant, source, thumb_names, outdir, force_thumb = args
    rel = source.relative_to(DAYS).as_posix()
    obj = outdir / (re.sub(r"[^A-Za-z0-9_.-]", "_", rel) + ".o")
    env = dict(os.environ, LM_LICENSE_FILE=str(ROOT / cm.compiler_config()["license"]))
    result = {"source": rel, "functions": [], "error": None}
    for thumb in ((True,) if force_thumb else (False, True)):
        done = subprocess.run(compiler_command(variant, source, obj, thumb), cwd=DAYS, env=env,
                              capture_output=True, text=True)
        if done.returncode:
            result["error"] = (done.stdout + done.stderr)[-400:]
            return result
        functions = read_functions(obj.read_bytes())
        wants_thumb = any(f["name"] in thumb_names and f["mode"] == "arm" for f in functions)
        result["functions"], result["thumb_flag"] = functions, thumb
        if thumb or not wants_thumb or force_thumb:
            return result
    return result


def compiled_files() -> list[tuple[str, Path]]:
    """(variant, path) for ARM builds and forced-Thumb rebuilds of the Days sources."""
    return [(v, WORK / f"compiled-{v}{suffix}.json") for suffix in ("", "-thumb") for v in VARIANTS
            if (WORK / f"compiled-{v}{suffix}.json").exists()]


def compile_all(jobs: int, force_thumb: bool, variants: list[str]) -> None:
    """Re:coded builds most game code as Thumb, Days mostly as ARM: build both ways."""
    thumb_names = days_thumb_names()
    sources = days_sources()
    suffix = "-thumb" if force_thumb else ""
    for variant in variants:
        outdir = WORK / "obj" / (variant + suffix)
        outdir.mkdir(parents=True, exist_ok=True)
        with ThreadPoolExecutor(jobs) as pool:
            results = list(pool.map(compile_one, [(variant, s, thumb_names, outdir, force_thumb) for s in sources]))
        (WORK / f"compiled-{variant}{suffix}.json").write_text(json.dumps(results), encoding="utf-8")
        failed = sum(1 for r in results if r["error"])
        count = sum(len(r["functions"]) for r in results)
        print(f"{variant}: {len(sources)} sources, {failed} failed, {count} functions")


# --------------------------------------------------------------------------- scan

def recoded_functions() -> dict:
    """BK9E functions with bytes, mode and match status, grouped by size."""
    inv = kh.inventory()
    matched = {(m["module"], m["symbol"]) for m in json.loads((ROOT / "matches.json").read_text())["matches"]}
    by_size: dict[int, list[dict]] = {}
    for module, data in inv.items():
        if module == "arm7":
            continue
        folder = kh.DSD_CONFIG.parent if module == "arm9" else (
            kh.DSD_CONFIG.parent / module if module in ("itcm", "dtcm") else kh.DSD_CONFIG.parent / "overlays" / module)
        modes = {m.group(1): m.group(2) for m in map(FUNCTION_LINE.match,
                 (folder / "symbols.txt").read_text(encoding="utf-8").splitlines()) if m}
        blob = data["binary"].read_bytes()
        for symbol, info in data["symbols"].items():
            offset = info["address"] - data["base"]
            by_size.setdefault(info["size"], []).append({
                "module": module, "symbol": symbol, "address": info["address"], "mode": modes[symbol],
                "bytes": blob[offset:offset + info["size"]], "matched": (module, symbol) in matched})
    return by_size


def solve_symbol(kind: int, days_word: int, recoded_word: int, addend: int, place: int) -> int | None:
    """Recover the symbol value that relocates days_word into recoded_word."""
    candidates = []
    if kind == R_ABS32:
        candidates.append((recoded_word - addend) & 0xFFFFFFFF)
    elif kind == R_PC24:
        offset = ((recoded_word & 0xFFFFFF) ^ 0x800000) - 0x800000
        if recoded_word >> 25 == 0x7D:  # BLX imm: Thumb target, H bit gives bit 1
            candidates.append((place - addend + (offset << 2) + ((recoded_word >> 23) & 2)) | 1)
        else:
            candidates.append(place - addend + (offset << 2))
    elif kind == R_THM_CALL:
        first, second = recoded_word & 0xFFFF, recoded_word >> 16
        raw = ((first & 0x7FF) << 12) | ((second & 0x7FF) << 1)
        offset = (raw ^ 0x400000) - 0x400000
        if second & 0xF800 == 0xE800:
            candidates.append((place & ~3) - addend + offset)
        else:
            candidates.append((place - addend + offset) | 1)
    for value in candidates:
        try:
            if cm.relocate_word(days_word, kind, value, addend, place) == recoded_word:
                return value
        except RuntimeError:
            pass
    return None


def try_candidate(days_fn: dict, target: dict) -> tuple[dict | None, str]:
    """Return bindings when all unrelocated bytes match and every relocation solves."""
    days = bytes.fromhex(days_fn["hex"])
    recoded = target["bytes"]
    masked = set()
    for offset, *_ in days_fn["relocs"]:
        masked.update(range(offset, offset + 4))
    if any(days[i] != recoded[i] for i in range(len(days)) if i not in masked):
        return None, "bytes"
    bindings: dict[str, int] = {}
    for offset, kind, name, addend, where, value in days_fn["relocs"]:
        if offset + 4 > len(days):
            return None, "reloc-span"
        days_word = int.from_bytes(days[offset:offset + 4], "little")
        recoded_word = int.from_bytes(recoded[offset:offset + 4], "little")
        place = target["address"] + offset
        if where == "text":
            local = target["address"] + value - days_fn["offset"]
            try:
                ok = cm.relocate_word(days_word, kind, local, addend, place) == recoded_word
            except RuntimeError:
                ok = False
            if not ok:
                return None, "local-layout"
            continue
        if where != "undef":
            return None, "data-section"
        solved = solve_symbol(kind, days_word, recoded_word, addend, place)
        if solved is None or bindings.get(name, solved) != solved:
            return None, "reloc-solve"
        bindings[name] = solved
    return bindings, "ok"


def source_rank(rel: str, name: str) -> tuple:
    descriptive = not ADDRESS_NAME.match(name)
    return (0 if rel.startswith("libs/") else 1 if rel.startswith("src/engine") else 2,
            0 if descriptive else 1, len(rel), rel, name)


def scan() -> None:
    by_size = recoded_functions()
    candidates: dict[tuple[str, str], list[dict]] = {}
    reasons: dict[str, int] = {}
    for variant, path in compiled_files():
        for record in json.loads(path.read_text(encoding="utf-8")):
            for fn in record["functions"]:
                size = len(fn["hex"]) // 2
                for target in by_size.get(size, ()):
                    if target["mode"] != fn["mode"]:
                        continue
                    bindings, why = try_candidate(fn, target)
                    if why != "bytes":
                        reasons[why] = reasons.get(why, 0) + 1
                    if bindings is None:
                        continue
                    key = (target["module"], target["symbol"])
                    candidates.setdefault(key, []).append({
                        "module": target["module"], "symbol": target["symbol"],
                        "address": target["address"], "size": size, "mode": fn["mode"],
                        "matched": target["matched"], "variant": variant,
                        "days_source": record["source"], "days_name": fn["name"],
                        "thumb_flag": record.get("thumb_flag", False),
                        "relocs": len(fn["relocs"]),
                        "bindings": {k: hex(v) for k, v in bindings.items()}})
    for key, options in candidates.items():
        options.sort(key=lambda c: (source_rank(c["days_source"], c["days_name"]), VARIANTS.index(c["variant"])))
    rows = [options for options in candidates.values()]
    (WORK / "candidates.json").write_text(json.dumps(rows, indent=1), encoding="utf-8")
    new = [o[0] for o in rows if not o[0]["matched"]]
    print(f"Candidate BK9E functions: {len(rows)} ({len(new)} unmatched, "
          f"{sum(c['size'] for c in new):,} bytes); near-miss reasons: {reasons}")


# --------------------------------------------------------------------------- similar

def shingles(code: bytes, mode: str, md_cache: dict) -> set[int]:
    """Hashed 4-grams of mnemonics: stable across address and struct-offset changes."""
    import capstone

    if mode not in md_cache:
        md_cache[mode] = capstone.Cs(capstone.CS_ARCH_ARM,
                                     capstone.CS_MODE_THUMB if mode == "thumb" else capstone.CS_MODE_ARM)
    ops = [insn.mnemonic for insn in md_cache[mode].disasm(code, 0)]
    return {hash(tuple(ops[i:i + 4])) for i in range(max(0, len(ops) - 3))}


def similar(top: int) -> None:
    """For every unmatched BK9E function, list the closest compiled Days functions."""
    md: dict = {}
    days, posting = [], {}
    for variant, path in compiled_files():
        if variant != VARIANTS[0]:
            continue
        for record in json.loads(path.read_text(encoding="utf-8")):
            for fn in record["functions"]:
                grams = shingles(bytes.fromhex(fn["hex"]), fn["mode"], md)
                if len(grams) < 3:
                    continue
                index = len(days)
                days.append((record["source"], fn["name"], len(fn["hex"]) // 2, len(grams)))
                for g in grams:
                    posting.setdefault(g, []).append(index)
    common = {g for g, ids in posting.items() if len(ids) > 400}
    result = {}
    for size, targets in recoded_functions().items():
        for target in targets:
            if target["matched"]:
                continue
            grams = shingles(target["bytes"], target["mode"], md) - common
            if len(grams) < 3:
                continue
            counts: dict[int, int] = {}
            for g in grams:
                for index in posting.get(g, ()):
                    counts[index] = counts.get(index, 0) + 1
            scored = sorted(((c / (len(grams) + days[i][3] - c), i) for i, c in counts.items()), reverse=True)
            best = [{"days_source": days[i][0], "days_name": days[i][1], "days_size": days[i][2],
                     "score": round(s, 3)} for s, i in scored[:top] if s >= 0.3]
            if best:
                result[f"{target['module']}:{target['symbol']}"] = best
    (WORK / "similar.json").write_text(json.dumps(result, indent=1), encoding="utf-8")
    print(f"Similar Days functions found for {len(result)} unmatched BK9E functions")


# --------------------------------------------------------------------------- port

def strip_comments(text: str) -> str:
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            out.append(text[i:j + 1])
            i = j + 1
        elif text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("\n" * text.count("\n", i, j) if "\n" in text[i:j] else " ")
            i = j
        elif text.startswith("//", i):
            j = text.find("\n", i)
            i = n if j < 0 else j
        else:
            out.append(c)
            i += 1
    lines = [line.rstrip() for line in "".join(out).splitlines()]
    tidy: list[str] = []
    for line in lines:
        if not line and (not tidy or not tidy[-1]):
            continue
        tidy.append(line)
    return "\n".join(tidy).strip() + "\n"


def clean_name(days_name: str) -> str | None:
    if ADDRESS_NAME.match(days_name):
        return None
    name = re.sub(r"^[Oo]v\d{3}_", "", days_name)  # Days overlay numbers differ from Re:coded's
    name = re.sub(r"_(?:[0-9a-f]{8}|\d{1,2})$", "", name).rstrip("_")
    return name if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name) and not ADDRESS_NAME.match(name) else None


def category(rel: str) -> str:
    parts = rel.split("/")
    if parts[0] == "libs":
        return "library_msl_c" if parts[1] == "msl" else f"library_{parts[1]}_{parts[2]}"
    return "shared_engine"


def binding_name(name: str, value: int, functions: set[int]) -> str:
    if not ADDRESS_NAME.match(name):
        return name
    address = value & ~1
    return f"func_{address:08x}" if address in functions else f"data_{address:08x}"


def build_entry(candidate: dict, revision: str, functions: set[int]) -> tuple[dict, str]:
    rel = candidate["days_source"]
    days_name = candidate["days_name"]
    nice = clean_name(days_name)
    address = candidate["address"]
    symbol = candidate["symbol"]
    source_symbol = f"{nice}_{address:08x}" if nice else symbol
    renames = {days_name: source_symbol}
    bindings = {}
    for name, value in candidate["bindings"].items():
        new = binding_name(name, int(value, 16), functions)
        renames[name] = new
        if new in bindings and bindings[new] != value:
            raise RuntimeError("two Days symbols resolve to one name with different addresses")
        bindings[new] = value
    text = strip_comments((DAYS / rel).read_text(encoding="utf-8"))
    for old, new in renames.items():
        if old != new:
            if re.search(rf"\b{re.escape(new)}\b", text):
                raise RuntimeError(f"renamed symbol {new} already exists in source")
            text = re.sub(rf"\b{re.escape(old)}\b", new, text)
    library = rel.startswith("libs/")
    size = candidate["size"]
    generic = candidate["relocs"] == 0 and size <= 16
    label = nice if nice and not generic else symbol
    if rel.startswith("libs/msl"):
        behavior = f"C standard library routine {label}."
    elif library:
        behavior = f"Nitro middleware routine {label}; no direct gameplay role on its own."
    else:
        behavior = f"Shared engine routine, identical to KH 358/2 Days {nice or days_name}."
    entry = {
        "module": candidate["module"], "symbol": symbol, "name": label, "language": "c",
        "source": f"src/{candidate['module']}/{category(rel)}/{source_symbol}.c",
        "source_symbol": source_symbol, "compiler": candidate["variant"], "mode": candidate["mode"],
        "bindings": bindings, "behavior": behavior,
        "evidence": (f"Relocation-masked bytes equal KH Days {days_name} ({rel}); every call and "
                     f"pointer resolves consistently and the rebuilt C matches all {size} bytes."),
        "uncertainty": ("Tiny generic body; name kept address-based." if generic else
                        "Name and role come from the Days decompilation; Re:coded callers not reviewed."),
        "domain": category(rel) if library else "shared_engine",
        "origin": "adapted CC0 library C" if library else "adapted CC0 shared C",
        "understanding": "subsystem" if (library and nice and not generic) else "unknown",
        "provenance": {"project": PROJECT, "revision": revision, "source": rel, "license": "CC0-1.0"},
    }
    return entry, text


SCRATCH = ROOT / "src" / ".port_scratch"  # compile_entry only accepts sources under src/


def verify_source(entry: dict, text: str, address: int, expected: bytes) -> str | None:
    """Compile text exactly as the manifest will; None means every byte matched."""
    SCRATCH.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="port-", dir=SCRATCH) as temp:
        staged = Path(temp) / f"{entry['source_symbol']}.c"
        staged.write_text(text, encoding="utf-8")
        trial = dict(entry, source=staged.relative_to(ROOT).as_posix())
        try:
            cm.compile_entry(trial, address, Path(temp) / "out.bin")
        except RuntimeError as error:
            lines = str(error).strip().splitlines()
            return lines[-1][:200] if lines else "error"
        actual = (Path(temp) / "out.bin").read_bytes()
    if actual != expected:
        return f"mismatch (compiled {len(actual)} vs {len(expected)} bytes)"
    return None


def port(limit: int | None, jobs: int, module: str | None) -> None:
    rows = json.loads((WORK / "candidates.json").read_text(encoding="utf-8"))
    manifest_path = ROOT / "matches.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    claimed = {(m["module"], m["symbol"]) for m in manifest["matches"]}
    inv = kh.inventory()
    spans = {}
    for m in manifest["matches"]:
        info = inv[m["module"]]["symbols"][m["symbol"]]
        spans.setdefault(m["module"], []).append((info["address"], info["address"] + info["size"]))
    functions = {info["address"] for data in inv.values() for info in data["symbols"].values()}
    blobs = {name: (data["base"], data["binary"].read_bytes()) for name, data in inv.items() if name != "arm7"}
    revision = days_revision()
    todo = [r for r in rows if (r[0]["module"], r[0]["symbol"]) not in claimed
            and (module is None or r[0]["module"] == module)]
    todo.sort(key=lambda r: -r[0]["size"])
    if limit:
        todo = todo[:limit]

    def attempt(options: list[dict]):
        errors = []
        first = options[0]
        base, blob = blobs[first["module"]]
        expected = blob[first["address"] - base:first["address"] - base + first["size"]]
        for candidate in options[:6]:
            try:
                entry, text = build_entry(candidate, revision, functions)
            except RuntimeError as error:
                errors.append(str(error))
                continue
            problem = verify_source(entry, text, candidate["address"], expected)
            if problem is None:
                return entry, text, None
            errors.append(f"{candidate['variant']} {candidate['days_name']}: {problem}")
        return None, None, errors

    with ThreadPoolExecutor(jobs) as pool:
        results = list(pool.map(attempt, todo))
    added, failures, used_paths = [], [], set()
    for options, (entry, text, errors) in zip(todo, results):
        if entry is None:
            failures.append({"module": options[0]["module"], "symbol": options[0]["symbol"],
                             "size": options[0]["size"], "errors": errors})
            continue
        address, stop = options[0]["address"], options[0]["address"] + options[0]["size"]
        if any(address < b and a < stop for a, b in spans.get(entry["module"], [])):
            continue
        path = ROOT / entry["source"]
        if entry["source"] in used_paths or path.exists():
            continue
        used_paths.add(entry["source"])
        spans.setdefault(entry["module"], []).append((address, stop))
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")
        manifest["matches"].append(entry)
        added.append(entry)
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    (WORK / "port-failures.json").write_text(json.dumps(failures, indent=1), encoding="utf-8")
    total = sum(inv[e["module"]]["symbols"][e["symbol"]]["size"] for e in added)
    print(f"Ported {len(added)} functions ({total:,} bytes); {len(failures)} candidates failed verification")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("command", choices=["compile", "scan", "similar", "port"])
    parser.add_argument("--jobs", type=int, default=max(2, (os.cpu_count() or 4) - 2))
    parser.add_argument("--limit", type=int)
    parser.add_argument("--module")
    parser.add_argument("--thumb", action="store_true", help="compile: force Thumb for every Days source")
    parser.add_argument("--variant", action="append", choices=VARIANTS, help="compile: compiler(s) to use")
    args = parser.parse_args()
    WORK.mkdir(parents=True, exist_ok=True)
    if args.command == "compile":
        compile_all(args.jobs, args.thumb, args.variant or list(VARIANTS))
    elif args.command == "scan":
        scan()
    elif args.command == "similar":
        similar(4)
    else:
        port(args.limit, args.jobs, args.module)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
