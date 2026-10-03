#!/usr/bin/env python3
"""Link registered C matches into the ARM9 modules in place of their delinked bytes.

Each matched source is compiled with its pinned compiler. Its object replaces the
function's address range as a dsd `complete` unit. Undefined symbols are renamed to
the canonical name at their bound address, so gap objects and C objects resolve
against each other. Objects the linker cannot place exactly (extra functions, data
sections, ambiguous overlay targets) stay as delinked bytes and are reported.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import compile_match  # noqa: E402
import data_match  # noqa: E402

CONFIG = ROOT / "config" / "bk9e" / "arm9"
LINK_CONFIG = ROOT / "build" / "linkcfg" / "arm9"
DELINKED = ROOT / "build" / "bk9e" / "delinked"
CACHE = ROOT / "build" / "bk9e" / "c_objects"
SYMBOL_LINE = re.compile(r"^(\S+) kind:(\w+)(\(([^)]*)\))? addr:0x([0-9a-f]+)", re.I)
RELOC_LINE = re.compile(r"^from:0x([0-9a-f]+) kind:(\S+) to:0x([0-9a-f]+) module:(\S+)", re.I)
ALLOWED_SECTIONS = {"", ".text", ".symtab", ".strtab", ".shstrtab", ".comment", ".rela.text"}


def module_dir(module: str) -> str:
    if module == "arm9":
        return ""
    if module in ("itcm", "dtcm"):
        return module
    return f"overlays/{module}"


def reloc_module(text: str) -> str | None:
    if text == "main":
        return "arm9"
    if text in ("itcm", "dtcm"):
        return text
    found = re.fullmatch(r"overlay\((\d+)\)", text)
    return f"ov{int(found.group(1)):03d}" if found else None


def reloc_modules(text: str) -> list[str]:
    found = re.fullmatch(r"overlays\(([\d,\s]+)\)", text)
    if found:
        return [f"ov{int(n):03d}" for n in found.group(1).split(",")]
    single = reloc_module(text)
    return [single] if single else []


def load_symbols(module: str) -> list[list]:
    rows = []
    for line in (CONFIG / module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
        found = SYMBOL_LINE.match(line)
        rows.append([found.group(1), found.group(2), int(found.group(5), 16), line] if found else [None, None, None, line])
    return rows


def load_relocs(module: str) -> dict[int, str]:
    result = {}
    for line in (CONFIG / module_dir(module) / "relocs.txt").read_text(encoding="utf-8").splitlines():
        found = RELOC_LINE.match(line)
        if found:
            result[int(found.group(1), 16)] = found.group(4)
    return result


def read_elf(data: bytes):
    shoff, = struct.unpack_from("<I", data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", data, 0x2e)
    sections = [list(struct.unpack_from("<10I", data, shoff + i * shentsize)) for i in range(shnum)]
    names = sections[shstrndx]
    for section in sections:
        start = names[4] + section[0]
        section.append(data[start:data.index(b"\0", start)].decode())
    return shoff, shentsize, sections


def symbols_of(data: bytes, sections):
    symtab = next(s for s in sections if s[1] == 2)
    strtab = sections[symtab[6]]
    result = []
    for i in range(symtab[5] // 16):
        offset = symtab[4] + i * 16
        name_off, value, size, info, other, shndx = struct.unpack_from("<IIIBBH", data, offset)
        start = strtab[4] + name_off
        name = data[start:data.index(b"\0", start)].decode()
        result.append((offset, name, value, size, info, shndx))
    return symtab, strtab, result


def rename_symbols(data: bytes, renames: dict[str, str]) -> bytes:
    """Append a new string table holding the renamed symbols; nothing else moves."""
    shoff, shentsize, sections = read_elf(data)
    symtab, strtab, symbols = symbols_of(data, sections)
    out = bytearray(data)
    table = bytearray(data[strtab[4]:strtab[4] + strtab[5]])
    for offset, name, *_ in symbols:
        if name in renames:
            struct.pack_into("<I", out, offset, len(table))
            table += renames[name].encode() + b"\0"
    while len(out) % 4:
        out.append(0)
    new_offset = len(out)
    out += table
    index = symtab[6]
    struct.pack_into("<II", out, shoff + index * shentsize + 16, new_offset, len(table))
    return bytes(out)


def compile_object(entry: dict, address: int) -> Path:
    source = ROOT / entry["source"]
    key = hashlib.sha256((source.read_text(encoding="utf-8") + entry["compiler"] + entry["mode"] +
                          json.dumps(entry.get("bindings", {}), sort_keys=True)).encode()).hexdigest()[:16]
    obj = CACHE / f"{entry['module']}_{entry['symbol']}_{key}.o"
    if not obj.exists():
        CACHE.mkdir(parents=True, exist_ok=True)
        temp = CACHE / f"{entry['module']}_{entry['symbol']}_{key}.tmp"
        compile_match.compile_entry(entry, address, temp.with_suffix(".bin"))
        temp.with_suffix(".bin").unlink(missing_ok=True)
        temp.with_suffix(".o").replace(obj)
    return obj


def prepare(entry: dict, info: dict, canonical: dict, relocs: dict, addresses: dict) -> tuple[bytes | None, str]:
    module = entry["module"]
    address, size = info["address"], info["size"]
    try:
        data = compile_object(entry, address).read_bytes()
    except Exception as exc:  # noqa: BLE001 - compile failures are reported, not fatal
        return None, f"compile: {str(exc).splitlines()[0][:80]}"
    _, _, sections = read_elf(data)
    extra = [s[10] for s in sections if s[10] not in ALLOWED_SECTIONS and "mwcats" not in s[10]
             and not (s[1] == 8 and s[5] == 0) and s[5] != 0]
    if extra:
        return None, f"sections {extra}"
    text_index = next(i for i, s in enumerate(sections) if s[10] == ".text")
    if sections[text_index][5] != size:
        return None, f"text size {sections[text_index][5]:#x} != {size:#x}"
    _, _, symbols = symbols_of(data, sections)
    renames = {}
    rela = next((s for s in sections if s[1] == 4 and s[7] == text_index), None)
    sites: dict[int, list[int]] = {}
    if rela:
        for i in range(rela[5] // 12):
            r_offset, r_info, _ = struct.unpack_from("<IIi", data, rela[4] + i * 12)
            sites.setdefault(r_info >> 8, []).append(r_offset)
    bindings = {k: int(v, 0) if isinstance(v, str) else v for k, v in entry.get("bindings", {}).items()}
    for index, (_, name, value, _, info_byte, shndx) in enumerate(symbols):
        if shndx == text_index and name == entry["source_symbol"]:
            if value & ~1:
                return None, "function not at offset 0"
            if entry["_link_name"] != name:
                renames[name] = entry["_link_name"]
            continue
        if shndx != 0 or not name:
            continue
        if name not in bindings:
            return None, f"unbound {name}"
        raw = bindings[name]
        candidates = [raw, raw & ~1] if raw & 1 else [raw]
        target_modules = {relocs.get(address + site) for site in sites.get(index, [])}
        target_modules.discard(None)
        resolved = {reloc_module(m) for m in target_modules}
        if None in resolved or len(resolved) > 1:
            # Overlays sharing an address: any one defining a symbol there yields the same bytes.
            options = [m for text in target_modules for m in reloc_modules(text)]
            options = [m for m in options if any((m, c) in canonical for c in candidates)]
            resolved = set(options[:1])
            if not resolved:
                return None, f"ambiguous target for {name}"
        if not resolved and not any(lo <= raw < hi for lo, hi in RANGES.values()):
            # Outside every module: an SDK constant or fixed memory address, defined absolutely.
            ABSOLUTES.setdefault(name, raw)
            continue
        if not resolved:
            order = (module, "arm9", "itcm", "dtcm")
            owners = [m for m in order if any((m, c) in canonical for c in candidates)]
            owners = owners or [m for m in order if RANGES[m][0] <= raw < RANGES[m][1]]
            resolved = set(owners[:1]) or set(sorted(m for (m, a) in canonical if a in candidates)[:1])
            if len(resolved) != 1:
                return None, f"no owner for {name}"
        owner = resolved.pop()
        target = raw & ~1 if raw & 1 and (owner, raw & ~1) in THUMB else raw
        new = canonical.get((owner, target))
        if new is None:
            if any(start <= target < end for start, end in SPANS[owner]["code"]):
                return None, f"no symbol at {target:#x} in {owner} for {name}"
            new = EXTRAS.setdefault((owner, target), name)
        if new != name:
            renames[name] = new
    if renames:
        data = rename_symbols(data, renames)
    if address % 4:
        shoff, shentsize, _ = read_elf(data)
        patched = bytearray(data)
        struct.pack_into("<I", patched, shoff + text_index * shentsize + 32, 2)
        data = bytes(patched)
    return data, "ok"


def defined_globals(data: bytes, section_name: str) -> list[tuple[str, int]]:
    _, _, sections = read_elf(data)
    index = next(i for i, s in enumerate(sections) if s[10] == section_name)
    return [(name, value) for _, name, value, _, info, shndx in symbols_of(data, sections)[2]
            if shndx == index and info >> 4 == 1 and name]


def lower_alignment(data: bytes, section_name: str, address: int) -> bytes:
    """MWCC marks data sections 4-aligned; a unit at a 2- or 1-aligned address needs less."""
    shoff, shentsize, sections = read_elf(data)
    index = next(i for i, s in enumerate(sections) if s[10] == section_name)
    align = sections[index][8]
    while align > 1 and address % align:
        align //= 2
    patched = bytearray(data)
    struct.pack_into("<I", patched, shoff + index * shentsize + 32, align)
    return bytes(patched)


def undefined_names(data: bytes) -> list[str]:
    _, _, sections = read_elf(data)
    return [name for _, name, _, _, _, shndx in symbols_of(data, sections)[2] if shndx == 0 and name]


MODULE_BYTES: dict[str, tuple[int, bytes]] = {}
THUMB: set = set()
SPANS: dict[str, dict[str, list]] = {}
RANGES: dict[str, tuple[int, int]] = {}
EXTRAS: dict = {}
ABSOLUTES: dict[str, int] = {}


def module_bytes(module: str) -> tuple[int, bytes]:
    if module not in MODULE_BYTES:
        extract = ROOT / "build" / "bk9e" / "extract"
        path = {"arm9": extract / "arm9" / "arm9.bin", "itcm": extract / "arm9" / "itcm.bin",
                "dtcm": extract / "arm9" / "dtcm.bin"}.get(module, extract / "arm9_overlays" / f"{module}.bin")
        header = (CONFIG / module_dir(module) / "delinks.txt").read_text(encoding="utf-8")
        base = min(int(x, 16) for x in re.findall(r"start:0x([0-9a-f]+)", header))
        MODULE_BYTES[module] = (base, path.read_bytes())
    return MODULE_BYTES[module]


def padded_end(module: str, end: int, rows: list[list]) -> int:
    """Absorb zero padding up to the next word boundary so no tiny gap object is needed."""
    if end % 4 == 0:
        return end
    base, data = module_bytes(module)
    target = (end + 3) & ~3
    starts = {row[2] for row in rows if row[2] is not None}
    if any(a in starts for a in range(end, target)) or any(data[a - base] for a in range(end, target)):
        return end
    return target


def main() -> int:
    matches = json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]
    entries = [m for m in matches if m.get("language") in ("c", "cpp") and m.get("source")]
    modules = sorted({e["module"] for e in entries} | {"arm9", "itcm", "dtcm"} |
                     {p.name for p in (CONFIG / "overlays").iterdir()})
    symbols = {m: load_symbols(m) for m in modules}
    by_name = {(m, row[0]): row for m in modules for row in symbols[m] if row[0]}
    infos = {}
    for entry in entries:
        row = by_name.get((entry["module"], entry["symbol"]))
        found = row and re.search(r"size=0x([0-9a-f]+)", row[3])
        if found:
            infos[id(entry)] = {"address": row[2], "size": int(found.group(1), 16), "row": row}
    # The matched C name becomes the canonical name at its address.
    owners: dict[str, str] = {}
    for entry in entries:
        name = entry["source_symbol"]
        owners.setdefault(name, entry["module"])
        entry["_link_name"] = name if owners[name] == entry["module"] else f"{name}_{entry['module']}"
        if id(entry) in infos:
            infos[id(entry)]["row"][0] = entry["_link_name"]
    data_entries = data_match.load()
    data_names = {}
    for entry in data_entries:
        start = int(entry["start"], 16)
        for name, offset in defined_globals(data_match.compile_source(entry), entry["section"]):
            data_names[(entry["module"], start + offset)] = name
    data_renamed = {}
    for m in modules:
        for row in symbols[m]:
            if row[0] and (m, row[2]) in data_names and row[1] in ("data", "bss"):
                data_renamed[(m, row[0])] = data_names[(m, row[2])]
                row[0] = data_names[(m, row[2])]
    canonical = {(m, row[2]): row[0] for m in modules for row in symbols[m] if row[0] and row[1] != "label"}
    for key, name in data_names.items():
        if key not in canonical:
            canonical[key] = name
            EXTRAS[key] = name
    relocs = {m: load_relocs(m) for m in modules}
    THUMB.update((m, row[2]) for m in modules for row in symbols[m] if row[0] and "function(thumb" in row[3])
    for m in modules:
        header = (CONFIG / module_dir(m) / "delinks.txt").read_text(encoding="utf-8")
        spans = [(kind, int(a, 16), int(b, 16)) for a, b, kind in
                 re.findall(r"start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:(\w+)", header)]
        SPANS[m] = {kind: [(a, b) for k, a, b in spans if k == kind] for kind in ("code", "bss")}
        RANGES[m] = (min(a for _, a, _ in spans), max(b for _, _, b in spans))

    def work(entry):
        info = infos.get(id(entry))
        if info is None:
            return entry, None, "no dsd symbol"
        data, status = prepare(entry, info, canonical, relocs[entry["module"]], None)
        return entry, data, status

    with ThreadPoolExecutor(max_workers=os.cpu_count() or 4) as pool:
        results = list(pool.map(work, entries))

    if LINK_CONFIG.exists():
        shutil.rmtree(LINK_CONFIG)
    shutil.copytree(CONFIG, LINK_CONFIG)
    linked: dict[str, list] = {}
    skipped = []
    used_names: dict[str, str] = {}
    for entry, data, status in results:
        if data is None:
            skipped.append((entry["module"], entry["symbol"], status))
            continue
        unit = Path(entry["source"])
        if unit.name in used_names and used_names[unit.name] != entry["module"]:
            unit = unit.with_name(f"{unit.stem}_{entry['module']}{unit.suffix}")
        used_names.setdefault(unit.name, entry["module"])
        out = DELINKED / unit.with_suffix(".o")
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_bytes(data)
        info = infos[id(entry)]
        linked.setdefault(entry["module"], []).append((info["address"], info["size"], unit.as_posix(), ".text"))
    index = data_match.symbol_index()
    data_bytes = 0
    for entry in data_entries:
        data = data_match.compile_source(entry)
        renames = {}
        for name in undefined_names(data):
            owner, target, _ = data_match.resolve(name, entry["module"], index)
            new = canonical.get((owner, target), name)
            if new != name:
                renames[name] = new
        if renames:
            data = rename_symbols(data, renames)
        data = lower_alignment(data, entry["section"], int(entry["start"], 16))
        unit = Path(entry["source"])
        out = DELINKED / unit.with_suffix(".o")
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_bytes(data)
        start, end = int(entry["start"], 16), int(entry["end"], 16)
        linked.setdefault(entry["module"], []).append((start, end - start, unit.as_posix(), entry["section"]))
        data_bytes += end - start
        if not any(row[2] == end for row in symbols[entry["module"]] if row[0]):
            EXTRAS.setdefault((entry["module"], end), f"data_{entry['module']}_{end:08x}")
    renamed = {(e["module"], e["symbol"]): e["_link_name"] for e in entries if id(e) in infos}
    renamed.update(data_renamed)
    for module in modules:
        folder = LINK_CONFIG / module_dir(module)
        lines = []
        for line in (CONFIG / module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
            found = SYMBOL_LINE.match(line)
            if found and (module, found.group(1)) in renamed:
                line = renamed[(module, found.group(1))] + line[len(found.group(1)):]
            lines.append(line)
        for (owner, address), name in sorted(EXTRAS.items()):
            if owner == module:
                kind = "bss" if any(a <= address < b for a, b in SPANS[module]["bss"]) else "data(any)"
                lines.append(f"{name} kind:{kind} addr:{address:#010x}")
        (folder / "symbols.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
        units = sorted(linked.get(module, []))
        if units:
            text = (CONFIG / module_dir(module) / "delinks.txt").read_text(encoding="utf-8").rstrip("\n") + "\n"
            for start, size, source, section in units:
                end = padded_end(module, start + size, symbols[module]) if section == ".text" else start + size
                text += f"\n{source}:\n    complete\n    {section} start:{start:#010x} end:{end:#010x}\n"
            (folder / "delinks.txt").write_text(text, encoding="utf-8")
    total = sum(size for units in linked.values() for _, size, _, section in units if section == ".text")
    (LINK_CONFIG / "absolutes.txt").write_text(
        "".join(f"{name} = {value:#010x};\n" for name, value in sorted(ABSOLUTES.items())), encoding="utf-8")
    report = ROOT / "build" / "bk9e" / "link_skipped.txt"
    report.write_text("".join(f"{m} {s} {why}\n" for m, s, why in sorted(skipped)), encoding="utf-8")
    print(f"C objects linked: {len(results) - len(skipped)} functions ({total:,} bytes), "
          f"{len(data_entries)} data units ({data_bytes:,} bytes); skipped {len(skipped)} -> {report}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
