"""ROM-free conservation and adversarial ownership checks."""

import contextlib
import copy
import io
import json
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import khrecoded as kh
from organization import build_hierarchy, print_tree


def fixture():
    inv = {"ov001": {"code_bytes": 32, "code_ranges": [(0, 24), (20, 32)],
                     "symbols": {"a": {"address": 0, "size": 8},
                                 "b": {"address": 12, "size": 8},
                                 "c": {"address": 24, "size": 4}}},
           "arm7": {"code_bytes": None, "code_ranges": [], "symbols": {}}}
    catalog = {"version": 1, "systems": [{"id": "game", "name": "Game", "evidence": "Call chain",
               "modules": [{"module": "ov001", "subsections": [
                   {"id": "actor", "name": "Actors", "evidence": "Shared actor structure", "symbols": ["a", "b"]},
                   {"id": "empty", "name": "Empty", "evidence": "No assignment yet", "symbols": []}]},
                           {"module": "arm7", "subsections": []}]}]}
    matches = [{"module": "ov001", "symbol": "a", "bytes": 8, "language": "c", "name": "A", "source": "src/a.c"},
               {"module": "ov001", "symbol": "c", "bytes": 4, "language": "c", "name": "C", "source": "src/c.c"}]
    return inv, matches, catalog


class OrganizationTests(unittest.TestCase):
    def test_unmatched_functions_and_all_code_gaps_remain_in_denominator(self):
        result = build_hierarchy(*fixture())
        module = result["systems"][0]["modules"][0]
        actor, empty, unknown = module["subsections"]
        self.assertEqual((actor["matched_c_bytes"], actor["code_bytes"], actor["percent"]), (8, 16, 50))
        self.assertEqual((unknown["matched_c_bytes"], unknown["code_bytes"]), (4, 16))
        self.assertEqual(unknown["unattributed_code_bytes"], 12)
        self.assertEqual(unknown["unattributed_code_ranges"], [
            {"start": "0x00000008", "end": "0x0000000c"},
            {"start": "0x00000014", "end": "0x00000018"},
            {"start": "0x0000001c", "end": "0x00000020"}])
        self.assertEqual((result["matched_c_bytes"], result["code_bytes"], result["percent"]), (12, 32, 37.5))
        self.assertEqual(result["identified_functions"], 3)
        self.assertFalse(empty["complete"])
        self.assertIsNone(empty["percent"])
        self.assertFalse(result["complete"])
        self.assertEqual(result["unknown_code_modules"], 1)
        self.assertIsNone(result["systems"][0]["modules"][1]["code_bytes"])

    def test_reclassification_cannot_change_coverage(self):
        inv, matches, catalog = fixture()
        before = build_hierarchy(inv, matches, catalog)
        catalog["systems"][0]["modules"][0]["subsections"] = []
        after = build_hierarchy(inv, matches, catalog)
        for field in ("matched_c_bytes", "code_bytes", "percent", "identified_functions"):
            self.assertEqual(before[field], after[field])

    def test_unknown_denominator_is_counted_once_per_module(self):
        inv, matches, catalog = fixture()
        catalog["systems"][0]["modules"][1]["subsections"] = [
            {"id": "pending", "name": "Pending", "evidence": "No inventory yet", "symbols": []}]
        result = build_hierarchy(inv, matches, catalog)
        self.assertEqual(result["unknown_code_modules"], 1)
        self.assertFalse(result["complete"])

    def test_duplicate_or_unknown_ownership_is_rejected(self):
        for claim in (["a", "a"], ["missing"]):
            inv, matches, catalog = fixture()
            catalog["systems"][0]["modules"][0]["subsections"][1]["symbols"] = claim
            with self.subTest(claim=claim), self.assertRaisesRegex(RuntimeError, "ownership"):
                build_hierarchy(inv, matches, catalog)

    def test_inventory_overlaps_and_outside_code_cannot_inflate_progress(self):
        for address in (4, 31):
            inv, matches, catalog = fixture()
            inv["ov001"]["symbols"]["b"]["address"] = address
            with self.subTest(address=address), self.assertRaises(RuntimeError):
                build_hierarchy(inv, matches, catalog)

    def test_verified_records_cannot_be_forged_into_duplicates_or_wrong_sizes(self):
        inv, matches, catalog = fixture()
        for extra in (matches[0], dict(matches[0], symbol="z"), dict(matches[0], symbol="b", bytes=9)):
            with self.subTest(extra=extra), self.assertRaises(RuntimeError):
                build_hierarchy(inv, matches + [extra], catalog)

    def test_modules_cannot_be_omitted_or_owned_by_two_systems(self):
        inv, matches, catalog = fixture()
        duplicate = copy.deepcopy(catalog["systems"][0])
        duplicate["id"] = "duplicate"
        catalog["systems"].append(duplicate)
        with self.assertRaisesRegex(RuntimeError, "module"):
            build_hierarchy(inv, matches, catalog)
        catalog["systems"] = catalog["systems"][:1]
        catalog["systems"][0]["modules"].pop()
        with self.assertRaisesRegex(RuntimeError, "missing"):
            build_hierarchy(inv, matches, catalog)

    def test_filtered_function_view_shows_pending_and_rejects_typos(self):
        result = build_hierarchy(*fixture())
        with contextlib.redirect_stdout(io.StringIO()) as output:
            print_tree(result, module_id="ov001", subsection_id="actor", functions=True)
        self.assertIn("MATCH   a", output.getvalue())
        self.assertIn("pending b", output.getvalue())
        self.assertNotIn("src/c.c", output.getvalue())
        with contextlib.redirect_stdout(io.StringIO()), self.assertRaisesRegex(RuntimeError, "No organization"):
            print_tree(result, module_id="ov999")

    def test_committed_catalog_conserves_every_original_function_and_byte(self):
        # Parse public address/size metadata only; CI requires no ROM or compiler.
        base = ROOT / "config/bk9e/arm9"
        inv = {}
        for module in ["arm9", "itcm", "dtcm"] + [f"ov{i:03}" for i in range(105)]:
            directory = base / "overlays" / module if module.startswith("ov") else (
                base if module == "arm9" else base / module)
            symbols = {}
            for line in (directory / "symbols.txt").read_text().splitlines():
                m = kh.SYMBOL_RE.match(line)
                if m and int(m[2], 16):
                    symbols[m[1]] = {"address": int(m[3], 16), "size": int(m[2], 16)}
            ranges = [(int(a, 16), int(b, 16)) for a, b in kh.RANGE_RE.findall((directory / "delinks.txt").read_text())]
            inv[module] = {"code_bytes": kh.union_size(ranges), "code_ranges": ranges, "symbols": symbols}
        inv["arm7"] = {"code_bytes": None, "code_ranges": [], "symbols": {}}
        catalog = json.loads((ROOT / "config/bk9e/organization.json").read_text())
        result = build_hierarchy(inv, [], catalog)
        self.assertEqual(result["code_bytes"], 1_768_220)
        self.assertEqual(result["identified_functions"], 10_359)
        owners = set()
        for system in result["systems"]:
            for module in system["modules"]:
                for section in module["subsections"]:
                    for function in section["functions"]:
                        key = (module["module"], function["symbol"])
                        self.assertNotIn(key, owners)
                        owners.add(key)
        self.assertEqual(len(owners), 10_359)
        self.assertEqual(result["matched_c_bytes"], 0)


if __name__ == "__main__":
    unittest.main()
