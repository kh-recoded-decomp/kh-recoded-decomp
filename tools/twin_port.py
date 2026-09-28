#!/usr/bin/env python3
"""Reuse verified BK9E C for byte-identical copies of the same function.

Overlays often carry their own copy of a helper. A copy differs only in its
relocated words, so each matched source is recompiled, compared with every
unmatched function of the same size and mode with those words masked, and
re-bound to the copy's callees and globals. A copy is registered only after
its own rebuilt bytes match exactly.

  python tools/twin_port.py [--jobs N]
"""

from __future__ import annotations

import argparse
import json
import re
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import compile_match as cm  # noqa: E402
import days_port as dp  # noqa: E402

ROOT = dp.ROOT
SUFFIX = re.compile(r"^(.*?)(?:_(?:ov\d+_)?)?([0-9a-fA-F]{8})$")


def compiled_donor(entry: dict, address: int) -> dict | None:
    with tempfile.TemporaryDirectory(prefix="twin-", dir=ROOT / "build") as temp:
        out = Path(temp) / "donor.bin"
        try:
            cm.compile_entry(entry, address, out)
        except RuntimeError:
            return None
        functions = dp.read_functions(out.with_suffix(".o").read_bytes())
    return next((f for f in functions if f["name"] == entry["source_symbol"]), None)


def rebind_name(name: str, old: int, new: int) -> str:
    """Keep a callee's name but move its address suffix to the copy's address."""
    if old == new:
        return name
    m = SUFFIX.match(name)
    if m and int(m.group(2), 16) == old & ~1:
        return name[:m.start(2)] + f"{new & ~1:08x}"
    return f"{name}_{new & ~1:08x}"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--jobs", type=int, default=12)
    args = parser.parse_args()
    manifest_path = ROOT / "matches.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    by_size = dp.recoded_functions()
    inv = dp.kh.inventory()
    donors = [m for m in manifest["matches"] if m["language"] == "c"]

    def find(entry: dict):
        info = inv[entry["module"]]["symbols"][entry["symbol"]]
        fn = compiled_donor(entry, info["address"])
        if fn is None:
            return entry, []
        hits = []
        for target in by_size.get(info["size"], ()):
            if target["matched"] or target["mode"] != entry["mode"]:
                continue
            bindings, why = dp.try_candidate(fn, target)
            if bindings is not None:
                hits.append((target, bindings))
        return entry, hits

    with ThreadPoolExecutor(args.jobs) as pool:
        found = list(pool.map(find, donors))

    claimed = {(m["module"], m["symbol"]) for m in manifest["matches"]}
    blobs = {name: (data["base"], data["binary"].read_bytes()) for name, data in inv.items() if name != "arm7"}
    jobs = []
    for donor, hits in found:
        old_bindings = {k: int(v, 16) if isinstance(v, str) else v for k, v in donor.get("bindings", {}).items()}
        for target, bindings in hits:
            key = (target["module"], target["symbol"])
            if key in claimed:
                continue
            claimed.add(key)
            address = target["address"]
            base_name = SUFFIX.match(donor["source_symbol"])
            stem = base_name.group(1) if base_name and base_name.group(1) and not base_name.group(1).startswith("func") else None
            if set(bindings.values()) != set(old_bindings.values()):
                stem = None  # same pattern, different callees: the donor's name is not evidence
            source_symbol = f"{stem}_{address:08x}" if stem else target["symbol"]
            renames = {donor["source_symbol"]: source_symbol}
            new_bindings = {}
            for name, value in bindings.items():
                new = rebind_name(name, old_bindings.get(name, value), value)
                renames[name] = new
                new_bindings[new] = hex(value)
            jobs.append((donor, target, source_symbol, renames, new_bindings))

    def build(job):
        donor, target, source_symbol, renames, new_bindings = job
        text = (ROOT / donor["source"]).read_text(encoding="utf-8")
        for old, new in renames.items():
            if old != new:
                if re.search(rf"\b{re.escape(new)}\b", text):
                    return None
                text = re.sub(rf"\b{re.escape(old)}\b", new, text)
        area = Path(donor["source"]).parent.name
        entry = {k: v for k, v in donor.items() if k not in ("module", "symbol", "source", "source_symbol", "bindings")}
        entry.update({"module": target["module"], "symbol": target["symbol"],
                      "source": f"src/{target['module']}/{area}/{source_symbol}{Path(donor['source']).suffix}",
                      "source_symbol": source_symbol, "bindings": new_bindings,
                      "name": source_symbol.rsplit("_", 1)[0] if source_symbol != target["symbol"] else source_symbol,
                      "evidence": (f"Same code as verified {donor['module']}:{donor['symbol']} with its own "
                                   f"calls and globals; rebuilt C matches all {len(target['bytes'])} bytes.")})
        if source_symbol == target["symbol"] and donor["source_symbol"] != donor["symbol"]:
            entry.update({"behavior": f"Same instruction pattern as {donor['name']} but with its own call "
                                      "targets; purpose not reviewed.", "understanding": "unknown",
                          "uncertainty": "Shares only a generic instruction pattern with the donor."})
        if Path(entry["source"]).suffix != ".c":
            return None
        base, blob = blobs[target["module"]]
        expected = blob[target["address"] - base:target["address"] - base + len(target["bytes"])]
        if dp.verify_source(entry, text, target["address"], expected) is not None:
            return None
        return entry, text

    with ThreadPoolExecutor(args.jobs) as pool:
        built = [b for b in pool.map(build, jobs) if b]
    added = 0
    for entry, text in built:
        path = ROOT / entry["source"]
        if path.exists():
            continue
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")
        manifest["matches"].append(entry)
        added += 1
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    total = sum(len(t["bytes"]) for _, t, *_ in jobs)
    print(f"Twin candidates: {len(jobs)} ({total:,} bytes); registered {added}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
