"""Regression checks for C/C++ library scope and safe rename preflight."""
import contextlib
import io
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


if __name__ == "__main__":
    unittest.main()
