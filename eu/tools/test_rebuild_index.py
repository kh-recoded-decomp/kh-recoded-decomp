"""Regression checks for ROM-backed relocation reconstruction."""
import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

import rebuild_index as rebuild
from verify_idx import _symbol_address


class RelocationTests(unittest.TestCase):
    def setUp(self):
        rebuild.by_mod.clear()
        rebuild.symbol_addresses.clear()
        rebuild.thumb_targets.clear()

    def test_linked_branch_targets(self):
        # Both displacement signs, the ARM BLX H bit, and Thumb BLX alignment.
        cases = [
            (0xeb000002, 0x02001000, "arm_call", 0x02001010),
            (0x1bfffffc, 0x02001000, "arm_call", 0x02000ff8),
            (0xeafffffc, 0x02001000, "arm_branch", 0x02000ff8),
            (0xfb000000, 0x02001000, "arm_call_thumb", 0x0200100a),
            (0xfafffffc, 0x02001000, "arm_call_thumb", 0x02000ff8),
            (0xf806f000, 0x02001000, "thumb_call", 0x02001010),
            (0xfffaf7ff, 0x02001000, "thumb_call", 0x02000ff8),
            (0xe806f000, 0x02001002, "thumb_call_arm", 0x02001010),
            (0xeffaf7ff, 0x02001002, "thumb_call_arm", 0x02000ff8),
        ]
        for word, source, kind, target in cases:
            with self.subTest(kind=kind, word=hex(word)):
                self.assertEqual(rebuild.linked_target(word, source, kind), target)

    def test_wrong_opcode_and_target_fail(self):
        for kind in ("arm_call", "arm_branch", "arm_call_thumb", "thumb_call", "thumb_call_arm"):
            with self.subTest(kind=kind), self.assertRaises(ValueError):
                rebuild.linked_target(0, 0x02001000, kind)
        with self.assertRaises(ValueError):
            rebuild.check_linked_target(bytes.fromhex("020000eb"), 0,
                                        0x02001000, 0x02001014, "arm_call", "main")
        with self.assertRaises(ValueError):
            rebuild.check_linked_target(b"\0\0", 0, 0, 0, "load", "main")

    def test_thumb_pointer_bit_requires_a_thumb_function(self):
        blob = (0x02002001).to_bytes(4, "little")
        with self.assertRaises(ValueError):
            rebuild.check_linked_target(blob, 0, 0x02001000, 0x02002000, "load", "main")
        rebuild.thumb_targets.add(("main", 0x02002000))
        rebuild.check_linked_target(blob, 0, 0x02001000, 0x02002000, "load", "main")
        with self.assertRaises(ValueError):
            rebuild.check_linked_target(blob, 0, 0x02001000, 0x02002000, "load", "overlay(1)")

    def test_symbol_lookup_preserves_odd_data_and_overlay_identity(self):
        rebuild.by_mod.update({"overlay(1)": {0x02002000: "first"},
                               "overlay(2)": {0x02002000: "second"}})
        self.assertEqual(rebuild.sym_at(0x02002000, "overlay(2)"), "second")
        self.assertEqual(rebuild.sym_at(0x02002001, "overlay(1)"), "0x02002001")
        rebuild.thumb_targets.add(("overlay(1)", 0x02002000))
        self.assertEqual(rebuild.sym_at(0x02002001, "overlays(1,2)"), "first")
        rebuild.by_mod["overlay(1)"][0x02002001] = "odd_byte"
        self.assertEqual(rebuild.sym_at(0x02002001, "overlay(1)"), "odd_byte")

    def test_renamed_relocations_require_address_or_linked_byte_proof(self):
        rebuild.symbol_addresses["current"] = {0x02002000}
        old = {"hex": "00000000", "relocs": [[0, "func_02002000"]]}
        new = {"hex": "00200002", "relocs": [[0, "current"]]}
        self.assertTrue(rebuild.same_relocations(old, new))
        old["relocs"] = [[0, "removed_name"]]
        self.assertFalse(rebuild.same_relocations(old, new))
        old["hex"] = new["hex"]
        self.assertTrue(rebuild.same_relocations(old, new))
        old["hex"] = "04200002"
        self.assertFalse(rebuild.same_relocations(old, new))
        old["relocs"] = [[4, "current"]]
        self.assertFalse(rebuild.same_relocations(old, new))

    def test_numeric_targets_are_accepted_by_verifier(self):
        self.assertEqual(_symbol_address("0x0209ee66"), 0x0209ee66)
        self.assertIsNone(_symbol_address("0x0209ee66junk"))


class ReconstructionTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.config = self.root / "config/arm9"
        self.config.mkdir(parents=True)
        binary = self.root / "dsd_extract/arm9/arm9.bin"
        binary.parent.mkdir(parents=True)
        # BL 0x02001010 followed by a pointer into the middle of a data symbol.
        binary.write_bytes(bytes.fromhex("020000eb06200002"))
        (self.config / "symbols.txt").write_text(
            "example kind:function(arm,size=0x8) addr:0x02001000\n"
            "target kind:function(arm,size=0x4) addr:0x02001010\n"
            "table kind:data(size=0x10) addr:0x02002000\n")
        (self.config / "delinks.txt").write_text(".text start:0x02001000 end:0x02001008\n")
        self.relocations = (
            "from:0x02001000 kind:arm_call to:0x02001010 module:main\n"
            "from:0x02001004 kind:load to:0x02002000 add:0x6 module:main\n")
        (self.config / "relocs.txt").write_text(self.relocations)
        self.index = self.root / "build/func_index.json"
        self.index.parent.mkdir()
        self.enterContext(patch.object(rebuild, "ROOT", str(self.root)))
        self.enterContext(patch.object(rebuild, "INDEX_PATH", str(self.index)))

    def run_tool(self, *args):
        with contextlib.redirect_stdout(io.StringIO()):
            return rebuild.main(list(args))

    def test_rebuild_addend_and_repeat_merge(self):
        self.assertEqual(self.run_tool("--write"), 0)
        index = json.loads(self.index.read_text())
        self.assertEqual(index["example"]["relocs"], [[0, "target"], [4, "0x02002006"]])
        index["example"]["relocs"][0][1] = "old_target_name"
        self.index.write_text(json.dumps(index))
        self.assertEqual(self.run_tool("--write"), 0)
        self.assertEqual(json.loads(self.index.read_text()), index)

    def test_wrong_addend_cannot_write_index(self):
        self.index.write_text("{}")
        (self.config / "relocs.txt").write_text(self.relocations.replace("add:0x6", "add:0x8"))
        with self.assertRaises(SystemExit):
            self.run_tool("--write")
        self.assertEqual(self.index.read_text(), "{}")

    def test_unknown_relocation_syntax_is_not_silently_dropped(self):
        (self.config / "relocs.txt").write_text(self.relocations.replace("add:0x6", "offset:0x6"))
        with self.assertRaises(ValueError):
            self.run_tool("--write")
        self.assertFalse(self.index.exists())

    def test_cross_check_guard_preserves_existing_index(self):
        with (self.config / "symbols.txt").open("a") as stream:
            for number in range(6):
                stream.write("alias%d kind:function(arm,size=0x8) addr:0x02001000\n" % number)
        index = {"alias%d" % number: {"hex": "00" * 8, "size": 8,
                                     "relocs": [], "module": "main", "mode": "arm"}
                 for number in range(6)}
        text = json.dumps(index)
        self.index.write_text(text)
        self.assertEqual(self.run_tool("--write"), 1)
        self.assertEqual(self.index.read_text(), text)


if __name__ == "__main__":
    unittest.main()
