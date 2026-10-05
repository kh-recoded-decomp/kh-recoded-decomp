#!/usr/bin/env python3
"""Verify C sources that reconstruct ARM9 data sections (.rodata, .data, .bss).

Each entry in data_matches.json names one address range inside one section of one
module. Its source is compiled with the pinned compiler; the object must contain
exactly that section with exactly that size. Pointers are applied as R_ARM_ABS32
relocations against the project's symbol tables, then every byte must equal the
original. A .bss range only has to match in size, since it holds no bytes.
"""

from __future__ import annotations

import argparse
import hashlib
import io
import json
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import compile_match  # noqa: E402

REGISTRY = ROOT / "data_matches.json"
CONFIG = ROOT / "config" / "bk9e" / "arm9"
EXTRACT = ROOT / "build" / "bk9e" / "extract"
CACHE = ROOT / "build" / "bk9e" / "data_objects"
SECTIONS = {".rodata": "rodata", ".data": "data", ".bss": "bss"}
SYMBOL_LINE = re.compile(r"^(\S+) kind:(\w+)(\(([^)]*)\))? addr:0x([0-9a-f]+)", re.I)
METADATA = {"", ".symtab", ".strtab", ".shstrtab", ".comment"}


def module_dir(module: str) -> Path:
    if module == "arm9":
        return CONFIG
    if module in ("itcm", "dtcm"):
        return CONFIG / module
    return CONFIG / "overlays" / module


def module_binary(module: str) -> tuple[int, bytes]:
    path = {"arm9": EXTRACT / "arm9" / "arm9.bin", "itcm": EXTRACT / "arm9" / "itcm.bin",
            "dtcm": EXTRACT / "arm9" / "dtcm.bin"}.get(module, EXTRACT / "arm9_overlays" / f"{module}.bin")
    header = (module_dir(module) / "delinks.txt").read_text(encoding="utf-8")
    base = min(int(x, 16) for x in re.findall(r"start:0x([0-9a-f]+)", header))
    return base, path.read_bytes()


def section_spans(module: str) -> dict[str, list[tuple[int, int]]]:
    header = (module_dir(module) / "delinks.txt").read_text(encoding="utf-8")
    spans: dict[str, list[tuple[int, int]]] = {}
    for start, end, kind in re.findall(r"start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:(\w+)", header):
        spans.setdefault(kind, []).append((int(start, 16), int(end, 16)))
    return spans


def all_modules() -> list[str]:
    return ["arm9", "itcm", "dtcm"] + sorted(p.name for p in (CONFIG / "overlays").iterdir())


def symbol_index() -> dict[str, list[tuple[str, int, bool]]]:
    """Every name a source may use for an address: dsd names, matched C names, data names."""
    index: dict[str, list[tuple[str, int, bool]]] = {}
    by_module_addr: dict[tuple[str, int], bool] = {}
    for module in all_modules():
        for line in (module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
            found = SYMBOL_LINE.match(line)
            if found:
                address = int(found.group(5), 16)
                thumb = found.group(2) == "function" and (found.group(4) or "").startswith("thumb")
                by_module_addr[(module, address)] = thumb
                index.setdefault(found.group(1), []).append((module, address, thumb))
    names = {}
    for line_module in all_modules():
        for line in (module_dir(line_module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
            found = SYMBOL_LINE.match(line)
            if found:
                names[(line_module, found.group(1))] = int(found.group(5), 16)
    matches = json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]
    for entry in matches:
        address = names.get((entry["module"], entry["symbol"]))
        if address is not None and entry.get("source_symbol"):
            thumb = by_module_addr.get((entry["module"], address), False)
            index.setdefault(entry["source_symbol"], []).append((entry["module"], address, thumb))
    return index


def resolve(name: str, module: str, index: dict) -> tuple[str, int, bool]:
    candidates = index.get(name, [])
    for preferred in (module, "arm9", "itcm", "dtcm"):
        hits = [c for c in candidates if c[0] == preferred]
        if hits:
            return hits[0]
    if len({(m, a) for m, a, _ in candidates}) == 1:
        return candidates[0]
    raise RuntimeError(f"cannot resolve {name} from {module}")


def compile_source(entry: dict) -> bytes:
    source = ROOT / entry["source"]
    key = hashlib.sha256((source.read_text(encoding="utf-8") + entry["compiler"]).encode()).hexdigest()[:16]
    obj = CACHE / f"{Path(entry['source']).stem}_{key}.o"
    if not obj.exists():
        compile_match.validate_c_source(source)
        config = compile_match.compiler_config()
        variant = config["variants"][entry["compiler"]]
        flags = list(config["flags"]) + ["-i", str(compile_match.INCLUDE_DIR)]
        CACHE.mkdir(parents=True, exist_ok=True)
        env = dict(os.environ, LM_LICENSE_FILE=str(ROOT / config["license"]))
        result = subprocess.run([str(ROOT / variant["executable"]), *flags, "-o", str(obj), str(source)],
                                cwd=ROOT, env=env, capture_output=True, text=True)
        if result.returncode:
            raise RuntimeError(result.stdout + result.stderr)
    return obj.read_bytes()


def verify(entry: dict, index: dict) -> int:
    """Return the verified byte count, or raise with the first mismatch."""
    from elftools.elf.elffile import ELFFile

    module, section_name = entry["module"], entry["section"]
    start, end = int(entry["start"], 16), int(entry["end"], 16)
    kind = SECTIONS[section_name]
    header = (module_dir(module) / "delinks.txt").read_text(encoding="utf-8")
    named = [(int(a, 16), int(b, 16)) for name, a, b in
             re.findall(r"^\s*(\S+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:", header, re.M) if name == section_name]
    if not any(a <= start and end <= b for a, b in named):
        raise RuntimeError(f"{start:#x}-{end:#x} is not inside {module} {section_name}")
    elf = ELFFile(io.BytesIO(compile_source(entry)))
    allocated = [s for s in elf.iter_sections() if s["sh_flags"] & 2 and s["sh_size"]]
    if [s.name for s in allocated] != [section_name]:
        raise RuntimeError(f"object must contain only {section_name}, found {[s.name for s in allocated]}")
    section = allocated[0]
    if section["sh_size"] != end - start:
        raise RuntimeError(f"{section_name} size {section['sh_size']:#x} != range {end - start:#x}")
    symtab = elf.get_section_by_name(".symtab")
    index_of = elf.get_section_index(section_name)
    defined = {start + s["st_value"] for s in symtab.iter_symbols()
               if s["st_shndx"] == index_of and s["st_info"]["bind"] == "STB_GLOBAL"}
    for symbol in symtab.iter_symbols():
        suffix = re.search(r"_([0-9a-f]{8})$", symbol.name)
        if suffix and symbol["st_shndx"] == index_of and int(suffix.group(1), 16) != start + symbol["st_value"]:
            raise RuntimeError(f"{symbol.name} lands at {start + symbol['st_value']:#x}")
    for line in (module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
        found = SYMBOL_LINE.match(line)
        if found and found.group(2) in ("data", "bss") and start <= int(found.group(5), 16) < end:
            if int(found.group(5), 16) not in defined:
                raise RuntimeError(f"{found.group(1)} needs its own variable at {found.group(5)}")
    if kind == "bss":
        return end - start
    data = bytearray(section.data())
    for rel in elf.iter_sections():
        if rel["sh_type"] not in ("SHT_RELA", "SHT_REL") or rel["sh_info"] != index_of:
            continue
        for relocation in rel.iter_relocations():
            if relocation["r_info_type"] != 2:
                raise RuntimeError(f"unsupported relocation type {relocation['r_info_type']}")
            symbol = symtab.get_symbol(relocation["r_info_sym"])
            offset = relocation["r_offset"]
            addend = relocation["r_addend"] if rel["sh_type"] == "SHT_RELA" else struct.unpack_from("<I", data, offset)[0]
            if symbol["st_shndx"] == index_of:
                value = start + symbol["st_value"]
            elif symbol["st_shndx"] == "SHN_UNDEF":
                _, address, thumb = resolve(symbol.name, module, index)
                value = address | int(thumb)
            else:
                raise RuntimeError(f"relocation against unsupported section for {symbol.name}")
            struct.pack_into("<I", data, offset, (value + addend) & 0xFFFFFFFF)
    base, binary = module_binary(module)
    original = binary[start - base:end - base]
    if bytes(data) != original:
        first = next(i for i, (x, y) in enumerate(zip(data, original)) if x != y)
        raise RuntimeError(f"byte mismatch at {start + first:#x}: {data[first]:#04x} != {original[first]:#04x}")
    return end - start


def load() -> list[dict]:
    if not REGISTRY.exists():
        return []
    return json.loads(REGISTRY.read_text(encoding="utf-8"))["data"]


def save(entries: list[dict]) -> None:
    entries.sort(key=lambda e: (e["module"], int(e["start"], 16)))
    REGISTRY.write_text(json.dumps({"data": entries}, indent=2) + "\n", encoding="utf-8", newline="\n")


def totals() -> dict[str, int]:
    result = {"rodata": 0, "data": 0, "bss": 0}
    for module in all_modules():
        for kind, spans in section_spans(module).items():
            if kind in result:
                result[kind] += sum(b - a for a, b in spans)
    return result


def verify_all(entries: list[dict] | None = None) -> tuple[dict[str, int], list[str]]:
    entries = load() if entries is None else entries
    index = symbol_index()
    verified = {"rodata": 0, "data": 0, "bss": 0}
    failures = []
    for entry in entries:
        try:
            verified[SECTIONS[entry["section"]]] += verify(entry, index)
        except Exception as exc:  # noqa: BLE001 - every failure is reported
            failures.append(f"{entry['module']} {entry['start']} {entry['source']}: {str(exc).splitlines()[0]}")
    return verified, failures


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    add = sub.add_parser("add", help="Verify a data source and register it")
    add.add_argument("module")
    add.add_argument("section", choices=sorted(SECTIONS))
    add.add_argument("start")
    add.add_argument("end")
    add.add_argument("source")
    add.add_argument("--compiler", default="mwccarm-4.0-1036")
    add.add_argument("--name", required=True)
    add.add_argument("--behavior", required=True)
    sub.add_parser("verify", help="Verify every registered data source")
    args = parser.parse_args()
    if args.command == "add":
        entry = {"module": args.module, "section": args.section, "start": args.start, "end": args.end,
                 "source": Path(args.source).as_posix(), "compiler": args.compiler,
                 "name": args.name, "behavior": args.behavior}
        try:
            size = verify(entry, symbol_index())
        except Exception as exc:  # noqa: BLE001
            print(f"NO MATCH: {exc}")
            return 1
        entries = [e for e in load() if not (e["module"] == entry["module"] and e["start"] == entry["start"])]
        overlap = [e for e in entries if e["module"] == entry["module"] and
                   int(e["start"], 16) < int(entry["end"], 16) and int(entry["start"], 16) < int(e["end"], 16)]
        if overlap:
            print(f"ERROR: overlaps {overlap[0]['source']}")
            return 1
        save(entries + [entry])
        print(f"MATCH {args.module} {args.section} {args.start}-{args.end} ({size} bytes)")
        return 0
    verified, failures = verify_all()
    for failure in failures:
        print("FAIL", failure)
    total = totals()
    for kind in ("rodata", "data", "bss"):
        print(f"{kind}: {verified[kind]:,} / {total[kind]:,}")
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
