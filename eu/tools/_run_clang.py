#!/usr/bin/env python3
"""Compile explicitly selected original ARM routines implemented in C."""
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

from _run_gcc import find_compiler as find_gcc
from project import ROOT


COMPILER_ID = "clang/22.1.3"
PROFILES = {
    COMPILER_ID: (),
    COMPILER_ID + "/source-order": ("-mllvm", "-disable-post-ra"),
}


def find_compiler():
    configured = os.environ.get("ARM_NONE_EABI_CLANG")
    if configured:
        return configured
    found = shutil.which("clang")
    if found:
        return found
    candidates = sorted(Path("C:/Program Files/Microsoft Visual Studio").glob(
        "*/*/VC/Tools/Llvm/x64/bin/clang.exe"))
    if not candidates:
        raise SystemExit("Clang 22.1.3 was not found; set ARM_NONE_EABI_CLANG")
    return str(candidates[0])


def compiler_command(source, output, mode="arm", selected=COMPILER_ID, compiler=None):
    if selected not in PROFILES:
        raise SystemExit("unsupported Clang selection: " + selected)
    if mode not in ("arm", "thumb"):
        raise SystemExit("unsupported instruction mode: " + mode)
    compiler = compiler or find_compiler()
    version = subprocess.run([str(compiler), "--version"],
                             check=True, capture_output=True, text=True).stdout
    match = re.search(r"\bclang version (\S+)", version)
    if not match or match.group(1) != "22.1.3":
        raise SystemExit("expected Clang 22.1.3, found " + version.strip())
    # Use the existing GNU assembler to emit the branch relocations mwldarm
    # accepts. Clang's integrated assembler emits EABI R_ARM_CALL instead.
    gcc = find_gcc()
    gcc_version = subprocess.run([str(gcc), "-dumpfullversion"],
                                 check=True, capture_output=True, text=True).stdout.strip()
    if gcc_version != "12.2.1":
        raise SystemExit("expected Arm GNU Toolchain 12.2.1, found " + gcc_version)
    assembler_dir = Path(gcc).resolve().parent
    return [
        str(compiler), "--target=arm-none-eabi", "-c", "-O2", "-std=c99",
        "-mcpu=arm946e-s", "-m" + mode, "-mfloat-abi=soft", "-mabi=apcs-gnu",
        "-fno-integrated-as", "-B" + str(assembler_dir), "-Wa,-meabi=gnu",
        "-ffreestanding", "-fsigned-char", "-fno-short-enums", "-fno-common",
        "-fno-pic", "-fno-pie", "-fno-unwind-tables", "-fno-asynchronous-unwind-tables",
        # EHABI emits .ARM.exidx even for nounwind C functions. Select DWARF
        # with unwinding disabled so neither format adds runtime metadata.
        "-fno-exceptions", "-Xclang", "-exception-model=dwarf",
        "-I", str(ROOT), "-I", str(ROOT.parent / "include"),
        *PROFILES[selected],
        "-MD", "-MF", str(output) + ".d", "-MQ", str(output),
        "-o", str(output), str(source),
    ]


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("output")
    parser.add_argument("source")
    parser.add_argument("--mode", choices=("arm", "thumb"), default="arm")
    parser.add_argument("--cc", default=COMPILER_ID)
    args = parser.parse_args()
    Path(args.output).parent.mkdir(parents=True, exist_ok=True)
    rc = subprocess.run(compiler_command(args.source, args.output, args.mode, args.cc)).returncode
    if rc == 0:
        from patch_align import patch_o
        patch_o(Path(args.output))
    return rc


if __name__ == "__main__":
    sys.exit(main())
