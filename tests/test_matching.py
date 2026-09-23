"""ROM-free regression tests for ARMv5 relocation and honest match accounting."""

import sys
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import compile_match as cm
import khrecoded as kh


class RelocationTests(unittest.TestCase):
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
