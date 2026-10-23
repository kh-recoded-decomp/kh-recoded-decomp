#!/usr/bin/env python3
"""Compile explicitly selected original ARM routines implemented in C."""
import os
import shutil
import subprocess
import sys
from pathlib import Path

from project import ROOT


COMPILER_ID = "gcc/12.2.1"
REGISTER_PROFILES = {
    COMPILER_ID: (),
    COMPILER_ID + "/operand-order": (),
    COMPILER_ID + "/scratch-r0": ("r1", "r2", "r3"),
    COMPILER_ID + "/scratch-r1": ("r0", "r2", "r3"),
    COMPILER_ID + "/scratch-r2": ("r0", "r1", "r3"),
}


def find_compiler():
    configured = os.environ.get("ARM_NONE_EABI_GCC")
    if configured:
        return configured
    found = shutil.which("arm-none-eabi-gcc")
    if found:
        return found
    candidates = sorted(Path("C:/Program Files (x86)").glob(
        "Arm GNU Toolchain arm-none-eabi/*/bin/arm-none-eabi-gcc.exe"))
    if not candidates:
        raise SystemExit("arm-none-eabi-gcc 12.2.1 was not found; set ARM_NONE_EABI_GCC")
    return str(candidates[0])


def compiler_command(source, output, mode="arm", selected=COMPILER_ID, compiler=None):
    if selected not in REGISTER_PROFILES:
        raise SystemExit("unsupported GCC selection: " + selected)
    if mode not in ("arm", "thumb"):
        raise SystemExit("unsupported instruction mode: " + mode)
    compiler = compiler or find_compiler()
    version = subprocess.run([str(compiler), "-dumpfullversion"],
                             check=True, capture_output=True, text=True).stdout.strip()
    if version != "12.2.1":
        raise SystemExit("expected Arm GNU GCC 12.2.1, found " + version)
    # Original leaf routines and tail-call wrappers use one scratch argument
    # register. Reserve the others and retain expression operand order.
    profile_flags = ["-ffixed-" + register for register in REGISTER_PROFILES[selected]]
    if profile_flags or selected == COMPILER_ID + "/operand-order":
        profile_flags.append("-fno-tree-ter")
    return [
        str(compiler), "-c", "-O2", "-std=c99", "-mcpu=arm946e-s", "-m" + mode,
        "-mthumb-interwork", "-mfloat-abi=soft", "-mabi=apcs-gnu",
        # mwldarm accepts GNU ABI branch relocations, not EABI R_ARM_CALL.
        "-Wa,-meabi=gnu", "-ffreestanding", "-fsigned-char", "-fno-short-enums",
        "-fno-common", "-fno-pic", "-fno-pie", "-fno-unwind-tables",
        "-fno-asynchronous-unwind-tables", "-I", str(ROOT),
        "-I", str(ROOT.parent / "include"),
        *profile_flags,
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
    return subprocess.run(compiler_command(args.source, args.output, args.mode, args.cc)).returncode


if __name__ == "__main__":
    sys.exit(main())
