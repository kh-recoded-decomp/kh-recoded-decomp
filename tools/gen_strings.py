#!/usr/bin/env python3
"""Generate string sources for .data and .rodata objects that hold one NUL-terminated string.

Each object becomes `char name[size] = "..."`, where size covers the object's zero
padding. MWCC orders a file's initialised data by size, so each file covers a run of
strictly increasing object sizes. Units are verified by data_match.py and registered
with origin "generated strings".
"""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import data_match  # noqa: E402
import gen_data_tables  # noqa: E402

ESCAPES = {9: "\\t", 10: "\\n", 13: "\\r", 34: '\\"', 92: "\\\\"}


def as_string(blob: bytes) -> str | None:
    text = blob.rstrip(b"\0")
    if not text or len(text) == len(blob) or any(not (32 <= c < 127 or c in (9, 10, 13)) for c in text):
        return None
    return "".join(ESCAPES.get(c, chr(c)) for c in text)


def write_unit(module: str, kind: str, run) -> dict:
    const = "const " if kind == "rodata" else ""
    lines = [f'{const}char {name}[{size}] = "{text}";' for _, name, size, text in reversed(run)]
    start = run[0][0]
    prefix = "RodataStrings" if kind == "rodata" else "DataStrings"
    source = ROOT / "src" / module / "data" / f"{prefix}_{module}_{start:08x}.c"
    source.parent.mkdir(parents=True, exist_ok=True)
    source.write_text('#include "nitro/types.h"\n\n' + "\n".join(lines) + "\n", encoding="utf-8", newline="\n")
    end = run[-1][0] + run[-1][2]
    return {"module": module, "section": f".{kind}", "start": f"{start:#010x}", "end": f"{end:#010x}",
            "source": source.relative_to(ROOT).as_posix(), "compiler": "mwccarm-4.0-1036",
            "name": f"{module} strings", "origin": "generated strings",
            "behavior": "Text strings referenced by this module's code."}


def main() -> int:
    symbols = gen_data_tables.load_symbols()
    index = data_match.symbol_index()
    registered = data_match.load()
    added, failed = 0, 0
    for module in data_match.all_modules():
        base, data = data_match.module_binary(module)
        taken = [(int(e["start"], 16), int(e["end"], 16)) for e in registered if e["module"] == module]
        rows = sorted(a for a, (_, k, _) in symbols[module].items() if k in ("data", "bss"))
        for kind in ("data", "rodata"):
            for span_start, span_end in data_match.section_spans(module).get(kind, []):
                inside = [a for a in rows if span_start <= a < span_end]
                objects = []
                for address, following in zip(inside, inside[1:] + [span_end]):
                    name = symbols[module][address][0]
                    text = as_string(data[address - base:following - base])
                    free = not any(a < following and address < b for a, b in taken)
                    objects.append((address, name, following - address, text) if text and free and name.isidentifier() else None)
                run = []
                for item in objects + [None]:
                    if item and run and item[0] == run[-1][0] + run[-1][2] and item[2] > run[-1][2]:
                        run.append(item)
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
                    run = [item] if item else []
    data_match.save(registered)
    print(f"Registered {added:,} string bytes; {failed} units failed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
