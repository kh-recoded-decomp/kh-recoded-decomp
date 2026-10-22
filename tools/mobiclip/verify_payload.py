#!/usr/bin/env python3
"""Verify the mnemonic source of a hand-written MobiClip block.

These blocks mix thousands of instructions with tables. A source passes only
when it writes all code as ARM mnemonics with one address label per
instruction, keeps raw bytes inside named DATA regions, spells dispatch entries
as symbolic relative words, assembles to the exact registered bytes, and keeps
them through a partial link with the project's linker. This is the first of
the gates in verify_mobiclip.py; the semantic gates live there.

    python tools/mobiclip/verify_payload.py <source.s> <policy-name>
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from datetime import datetime, timezone
from pathlib import Path


import region

ROOT = region.ROOT
POLICY = region.EU / "config/arm9/mobiclip_blocks.json"
MWLDARM = region.EU / "tools/mwccarm/2.0/sp2p4/mwldarm.exe"
LICENSE = region.EU / "tools/mwccarm/license.dat"

REFUSED = "refused"
DIFFERS = "differs"
MATCH = "match"

CODE_LABEL_RE = re.compile(r"^MobiClip_Code_([0-9A-Fa-f]{8}):$")
SYMBOLIC_WORD_RE = re.compile(
    r"^MobiClip_Code_[0-9A-Fa-f]{8}\s*-\s*\."
    r"(?:\s*\+\s*(?:0x[0-9A-Fa-f]+|[0-9]+))?$"
)
FORBIDDEN_RE = re.compile(r"^\s*\.(?:incbin|inst|insn|4byte|long|hword|short|fill|space|zero)\b", re.I)


def find_tool(name: str) -> str:
    configured = shutil.which(name)
    if configured:
        return configured
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        f"Arm GNU Toolchain arm-none-eabi/*/bin/{name}.exe"
    ))
    if not candidates:
        raise FileNotFoundError(f"{name} was not found")
    return str(candidates[0])


def _integer(value) -> int:
    return int(value, 0) if isinstance(value, str) else int(value)


def load_spec(name: str, policy_path: Path = POLICY) -> dict:
    """One entry of eu/config/arm9/mobiclip_blocks.json, with integer bounds."""
    policy = json.loads(Path(policy_path).read_text(encoding="utf-8"))
    for block in policy.get("blocks", []):
        if block.get("name") != name:
            continue
        if block.get("format") != "arm_mnemonic_payload_v1":
            raise ValueError(f"{name} is not registered as an ARM mnemonic block")
        spec = dict(block)
        spec["start"] = _integer(block["start"])
        spec["end"] = _integer(block["end"])
        spec["size"] = spec["end"] - spec["start"]
        spec["sections"] = [(sec, _integer(lo), _integer(hi)) for sec, lo, hi in block["sections"]]
        if spec["sections"][0][1] != spec["start"] or spec["sections"][-1][2] != spec["end"]:
            raise ValueError(f"{name}: sections do not span the block")
        for (_, _, hi), (_, lo, _) in zip(spec["sections"], spec["sections"][1:]):
            if hi != lo:
                raise ValueError(f"{name}: sections are not contiguous")
        return spec
    raise KeyError(f"no MobiClip block named {name}")


def _without_comment(line: str) -> str:
    return line.split("/*", 1)[0].strip()


def validate_source(text: str, spec: dict) -> dict:
    """Reject opaque encodings and prove the declared code/DATA accounting."""
    code_addresses = []
    instruction_count = 0
    data_bytes = 0
    mode = None
    awaiting_instruction = False
    seen_sections = []

    # block comments may span lines; blank them out but keep the line numbers
    text = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), text, flags=re.S)
    for line_number, original in enumerate(text.splitlines(), 1):
        line = _without_comment(original)
        if not line:
            continue
        if FORBIDDEN_RE.match(line):
            raise ValueError(f"forbidden opaque directive at line {line_number}: {line}")

        code_label = CODE_LABEL_RE.match(line)
        if code_label:
            if awaiting_instruction:
                raise ValueError(f"code label without an instruction before line {line_number}")
            code_addresses.append(int(code_label.group(1), 16))
            mode = "code"
            awaiting_instruction = True
            continue

        if line.endswith(":"):
            if awaiting_instruction:
                raise ValueError(f"code label without an instruction before line {line_number}")
            mode = "data"
            continue

        if line.startswith("."):
            directive, _, operand = line.partition(" ")
            directive = directive.lower()
            operand = operand.strip()
            if awaiting_instruction:
                raise ValueError(f"directive where an ARM mnemonic is required at line {line_number}")
            if directive in (".text", ".section"):
                section = "text" if directive == ".text" else operand.split(",")[0].lstrip(".")
                if directive == ".section" and not operand.startswith('.rodata,"a",%progbits'):
                    raise ValueError(f"unsupported section at line {line_number}: {operand}")
                expected = spec["sections"][len(seen_sections)][0] if len(seen_sections) < len(spec["sections"]) else None
                if section != expected:
                    raise ValueError(f"section .{section} at line {line_number}, expected .{expected}")
                seen_sections.append(section)
            elif directive == ".byte":
                if mode != "data":
                    raise ValueError(f"raw bytes outside a named DATA region at line {line_number}")
                values = [part.strip() for part in operand.split(",")]
                if not values or any(not value for value in values):
                    raise ValueError(f"empty .byte directive at line {line_number}")
                parsed = [_integer(value) for value in values]
                if any(value < 0 or value > 0xFF for value in parsed):
                    raise ValueError(f"non-byte value at line {line_number}")
                data_bytes += len(parsed)
            elif directive == ".word":
                if mode != "data":
                    raise ValueError(f"raw word outside a named DATA region at line {line_number}")
                if operand != "0" and not SYMBOLIC_WORD_RE.fullmatch(operand):
                    raise ValueError(
                        f"non-symbolic/non-reserved .word at line {line_number}: {operand}"
                    )
                data_bytes += 4
            elif directive not in {
                ".syntax", ".arch", ".arm", ".align", ".global", ".type", ".size"
            }:
                raise ValueError(f"unsupported directive at line {line_number}: {directive}")
            continue

        if not awaiting_instruction or mode != "code":
            raise ValueError(f"unexpected source text at line {line_number}: {line}")
        instruction_count += 1
        awaiting_instruction = False

    if awaiting_instruction:
        raise ValueError("final code label has no ARM mnemonic")
    if len(seen_sections) != len(spec["sections"]):
        raise ValueError("source does not emit every registered section")
    if len(code_addresses) != len(set(code_addresses)):
        raise ValueError("duplicate ARM instruction labels")
    if code_addresses != sorted(code_addresses):
        raise ValueError("ARM instruction labels are not in address order")
    if any(address < spec["start"] or address + 4 > spec["end"] or address % 4
           for address in code_addresses):
        raise ValueError("ARM instruction label outside/alignment mismatch")
    if instruction_count != _integer(spec["instruction_count"]):
        raise ValueError(
            f"instruction count {instruction_count} != {spec['instruction_count']}"
        )
    if data_bytes != _integer(spec["embedded_data_bytes"]):
        raise ValueError(f"embedded DATA bytes {data_bytes} != {spec['embedded_data_bytes']}")
    if instruction_count * 4 + data_bytes != spec["size"]:
        raise ValueError("code plus embedded DATA does not cover the payload exactly")
    return {"instruction_count": instruction_count, "embedded_data_bytes": data_bytes}


def extract_sections(object_path: Path, spec: dict) -> bytes:
    """The block's bytes: each registered section of the object, in order.

    The block symbol must start the first section and every registered section
    must be owned entirely by the block (no other code or data beside it)."""
    from elftools.elf.elffile import ELFFile

    with object_path.open("rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            raise ValueError("assembled object has no symbol table")
        first = elf.get_section_by_name("." + spec["sections"][0][0])
        if first is None:
            raise ValueError("first registered section is missing")
        owner = [s for s in symtab.iter_symbols() if s.name == spec["symbol"]]
        if (not owner or elf.get_section(owner[0]["st_shndx"]).name != first.name
                or owner[0]["st_value"] != first["sh_addr"]):
            raise ValueError(f"{spec['symbol']} does not start .{spec['sections'][0][0]}")
        out = b""
        for section, lo, hi in spec["sections"]:
            data = elf.get_section_by_name("." + section)
            if data is None or len(data.data()) != hi - lo:
                raise ValueError(f".{section} does not hold exactly {hi - lo:#x} bytes")
            out += data.data()
        return out


def assemble_and_link(source: Path, spec: dict) -> tuple[bytes, bytes, bytes]:
    """(bytes placed at the block's addresses, GAS object bytes, MWLD partial-link bytes).

    A block whose code calls across its two sections keeps those branches as
    relocations in the object, so the first value comes from placing every
    registered section at its address with GNU ld; the other two must agree
    with each other word for word (the project's linker keeps the bytes)."""
    with tempfile.TemporaryDirectory() as directory:
        directory = Path(directory)
        assembled = directory / "payload.o"
        placed = directory / "payload_placed.elf"
        linked = directory / "payload_mwld.o"
        subprocess.run([
            find_tool("arm-none-eabi-as"), "-mcpu=arm946e-s", "-meabi=gnu",
            "-o", str(assembled), str(source),
        ], check=True, capture_output=True)
        layout = []
        for section, lo, _ in spec["sections"]:
            layout += ["-Ttext=%#x" % lo] if section == "text" else ["--section-start=.%s=%#x" % (section, lo)]
        subprocess.run([
            find_tool("arm-none-eabi-ld"), "-e", spec["symbol"], *layout, "-o", str(placed), str(assembled),
        ], check=True, capture_output=True)
        at_address = extract_sections(placed, spec)
        first = extract_sections(assembled, spec)
        if not MWLDARM.is_file():
            raise FileNotFoundError(f"project linker was not found: {MWLDARM}")
        env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
        subprocess.run([
            str(MWLDARM), "-proc", "arm946e", "-nostdlib", "-nodead",
            "-partial", "-main", "", "-o", str(linked), str(assembled),
        ], check=True, capture_output=True, env=env)
        second = extract_sections(linked, spec)
        return at_address, first, second


def verify(source, name: str, policy_path: Path = POLICY):
    try:
        spec = load_spec(name, policy_path)
        source = Path(source)
        accounting = validate_source(source.read_text(encoding="ascii"), spec)
        assembled, unplaced, linked = assemble_and_link(source, spec)
    except (KeyError, ValueError, FileNotFoundError, UnicodeError) as exc:
        return REFUSED, str(exc), {}
    except subprocess.CalledProcessError as exc:
        output = (exc.stderr or exc.stdout or b"").decode(errors="replace").strip()
        return DIFFERS, f"assembler/linker failed: {output}", {}

    if len(assembled) != spec["size"]:
        return DIFFERS, f"size {len(assembled)} != {spec['size']}", {}
    digest = hashlib.sha256(assembled).hexdigest()
    if digest != spec["sha256"]:
        return DIFFERS, f"sha256 {digest} != {spec['sha256']}", {}
    if linked != unplaced:
        return DIFFERS, "project linker changed the assembled payload bytes", {}
    info = {
        "kind": "executable_payload",
        "name": name,
        "symbol": spec["symbol"],
        "module": spec["unit"],
        "sections": [[s, f"{lo:#010x}", f"{hi:#010x}"] for s, lo, hi in spec["sections"]],
        "start": spec["start"],
        "end": spec["end"],
        "size": spec["size"],
        "sha256": digest,
        **accounting,
    }
    return MATCH, (
        f"{name} {spec['size']} bytes, {accounting['instruction_count']} ARM instructions, "
        f"{accounting['embedded_data_bytes']} embedded DATA bytes, GAS+MWLD exact"
    ), info


def _repo_path(path: Path) -> str:
    try:
        return path.resolve().relative_to(ROOT).as_posix()
    except ValueError:
        return path.resolve().as_posix()


def main() -> None:
    args = [arg for arg in sys.argv[1:] if not arg.startswith("--")]
    if len(args) != 2:
        raise SystemExit(__doc__)
    source = Path(args[0])
    name = args[1]
    status, message, info = verify(source, name)
    if status == REFUSED:
        print(">>> REFUSED <<< " + message)
        raise SystemExit(2)
    if status == DIFFERS:
        print(">>> DIFIERE <<< " + message)
        raise SystemExit(1)
    print(">>> MATCH <<< " + message)

if __name__ == "__main__":
    main()
