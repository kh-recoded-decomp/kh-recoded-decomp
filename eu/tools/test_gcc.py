"""Check GNU object compatibility with the existing ARM linker and verifier."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from _run_gcc import compiler_command
from match import text_relocs


class GccObjectTests(unittest.TestCase):
    def compile(self, text, mode="arm"):
        temporary = tempfile.TemporaryDirectory(prefix="recoded-gcc-")
        self.addCleanup(temporary.cleanup)
        source = Path(temporary.name) / "probe.c"
        output = source.with_suffix(".o")
        source.write_text(text, encoding="utf-8")
        subprocess.run(compiler_command(source, output, mode), check=True,
                       capture_output=True, text=True)
        return text_relocs(output, "probe")

    def test_arm_call_uses_mwld_compatible_relocation(self):
        _, relocations = self.compile(
            "extern unsigned int external(unsigned int);\n"
            "unsigned int probe(unsigned int value) { return external(value) + 1; }\n")
        self.assertEqual(list(relocations.values()), [("external", 1)])  # R_ARM_PC24

    def test_zero_safe_clz_is_one_instruction_and_return(self):
        code, relocations = self.compile(
            "unsigned int probe(unsigned int value) "
            "{ return value ? __builtin_clz(value) : 32; }\n")
        self.assertEqual(code, bytes.fromhex("100f6fe11eff2fe1"))
        self.assertEqual(relocations, {})

    def test_thumb_mode_is_forwarded(self):
        code, relocations = self.compile(
            "unsigned int probe(unsigned int value) { return value + 1; }\n", "thumb")
        self.assertEqual(code, bytes.fromhex("01307047"))
        self.assertEqual(relocations, {})

    def test_unverified_compiler_version_is_rejected(self):
        result = subprocess.CompletedProcess([], 0, stdout="13.2.1\n")
        with patch("_run_gcc.subprocess.run", return_value=result):
            with self.assertRaisesRegex(SystemExit, "expected Arm GNU GCC 12.2.1"):
                compiler_command("source.c", "output.o", compiler="arm-none-eabi-gcc")


if __name__ == "__main__":
    unittest.main()
