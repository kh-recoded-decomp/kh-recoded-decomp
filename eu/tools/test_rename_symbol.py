"""Regression checks for C/C++ library scope and safe rename preflight."""
import contextlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

import rename_symbol


class RenameSymbolTest(unittest.TestCase):
    def setUp(self):
        base = Path(__file__).resolve().parents[1] / "build"
        base.mkdir(exist_ok=True)
        self.temp = tempfile.TemporaryDirectory(prefix="rename_test_", dir=base)
        self.root = Path(self.temp.name).resolve()
        assert self.root.is_relative_to(base.resolve())
        assert self.root.name.startswith("rename_test_")
        self.addCleanup(self.temp.cleanup)
        patch = mock.patch.object(rename_symbol, "ROOT", self.root)
        patch.start()
        self.addCleanup(patch.stop)

    def put(self, relative, text):
        p = self.root / relative
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text, encoding="utf-8", newline="\n")
        return p

    def rename(self):
        with mock.patch.object(sys, "argv", ["rename_symbol.py", "OldFunction", "NewFunction"]):
            with contextlib.redirect_stdout(io.StringIO()):
                rename_symbol.main()

    def snapshot(self):
        return {p.relative_to(self.root).as_posix(): p.read_bytes()
                for p in self.root.rglob("*") if p.is_file()}

    def test_library_definition_and_references_keep_other_regions_and_bom(self):
        self.put("libs/nitro/fs/calls/OldFunction.c", "int OldFunction(void) { return 0; }\n")
        caller = self.put("src/calls/Caller.c", "\ufeffextern int OldFunction(void);\nint Caller(void) { return OldFunction(); }\n")
        header = self.put("libs/nitro/fs/library.h", "int OldFunction(void);\nint OldFunctionSuffix(void);\n")
        config = self.put("config/arm9/delinks.txt", "libs/nitro/fs/calls/OldFunction.c:\n")
        external = self.put("shared_region/OldFunction.c", "int OldFunction(void) { return 1; }\n")
        doc = self.put("docs/history.md", "OldFunction is the previous symbol.\n")
        before_external, before_doc = external.read_bytes(), doc.read_bytes()
        self.rename()
        self.assertFalse((self.root / "libs/nitro/fs/calls/OldFunction.c").exists())
        self.assertIn("int NewFunction", (self.root / "libs/nitro/fs/calls/NewFunction.c").read_text(encoding="utf-8"))
        self.assertTrue(caller.read_bytes().startswith(b"\xef\xbb\xbf"))
        self.assertIn("return NewFunction();", caller.read_text(encoding="utf-8"))
        self.assertIn("int NewFunction(void);", header.read_text(encoding="utf-8"))
        self.assertIn("OldFunctionSuffix", header.read_text(encoding="utf-8"))
        self.assertIn("calls/NewFunction.c", config.read_text(encoding="utf-8"))
        self.assertEqual(external.read_bytes(), before_external)
        self.assertEqual(doc.read_bytes(), before_doc)

    def test_missing_definition_leaves_all_references_unchanged(self):
        self.put("src/calls/Caller.c", "void Caller(void) { OldFunction(); }\n")
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, "expected one defining source"):
            self.rename()
        self.assertEqual(self.snapshot(), before)

    def test_cpp_caller_and_header_follow_c_definition(self):
        self.put("src/calls/OldFunction.c", "void OldFunction(void) {}\n")
        caller = self.put("src/calls/Caller.cpp", 'extern "C" void OldFunction(void);\nvoid Caller() { OldFunction(); }\n')
        header = self.put("src/calls/api.hpp", 'extern "C" void OldFunction(void);\n')
        self.rename()
        self.assertIn("NewFunction();", caller.read_text(encoding="utf-8"))
        self.assertIn("NewFunction(void)", header.read_text(encoding="utf-8"))

    def test_cpp_definition_preserves_extension(self):
        self.put("src/calls/OldFunction.cpp", 'extern "C" void OldFunction(void) {}\n')
        config = self.put("config/arm9/delinks.txt", "src/calls/OldFunction.cpp:\n")
        self.rename()
        self.assertFalse((self.root / "src/calls/OldFunction.cpp").exists())
        self.assertIn("NewFunction(void)", (self.root / "src/calls/NewFunction.cpp").read_text(encoding="utf-8"))
        self.assertIn("NewFunction.cpp", config.read_text(encoding="utf-8"))

    def test_existing_direct_alias_to_same_symbol_is_preserved(self):
        self.put("src/calls/OldFunction.c", "int OldFunction(void) { return 1; }\n")
        caller = self.put("src/calls/Caller.c", "#define NewFunction OldFunction\n#include \"shared.c\"\n")
        self.rename()
        self.assertEqual(caller.read_text(encoding="utf-8"), "#define NewFunction NewFunction\n#include \"shared.c\"\n")
        self.assertTrue((self.root / "src/calls/NewFunction.c").exists())

    def test_alias_does_not_hide_another_use_of_new_name(self):
        self.put("src/calls/OldFunction.c", "int OldFunction(void) { return 1; }\n")
        self.put("src/calls/Caller.c", "extern int NewFunction(void);\n#define NewFunction OldFunction\n")
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, "new symbol already appears"):
            self.rename()
        self.assertEqual(self.snapshot(), before)

    def test_duplicate_c_and_cpp_definitions_leave_all_files_unchanged(self):
        self.put("src/calls/OldFunction.c", "void OldFunction(void) {}\n")
        self.put("libs/runtime/OldFunction.cpp", 'extern "C" void OldFunction(void) {}\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, "found 2"):
            self.rename()
        self.assertEqual(self.snapshot(), before)

    def test_duplicate_definitions_leave_all_files_unchanged(self):
        self.put("src/calls/OldFunction.c", "void OldFunction(void) {}\n")
        self.put("libs/nitro/fs/calls/OldFunction.c", "void OldFunction(void) {}\n")
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, "found 2"):
            self.rename()
        self.assertEqual(self.snapshot(), before)

    def test_late_library_collision_does_not_rewrite_earlier_source(self):
        self.put("src/calls/OldFunction.c", "void OldFunction(void) {}\n")
        self.put("src/calls/Caller.c", "void Caller(void) { OldFunction(); }\n")
        self.put("libs/nitro/fs/used.h", "void NewFunction(void);\n")
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, "new symbol already appears"):
            self.rename()
        self.assertEqual(self.snapshot(), before)

    def test_existing_destination_does_not_change_inputs(self):
        self.put("src/calls/OldFunction.c", "void OldFunction(void) {}\n")
        self.put("src/calls/NewFunction.c", "/* Reserved destination. */\n")
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, "destination already exists"):
            self.rename()
        self.assertEqual(self.snapshot(), before)


    def rename_batch(self, pairs):
        plan = self.root / 'reviewed_pairs.json'
        plan.write_text(json.dumps({'candidates': [{'old': a, 'new': b} for a, b in pairs]}))
        with mock.patch.object(sys, 'argv', ['rename_symbol.py', '--map-file', str(plan)]):
            with contextlib.redirect_stdout(io.StringIO()):
                rename_symbol.main()

    def test_batch_preserves_cross_references_cpp_extensions_and_region(self):
        self.put('src/calls/OldFunction.c', 'int OtherOld(void);\nint OldFunction(void) { return OtherOld(); }\n')
        self.put('libs/runtime/OtherOld.cpp', 'int OldFunction(void);\nint OtherOld() { return OldFunction(); }\n')
        caller = self.put('src/calls/Caller.c', '\ufeffint OldFunction(void);\nint OtherOld(void);\n')
        config = self.put('config/arm9/delinks.txt', 'src/calls/OldFunction.c:\nlibs/runtime/OtherOld.cpp:\n')
        external = self.put('shared_region/OldFunction.c', 'OldFunction OtherOld\n')
        self.rename_batch([('OldFunction', 'NewFunction'), ('OtherOld', 'OtherNew')])
        self.assertIn('return OtherNew();', (self.root / 'src/calls/NewFunction.c').read_text())
        self.assertIn('return NewFunction();', (self.root / 'libs/runtime/OtherNew.cpp').read_text())
        self.assertTrue(caller.read_bytes().startswith(b'\xef\xbb\xbf'))
        self.assertIn('OtherNew.cpp:', config.read_text())
        self.assertEqual(external.read_text(), 'OldFunction OtherOld\n')

    def test_batch_missing_second_definition_does_not_apply_first(self):
        self.put('src/calls/OldFunction.c', 'int OldFunction(void) { return 1; }\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'expected one defining source for Missing'):
            with contextlib.redirect_stdout(io.StringIO()):
                rename_symbol.rename_symbols([('OldFunction', 'NewFunction'), ('Missing', 'OtherNew')])
        self.assertEqual(self.snapshot(), before)

    def test_batch_late_collision_leaves_all_names_unchanged(self):
        self.put('src/calls/OldFunction.c', 'int OldFunction(void) { return 1; }\n')
        self.put('src/calls/OtherOld.c', 'int OtherOld(void) { return OldFunction(); }\n')
        self.put('libs/runtime/used.h', 'int OtherNew(void);\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'new symbol already appears'):
            rename_symbol.rename_symbols([('OldFunction', 'NewFunction'), ('OtherOld', 'OtherNew')])
        self.assertEqual(self.snapshot(), before)

    def test_batch_rejects_name_chains_before_writes(self):
        self.put('src/calls/OldFunction.c', 'void OldFunction(void) {}\n')
        self.put('src/calls/NewFunction.c', 'void NewFunction(void) {}\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'chains or cycles'):
            rename_symbol.rename_symbols([('OldFunction', 'NewFunction'), ('NewFunction', 'OtherNew')])
        self.assertEqual(self.snapshot(), before)

    def test_data_batch_keeps_aggregate_path_layout_and_other_regions(self):
        source = self.put('src/data/Tables.c', '\ufeffconst unsigned char oldTable[4] = {1,2,3,4};\nunsigned int oldHandle;\n')
        caller = self.put('src/calls/Caller.c', 'extern const unsigned char oldTable[];\nextern unsigned int oldHandle;\nint Caller(void) { return oldTable[oldHandle]; }\n')
        config = self.put('config/symbols.txt', 'oldTable kind:data addr:0x02000000\noldHandle kind:bss addr:0x02000004\n')
        other = self.put('shared_region/Tables.c', 'unsigned int oldHandle;\n')
        with contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldTable','gTable'),('oldHandle','gHandle')],
                                         definition_sources={'oldTable':'src/data/Tables.c','oldHandle':'src/data/Tables.c'})
        self.assertEqual(source.read_text(encoding='utf-8'), '\ufeffconst unsigned char gTable[4] = {1,2,3,4};\nunsigned int gHandle;\n')
        self.assertTrue(source.read_bytes().startswith(b'\xef\xbb\xbf'))
        self.assertEqual(list(source.parent.glob('*.c')), [source])
        self.assertIn('gTable[gHandle]', caller.read_text())
        self.assertIn('gHandle kind:bss addr:0x02000004', config.read_text())
        self.assertEqual(other.read_text(), 'unsigned int oldHandle;\n')

    def test_data_source_containing_only_extern_is_rejected_without_writes(self):
        self.put('src/data/Tables.c', '  extern unsigned int oldHandle;\n/* unsigned int oldHandle; */\nint Work(void) {\n    oldHandle = 1;\n    return oldHandle;\n}\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'expected one defining source'):
            rename_symbol.rename_symbols([('oldHandle','gHandle')], definition_sources={'oldHandle':'src/data/Tables.c'})
        self.assertEqual(self.snapshot(), before)

    def test_data_definition_must_match_the_reviewed_path(self):
        self.put('src/data/Actual.c', 'unsigned int oldHandle;\n')
        self.put('src/data/Wrong.c', 'extern unsigned int oldHandle;\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'does not match the reviewed source'):
            rename_symbol.rename_symbols([('oldHandle','gHandle')], definition_sources={'oldHandle':'src/data/Wrong.c'})
        self.assertEqual(self.snapshot(), before)

    def test_data_duplicate_definition_rejects_the_entire_batch(self):
        self.put('src/data/Actual.c', 'unsigned int oldHandle;\nconst int oldTable[2] = {1,2};\n')
        self.put('libs/data/Duplicate.c', 'unsigned int oldHandle;\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'found 2'):
            rename_symbol.rename_symbols([('oldTable','gTable'),('oldHandle','gHandle')],
                                         definition_sources={'oldTable':'src/data/Actual.c','oldHandle':'src/data/Actual.c'})
        self.assertEqual(self.snapshot(), before)

    def test_data_sources_cannot_escape_region_or_request_moves(self):
        self.put('shared_region/Tables.c', 'unsigned int oldHandle;\n')
        before = self.snapshot()
        for source, move in [('shared_region/Tables.c',False),('src/data/Tables.c',True)]:
            with self.assertRaises(SystemExit):
                rename_symbol.rename_symbols([('oldHandle','gHandle')], move_calls=move,
                                             definition_sources={'oldHandle':source})
        self.assertEqual(self.snapshot(), before)

    def test_data_cli_requires_explicit_sources(self):
        plan = self.put('plan.json', json.dumps({'candidates':[{'old':'oldHandle','new':'gHandle'}]}))
        before = self.snapshot()
        with mock.patch.object(sys,'argv',['rename_symbol.py','--map-file',str(plan),'--keep-source-paths']):
            with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit):
                rename_symbol.main()
        self.assertEqual(self.snapshot(), before)

    def test_data_assembly_reference_requires_review_before_any_write(self):
        self.put('src/data/Tables.c', 'unsigned int oldHandle;\n')
        self.put('libs/runtime/reference.s', '.word oldHandle\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit, 'assembly symbols need explicit'):
            rename_symbol.rename_symbols([('oldHandle','gHandle')], definition_sources={'oldHandle':'src/data/Tables.c'})
        self.assertEqual(self.snapshot(), before)

    def test_data_anonymous_packed_aggregate_keeps_opaque_tail(self):
        body = 'struct {\n    void *pointers[19];\n    unsigned char tail[17];\n} __attribute__((packed)) oldTable = {{0}, {0}};\n'
        source = self.put('src/data/Tables.c', body)
        with contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldTable','gHandlerStorage')],
                                         definition_sources={'oldTable':'src/data/Tables.c'})
        self.assertEqual(source.read_text(),body.replace('oldTable','gHandlerStorage'))

    def test_data_callback_array_preserves_signature_and_count(self):
        body = 'void (*const oldTable[8])(void) = {0};\n'
        source = self.put('src/data/Tables.c', body)
        with contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldTable','gPopupStateHandlers')],
                                         definition_sources={'oldTable':'src/data/Tables.c'})
        self.assertEqual(source.read_text(),body.replace('oldTable','gPopupStateHandlers'))
        self.assertFalse(rename_symbol.has_data_definition('typedef void (*oldTable[8])(void);','oldTable'))
        self.assertFalse(rename_symbol.has_data_definition('extern void (*oldTable[8])(void);','oldTable'))

    def test_data_shared_definition_gets_eu_alias_and_preserves_reference_region(self):
        shared = self.put('src/data/Shared.c', 'const int oldData[2] = {1,2};\n')
        wrapper = self.put('eu/src/data/Shared.c', '\ufeff#include "src/data/Shared.c"\n')
        caller = self.put('eu/src/calls/Caller.c', 'extern const int oldData[];\nint Caller(void) { return oldData[1]; }\n')
        with mock.patch.object(rename_symbol,'ROOT',self.root/'eu'), contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldData','gData')], definition_sources={'oldData':'src/data/Shared.c'})
        self.assertEqual(shared.read_text(), 'const int oldData[2] = {1,2};\n')
        self.assertEqual(wrapper.read_text(encoding='utf-8'), '\ufeff#define oldData gData\n#include "src/data/Shared.c"\n')
        self.assertIn('gData[1]',caller.read_text())

    def test_data_shared_alias_preserves_macro_left_side_and_include_path(self):
        shared = self.put('src/data/Shared.c','const int referenceData[2] = {1,2};\n')
        wrapper = self.put('eu/src/data/Shared.c','#define referenceData oldData\n#include "src/data/Shared.c"\n')
        with mock.patch.object(rename_symbol,'ROOT',self.root/'eu'), contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldData','gData')], definition_sources={'oldData':'src/data/Shared.c'})
        self.assertEqual(shared.read_text(),'const int referenceData[2] = {1,2};\n')
        self.assertEqual(wrapper.read_text(),'#define referenceData gData\n#include "src/data/Shared.c"\n')

    def test_anonymous_aggregate_extern_and_typedef_are_not_storage(self):
        for storage in ('extern', 'typedef'):
            with self.subTest(storage=storage):
                body = storage+' struct {\n int flag;\n struct { int lock; } work;\n} oldData;\n'
                self.assertFalse(rename_symbol.has_data_definition(body,'oldData'))

    def test_data_aggregate_extern_view_does_not_duplicate_canonical_owner(self):
        owner = self.put('src/data/Owner.c','unsigned int oldData;\n')
        view = self.put('src/calls/Caller.c','extern struct {\n int flag;\n} oldData;\n')
        with contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldData','gData')],
                                         definition_sources={'oldData':'src/data/Owner.c'})
        self.assertEqual(owner.read_text(),'unsigned int gData;\n')
        self.assertEqual(view.read_text(),'extern struct {\n int flag;\n} gData;\n')

    def test_data_aligned_definition_preserves_native_declarator(self):
        body = 'const CellGrid oldGrid __attribute__((aligned(4))) = {1,2,0,0};\n'
        source = self.put('src/data/Tables.c', body)
        self.put('src/calls/Caller.c', 'extern const CellGrid oldGrid __attribute__((aligned(4)));\n')
        with contextlib.redirect_stdout(io.StringIO()):
            rename_symbol.rename_symbols([('oldGrid','gGrid')],
                                         definition_sources={'oldGrid':'src/data/Tables.c'})
        self.assertEqual(source.read_text(),body.replace('oldGrid','gGrid'))

    def test_aligned_local_and_extern_declarations_are_not_definitions(self):
        for body in ('extern int oldGrid[4] __attribute__((aligned(0x20)));\n',
                     'void Work(void) {\n int oldGrid[4] __attribute__((aligned(4))) = {0};\n}\n'):
            self.assertFalse(rename_symbol.has_data_definition(body,'oldGrid'))

    def test_aligned_duplicate_rejects_without_writes(self):
        self.put('src/data/Actual.c','int oldGrid[4] __attribute__((aligned(4))) = {0};\n')
        self.put('libs/data/Duplicate.c','int oldGrid[4];\n')
        before = self.snapshot()
        with self.assertRaisesRegex(SystemExit,'found 2'):
            rename_symbol.rename_symbols([('oldGrid','gGrid')],
                                         definition_sources={'oldGrid':'src/data/Actual.c'})
        self.assertEqual(self.snapshot(),before)

if __name__ == "__main__":
    unittest.main()
