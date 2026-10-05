#!/usr/bin/env python3
"""Write an objdiff progress report (report.proto v2, JSON) for decomp.dev.

Needs only tracked files: the dsd symbol and delink tables in config/bk9e/arm9,
matches.json and data_matches.json. Every entry in those manifests has passed the
byte-for-byte check of `khrecoded.py progress`, so a function counts as 100% matched
when it is registered and 0% otherwise. Each ARM9 module (main, ITCM, DTCM and every
overlay) becomes one report unit. A matched function counts as fully linked when
linked.txt lists it: `khrecoded.py link` writes that file only after the ROM built
from the C objects is byte-identical to the original.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config" / "bk9e" / "arm9"
REPORT_VERSION = 2
SYMBOL_RE = re.compile(r"^(\S+) kind:function\([^,]+,size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", re.I)
SPAN_RE = re.compile(r"start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:(\w+)", re.I)
DATA_KINDS = ("rodata", "data", "bss")
CATEGORIES = {"core": "ARM9 core/autoload", "overlays": "ARM9 overlays"}


def module_dirs() -> list[tuple[str, Path]]:
    overlays = sorted(p for p in (CONFIG / "overlays").iterdir() if p.is_dir())
    return [("arm9", CONFIG), ("itcm", CONFIG / "itcm"), ("dtcm", CONFIG / "dtcm")] + \
        [(p.name, p) for p in overlays]


def header_spans(config_dir: Path) -> dict[str, list[tuple[int, int]]]:
    # Only the module header (before the first per-file block) lists the section spans.
    header = (config_dir / "delinks.txt").read_text(encoding="utf-8").split("\n\n", 1)[0]
    spans: dict[str, list[tuple[int, int]]] = {}
    for start, end, kind in SPAN_RE.findall(header):
        spans.setdefault(kind, []).append((int(start, 16), int(end, 16)))
    return spans


def union_size(ranges: list[tuple[int, int]]) -> int:
    total, end = 0, None
    for start, stop in sorted(ranges):
        if end is None or start >= end:
            total += stop - start
            end = stop
        elif stop > end:
            total += stop - end
            end = stop
    return total


def percent(part: int, whole: int) -> float:
    return 100.0 * part / whole if whole else 0.0


def measures(code: int, matched_code: int, data: int, matched_data: int,
             functions: int, matched_functions: int, units: int,
             complete_code: int = 0, complete_units: int = 0) -> dict:
    return {"fuzzy_match_percent": percent(matched_code, code),
            "total_code": code, "matched_code": matched_code,
            "matched_code_percent": percent(matched_code, code),
            "total_data": data, "matched_data": matched_data,
            "matched_data_percent": percent(matched_data, data),
            "total_functions": functions, "matched_functions": matched_functions,
            "matched_functions_percent": percent(matched_functions, functions),
            "complete_code": complete_code, "complete_code_percent": percent(complete_code, code),
            "complete_data": 0, "complete_data_percent": 0.0,
            "total_units": units, "complete_units": complete_units}


def sum_measures(items: list[dict]) -> dict:
    keys = ("total_code", "matched_code", "total_data", "matched_data", "total_functions", "matched_functions",
            "complete_code", "total_units", "complete_units")
    total = {key: sum(item[key] for item in items) for key in keys}
    return measures(total["total_code"], total["matched_code"], total["total_data"], total["matched_data"],
                    total["total_functions"], total["matched_functions"], total["total_units"],
                    total["complete_code"], total["complete_units"])


def load_linked() -> set[tuple[str, str]]:
    path = ROOT / "linked.txt"
    if not path.exists():
        return set()
    return {tuple(line.split()[:2]) for line in path.read_text(encoding="utf-8").splitlines() if line.strip()}


def build_report() -> dict:
    matches = {(m["module"], m["symbol"]): m
               for m in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]}
    # Verified original assembly counts as matched code on decomp.dev, never as C (README keeps it apart).
    asm_path = ROOT / "asm_matches.json"
    if asm_path.exists():
        for m in json.loads(asm_path.read_text(encoding="utf-8"))["matches"]:
            matches.setdefault((m["module"], m["symbol"]), m)
    data_matches = json.loads((ROOT / "data_matches.json").read_text(encoding="utf-8"))["data"]
    linked = load_linked()
    units = []
    for module, config_dir in module_dirs():
        spans = header_spans(config_dir)
        code_ranges = spans.get("code", [])
        base = min(start for start, _ in code_ranges) if code_ranges else 0
        functions = []
        for line in (config_dir / "symbols.txt").read_text(encoding="utf-8").splitlines():
            found = SYMBOL_RE.match(line)
            if not found or not int(found.group(2), 16):
                continue
            symbol, size, address = found.group(1), int(found.group(2), 16), int(found.group(3), 16)
            match = matches.get((module, symbol))
            # Keep the dsd symbol so a function's history stays linked once it gets a real name.
            metadata = {"virtual_address": address}
            if match:
                metadata["demangled_name"] = Path(match["source"]).stem
            functions.append({"name": symbol, "size": size,
                              "fuzzy_match_percent": 100.0 if match else 0.0,
                              "address": address - base, "metadata": metadata})
        functions.sort(key=lambda f: f["metadata"]["virtual_address"])
        code = union_size(code_ranges)
        matched_code = sum(f["size"] for f in functions if f["fuzzy_match_percent"])
        linked_code = sum(f["size"] for f in functions
                          if f["fuzzy_match_percent"] and (module, f["name"]) in linked)
        sections = [{"name": ".text", "size": code, "fuzzy_match_percent": percent(matched_code, code),
                     "address": 0, "metadata": {"virtual_address": base}}]
        data_total = data_matched = 0
        for kind in DATA_KINDS:
            kind_spans = spans.get(kind, [])
            if not kind_spans:
                continue
            total = union_size(kind_spans)
            done = sum(int(e["end"], 16) - int(e["start"], 16) for e in data_matches
                       if e["module"] == module and e["section"] == f".{kind}")
            data_total += total
            data_matched += done
            start = min(s for s, _ in kind_spans)
            sections.append({"name": f".{kind}", "size": total, "fuzzy_match_percent": percent(done, total),
                             "address": start - base, "metadata": {"virtual_address": start}})
        category = "overlays" if module.startswith("ov") else "core"
        metadata = {"complete": bool(code) and linked_code == code, "module_name": module,
                    "progress_categories": [category], "auto_generated": True}
        if module.startswith("ov"):
            metadata["module_id"] = int(module[2:])
        units.append({"name": module,
                      "measures": measures(code, matched_code, data_total, data_matched, len(functions),
                                           sum(1 for f in functions if f["fuzzy_match_percent"]), 1,
                                           linked_code, int(bool(code) and linked_code == code)),
                      "sections": sections, "functions": functions, "metadata": metadata})
    categories = [{"id": cid, "name": name,
                   "measures": sum_measures([u["measures"] for u in units
                                             if cid in u["metadata"]["progress_categories"]])}
                  for cid, name in CATEGORIES.items()]
    return {"measures": sum_measures([u["measures"] for u in units]), "units": units,
            "version": REPORT_VERSION, "categories": categories}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("-o", "--output", type=Path, default=ROOT / "build" / "report.json")
    args = parser.parse_args()
    report = build_report()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, separators=(",", ":")) + "\n", encoding="utf-8")
    m = report["measures"]
    print(f"{args.output}: code {m['matched_code']:,} / {m['total_code']:,} ({m['matched_code_percent']:.3f}%), "
          f"linked {m['complete_code']:,} ({m['complete_code_percent']:.3f}%), "
          f"data {m['matched_data']:,} / {m['total_data']:,}, functions "
          f"{m['matched_functions']:,} / {m['total_functions']:,}, {m['total_units']} units")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
