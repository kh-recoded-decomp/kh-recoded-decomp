#!/usr/bin/env python3
"""Compile one source with mwccarm, or dispatch an explicit GCC/Clang selection.

Usage: _run_mwcc.py <out.o> <in.c> [--mode=arm|thumb] [--cc=default|<mwccarm dir>]

The environment variable (LM_LICENSE_FILE) is set here because ninja cannot
reliably do it through `cmd /c` when paths contain spaces.
"""
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from project import BUILD_DIR, CFLAGS, LICENSE, MWCC_DIR, MWCCARM, ROOT  # noqa: E402


# A wrapper whose EU names collide with US names in the shared source compiles
# them under temporary names and renames them in the object afterwards.
REDEFINE = re.compile(r"^// redefine-sym (\w+)=(\w+)\s*$", re.M)


def write_depfile(output, compiler_cwd=ROOT):
    """Normalize CodeWarrior's native Windows makefile for Ninja's GCC reader."""
    output = Path(output)
    native = output.with_suffix(".d")
    text = native.read_text(encoding="utf-8")
    _, separator, dependencies = text.partition(": ")
    if not separator:
        raise ValueError("invalid CodeWarrior dependency file: " + str(native))
    # Keep escaped spaces and line continuations, but normalize path separators.
    dependencies = re.sub(r"\\(?![ \t#\r\n])", "/", dependencies)
    dependencies = dependencies.replace("\\\n", " ")

    def escape(path):
        return str(path).replace("\\", "/").replace("$", "$$").replace("#", "\\#").replace(" ", "\\ ")

    paths = []
    for token in re.findall(r"(?:\\[ \t#]|[^\s])+", dependencies):
        value = token.replace("\\ ", " ").replace("\\\t", "\t").replace("\\#", "#")
        path = Path(value)
        # CodeWarrior can shorten even an absolute input relative to its cwd.
        # Wrappers run from the shared root; Ninja always runs from eu/.
        if not path.is_absolute() and not re.match(r"^[A-Za-z]:/", value):
            path = (Path(compiler_cwd) / path).resolve()
        paths.append(escape(path))
    Path(str(output) + ".d").write_text(escape(output) + ": " + " \\\n\t".join(paths) + "\n",
                                       encoding="utf-8", newline="\n")
    native.unlink()


def find_objcopy():
    import shutil
    configured = shutil.which("arm-none-eabi-objcopy")
    if configured:
        return configured
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        "Arm GNU Toolchain arm-none-eabi/*/bin/arm-none-eabi-objcopy.exe"))
    if not candidates:
        raise SystemExit("arm-none-eabi-objcopy was not found")
    return str(candidates[0])


def redefine_symbols(obj, pairs):
    args = [find_objcopy()]
    for old, new in pairs:
        args += ["--redefine-sym", "%s=%s" % (old, new)]
    subprocess.run(args + [str(obj)], check=True)


def load_json_retry(path, attempts=20):
    """Read a generated JSON sidecar across a concurrent write window."""
    for attempt in range(attempts):
        try:
            text = path.read_text(encoding="utf-8")
            if not text.strip():
                raise json.JSONDecodeError("empty sidecar", text, 0)
            return json.loads(text)
        except (OSError, json.JSONDecodeError):
            if attempt + 1 == attempts:
                raise
            time.sleep(0.05 * (attempt + 1))


def main():
    out_path = Path(sys.argv[1])
    src_path = Path(sys.argv[2])
    rel = src_path.resolve().relative_to(ROOT).as_posix()

    opt_mode = opt_cc = None
    for a in sys.argv[3:]:
        if a.startswith("--mode="):
            opt_mode = a[len("--mode="):]
        elif a.startswith("--cc="):
            opt_cc = a[len("--cc="):]
        elif a.startswith("--unit="):
            rel = a[len("--unit="):]

    # Without explicit options (a direct call) fall back to the sidecar maps
    # that gen_delinks.py / configure.py produce.
    extra = []
    if opt_mode is None:
        modes_path = BUILD_DIR / "file_modes.json"
        if modes_path.exists():
            opt_mode = load_json_retry(modes_path).get(rel, "arm")
    if opt_mode == "thumb":
        extra.append("-thumb")

    mwcc_bin = MWCCARM
    if opt_cc is None:
        comp_path = BUILD_DIR / "file_compilers.json"
        if comp_path.exists():
            opt_cc = load_json_retry(comp_path).get(rel)
    if opt_cc and opt_cc.startswith("gcc/"):
        from _run_gcc import compiler_command
        return subprocess.run(compiler_command(src_path, out_path, opt_mode or "arm", opt_cc)).returncode
    if opt_cc and opt_cc.startswith("clang/"):
        from _run_clang import compiler_command
        return subprocess.run(compiler_command(src_path, out_path, opt_mode or "arm", opt_cc)).returncode
    if opt_cc and opt_cc != "default":
        mwcc_bin = MWCC_DIR / opt_cc / "mwccarm.exe"

    flags = list(CFLAGS)
    # Wrappers around shared US sources build from the repo root with its headers.
    shared_root = ROOT.parent
    shared_include = re.search(r'#include "(src/[^"]+\.c)"', src_path.read_text(encoding="utf-8", errors="replace"))
    if shared_include is None:
        shared_include = re.search(
            r'#include "(src/[^"]+\.(?:cpp|cp|cc))"',
            src_path.read_text(encoding="utf-8", errors="replace"),
        )
    is_wrapper = bool(shared_include) and (shared_root / shared_include.group(1)).is_file()
    if is_wrapper:
        flags.extend(["-i", str(shared_root), "-i", str(shared_root / "include")])
    if opt_cc == "2.0/sp2p3":
        flags.extend(["-fp", "soft", "-ipa", "file"])
    if src_path.suffix.lower() in (".cpp", ".cp", ".cc"):
        flags[flags.index("c99")] = "c++"

    env = dict(os.environ, LM_LICENSE_FILE=str(LICENSE))
    # Absolute inputs keep dependencies unambiguous when wrappers compile from
    # the shared root rather than eu/. -gccdep writes beside the output object.
    out_arg, src_arg = str(out_path.resolve()), str(src_path.resolve())
    cmd = [str(mwcc_bin), "-c", *flags, *extra, "-gccdep", "-MD",
           "-o", out_arg, src_arg]

    # The FLEXlm license check fails intermittently under a parallel build: an
    # arbitrary translation unit dies and the same command succeeds on its own.
    # A real diagnostic fails every attempt and is reported as usual.
    for attempt in range(8):
        r = subprocess.run(cmd, env=env, capture_output=True, text=True,
                           cwd=str(shared_root) if is_wrapper else None)
        if r.returncode == 0:
            sys.stdout.write(r.stdout)
            sys.stderr.write(r.stderr)
            write_depfile(out_path, shared_root if is_wrapper else ROOT)
            renames = REDEFINE.findall(src_path.read_text(encoding="utf-8", errors="replace"))
            if renames:
                redefine_symbols(out_path, renames)
            # mwcc emits one section per global and orders them by its own rule;
            # put data sections back in address order so a source that owns a
            # data range lays it down where its delinks claim says.
            from reorder_data_sections import reorder
            reorder(out_path)
            from share_bss import share, wants_sharing
            if wants_sharing(src_path):
                share(out_path)
            # Finish metadata preparation before Ninja records the output time.
            # Doing this first at link time invalidates the dependency cache.
            from patch_align import patch_o
            patch_o(out_path)
            return 0
        time.sleep(0.25 * (attempt + 1))

    sys.stdout.write(r.stdout)
    sys.stderr.write(r.stderr)
    return r.returncode


if __name__ == "__main__":
    sys.exit(main())
