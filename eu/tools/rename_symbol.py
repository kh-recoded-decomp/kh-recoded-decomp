#!/usr/bin/env python3
"""Rename reviewed C symbols and their references after a complete preflight.

Accept one old/new pair or --map-file JSON containing pairs or candidate objects.
Batch mode reads each source/library/config file once and validates every name
and destination before writing. In function mode, shared-region alias
interpretation remains the caller's responsibility, as for a single rename.

For reviewed DATA definitions in aggregate files, --keep-source-paths requires
an explicit source for every candidate and preserves filenames and declarations.
It preserves shared-region include paths and macro left sides, and supplies
EU aliases when the actual DATA definition comes from a shared source.
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


def has_data_definition(text: str, name: str) -> bool:
    """Recognize plain/aligned, aggregate and callback-pointer data declarations.

    Deliberately reject assembly aliases, macros and other declarators: those
    need their own reviewed definition handling instead of a guessed source.
    """
    text = re.sub(r"/\*.*?\*/|//[^\n]*", "", text.lstrip("\ufeff"), flags=re.S)
    text = re.sub(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  lambda match: re.sub(r"[^\n]", " ", match[0]), text)
    declaration = re.compile(
        r"(?m)^(?![ \t]*(?:extern|typedef)\b)[ \t]*[A-Za-z_]\w*[\w \t*]*[ \t*]" + re.escape(name)
        + r"[ \t]*(?:\[[^\]\n]*\][ \t]*)*"
        + r"(?:__attribute__[ \t]*\(\([ \t]*aligned[ \t]*\([ \t]*(?:0[xX][0-9a-fA-F]+|[0-9]+)[ \t]*\)[ \t]*\)\)[ \t]*)?"
        + r"(?:=|;)"
    )
    aggregate = re.compile(
        r"(?m)^}[ \t]*(?:__attribute__[ \t]*\(\([ \t]*packed[ \t]*\)\)[ \t]*)?"
        + re.escape(name) + r"[ \t]*(?:\[[^\]\n]*\][ \t]*)*(?:=|;)"
    )
    callback = re.compile(
        r"(?m)^(?![ \t]*(?:extern|typedef)\b)[ \t]*[\w \t*]+\(\*[ \t]*(?:const[ \t]+)?"
        + re.escape(name) + r"[ \t]*(?:\[[^\]\n]*\][ \t]*)*\)[ \t]*\([^;{}\n]*\)[ \t]*(?:=|;)"
    )
    for pattern, expected_depth in ((declaration, 0), (aggregate, 1), (callback, 0)):
        for match in pattern.finditer(text):
            prefix = text[:match.start()]
            if prefix.count("{") - prefix.count("}") == expected_depth:
                return True
    return False


def rename_symbols(pairs, move_calls=False, definition_sources=None):
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
    if definition_sources is not None:
        if move_calls or set(definition_sources) != set(mapping):
            raise SystemExit("keep-source mode needs one source per pair and cannot move calls")
        expected = {}
        for old, relative in definition_sources.items():
            path = (ROOT / relative).resolve()
            if (not any(path.is_relative_to((ROOT / root).resolve()) for root in ("src", "libs"))
                    or not path.is_file() or path.suffix.lower() not in SOURCE_SUFFIXES):
                raise SystemExit(f"expected a C/C++ defining source inside src or libs for {old}")
            expected[old] = path
    reverse = {new: old for old, new in pairs}
    pattern = re.compile(r"\b(?:" + "|".join(map(re.escape, mapping)) + r")\b")
    new_pattern = re.compile(r"\b(?:" + "|".join(map(re.escape, reverse)) + r")\b")
    changed = []
    definitions = {old: [] for old in mapping}
    shared_cache = {}
    for root_name in ("src", "libs", "config"):
        for path in (ROOT / root_name).rglob("*"):
            if definition_sources is not None and path.is_file() and path.suffix.lower() == ".s":
                assembly = path.read_text(encoding="utf-8")
                if pattern.search(assembly) or new_pattern.search(assembly):
                    raise SystemExit(f"assembly symbols need explicit definition/reference handling: {path}")
            if not path.is_file() or path.suffix.lower() not in TEXT_SUFFIXES:
                continue
            text = path.read_text(encoding="utf-8")
            body, aliases = None, {}
            if definition_sources is not None and path.suffix.lower() in SOURCE_SUFFIXES:
                include = re.search(r'^\s*#include "(src/[^\"]+\.(?:c|cpp|cc|cp))"', text.lstrip("\ufeff"), re.M)
                if include:
                    shared = (ROOT.parent / include[1]).resolve()
                    if shared.is_relative_to((ROOT.parent / "src").resolve()) and shared.is_file():
                        if shared not in shared_cache:
                            shared_cache[shared] = shared.read_text(encoding="utf-8-sig")
                        body = shared_cache[shared]
                        aliases = dict(re.findall(r'^#define (\w+) (\w+)$', text.lstrip("\ufeff"), re.M))
            defining = path.stem if path.stem in mapping and path.suffix.lower() in SOURCE_SUFFIXES else None
            for new in set(new_pattern.findall(text)):
                old = reverse[new]
                if defining != old and not is_existing_alias(text, old, new):
                    raise SystemExit(f"new symbol already appears in {path}")
            replaced, count = pattern.subn(lambda match: mapping[match[0]], text)
            if body is not None:
                hidden = sorted(old for old in set(pattern.findall(body)) if old not in aliases)
                lines = []
                for line in text.lstrip("\ufeff").splitlines():
                    macro = re.match(r'(\s*#define\s+\w+)(\s+)(.*)', line)
                    if re.match(r'\s*#include "src/[^\"]+\.(?:c|cpp|cc|cp)"', line):
                        lines.append(line)
                    elif macro:
                        lines.append(macro[1] + macro[2] + pattern.sub(lambda m: mapping[m[0]], macro[3]))
                    else:
                        lines.append(pattern.sub(lambda m: mapping[m[0]], line))
                prefix = ''.join('#define ' + old + ' ' + mapping[old] + '\n' for old in hidden)
                replaced = ('\ufeff' if text.startswith('\ufeff') else '') + prefix + '\n'.join(lines) + '\n'
                count += len(hidden)
            if count:
                changed.append((path, replaced, count))
            if definition_sources is not None and path.suffix.lower() in SOURCE_SUFFIXES:
                expanded = body
                if body is not None and aliases:
                    alias_pattern = re.compile(r'\b(?:'+'|'.join(map(re.escape,aliases))+r')\b')
                    expanded = alias_pattern.sub(lambda m:aliases[m[0]],body)
                names = set(pattern.findall(text)) | (set(pattern.findall(expanded)) if expanded is not None else set())
                for old in names:
                    if has_data_definition(text, old) or (expanded is not None and has_data_definition(expanded,old)):
                        definitions[old].append(path)
            elif defining is not None:
                definitions[defining].append(path)

    moves = []
    for old, new in pairs:
        if len(definitions[old]) != 1:
            raise SystemExit(f"expected one defining source for {old}, found {len(definitions[old])}")
        source = definitions[old][0]
        if definition_sources is not None:
            if source.resolve() != expected[old]:
                raise SystemExit(f"defining source does not match the reviewed source for {old}")
            continue
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
    for index, (old, new) in enumerate(pairs):
        if definition_sources is None:
            source, destination = moves[index]
            destination.parent.mkdir(parents=True, exist_ok=True)
            source.rename(destination)
        else:
            destination = definitions[old][0]
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
    parser.add_argument("--keep-source-paths", action="store_true",
                        help="rename DATA in place; every map candidate must include its defining source")
    args = parser.parse_args()
    if args.map_file is not None:
        if args.old is not None or args.new is not None:
            parser.error("use either old/new or --map-file")
        data = json.loads(args.map_file.read_text(encoding="utf-8-sig"))
        entries = data["candidates"] if isinstance(data, dict) else data
        pairs = [[item["old"], item["new"]] if isinstance(item, dict) else item for item in entries]
        if args.keep_source_paths:
            if args.move_calls or any(not isinstance(item, dict) or not isinstance(item.get("source"), str)
                                      for item in entries):
                parser.error("--keep-source-paths needs candidate sources and cannot use --move-calls")
            sources = {item["old"]: item["source"] for item in entries}
        else:
            sources = None
    else:
        if args.keep_source_paths:
            parser.error("--keep-source-paths requires --map-file with candidate sources")
        if args.old is None or args.new is None:
            parser.error("provide old/new or --map-file")
        pairs = [[args.old, args.new]]
        sources = None
    rename_symbols(pairs, args.move_calls, sources)


if __name__ == "__main__":
    main()
