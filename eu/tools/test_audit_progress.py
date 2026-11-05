"""Keep register annotations distinct from assembly instructions in progress."""
import hashlib
from pathlib import Path
import tempfile
import unittest
from unittest import mock

import audit_progress
from audit_progress import contains_assembly


class RegisterBindingClassification(unittest.TestCase):
    def test_complete_register_declarations_are_c(self):
        for declaration in [
            'register u32 mask __asm("r1");',
            'register volatile u32 *bitmap __asm("r3");',
            'register unsigned int value __asm("r2");',
        ]:
            with self.subTest(declaration=declaration):
                self.assertFalse(contains_assembly(declaration))

    def test_c_without_annotations_is_unchanged(self):
        self.assertFalse(contains_assembly('void Clear(unsigned *value) { *value = 0; }'))

    def test_assembly_after_a_binding_is_still_detected(self):
        binding = 'register u32 value __asm("r2");'
        self.assertTrue(contains_assembly(binding + '\n__asm("nop");'))
        self.assertTrue(contains_assembly(binding + ' __asm("nop");'))

    def test_instruction_and_malformed_annotations_remain_assembly(self):
        for source in [
            '__asm("nop");',
            'asm void Routine(void) { bx lr }',
            'register u32 value __asm("r2\\nnop");',
            'register u32 value __asm("r16");',
            'register u32 value __asm("r2") = 0;',
        ]:
            with self.subTest(source=source):
                self.assertTrue(contains_assembly(source))


class LibraryReceiptFreshness(unittest.TestCase):
    def setUp(self):
        base = Path(__file__).resolve().parents[1] / 'build'
        base.mkdir(parents=True, exist_ok=True)
        self.temp = tempfile.TemporaryDirectory(prefix='receipt_test_', dir=base)
        root = Path(self.temp.name).resolve()
        assert root.is_relative_to(base.resolve())
        self.addCleanup(self.temp.cleanup)
        self.source = root / 'Entry.c'
        self.doc = root / 'sdk_os.md'
        self.source.write_bytes(b'original source\n')
        self.doc.write_bytes(b'original documentation\n')
        self.receipt = {'source': 'eu/Entry.c', 'source_sha256': hashlib.sha256(self.source.read_bytes()).hexdigest(),
                        'doc': 'eu/sdk_os.md', 'doc_sha256': hashlib.sha256(self.doc.read_bytes()).hexdigest()}
        patch = mock.patch.object(audit_progress, 'ROOT', root)
        patch.start()
        self.addCleanup(patch.stop)
        patch = mock.patch.object(audit_progress, 'library_receipts',
                                  return_value=[('library_receipts.json', 'Entry', self.receipt)])
        patch.start()
        self.addCleanup(patch.stop)

    def test_current_receipt_passes(self):
        audit_progress.check_library_receipts()
        self.assertEqual(audit_progress.verified_library_sources(), {'Entry.c'})

    def test_source_rename_alias_invalidates_receipt_without_refreshing_it(self):
        self.source.write_bytes(b'#define OldName NewName\noriginal source\n')
        original_digest = self.receipt['source_sha256']
        with self.assertRaisesRegex(SystemExit, 'library_receipts.json: Entry'):
            audit_progress.check_library_receipts()
        self.assertEqual(audit_progress.verified_library_sources(), set())
        self.assertEqual(self.receipt['source_sha256'], original_digest)

    def test_documentation_edit_also_invalidates_receipt(self):
        self.doc.write_bytes(b'changed documentation\n')
        with self.assertRaisesRegex(SystemExit, 'Entry'):
            audit_progress.check_library_receipts()


if __name__ == '__main__':
    unittest.main()
