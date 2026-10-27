#!/usr/bin/env python3
"""Compile explicitly selected original assembly routines as ARMCC C."""
import hashlib
import json
import os
import subprocess
import sys
from pathlib import Path

from project import ROOT


COMPILER_ID = "armcc/5.06u7"
COMPILER_HASHES = {
    "52fcff95b164ef766b7ba8931b6fc4cc9504018db94d7f10f8b62107df74f963": "original build 960",
    "90366b3b7879aa7d2909cbade2c25b9cbfc2bae352100fd9915471b7f7f8b597": "local CPU/ELF capability variant of build 960",
}


def find_compiler():
    configured = os.environ.get("ARMCC5")
    compiler = Path(configured) if configured else ROOT / "tools/armcc/5.06u7/ARM/ARMCC/bin/armcc.exe"
    if not compiler.is_file():
        raise SystemExit("ARMCC 5.06u7 build 960 was not found; set ARMCC5")
    return str(compiler)


def compiler_environment(compiler):
    env = dict(os.environ)
    mappings = Path(compiler).resolve().parents[2] / "sw/mappings"
    if mappings.is_dir():
        env.setdefault("ARM_PRODUCT_PATH", str(mappings))
        env.setdefault("ARM_TOOL_VARIANT", "mdk_lite")
    return env


def compiler_command(source, output, mode="arm", selected=COMPILER_ID, compiler=None):
    if selected != COMPILER_ID:
        raise SystemExit("unsupported ARMCC selection: " + selected)
    if mode not in ("arm", "thumb"):
        raise SystemExit("unsupported instruction mode: " + mode)
    compiler = compiler or find_compiler()
    digest = hashlib.sha256(Path(compiler).read_bytes()).hexdigest()
    if digest not in COMPILER_HASHES:
        raise SystemExit("unsupported ARMCC executable SHA-256: " + digest)
    return [str(compiler), "--cpu=ARM946E-S", "--" + mode, "--c99",
            "-O3", "-Ospace", "--signed_chars", "--enum_is_int",
            "-I", str(ROOT), "-I", str(ROOT.parent / "include"),
            "-c", str(source), "-o", str(output)]


def compile_source(source, output, mode="arm", selected=COMPILER_ID, compiler=None):
    command = compiler_command(source, output, mode, selected, compiler)
    Path(output).parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(command, env=compiler_environment(command[0]), check=True)
    if Path(output).read_bytes()[:4] != b"\x7fELF":
        raise SystemExit("ARMCC must emit native ELF; restricted-format output is not supported")
    digest = hashlib.sha256(Path(command[0]).read_bytes()).hexdigest()
    provenance = {"compiler": command[0], "compiler_sha256": digest,
                  "compiler_variant": COMPILER_HASHES[digest], "command": command,
                  "source_sha256": hashlib.sha256(Path(source).read_bytes()).hexdigest(),
                  "object_sha256": hashlib.sha256(Path(output).read_bytes()).hexdigest()}
    Path(str(output) + ".compiler.json").write_text(json.dumps(provenance, indent=2) + "\n")
    return str(output)


def main():
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("output")
    parser.add_argument("source")
    parser.add_argument("--mode", choices=("arm", "thumb"), default="arm")
    parser.add_argument("--cc", default=COMPILER_ID)
    args = parser.parse_args()
    compile_source(args.source, args.output, args.mode, args.cc)


if __name__ == "__main__":
    main()
