#!/usr/bin/env python3
"""Rebuild build/func_index.json from FIRST PRINCIPLES: the extracted module binaries plus the
dsd config (symbols.txt / relocs.txt / delinks.txt).

The delink objects only contain the functions that are still gaps: once a function has a
source it leaves them, so an index built from delinks can never cover finished functions.

A function's bytes are the ROM at its address. This indexes functions with an explicit size in
symbols.txt and relocations recorded in relocs.txt, whether decompiled or not. Existing entries
may contain additional compiler-derived relocations, so merging never replaces them.

Configured relocation targets, including addends, are checked against linked ROM instructions
and pointers before any cross-check or write. Historical symbol names may differ only when their
resolved addresses or linked relocation bytes agree with the reconstruction.

At a relocated word an entry holds the ROM's linked value. Every consumer of this index
(verify_idx.py, dedupprop.py, port_days.py) masks relocated words before comparing; do not
"fix" this by zeroing the words, because the opcode byte of a `bl` lives in the same word.

Default is a dry run that VERIFIES itself against the entries already in the index; pass --write
to merge the missing ones in.

Usage:  python tools/rebuild_index.py [--write]
"""
import glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INDEX_PATH = os.path.join(ROOT, "build", "func_index.json")

SEC_RE = re.compile(r"^\s*\.text\s+start:0x([0-9a-fA-F]+)\s+end:0x([0-9a-fA-F]+)")
SYM_RE = re.compile(r"^(\S+)\s+kind:(\w+)\(?([^,)]*),?[^)]*\)?[^a-z]*.*addr:0x([0-9a-fA-F]+)")
FUNC_RE = re.compile(r"^(\S+)\s+kind:function\((arm|thumb),size=0x([0-9a-fA-F]+)\)\s+addr:0x([0-9a-fA-F]+)")
REL_RE = re.compile(r"^from:0x([0-9a-fA-F]+)\s+kind:(\S+)\s+to:0x([0-9a-fA-F]+)(?:\s+add:(-?0x[0-9a-fA-F]+))?\s+module:(\S+)")


def module_dirs():
    """Every dsd module directory, paired with the binary it was extracted from."""
    out = []
    main = os.path.join(ROOT, "config", "arm9")
    out.append((main, os.path.join(ROOT, "dsd_extract", "arm9", "arm9.bin")))
    for name in ("itcm", "dtcm"):
        d = os.path.join(main, name)
        if os.path.isdir(d):
            out.append((d, os.path.join(ROOT, "dsd_extract", "arm9", name + ".bin")))
    for d in sorted(glob.glob(os.path.join(main, "overlays", "ov*"))):
        ov = os.path.basename(d)
        out.append((d, os.path.join(ROOT, "dsd_extract", "arm9_overlays", ov + ".bin")))
    return out


def text_start(delinks_path):
    with open(delinks_path, encoding="utf-8", errors="replace") as f:
        for ln in f:
            m = SEC_RE.match(ln)
            if m:
                return int(m.group(1), 16)
    return None


# Pass 1: symbol address -> name, kept PER MODULE. Overlays share address ranges, so a global map
# is ambiguous: one address can be a real function in two overlays. relocs.txt names the target
# module for exactly this reason -- use it.
def mod_key(d):
    if d == os.path.join(ROOT, "config", "arm9"):
        return "main"
    b = os.path.basename(d)
    return "overlay(%d)" % int(b[2:]) if b.startswith("ov") and b[2:].isdigit() else b


by_mod = {}
symbol_addresses = {}
thumb_targets = set()


def load_symbols():
    by_mod.clear()
    symbol_addresses.clear()
    thumb_targets.clear()
    for d, _bin in module_dirs():
        p = os.path.join(d, "symbols.txt")
        if not os.path.exists(p):
            continue
        m2 = by_mod.setdefault(mod_key(d), {})
        with open(p, encoding="utf-8", errors="replace") as f:
            for ln in f:
                m = SYM_RE.match(ln)
                if m:
                    m2.setdefault(int(m.group(4), 16), m.group(1))
                    symbol_addresses.setdefault(m.group(1), set()).add(int(m.group(4), 16))
                m = FUNC_RE.match(ln)
                if m and m.group(2) == "thumb":
                    thumb_targets.add((mod_key(d), int(m.group(4), 16)))


def candidate_mods(mod):
    """relocs.txt names the target module three ways: `main` / `itcm` / `dtcm`, `overlay(N)`, and
    `overlays(N,M)` -- the last for a target that could be in either of two overlays (they never
    share a slot at runtime, so dsd records the ambiguity rather than resolving it)."""
    m = re.match(r"^overlays\(([\d,]+)\)$", mod)
    if m:
        return ["overlay(%s)" % n for n in m.group(1).split(",")]
    return [mod]


def sym_at(t, mod):
    """Name for a reloc target, resolved inside the module(s) the reloc names.

    Three traps, each of which produced silently wrong names:
      - the address is tried AS-IS first, because data symbols can sit on an odd address
        (a byte symbol at an odd address is distinct from its even neighbour); &~1 is only the THUMB bit on a
        code target, so it is the fallback, not the rule;
      - the lookup is per module, because overlays overlap in address space (one address can be
        a real function in two overlays);
      - `overlays(N,M)` targets have to try each named overlay.
    """
    for key in candidate_mods(mod) + ["main"]:
        table = by_mod.get(key, {})
        if t in table:
            return table[t]
        if (key, t & ~1) in thumb_targets and (t & ~1) in table:
            return table[t & ~1]
    return "0x%08x" % t


def linked_target(word, address, kind):
    """Decode a linked ARM9 relocation, rejecting an unexpected instruction kind."""
    def signed(value, bits):
        return value - (1 << bits) if value & (1 << (bits - 1)) else value

    if kind == "load":
        return word
    if kind in ("arm_call", "arm_branch"):
        opcode = 0x0b000000 if kind == "arm_call" else 0x0a000000
        if word >> 28 == 15 or word & 0x0f000000 != opcode:
            raise ValueError("unexpected ARM branch opcode")
        return (address + 8 + signed(word & 0xffffff, 24) * 4) & 0xffffffff
    if kind == "arm_call_thumb":
        if word & 0xfe000000 != 0xfa000000:
            raise ValueError("unexpected ARM BLX opcode")
        return (address + 8 + signed(word & 0xffffff, 24) * 4
                + ((word >> 23) & 2)) & 0xffffffff
    if kind in ("thumb_call", "thumb_call_arm"):
        first, second = word & 0xffff, word >> 16
        opcode = 0xf800 if kind == "thumb_call" else 0xe800
        if first & 0xf800 != 0xf000 or second & 0xf800 != opcode:
            raise ValueError("unexpected Thumb BL/BLX opcode")
        displacement = signed(((first & 0x7ff) << 12) | ((second & 0x7ff) << 1), 23)
        target = (address + 4 + displacement) & 0xffffffff
        return target & ~3 if kind == "thumb_call_arm" else target
    raise ValueError("unsupported relocation kind: " + kind)


def check_linked_target(blob, offset, address, target, kind, target_module):
    if offset < 0 or offset + 4 > len(blob):
        raise ValueError("relocation extends outside its function")
    actual = linked_target(int.from_bytes(blob[offset:offset + 4], "little"), address, kind)
    if actual == target:
        return
    # Only a known Thumb function may acquire bit zero in an absolute pointer.
    if (kind == "load" and actual == (target | 1)
            and any((key, target) in thumb_targets for key in candidate_mods(target_module))):
        return
    raise ValueError("ROM target 0x%08x != configured target 0x%08x" % (actual, target))


def rebuild():
    # Pass 2: rebuild each module's functions.
    rebuilt = {}
    invalid = []
    for d, binpath in module_dirs():
        sp, rp, dp = (os.path.join(d, n) for n in ("symbols.txt", "relocs.txt", "delinks.txt"))
        if not (os.path.exists(sp) and os.path.exists(dp) and os.path.exists(binpath)):
            continue
        base = text_start(dp)
        if base is None:
            continue
        with open(binpath, "rb") as stream:
            blob = stream.read()
        mod = os.path.basename(d) if d != os.path.join(ROOT, "config", "arm9") else "main"

        rels = {}
        if os.path.exists(rp):
            with open(rp, encoding="utf-8", errors="replace") as f:
                for ln in f:
                    m = REL_RE.match(ln)
                    if m:
                        rels[int(m.group(1), 16)] = (
                            int(m.group(3), 16) + int(m.group(4) or "0", 16), m.group(5), m.group(2))
                    elif ln.startswith("from:") and "kind:link_time_const(" not in ln:
                        raise ValueError("unrecognized relocation: " + ln.strip())

        with open(sp, encoding="utf-8", errors="replace") as f:
            for ln in f:
                m = FUNC_RE.match(ln)
                if not m:
                    continue
                name, mode, size, addr = m.group(1), m.group(2), int(m.group(3), 16), int(m.group(4), 16)
                off = addr - base
                if size == 0 or off < 0 or off + size > len(blob):
                    continue
                r = []
                for a, (t, tm, kind) in rels.items():
                    if not addr <= a < addr + size:
                        continue
                    try:
                        check_linked_target(blob[off:off + size], a - addr, a, t, kind, tm)
                    except ValueError as exc:
                        invalid.append("%s +0x%x: %s" % (name, a - addr, exc))
                    r.append((a - addr, sym_at(t, tm)))
                r.sort()
                rebuilt[name] = {"hex": blob[off:off + size].hex(), "size": size,
                                 "relocs": [list(x) for x in r], "module": mod, "mode": mode}

    print("rebuilt from ROM+config: %d functions" % len(rebuilt))
    if invalid:
        print("\n".join(invalid[:20]))
        raise SystemExit("refusing to merge: %d relocation targets disagree with the ROM" % len(invalid))
    return rebuilt


def masked(entry):
    """hex with every reloc'd word zeroed -- the only place the ROM and the object legitimately
    disagree, and what every consumer compares on anyway."""
    b = bytearray.fromhex(entry["hex"])
    for off, _sym in entry["relocs"]:
        if off + 4 <= len(b):
            b[off:off + 4] = b"\x00\x00\x00\x00"
    return bytes(b)


def symbol_address(name):
    addresses = symbol_addresses.get(name, set())
    if len(addresses) == 1:
        return next(iter(addresses))
    if addresses:
        return None
    if re.fullmatch(r"0x[0-9a-fA-F]{8}", name):
        return int(name, 16)
    m = re.search(r"_([0-9a-fA-F]{8})$", name)
    return int(m.group(1), 16) if m else None


def same_relocations(old, new):
    """Compare an old index with a reconstruction already checked against the ROM.

    Historical indexes retain names that have since been renamed or merged. A
    changed spelling is allowed only at the same offset and with either the same
    resolved address or identical linked bytes. The latter handles names that no
    longer exist; the new target has independently been decoded from those bytes.
    Zeroed object relocations cannot establish that proof.
    """
    previous, current = dict(old["relocs"]), dict(new["relocs"])
    if previous.keys() != current.keys():
        return False
    old_bytes, new_bytes = bytes.fromhex(old["hex"]), bytes.fromhex(new["hex"])
    for off, name in previous.items():
        if name == current[off]:
            continue
        address = symbol_address(name)
        if address is not None and address == symbol_address(current[off]):
            continue
        if (0 <= off <= len(old_bytes) - 4
                and old_bytes[off:off + 4] == new_bytes[off:off + 4]
                and old_bytes[off:off + 4] != b"\0\0\0\0"):
            continue
        return False
    return True


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    load_symbols()
    rebuilt = rebuild()
    index = {}
    if os.path.exists(INDEX_PATH):
        with open(INDEX_PATH) as stream:
            index = json.load(stream)
    print("current index: %d functions" % len(index))
    # Self-check: for every function BOTH have, the reconstruction must agree once the relocated
    # words are masked. If it does not, the reconstruction is wrong and must not be merged.
    same = bad = 0
    for n, e in index.items():
        if n not in rebuilt:
            continue
        got = rebuilt[n]
        ok = (masked(got) == masked(e) and got["size"] == e["size"]
              and got["mode"] == e["mode"]
              and got["module"] == e.get("module", got["module"])
              and same_relocations(e, got))
        if ok:
            same += 1
        else:
            bad += 1
            if bad <= 5:
                print("  MISMATCH %s" % n)
                if masked(got) != masked(e):
                    mg, me = masked(got), masked(e)
                    d = [i for i in range(min(len(mg), len(me))) if mg[i] != me[i]]
                    print("    bytes differ at %d offsets (first: %s), sizes %d vs %d"
                          % (len(d), d[:6], len(mg), len(me)))
                if [list(x) for x in got["relocs"]] != [list(x) for x in e["relocs"]]:
                    print("    relocs: rebuilt=%s" % got["relocs"][:4])
                    print("            index  =%s" % [list(x) for x in e["relocs"]][:4])
    print("cross-check vs existing entries (reloc words masked): %d agree, %d DISAGREE" % (same, bad))

    missing = [n for n in rebuilt if n not in index]
    print("functions the index is missing: %d" % len(missing))

    # Keep the existing guard against widespread disagreement. Old compiler-derived entries
    # can include relocations absent from relocs.txt (including linker-defined symbols).
    # Preserve them: this command only adds missing entries.
    if bad > 5:
        print("\nrefusing to merge: %d disagreements exceed the existing-entry tolerance --"
              " inspect the existing index and configuration." % bad)
        return 1
    if bad:
        print("  (those %d entries are NOT overwritten; the existing index may contain"
              " compiler-derived relocations absent from relocs.txt)" % bad)
    if "--write" not in argv:
        print("\ndry run; pass --write to merge the missing entries in.")
        return 0

    for n in missing:
        index[n] = rebuilt[n]
    with open(INDEX_PATH, "w") as stream:
        json.dump(index, stream)
    print("merged. index now: %d functions" % len(index))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
