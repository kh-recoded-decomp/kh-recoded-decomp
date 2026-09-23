"""ROM-free tests for the correctness-critical accounting and comparison code."""

import importlib.util
import json
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("khrecoded", ROOT / "tools" / "khrecoded.py")
kh = importlib.util.module_from_spec(spec)
spec.loader.exec_module(kh)


class ToolingTests(unittest.TestCase):
    def test_profile_identifies_one_exact_rom(self):
        p = json.loads((ROOT / "profiles" / "bk9e.json").read_text())
        self.assertEqual((p["game_code"], p["maker_code"], p["revision"]), ("BK9E", "GD", 0))
        self.assertEqual(len(p["rom_sha256"]), 64)
        self.assertEqual(p["header_restore_offsets"], [108, 109, 350, 351])

    def test_code_ranges_are_counted_as_union(self):
        self.assertEqual(kh.union_size([(100, 120), (110, 130), (130, 140)]), 40)
        self.assertEqual(kh.union_size([(20, 20), (30, 35)]), 5)

    def test_comparison_catches_distant_differences_and_size(self):
        with tempfile.TemporaryDirectory() as tmp:
            a, b = Path(tmp) / "a", Path(tmp) / "b"
            a.write_bytes(b"a" * 1_100_000 + b"z")
            b.write_bytes(b"b" + b"a" * 1_099_999 + b"x")
            self.assertEqual(kh.compare_files(a, b), (2, [0, 1_100_000]))
            b.write_bytes(b"a")
            self.assertEqual(kh.compare_files(a, b)[0], 1_100_000)

    def test_all_overlay_profiles_are_present(self):
        directories = {p.name for p in (ROOT / "config" / "bk9e" / "arm9" / "overlays").iterdir()
                       if p.is_dir()}
        self.assertEqual(directories, {f"ov{i:03}" for i in range(105)})


if __name__ == "__main__":
    unittest.main()
