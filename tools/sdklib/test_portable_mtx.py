#!/usr/bin/env python3
"""Compare compiled portable matrix C with the existing models and ROM ARM.

Requires the local EU ROM extraction. Does not modify receipts or C progress.
Uses the existing sdk_mtx cases, ARM interpreter and SDK symbol loader.
"""
from __future__ import annotations

import argparse
import ctypes
import hashlib
import json
import os
from pathlib import Path
import random
import shutil
import subprocess
import sys
import tempfile

import verify_sdklib as sdk
from families import sdk_mtx

SOURCE = sdk.EU / "portable/nitro/matrix.c"
HEADER = SOURCE.with_suffix(".h")
EXPORTS = {
    "MI_Zero36B": ("KH_MI_Zero36B", "destination"),
    "MTX_Identity22_": ("KH_MTX_Identity22", "destination"),
    "MTX_Identity33_": ("KH_MTX_Identity33", "destination"),
    "MTX_Identity43_": ("KH_MTX_Identity43", "destination"),
    "MTX_Identity44_": ("KH_MTX_Identity44", "destination"),
    "MTX_Copy43To44_": ("KH_MTX_Copy43To44", "conversion"),
    "MTX_Copy44To43_": ("KH_MTX_Copy44To43", "conversion"),
    "MTX_RotX43_": ("KH_MTX_RotX43", "rotation"),
    "MTX_RotY43_": ("KH_MTX_RotY43", "rotation"),
}


def sha256(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def build_library(compiler, directory):
    command = [compiler, "-std=c99", "-O2", "-Wall", "-Wextra", "-Werror"]
    if os.name == "nt":
        # No CRT is needed: the matrix implementation only touches its buffers.
        # Clang's own freestanding stdint.h supplies the exact-width types.
        library = directory / "matrix.dll"
        command += ["-DKH_PORTABLE_TEST_DLL", "-shared", "-ffreestanding",
                    "-fno-builtin", "-nostdlib", "-fuse-ld=lld", "-Wl,/noentry"]
    else:
        library = directory / "matrix.so"
        command += ["-shared", "-fPIC"]
    command += [str(SOURCE), "-o", str(library)]
    subprocess.run(command, check=True, capture_output=True, text=True)
    return library, command


def check_routine(routine, native, symbols):
    export, kind = EXPORTS[routine.symbol]
    function = getattr(native, export)
    function.restype = None
    function.argtypes = ([ctypes.c_void_p, ctypes.c_void_p] if kind == "conversion"
                         else [ctypes.c_void_p, ctypes.c_int32, ctypes.c_int32]
                         if kind == "rotation" else [ctypes.c_void_p])
    memory = sdk.rom_memory()
    cpu = sdk.Cpu(memory)
    entry, _, mode = symbols[routine.symbol]
    entry |= mode == "thumb"
    seed = 0x5D1B ^ int(hashlib.sha256(routine.symbol.encode()).hexdigest()[:8], 16)
    count = 0
    for case in routine.cases(random.Random(seed)):
        if case.setup:
            case.setup(memory)
        before = memory.bytes(sdk.SCRATCH, sdk_mtx.WINDOW)
        # The original run must also satisfy the independent existing model.
        problem = sdk.run_case(cpu, entry, case)
        if problem:
            raise AssertionError(f"{routine.symbol} ROM/model: {case.label}: {problem}")
        expected = memory.bytes(sdk.SCRATCH, sdk_mtx.WINDOW)
        buffer = ctypes.create_string_buffer(before, len(before))
        base = ctypes.addressof(buffer)

        def pointer(address):
            offset = address - sdk.SCRATCH
            if not 0 <= offset < len(before):
                raise AssertionError("case pointer is outside the test window")
            return ctypes.c_void_p(base + offset)

        if kind == "conversion":
            function(pointer(case.args[0]), pointer(case.args[1]))
        elif kind == "rotation":
            function(pointer(case.args[0]), ctypes.c_int32(case.args[1]),
                     ctypes.c_int32(case.args[2]))
        else:
            function(pointer(case.args[0]))
        actual = bytes(buffer)
        if actual != expected:
            offset = next(i for i, (a, b) in enumerate(zip(actual, expected)) if a != b)
            raise AssertionError(f"{routine.symbol} compiled C/ROM: {case.label}: "
                                 f"window byte +0x{offset:x}: {actual[offset]:02x} != {expected[offset]:02x}")
        count += 1
    if count < 100:
        raise AssertionError("routine needs at least 100 differential cases")
    return {"symbol": routine.symbol, "portable_function": export, "cases": count,
            "rom_model_and_compiled_c_agree": True}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cc", help="native C compiler; use Clang on Windows")
    parser.add_argument("--report", type=Path, help="optional local JSON evidence")
    args = parser.parse_args()
    if sys.byteorder != "little":
        parser.error("raw ROM-byte comparison currently requires a little-endian test host")
    compiler = (shutil.which(args.cc) or args.cc) if args.cc else (
        shutil.which("clang") or shutil.which("gcc"))
    if not compiler and os.name == "nt":
        from _run_clang import find_compiler
        compiler = find_compiler()
    if not compiler:
        parser.error("a native Clang or GCC is required")
    compiler = str(Path(compiler).resolve())
    symbols = sdk.load_symbols()
    with tempfile.TemporaryDirectory(prefix="recoded-portable-mtx-") as directory:
        library, command = build_library(compiler, Path(directory))
        native = ctypes.CDLL(str(library))
        try:
            results = []
            for routine in sdk_mtx.ROUTINES:
                result = check_routine(routine, native, symbols)
                results.append(result)
                print(f"OK {routine.symbol}: {result['cases']} compiled-C / ROM / model cases", flush=True)
            report = {"source": str(SOURCE), "source_sha256": sha256(SOURCE),
                      "header_sha256": sha256(HEADER), "compiler": compiler,
                      "compiler_sha256": sha256(compiler), "compile_command": command,
                      "native_library_sha256": sha256(library), "routines": results,
                      "total_cases": sum(r['cases'] for r in results),
                      "scope": "buffer contents and guards, existing model checks, aligned inputs, supported overlap; no hardware timing, unaligned ARM accesses or register-clobber equivalence for host C",
                      "matching_c_progress_changed": False}
        finally:
            # Windows keeps a loaded DLL locked; unload even after a failed case.
            if os.name == "nt":
                import _ctypes
                _ctypes.FreeLibrary(native._handle)
            del native
        if args.report:
            args.report.parent.mkdir(parents=True, exist_ok=True)
            args.report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        print(f"PASS: {len(results)} routines, {report['total_cases']} cases")


if __name__ == "__main__":
    main()
