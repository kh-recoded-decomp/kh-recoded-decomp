"""Compile reviewed C and resolve ARM ELF relocations without reading a ROM."""

from __future__ import annotations

import argparse
import functools
import hashlib
import io
import json
import os
import re
import struct
import subprocess
import urllib.request
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def compiler_config() -> dict:
    return json.loads((ROOT / "profiles/compilers.json").read_text(encoding="utf-8"))


def install() -> None:
    config = compiler_config()
    archive = ROOT / ".tools/mwccarm.zip"
    archive.parent.mkdir(parents=True, exist_ok=True)
    if not archive.exists():
        urllib.request.urlretrieve(config["archive_url"], archive)
    if digest(archive) != config["archive_sha256"]:
        raise RuntimeError("Compiler archive SHA-256 mismatch")
    dest = ROOT / ".tools/mwccarm"
    dest.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(archive) as z:
        for name in z.namelist():
            if not (dest / name).resolve().is_relative_to(dest.resolve()):
                raise RuntimeError("Unsafe path in compiler archive")
        z.extractall(dest)
    print("Pinned compiler variants installed under .tools/ (ignored by Git)")


INCLUDE_DIR = ROOT / "include"
# Compiler switches only; the byte comparison still decides ARM/Thumb state.
ALLOWED_PRAGMA = re.compile(
    r"#\s*pragma\s+(?:push|pop|(?:opt_[a-z_]+|optimize_for_size|explicit_zero_data|scheduling|"
    r"peephole|dont_inline|always_inline|thumb)\s+(?:on|off|reset)|optimization_level\s+\d|"
    r"inline_max_size\(\d+\)|pack\(\d*\)|unused\(\w+(?:,\s*\w+)*\))\s*$")


def validate_c_source(source: Path, seen: set[Path] | None = None, allow_asm: bool = False) -> None:
    """Reject assembly anywhere in a source or the project headers it includes.

    Verified original assembly (asm_matches.json) passes allow_asm and is never counted as C.
    """
    seen = set() if seen is None else seen
    if source in seen:
        return
    seen.add(source)
    text = source.read_text(encoding="utf-8")
    clean = re.sub(r"/\*.*?\*/|//[^\n]*", "", text, flags=re.S)
    if not allow_asm and re.search(r"\b(?:asm|__asm|__asm__|INCLUDE_ASM|INLINE_ASM)\b", clean):
        raise RuntimeError("Inline assembly cannot count as C progress")
    for line in re.findall(r"(?m)^\s*#\s*pragma\b.*$", clean):
        if not ALLOWED_PRAGMA.fullmatch(line.strip()):
            raise RuntimeError(f"Unsupported pragma: {line.strip()}")
    for line in re.findall(r"(?m)^\s*#\s*include\b.*$", clean):
        header = re.fullmatch(r'\s*#\s*include\s+"([A-Za-z0-9_./]+)"\s*', line)
        path = (INCLUDE_DIR / header.group(1)).resolve() if header else None
        if path is None or not path.is_relative_to(INCLUDE_DIR.resolve()) or not path.is_file():
            raise RuntimeError(f"Only project headers under include/ may be included: {line.strip()}")
        validate_c_source(path, seen, allow_asm)


def relocate_word(word: int, kind: int, symbol: int, addend: int, place: int) -> int:
    """ARMv5 RELA: R_ARM_ABS32, R_ARM_PC24, and R_ARM_THM_CALL.

    A symbol's low bit denotes Thumb state. No reference bytes participate.
    Unsupported instruction forms and out-of-range branches fail closed.
    """
    if kind == 2:
        return (symbol + addend) & 0xFFFFFFFF
    if kind == 1:
        if word & 0x0E000000 != 0x0A000000:
            raise RuntimeError("R_ARM_PC24 does not point at a branch")
        delta = (symbol & ~1) + addend - place
        if not -(1 << 25) <= delta < (1 << 25):
            raise RuntimeError("ARM branch exceeds its range")
        if symbol & 1:
            if word & 0xFF000000 != 0xEB000000 or delta & 1:
                raise RuntimeError("Unsupported ARM-to-Thumb branch")
            return 0xFA000000 | ((delta & 2) << 23) | ((delta >> 2) & 0xFFFFFF)
        if delta & 3:
            raise RuntimeError("ARM branch target is unaligned")
        return (word & 0xFF000000) | ((delta >> 2) & 0xFFFFFF)
    if kind == 10:
        first, second = word & 0xFFFF, word >> 16
        if first & 0xF800 != 0xF000 or second & 0xE800 != 0xE800:
            raise RuntimeError("R_ARM_THM_CALL does not point at BL/BLX")
        thumb = symbol & 1
        delta = (symbol & ~1) + addend - (place if thumb else place & ~3)
        if not -(1 << 22) <= delta < (1 << 22) or delta & (1 if thumb else 3):
            raise RuntimeError("Thumb branch target exceeds its range or is unaligned")
        first = 0xF000 | ((delta >> 12) & 0x7FF)
        second = (0xF800 if thumb else 0xE800) | ((delta >> 1) & 0x7FF)
        return first | (second << 16)
    raise RuntimeError(f"Unsupported ARM relocation type {kind}")


def link_function(obj: bytes, function_name: str, address: int, bindings: dict[str, int]) -> bytes:
    from elftools.elf.elffile import ELFFile

    elf = ELFFile(io.BytesIO(obj))
    if elf['e_machine'] != 'EM_ARM' or not elf.little_endian or elf.elfclass != 32:
        raise RuntimeError("Expected a 32-bit little-endian ARM object")
    symtab = elf.get_section_by_name(".symtab")
    symbols = symtab.get_symbol_by_name(function_name) if symtab else None
    symbols = [s for s in symbols or [] if s['st_info']['type'] == 'STT_FUNC']
    if len(symbols) != 1:
        raise RuntimeError(f"Expected one compiled definition of {function_name}")
    function = symbols[0]
    index = function['st_shndx']
    if not isinstance(index, int):
        raise RuntimeError("Function is not defined in an object section")
    section = elf.get_section(index)
    if section.name != '.text':
        raise RuntimeError("Function must reside in .text")
    start, size = function['st_value'] & ~1, function['st_size']
    result = bytearray(section.data()[start:start + size])
    if len(result) != size or not size:
        raise RuntimeError("Invalid compiled function size")
    mapping = sorted((s['st_value'] & ~1, s.name) for s in symtab.iter_symbols()
                     if s['st_shndx'] == index and s.name in ('$a', '$t', '$d'))
    used = set()
    for reloc_section in elf.iter_sections():
        if reloc_section['sh_type'] not in ('SHT_REL', 'SHT_RELA') or reloc_section['sh_info'] != index:
            continue
        if reloc_section['sh_type'] != 'SHT_RELA':
            raise RuntimeError("Only explicit-addend RELA relocations are supported")
        for relocation in reloc_section.iter_relocations():
            offset = relocation['r_offset'] - start
            if not 0 <= offset < len(result):
                continue  # belongs to another function in the same source file
            if offset > len(result) - 4:
                raise RuntimeError("Relocation lies outside the compiled function")
            symbol = symtab.get_symbol(relocation['r_info_sym'])
            if symbol['st_shndx'] == index:
                value = address + symbol['st_value'] - start
                # MWCC marks Thumb functions with $t even when st_value is even.
                if symbol['st_info']['type'] == 'STT_FUNC' and not symbol.name.startswith('$'):
                    marks = [name for offset, name in mapping if offset <= (symbol['st_value'] & ~1)]
                    if marks and marks[-1] == '$t':
                        value |= 1
            elif symbol.name in bindings and (symbol['st_shndx'] == 'SHN_UNDEF' or (
                    isinstance(symbol['st_shndx'], int) and symbol['st_info']['type'] == 'STT_FUNC')):
                # An inline helper emitted in its own section binds to the original copy like an external.
                value = bindings[symbol.name]
                used.add(symbol.name)
            else:
                raise RuntimeError(f"Unresolved symbol or unsupported data section: {symbol.name}")
            word = struct.unpack_from('<I', result, offset)[0]
            linked = relocate_word(word, relocation['r_info_type'], value,
                                   relocation['r_addend'], address + offset)
            struct.pack_into('<I', result, offset, linked)
    if set(bindings) != used:
        raise RuntimeError(f"Unused linker bindings: {sorted(set(bindings) - used)}")
    return bytes(result)


@functools.lru_cache(maxsize=None)
def executable_digest(executable: Path, mtime_ns: int) -> str:
    return digest(executable)


def compile_entry(entry: dict, address: int, output: Path) -> dict:
    """Compile, link at address into output; the object stays at output.with_suffix('.o')."""
    source = (ROOT / entry['source']).resolve()
    if not source.is_relative_to(ROOT / 'src') or source.suffix not in ('.c', '.cpp'):
        raise RuntimeError("C/C++ source must be inside src/")
    validate_c_source(source, allow_asm=entry.get('language') == 'asm')
    config = compiler_config()
    variant = config['variants'][entry['compiler']]
    executable = ROOT / variant['executable']
    if not executable.exists():
        raise RuntimeError("Compiler missing: run python tools/compile_match.py install")
    if executable_digest(executable, executable.stat().st_mtime_ns) != variant['sha256']:
        raise RuntimeError("Compiler executable SHA-256 mismatch")
    mode = entry['mode']
    if mode not in ('arm', 'thumb'):
        raise RuntimeError("Function mode must be arm or thumb")
    flags = list(config['flags']) + ['-i', str(INCLUDE_DIR)]
    if source.suffix == '.cpp':
        flags[flags.index('c99')] = 'c++'
    if mode == 'thumb':
        flags.append('-thumb')
    obj = output.with_suffix('.o')
    env = dict(os.environ, LM_LICENSE_FILE=str(ROOT / config['license']))
    command = [str(executable), *flags, '-o', str(obj), str(source)]
    compiled = subprocess.run(command, cwd=ROOT, env=env, capture_output=True, text=True)
    if compiled.returncode:
        raise RuntimeError(compiled.stdout + compiled.stderr)
    bindings = {name: int(value, 0) if isinstance(value, str) else value
                for name, value in entry.get('bindings', {}).items()}
    result = link_function(obj.read_bytes(), entry['source_symbol'], address, bindings)
    output.write_bytes(result)
    return {'compiler_sha256': variant['sha256'], 'source_sha256': digest(source),
            'object_sha256': digest(obj), 'linked_sha256': digest(output),
            'source_symbol': entry['source_symbol'], 'compiler': entry['compiler'], 'flags': flags}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['install'])
    parser.parse_args()
    install()
