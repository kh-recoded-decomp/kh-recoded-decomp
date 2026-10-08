#!/usr/bin/env python3
"""Score the best saved draft of every unmatched US function for decomp.dev's fuzzy match.

Each draft under src/ whose file name carries the function address is compiled with
both compilers and aligned against the target instructions. The score is the share of
target instructions reproduced in order, so a draft only reaches 100 when it matches.
Results go to fuzzy.json (tracked, read by objdiff_report.py); a function keeps its
best score across runs until it is matched.

    python tools/fuzzy_score.py [--jobs N] [--module ov001] [--max-drafts 6]
"""

from __future__ import annotations

import argparse
import difflib
import json
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import days_port as dp  # noqa: E402
import match_tool as mt  # noqa: E402

OUTPUT = ROOT / "fuzzy.json"
COMPILERS = ["mwccarm-4.0-1036", "mwccarm-3.0-139"]
ADDRESS = re.compile(r"([0-9a-f]{8})(?:_[^.]*)?\.c$")


def score(target: bytes, actual: bytes, address: int, mode: str) -> float:
    want = [text for _, text in mt.disassemble(target, address, mode)]
    got = [text for _, text in mt.disassemble(actual, address, mode)]
    matcher = difflib.SequenceMatcher(a=want, b=got, autojunk=False)
    same = sum(block.size for block in matcher.get_matching_blocks())
    return 100.0 * same / max(len(want), len(got), 1)


def drafts_by_address(max_drafts: int) -> dict[str, list[Path]]:
    found: dict[str, list[Path]] = {}
    for path in (ROOT / "src").rglob("*.c"):
        m = ADDRESS.search(path.name)
        if m:
            found.setdefault(m.group(1), []).append(path)
    for paths in found.values():
        paths.sort(key=lambda p: p.stat().st_mtime, reverse=True)
        del paths[max_drafts:]
    return found


def best_draft(task) -> tuple[str, float, str] | None:
    target, paths = task
    best = None
    for path in paths:
        text = path.read_text(encoding="utf-8", errors="replace")
        if not re.search(rf"\b{re.escape(path.stem)}\s*\([^;]*?\)\s*\{{", text):
            continue
        for compiler in COMPILERS:
            try:
                actual, _, _ = mt.compile_candidate(target["module"], target["symbol"], path, compiler,
                                                    target["mode"], path.stem)
            except (SystemExit, Exception):
                actual = None
            if not actual:
                continue
            value = min(score(target["bytes"], actual, target["address"], target["mode"]), 99.9)
            if best is None or value > best[1]:
                best = (path.relative_to(ROOT).as_posix(), value, compiler)
    return best


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("--module")
    parser.add_argument("--max-drafts", type=int, default=6)
    args = parser.parse_args()
    previous = json.loads(OUTPUT.read_text(encoding="utf-8")) if OUTPUT.exists() else {}
    open_funcs = [t for rows in dp.recoded_functions().values() for t in rows
                  if not t["matched"] and (args.module is None or t["module"] == args.module)]
    drafts = drafts_by_address(args.max_drafts)
    tasks = [(t, drafts[f"{t['address']:08x}"]) for t in open_funcs if f"{t['address']:08x}" in drafts]
    print(f"{len(open_funcs)} open functions, {len(tasks)} with drafts", flush=True)
    with ThreadPoolExecutor(args.jobs) as pool:
        results = list(pool.map(best_draft, tasks))
    still_open = {f"{t['module']}:{t['symbol']}" for rows in dp.recoded_functions().values()
                  for t in rows if not t["matched"]}
    scores = {key: value for key, value in previous.items() if key in still_open}
    for (target, _), best in zip(tasks, results):
        key = f"{target['module']}:{target['symbol']}"
        if best and best[1] > scores.get(key, {}).get("percent", 0):
            scores[key] = {"percent": round(best[1], 2), "draft": best[0], "compiler": best[2]}
    OUTPUT.write_text(json.dumps(dict(sorted(scores.items())), indent=1) + "\n", encoding="utf-8")
    sizes = {f"{t['module']}:{t['symbol']}": len(t["bytes"]) for t in open_funcs}
    fuzzy_bytes = sum(sizes.get(k, 0) * v["percent"] / 100 for k, v in scores.items())
    print(f"{len(scores)} scored functions, {fuzzy_bytes:,.0f} fuzzy bytes -> {OUTPUT.name}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
