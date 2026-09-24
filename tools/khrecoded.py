#!/usr/bin/env python3
"""Local, ROM-gated bootstrap and evidence-based progress for KH Re:coded."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import urllib.request
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROFILE = ROOT / "profiles" / "bk9e.json"
EXTRACT = ROOT / "build" / "bk9e" / "extract"
DSD_CONFIG = ROOT / "config" / "bk9e" / "arm9" / "config.yaml"
SYMBOL_RE = re.compile(r"^(\S+) kind:function\([^,]+,size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", re.I)
RANGE_RE = re.compile(r"start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:code", re.I)
OVERLAY_RE = re.compile(r"(?m)^  - id: (\d+)\n    base_address: (\d+)")


def profile() -> dict:
    return json.loads(PROFILE.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(4 * 1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def rom_path(arg: str | None) -> Path:
    value = arg or os.environ.get("KH_RECODED_ROM")
    if not value and (ROOT / "local.json").exists():
        value = json.loads((ROOT / "local.json").read_text(encoding="utf-8")).get("rom")
    if not value:
        raise RuntimeError("Set --rom, KH_RECODED_ROM, or local.json (see local.json.example).")
    path = Path(value).expanduser().resolve()
    if not path.is_file():
        raise RuntimeError(f"ROM not found: {path}")
    return path


def validate_rom(path: Path) -> None:
    p = profile()
    if path.stat().st_size != p["rom_size"]:
        raise RuntimeError("ROM size does not match BK9E revision 0.")
    with path.open("rb") as f:
        header = f.read(0x200)
    if (header[12:16].decode("ascii", errors="replace") != p["game_code"]
            or header[16:18].decode("ascii", errors="replace") != p["maker_code"]
            or header[30] != p["revision"]):
        raise RuntimeError("ROM game code, maker, or revision is not BK9E revision 0.")
    actual = sha256(path)
    if actual != p["rom_sha256"]:
        raise RuntimeError(f"ROM SHA-256 differs from the configured revision: {actual}")


def dsd(install: bool = False) -> Path:
    if sys.platform == "win32":
        binary = ROOT / ".tools" / "dsd-windows-x86_64.exe"
        if not binary.exists() and install:
            binary.parent.mkdir(parents=True, exist_ok=True)
            url = ("https://github.com/AetiasHax/ds-decomp/releases/download/"
                   "v0.12.1/dsd-windows-x86_64.exe")
            print(f"Downloading dsd 0.12.1 from {url}")
            urllib.request.urlretrieve(url, binary)
        if binary.exists():
            if sha256(binary) != profile()["dsd_windows_sha256"]:
                raise RuntimeError("dsd executable checksum mismatch; delete .tools/dsd-windows-x86_64.exe")
            return binary
    found = shutil.which("dsd")
    if found:
        version = subprocess.run([found, "--version"], capture_output=True, text=True, check=True).stdout
        if profile()["dsd_version"] not in version:
            raise RuntimeError(f"Expected dsd {profile()['dsd_version']}, found {version.strip()}")
        return Path(found)
    raise RuntimeError("dsd 0.12.1 is required. On Windows, run setup to download it.")


def run(*command: str | Path) -> None:
    args = [str(c) for c in command]
    print("+", " ".join(args))
    subprocess.run(args, cwd=ROOT, check=True)


def setup(rom: Path) -> None:
    validate_rom(rom)
    tool = dsd(install=True)
    if not (EXTRACT / "config.yaml").exists():
        EXTRACT.parent.mkdir(parents=True, exist_ok=True)
        run(tool, "rom", "extract", "--rom", rom, "--output-path", EXTRACT)
    if not DSD_CONFIG.exists():
        run(tool, "init", "--rom-config", EXTRACT / "config.yaml",
            "--output-path", DSD_CONFIG.parent,
            "--build-path", ROOT / "build" / "bk9e" / "delinked")
    local = ROOT / "local.json"
    if not local.exists():
        local.write_text(json.dumps({"rom": str(rom)}, indent=2) + "\n", encoding="utf-8")
    check_extract()
    print("BK9E baseline ready. Run: python tools/khrecoded.py check --profile full")


def check_extract() -> None:
    required = [EXTRACT / "config.yaml", EXTRACT / "arm9" / "arm9.bin",
                EXTRACT / "arm9" / "itcm.bin", EXTRACT / "arm9" / "dtcm.bin",
                EXTRACT / "arm7" / "arm7.bin", EXTRACT / "arm9_overlays" / "overlays.yaml"]
    missing = [str(p) for p in required if not p.is_file()]
    overlays = list((EXTRACT / "arm9_overlays").glob("ov[0-9][0-9][0-9].bin"))
    files = list((EXTRACT / "files").rglob("*")) if (EXTRACT / "files").exists() else []
    if missing or len(overlays) != 105 or sum(p.is_file() for p in files) != 805:
        raise RuntimeError(f"Incomplete extraction: missing={missing}, overlays={len(overlays)}, "
                           f"asset_files={sum(p.is_file() for p in files)}")
    fingerprints = json.loads((ROOT / "profiles/bk9e-reference-binaries.json").read_text(encoding="utf-8"))
    expected_paths = {"arm9/arm9.bin", "arm9/itcm.bin", "arm9/dtcm.bin", "arm7/arm7.bin"}
    expected_paths.update(f"arm9_overlays/ov{i:03}.bin" for i in range(105))
    if set(fingerprints) != expected_paths:
        raise RuntimeError("Reference fingerprint inventory must contain all 109 binaries")
    for relative, expected in fingerprints.items():
        binary = EXTRACT / relative
        if binary.stat().st_size != expected["size"] or sha256(binary) != expected["sha256"]:
            raise RuntimeError(f"Reference binary was modified or extracted incorrectly: {relative}")


def compare_files(a: Path, b: Path) -> tuple[int, list[int]]:
    if a.stat().st_size != b.stat().st_size:
        return abs(a.stat().st_size - b.stat().st_size), []
    count, first, offset = 0, [], 0
    with a.open("rb") as fa, b.open("rb") as fb:
        while True:
            ca, cb = fa.read(1024 * 1024), fb.read(1024 * 1024)
            if not ca:
                break
            if ca != cb:
                for i, (x, y) in enumerate(zip(ca, cb)):
                    if x != y:
                        count += 1
                        if len(first) < 16:
                            first.append(offset + i)
            offset += len(ca)
    return count, first


def build_baseline(rom: Path) -> Path:
    validate_rom(rom)
    check_extract()
    output = ROOT / "build" / "bk9e" / "rebuilt.nds"
    run(dsd(), "rom", "build", "--config", EXTRACT / "config.yaml", "--rom", output)
    # dsd 0.12.1 zeroes two unused header bytes, then recalculates the header CRC.
    # Restore precisely these four known bytes. Every other byte must already match.
    with rom.open("rb") as f:
        original = f.read(0x200)
    with output.open("r+b") as f:
        rebuilt = f.read(0x200)
        allowed = set(profile()["header_restore_offsets"])
        unexpected = [i for i, (x, y) in enumerate(zip(original, rebuilt)) if x != y and i not in allowed]
        if unexpected:
            raise RuntimeError(f"Unexpected header changes: {[hex(x) for x in unexpected[:16]]}")
        for offset in allowed:
            f.seek(offset)
            f.write(original[offset:offset + 1])
    mismatches, first = compare_files(rom, output)
    if mismatches:
        raise RuntimeError(f"Rebuilt ROM differs at {mismatches} bytes; first: {[hex(x) for x in first]}")
    print(f"Exact baseline ROM match: {sha256(output)}")
    return output


def scalar_yaml(path: Path, key: str) -> int:
    match = re.search(rf"(?m)^{re.escape(key)}: (\d+)$", path.read_text(encoding="utf-8"))
    if not match:
        raise RuntimeError(f"Missing {key} in {path}")
    return int(match.group(1))


def union_size(ranges: list[tuple[int, int]]) -> int:
    end, total = -1, 0
    for start, stop in sorted(ranges):
        if stop <= start:
            continue
        total += max(0, stop - max(start, end))
        end = max(end, stop)
    return total


def inventory() -> dict[str, dict]:
    check_extract()
    arm9 = DSD_CONFIG.parent
    overlay_bases = {int(i): int(base) for i, base in OVERLAY_RE.findall(
        (EXTRACT / "arm9_overlays" / "overlays.yaml").read_text(encoding="utf-8"))}
    if set(overlay_bases) != set(range(105)):
        raise RuntimeError("Overlay inventory is incomplete")
    specs = [
        ("arm9", arm9, EXTRACT / "arm9" / "arm9.bin",
         scalar_yaml(EXTRACT / "arm9" / "arm9.yaml", "base_address")),
        ("itcm", arm9 / "itcm", EXTRACT / "arm9" / "itcm.bin",
         scalar_yaml(EXTRACT / "arm9" / "itcm.yaml", "base_address")),
        ("dtcm", arm9 / "dtcm", EXTRACT / "arm9" / "dtcm.bin",
         scalar_yaml(EXTRACT / "arm9" / "dtcm.yaml", "base_address")),
    ]
    specs += [(f"ov{i:03}", arm9 / "overlays" / f"ov{i:03}",
               EXTRACT / "arm9_overlays" / f"ov{i:03}.bin", overlay_bases[i]) for i in range(105)]
    result = {}
    for name, config_dir, binary, base in specs:
        symbols = {}
        ranges = []
        for line in (config_dir / "symbols.txt").read_text(encoding="utf-8").splitlines():
            m = SYMBOL_RE.match(line)
            if m:
                symbol, size, addr = m.group(1), int(m.group(2), 16), int(m.group(3), 16)
                if size:
                    symbols[symbol] = {"address": addr, "size": size}
                    ranges.append((addr, addr + size))
        code_ranges = [(int(a, 16), int(b, 16)) for a, b in RANGE_RE.findall(
            (config_dir / "delinks.txt").read_text(encoding="utf-8"))]
        result[name] = {"binary": binary, "base": base, "binary_bytes": binary.stat().st_size,
                        "code_bytes": union_size(code_ranges), "identified_function_bytes": union_size(ranges),
                        "code_ranges": code_ranges, "symbols": symbols}
    arm7 = EXTRACT / "arm7" / "arm7.bin"
    result["arm7"] = {"binary": arm7, "base": scalar_yaml(EXTRACT / "arm7" / "arm7.yaml", "base_address"),
                      "binary_bytes": arm7.stat().st_size, "code_bytes": None,
                      "identified_function_bytes": 0, "code_ranges": [], "symbols": {}}
    return result


def verify_matches(inv: dict[str, dict]) -> dict:
    manifest = json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))
    if manifest.get("version") != 1 or not isinstance(manifest.get("matches"), list):
        raise RuntimeError("Invalid matches.json schema")
    verified, seen = [], set()
    claimed_ranges: dict[str, list[tuple[int, int]]] = defaultdict(list)
    for entry in manifest["matches"]:
        module, symbol, language = entry["module"], entry["symbol"], entry["language"]
        key = (module, symbol)
        if key in seen or module not in inv or symbol not in inv[module]["symbols"]:
            raise RuntimeError(f"Duplicate or unknown match: {key}")
        seen.add(key)
        if language not in ("c", "cpp"):
            raise RuntimeError(f"Unknown language for {key}: {language}")
        source = (ROOT / entry["source"]).resolve()
        if not source.is_relative_to(ROOT / "src") or not source.is_file():
            raise RuntimeError(f"Missing or external source for {key}: {source}")
        if language == "c" and source.suffix.lower() != ".c":
            raise RuntimeError(f"C match must point to a .c file: {key}")
        for field in ("name", "behavior", "evidence", "uncertainty", "domain", "origin"):
            if not isinstance(entry.get(field), str) or not entry[field].strip():
                raise RuntimeError(f"Missing {field} for {key}")
        if entry.get("understanding") not in ("gameplay", "subsystem", "unknown"):
            raise RuntimeError(f"Invalid understanding level for {key}")
        if "build" in entry:
            raise RuntimeError("Arbitrary build recipes cannot count as verified C")
        function = inv[module]["symbols"][symbol]
        with tempfile.TemporaryDirectory(prefix="candidate-", dir=ROOT / "build") as temp:
            from compile_match import compile_entry
            candidate = Path(temp) / "candidate.bin"
            build_proof = compile_entry(entry, function["address"], candidate)
            offset = function["address"] - inv[module]["base"]
            if offset < 0 or offset + function["size"] > inv[module]["binary_bytes"]:
                raise RuntimeError(f"Function span outside {module}: {symbol}")
            start, stop = function["address"], function["address"] + function["size"]
            if any(start < old_stop and old_start < stop for old_start, old_stop in claimed_ranges[module]):
                raise RuntimeError(f"Overlapping verified spans in {module}: {symbol}")
            claimed_ranges[module].append((start, stop))
            with inv[module]["binary"].open("rb") as f:
                f.seek(offset)
                expected = f.read(function["size"])
            actual = candidate.read_bytes()
            if actual != expected:
                first = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b), None)
                raise RuntimeError(f"Byte mismatch for {module}:{symbol}: compiled={len(actual)}, "
                                   f"expected={len(expected)}, first_difference={first}")
            verified.append({"module": module, "symbol": symbol, "language": language,
                             "bytes": function["size"], "source": entry["source"],
                             **{field: entry[field] for field in (
                                 "name", "behavior", "evidence", "uncertainty", "domain", "origin", "understanding")},
                             **build_proof})
    return {"verified": verified}


def progress(write: bool = True) -> dict:
    from organization import build_hierarchy, markdown

    inv = inventory()
    proof = verify_matches(inv)
    hierarchy = build_hierarchy(inv, proof["verified"], json.loads(
        (ROOT / "config/bk9e/organization.json").read_text(encoding="utf-8")))
    by_module = defaultdict(list)
    for match in proof["verified"]:
        by_module[match["module"]].append(match)
    groups = defaultdict(lambda: {"matched_c_bytes": 0, "matched_asm_bytes": 0,
                                  "matched_sdk_bytes": 0, "identified_function_bytes": 0,
                                  "binary_bytes": 0, "code_bytes": 0,
                                  "identified_functions": 0, "matched_c_functions": 0})
    module_rows = []
    for name, data in inv.items():
        matches = by_module[name]
        cbytes = sum(m["bytes"] for m in matches if m["language"] in ("c", "cpp"))
        abytes = sum(m["bytes"] for m in matches if m["language"] == "asm")
        sbytes = sum(m["bytes"] for m in matches if m["language"] == "sdk")
        row = {"module": name, "binary_bytes": data["binary_bytes"], "code_bytes": data["code_bytes"],
               "identified_function_bytes": data["identified_function_bytes"],
               "identified_functions": len(data["symbols"]), "matched_c_bytes": cbytes,
               "matched_c_functions": sum(m["language"] in ("c", "cpp") for m in matches),
               "matched_asm_bytes": abytes, "matched_sdk_bytes": sbytes}
        module_rows.append(row)
        group = "ARM7 (unanalysed)" if name == "arm7" else (
            "ARM9 overlays" if name.startswith("ov") else "ARM9 core/autoload")
        for field in groups[group]:
            groups[group][field] += row[field] or 0
    understanding = {level: {"functions": sum(m["understanding"] == level for m in proof["verified"]),
                              "bytes": sum(m["bytes"] for m in proof["verified"] if m["understanding"] == level)}
                     for level in ("gameplay", "subsystem", "unknown")}
    result = {"profile": "bk9e", "rom_sha256": profile()["rom_sha256"], "understanding": understanding,
              "verified_at_utc": datetime.now(timezone.utc).isoformat(),
              "groups": dict(groups), "modules": module_rows, "matches": proof["verified"],
              "organization": hierarchy,
              "assets": {"extracted_files": 805, "decompiled_files": 0}}
    if write:
        out = ROOT / "build" / "progress.json"
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
        total_c = sum(g["matched_c_bytes"] for g in groups.values())
        total_code = sum(g["code_bytes"] for g in groups.values())
        lines = ["# Progress — BK9E revision 0", "", "Generated by `python tools/khrecoded.py progress`.", "",
                 f"Last successful verification: `{result['verified_at_utc']}`. This is a snapshot; rerun after source changes.", "",
                 f"**Verified C/C++: {total_c:,} / {total_code:,} analysed ARM9 code bytes "
                 f"({100 * total_c / total_code if total_code else 0:.3f}%).**", "",
                 "C/C++ progress counts only functions rebuilt from source during this command and byte-matched "
                 "against the extracted ROM, including resolved relocations and literal pools. Recovered middleware "
                 "C is included and labelled by origin; original SDK binaries are never counted. No extracted binary, "
                 "delinked object, renamed symbol, or repacked ROM counts as decompiled source.", "",
                 "| Target | C bytes / analysed code bytes | Identified function bytes | "
                 "C functions / identified functions | Assembly bytes | SDK bytes | Binary container bytes |",
                 "|---|---:|---:|---:|---:|---:|---:|"]
        for name, data in result["groups"].items():
            code_label = f"{data['code_bytes']:,}" if data['code_bytes'] else "unknown"
            lines.append(f"| {name} | {data['matched_c_bytes']:,} / {code_label} | "
                         f"{data['identified_function_bytes']:,} | "
                         f"{data['matched_c_functions']:,} / {data['identified_functions']:,} | "
                         f"{data['matched_asm_bytes']:,} | {data['matched_sdk_bytes']:,} | "
                         f"{data['binary_bytes']:,} |")
        lines += ["", "ARM7 is included in the project but has no function inventory yet. The binary container "
                  "column includes code and data; it is not a source progress denominator. This percentage is "
                  "ARM9 code coverage, not completion of the entire game or a fully linked source build.", "",
                  "## Understanding", "", "Names and explanations do not add matching bytes. A subsystem name "
                  "describes a shared operation such as model animation; a gameplay label requires evidence of "
                  "the particular in-game feature or actor.", "",
                  "| Evidence level | Matched functions | Matched bytes |", "|---|---:|---:|"]
        for level, data in understanding.items():
            lines.append(f"| {level} | {data['functions']} | {data['bytes']:,} |")
        lines += [""] + markdown(hierarchy)
        owners = {(module["module"], f["symbol"]): f"{system['id']} / {module['module']} / {section['id']}"
                  for system in hierarchy["systems"] for module in system["modules"]
                  for section in module["subsections"] for f in section["functions"]}
        lines += ["", "## What the matched code does", "", "| Function | Owning subsection | Player-facing role | Scope | Bytes |",
                  "|---|---|---|---|---:|"]
        for match in proof["verified"]:
            lines.append(f"| [{match['name']}]({match['source']}) ({match['module']}:{match['symbol']}) | "
                         f"{owners[(match['module'], match['symbol'])]} | "
                         f"{match['behavior'].replace('|', '/')} | {match['understanding']} | {match['bytes']} |")
        lines += ["",
                  "## Per-module status", "", "| Module | C bytes | Analysed code bytes | "
                  "Identified function bytes | Identified functions | Container bytes |",
                  "|---|---:|---:|---:|---:|---:|"]
        for row in module_rows:
            code_label = f"{row['code_bytes']:,}" if row['code_bytes'] is not None else "unknown"
            lines.append(f"| {row['module']} | {row['matched_c_bytes']:,} | "
                         f"{code_label} | {row['identified_function_bytes']:,} | "
                         f"{row['identified_functions']:,} | "
                         f"{row['binary_bytes']:,} |")
        lines += ["", "Machine-readable detail: `build/progress.json` (local, ignored by Git).", ""]
        (ROOT / "PROGRESS.md").write_text("\n".join(lines), encoding="utf-8")
    total_c = sum(g["matched_c_bytes"] for g in groups.values())
    total_code = sum(g["code_bytes"] for g in groups.values())
    print(f"Verified C/C++: {total_c:,} / {total_code:,} analysed ARM9 code bytes "
          f"({100 * total_c / total_code if total_code else 0:.3f}%)")
    print(f"Profiles: {len(module_rows)} modules; 105 overlays, ARM9 core/autoloads, ARM7")
    return result


def unit_tests() -> None:
    run(sys.executable, "-m", "unittest", "discover", "-s", "tests", "-v")


def check(level: str, rom: Path | None) -> None:
    unit_tests()
    if level == "ci":
        print("ROM-free CI checks passed")
        return
    assert rom is not None
    validate_rom(rom)
    check_extract()
    print("ROM identity and extraction inventory passed")
    if level in ("full", "strict"):
        build_baseline(rom)
        progress()
    if level == "strict":
        built = ROOT / "build" / "bk9e" / "delinked" / "build"
        if not built.exists() or not list(built.glob("*.bin")):
            raise RuntimeError("DSD linked-module check unavailable: whole source modules are not linked yet")
        else:
            run(dsd(), "check", "modules", "--config-path", DSD_CONFIG, "--fail")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("setup", "build", "progress", "check"):
        command = sub.add_parser(name)
        command.add_argument("--rom", help="Path to the user's BK9E revision 0 ROM")
        if name == "check":
            command.add_argument("--profile", choices=("ci", "quick", "full", "strict"), default="full")
        if name == "progress":
            command.add_argument("--system", help="Show a system ID from the organization catalog")
            command.add_argument("--module", help="Show one original overlay/module ID, e.g. ov001")
            command.add_argument("--subsection", help="Show one subsection ID, e.g. actor_animation")
            command.add_argument("--functions", action="store_true", help="List matched and unmatched functions")
    args = parser.parse_args()
    try:
        rom = None if args.command == "check" and args.profile == "ci" else rom_path(args.rom)
        if args.command == "setup":
            setup(rom)
        elif args.command == "build":
            build_baseline(rom)
        elif args.command == "progress":
            validate_rom(rom)
            result = progress()
            if args.system or args.module or args.subsection or args.functions:
                from organization import print_tree
                print_tree(result["organization"], args.system, args.module, args.subsection, args.functions)
        else:
            check(args.profile, rom)
        return 0
    except (RuntimeError, subprocess.CalledProcessError, OSError, KeyError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
