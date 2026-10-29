#!/usr/bin/env python3
"""Compile explicitly selected original ARM routines implemented in C."""
import os
import shutil
import subprocess
import sys
from pathlib import Path

from project import ROOT


COMPILER_ID = "gcc/12.2.1"
COMPILER_RELEASE = "Arm GNU Toolchain 12.2.Rel1"
COMPILER_DATE = "20221205"
REGISTER_PROFILES = {
    COMPILER_ID: (),
    COMPILER_ID + "/operand-order": (),
    COMPILER_ID + "/scratch-r0": ("r1", "r2", "r3"),
    COMPILER_ID + "/scratch-r1": ("r0", "r2", "r3"),
    COMPILER_ID + "/scratch-r2": ("r0", "r1", "r3"),
    COMPILER_ID + "/cache-sets": ("r3",),
    COMPILER_ID + "/cache-flush": ("r3",),
    COMPILER_ID + "/control-mask": ("r2", "r3"),
    COMPILER_ID + "/wait-state": ("r2", "r3"),
    COMPILER_ID + "/fifo-zeros": (),
    COMPILER_ID + "/mode-select": (),
    COMPILER_ID + "/byte-copy": (),
    COMPILER_ID + "/armv4t-return": (),
    COMPILER_ID + "/cp15-setup": (),
}


def find_compiler():
    configured = os.environ.get("ARM_NONE_EABI_GCC")
    if configured:
        return configured
    executable = "arm-none-eabi-gcc.exe" if os.name == "nt" else "arm-none-eabi-gcc"
    bundled = sorted((ROOT.parent / ".tools/arm-gnu-12.2.rel1").glob(
        "arm-gnu-toolchain-12.2.rel1-*/bin/" + executable))
    if bundled:
        return str(bundled[0])
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
    banner = subprocess.run([str(compiler), "--version"],
                            check=True, capture_output=True, text=True).stdout.splitlines()[0]
    if COMPILER_RELEASE not in banner or "12.2.1 " + COMPILER_DATE not in banner:
        raise SystemExit("expected Arm GNU 12.2.Rel1 (12.2.1 20221205), found " + banner +
                         "; run python tools/install_gcc.py from eu/, or set ARM_NONE_EABI_GCC")
    # Original leaf routines and tail-call wrappers use one scratch argument
    # register. Reserve the others and retain expression operand order.
    profile_flags = ["-ffixed-" + register for register in REGISTER_PROFILES[selected]]
    if profile_flags or selected == COMPILER_ID + "/operand-order":
        profile_flags.append("-fno-tree-ter")
    if selected in (COMPILER_ID + "/cache-sets", COMPILER_ID + "/cache-flush"):
        # Retain the original cache-set loops and separate arithmetic/compares.
        profile_flags.extend(("-fno-tree-vrp", "-fno-tree-loop-optimize",
                              "-fdisable-rtl-combine"))
    if selected == COMPILER_ID + "/cache-flush":
        # Keep the independent drain operand before the cache-set initializer.
        profile_flags.extend(("-fira-algorithm=priority", "-fdisable-rtl-cse2",
                              "-fdisable-rtl-postreload", "-fno-tree-ccp",
                              "-fno-tree-copy-prop", "-fno-tree-forwprop",
                              "-fno-tree-fre", "-fno-tree-dominator-opts",
                              "-fdisable-tree-pre", "-fno-tree-reassoc"))
    if selected == COMPILER_ID + "/control-mask":
        # Retain the loaded control-register mask and the separate AND.
        profile_flags.append("-fdisable-rtl-combine")
    if selected == COMPILER_ID + "/fifo-zeros":
        # Keep each bound zero register's own initialization.
        profile_flags.extend(("-fdisable-rtl-cse2", "-fdisable-rtl-postreload"))
    if selected == COMPILER_ID + "/mode-select":
        # Keep the masked mode bit as the flag-setting AND's result.
        profile_flags.extend(("-fno-tree-dominator-opts", "-fno-tree-vrp", "-fno-tree-sink"))
    if selected == COMPILER_ID + "/byte-copy":
        # Retain the original size compares, block order and unscheduled accesses.
        profile_flags.extend(("-fno-tree-sink", "-fno-tree-vrp", "-fno-schedule-insns",
                              "-fno-schedule-insns2", "-fno-move-loop-invariants",
                              "-fno-thread-jumps", "-fno-tree-ccp", "-fno-tree-forwprop",
                              "-fno-tree-fre", "-fno-tree-pre", "-fno-tree-copy-prop",
                              "-fno-tree-dominator-opts", "-fno-reorder-blocks"))
    if selected == COMPILER_ID + "/armv4t-return":
        # ARMv4T subset: separate register restore and BX return.
        profile_flags.extend(("-march=armv4t", "-fno-schedule-insns", "-fno-schedule-insns2",
                              "-fno-tree-fre", "-fno-tree-pre", "-fno-tree-dominator-opts",
                              "-fno-tree-dce", "-fno-dce"))
    if selected == COMPILER_ID + "/cp15-setup":
        # Keep every coprocessor value in r0 and each mask as a pool literal.
        profile_flags.extend(("-ffixed-r1", "-ffixed-r2", "-ffixed-r3", "-fno-tree-vrp",
                              "-fno-tree-ccp", "-fno-tree-forwprop", "-fno-tree-fre",
                              "-fno-tree-pre", "-fno-tree-copy-prop", "-fno-tree-dominator-opts",
                              "-fdisable-rtl-cse1", "-fdisable-rtl-cse2",
                              "-fdisable-rtl-postreload"))
    return [
        str(compiler), "-c", "-O2", "-std=c99", "-mcpu=arm946e-s", "-m" + mode,
        "-mthumb-interwork", "-mfloat-abi=soft", "-mabi=apcs-gnu",
        # mwldarm accepts GNU ABI branch relocations, not EABI R_ARM_CALL.
        "-Wa,-meabi=gnu", "-ffreestanding", "-fsigned-char", "-fno-short-enums",
        "-fno-common", "-fno-pic", "-fno-pie", "-fno-unwind-tables",
        "-fno-asynchronous-unwind-tables", "-I", str(ROOT),
        "-I", str(ROOT.parent / "include"),
        *profile_flags,
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
