#!/usr/bin/env python3
"""Rename reviewed C symbols and their references after a complete preflight.

Accept one old/new pair or --map-file JSON containing pairs or candidate objects.
Batch mode reads each source/library/config file once and validates every name
and destination before writing. Shared-region alias interpretation remains the
caller's responsibility, as for a single rename.
"""

import argparse
import json
from pathlib import Path
import re

from project import ROOT


SOURCE_SUFFIXES = {".c", ".cpp", ".cc", ".cp"}
TEXT_SUFFIXES = SOURCE_SUFFIXES | {".h", ".hpp", ".txt", ".json", ".yaml", ".yml"}
IDENTIFIER = re.compile(r"^[A-Za-z_]\w*$")


def is_existing_alias(text: str, old: str, new: str) -> bool:
    """Accept a lone direct alias for this same symbol, not an occupied name."""
    if len(re.findall(rf"\b{re.escape(new)}\b", text)) != 1:
        return False
    alias = re.compile(rf"[ \t]*#[ \t]*define[ \t]+{re.escape(new)}[ \t]+{re.escape(old)}[ \t]*")
    return any(alias.fullmatch(line) for line in text.lstrip("\ufeff").splitlines())


def rename_symbols(pairs, move_calls=False):
    if not pairs or any(len(pair) != 2 for pair in pairs):
        raise SystemExit("expected at least one old/new pair")
    if any(not isinstance(name, str) or not IDENTIFIER.fullmatch(name)
           for pair in pairs for name in pair):
        raise SystemExit("both names must be C identifiers")
    if any(old == new for old, new in pairs):
        raise SystemExit("old and new names are identical")
    mapping = dict(pairs)
    if len(mapping) != len(pairs) or len(set(mapping.values())) != len(pairs):
        raise SystemExit("old and new names must each be unique")
    if set(mapping).intersection(mapping.values()):
        raise SystemExit("old/new name chains or cycles are not supported")
    reverse = {new: old for old, new in pairs}
    pattern = re.compile(r"\b(?:" + "|".join(map(re.escape, mapping)) + r")\b")
    new_pattern = re.compile(r"\b(?:" + "|".join(map(re.escape, reverse)) + r")\b")
    changed = []
    definitions = {old: [] for old in mapping}
    for root_name in ("src", "libs", "config"):
        for path in (ROOT / root_name).rglob("*"):
            if not path.is_file() or path.suffix.lower() not in TEXT_SUFFIXES:
                continue
            text = path.read_text(encoding="utf-8")
            defining = path.stem if path.stem in mapping and path.suffix.lower() in SOURCE_SUFFIXES else None
            for new in set(new_pattern.findall(text)):
                old = reverse[new]
                if defining != old and not is_existing_alias(text, old, new):
                    raise SystemExit(f"new symbol already appears in {path}")
            replaced, count = pattern.subn(lambda match: mapping[match[0]], text)
            if count:
                changed.append((path, replaced, count))
            if defining is not None:
                definitions[defining].append(path)

    moves = []
    for old, new in pairs:
        if len(definitions[old]) != 1:
            raise SystemExit(f"expected one defining source for {old}, found {len(definitions[old])}")
        source = definitions[old][0]
        if move_calls and source.parent.name == "auto":
            destination = source.parent.parent / "calls" / f"{new}{source.suffix}"
        else:
            destination = source.with_name(f"{new}{source.suffix}")
        if destination.exists():
            raise SystemExit(f"destination already exists: {destination}")
        moves.append((source, destination))
    if len({destination for _, destination in moves}) != len(moves):
        raise SystemExit("rename destinations must be unique")

    for path, replaced, _count in changed:
        path.write_text(replaced, encoding="utf-8", newline="\n")
    for (old, new), (source, destination) in zip(pairs, moves):
        destination.parent.mkdir(parents=True, exist_ok=True)
        source.rename(destination)
        print(f"{old} -> {new}")
        print(f"definition: {destination.relative_to(ROOT)}")
    print(f"updated {len(changed)} files, {sum(count for _, _, count in changed)} references")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("old", nargs="?")
    parser.add_argument("new", nargs="?")
    parser.add_argument("--map-file", type=Path, help="JSON old/new pairs or an object with candidates")
    parser.add_argument("--move-calls", action="store_true",
                        help="move defining auto sources to their sibling calls directories")
    args = parser.parse_args()
    if args.map_file is not None:
        if args.old is not None or args.new is not None:
            parser.error("use either old/new or --map-file")
        data = json.loads(args.map_file.read_text(encoding="utf-8-sig"))
        entries = data["candidates"] if isinstance(data, dict) else data
        pairs = [[item["old"], item["new"]] if isinstance(item, dict) else item for item in entries]
    else:
        if args.old is None or args.new is None:
            parser.error("provide old/new or --map-file")
        pairs = [[args.old, args.new]]
    rename_symbols(pairs, args.move_calls)


if __name__ == "__main__":
    main()
