#!/usr/bin/env python3
"""Semantic model of the MobiClip colour converter (ov022 0x020aa300, MobiClip_BlitRows).

The player hands renderDecodedMovieFrame's view block to this routine: luma and
chroma planes (256-byte rows; the chroma row holds Co at +0 and Cg at +0x80),
the destination, its stride in bytes, the width in pixels, the height in rows
and a byte ramp indexed signed around +0x100. Each chroma pair covers a 2x2 luma
quad; the two anti-diagonal pixels of the quad are dithered 4 levels down, and
every pixel becomes 0x8000 | R | G << 5 | B << 10 with

    G = ramp[Y + Cg],  R = ramp[Y + Co - Cg],  B = ramp[Y - Co - Cg],

which is mobiclip_reference.convert_ycocg_to_rgb555 when ramp[v] = clamp(v) >> 3.

`--selftest` runs the ROM's own instructions (arm_exec.py) with that ramp and the
model on random planes and on frames decoded from a MODS stream, and compares
every destination word; `--capture` replays a hardware capture of the real call.
"""

from __future__ import annotations

import argparse
import random
import struct
from pathlib import Path

import mobiclip_reference
import region

ENTRY, END = 0x020AA300, 0x020AA8C0
STRIDE = 0x100


RAMP_LOW, RAMP_HIGH = -0x200, 0x300   # Y + Co - Cg reaches -259, Y + Cg reaches 382


def ramp() -> bytes:
    """The byte ramp the routine reads at table + 0x100 + v: clamp(v, 0, 255) >> 3."""
    return bytes(max(0, min(255, v)) >> 3 for v in range(RAMP_LOW, RAMP_HIGH))


def run_original(luma: bytes, chroma: bytes, width: int, height: int, dest_stride: int = 0x200):
    """Run the ROM's 0x020aa300 on one frame inside arm_exec.py; returns the pixels."""
    from arm_exec import Cpu, Memory
    mem = Memory()
    mem.map(ENTRY, region.ov022_bytes(ENTRY, END))
    src_l, src_c, dst, table, view, stack = 0x02200000, 0x02210000, 0x02220000, 0x02240000, 0x02250000, 0x02260000
    mem.map(src_l, luma[:height * STRIDE].ljust(height * STRIDE, b"\0"))
    mem.map(src_c, chroma[:(height >> 1) * STRIDE].ljust((height >> 1) * STRIDE, b"\0"))
    out = mem.map(dst, size=dest_stride * height)
    mem.map(table + 0x100 + RAMP_LOW, ramp())
    block = mem.map(view, size=0x1c)
    struct.pack_into("<7I", block, 0, src_l, src_c, dst, dest_stride, width, height, table)
    mem.map(stack - 0x400, size=0x400)
    Cpu(mem).call(ENTRY, [view], sp=stack)
    pixels = []
    for y in range(height):
        pixels.extend(struct.unpack_from(f"<{width}H", out, y * dest_stride))
    return pixels


def model(luma: bytes, chroma: bytes, width: int, height: int):
    return mobiclip_reference.convert_ycocg_to_rgb555(luma, chroma, width, height, STRIDE, STRIDE)


def _compare(luma, chroma, width, height):
    want = run_original(luma, chroma, width, height)
    got = model(luma, chroma, width, height)
    if want != got:
        index = next(i for i, (a, b) in enumerate(zip(want, got)) if a != b)
        raise AssertionError(f"pixel ({index % width},{index // width}) of {width}x{height}: "
                             f"rom {want[index]:#06x} model {got[index]:#06x}")


def selftest(count: int, seed: int, mods: str | None) -> None:
    rng = random.Random(seed)
    for _ in range(count):
        width = rng.choice([16, 32, 64, 128, 256])
        height = rng.choice([2, 16, 32, 64, 96, 192])
        luma = bytes(rng.randrange(256) for _ in range(height * STRIDE))
        chroma = bytes(rng.randrange(256) for _ in range((height >> 1) * STRIDE))
        _compare(luma, chroma, width, height)
    print(f"random planes: {count} frames byte-exact against the ROM routine")
    if mods:
        import mobiclip_deblock
        frames = mobiclip_deblock.decoded_frames(mods, 10)
        for luma, chroma, width, height, _ in frames:
            _compare(luma, chroma, width, height)
        print(f"{Path(mods).name}: {len(frames)} decoded frames byte-exact against the ROM routine")


def replay_capture(path: str) -> None:
    """Check a DeSmuME capture of the real call (capture_mobiclip_kernels.lua writes colour.json)."""
    import json
    manifest = Path(path)
    report = mobiclip_reference.evaluate_color_capture(json.loads(manifest.read_text(encoding="utf-8")),
                                                       manifest.parent)
    if not report["matchesObserved"]:
        raise AssertionError(f"capture: {report['mismatchCount']} pixels differ from the hardware")
    print(f"{manifest.name}: {report['width']}x{report['height']} model matches the captured RGB555 rows")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--capture", help="replay a DeSmuME capture manifest (colour.json)")
    ap.add_argument("--count", type=int, default=40)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--mods", help="also convert frames decoded from this MODS file")
    args = ap.parse_args()
    if args.selftest:
        selftest(args.count, args.seed, args.mods)
    if args.capture:
        replay_capture(args.capture)


if __name__ == "__main__":
    main()
