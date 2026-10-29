"""Exercise real Ninja rebuilds after changing a transitive include.

No ROM is needed. Integration tests use the installed, pinned toolchains;
unavailable compilers are skipped.
"""
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time
import unittest

from _run_mwcc import write_depfile
from match import text_relocs
from project import BUILD_DIR, MWCC_DIR, ROOT


def ninja_path(path):
    return str(path).replace("\\", "/").replace("$", "$$").replace(" ", "$ ").replace(":", "$:")


class DependencyTests(unittest.TestCase):
    def setUp(self):
        BUILD_DIR.mkdir(exist_ok=True)
        temporary = tempfile.TemporaryDirectory(prefix="dependency test ", dir=BUILD_DIR)
        self.addCleanup(temporary.cleanup)
        self.directory = Path(temporary.name)

    def test_codewarrior_windows_paths_keep_escaped_spaces(self):
        output = self.directory / "probe.o"
        output.with_suffix(".d").write_text(
            "E:\\build\\probe.o: E:\\project\\ source\\probe.c \\\n"
            "\tE:\\project\\ source\\nested.h\n", encoding="utf-8")
        write_depfile(output)
        text = Path(str(output) + ".d").read_text()
        self.assertIn("E:/project\\ source/probe.c", text)
        self.assertIn("E:/project\\ source/nested.h", text)
        self.assertIn(" \\\n", text)
        self.assertFalse(output.with_suffix(".d").exists())

    def rebuild_after_include_change(self, driver, selected=None, wrapper=False, assembly=False):
        ninja = shutil.which("ninja")
        if ninja is None:
            self.skipTest("ninja is not installed")
        outer = self.directory / ("outer.inc" if assembly else "outer.h")
        inner = self.directory / ("nested.inc" if assembly else "nested.h")
        source = self.directory / ("probe.s" if assembly else "probe.c")
        output = self.directory / "probe.o"
        if assembly:
            outer.write_text('.include "' + inner.as_posix() + '"\n')
            inner.write_text('.equ DEPENDENCY_VALUE, 1\n')
            source.write_text('.include "' + outer.as_posix() + '"\n'
                              '.text\n.global probe\n.type probe,%function\n'
                              'probe:\n mov r0, #DEPENDENCY_VALUE\n bx lr\n')
        else:
            outer.write_text('#include "' + inner.as_posix() + '"\n')
            inner.write_text('#define DEPENDENCY_VALUE 1\n')
            source.write_text('#include "' + outer.as_posix() + '"\n'
                              'unsigned int probe(void) { return DEPENDENCY_VALUE; }\n' +
                              ('#include "src/arm9/spatial_queries/SweepWorldCollision_020364a0.c"\n'
                               if wrapper else ''))
        recipe = self.directory / "build.ninja"
        driver_path = ROOT / "tools" / driver
        command = ('"' + sys.executable.replace("\\", "/") + '" "' +
                   driver_path.as_posix() + '" $out $in')
        if selected is not None:
            command += " --mode=arm --cc=" + selected
        recipe.write_text("builddir = " + ninja_path(self.directory) + "\nrule compile\n  command = " + command +
                          "\n  depfile = $out.d\n  deps = gcc\n" +
                          "build " + ninja_path(output) + ": compile " + ninja_path(source) + "\n")

        def run(*arguments):
            result = subprocess.run([ninja, "-f", str(recipe), *arguments], cwd=ROOT,
                                    capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            return result.stdout

        run()
        # The linker repeats this metadata preparation. It must already be a
        # no-op so it cannot make Ninja's freshly recorded deps become stale.
        from patch_align import patch_o
        self.assertFalse(patch_o(output))
        before, _ = text_relocs(output, "probe")
        dependencies = run("-t", "deps", str(output)).replace("\\", "/")
        self.assertIn(outer.as_posix(), dependencies)
        self.assertIn(inner.as_posix(), dependencies)
        if wrapper:
            self.assertIn("src/arm9/spatial_queries/SweepWorldCollision_020364a0.c", dependencies)
        self.assertIn("no work to do", run())
        time.sleep(0.02)
        inner.write_text('.equ DEPENDENCY_VALUE, 7\n' if assembly else '#define DEPENDENCY_VALUE 7\n')
        self.assertNotIn("no work to do", run())
        after, _ = text_relocs(output, "probe")
        self.assertNotEqual(before, after)
        self.assertIn("no work to do", run())

    def test_codewarrior_and_shared_wrapper(self):
        tested = 0
        for selected in ("default", "dsi/1.1", "2.0/base", "2.0/sp2p3"):
            directory = "3.0_patch4" if selected == "default" else selected
            if not (MWCC_DIR / directory / "mwccarm.exe").is_file():
                continue
            for wrapper in (False, True):
                with self.subTest(compiler=selected, wrapper=wrapper):
                    self.rebuild_after_include_change("_run_mwcc.py", selected, wrapper=wrapper)
                    tested += 1
        if not tested:
            self.skipTest("CodeWarrior is not installed")

    def test_gcc(self):
        from _run_gcc import find_compiler
        try:
            find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        self.rebuild_after_include_change("_run_gcc.py", "gcc/12.2.1")

    def test_clang(self):
        from _run_clang import find_compiler
        try:
            find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        self.rebuild_after_include_change("_run_clang.py", "clang/22.1.3")

    def test_armcc(self):
        from _run_armcc import find_compiler
        try:
            find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        self.rebuild_after_include_change("_run_armcc.py", "armcc/5.06u7")

    def test_assembler(self):
        from _run_armasm import find_assembler
        try:
            find_assembler()
        except SystemExit as error:
            self.skipTest(str(error))
        self.rebuild_after_include_change("_run_armasm.py", assembly=True)


if __name__ == "__main__":
    unittest.main()
