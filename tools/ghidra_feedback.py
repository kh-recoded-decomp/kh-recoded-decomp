#!/usr/bin/env python3
"""Feed matched C back into Ghidra so its decompiler output improves.

Every verified match gives a real prototype (argument count, widths, return
type). Applied in Ghidra, callers of those functions decompile with correct
calls, which makes more of them compile byte-exact in ghidra_autoport.

  python tools/ghidra_feedback.py   # writes build/ghidra/prototypes.json, then run Ghidra
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import days_port as dp  # noqa: E402
import match_tool as mt  # noqa: E402

ROOT = mt.ROOT
SCALARS = {"void": "void", "u8": "uchar", "s8": "char", "u16": "ushort", "s16": "short", "u32": "uint",
           "s32": "int", "fx32": "int", "fx16": "short", "BOOL": "int", "int": "int", "char": "char",
           "short": "short", "long": "int", "unsigned": "uint", "unsigned int": "uint", "unsigned short": "ushort",
           "unsigned char": "uchar", "signed char": "char", "unsigned long": "uint", "signed int": "int",
           "signed short": "short", "signed long": "int", "bool": "int", "f32": "float", "float": "float",
           "u64": "ulonglong", "s64": "longlong", "long long": "longlong", "unsigned long long": "ulonglong"}


def ghidra_type(text: str) -> str | None:
    text = re.sub(r"\b(?:const|volatile|struct|union|enum|register|static|extern)\b", " ", text)
    text = " ".join(text.split())
    if "*" in text or "[" in text:
        return "void *"
    return SCALARS.get(text)


def prototype(source: Path, name: str) -> str | None:
    code = dp.strip_comments(source.read_text(encoding="utf-8"))
    m = re.search(rf"(?m)^([A-Za-z_][\w\s\*]*?)\b{re.escape(name)}\s*\(([^)]*)\)\s*\{{", code)
    if not m:
        return None
    ret = ghidra_type(m.group(1).replace("inline", "").strip())
    if ret is None:
        return None
    params = [p.strip() for p in m.group(2).split(",") if p.strip()]
    if params in ([], ["void"]):
        return f"{ret} {name}(void)"
    out = []
    for index, param in enumerate(params):
        if param == "...":
            out.append("...")
            continue
        pm = re.match(r"(.*?)([A-Za-z_]\w*)\s*(\[\s*\w*\s*\])?$", param)
        if not pm or not pm.group(1).strip():
            return None
        kind = ghidra_type(pm.group(1) + ("*" if pm.group(3) else ""))
        if kind is None:
            return None
        out.append(f"{kind} {pm.group(2)}")
    return f"{ret} {name}({', '.join(out)})"


def main() -> int:
    inv = mt.inventory()
    rows, skipped = [], 0
    for m in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]:
        if m["language"] != "c":
            continue
        proto = prototype(ROOT / m["source"], m["source_symbol"])
        # Placeholder four-register signatures carry no argument-count evidence.
        if proto and re.search(r"\(\w+ \*? ?(?:argument|arg)\d", proto):
            proto = None
        if proto is None:
            skipped += 1
            continue
        rows.append({"module": m["module"], "address": inv[m["module"]]["symbols"][m["symbol"]]["address"],
                     "name": m["source_symbol"], "prototype": proto})
    out = ROOT / "build" / "ghidra" / "prototypes.json"
    out.write_text(json.dumps(rows, indent=1), encoding="utf-8")
    print(f"{len(rows)} prototypes written; {skipped} sources with struct-by-value or unknown types skipped")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
