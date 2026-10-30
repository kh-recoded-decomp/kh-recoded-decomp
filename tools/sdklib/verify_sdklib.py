#!/usr/bin/env python3
"""Prove hand-written NitroSDK and MSL runtime routines and write their receipts.

Some SDK and CodeWarrior runtime routines were written in assembly by their
authors (copy kernels, soft-float and division helpers, context switches). No
compiler reproduces them, so they stay as their original assembly. A routine
counts as verified library code, reported beside the C and never inside it,
only when every gate below passes for its checked-in source:

1. Source: the asm stub rebuilds the ROM bytes and relocations exactly
   (eu/tools/verify_idx.py) and holds instructions, not raw words.
2. Inventory: the instructions reachable from the entry and its literal pools
   tile the routine's symbol range exactly.
3. Semantics: a portable Python model (tools/sdklib/families/*.py) and the
   ROM's own instructions, run in tools/mobiclip/arm_exec.py, agree on
   random and edge-case inputs, register results and memory alike.
4. Documentation: the routine's section in eu/docs/library/ states its
   interface, behavior and hardware dependencies.

    python tools/sdklib/verify_sdklib.py                # every registered routine
    python tools/sdklib/verify_sdklib.py _u32_div_f     # selected routines
    python tools/sdklib/verify_sdklib.py --check        # verify without writing

Receipts are kept in eu/library_receipts.json; each applies only while its
source and documentation SHA-256 are unchanged, and eu/tools/audit_progress.py
counts the routines they cover as verified library code.
"""

from __future__ import annotations

import argparse
import hashlib
import importlib
import json
import os
import random
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable, Iterable

ROOT = Path(__file__).resolve().parents[2]
EU = ROOT / "eu"
RECEIPTS = EU / "library_receipts.json"
FAMILIES = Path(__file__).resolve().parent / "families"
sys.path.insert(0, str(ROOT / "tools" / "mobiclip"))
sys.path.insert(0, str(EU / "tools"))
from arm_exec import ArmFault, Cpu, Memory  # noqa: E402

MAIN_BASE = 0x02000000
MAIN_SIZE = 0x00400000
ITCM_BASE = 0x01FF8000
ITCM_SIZE = 0x00008000
STACK_TOP = 0x023F0000
SCRATCH = 0x02380000
RAW_WORDS = re.compile(r"^\s*(?:\.word|\.long|\.inst|\.incbin|dcd)\b", re.I | re.M)
DOC_FIELDS = ("Interface", "Behavior", "Hardware")


@dataclass
class Case:
    """One call: register arguments, optional memory setup and expected results."""
    args: tuple
    regs: dict = field(default_factory=dict)       # register index -> expected value
    flags: dict = field(default_factory=dict)      # "n"/"z"/"c"/"v" -> expected bit
    setup: Callable[[Memory], None] | None = None
    check: Callable[[Cpu], str | None] | None = None   # returns a mismatch text or None
    label: str = ""


@dataclass
class Routine:
    symbol: str                     # ROM symbol (eu/config/arm9/**/symbols.txt)
    source: str                     # eu-relative asm stub
    doc: str                        # eu-relative documentation file
    cases: Callable[[random.Random], Iterable[Case]]
    index_name: str | None = None   # func_index.json name when it differs
    data: tuple = ()                # (start, end) DATA ranges inside the routine
    extent: int | None = None       # bytes to inventory when the symbol size is not the routine
    object_gate: bool = False       # check branches into other routines against the ROM image
    unreachable: tuple = ()         # (start, end) code no path reaches; documented, reported apart
    module: str | None = None       # overlay holding the routine (e.g. "ov104"); main and ITCM are always mapped


def load_symbols() -> dict:
    out = {}
    pattern = re.compile(r"^(\S+)\s+kind:(?:function\((arm|thumb),size=0x([0-9a-f]+)[^)]*\)|label\((arm|thumb)\))\s+addr:0x([0-9a-f]+)", re.I)
    for path in (EU / "config" / "arm9").glob("**/symbols.txt"):
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            m = pattern.match(line)
            if m:
                size = int(m.group(3), 16) if m.group(3) else 0
                out.setdefault(m.group(1), (int(m.group(5), 16), size, m.group(2) or m.group(4)))
    return out


def overlay_base(module: str) -> int:
    """Load address of an overlay, from the extracted overlay table."""
    table = (EU / "dsd_extract" / "arm9_overlays" / "overlays.yaml").read_text(encoding="utf-8")
    number = int(module[2:])
    for block in re.split(r"\n\s*- ", table):
        if re.search(r"^\s*id:\s*%d\s*$" % number, block, re.M):
            return int(re.search(r"base_address:\s*(\d+)", block).group(1))
    raise AssertionError("no overlay " + module)


def rom_memory(module: str | None = None) -> Memory:
    mem = Memory()
    main = bytearray(MAIN_SIZE)
    image = (EU / "dsd_extract" / "arm9" / "arm9.bin").read_bytes()
    main[:len(image)] = image
    if module:                      # overlays load into main RAM above the ARM9 image
        image = (EU / "dsd_extract" / "arm9_overlays" / (module + ".bin")).read_bytes()
        base = overlay_base(module) - MAIN_BASE
        main[base:base + len(image)] = image
    mem.map(MAIN_BASE, main)
    itcm = bytearray(ITCM_SIZE)
    image = (EU / "dsd_extract" / "arm9" / "itcm.bin").read_bytes()
    itcm[:len(image)] = image
    mem.map(ITCM_BASE, itcm)
    return mem


def gate_source(routine: Routine, symbols: dict) -> str:
    import verify_idx
    text = (EU / routine.source).read_text(encoding="utf-8", errors="replace")
    if RAW_WORDS.search(text):
        raise AssertionError("source holds raw words instead of instructions")
    name = routine.index_name or routine.symbol
    if routine.object_gate or name not in verify_idx._index():
        return gate_source_object(routine, symbols)
    object_symbol = routine.symbol if routine.index_name else None
    rc, out = verify_idx.check(str(EU / routine.source), name, symbols[routine.symbol][2] == "thumb",
                               object_name=object_symbol)
    if rc != 0:
        raise AssertionError("rebuild differs: " + out.strip().splitlines()[-1])
    return out.strip().splitlines()[-1].replace(">>> ", "").replace(" <<<", "")


def _branch_target(word: int, address: int) -> int:
    offset = word & 0xFFFFFF
    offset -= (1 << 24) if offset >> 23 else 0
    return (address + 8 + offset * 4) & 0xFFFFFFFF


def gate_source_object(routine: Routine, symbols: dict) -> str:
    """Build the stub and compare its symbol's bytes with the ROM range.

    Branch relocations are resolved against symbols.txt: the ROM's branch at
    that offset must reach the relocated symbol plus the encoded addend. Any
    other relocation kind is refused."""
    import match
    from elftools.elf.elffile import ELFFile
    start, size, mode = symbols[routine.symbol]
    obj = match.compile_c(str(EU / routine.source), mode == "thumb")
    rom = rom_memory(routine.module).bytes(start, size)
    resolved = []
    with open(obj, "rb") as fh:
        elf = ELFFile(fh)
        symtab = elf.get_section_by_name(".symtab")
        sym = next((s for s in symtab.iter_symbols() if s.name == routine.symbol), None)
        if sym is None:
            raise AssertionError("object has no symbol " + routine.symbol)
        section = elf.get_section(sym["st_shndx"])
        built = bytearray(section.data()[sym["st_value"]:sym["st_value"] + size])
        for rel in elf.iter_sections():
            if rel.header["sh_type"] not in ("SHT_REL", "SHT_RELA") or rel.header["sh_info"] != sym["st_shndx"]:
                continue
            for r in rel.iter_relocations():
                offset = r["r_offset"] - sym["st_value"]
                if not 0 <= offset < size:
                    continue
                target = symtab.get_symbol(r["r_info_sym"]).name
                if r["r_info_type"] not in (1, 28, 29) or target not in symbols:   # PC24, CALL, JUMP24
                    raise AssertionError("unsupported relocation at +0x%x against %s" % (offset, target))
                word = int.from_bytes(built[offset:offset + 4], "little")
                rom_word = int.from_bytes(rom[offset:offset + 4], "little")
                if rel.header["sh_type"] == "SHT_RELA":    # mwcc: addend in the entry, zero field
                    expected = (symbols[target][0] + r["r_addend"] + 8) & 0xFFFFFFFF
                else:                                       # GAS: addend encoded in the branch field
                    expected = _branch_target(word, symbols[target][0])
                if (word ^ rom_word) >> 24 or _branch_target(rom_word, start + offset) != expected:
                    raise AssertionError("branch at +0x%x does not reach %s in the ROM" % (offset, target))
                built[offset:offset + 4] = rom[offset:offset + 4]
                resolved.append("%s%+d" % (target, expected - symbols[target][0]))
    if bytes(built) != rom:
        raise AssertionError("rebuilt bytes differ from the ROM at 0x%08x" % start)
    return "MATCH %d bytes, %d relocs%s (object vs ROM image)" % (
        size, len(resolved), " -> " + ", ".join(resolved) if resolved else "")


def gate_inventory(routine: Routine, symbols: dict, mem: Memory) -> dict:
    from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs
    from capstone.arm import ARM_CC_AL
    start, size, mode = symbols[routine.symbol]
    size = routine.extent or size
    if mode == "thumb":
        return gate_inventory_thumb(routine, start, start + size, mem)
    if mode != "arm":
        raise AssertionError("inventory covers ARM and THUMB routines only")
    end = start + size
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.detail = True
    code, data = set(), set()
    for lo, hi in routine.data:
        data.update(range(lo, hi, 4))
    dead = set()
    for lo, hi in routine.unreachable:
        dead.update(range(lo, hi, 4))
    todo = [start]
    while todo:
        pc = todo.pop()
        while start <= pc < end and pc not in code and pc not in data:
            ins = next(md.disasm(mem.bytes(pc, 4), pc), None)
            if ins is None:
                raise AssertionError("undecodable word at 0x%08x" % pc)
            code.add(pc)
            text = ins.mnemonic + " " + ins.op_str
            pool = re.search(r"\[pc, #(-?0x[0-9a-f]+|-?\d+)\]", ins.op_str)
            if ins.mnemonic.startswith("ldr") and pool:
                data.add(pc + 8 + int(pool.group(1), 0))
            if re.match(r"(add|ldr)\w*\s+pc, pc", text):
                todo.append(pc + 4)      # computed jump: the following run is a table of targets
                todo.extend(range(pc + 8, end, 4))
            branch = re.match(r"b(l)?(\w{2})?\s+#(0x[0-9a-f]+)$", text)
            if branch and ins.mnemonic in ("b", "bl") or (branch and ins.mnemonic[:1] == "b" and ins.mnemonic not in ("bic", "bics")):
                target = int(branch.group(3), 16)
                if start <= target < end:
                    todo.append(target)
            if ins.mnemonic == "b" or (ins.mnemonic == "bx" and ins.op_str == "lr") \
                    or ("pc" in ins.op_str.split(",")[0] and ins.mnemonic in ("mov", "ldr", "sub", "add")) \
                    or (ins.mnemonic.startswith(("pop", "ldm")) and "pc" in ins.op_str and ins.cc in (0, ARM_CC_AL)):
                break
            pc += 4
    if dead & code:
        raise AssertionError("declared unreachable words are reachable")
    covered = code | data | dead
    gaps = [a for a in range(start, end, 4) if a not in covered]
    stray = [a for a in data if not start <= a < end]
    if gaps:
        raise AssertionError("uncovered words at " + ", ".join("0x%08x" % a for a in gaps[:6]))
    pool_words = len([a for a in data if start <= a < end])
    result = "0x%x bytes: %d reachable ARM instructions + %d literal/DATA words" % (size, len(code), pool_words)
    if dead:
        result += " + %d unreachable instruction words" % len(dead)
    return {"result": result + " tile 0x%08x-0x%08x" % (start, end),
            "instructions": len(code), "data_words": pool_words, "unreachable_words": len(dead),
            "external_literals": len(stray)}


def gate_inventory_thumb(routine: Routine, start: int, end: int, mem: Memory) -> dict:
    """THUMB inventory: 2-byte steps, BL/BLX pairs as one 4-byte instruction,
    `ldr rX, [pc, #imm]` literals at ((pc + 4) & ~3) + imm, one 4-byte word each."""
    from capstone import CS_ARCH_ARM, CS_MODE_THUMB, Cs
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
    code, data, dead = set(), set(), set()
    for lo, hi in routine.data:
        data.update(range(lo, hi, 2))
    for lo, hi in routine.unreachable:
        dead.update(range(lo, hi, 2))
    instructions, pool_words, stray = 0, set(), 0
    todo = [start]
    while todo:
        pc = todo.pop()
        while start <= pc < end and pc not in code and pc not in data:
            ins = next(md.disasm(mem.bytes(pc, 4 if pc + 4 <= end else 2), pc), None)
            if ins is None:
                raise AssertionError("undecodable halfword at 0x%08x" % pc)
            if pc + ins.size > end:
                raise AssertionError("instruction at 0x%08x runs past the routine" % pc)
            code.update(range(pc, pc + ins.size, 2))
            instructions += 1
            mnemonic, operands = ins.mnemonic, ins.op_str
            pool = re.match(r"r[0-7], \[pc, #(0x[0-9a-f]+|\d+)\]$", operands)
            if mnemonic == "ldr" and pool:
                literal = ((pc + 4) & ~3) + int(pool.group(1), 0)
                if start <= literal < end:
                    data.update((literal, literal + 2))
                    pool_words.add(literal)
                else:
                    stray += 1
            elif "pc" in operands and mnemonic not in ("push", "pop", "bx", "blx"):
                raise AssertionError("pc operand the inventory does not follow at 0x%08x: %s %s" % (pc, mnemonic, operands))
            branch = re.match(r"#(0x[0-9a-f]+)$", operands)
            if mnemonic in ("b", "beq", "bne", "bhs", "blo", "bmi", "bpl", "bvs", "bvc",
                            "bhi", "bls", "bge", "blt", "bgt", "ble", "bcs", "bcc") and branch:
                target = int(branch.group(1), 16)
                if start <= target < end:
                    todo.append(target)
                elif mnemonic != "b":
                    raise AssertionError("conditional branch out of the routine at 0x%08x" % pc)
            if mnemonic in ("b", "bx") or (mnemonic == "pop" and "pc" in operands):
                break
            pc += ins.size
    if dead & code:
        raise AssertionError("declared unreachable halfwords are reachable")
    covered = code | data | dead
    gaps = [a for a in range(start, end, 2) if a not in covered]
    if gaps:
        raise AssertionError("uncovered halfwords at " + ", ".join("0x%08x" % a for a in gaps[:6]))
    result = "0x%x bytes: %d reachable THUMB instructions + %d literal words" % (end - start, instructions, len(pool_words))
    if routine.data:
        result += " + %d DATA halfwords" % sum((hi - lo) // 2 for lo, hi in routine.data)
    if dead:
        result += " + %d unreachable halfwords" % len(dead)
    return {"result": result + " tile 0x%08x-0x%08x" % (start, end),
            "instructions": instructions, "data_words": len(pool_words), "unreachable_words": len(dead),
            "external_literals": stray}


def run_case(cpu: Cpu, entry: int, case: Case) -> str | None:
    if case.setup:
        case.setup(cpu.mem)
    cpu.r = [0] * 16
    cpu.n = cpu.z = cpu.c = cpu.v = 0
    try:
        cpu.call(entry, case.args, sp=STACK_TOP, limit=5_000_000)
    except ArmFault as fault:
        return "fault: %s" % fault
    for reg, value in case.regs.items():
        if cpu.r[reg] != value & 0xFFFFFFFF:
            return "r%d = 0x%08x, model 0x%08x" % (reg, cpu.r[reg], value & 0xFFFFFFFF)
    for flag, value in case.flags.items():
        if getattr(cpu, flag) != value:
            return "%s = %d, model %d" % (flag, getattr(cpu, flag), value)
    if case.check:
        return case.check(cpu)
    return None


def gate_semantics(routine: Routine, symbols: dict, mem: Memory) -> dict:
    entry = symbols[routine.symbol][0] | (symbols[routine.symbol][2] == "thumb")
    rng = random.Random(0x5D1B ^ int(hashlib.sha256(routine.symbol.encode()).hexdigest()[:8], 16))
    cpu = Cpu(mem)
    count = 0
    for case in routine.cases(rng):
        problem = run_case(cpu, entry, case)
        if problem:
            raise AssertionError("args %s %s: %s" % (tuple("0x%x" % (a & 0xFFFFFFFF) for a in case.args), case.label, problem))
        count += 1
    if count < 100:
        raise AssertionError("only %d cases; at least 100 are required" % count)
    return {"result": "%d cases agree with the ROM instructions" % count, "cases": count}


def gate_documentation(routine: Routine) -> dict:
    text = (EU / routine.doc).read_text(encoding="utf-8")
    section = re.search(r"^### `%s`\n(.*?)(?=^### |\Z)" % re.escape(routine.symbol), text, re.M | re.S)
    if not section:
        raise AssertionError("%s has no `### `%s`` section" % (routine.doc, routine.symbol))
    body = section.group(1)
    missing = [f for f in DOC_FIELDS if not re.search(r"^- \*\*%s:\*\* \S" % f, body, re.M)]
    if missing:
        raise AssertionError("documentation lacks " + ", ".join(missing))
    return {"result": "interface, behavior and hardware documented in " + routine.doc}


def registered() -> list[Routine]:
    sys.path.insert(0, str(FAMILIES.parent))
    out = []
    for path in sorted(FAMILIES.glob("*.py")):
        if path.stem.startswith("_"):
            continue
        out.extend(importlib.import_module("families." + path.stem).ROUTINES)
    return out


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("names", nargs="*")
    parser.add_argument("--check", action="store_true", help="verify without writing receipts")
    args = parser.parse_args()
    os.chdir(EU)                    # stubs include "src/..." headers relative to eu/, as the build does
    symbols = load_symbols()
    routines = [r for r in registered() if not args.names or r.symbol in args.names]
    receipts = json.loads(RECEIPTS.read_text(encoding="utf-8")) if RECEIPTS.is_file() else {"schema_version": 1, "receipts": {}}
    failed = 0
    for routine in routines:
        mem = rom_memory(routine.module)
        start, size, _ = symbols[routine.symbol]
        try:
            gates = {"source": {"result": gate_source(routine, symbols)},
                     "inventory": gate_inventory(routine, symbols, mem),
                     "semantics": gate_semantics(routine, symbols, mem),
                     "documentation": gate_documentation(routine)}
        except AssertionError as error:
            print("FAIL %-28s %s" % (routine.symbol, error))
            failed += 1
            continue
        print("OK   %-28s %s; %s" % (routine.symbol, gates["inventory"]["result"].split(":")[0], gates["semantics"]["result"]))
        receipts["receipts"][routine.symbol] = {
            "schema_version": 1, "kind": "sdk_library_routine", "symbol": routine.symbol,
            "source": "eu/" + routine.source, "source_sha256": sha256(EU / routine.source),
            "doc": "eu/" + routine.doc, "doc_sha256": sha256(EU / routine.doc),
            "start": "0x%08x" % start, "end": "0x%08x" % (start + size),
            "sha256": hashlib.sha256(rom_memory(routine.module).bytes(start, size)).hexdigest(), "gates": gates}
    if not args.check:
        RECEIPTS.write_text(json.dumps(receipts, indent=1, sort_keys=True) + "\n", encoding="utf-8", newline="\n")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
