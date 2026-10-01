"""ROM-free regression tests for ARMv5 relocation and honest match accounting."""

import sys
import json
import struct
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import compile_match as cm
import khrecoded as kh


class RelocationTests(unittest.TestCase):
    def test_local_thumb_calls_and_function_pointers_use_elf_mapping(self):
        # A tiny ARM ELF fixture, independent of the compiler and reference ROM.
        names = b'\0$t\0$d\0recursive\0pool\0'
        section_names = b'\0.text\0.symtab\0.strtab\0.rela.text\0.shstrtab\0'
        symbol = lambda name, value, size, info: struct.pack('<IIIBBH', name, value, size, info, 0, 1)
        symbols = (bytes(16) + symbol(1, 0, 0, 2) + symbol(4, 4, 0, 2)
                   + symbol(7, 0, 12, 0x12) + symbol(17, 8, 4, 1))
        relocations = b''.join(struct.pack('<IIi', offset, (index << 8) | kind, addend)
                               for offset, index, kind, addend in
                               [(0, 3, 10, -4), (4, 3, 2, 0), (8, 4, 2, 0)])
        parts = [struct.pack('<III', 0xFFFEF7FF, 0, 0), symbols, names,
                 relocations, section_names]
        body = bytearray(52)
        offsets = []
        for part in parts:
            body.extend(bytes((-len(body)) % 4))
            offsets.append(len(body))
            body.extend(part)
        body.extend(bytes((-len(body)) % 4))
        section_offset = len(body)
        body.extend(bytes(40))
        specs = [(1, 1, 6, 0, 0, 0), (7, 2, 0, 3, 3, 16),
                 (15, 3, 0, 0, 0, 0), (23, 4, 0, 2, 1, 12),
                 (34, 3, 0, 0, 0, 0)]
        for offset, part, (name, kind, flags, link, info, entsize) in zip(offsets, parts, specs):
            body.extend(struct.pack('<IIIIIIIIII', name, kind, flags, 0, offset,
                                    len(part), link, info, 4, entsize))
        ident = b'\x7fELF\x01\x01\x01' + bytes(9)
        body[:52] = struct.pack('<16sHHIIIIIHHHHHH', ident, 1, 40, 1, 0, 0,
                               section_offset, 0, 52, 0, 0, 40, 6, 5)
        linked = cm.link_function(bytes(body), 'recursive', 0x02000100, {})
        self.assertEqual(struct.unpack('<III', linked),
                         (0xFFFEF7FF, 0x02000101, 0x02000108))
        import days_port
        function = days_port.read_functions(bytes(body))[0]
        self.assertEqual([r[5] for r in function['relocs']], [1, 1, 8])
        self.assertEqual(days_port.try_candidate(function,
                         {'address': 0x02000100, 'bytes': linked}), ({}, 'ok'))

    def test_arm_calls_and_interworking(self):
        self.assertEqual(cm.relocate_word(0xEBFFFFFE, 1, 0x02000200, -8, 0x02000100), 0xEB00003E)
        self.assertEqual(cm.relocate_word(0xEBFFFFFE, 1, 0x02000203, -8, 0x02000100), 0xFB00003E)
        self.assertEqual(cm.relocate_word(0xEBFFFFFE, 1, 0x02000100, -8, 0x02000200), 0xEBFFFFBE)

    def test_thumb_calls_and_aligned_blx_pc(self):
        self.assertEqual(cm.relocate_word(0xFFFEF7FF, 10, 0x02000201, -4, 0x02000102), 0xF87DF000)
        self.assertEqual(cm.relocate_word(0xFFFEF7FF, 10, 0x02000200, -4, 0x02000102), 0xE87EF000)

    def test_literal_addresses_keep_thumb_bit(self):
        self.assertEqual(cm.relocate_word(0, 2, 0x02000301, 16, 0x02000100), 0x02000311)

    def test_invalid_relocations_fail_closed(self):
        for arguments in [(0, 1, 0x200, -8, 0x100), (0, 10, 0x201, -4, 0x100),
                          (0xEBFFFFFE, 1, 0x10000000, -8, 0x100),
                          (0xEBFFFFFE, 1, 0x202, -8, 0x100), (0, 99, 0, 0, 0)]:
            with self.subTest(arguments=arguments), self.assertRaises(RuntimeError):
                cm.relocate_word(*arguments)

    def test_inline_assembly_cannot_be_counted_as_c(self):
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / 'function.c'
            for code in ['asm void f() {}', '__asm__("mov r0, r0");', '#include "dump.h"']:
                source.write_text(code)
                with self.assertRaises(RuntimeError):
                    cm.validate_c_source(source)
            source.write_text('/* asm is forbidden */ int f(void) { return 1; }')
            cm.validate_c_source(source)

    def test_only_project_headers_and_optimizer_pragmas_are_allowed(self):
        with tempfile.TemporaryDirectory() as tmp:
            source = Path(tmp) / 'function.c'
            source.write_text('#include "nitro/types.h"\n#pragma opt_propagation off\nu32 f(void) { return 1; }')
            cm.validate_c_source(source)
            for code in ['#include "../tools/khrecoded.py"', '#include <stdio.h>', '#pragma section ".data"']:
                source.write_text(code)
                with self.assertRaises(RuntimeError):
                    cm.validate_c_source(source)


class AccountingTests(unittest.TestCase):
    def test_mismatch_truncation_overlap_and_duplicate_are_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'src').mkdir()
            (root / 'build').mkdir()
            (root / 'src/example.c').write_text('int f(void) { return 1; }')
            reference = root / 'reference.bin'
            reference.write_bytes(bytes.fromhex('0100a0e31eff2fe1'))
            inv = {'arm9': {'binary': reference, 'base': 0x2000000, 'binary_bytes': 8,
                            'symbols': {'f': {'address': 0x2000000, 'size': 8},
                                        'alias': {'address': 0x2000000, 'size': 8}}}}
            entry = dict(module='arm9', symbol='f', language='c', source='src/example.c',
                         name='Example', behavior='Example', evidence='Fixture', uncertainty='None',
                         domain='test', origin='test', understanding='unknown')
            def verify(entries, candidate):
                (root / 'matches.json').write_text(json.dumps({'version': 1, 'matches': entries}))
                def fake_compile(_entry, _address, output):
                    output.write_bytes(candidate)
                    return {}
                with patch.object(kh, 'ROOT', root), patch.object(cm, 'compile_entry', fake_compile):
                    return kh.verify_matches(inv)
            correct = reference.read_bytes()
            self.assertEqual(verify([entry], correct)['verified'][0]['bytes'], 8)
            for candidate in [correct[:-1], correct + b'\0', bytes([0]) + correct[1:]]:
                with self.assertRaisesRegex(RuntimeError, 'Byte mismatch'):
                    verify([entry], candidate)
            with self.assertRaisesRegex(RuntimeError, 'Duplicate'):
                verify([entry, entry], correct)
            with self.assertRaisesRegex(RuntimeError, 'Overlapping'):
                verify([entry, dict(entry, symbol='alias')], correct)
            with self.assertRaisesRegex(RuntimeError, 'Arbitrary build'):
                verify([dict(entry, build=[['copy-reference']])], correct)


if __name__ == '__main__':
    unittest.main()
