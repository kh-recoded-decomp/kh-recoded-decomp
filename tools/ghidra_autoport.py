#!/usr/bin/env python3
"""Try Ghidra's decompiler output as matching C, with no manual edits.

Each exported view (build/ghidra/decomp) is made compilable: namespaces removed,
Ghidra types declared, callees and globals declared extern and bound by address.
It is compiled with both compilers and two integer spellings. Byte-exact
results are copied to build/ghidra_auto/ for a naming pass; they are never
registered as-is, because decompiler names like iVar1 fail the style gate.

  python tools/ghidra_autoport.py [--limit N] [--max-size BYTES]
"""

from __future__ import annotations

import argparse
import json
import re
import shutil
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match_tool as mt  # noqa: E402

ROOT = mt.ROOT
OUT = ROOT / "build" / "ghidra_auto"
DECOMP_DIR = ROOT / "build" / "ghidra" / "decomp"
SCRATCH = ROOT / "src" / ".port_scratch"
PRELUDE = """typedef unsigned char undefined;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef unsigned long long undefined8;
typedef int bool;
typedef void code();
#define false 0
#define true 1
"""
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "goto"}
RAM_TYPES = {"i": "int", "u": "UNDEF4", "pc": "code *", "p": "void *", "pu": "UNDEF4 *", "pi": "int *",
             "s": "short", "us": "ushort", "c": "char", "b": "byte", "uc": "uchar", "pp": "void **",
             "ps": "short *", "pus": "ushort *", "pb": "byte *", "pc_": "char *", "ppu": "UNDEF4 **"}
GLOBAL = re.compile(r"\b(_*(?:DAT|data)_(?:ov\d+_)?[0-9a-fA-F]{8})\b")
RAM = re.compile(r"\b([a-z]{1,3})Ram([0-9a-fA-F]{8})\b")
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
UNSUPPORTED = re.compile(r"\b(?:CONCAT\d+|SUB\d+|ZEXT\d+|SEXT\d+|CARRY\d|SCARRY\d|SBORROW\d|LZCOUNT|POPCOUNT|"
                         r"halt_baddata|software_interrupt|coprocessor_\w+|PTR_\w+|LAB_\w+|in_\w+|unaff_\w+|"
                         r"extraout_\w+|WARNING)\b")


def convert(text: str, symbol: str, int_type: str) -> str | None:
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"\b(?:arm9|itcm|dtcm|ov\d{3})::", "", text)
    # Local goto labels are ordinary C; external code addresses are not.
    labels = set(re.findall(r"(?m)^\s*(LAB_[0-9a-fA-F]+)\s*:", text))
    for label in labels:
        text = re.sub(rf"\b{label}\b", label.replace("LAB_", "branch_"), text)
    if UNSUPPORTED.search(text) or symbol not in text:
        return None
    text = text.replace("undefined4", "UNDEF4")
    declared = set()
    externs = []
    for m in sorted(set(RAM.findall(text))):
        prefix, address = m
        kind = RAM_TYPES.get(prefix)
        if kind is None:
            return None
        name = f"{prefix}Ram{address}"
        externs.append(f"extern {kind} {name};")
        declared.add(name)
    for name in sorted(set(GLOBAL.findall(text))):
        externs.append(f"extern UNDEF4 {name};")
        declared.add(name)
    body_calls = {m for m in CALL.findall(text)} - KEYWORDS - {symbol} - declared
    for name in sorted(body_calls):
        if name in ("UNDEF4", "code") or re.fullmatch(r"(?:u?int|u?short|u?char|byte|bool|undefined\d?|ulong|longlong)", name):
            continue
        externs.append(f"extern UNDEF4 {name}();")
    return (PRELUDE + f"typedef {int_type} UNDEF4;\n" + "\n".join(externs) + "\n\n" + text.strip() + "\n")


def attempt(target: dict) -> dict | None:
    module, symbol = target["module"], target["symbol"]
    view = DECOMP_DIR / module / f"{symbol}.c"
    if not view.exists():
        return None
    raw = view.read_text(encoding="utf-8")
    _, info, expected = mt.target_bytes(module, symbol)
    SCRATCH.mkdir(parents=True, exist_ok=True)
    best = None  # closest same-size build: a good starting point for manual work
    for int_type in ("unsigned int", "int"):
        text = convert(raw, symbol, int_type)
        if text is None:
            return None
        for compiler in ("mwccarm-4.0-1036", "mwccarm-3.0-139"):
            with tempfile.TemporaryDirectory(prefix="gh-", dir=SCRATCH) as temp:
                source = Path(temp) / f"{symbol}.c"
                source.write_text(text, encoding="utf-8")
                try:
                    actual, entry, error = mt.compile_candidate(module, symbol, source, compiler, None, None)
                except SystemExit:
                    return None
                if actual is None:
                    if "Cannot bind" in error or "rror" in error:
                        break  # the other compiler fails the same way
                    continue
                if actual == expected:
                    dest = OUT / module / f"{symbol}.c"
                    dest.parent.mkdir(parents=True, exist_ok=True)
                    dest.write_text(text, encoding="utf-8")
                    return {"status": "match", "module": module, "symbol": symbol, "size": info["size"],
                            "compiler": compiler, "bindings": entry["bindings"],
                            "source": dest.relative_to(ROOT).as_posix()}
                if len(actual) == len(expected):
                    wrong = sum(actual[i:i + 2] != expected[i:i + 2] for i in range(0, len(actual), 2))
                    if best is None or wrong < best[0]:
                        best = (wrong, compiler, text)
    if best is None:
        return None
    dest = OUT / "near" / module / f"{symbol}.c"
    dest.parent.mkdir(parents=True, exist_ok=True)
    if not dest.exists():  # agents may already be working from an earlier near miss
        dest.write_text(best[2], encoding="utf-8")
    return {"status": "near", "module": module, "symbol": symbol, "size": info["size"], "compiler": best[1],
            "differing_halfwords": best[0], "source": dest.relative_to(ROOT).as_posix()}


TYPE_NAMES = {"uint": "u32", "ushort": "u16", "uchar": "u8", "byte": "u8", "undefined1": "u8",
              "undefined2": "u16", "undefined": "u8", "undefined8": "u64", "ulonglong": "u64",
              "longlong": "s64", "bool": "BOOL", "ulong": "u32", "true": "TRUE", "false": "FALSE"}


def tidy(text: str, int_type: str, unsigned: str) -> str:
    """Nitro types, address-named globals, K&R layout; code is unchanged."""
    body = text.split(f"typedef {int_type} UNDEF4;\n", 1)[1]
    body = re.sub(r"\bUNDEF4\b", unsigned if int_type == "unsigned int" else "s32", body)
    for old, new in TYPE_NAMES.items():
        body = re.sub(rf"\b{old}\b", new, body)
    body = RAM.sub(lambda m: f"data_{m.group(2)}", body)
    body = re.sub(r"\b_*DAT_([0-9a-fA-F]{8})\b", r"data_\1", body)
    body = re.sub(r"\b_+(data_(?:ov\d+_)?[0-9a-fA-F]{8})\b", r"\1", body)
    body = re.sub(r"\)\s*\n\s*\n\{", ") {", body)
    body = re.sub(r"\n\s*return;\n\}\s*$", "\n}\n", body)
    body = re.sub(r"\n{3,}", "\n\n", body)
    lines = [line.rstrip() for line in body.strip().splitlines()]
    # Declarations may repeat after renaming (e.g. two views of one global).
    seen, out = set(), []
    for line in lines:
        if line.startswith("extern ") and line in seen:
            continue
        seen.add(line)
        out.append(line)
    header = '#include "nitro/types.h"\n'
    if "code" in body.split():
        header += "\ntypedef void code();\n"
    return header + "\n" + "\n".join(out) + "\n"


def clean(jobs: int) -> None:
    """Stage auto-matched functions whose only names are addresses."""
    index = json.loads((OUT / "index.json").read_text())
    matched = {(m["module"], m["symbol"]) for m in json.loads((ROOT / "matches.json").read_text())["matches"]}
    pending = mt.PENDING

    def one(record: dict) -> dict | None:
        module, symbol = record["module"], record["symbol"]
        if (module, symbol) in matched or (pending / f"{module}__{symbol}.json").exists():
            return None
        raw = (ROOT / record["source"]).read_text(encoding="utf-8")
        int_type = "unsigned int" if "typedef unsigned int UNDEF4;" in raw else "int"
        code = raw.split(f"typedef {int_type} UNDEF4;\n", 1)[1]
        if re.search(r"\b(?:param_\d+|[a-z]{1,5}Var\d+|local_\w+|[a-z]*Stack_\w+)\b", code):
            return None
        _, info, expected = mt.target_bytes(module, symbol)
        for unsigned in ("u32", "unsigned int"):
            text = tidy(raw, int_type, unsigned)
            dest = ROOT / "src" / module / "unclassified_helpers" / f"{symbol}.c"
            if dest.exists():
                return None
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_text(text, encoding="utf-8")
            actual, entry, _ = mt.compile_candidate(module, symbol, dest, record["compiler"], None, None)
            if actual == expected and not mt.style_problems(text):
                staged = {"module": module, "symbol": symbol, "name": symbol, "language": "c",
                          "source": entry["source"], "source_symbol": symbol, "compiler": record["compiler"],
                          "mode": entry["mode"], "bindings": entry["bindings"],
                          "behavior": "Small address-named helper; purpose not yet reviewed.",
                          "evidence": f"Ghidra decompiler output with Nitro types rebuilds all {info['size']} bytes.",
                          "uncertainty": "Callers not reviewed; name stays address-based.",
                          "domain": "unclassified_helpers", "origin": "Ghidra decompiler output, cleaned and verified",
                          "understanding": "unknown"}
                pending.mkdir(parents=True, exist_ok=True)
                (pending / f"{module}__{symbol}.json").write_text(json.dumps(staged, indent=2) + "\n", encoding="utf-8")
                return staged
            dest.unlink()
        return None

    mt.thumb_addresses()
    mt.known_names()
    with ThreadPoolExecutor(jobs) as pool:
        staged = [s for s in pool.map(one, index) if s]
    total = sum(mt.inventory()[s["module"]]["symbols"][s["symbol"]]["size"] for s in staged)
    print(f"Staged {len(staged)} address-named helpers ({total:,} bytes)")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("command", nargs="?", default="match", choices=("match", "clean"))
    parser.add_argument("--limit", type=int)
    parser.add_argument("--max-size", type=int, default=4096)
    parser.add_argument("--jobs", type=int, default=16)
    parser.add_argument("--decomp", help="directory of Ghidra views (default build/ghidra/decomp)")
    args = parser.parse_args()
    global DECOMP_DIR
    if args.decomp:
        DECOMP_DIR = ROOT / args.decomp
    if args.command == "clean":
        clean(args.jobs)
        return 0
    inv = mt.inventory()
    matched = {(m["module"], m["symbol"]) for m in json.loads((ROOT / "matches.json").read_text())["matches"]}
    done = {p.stem for p in OUT.glob("*/*.c") if p.parent.name != "near"} if OUT.exists() else set()
    targets = [{"module": module, "symbol": s} for module, data in inv.items() if module not in ("arm7", "dtcm")
               for s, i in data["symbols"].items()
               if (module, s) not in matched and s not in done and i["size"] <= args.max_size]
    targets.sort(key=lambda t: inv[t["module"]]["symbols"][t["symbol"]]["size"])
    if args.limit:
        targets = targets[:args.limit]
    mt.thumb_addresses()
    mt.known_names()
    with ThreadPoolExecutor(args.jobs) as pool:
        outcomes = [r for r in pool.map(attempt, targets) if r]
    results = [r for r in outcomes if r["status"] == "match"]
    near = [r for r in outcomes if r["status"] == "near"]
    index = OUT / "index.json"
    previous = json.loads(index.read_text()) if index.exists() else []
    index.write_text(json.dumps(previous + results, indent=1))
    (OUT / f"near{'_' + DECOMP_DIR.name if args.decomp else ''}.json").write_text(
        json.dumps(sorted(near, key=lambda r: r["differing_halfwords"]), indent=1))
    print(f"Tried {len(targets)}; Ghidra C matched {len(results)} ({sum(r['size'] for r in results):,} bytes); "
          f"{len(near)} same-size near misses")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
