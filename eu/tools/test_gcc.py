"""Check GNU object compatibility with the existing ARM linker and verifier."""
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from _run_gcc import COMPILER_ID, compiler_command
from match import text_relocs


class GccObjectTests(unittest.TestCase):
    def compile(self, text, mode="arm", selected=COMPILER_ID):
        temporary = tempfile.TemporaryDirectory(prefix="recoded-gcc-")
        self.addCleanup(temporary.cleanup)
        source = Path(temporary.name) / "probe.c"
        output = source.with_suffix(".o")
        source.write_text(text, encoding="utf-8")
        subprocess.run(compiler_command(source, output, mode, selected), check=True,
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

    def test_mpacbti_with_the_same_short_version_is_rejected(self):
        responses = [subprocess.CompletedProcess([], 0, stdout="12.2.1\n"),
                     subprocess.CompletedProcess([], 0, stdout=(
                         "arm-none-eabi-gcc (Arm GNU Toolchain 12.2.MPACBTI-Rel1) "
                         "12.2.1 20230214\n"))]
        with patch("_run_gcc.subprocess.run", side_effect=responses):
            with self.assertRaisesRegex(SystemExit, "12.2.Rel1"):
                compiler_command("source.c", "output.o", compiler="arm-none-eabi-gcc")

    def test_cp15_leaf_register_profiles(self):
        cases = [
            ("scratch-r0", "void probe(void) { __builtin_arm_mcr(15,0,0,7,10,4); }",
             "0000a0e39a0f07ee1eff2fe1"),
            ("scratch-r1", "void probe(unsigned int mask) { "
             "unsigned int regions=__builtin_arm_mrc(15,0,2,0,0); "
             "__builtin_arm_mcr(15,0,regions|mask,2,0,0); }",
             "101f12ee001081e1101f02ee1eff2fe1"),
            ("scratch-r2", "void probe(unsigned int mask, unsigned int flags) { "
             "unsigned int access=__builtin_arm_mrc(15,0,5,0,2); "
             "__builtin_arm_mcr(15,0,(access&~mask)|flags,5,0,2); }",
             "502f15ee0020c2e1012082e1502f05ee1eff2fe1"),
        ]
        for profile, source, expected in cases:
            with self.subTest(profile=profile):
                code, relocations = self.compile(source, selected=COMPILER_ID + "/" + profile)
                self.assertEqual(code, bytes.fromhex(expected))
                self.assertEqual(relocations, {})

    def test_countdown_preserves_subtraction_and_borrow_branch(self):
        code, relocations = self.compile(
            "void probe(unsigned int cycles) "
            "{ while (!__builtin_usub_overflow(cycles, 4u, &cycles)) {} }\n")
        self.assertEqual(code, bytes.fromhex("040050e2fdffff2a1eff2fe1"))
        self.assertEqual(relocations, {})

    def test_long_tail_call_preserves_argument_and_literal_relocation(self):
        code, relocations = self.compile(
            "extern void external(int value) __attribute__((long_call));\n"
            "void probe(int value) { external(value); }\n",
            selected=COMPILER_ID + "/scratch-r1")
        self.assertEqual(code, bytes.fromhex("00109fe511ff2fe100000000"))
        self.assertEqual(relocations, {8: ("external", 2)})  # R_ARM_ABS32

    def test_cache_loop_preserves_address_operands_and_signed_branch(self):
        code, relocations = self.compile(
            "void probe(unsigned int start, unsigned int size) { "
            "unsigned int end = size + start; unsigned int line = start & ~31u; "
            "do { __builtin_arm_mcr(15,0,line,7,6,1); line += 32; } "
            "while ((int)line < (int)end); }\n",
            selected=COMPILER_ID + "/operand-order")
        self.assertEqual(code, bytes.fromhex(
            "001081e01f00c0e3360f07ee200080e2010050e1fbffffba1eff2fe1"))
        self.assertEqual(relocations, {})


if __name__ == "__main__":
    unittest.main()
