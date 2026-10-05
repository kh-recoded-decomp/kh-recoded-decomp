#!/usr/bin/env python3
"""Generate sources for every data range that no other generator or hand source covers.

Each dsd symbol (and each uncovered range start) becomes one C definition sized to the
next symbol. Content picks the type: a printable string becomes a char array, a table of
relocated words becomes an array of pointers named by their targets (symbol + offset),
pointers at unaligned offsets go in a byte-packed struct, small halfword pairs become
s16/u16 arrays, and everything else becomes u32, u16 or u8 words by alignment. .bss gets
sized globals. .ctor is not C data and is skipped.
MWCC orders a file's data by size, so each file covers a run of strictly increasing
sizes; a run that does not verify is retried one object per file. Units are verified by
data_match.py before they are registered.
"""

from __future__ import annotations

import argparse
import bisect
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import data_match  # noqa: E402
import gen_bss  # noqa: E402
import gen_data_tables  # noqa: E402
import gen_strings  # noqa: E402

RELOC_LINE = re.compile(r"^from:0x([0-9a-f]+) kind:load to:0x([0-9a-f]+) module:(\S+)", re.I)
UNALIGNED_PTR = ("typedef struct UnalignedPtr {\n    void *ptr __attribute__((packed));\n"
                 "} __attribute__((packed)) UnalignedPtr;")
PREFIX = {"rodata": "Rodata", "data": "Data", "bss": "Bss"}
ORIGIN = {"words": "generated words", "table": "generated table", "strings": "generated strings",
          "layout": "generated layout"}


def owner_modules(text: str) -> list[str]:
    found = re.fullmatch(r"overlays\(([\d,\s]+)\)", text)
    if found:
        return [f"ov{int(n):03d}" for n in found.group(1).split(",")]
    owner = gen_data_tables.reloc_owner(text)
    return [owner] if owner else []


class Symbols:
    """Non-label symbols per module, with the names a source may use for each."""

    def __init__(self) -> None:
        self.rows: dict[str, dict[int, list[tuple[str, str, bool]]]] = {}
        for module in data_match.all_modules():
            table = self.rows.setdefault(module, {})
            for line in (data_match.module_dir(module) / "symbols.txt").read_text(encoding="utf-8").splitlines():
                found = data_match.SYMBOL_LINE.match(line)
                if found and found.group(2) != "label":
                    thumb = found.group(2) == "function" and (found.group(4) or "").startswith("thumb")
                    table.setdefault(int(found.group(5), 16), []).append((found.group(1), found.group(2), thumb))
        preferred = gen_data_tables.load_symbols()
        for module, table in self.rows.items():
            for address, names in table.items():
                name, kind, thumb = preferred[module].get(address, names[0])
                if kind != "label" and name != names[0][0]:
                    names.insert(0, (name, kind, thumb))
        self.sorted = {m: sorted(t) for m, t in self.rows.items()}

    def data_names(self, module: str) -> dict[int, str]:
        return {a: n[0] for a, names in self.rows[module].items() for n in names if n[1] in ("data", "bss")}

    def reference(self, module: str, word: int, owner_text: str, index: dict):
        """(name, kind, addend) whose resolved address plus addend equals word, or None."""
        for owner in owner_modules(owner_text):
            if owner not in self.sorted:
                continue
            addresses = self.sorted[owner]
            position = bisect.bisect_right(addresses, word) - 1
            if position < 0:
                continue
            for address in (word & ~1, addresses[position]) if word & 1 else (addresses[position],):
                for name, kind, thumb in self.rows[owner].get(address, []):
                    value = address | int(thumb)
                    if value > word or not name.isidentifier():
                        continue
                    try:
                        if data_match.resolve(name, module, index)[:2] != (owner, address):
                            continue
                    except RuntimeError:
                        continue
                    return name, kind, word - value
        return None


def printable(blob: bytes) -> str | None:
    """A char array literal when the object is text (with NUL separators and padding)."""
    text = blob.rstrip(b"\0")
    if len(text) < 2 or len(text) == len(blob) or not (32 <= text[0] < 127):
        return None
    if any(not (32 <= c < 127 or c in (0, 9, 10, 13)) for c in text):
        return None
    if sum(c == 0 for c in text) * 4 > len(text):
        return None
    out = []
    for c in text:
        out.append("\\000" if c == 0 else gen_strings.ESCAPES.get(c, chr(c)))
    return "".join(out)


def halfword_type(blob: bytes) -> str | None:
    """s16/u16 when every halfword is a small number and the words are not plain 32-bit ints."""
    halves = list(struct.unpack(f"<{len(blob) // 2}H", blob))
    if len(halves) < 4 or not all(h < 0x200 or h >= 0xFE00 for h in halves):
        return None
    if all(upper in (0, 0xFFFF) for upper in halves[1::2]):
        return None
    return "s16" if any(h >= 0x8000 for h in halves) else "u16"


def number_lines(values: list[int], width: int, per_line: int) -> str:
    items = [str(v) for v in values] if width == 0 else [f"0x{v:0{width}X}" for v in values]
    return "\n".join("    " + ", ".join(items[i:i + per_line]) + "," for i in range(0, len(items), per_line))


class Object:
    def __init__(self, address: int, name: str, size: int) -> None:
        self.address, self.name, self.size = address, name, size
        self.origin = "words"
        self.text = ""
        self.forward = ""
        self.externs: dict[str, str] = {}
        self.references: set[str] = set()
        self.packed = False


def pointer(module: str, obj: Object, word: int, reloc, symbols: Symbols, index: dict) -> str | None:
    target = symbols.reference(module, word, reloc[1], index)
    if target is None:
        return None
    name, target_kind, addend = target
    obj.references.add(name)
    if target_kind == "function":
        obj.externs[name] = f"extern void {name}(void);"
    else:
        obj.externs[name] = f"extern u8 {name}[];"
    return f"(u8 *){name} + 0x{addend:X}" if addend else f"(void *){name}"


def packed(module: str, kind: str, obj: Object, blob: bytes, relocs: dict, inside: list[int],
           symbols: Symbols, index: dict) -> bool:
    """Pointers at unaligned offsets: a byte-packed struct of byte runs and pointer runs."""
    members, values, cursor = [], [], 0
    while cursor < obj.size:
        at = obj.address + cursor
        if at in relocs:
            items = []
            while obj.address + cursor in relocs and cursor + 4 <= obj.size:
                word = struct.unpack_from("<I", blob, cursor)[0]
                item = pointer(module, obj, word, relocs[obj.address + cursor], symbols, index)
                if item is None:
                    return False
                items.append(item)
                cursor += 4
            members.append(f"    UnalignedPtr pointers{len(members)}[{len(items)}];")
            values.append("    {\n" + "\n".join(f"        {{{item}}}," for item in items) + "\n    },")
            continue
        following = min([a - obj.address for a in inside if a >= at] + [obj.size])
        chunk = list(blob[cursor:following])
        members.append(f"    u8 bytes{len(members)}[{len(chunk)}];")
        rows = "\n".join("        " + ", ".join(f"0x{v:02X}" for v in chunk[i:i + 16]) + ","
                         for i in range(0, len(chunk), 16))
        values.append("    {\n" + rows + "\n    },")
        cursor = following
    const = "const " if kind == "rodata" else ""
    obj.packed = True
    obj.text = (f"{const}struct {{\n" + "\n".join(members) + f"\n}} __attribute__((packed)) {obj.name} = {{\n"
                + "\n".join(values) + "\n};")
    return True


def build(module: str, kind: str, obj: Object, blob: bytes, relocs: dict, symbols: Symbols, index: dict) -> bool:
    const = "const " if kind == "rodata" else ""
    if kind == "bss":
        obj.origin = "layout"
        obj.text = gen_bss.declaration(obj.name, obj.address, obj.size)
        return True
    inside = sorted(at for at in relocs if obj.address <= at < obj.address + obj.size)
    if any(at < obj.address < at + 4 for at in range(obj.address - 3, obj.address) if at in relocs):
        return False
    if inside:
        if any(at + 4 > obj.address + obj.size for at in inside):
            return False
        if obj.address % 4 or obj.size % 4 or any(at % 4 for at in inside):
            return packed(module, kind, obj, blob, relocs, inside, symbols, index)
        items = []
        for offset in range(0, obj.size, 4):
            word = struct.unpack_from("<I", blob, offset)[0]
            reloc = relocs.get(obj.address + offset)
            if reloc is None:
                items.append("NULL" if word == 0 else f"(void *)0x{word:08X}")
                continue
            item = pointer(module, obj, word, reloc, symbols, index)
            if item is None:
                return False
            items.append(item)
        obj.origin = "table" if all(i == "NULL" or not i.startswith("(void *)0x") for i in items) else "words"
        qualifier = "const " if const else ""
        body = "\n".join(f"    {item}," for item in items)
        obj.text = f"void *{qualifier}{obj.name}[{len(items)}] = {{\n{body}\n}};"
        obj.forward = f"extern void *{qualifier}{obj.name}[];"
        return True
    text = printable(blob)
    if text is not None:
        obj.origin = "strings"
        obj.text = f'{const}char {obj.name}[{obj.size}] = "{text}";'
        obj.forward = f"extern {const}char {obj.name}[];"
        return True
    halfwords = halfword_type(blob) if obj.address % 4 == 0 and obj.size % 4 == 0 else None
    if halfwords:
        values = list(struct.unpack(f"<{obj.size // 2}{'h' if halfwords == 's16' else 'H'}", blob))
        element, width, per_line = halfwords, 0, 8
    elif obj.address % 4 == 0 and obj.size % 4 == 0:
        values = list(struct.unpack(f"<{obj.size // 4}I", blob))
        element, width, per_line = "u32", 8, 4
    elif obj.address % 2 == 0 and obj.size % 2 == 0:
        values = list(struct.unpack(f"<{obj.size // 2}H", blob))
        element, width, per_line = "u16", 4, 8
    else:
        values = list(blob)
        element, width, per_line = "u8", 2, 16
    obj.text = f"{const}{element} {obj.name}[{len(values)}] = {{\n{number_lines(values, width, per_line)}\n}};"
    obj.forward = f"extern {const}{element} {obj.name}[];"
    return True


def write_unit(module: str, kind: str, run: list[Object]) -> dict:
    defined = {o.name: o for o in run}
    externs = {}
    forwards = []
    for obj in run:
        for name, line in obj.externs.items():
            if name in defined:
                if defined[name].forward and defined[name].forward not in forwards:
                    forwards.append(defined[name].forward)
            else:
                externs[name] = line
    lines = ['#include "nitro/types.h"', ""]
    if kind == "data":
        lines += ["#pragma explicit_zero_data on", ""]
    if externs or forwards:
        lines += sorted(externs.values()) + forwards + [""]
    if any(o.packed for o in run):
        lines += [UNALIGNED_PTR, ""]
    lines.append("\n\n".join(o.text for o in reversed(run)))
    start, end = run[0].address, run[-1].address + run[-1].size
    source = ROOT / "src" / module / "data" / f"{PREFIX[kind]}_{module}_{start:08x}.c"
    source.parent.mkdir(parents=True, exist_ok=True)
    source.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")
    origins = {o.origin for o in run}
    origin = origins.pop() if len(origins) == 1 else "words"
    behaviors = {"words": "Initialised data words, pointers named by their targets.",
                 "table": "Tables of function and data pointers, each entry named by its target.",
                 "strings": "Text strings referenced by this module's code.",
                 "layout": "Uninitialised globals, one per known symbol, sized by layout."}
    names = {"words": "data words", "table": "pointer tables", "strings": "strings", "layout": ".bss layout"}
    return {"module": module, "section": f".{kind}", "start": f"{start:#010x}", "end": f"{end:#010x}",
            "source": source.relative_to(ROOT).as_posix(), "compiler": "mwccarm-4.0-1036",
            "name": f"{module} {names[origin]}", "origin": ORIGIN[origin], "behavior": behaviors[origin]}


def named_spans(module: str, kind: str) -> list[tuple[int, int]]:
    """Spans of the section itself; .ctor shares the rodata kind but is not C data."""
    header = (data_match.module_dir(module) / "delinks.txt").read_text(encoding="utf-8")
    return [(int(a, 16), int(b, 16)) for name, a, b in
            re.findall(r"^\s*(\S+)\s+start:0x([0-9a-f]+) end:0x([0-9a-f]+) kind:", header, re.M) if name == f".{kind}"]


def gaps(spans: list[tuple[int, int]], taken: list[tuple[int, int]]) -> list[tuple[int, int, int]]:
    """Uncovered (start, end, span_end) ranges."""
    result = []
    for start, end in spans:
        cursor = start
        for a, b in sorted(t for t in taken if t[0] < end and start < t[1]):
            if a > cursor:
                result.append((cursor, a, end))
            cursor = max(cursor, b)
        if cursor < end:
            result.append((cursor, end, end))
    return result


def try_unit(module: str, kind: str, run: list[Object], index: dict, registered_sources: set[str]):
    entry = write_unit(module, kind, run)
    if entry["source"] in registered_sources:
        raise RuntimeError(f"source name {entry['source']} already registered")
    try:
        data_match.verify(entry, index)
        return entry, None
    except Exception as exc:  # noqa: BLE001 - failing units are retried or reported
        (ROOT / entry["source"]).unlink(missing_ok=True)
        return None, str(exc).splitlines()[0][:120]


def drop_unaligned(entries: list[dict], new: list[dict]) -> list[dict]:
    """A dsd gap object starts word-aligned, so a new unit may not end mid-word before a gap."""
    while True:
        removed = False
        for entry in list(new):
            module, end = entry["module"], int(entry["end"], 16)
            if end % 4 == 0:
                continue
            span_end = next(b for a, b in named_spans(module, data_match.SECTIONS[entry["section"]])
                            if a <= int(entry["start"], 16) < b)
            if end == span_end or any(e["module"] == module and int(e["start"], 16) == end for e in entries):
                continue
            entries.remove(entry)
            new.remove(entry)
            (ROOT / entry["source"]).unlink(missing_ok=True)
            removed = True
        if not removed:
            return entries


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--module", action="append", help="Limit to these modules")
    parser.add_argument("--section", action="append", choices=["rodata", "data", "bss"])
    parser.add_argument("--dry-run", action="store_true", help="Report coverage without writing")
    args = parser.parse_args()
    symbols = Symbols()
    index = data_match.symbol_index()
    registered = data_match.load()
    sources = {e["source"] for e in registered}
    new, failures, unsupported = [], [], []
    for module in args.module or data_match.all_modules():
        relocs = {}
        for line in (data_match.module_dir(module) / "relocs.txt").read_text(encoding="utf-8").splitlines():
            found = RELOC_LINE.match(line)
            if found:
                relocs[int(found.group(1), 16)] = (int(found.group(2), 16), found.group(3))
        base, binary = data_match.module_binary(module)
        names = symbols.data_names(module)
        taken = [(int(e["start"], 16), int(e["end"], 16)) for e in registered if e["module"] == module]
        for kind in args.section or ["rodata", "data", "bss"]:
            for gap_start, gap_end, _ in gaps(named_spans(module, kind), taken):
                starts = sorted({gap_start} | {a for a in names if gap_start < a < gap_end})
                objects = []
                for address, following in zip(starts, starts[1:] + [gap_end]):
                    name = names.get(address, gen_bss.symbol_name(module, address))
                    if not name.isidentifier():
                        name = gen_bss.symbol_name(module, address)
                    obj = Object(address, name, following - address)
                    blob = binary[address - base:following - base]
                    if build(module, kind, obj, blob, relocs, symbols, index):
                        objects.append(obj)
                    else:
                        objects.append(None)
                        unsupported.append(f"{module} {kind} {address:#010x} size {following - address:#x}")
                if args.dry_run:
                    continue
                runs, run = [], []
                for obj in objects + [None]:
                    if obj and run and obj.size > run[-1].size:
                        run.append(obj)
                        continue
                    if run:
                        runs.append(run)
                    run = [obj] if obj else []
                for run in runs:
                    entry, error = try_unit(module, kind, run, index, sources)
                    if entry:
                        new.append(entry)
                        continue
                    if len(run) == 1:
                        failures.append(f"{module} {kind} {run[0].address:#010x}: {error}")
                        continue
                    for obj in run:
                        entry, error = try_unit(module, kind, [obj], index, sources)
                        if entry:
                            new.append(entry)
                        else:
                            failures.append(f"{module} {kind} {obj.address:#010x}: {error}")
    for line in unsupported:
        print("UNSUPPORTED", line)
    for line in failures:
        print("FAIL", line)
    if args.dry_run:
        return 0
    registered = drop_unaligned(registered + new, new)
    data_match.save(registered)
    added = {}
    for entry in new:
        added[entry["section"]] = added.get(entry["section"], 0) + int(entry["end"], 16) - int(entry["start"], 16)
    print(f"Registered {len(new)} units: " + ", ".join(f"{k} {v:,}" for k, v in sorted(added.items())))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
