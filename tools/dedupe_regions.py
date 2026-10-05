#!/usr/bin/env python3
"""Replace EU copies of shared functions with wrappers around the US source.

For every function matched in both regions with the same C structure, the EU file
under eu/ becomes a few `#define US_NAME EU_NAME` lines plus an `#include` of the
US source, so the real C lives once in src/. A pair is only rewritten after the
wrapper compiles (with the EU compiler, mode and flags) to an object identical to
the EU build's existing object: same section bytes, relocations and symbols.

    python tools/dedupe_regions.py [--limit N] [--dry-run]

Needs a completed EU build (`bash tools/gate.sh` in eu/) for the reference objects.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tempfile
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

ROOT = Path(__file__).resolve().parents[1]
EU = ROOT / "eu"
sys.path.insert(0, str(ROOT / "tools"))
from region_progress import fingerprint, function_body  # noqa: E402

US_COMPILER_DIRS = {"mwccarm-4.0-1036": "dsi/1.3p1", "mwccarm-3.0-139": "2.0/sp2p4"}
ALTERNATE_COMPILERS = ["dsi/1.1", "dsi/1.3p1", "2.0/sp2p4", "dsi/1.2", "dsi/1.1p1", "2.0/sp2p3"]
SYMBOL_LIKE = re.compile(r"^(?:func_|data_)\w*$|_[0-9a-f]{8}$")
TOKEN = re.compile(r"[A-Za-z_]\w*|0x[0-9a-fA-F]+|\d+|\S")
WRAPPER_MARK = "#include \"src/"


def tokens(body: str) -> list[str]:
    return TOKEN.findall(body)


def symbol_map(us_body: str, eu_body: str, us_name: str, eu_name: str) -> dict[str, str] | None:
    us_tokens, eu_tokens = tokens(us_body), tokens(eu_body)
    if len(us_tokens) != len(eu_tokens):
        return None
    mapping = {us_name: eu_name} if us_name != eu_name else {}
    for us_token, eu_token in zip(us_tokens, eu_tokens):
        if us_token == eu_token or not SYMBOL_LIKE.search(us_token):
            continue
        if mapping.setdefault(us_token, eu_token) != eu_token:
            return None
    return mapping


def object_signature(path: Path):
    with path.open("rb") as handle:
        elf = ELFFile(handle)
        symtab = elf.get_section_by_name(".symtab")
        sections, relocations = [], []
        for section in elf.iter_sections():
            if section["sh_flags"] & 0x2 and section["sh_type"] != "SHT_NOBITS":
                sections.append((section.name, section.data()))
            elif section["sh_flags"] & 0x2:
                sections.append((section.name, section["sh_size"]))
            if isinstance(section, RelocationSection):
                target = elf.get_section(section["sh_info"]).name
                for rel in section.iter_relocations():
                    sym = symtab.get_symbol(rel["r_info_sym"])
                    name = sym.name or elf.get_section(sym["st_shndx"]).name
                    addend = rel.entry["r_addend"] if "r_addend" in rel.entry else 0
                    relocations.append((target, rel["r_offset"], rel["r_info_type"], name, addend))
        globals_ = sorted(sym.name for sym in symtab.iter_symbols()
                          if sym["st_info"]["bind"] == "STB_GLOBAL" and sym["st_shndx"] != "SHN_UNDEF")
    return sections, sorted(relocations), globals_


def wrapper_text(mapping: dict[str, str], us_source: Path) -> str:
    include = us_source.resolve().relative_to(ROOT).as_posix()
    lines = [f"#define {us} {eu}" for us, eu in sorted(mapping.items())]
    return "\n".join(lines + [f'#include "{include}"', ""])


def pairs():
    sys.path.insert(0, str(EU / "tools"))
    import audit_progress
    eu_functions, _ = audit_progress.classify_functions()
    eu_index = defaultdict(list)
    for f in eu_functions:
        if f["category"] != "c_decompiled_matched" or not f["source"]:
            continue
        path = EU / f["source"]
        text = path.read_text(encoding="utf-8", errors="replace")
        if re.search(r'#include "src/[^"]+\.c"', text):
            continue
        body = function_body(text, f["name"])
        if body:
            eu_index[fingerprint(body)].append((f, path, body))
    us_index = defaultdict(list)
    for entry in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]:
        path = ROOT / entry["source"]
        if not path.exists():
            continue
        body = function_body(path.read_text(encoding="utf-8", errors="replace"), entry["source_symbol"])
        if body:
            us_index[fingerprint(body)].append((entry, path, body))
    out = []
    for mark, eu_list in eu_index.items():
        us_list = us_index.get(mark, [])
        for f, eu_path, eu_body in eu_list:
            module = "arm9" if f["unit"] == "main" else f["unit"]
            same_module = [u for u in us_list if u[0]["module"] == module]
            base = [u for u in same_module if re.sub(r"_[0-9a-f]{8}$", "", u[0]["source_symbol"]) == f["name"]]
            chosen = base or (same_module if len(same_module) == 1 and len(eu_list) == 1 else [])
            if len(chosen) == 1:
                entry, us_path, us_body = chosen[0]
                out.append((f, eu_path, eu_body, entry, us_path, us_body))
    return out


FUNCTION_LINE = re.compile(r"^(\S+) kind:function\([^,]+,size=0x([0-9a-f]+)\) addr:0x([0-9a-f]+)", re.I)


def module_functions(config: Path) -> dict[str, list[tuple[int, int, str]]]:
    out = {}
    for path in config.rglob("symbols.txt"):
        module = "arm9" if path.parent == config else path.parent.name
        rows = []
        for line in path.read_text(encoding="utf-8").splitlines():
            found = FUNCTION_LINE.match(line)
            if found and int(found.group(2), 16):
                rows.append((int(found.group(3), 16), int(found.group(2), 16), found.group(1)))
        out[module] = sorted(rows)
    return out


def positional_pairs():
    """Pair functions by their place in each module: same order, same sizes."""
    import difflib
    sys.path.insert(0, str(EU / "tools"))
    import audit_progress
    eu_functions, _ = audit_progress.classify_functions()
    eu_matched = {}
    for f in eu_functions:
        if f["category"] == "c_decompiled_matched" and f["source"]:
            eu_matched[("arm9" if f["unit"] == "main" else f["unit"], f["name"])] = f
    us_matched = {(e["module"], e["symbol"]): e
                  for e in json.loads((ROOT / "matches.json").read_text(encoding="utf-8"))["matches"]}
    us_modules = module_functions(ROOT / "config" / "bk9e" / "arm9")
    eu_modules = module_functions(EU / "config" / "arm9")
    out = []
    for module, us_rows in us_modules.items():
        eu_rows = eu_modules.get(module, [])
        matcher = difflib.SequenceMatcher(None, [r[1] for r in us_rows], [r[1] for r in eu_rows], autojunk=False)
        for block in matcher.get_matching_blocks():
            for k in range(block.size):
                us_name = us_rows[block.a + k][2]
                eu_name = eu_rows[block.b + k][2]
                entry, f = us_matched.get((module, us_name)), eu_matched.get((module, eu_name))
                if not entry or not f:
                    continue
                eu_path, us_path = EU / f["source"], ROOT / entry["source"]
                if not us_path.exists() or not eu_path.exists():
                    continue
                eu_text = eu_path.read_text(encoding="utf-8", errors="replace")
                if re.search(r'#include "src/[^"]+\.c"', eu_text):
                    continue
                us_body = function_body(us_path.read_text(encoding="utf-8", errors="replace"), entry["source_symbol"])
                eu_body = function_body(eu_text, f["name"]) or ""
                if us_body:
                    out.append((f, eu_path, eu_body, entry, us_path, us_body))
    return out


def try_pair(pair, scratch: Path):
    f, eu_path, eu_body, entry, us_path, us_body = pair
    mapping = symbol_map(us_body, eu_body, entry["source_symbol"], f["name"])
    if mapping is None:
        # Different source shape: start from the function name and let relocations supply the rest.
        mapping = {entry["source_symbol"]: f["name"]} if entry["source_symbol"] != f["name"] else {}
    reference = EU / "build" / Path(f["source"]).with_suffix(".o")
    if not reference.exists():
        return pair, None, "no reference object"
    text = wrapper_text(mapping, us_path)
    work = scratch / f["source"]
    work.parent.mkdir(parents=True, exist_ok=True)
    wrapper = work.with_name(eu_path.name)
    wrapper.write_text(text, encoding="utf-8", newline="\n")
    out = wrapper.with_suffix(".o")
    expected = object_signature(reference)
    # The EU unit's own compiler first, then the one the US source matched with, then the others.
    us_cc = US_COMPILER_DIRS.get(entry.get("compiler"))
    status = "object differs"
    for cc in [None] + [c for c in dict.fromkeys([us_cc, *ALTERNATE_COMPILERS]) if c]:
        out.unlink(missing_ok=True)
        args = [sys.executable, str(EU / "tools" / "_run_mwcc.py"), str(out), str(wrapper), f"--unit={f['source']}"]
        result = subprocess.run(args + ([f"--cc={cc}"] if cc else []), capture_output=True, text=True, cwd=EU)
        if result.returncode or not out.exists():
            if cc is None:
                status = "compile"
            continue
        actual = object_signature(out)
        if actual == expected:
            return pair, (text, cc), "ok" if cc is None else "ok with other compiler"
        extra = relocation_renames(actual, expected)
        if extra:
            # Same bytes and relocation sites: the remaining names pair up by position.
            mapping = {**mapping, **extra}
            text = wrapper_text(mapping, us_path)
            wrapper.write_text(text, encoding="utf-8", newline="\n")
            out.unlink(missing_ok=True)
            result = subprocess.run(args + ([f"--cc={cc}"] if cc else []), capture_output=True, text=True, cwd=EU)
            if not result.returncode and out.exists() and object_signature(out) == expected:
                return pair, (text, cc), "ok via relocations"
    return pair, None, status


def relocation_renames(actual, expected) -> dict[str, str] | None:
    if actual[0] != expected[0] or len(actual[1]) != len(expected[1]):
        return None
    renames = {}
    for ours, theirs in zip(actual[1], expected[1]):
        if ours[:3] != theirs[:3] or ours[4] != theirs[4]:
            return None
        if ours[3] == theirs[3]:
            continue
        if not re.match(r"^[A-Za-z_]\w*$", ours[3]) or renames.setdefault(ours[3], theirs[3]) != theirs[3]:
            return None
    return renames or None


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--jobs", type=int, default=8)
    parser.add_argument("--positional", action="store_true", help="pair functions by module position and size")
    args = parser.parse_args()
    candidates = positional_pairs() if args.positional else pairs()
    if args.limit:
        candidates = candidates[:args.limit]
    print(f"{len(candidates)} candidate pairs", flush=True)
    results = defaultdict(int)
    rewritten = []
    compilers_path = EU / "config" / "arm9" / "file_compilers.json"
    compilers = json.loads(compilers_path.read_text(encoding="utf-8"))
    with tempfile.TemporaryDirectory(dir=EU / "build") as temp, ThreadPoolExecutor(args.jobs) as pool:
        for pair, found, status in pool.map(lambda p: try_pair(p, Path(temp)), candidates):
            results[status.split(":")[0]] += 1
            if found is None:
                continue
            text, cc = found
            rewritten.append(pair[1].relative_to(ROOT).as_posix())
            if not args.dry_run:
                pair[1].write_text(text, encoding="utf-8", newline="\n")
                if cc:
                    compilers[pair[0]["source"]] = cc
    if not args.dry_run:
        compilers_path.write_text(json.dumps(compilers, indent=2) + "\n", encoding="utf-8")
    report = ROOT / "build" / "dedupe_regions.json"
    report.write_text(json.dumps({"results": results, "rewritten": rewritten}, indent=1) + "\n", encoding="utf-8")
    print(dict(results), f"-> {len(rewritten)} EU files {'would be ' if args.dry_run else ''}rewritten")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
