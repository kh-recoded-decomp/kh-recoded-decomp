"""Link a temporary Thumb candidate for instruction replay, without matching credit.

GNU ld handles GNU-format local data, jump tables and ARM/Thumb interworking.
MWCC's RELA Thumb calls are resolved directly in the private replay byte image;
GNU ld interprets their addend/state differently from the production MW linker.
External symbols must exactly match the caller's explicit address/state manifest.
Compiler objects and ROM references are never modified.
"""
import os
from pathlib import Path
import subprocess
import struct
import tempfile

from elftools.elf.elffile import ELFFile
from project import BUILD_DIR, ROOT


def compile_thumb_image(source, name, compiler, address, externs, thumb_functions=()):
    import match
    from _run_gcc import find_compiler

    source = Path(source)
    previous_compilers, previous_cwd = match._COMPILER_MAP, Path.cwd()
    try:
        if not set(thumb_functions) <= set(externs):
            raise AssertionError('unknown Thumb function in replay manifest')
        os.chdir(ROOT)
        match._COMPILER_MAP = {source.relative_to(ROOT).as_posix(): compiler}
        with tempfile.TemporaryDirectory(prefix='thumb-replay-', dir=BUILD_DIR) as directory:
            directory = Path(directory)
            obj, linked = directory / 'candidate.o', directory / 'candidate.elf'
            match.compile_c(str(source), thumb=True, out=str(obj))
            with obj.open('rb') as stream:
                elf = ELFFile(stream)
                symbols = elf.get_section_by_name('.symtab')
                undefined = {symbol.name for symbol in symbols.iter_symbols()
                             if symbol['st_shndx'] == 'SHN_UNDEF' and symbol.name}
                if undefined != set(externs):
                    raise AssertionError('candidate external symbols differ from replay manifest: ' +
                                         str(undefined ^ set(externs)))
                for section in elf.iter_sections():
                    if section['sh_type'] in ('SHT_REL', 'SHT_RELA'):
                        for relocation in section.iter_relocations():
                            if relocation['r_info_type'] not in (2, 10):
                                raise AssertionError('unexpected candidate relocation type')
                if compiler.startswith('dsi/'):
                    section_index = match.func_section(elf, name)
                    code = bytearray(elf.get_section(section_index).data())
                    for section in elf.iter_sections():
                        if section['sh_type'] not in ('SHT_REL', 'SHT_RELA'):
                            continue
                        if section['sh_info'] != section_index:
                            raise AssertionError('unexpected MWCC replay relocation section')
                        if section['sh_type'] != 'SHT_RELA':
                            raise AssertionError('MWCC replay expects explicit RELA addends')
                        for relocation in section.iter_relocations():
                            symbol = symbols.get_symbol(relocation['r_info_sym']).name
                            if symbol not in externs:
                                raise AssertionError('unexpected MWCC local relocation')
                            offset, kind = relocation['r_offset'], relocation['r_info_type']
                            if kind == 2:
                                struct.pack_into('<I', code, offset,
                                                 externs[symbol] + relocation['r_addend'])
                                continue
                            if kind != 10 or relocation['r_addend'] != -4:
                                raise AssertionError('expected ordinary MWCC Thumb call')
                            first, second = struct.unpack_from('<HH', code, offset)
                            if first != 0xf000 or second != 0xf800:
                                raise AssertionError('unexpected MWCC call placeholder')
                            thumb = symbol in thumb_functions
                            target = externs[symbol]
                            if bool(target & 1) != thumb:
                                raise AssertionError('call target state disagrees with manifest')
                            pc = address + offset + 4
                            displacement = (target & ~1) - (pc if thumb else pc & ~3)
                            if displacement % (2 if thumb else 4) or not -(1 << 22) <= displacement < (1 << 22):
                                raise AssertionError('Thumb call target is out of range or unaligned')
                            struct.pack_into('<HH', code, offset, 0xf000 | ((displacement >> 12) & 0x7ff),
                                             (0xf800 if thumb else 0xe800) | ((displacement >> 1) & 0x7ff))
                    return address | 1, [(address, bytes(code))]
            script = directory / 'replay.ld'
            script.write_text(
                'SECTIONS { . = %d; .text : { *(.text*) *(.rodata*) }\n'
                '/DISCARD/ : { *(.comment*) *(.ARM.attributes*) } }\n' % address, encoding='ascii')
            # A linker-script integer lacks the Thumb function type. GNU ld
            # would generate an ARM veneer even when that integer is odd.
            # This object contains only absolute symbol metadata, no instructions.
            manifest = directory / 'externs.s'
            lines = []
            for symbol, value in externs.items():
                lines.append('.global ' + symbol)
                if symbol in thumb_functions:
                    if not value & 1:
                        raise AssertionError('Thumb function address must carry its state bit')
                    lines += ['.type %s, %%function' % symbol,
                              '.thumb_set %s, %d' % (symbol, value)]
                else:
                    lines.append('.set %s, %d' % (symbol, value))
            manifest.write_text('\n'.join(lines) + '\n', encoding='ascii')
            tool_dir = Path(find_compiler()).parent
            suffix = '.exe' if os.name == 'nt' else ''
            manifest_obj = directory / 'externs.o'
            subprocess.run([str(tool_dir / ('arm-none-eabi-as' + suffix)), '-mcpu=arm946e-s', '-meabi=gnu',
                            '-o', str(manifest_obj), str(manifest)],
                           check=True, capture_output=True, text=True)
            result = subprocess.run(
                [str(tool_dir / ('arm-none-eabi-ld' + suffix)), '-T', str(script),
                 '-o', str(linked), str(obj), str(manifest_obj)], capture_output=True, text=True)
            if result.returncode:
                raise AssertionError('replay link failed: ' + result.stdout + result.stderr)
            with linked.open('rb') as stream:
                elf = ELFFile(stream)
                symbols = elf.get_section_by_name('.symtab')
                entry = symbols.get_symbol_by_name(name)[0]['st_value'] | 1
                for symbol, value in externs.items():
                    if symbols.get_symbol_by_name(symbol)[0]['st_value'] != value:
                        raise AssertionError('linker changed a replay manifest address')
                segments = []
                for section in elf.iter_sections():
                    if section['sh_flags'] & 2 and section['sh_size']:
                        if section.name != '.text':
                            raise AssertionError('unexpected allocated replay section: ' + section.name)
                        segments.append((section['sh_addr'], section.data()))
                if not any(start <= (entry & ~1) < start + len(data) for start, data in segments):
                    raise AssertionError('candidate entry is outside its linked image')
                return entry, segments
    finally:
        match._COMPILER_MAP = previous_compilers
        os.chdir(previous_cwd)
