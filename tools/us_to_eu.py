#!/usr/bin/env python3
"""Port verified US (BK9E) matches to their unmatched EU (BK9P) twins.

US and EU functions are paired by name or by their place in each module (same order,
same sizes). For each pair whose EU side has no source yet, an EU wrapper is written:
`#define US_NAME EU_NAME` lines plus an `#include` of the US source, so the C stays
in src/ once. The wrapper is compiled with the EU toolchain; its text must equal the
EU ROM bytes with relocated words masked, at the same relocation offsets, and every
relocation must resolve to the EU symbol relocs.txt names. Only then is the wrapper
written and its range claimed in delinks.txt.

    python tools/us_to_eu.py [--jobs N] [--dry-run] [--module ovNNN]

Run the EU gate afterwards (`python tools/khrecoded.py eu gate`).
"""

from __future__ import annotations

import argparse
import difflib
import json
import re
import subprocess
import sys
import tempfile
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[1]
EU = ROOT / "eu"
sys.path.insert(0, str(ROOT / "tools"))
from dedupe_regions import ALTERNATE_COMPILERS, US_COMPILER_DIRS, module_functions  # noqa: E402

PLACEHOLDER = re.compile(r"^func_(?:ov\d{3}_)?[0-9a-f]{8}$")
SYMBOL_LINE = re.compile(r"^(\S+)\s+kind:(\w+)[^\r\n]*?addr:0x([0-9a-fA-F]+)")
RELOC_LINE = re.compile(r"^from:0x([0-9a-fA-F]+)\s+kind:(\S+)\s+to:0x([0-9a-fA-F]+)\s+module:(\S+)")
TEXT_LINE = re.compile(r"^\s*\.text\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)")
SCRATCH = EU / "build" / "us_to_eu"


def config_dir(module: str) -> Path:
    base = EU / "config" / "arm9"
    return base if module == "arm9" else base / module if module in ("itcm", "dtcm") else base / "overlays" / module


def binary_path(module: str) -> Path:
    if module == "arm9":
        return EU / "dsd_extract" / "arm9" / "arm9.bin"
    if module in ("itcm", "dtcm"):
        return EU / "dsd_extract" / "arm9" / f"{module}.bin"
    return EU / "dsd_extract" / "arm9_overlays" / f"{module}.bin"


def reloc_key(module: str) -> str:
    return "main" if module == "arm9" else f"overlay({int(module[2:])})" if module.startswith("ov") else module


def target_keys(name: str) -> list[str]:
    found = re.fullmatch(r"overlays\(([\d,]+)\)", name)
    return [f"overlay({n})" for n in found.group(1).split(",")] if found else [name]


class EuModel:
    """EU ROM bytes, symbols, relocations and claimed ranges per module."""

    def __init__(self):
        self.modules = sorted(["arm9", "itcm", "dtcm"] + [p.name for p in (EU / "config" / "arm9" / "overlays").glob("ov*")])
        self.symbols: dict[str, dict[int, str]] = {}
        self.relocs: dict[str, dict[int, tuple[int, str]]] = {}
        self.text_base: dict[str, int] = {}
        self.claimed: dict[str, list[tuple[int, int]]] = defaultdict(list)
        self.blobs: dict[str, bytes] = {}
        for module in self.modules:
            directory = config_dir(module)
            if not (directory / "symbols.txt").exists():
                continue
            table = self.symbols.setdefault(reloc_key(module), {})
            for line in (directory / "symbols.txt").read_text(encoding="utf-8").splitlines():
                found = SYMBOL_LINE.match(line)
                if found:
                    table.setdefault(int(found.group(3), 16), found.group(1))
            relocs = self.relocs.setdefault(module, {})
            if (directory / "relocs.txt").exists():
                for line in (directory / "relocs.txt").read_text(encoding="utf-8").splitlines():
                    found = RELOC_LINE.match(line)
                    if found:
                        relocs[int(found.group(1), 16)] = (int(found.group(3), 16), found.group(4))
            lines = (directory / "delinks.txt").read_text(encoding="utf-8").splitlines()
            in_file = False
            for line in lines:
                if line.endswith(":") and not line.startswith(" "):
                    in_file = True
                found = TEXT_LINE.match(line)
                if found and not in_file:
                    self.text_base[module] = int(found.group(1), 16)
                elif found:
                    self.claimed[module].append((int(found.group(1), 16), int(found.group(2), 16)))
            if binary_path(module).exists():
                self.blobs[module] = binary_path(module).read_bytes()

    def name_at(self, target: int, module_name: str) -> str | None:
        names = set()
        for key in target_keys(module_name):
            table = self.symbols.get(key, {})
            name = table.get(target) or table.get(target & ~1)
            if name:
                names.add(name)
        return next(iter(names)) if len(names) == 1 else None

    def function(self, module: str, address: int, size: int):
        base = self.text_base.get(module)
        blob = self.blobs.get(module)
        if base is None or blob is None or address - base + size > len(blob):
            return None
        data = blob[address - base:address - base + size]
        relocs = {a - address: t for a, t in self.relocs.get(module, {}).items() if address <= a < address + size}
        return data, relocs

    def is_claimed(self, module: str, address: int, size: int) -> bool:
        return any(start < address + size and address < end for start, end in self.claimed[module])


def eu_sources() -> set[str]:
    return {path.stem for top in ("src", "libs") for path in (EU / top).rglob("*")
            if path.is_file() and path.suffix.lower() in (".c", ".cpp", ".s")}


def candidate_pairs(model: EuModel, only: str | None, asm: bool = False):
    manifest = "asm_matches.json" if asm else "matches.json"
    us_matched = {(e["module"], e["symbol"]): e
                  for e in json.loads((ROOT / manifest).read_text(encoding="utf-8"))["matches"]
                  if asm or e.get("language", "c") == "c"}
    us_modules = module_functions(ROOT / "config" / "bk9e" / "arm9")
    eu_modules = module_functions(EU / "config" / "arm9")
    have_source = eu_sources()
    out = {}
    for module, us_rows in us_modules.items():
        if only and module != only:
            continue
        eu_rows = eu_modules.get(module, [])
        open_eu = {row[2]: row for row in eu_rows if row[2] not in have_source}
        pairs = []
        by_name = {row[2]: row for row in us_rows}
        for name, row in open_eu.items():
            if not PLACEHOLDER.match(name) and name in by_name:
                pairs.append((by_name[name], row))
        matcher = difflib.SequenceMatcher(None, [r[1] for r in us_rows], [r[1] for r in eu_rows], autojunk=False)
        for block in matcher.get_matching_blocks():
            pairs.extend((us_rows[block.a + k], eu_rows[block.b + k]) for k in range(block.size))
        for us_row, eu_row in pairs:
            entry = us_matched.get((module, us_row[2]))
            if not entry or eu_row[2] not in open_eu or us_row[1] != eu_row[1]:
                continue
            if model.is_claimed(module, eu_row[0], eu_row[1]):
                continue
            out.setdefault((module, eu_row[2]), (module, entry, eu_row))
    return list(out.values())


def read_object(path: Path, name: str):
    """(text bytes, {offset: (symbol, type, in-place word)}) for the one function in the object."""
    with path.open("rb") as handle:
        elf = ELFFile(handle)
        symtab = elf.get_section_by_name(".symtab")
        for section in elf.iter_sections():
            if section["sh_flags"] & 0x2 and section["sh_size"] and section.name not in (".text",):
                return None, "has data"
        text = elf.get_section_by_name(".text")
        functions = [s for s in symtab.iter_symbols() if s["st_info"]["type"] == "STT_FUNC"
                     and isinstance(s["st_shndx"], int) and not s.name.startswith("$")]
        if text is None or len(functions) != 1 or functions[0].name != name or functions[0]["st_value"] != 0:
            return None, "not one function"
        data = text.data()
        relocs = {}
        for section in elf.iter_sections():
            if not isinstance(section, RelocationSection) or elf.get_section(section["sh_info"]).name != ".text":
                continue
            for rel in section.iter_relocations():
                sym = symtab.get_symbol(rel["r_info_sym"])
                offset = rel["r_offset"]
                word = int.from_bytes(data[offset:offset + 4], "little")
                addend = rel.entry["r_addend"] if "r_addend" in rel.entry else word
                relocs[offset] = (sym.name, rel["r_info_type"], addend, sym["st_info"]["type"] == "STT_SECTION")
        return (data, relocs), None


def masked(data: bytes, offsets) -> bytes:
    out = bytearray(data)
    for offset in offsets:
        out[offset:offset + 4] = bytes(len(out[offset:offset + 4]))
    return bytes(out)


R_ARM_ABS32 = 2


def wrapper_text(mapping: dict[str, str], us_source: str) -> str:
    lines = [f"#define {us} {eu}" for us, eu in sorted(mapping.items()) if us != eu]
    return "\n".join(lines + [f'#include "{us_source}"', ""])


def destination(module: str, name: str, asm: bool = False) -> str:
    calls = "asm_stubs/calls" if asm else "calls"
    folder = f"src/overlays/{module}/{calls}" if module.startswith("ov") else f"src/{calls}"
    return f"{folder}/{name}.c"


def try_pair(model: EuModel, pair, scratch: Path):
    module, entry, (address, size, eu_name) = pair
    expected = model.function(module, address, size)
    if expected is None:
        return pair, None, "no rom bytes"
    rom, rom_relocs = expected
    mode = "thumb" if entry["mode"] == "thumb" else "arm"
    unit = destination(module, eu_name, entry.get("language") == "asm")
    work = scratch / unit
    work.parent.mkdir(parents=True, exist_ok=True)
    out = work.with_suffix(".o")
    us_cc = US_COMPILER_DIRS.get(entry.get("compiler"))
    status = "compile"
    for cc in dict.fromkeys([us_cc, *ALTERNATE_COMPILERS]):
        mapping = {entry["source_symbol"]: eu_name}
        for attempt in range(2):
            text = wrapper_text(mapping, entry["source"])
            work.write_text(text, encoding="utf-8", newline="\n")
            out.unlink(missing_ok=True)
            result = subprocess.run([sys.executable, str(EU / "tools" / "_run_mwcc.py"), str(out), str(work),
                                     f"--unit={unit}", f"--mode={mode}", f"--cc={cc}"],
                                    capture_output=True, text=True, cwd=EU)
            if result.returncode or not out.exists():
                break
            found, why = read_object(out, eu_name)
            if found is None:
                return pair, None, why
            data, relocs = found
            if len(data) != size:
                status = "size differs"
                break
            if set(relocs) != set(rom_relocs) or masked(data, relocs) != masked(rom, relocs):
                status = "bytes differ"
                break
            renames, ok = {}, True
            for offset, (symbol, kind, addend, is_section) in relocs.items():
                target, target_module = rom_relocs[offset]
                addend = addend if kind == R_ARM_ABS32 else 0
                want = model.name_at(target - addend, target_module)
                if want is None or is_section:
                    ok = False
                    break
                if symbol != want and renames.setdefault(symbol, want) != want:
                    ok = False
                    break
            if not ok:
                status = "relocation names"
                break
            if not renames:
                return pair, (text, cc), "ok"
            if attempt:
                status = "relocation names"
                break
            mapping = {**mapping, **renames}
    return pair, None, status


def claim(module: str, unit: str, address: int, size: int):
    path = config_dir(module) / "delinks.txt"
    text = path.read_text(encoding="utf-8").rstrip()
    line = f"    .text       start:0x{address:08x} end:0x{address + size:08x}"
    path.write_text(f"{text}\n\n{unit}:\n    complete\n{line}\n", encoding="utf-8", newline="\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--module")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--asm", action="store_true", help="port asm_matches.json entries into EU asm_stubs/")
    args = parser.parse_args()
    model = EuModel()
    pairs = candidate_pairs(model, args.module, args.asm)
    if args.limit:
        pairs = pairs[:args.limit]
    print(f"{len(pairs)} US matches with an open EU twin ({sum(p[2][1] for p in pairs):,} bytes)", flush=True)
    SCRATCH.mkdir(parents=True, exist_ok=True)
    results = defaultdict(int)
    ported = []
    compilers_path = EU / "config" / "arm9" / "file_compilers.json"
    compilers = json.loads(compilers_path.read_text(encoding="utf-8"))
    with tempfile.TemporaryDirectory(dir=SCRATCH) as temp, ThreadPoolExecutor(args.jobs) as pool:
        for pair, found, status in pool.map(lambda p: try_pair(model, p, Path(temp)), pairs):
            results[status] += 1
            if found is None:
                continue
            module, entry, (address, size, eu_name) = pair
            text, cc = found
            unit = destination(module, eu_name, args.asm)
            ported.append({"module": module, "eu": eu_name, "us": entry["symbol"], "size": size, "source": unit})
            if args.dry_run:
                continue
            path = EU / unit
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8", newline="\n")
            claim(module, unit, address, size)
            if cc not in ("3.0_patch4", "2.0/sp2p4"):
                compilers[unit] = cc
    if not args.dry_run:
        compilers_path.write_text(json.dumps(compilers, indent=2) + "\n", encoding="utf-8")
    (ROOT / "build" / "us_to_eu.json").write_text(json.dumps({"results": results, "ported": ported}, indent=1) + "\n",
                                                  encoding="utf-8")
    print(dict(results), f"-> {len(ported)} EU functions ({sum(p['size'] for p in ported):,} bytes)"
          f"{' would be' if args.dry_run else ''} ported")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
