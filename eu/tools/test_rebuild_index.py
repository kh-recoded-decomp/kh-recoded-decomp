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

    def test_explicit_refresh_changes_proven_names_without_replacing_bytes(self):
        self.assertEqual(self.run_tool("--write"), 0)
        original = json.loads(self.index.read_text())
        original["example"]["relocs"][0][1] = "old_target_name"
        original["example"]["annotation"] = "keep historical metadata"
        self.index.write_text(json.dumps(original))
        text = self.index.read_text()
        self.assertEqual(self.run_tool("--refresh-reloc-names"), 0)
        self.assertEqual(self.index.read_text(), text)
        self.assertEqual(self.run_tool("--write", "--refresh-reloc-names"), 0)
        result = json.loads(self.index.read_text())
        expected = dict(original["example"], relocs=[[0, "target"], [4, "0x02002006"]])
        self.assertEqual(result["example"], expected)
        self.assertEqual(result["example"]["hex"], original["example"]["hex"])

    def test_refresh_does_not_accept_unproven_zeroed_old_relocations(self):
        self.assertEqual(self.run_tool("--write"), 0)
        original = json.loads(self.index.read_text())
        original["example"]["relocs"][0][1] = "unknown_removed_name"
        original["example"]["hex"] = "00000000" + original["example"]["hex"][8:]
        self.index.write_text(json.dumps(original))
        self.assertEqual(self.run_tool("--write", "--refresh-reloc-names"), 0)
        self.assertEqual(json.loads(self.index.read_text()), original)

    def test_refresh_preserves_offset_count_and_order(self):
        self.assertEqual(self.run_tool("--write"), 0)
        original = json.loads(self.index.read_text())["example"]
        for relocs in [
            [[0, "old_target_name"], [0, "old_target_name"], [4, "0x02002006"]],
            [[4, "0x02002006"], [0, "old_target_name"]],
        ]:
            with self.subTest(relocs=relocs):
                entry = dict(original, relocs=relocs)
                self.index.write_text(json.dumps({"example": entry}))
                self.assertEqual(self.run_tool("--write", "--refresh-reloc-names"), 0)
                self.assertEqual(json.loads(self.index.read_text()), {"example": entry})

    def test_refresh_preserves_mode_module_and_size_disagreements(self):
        self.assertEqual(self.run_tool("--write"), 0)
        original = json.loads(self.index.read_text())
        for key, value in [("mode", "thumb"), ("module", "overlay(1)"), ("size", 12)]:
            with self.subTest(key=key):
                entry = dict(original["example"], **{key: value})
                entry["relocs"] = [[0, "old_target_name"], [4, "0x02002006"]]
                self.index.write_text(json.dumps({"example": entry}))
                self.assertEqual(self.run_tool("--write", "--refresh-reloc-names"), 0)
                self.assertEqual(json.loads(self.index.read_text()), {"example": entry})

    def test_wrong_addend_cannot_write_index(self):
        self.index.write_text("{}")
        (self.config / "relocs.txt").write_text(self.relocations.replace("add:0x6", "add:0x8"))
        for args in [("--write",), ("--write", "--refresh-reloc-names")]:
            with self.subTest(args=args), self.assertRaises(SystemExit):
                self.run_tool(*args)
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
        for args in [("--write",), ("--write", "--refresh-reloc-names")]:
            with self.subTest(args=args):
                self.assertEqual(self.run_tool(*args), 1)
                self.assertEqual(self.index.read_text(), text)


class NativeRefreshTests(unittest.TestCase):
    """Fixtures exercise only native ROM/config; no candidates or compilers."""

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.config = self.root / "config/arm9"
        self.config.mkdir(parents=True)
        self.binary = self.root / "dsd_extract/arm9/arm9.bin"
        self.binary.parent.mkdir(parents=True)
        # +0 internal BL to +0x14; +4 BLX to external ARM +0x20;
        # +8 Thumb callback pointer; +0xc existing DATA field pointer.
        self.native = bytes.fromhex(
            "00f008f8 00f00ce8 01200002 06300002 c046c046 00bdc046")
        self.binary.write_bytes(self.native + b"\0" * 12)
        self.symbols = (
            "example kind:function(thumb,size=0x18) addr:0x02001000\n"
            "local_return kind:label(thumb) addr:0x02001014 local\n"
            "external_arm kind:function(arm,size=0x4) addr:0x02001020\n"
            "callback kind:function(thumb,size=0x4) addr:0x02002000\n"
            "table kind:data(size=0x10) addr:0x02003000\n")
        (self.config / "symbols.txt").write_text(self.symbols)
        (self.config / "delinks.txt").write_text(
            ".text start:0x02001000 end:0x02001024\n")
        # The native config has already had the intraprocedural BL removed.
        # Its two additions must be decoded by the existing builder first.
        self.relocations = (
            "from:0x02001004 kind:thumb_call_arm to:0x02001020 module:main\n"
            "from:0x02001008 kind:load to:0x02002000 module:main\n"
            "from:0x0200100c kind:load to:0x02003000 add:0x6 module:main\n")
        (self.config / "relocs.txt").write_text(self.relocations)
        self.index = self.root / "build/func_index.json"
        self.index.parent.mkdir()
        self.original = {
            "example": {"hex": self.native.hex(), "size": 24, "mode": "thumb",
                        "module": "main", "relocs": [[0, "local_return"],
                                                        [12, "historic_data_name"]],
                        "annotation": {"keep": ["all", "historical", "fields"]}},
            "not_configured": {"hex": "00", "relocs": [], "private": [1, 2]},
        }
        self.store(self.original)
        self.enterContext(patch.object(rebuild, "ROOT", str(self.root)))
        self.enterContext(patch.object(rebuild, "INDEX_PATH", str(self.index)))

    def store(self, index):
        self.index.write_text(json.dumps(index, indent=2))

    def read(self):
        return json.loads(self.index.read_text())

    def run_tool(self, *args):
        output = io.StringIO()
        with contextlib.redirect_stdout(output), contextlib.redirect_stderr(output):
            code = rebuild.main(list(args))
        self.last_output = output.getvalue()
        return code

    def refresh(self, *args):
        return self.run_tool("--write", "--refresh-native-relocs", "example", *args)

    def assert_refusal_preserves_file(self, *args):
        before = self.index.read_bytes()
        self.assertNotEqual(self.run_tool(*args), 0)
        self.assertEqual(self.index.read_bytes(), before)

    def test_additions_and_internal_drop_preserve_every_other_field(self):
        self.assertEqual(self.refresh(), 0)
        result = self.read()
        expected = dict(self.original["example"], relocs=[
            [4, "external_arm"], [8, "callback"], [12, "historic_data_name"]])
        self.assertEqual(result["example"], expected)
        self.assertEqual(result["not_configured"], self.original["not_configured"])
        # Native refresh does not opportunistically add missing unselected code.
        self.assertEqual(set(result), set(self.original))
        self.assertEqual(self.refresh(), 0)
        self.assertEqual(self.read(), result)

    def test_dry_run_does_not_write_contents_or_mtime(self):
        before, mtime = self.index.read_bytes(), self.index.stat().st_mtime_ns
        self.assertEqual(self.run_tool("--refresh-native-relocs", "example"), 0)
        self.assertEqual(self.index.read_bytes(), before)
        self.assertEqual(self.index.stat().st_mtime_ns, mtime)
        self.assertIn("+2 configured, -1 internal Thumb BL", self.last_output)

    def test_default_and_name_refresh_remain_conservative(self):
        for args in [(), ("--refresh-reloc-names",)]:
            self.store(self.original)
            before = self.index.read_bytes()
            self.assertEqual(self.run_tool(*args), 0)
            self.assertEqual(self.index.read_bytes(), before)
        for args in [("--write",), ("--write", "--refresh-reloc-names")]:
            self.store(self.original)
            self.assertEqual(self.run_tool(*args), 0)
            self.assertEqual(self.read()["example"], self.original["example"])

    def test_cli_requires_names_and_rejects_mixed_refresh_modes(self):
        for args in [("--refresh-native-relocs",),
                     ("--refresh-reloc-names", "--refresh-native-relocs", "example")]:
            with self.subTest(args=args):
                before = self.index.read_bytes()
                with self.assertRaises(SystemExit):
                    self.run_tool(*args)
                self.assertEqual(self.index.read_bytes(), before)

    def test_unknown_or_duplicate_selection_fails_without_write(self):
        for names in [("unknown",), ("external_arm",),
                      ("example", "unknown"), ("example", "example")]:
            with self.subTest(names=names):
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", *names)

    def test_exact_unmasked_byte_identity_is_mandatory(self):
        for offset in (0, 8, 16):  # old relocation, new relocation, ordinary code
            with self.subTest(offset=offset):
                old = json.loads(json.dumps(self.original))
                changed = bytearray(self.native)
                changed[offset] ^= 1
                old["example"]["hex"] = changed.hex()
                self.store(old)
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", "example")

    def test_exact_size_mode_and_module_are_mandatory(self):
        for key, value in [("size", 28), ("mode", "arm"), ("module", "ov001")]:
            with self.subTest(key=key):
                old = json.loads(json.dumps(self.original))
                old["example"][key] = value
                self.store(old)
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", "example")

    def test_zeroed_old_relocation_bytes_are_rejected(self):
        old = json.loads(json.dumps(self.original))
        old["example"]["hex"] = "00000000" + self.native[4:].hex()
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_changed_opcode_is_rejected_even_when_both_hex_strings_agree(self):
        changed = bytearray(self.native)
        # BL -> BLX: still a branch, but not an allowed intraprocedural Thumb BL.
        changed[3] = 0xe8
        self.binary.write_bytes(changed + b"\0" * 12)
        old = json.loads(json.dumps(self.original))
        old["example"]["hex"] = changed.hex()
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_external_thumb_bl_drop_is_rejected(self):
        changed = bytearray(self.native)
        changed[:4] = bytes.fromhex("00f012f8")  # target02001028, outside function
        self.binary.write_bytes(changed + b"\0" * 12)
        with (self.config / "symbols.txt").open("a") as stream:
            stream.write("outside kind:label(thumb) addr:0x02001028\n")
        old = json.loads(json.dumps(self.original))
        old["example"]["hex"] = changed.hex()
        old["example"]["relocs"][0][1] = "outside"
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_wrong_old_target_is_rejected(self):
        with (self.config / "symbols.txt").open("a") as stream:
            stream.write("other_label kind:label(thumb) addr:0x02001010\n")
        old = json.loads(json.dumps(self.original))
        old["example"]["relocs"][0][1] = "other_label"
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_unknown_old_target_is_not_accepted_from_byte_similarity(self):
        old = json.loads(json.dumps(self.original))
        old["example"]["relocs"][0][1] = "unknown_old_target"
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_same_address_old_target_in_wrong_bank_is_rejected(self):
        (self.config / "symbols.txt").write_text(
            self.symbols.replace("local_return kind:label", "actual_local kind:label"))
        foreign = self.config / "overlays/ov001"
        foreign.mkdir(parents=True)
        (foreign / "symbols.txt").write_text(
            "local_return kind:label(thumb) addr:0x02001014\n")
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_old_target_ambiguous_inside_its_bank_is_rejected(self):
        with (self.config / "symbols.txt").open("a") as stream:
            stream.write("local_return kind:label(thumb) addr:0x02001010\n")
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_historical_dropped_label_address_must_match_exactly(self):
        old = json.loads(json.dumps(self.original))
        old["example"]["relocs"][0][1] = "historical_02001014"
        self.store(old)
        self.assertEqual(self.refresh(), 0)
        old["example"]["relocs"][0][1] = "historical_02001010"
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_recursive_function_entry_cannot_be_relabelled_as_internal(self):
        changed = bytearray(self.native)
        changed[:4] = bytes.fromhex("fff7feff")  # BL to the current function start
        self.binary.write_bytes(changed + b"\0" * 12)
        with (self.config / "symbols.txt").open("a") as stream:
            stream.write("local_start kind:label(thumb) addr:0x02001000\n")
        old = json.loads(json.dumps(self.original))
        old["example"]["hex"] = changed.hex()
        old["example"]["relocs"][0][1] = "local_start"
        self.store(old)
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_local_target_must_have_current_thumb_label_metadata(self):
        for replacement in ["", "local_return kind:label(arm) addr:0x02001014\n"]:
            with self.subTest(replacement=replacement):
                (self.config / "symbols.txt").write_text(self.symbols.replace(
                    "local_return kind:label(thumb) addr:0x02001014 local\n", replacement))
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", "example")

    def test_real_function_entry_is_never_dropped_even_with_label_alias(self):
        for mode in ("arm", "thumb"):
            with self.subTest(mode=mode):
                (self.config / "symbols.txt").write_text(self.symbols +
                    "real_function kind:function(%s,size=0x4) addr:0x02001014\n" % mode)
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", "example")

    def test_unsized_real_function_entry_also_prevents_internal_drop(self):
        with (self.config / "symbols.txt").open("a") as stream:
            stream.write("unsized_function kind:function(thumb) addr:0x02001014\n")
        self.assert_refusal_preserves_file(
            "--write", "--refresh-native-relocs", "example")

    def test_unexplained_data_or_external_blx_drop_is_rejected(self):
        for offset, name, line in [
            (4, "external_arm", self.relocations.splitlines(keepends=True)[0]),
            (8, "callback", self.relocations.splitlines(keepends=True)[1]),
        ]:
            with self.subTest(offset=offset):
                old = json.loads(json.dumps(self.original))
                old["example"]["relocs"].insert(1, [offset, name])
                self.store(old)
                (self.config / "relocs.txt").write_text(self.relocations.replace(line, ""))
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", "example")

    def test_added_target_and_wrong_bank_thumb_pointer_must_pass_native_builder(self):
        mutations = [
            self.relocations.replace("to:0x02001020", "to:0x02001024"),
            self.relocations.replace("to:0x02002000 module:main",
                                     "to:0x02002000 module:overlay(1)"),
        ]
        for config in mutations:
            with self.subTest(config=config):
                (self.config / "relocs.txt").write_text(config)
                before = self.index.read_bytes()
                with self.assertRaises(SystemExit):
                    self.refresh()
                self.assertEqual(self.index.read_bytes(), before)

    def test_duplicate_or_reordered_old_offsets_are_not_normalized(self):
        for rows in [[[0, "local_return"], [0, "local_return"], [12, "historic_data_name"]],
                     [[12, "historic_data_name"], [0, "local_return"]]]:
            with self.subTest(rows=rows):
                old = json.loads(json.dumps(self.original))
                old["example"]["relocs"] = rows
                self.store(old)
                self.assert_refusal_preserves_file(
                    "--write", "--refresh-native-relocs", "example")

    def test_selected_proposal_precedes_original_five_disagreement_guard(self):
        for count in (5, 6):
            with self.subTest(unselected_disagreements=count):
                symbols = self.symbols
                old = json.loads(json.dumps(self.original))
                for number in range(count):
                    name = "unselected%d" % number
                    symbols += "%s kind:function(thumb,size=0x18) addr:0x02001000\n" % name
                    old[name] = {"hex": "00" * 24, "size": 24, "mode": "thumb",
                                 "module": "main", "relocs": []}
                (self.config / "symbols.txt").write_text(symbols)
                self.store(old)
                before = self.index.read_bytes()
                result = self.refresh()
                self.assertEqual(result, 0 if count == 5 else 1)
                self.assertIn("%d DISAGREE" % count, self.last_output)
                if count == 6:
                    self.assertEqual(self.index.read_bytes(), before)
                else:
                    after = self.read()
                    self.assertNotEqual(after["example"]["relocs"], old["example"]["relocs"])
                    for name in old.keys() - {"example"}:
                        self.assertEqual(after[name], old[name])


if __name__ == "__main__":
    unittest.main()
