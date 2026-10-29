"""Link a temporary ARM candidate image for instruction replay in behavior tests.

This resolves ordinary ELF relocations without changing compiler objects, ROM
references or production verification. It never grants matching progress.
"""
import collections
import os
from pathlib import Path
import struct
import tempfile

from project import BUILD_DIR, ROOT


def compile_image(source, name, target, compiler, index, addresses):
    import match
    from elftools.elf.elffile import ELFFile
    if index[target]['mode'] != 'arm':
        raise AssertionError('this replay linker only supports ARM-state functions')
    source = Path(source)
    entry_address = addresses[target]
    previous_compilers, previous_cwd = match._COMPILER_MAP, Path.cwd()
    try:
        os.chdir(ROOT)
        match._COMPILER_MAP = {source.relative_to(ROOT).as_posix(): compiler}
        with tempfile.TemporaryDirectory(prefix='arm-replay-', dir=BUILD_DIR) as directory:
            obj = Path(directory) / 'candidate.o'
            match.compile_c(str(source), out=str(obj))
            code, refs = match.text_relocs(str(obj), name)
            with obj.open('rb') as stream:
                elf = ELFFile(stream)
                section_index = match.func_section(elf, name)
                addends = {rel['r_offset']: rel['r_addend']
                           for section in elf.iter_sections()
                           if section['sh_type'] == 'SHT_RELA' and section['sh_info'] == section_index
                           for rel in section.iter_relocations()}
                # GCC/Clang keep the six switch destinations in their text section.
                local_targets = {}
                symbols = elf.get_section_by_name('.symtab')
                for section in elf.iter_sections():
                    if section['sh_type'] not in ('SHT_REL', 'SHT_RELA') or section['sh_info'] != section_index:
                        continue
                    for rel in section.iter_relocations():
                        symbol = symbols.get_symbol(rel['r_info_sym'])
                        if symbol['st_info']['type'] == 'STT_SECTION':
                            offset = rel['r_offset']
                            if rel['r_info_type'] != 2 or symbol['st_shndx'] != section_index:
                                raise AssertionError('unexpected local-section relocation')
                            relative = symbol['st_value'] + rel.entry.get(
                                'r_addend', int.from_bytes(code[offset:offset + 4], 'little'))
                            if relative % 4 or not 0 <= relative < len(code):
                                raise AssertionError('switch destination is outside the ARM function')
                            local_targets[offset] = entry_address + relative
            expected = collections.Counter(addresses[name] for _, name in
                                           index[target]['relocs'])
            destinations = collections.Counter(addresses[name] for offset, (name, _) in refs.items()
                                               if offset not in local_targets)
            same_symbols = destinations == expected if compiler.startswith('dsi/') else set(destinations) == set(expected)
            if not same_symbols:
                raise AssertionError('candidate referenced symbols differ from the ROM')
            linked = bytearray(code)
            for offset, (name, kind) in refs.items():
                if offset in local_targets:
                    linked[offset:offset + 4] = struct.pack('<I', local_targets[offset])
                    continue
                word = int.from_bytes(code[offset:offset + 4], 'little')
                if kind == 2:
                    address = addresses[name] + addends.get(offset, word)
                    linked[offset:offset + 4] = struct.pack('<I', address)
                    continue
                # MWCC uses RELA; GNU tools put the -8 pipeline addend in REL's instruction.
                embedded = ((word & 0xffffff) ^ 0x800000) - 0x800000
                addend = addends.get(offset, embedded << 2)
                if kind != 1 or addend != -8:
                    raise AssertionError('only ordinary ARM branch relocations are expected')
                displacement = addresses[name] - entry_address - offset - 8
                if displacement % 4 or not -(1 << 25) <= displacement < (1 << 25):
                    raise AssertionError('ARM branch target is unaligned or out of range')
                word = (word & 0xff000000) | ((displacement >> 2) & 0xffffff)
                linked[offset:offset + 4] = struct.pack('<I', word)
            return linked
    finally:
        match._COMPILER_MAP = previous_compilers
        os.chdir(previous_cwd)
