#!/usr/bin/env python3
"""Verified original assembly: functions whose real source is assembly (NitroSDK, MSL, BIOS veneers).

These are byte-verified like C matches but recorded in asm_matches.json and never counted as C.
decomp.dev reports them as matched code; the README keeps them in a separate row.

    python tools/asm_match.py try MODULE SYMBOL SOURCE [--compiler C]
    python tools/asm_match.py register MODULE SYMBOL SOURCE --name NAME --evidence TEXT [--compiler C]
    python tools/asm_match.py port [--dry-run]     # port the EU build's verified asm stubs to US
    python tools/asm_match.py days DAYS_CHECKOUT   # port 358/2 Days asm stubs by exact code match
"""

from __future__ import annotations

import argparse
import difflib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EU = ROOT / "eu"
REGISTRY = ROOT / "asm_matches.json"
COMPILERS = ("mwccarm-4.0-1036", "mwccarm-3.0-139")
sys.path.insert(0, str(ROOT / "tools"))
import match_tool  # noqa: E402
from dedupe_regions import module_functions  # noqa: E402


def load() -> dict:
    return json.loads(REGISTRY.read_text(encoding="utf-8")) if REGISTRY.exists() else {"matches": []}


def verify(module: str, symbol: str, source: Path, compiler: str | None):
    name, info, target = match_tool.target_bytes(module, symbol)
    mode = match_tool.inventory()[module]["modes"][name]
    for candidate in ([compiler] if compiler else COMPILERS):
        actual, entry, error = match_tool.compile_candidate(module, name, source, candidate, mode,
                                                            source.stem, language="asm")
        if actual == target:
            return name, entry, ""
        if actual is None and "bind" in error:
            return None, entry, error
    return None, None, error if actual is None else "bytes differ"


def register(module: str, symbol: str, source: Path, name: str, evidence: str, compiler: str | None) -> bool:
    found, entry, error = verify(module, symbol, source, compiler)
    if not found:
        print(f"NO MATCH {module}:{symbol}: {error}")
        return False
    registry = load()
    registry["matches"] = [m for m in registry["matches"] if (m["module"], m["symbol"]) != (module, found)]
    registry["matches"].append({"module": module, "symbol": found, "name": name, "language": "asm",
                                "source": entry["source"], "source_symbol": entry["source_symbol"],
                                "compiler": entry["compiler"], "mode": entry["mode"],
                                "bindings": entry["bindings"], "evidence": evidence})
    registry["matches"].sort(key=lambda m: (m["module"], m["symbol"]))
    REGISTRY.write_text(json.dumps(registry, indent=2) + "\n", encoding="utf-8")
    print(f"REGISTERED {module}:{found} as assembly")
    return True


def us_name(eu_name: str, address: int, us_symbol: str) -> str:
    if re.fullmatch(r"func_(?:ov\d{3}_)?[0-9a-f]{8}", eu_name):
        return us_symbol
    return f"{eu_name.rstrip('_')}_{address:08x}"


def port(dry_run: bool) -> int:
    sys.path.insert(0, str(EU / "tools"))
    import audit_progress
    eu_asm = {}
    for f in audit_progress.classify_functions()[0]:
        if f["category"] == "asm_stub_matched" and f["source"] and f["source"].endswith(".c"):
            eu_asm[("arm9" if f["unit"] == "main" else f["unit"], f["name"])] = f
    c_matched = {(m["module"], m["symbol"]) for m in json.loads((ROOT / "matches.json").read_text())["matches"]}
    asm_matched = {(m["module"], m["symbol"]) for m in load()["matches"]}
    us_modules = module_functions(ROOT / "config" / "bk9e" / "arm9")
    eu_modules = module_functions(EU / "config" / "arm9")
    tried = ported = 0
    for module, us_rows in sorted(us_modules.items()):
        eu_rows = eu_modules.get(module, [])
        matcher = difflib.SequenceMatcher(None, [r[1] for r in us_rows], [r[1] for r in eu_rows], autojunk=False)
        eu_to_us = {}
        for block in matcher.get_matching_blocks():
            for k in range(block.size):
                eu_to_us[eu_rows[block.b + k][2]] = us_rows[block.a + k]
        for eu_name, (address, size, us_symbol) in eu_to_us.items():
            stub = eu_asm.get((module, eu_name))
            if not stub or (module, us_symbol) in c_matched or (module, us_symbol) in asm_matched:
                continue
            text = (EU / stub["source"]).read_text(encoding="utf-8", errors="replace").lstrip("﻿")
            if re.search(r'#include "(?!nitro/)', text):
                continue
            tried += 1
            # Rename the function and every paired EU function it references to US address names.
            for other, (other_address, _, _) in eu_to_us.items():
                if re.search(rf"\b{re.escape(other)}\b", text):
                    text = re.sub(rf"\b{re.escape(other)}\b", f"{other}_{other_address:08x}", text)
            stem = f"{eu_name}_{address:08x}"
            target = ROOT / "src" / module / "asm" / f"{stem}.c"
            target.parent.mkdir(parents=True, exist_ok=True)
            existed = target.exists()
            target.write_text(text, encoding="utf-8", newline="\n")
            evidence = f"Original assembly; ported from the EU build's verified stub {stub['source']}"
            if dry_run:
                found, _, error = verify(module, us_symbol, target, None)
                print(("MATCH " if found else "MISS  ") + f"{module}:{us_symbol} {stem} {error}")
                ok = bool(found)
                if not existed:
                    target.unlink()
            else:
                ok = register(module, us_symbol, target, stem.rsplit("_", 1)[0], evidence, None)
                if not ok and not existed:
                    target.unlink()
            ported += ok
    print(f"tried {tried}, {'would port' if dry_run else 'ported'} {ported}")
    return 0


def days(checkout: Path) -> int:
    sys.path.insert(0, str(ROOT / "build"))
    from unmatched import unmatched
    done = {(m["module"], m["symbol"]) for m in load()["matches"]}
    by_code: dict[tuple[str, bytes], list[tuple[str, str]]] = {}
    anchor = {}
    for module, symbol, size, mode in unmatched():
        if (module, symbol) in done:
            continue
        mode = "thumb" if "thumb" in mode else "arm"
        anchor.setdefault(mode, (module, symbol))
        by_code.setdefault((mode, match_tool.target_bytes(module, symbol)[2]), []).append((module, symbol))
    scratch = ROOT / "src" / ".port_scratch" / "days_asm"
    scratch.mkdir(parents=True, exist_ok=True)
    asm_re = re.compile(r"^\s*asm\b|\basm\s+(?:static\s+)?\w+\s*\**\s*\w+\s*\(", re.M)
    ported = 0
    for path in sorted(checkout.glob("libs/**/*.c")) + sorted(checkout.glob("src/**/*.c")):
        text = path.read_text(encoding="utf-8", errors="replace").lstrip("\ufeff")
        if not asm_re.search(text) or re.search(r'#include "(?!nitro/)', text):
            continue
        func = path.stem
        if not re.search(rf"\b{re.escape(func)}\s*\(", text):
            continue
        probe = scratch / path.name
        probe.write_text(text, encoding="utf-8", newline="\n")
        hits = []
        for mode, (module, symbol) in anchor.items():
            for compiler in COMPILERS:
                actual, _, _ = match_tool.compile_candidate(module, symbol, probe, compiler, mode, func,
                                                            language="asm")
                if actual:
                    hits += by_code.get((mode, actual), [])
        probe.unlink()
        for module, symbol in dict.fromkeys(hits):
            address = match_tool.target_bytes(module, symbol)[1]["address"]
            stem = us_name(func, address, symbol)
            renamed = re.sub(rf"\b{re.escape(func)}\b", stem, text)
            target = ROOT / "src" / module / "asm" / f"{stem}.c"
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(renamed, encoding="utf-8", newline="\n")
            evidence = f"Original assembly; same code as the 358/2 Days asm stub {path.relative_to(checkout).as_posix()}"
            if register(module, symbol, target, stem.rsplit("_", 1)[0], evidence, None):
                ported += 1
            else:
                target.unlink()
    print(f"ported {ported} from Days")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("try", "register"):
        cmd = sub.add_parser(name)
        cmd.add_argument("module")
        cmd.add_argument("symbol")
        cmd.add_argument("source", type=Path)
        cmd.add_argument("--compiler")
        if name == "register":
            cmd.add_argument("--name", required=True)
            cmd.add_argument("--evidence", required=True)
    port_cmd = sub.add_parser("port")
    port_cmd.add_argument("--dry-run", action="store_true")
    sub.add_parser("days").add_argument("checkout", type=Path)
    args = parser.parse_args()
    if args.command == "days":
        return days(args.checkout)
    if args.command == "port":
        return port(args.dry_run)
    if args.command == "try":
        found, _, error = verify(args.module, args.symbol, args.source, args.compiler)
        print(f"MATCH {args.module}:{found}" if found else f"NO MATCH: {error}")
        return 0 if found else 1
    return 0 if register(args.module, args.symbol, args.source, args.name, args.evidence, args.compiler) else 1


if __name__ == "__main__":
    raise SystemExit(main())
