"""Check Clang object compatibility with the ARM linker and verifier."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch
from elftools.elf.elffile import ELFFile

from _run_clang import COMPILER_ID, compiler_command
from match import text_relocs


class ClangObjectTests(unittest.TestCase):
    def compile(self, text, mode="arm", selected=COMPILER_ID):
        temporary = tempfile.TemporaryDirectory(prefix="recoded-clang-")
        self.addCleanup(temporary.cleanup)
        source = Path(temporary.name) / "probe.c"
        output = source.with_suffix(".o")
        source.write_text(text, encoding="utf-8")
        subprocess.run(compiler_command(source, output, mode, selected), check=True,
                       capture_output=True, text=True)
        with output.open("rb") as stream:
            elf = ELFFile(stream)
            self.assertFalse(any(section.name.startswith((".ARM.exidx", ".ARM.extab", ".eh_frame"))
                                 for section in elf.iter_sections()))
        return text_relocs(output, "probe")

    def test_cpsr_read_and_mask(self):
        code, relocations = self.compile(
            'unsigned int probe(void) { return __builtin_arm_rsr("cpsr") & 0x1f; }\n')
        self.assertEqual(code, bytes.fromhex("00000fe11f0000e21eff2fe1"))
        self.assertEqual(relocations, {})

    def test_arm_call_uses_mwld_compatible_relocation(self):
        _, relocations = self.compile(
            "extern unsigned int external(unsigned int);\n"
            "unsigned int probe(unsigned int value) { return external(value) + 1; }\n")
        self.assertEqual(list(relocations.values()), [("external", 1)])  # R_ARM_PC24

    def test_thumb_mode_is_forwarded(self):
        code, relocations = self.compile(
            "unsigned int probe(unsigned int value) { return value + 1; }\n", "thumb")
        self.assertEqual(code, bytes.fromhex("01307047"))
        self.assertEqual(relocations, {})

    def test_unverified_compiler_version_is_rejected(self):
        result = subprocess.CompletedProcess([], 0, stdout="clang version 23.0.0\n")
        with patch("_run_clang.subprocess.run", return_value=result):
            with self.assertRaisesRegex(SystemExit, "expected Clang 22.1.3"):
                compiler_command("source.c", "output.o", compiler="clang")

    def test_interrupt_write_precedes_result_mask(self):
        code, relocations = self.compile(
            'unsigned int probe(void) { unsigned int previous=__builtin_arm_rsr("cpsr"); '
            '__builtin_arm_wsr("cpsr_c", previous | 0x80); return previous & 0x80; }\n',
            selected=COMPILER_ID + "/source-order")
        self.assertEqual(code, bytes.fromhex("00000fe1801080e301f021e1800000e21eff2fe1"))
        self.assertEqual(relocations, {})


if __name__ == "__main__":
    unittest.main()
