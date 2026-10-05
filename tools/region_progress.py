#!/usr/bin/env python3
"""US / EU / shared progress for the multi-region merge.

US comes from matches.json (byte-verified per function), EU from eu/tools/audit_progress.py.
A function counts as shared when its matched C body in both regions is the same code:
identical token structure once address-specific symbol names are abstracted away.
Writes build/regions.json and the regions table in README.md and PROGRESS.md.
"""

from __future__ import annotations

import hashlib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EU_ROOT = ROOT / "eu"
START, END = "<!-- regions:start -->", "<!-- regions:end -->"
KEYWORDS = set("""if else for while do return switch case default break continue goto sizeof struct union enum
typedef static inline const volatile extern unsigned signed int char short long void float double""".split())


def strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    return re.sub(r"//[^\n]*", " ", text)


def function_body(text: str, name: str) -> str | None:
    text = strip_comments(text)
    found = re.search(rf"\b{re.escape(name)}\s*\([^;{{)]*\)\s*\{{", text)
    if not found:
        return None
    depth = 0
    for index in range(found.end() - 1, len(text)):
        depth += {"{": 1, "}": -1}.get(text[index], 0)
        if depth == 0:
            return text[found.end() - 1:index + 1]
    return None


def fingerprint(body: str) -> str:
    tokens = re.findall(r"[A-Za-z_]\w*|0x[0-9a-fA-F]+|\d+|\S", body)
    shape = ["ID" if re.match(r"[A-Za-z_]", t) and t not in KEYWORDS else t.lower() for t in tokens]
    return hashlib.md5(" ".join(shape).encode()).hexdigest()


def us_functions() -> dict[str, tuple[int, str]]:
    sys.path.insert(0, str(ROOT / "tools"))
    import objdiff_report
    sizes = {(unit["name"], f["name"]): f["size"]
             for unit in objdiff_report.build_report()["units"] for f in unit["functions"]}
    out = {}
    matches = json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]
    for entry in matches:
        path = ROOT / entry["source"]
        body = path.exists() and function_body(path.read_text(encoding="utf-8", errors="replace"),
                                                entry["source_symbol"])
        if body:
            out[f"{entry['module']}:{entry['symbol']}"] = (sizes.get((entry["module"], entry["symbol"]), 0),
                                                           fingerprint(body))
    return out


def eu_functions() -> tuple[dict, dict]:
    sys.path.insert(0, str(EU_ROOT / "tools"))
    import audit_progress
    functions, _ = audit_progress.classify_functions()
    summary = audit_progress.summarize(functions, [])
    out, deduped, deduped_bytes = {}, 0, 0
    for f in functions:
        if f["category"] != "c_decompiled_matched" or not f["source"]:
            continue
        path = EU_ROOT / f["source"]
        text = path.read_text(encoding="utf-8", errors="replace") if path.exists() else ""
        shared = re.search(r'#include "(src/[^"]+\.c)"', text)
        if shared and (ROOT / shared.group(1)).is_file():
            # Wrapper around a shared US source: read the body it actually compiles.
            us_name = next((us for us, eu in re.findall(r"#define (\S+) (\S+)", text) if eu == f["name"]),
                           f["name"])
            text = (ROOT / shared.group(1)).read_text(encoding="utf-8", errors="replace")
            body = function_body(text, us_name)
            deduped += bool(body)
            deduped_bytes += f["size"] if body else 0
        else:
            body = function_body(text, f["name"])
        if body:
            out[f"{f['unit']}:{f['name']}"] = (f["size"], fingerprint(body))
    summary["deduped_functions"] = deduped
    summary["deduped_bytes"] = deduped_bytes
    return out, summary


def pct(part: int, whole: int) -> str:
    return f"{100 * part / whole:.1f}%" if whole else "0.0%"


def main() -> int:
    sys.path.insert(0, str(ROOT / "tools"))
    import objdiff_report
    report = objdiff_report.build_report()
    us_measures = report["measures"]
    sizes = {(unit["name"], f["name"]): f["size"] for unit in report["units"] for f in unit["functions"]}
    asm_path = ROOT / "asm_matches.json"
    asm_entries = json.loads(asm_path.read_text(encoding="utf-8"))["matches"] if asm_path.exists() else []
    asm_bytes = sum(sizes.get((m["module"], m["symbol"]), 0) for m in asm_entries)
    # The report counts assembly as matched; the C figures below exclude it.
    us_measures = dict(us_measures, matched_code=us_measures["matched_code"] - asm_bytes,
                       matched_functions=us_measures["matched_functions"] - len(asm_entries))
    us = us_functions()
    eu, eu_summary = eu_functions()
    from dedupe_regions import pairs
    pending = pairs()
    shared_functions = eu_summary["deduped_functions"] + len(pending)
    shared_bytes = eu_summary["deduped_bytes"] + sum(p[0]["size"] for p in pending)
    result = {
        "us": {"matched_code": us_measures["matched_code"], "total_code": us_measures["total_code"],
               "matched_functions": us_measures["matched_functions"],
               "total_functions": us_measures["total_functions"]},
        "eu": {"matched_code": eu_summary["code_bytes"]["c_decompiled_matched"],
               "total_code": eu_summary["total_code_bytes"],
               "matched_functions": eu_summary["counts"]["c_decompiled_matched"],
               "total_functions": eu_summary["total_functions"]},
        "shared": {"functions": shared_functions, "bytes": shared_bytes,
                   "deduped_functions": eu_summary["deduped_functions"], "pending_pairs": len(pending),
                   "us_only_functions": us_measures["matched_functions"] - shared_functions,
                   "eu_only_functions": eu_summary["counts"]["c_decompiled_matched"] - shared_functions},
    }
    (ROOT / "build").mkdir(exist_ok=True)
    (ROOT / "build" / "regions.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    u, e, s = result["us"], result["eu"], result["shared"]
    table = "\n".join([
        START,
        "| Region | C code bytes | % | Functions |",
        "|---|---:|---:|---:|",
        f"| **US** `BK9E` | {u['matched_code']:,} / {u['total_code']:,} | **{pct(u['matched_code'], u['total_code'])}** "
        f"| {u['matched_functions']:,} / {u['total_functions']:,} |",
        f"| **EU** `BK9P` | {e['matched_code']:,} / {e['total_code']:,} | **{pct(e['matched_code'], e['total_code'])}** "
        f"| {e['matched_functions']:,} / {e['total_functions']:,} |",
        f"| US verified original assembly (not C) | {asm_bytes:,} | {pct(asm_bytes, u['total_code'])} "
        f"| {len(asm_entries):,} |",
        f"| **Shared** (same function, matched in both) | {s['bytes']:,} | {pct(s['bytes'], e['total_code'])} of EU "
        f"| {s['functions']:,} |",
        "",
        f"{s['deduped_functions']:,} shared functions are stored once in `src/` and built for both regions; "
        f"{s['pending_pairs']:,} still have separate EU copies. "
        f"{s['us_only_functions']:,} matched functions are US-only so far and {s['eu_only_functions']:,} are EU-only. "
        "EU numbers come from `eu/tools/audit_progress.py`; per-module EU detail is in [eu/PROGRESS.md](eu/PROGRESS.md).",
        END,
    ])
    for name in ("README.md", "PROGRESS.md"):
        path = ROOT / name
        text = path.read_text(encoding="utf-8")
        if START in text:
            text = re.sub(re.escape(START) + r".*?" + re.escape(END), lambda _: table, text, flags=re.S)
        else:
            heading = "## Progress\n\n" if "## Progress\n\n" in text else None
            if heading:
                text = text.replace(heading, heading + table + "\n\n", 1)
            else:
                first_break = text.find("\n\n")
                text = text[:first_break + 2] + table + "\n\n" + text[first_break + 2:]
        path.write_text(text, encoding="utf-8", newline="\n")
    print(f"US {pct(u['matched_code'], u['total_code'])}, EU {pct(e['matched_code'], e['total_code'])}, "
          f"shared {s['functions']:,} functions ({s['deduped_functions']:,} stored once)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
