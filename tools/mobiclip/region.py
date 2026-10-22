"""Where the MobiClip library lives in the EU (BK9P) image, and local work paths.

The MobiClip player sits in ov022. Its hand-written ARM blocks and run/level
tables are stored in the overlay's .text (the deblocking filter runs on into
.rodata). Everything here is read from the extracted ROM under eu/dsd_extract;
derived files go to the ignored eu/build/mobiclip directory.
"""

from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EU = ROOT / "eu"
WORK = EU / "build" / "mobiclip"
OV022 = EU / "dsd_extract" / "arm9_overlays" / "ov022.bin"
OV022_BASE = 0x020A6EE0
MODS_DIR = EU / "dsd_extract" / "files" / "mv"

AUDIO_TRANSFORM = (0x020AAC54, 0x020AB614)
FASTAUDIO = (0x020AB614, 0x020AC9C0)
RUN_LEVEL_TABLE_1 = (0x020AC9C0, 0x020AEAC0)  # format variant 1
RUN_LEVEL_TABLE_0 = (0x020AEAC0, 0x020B0BC0)  # format variant 0
PAYLOAD = (0x020B0BC0, 0x020B715C)
DEBLOCK = (0x020B715C, 0x020B76A8)


def ov022_bytes(start: int, end: int) -> bytes:
    data = OV022.read_bytes()
    return data[start - OV022_BASE:end - OV022_BASE]


def run_level_tables() -> tuple[bytes, bytes]:
    """(variant 0, variant 1) prefix tables, as the decoder state indexes them."""
    return ov022_bytes(*RUN_LEVEL_TABLE_0), ov022_bytes(*RUN_LEVEL_TABLE_1)


def table_paths() -> tuple[Path, Path]:
    """Write both tables to the work directory (for tools that take file paths)."""
    WORK.mkdir(parents=True, exist_ok=True)
    table0, table1 = run_level_tables()
    paths = (WORK / "run_level_table_0.bin", WORK / "run_level_table_1.bin")
    for path, data in zip(paths, (table0, table1)):
        if not path.exists() or path.read_bytes() != data:
            path.write_bytes(data)
    return paths
