#!/usr/bin/env python3
"""Install the pinned free Windows Arm GNU toolchain locally, without changing PATH."""
import argparse
import hashlib
import os
from pathlib import Path, PurePosixPath
import subprocess
from urllib.request import urlopen
from zipfile import ZipFile

from project import ROOT

PACKAGE = "arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi"
URL = "https://developer.arm.com/-/media/Files/downloads/gnu/12.2.rel1/binrel/" + PACKAGE + ".zip"
SHA256 = "ad1427496cde9bbe7604bc448ec6e115c6538e04af1c8275795ebb1c2b7b2830"
DESTINATION = ROOT.parent / ".tools/arm-gnu-12.2.rel1"


def checked_members(archive, destination):
    root = Path(destination).resolve()
    for member in archive.infolist():
        path = PurePosixPath(member.filename)
        if path.is_absolute() or ".." in path.parts:
            raise ValueError("unsafe path in toolchain archive")
        (root / member.filename).resolve().relative_to(root)
        yield member


def main():
    argparse.ArgumentParser(description=__doc__).parse_args()
    if os.name != "nt":
        raise SystemExit("This installer downloads the Windows archive. Install Arm GNU 12.2.Rel1 "
                         "(12.2.1 20221205) for your host and set ARM_NONE_EABI_GCC instead.")
    DESTINATION.mkdir(parents=True, exist_ok=True)
    archive_path = DESTINATION / "toolchain.zip"
    if not archive_path.is_file():
        partial = archive_path.with_suffix(".zip.part")
        print("Downloading", URL, flush=True)
        with urlopen(URL, timeout=60) as response, partial.open("wb") as output:
            while chunk := response.read(1024 * 1024):
                output.write(chunk)
        partial.replace(archive_path)
    with archive_path.open("rb") as stream:
        digest = hashlib.file_digest(stream, "sha256").hexdigest()
    if digest != SHA256:
        raise SystemExit("Toolchain archive SHA-256 mismatch; no files extracted")
    compiler = DESTINATION / PACKAGE / "bin/arm-none-eabi-gcc.exe"
    completed = DESTINATION / "installed.sha256"
    if not compiler.is_file() or not completed.is_file() or completed.read_text().strip() != SHA256:
        with ZipFile(archive_path) as archive:
            members = list(checked_members(archive, DESTINATION))
            archive.extractall(DESTINATION, members=members)
    banner = subprocess.run([str(compiler), "--version"], check=True,
                            capture_output=True, text=True).stdout.splitlines()[0]
    if "Arm GNU Toolchain 12.2.Rel1" not in banner or "12.2.1 20221205" not in banner:
        raise SystemExit("Unexpected installed compiler: " + banner)
    completed.write_text(SHA256 + "\n", encoding="ascii")
    print(banner)
    print("Verified archive SHA-256:", SHA256)
    print("Ready:", compiler)


if __name__ == "__main__":
    main()
