#!/usr/bin/env python3
"""Generate .bss layout sources: one global per dsd symbol, sized to the next symbol.

MWCC emits uninitialised globals in reverse definition order, so the generated
file declares them from the highest address down. Each unit is verified by
data_match.py and registered with origin "generated layout", which progress reports
separately from hand-typed data.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import data_match  # noqa: E402

SYMBOL_LINE = data_match.SYMBOL_LINE


def symbol_name(module: str, address: int) -> str:
    return f"data_{address:08x}" if module in ("arm9", "itcm", "dtcm") else f"data_{module}_{address:08x}"


def declaration(name: str, address: int, size: int) -> str:
    if address % 4 == 0 and size % 4 == 0:
        kind, count = "u32", size // 4
    elif address % 2 == 0 and size % 2 == 0:
        kind, count = "u16", size // 2
    else:
        kind, count = "u8", size
    return f"{kind} {name};" if count == 1 else f"{kind} {name}[{count}];"


REFERENCES: dict[str, set[int]] = {}


def referenced_addresses(module: str, spans: list[tuple[int, int]]) -> set[int]:
    """Addresses that matched C binds to; each one starts a variable of its own."""
    if not REFERENCES:
        import json
        for entry in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]:
            for value in entry.get("bindings", {}).values():
                address = int(value, 0) if isinstance(value, str) else value
                for owner in (entry["module"], "arm9", "itcm", "dtcm"):
                    REFERENCES.setdefault(owner, set()).add(address)
    return {a for a in REFERENCES.get(module, set()) if any(start <= a < end for start, end in spans)}


def write_unit(module: str, run: list[tuple[int, str, int]]) -> dict:
    lines = ['#include "nitro/types.h"', ""]
    for address, name, size in reversed(run):
        lines.append(declaration(name, address, size))
    start, end = run[0][0], run[-1][0] + run[-1][2]
    source = ROOT / "src" / module / "data" / f"Bss_{module}_{start:08x}.c"
    source.parent.mkdir(parents=True, exist_ok=True)
    source.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")
    return {"module": module, "section": ".bss", "start": f"{start:#010x}", "end": f"{end:#010x}",
            "source": source.relative_to(ROOT).as_posix(), "compiler": "mwccarm-4.0-1036",
            "name": f"{module} .bss layout", "origin": "generated layout",
            "behavior": "Uninitialised globals, one per known symbol, sized by layout."}


def generate(module: str) -> list[dict]:
    """MWCC orders a file's .bss by size (ties by name hash), so each file covers strictly increasing sizes."""
    spans = data_match.section_spans(module).get("bss", [])
    rows = {}
    for line in (data_match.module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
        found = SYMBOL_LINE.match(line)
        if found and found.group(2) in ("bss", "data"):
            rows.setdefault(int(found.group(5), 16), found.group(1))
    for address in referenced_addresses(module, spans):
        rows.setdefault(address, symbol_name(module, address))
    taken = [(int(e["start"], 16), int(e["end"], 16)) for e in data_match.load() if e["module"] == module]
    entries = []
    for start, end in spans:
        if end <= start:
            continue
        inside = sorted((a, n) for a, n in rows.items() if start <= a < end)
        if not inside or inside[0][0] != start:
            inside.insert(0, (start, symbol_name(module, start)))
        bounds = [a for a, _ in inside] + [end]
        variables = [(a, n, b - a) for (a, n), b in zip(inside, bounds[1:])]
        run: list[tuple[int, str, int]] = []
        for variable in variables + [None]:
            if variable and run and variable[2] > run[-1][2]:
                run.append(variable)
                continue
            if run and not any(a < run[-1][0] + run[-1][2] and run[0][0] < b for a, b in taken):
                # A file's .bss size is padded to its widest alignment; an odd tail gets its own file.
                end_address = run[-1][0] + run[-1][2]
                if len(run) > 1 and end_address % 4:
                    entries.append(write_unit(module, run[:-1]))
                    entries.append(write_unit(module, run[-1:]))
                else:
                    entries.append(write_unit(module, run))
            run = [variable] if variable else []
    return entries


def drop_unaligned_gaps(entries: list[dict]) -> list[dict]:
    """dsd gap objects are word-aligned, so a gap may not start mid-word after a generated unit."""
    while True:
        removed = False
        for module in {e["module"] for e in entries}:
            units = sorted((int(e["start"], 16), int(e["end"], 16), e) for e in entries
                           if e["module"] == module and e["section"] == ".bss")
            for span_start, span_end in data_match.section_spans(module).get("bss", []):
                inside = [u for u in units if span_start <= u[0] < span_end]
                for (start, end, entry), following in zip(inside, inside[1:] + [(span_end, None, None)]):
                    if end != following[0] and end % 4 and entry.get("origin") == "generated layout":
                        entries.remove(entry)
                        (ROOT / entry["source"]).unlink(missing_ok=True)
                        removed = True
                        break
        if not removed:
            return entries


def main() -> int:
    index = data_match.symbol_index()
    registered = data_match.load()
    added, failed = 0, []
    for module in data_match.all_modules():
        for entry in generate(module):
            try:
                data_match.verify(entry, index)
            except Exception as exc:  # noqa: BLE001 - failures are reported, file removed
                failed.append(f"{module}: {str(exc).splitlines()[0]}")
                (ROOT / entry["source"]).unlink()
                continue
            registered.append(entry)
            added += int(entry["end"], 16) - int(entry["start"], 16)
    registered = drop_unaligned_gaps(registered)
    data_match.save(registered)
    for line in failed:
        print("FAIL", line)
    print(f"Registered {added:,} .bss bytes; {len(failed)} modules failed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
