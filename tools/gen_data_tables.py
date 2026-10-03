#!/usr/bin/env python3
"""Generate pointer-table sources for .data and .rodata objects.

An object (the bytes from one dsd symbol to the next) qualifies when every word is
either a relocation to the start of a known function or variable, or NULL. It
becomes a typed array of pointers that names its targets, so the table carries no
copied bytes. MWCC orders a file's initialised data by size, so each file covers a
run of strictly increasing object sizes. Units are verified by data_match.py and
registered with origin "generated table".
"""

from __future__ import annotations

import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import data_match  # noqa: E402

SYMBOL_LINE = data_match.SYMBOL_LINE
RELOC_LINE = re.compile(r"^from:0x([0-9a-f]+) kind:load to:0x([0-9a-f]+) module:(\S+)", re.I)


def reloc_owner(text: str) -> str | None:
    if text == "main":
        return "arm9"
    if text in ("itcm", "dtcm"):
        return text
    found = re.fullmatch(r"overlay\((\d+)\)", text)
    return f"ov{int(found.group(1)):03d}" if found else None


def load_symbols() -> dict[str, dict[int, tuple[str, str, bool]]]:
    """Per module: address -> (name, kind, thumb), with matched C names preferred."""
    table: dict[str, dict[int, tuple[str, str, bool]]] = {}
    by_name: dict[tuple[str, str], int] = {}
    for module in data_match.all_modules():
        rows = table.setdefault(module, {})
        for line in (data_match.module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
            found = SYMBOL_LINE.match(line)
            if found:
                address = int(found.group(5), 16)
                thumb = found.group(2) == "function" and (found.group(4) or "").startswith("thumb")
                rows.setdefault(address, (found.group(1), found.group(2), thumb))
                by_name[(module, found.group(1))] = address
    for entry in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]:
        address = by_name.get((entry["module"], entry["symbol"]))
        if address is not None and entry.get("source_symbol"):
            _, kind, thumb = table[entry["module"]][address]
            table[entry["module"]][address] = (entry["source_symbol"], kind, thumb)
    return table


def objects_in(module: str, kind: str, symbols, relocs, binary, taken):
    base, data = binary
    rows = sorted(a for a, (_, k, _) in symbols[module].items() if k in ("data", "bss"))
    for start, end in data_match.section_spans(module).get(kind, []):
        inside = [a for a in rows if start <= a < end]
        for address, following in zip(inside, inside[1:] + [end]):
            if any(a < following and address < b for a, b in taken):
                yield address, None
                continue
            words = []
            limit = following
            if following == end:
                while limit > address and not any(data[limit - 4 - base:limit - base]):
                    limit -= 4
            if address % 4 or (limit - address) % 4 or limit <= address:
                yield address, None
                continue
            ok, pointers = True, 0
            for at in range(address, limit, 4):
                word = struct.unpack_from("<I", data, at - base)[0]
                reloc = relocs.get(at)
                if reloc is None:
                    if word:
                        ok = False
                        break
                    words.append(None)
                    continue
                owner = reloc_owner(reloc[1])
                target = reloc[0]
                found = symbols.get(owner, {}).get(target) if owner else None
                if found is None and owner and target & 1:
                    found = symbols[owner].get(target & ~1)
                    found = found if found and found[2] else None
                if found is None or found[1] == "label":
                    ok = False
                    break
                words.append(found)
                pointers += 1
            yield address, (words, limit) if ok and pointers else None


def write_unit(module: str, kind: str, run) -> dict:
    const = " const" if kind == "rodata" else ""
    externs, lines = {}, []
    for address, name, words in reversed(run):
        items = []
        for word in words:
            if word is None:
                items.append("NULL")
                continue
            target, target_kind, _ = word
            if target_kind == "function":
                externs[target] = f"extern void {target}(void);"
                items.append(target)
            else:
                externs[target] = f"extern u8 {target}[];"
                items.append(f"(void (*)(void)){target}")
        body = ",\n".join(f"    {item}" for item in items)
        lines.append(f"void (*{const[1:] + ' ' if const else ''}{name}[{len(items)}])(void) = {{\n{body},\n}};"
                     if not const else f"void (*const {name}[{len(items)}])(void) = {{\n{body},\n}};")
    start = run[0][0]
    source = ROOT / "src" / module / "data" / f"{'Rodata' if kind == 'rodata' else 'Data'}_{module}_{start:08x}.c"
    source.parent.mkdir(parents=True, exist_ok=True)
    text = '#include "nitro/types.h"\n\n' + "\n".join(sorted(externs.values())) + "\n\n" + "\n\n".join(lines) + "\n"
    source.write_text(text, encoding="utf-8", newline="\n")
    end = run[-1][0] + 4 * len(run[-1][2])
    return {"module": module, "section": f".{kind}", "start": f"{start:#010x}", "end": f"{end:#010x}",
            "source": source.relative_to(ROOT).as_posix(), "compiler": "mwccarm-4.0-1036",
            "name": f"{module} pointer tables", "origin": "generated table",
            "behavior": "Tables of function and data pointers, each entry named by its target."}


def main() -> int:
    symbols = load_symbols()
    index = data_match.symbol_index()
    registered = data_match.load()
    added, failed = 0, 0
    for module in data_match.all_modules():
        relocs = {}
        for line in (data_match.module_dir(module) / "relocs.txt").read_text(encoding="utf-8").splitlines():
            found = RELOC_LINE.match(line)
            if found:
                relocs[int(found.group(1), 16)] = (int(found.group(2), 16), found.group(3))
        binary = data_match.module_binary(module)
        taken = [(int(e["start"], 16), int(e["end"], 16)) for e in registered if e["module"] == module]
        for kind in ("data", "rodata"):
            run = []
            items = list(objects_in(module, kind, symbols, relocs, binary, taken)) + [(None, None)]
            for address, result in items:
                size = 4 * len(result[0]) if result else 0
                contiguous = run and address == run[-1][0] + 4 * len(run[-1][2])
                if result and run and contiguous and size > 4 * len(run[-1][2]) and result[1] == address + size:
                    run.append((address, symbols[module][address][0], result[0]))
                    continue
                if run:
                    entry = write_unit(module, kind, run)
                    try:
                        data_match.verify(entry, index)
                        registered.append(entry)
                        added += int(entry["end"], 16) - int(entry["start"], 16)
                    except Exception as exc:  # noqa: BLE001 - failing units are dropped
                        failed += 1
                        print("FAIL", module, entry["start"], str(exc).splitlines()[0][:100])
                        (ROOT / entry["source"]).unlink()
                run = [(address, symbols[module][address][0], result[0])] if result else []
    data_match.save(registered)
    print(f"Registered {added:,} table bytes; {failed} units failed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
