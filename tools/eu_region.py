"""EU (BK9P) commands for khrecoded.py: setup, gate and progress for the build in eu/.

The EU build keeps its own tools under eu/tools. This module wires them to the
shared toolchain in .tools/ so one checkout builds both regions.
"""

from __future__ import annotations

import hashlib
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EU = ROOT / "eu"
EU_SHA1 = "b9d45dcd654265fc7b8ba83f1bb3c15f011d6acf"
MWCC_ROOT = ROOT / ".tools" / "mwccarm" / "mwccarm"


def link_dir(link: Path, target: Path) -> None:
    if link.exists():
        return
    if os.name == "nt":
        subprocess.run(["cmd", "/c", "mklink", "/J", str(link), str(target)], check=True, capture_output=True)
    else:
        link.symlink_to(target, target_is_directory=True)


def run(*command, cwd: Path = EU) -> None:
    print("+", " ".join(str(c) for c in command))
    subprocess.run([str(c) for c in command], cwd=cwd, check=True)


def setup(rom: Path, dsd_path: Path) -> None:
    digest = hashlib.sha1(rom.read_bytes()).hexdigest()
    if digest != EU_SHA1:
        raise RuntimeError(f"{rom} is not the EU BK9P dump (sha1 {digest}, expected {EU_SHA1})")
    if not MWCC_ROOT.is_dir():
        run(sys.executable, ROOT / "tools" / "compile_match.py", "install", cwd=ROOT)
    link_dir(MWCC_ROOT / "3.0_patch4", MWCC_ROOT / "2.0" / "sp2p4")
    link_dir(EU / "tools" / "mwccarm", MWCC_ROOT)
    shutil.copyfile(dsd_path, EU / "tools" / ("dsd.exe" if os.name == "nt" else "dsd"))
    target = EU / "recoded.nds"
    if not target.exists():
        shutil.copyfile(rom, target)
    run(EU / "tools" / ("dsd.exe" if os.name == "nt" else "dsd"), "rom", "extract",
        "--rom", "recoded.nds", "--output-path", "dsd_extract/")
    run(sys.executable, "tools/configure.py")
    run(sys.executable, "tools/rebuild_index.py", "--write")
    print("EU setup done. Run `python tools/khrecoded.py eu gate` to link and verify every module.")


def gate() -> None:
    if not shutil.which("ninja"):
        raise RuntimeError("ninja is not on PATH (pip install ninja, then put its executable on PATH)")
    run("bash", "tools/gate.sh")


def progress() -> None:
    run(sys.executable, "tools/progress.py")
    run(sys.executable, ROOT / "tools" / "region_progress.py", cwd=ROOT)
