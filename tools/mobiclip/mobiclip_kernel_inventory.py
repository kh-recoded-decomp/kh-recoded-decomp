#!/usr/bin/env python3
"""Code/DATA inventory of the MobiClip kernels that run in place from ov022.

Besides the decoder payload the player copies into its arena (mobiclip_inventory.py), the
MobiClip library keeps two hand-written ARM blocks in its read-only data that the
player calls directly: the FastAudio decoder (0x020ab614) and the deblocking
post-filter (0x020b715c). This walks every path from each block's entry points,
follows branches and calls, stops at computed or returning writes of pc, and
checks that the reachable instructions plus the declared embedded-DATA ranges
tile the block exactly -- no gap, no overlap.

    python tools/mobiclip/mobiclip_kernel_inventory.py            # both blocks
    python tools/mobiclip/mobiclip_kernel_inventory.py deblock --json
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs
from capstone import arm

import region

OVERLAY = region.OV022
OVERLAY_BASE = region.OV022_BASE

# name -> (start, end, entry points, embedded DATA ranges [start, end, label])
BLOCKS = {
    "audio": (
        0x020AAC54, 0x020AB614,
        [0x020AAC54],
        [
            (0x020AAC58, 0x020AAC64, "gMobiClipAudioAlign_ClearExcitation"),
            (0x020AAC8C, 0x020AAC94, "gMobiClipAudioAlign_LongTermPredict"),
            (0x020AADDC, 0x020AADE4, "gMobiClipAudioAlign_AddPulses2Bit"),
            (0x020AAE2C, 0x020AAE34, "gMobiClipAudioAlign_AddPulses3Bit"),
            (0x020AAEC0, 0x020AAEC4, "gMobiClipAudioAlign_DecodeCoefficients"),
            (0x020AB078, 0x020AB084, "gMobiClipAudioAlign_SynthesisFilter"),
            (0x020AB34C, 0x020AB354, "gMobiClipAudioAlign_AverageCoefficients"),
            (0x020AB3BC, 0x020AB3C4, "gMobiClipAudioAlign_SynthesiseSubframes"),
            (0x020AB4DC, 0x020AB4E2, "gMobiClipAudioPulseLayout"),
            (0x020AB4E2, 0x020AB4E6, "gMobiClipAudioFrameBytes"),
            (0x020AB4E6, 0x020AB4F4, "gMobiClipAudioAlign_ReadFrameHeader"),
            (0x020AB56C, 0x020AB574, "gMobiClipAudioAlign_DecodeResetFrame"),
            (0x020AB60C, 0x020AB610, "gMobiClipAudioSampleMax"),
            (0x020AB610, 0x020AB614, "gMobiClipAudioSampleMin"),
        ],
    ),
    "colour": (
        0x020AA300, 0x020AA8C0,
        [0x020AA300],
        [],
    ),
    "fastaudio": (
        0x020ab614, 0x020AC9C0,
        [0x020ab614],
        [
            (0x020AB618, 0x020AB718, "gFastAudioReflection6Bit"),
            (0x020AB718, 0x020AB798, "gFastAudioReflection2"),
            (0x020AB798, 0x020AB818, "gFastAudioReflection3"),
            (0x020AB818, 0x020AB858, "gFastAudioReflection4"),
            (0x020AB858, 0x020AB878, "gFastAudioReflection6"),
            (0x020AB878, 0x020AB898, "gFastAudioReflection7"),
            (0x020ABE04, 0x020ABE44, "gFastAudioReflection5"),
            (0x020AC010, 0x020AC020, "gFastAudioSynthesisConstants"),
            (0x020AC1C0, 0x020AC9C0, "gFastAudioExcitation"),
        ],
    ),
    "deblock": (
        0x020B715C, 0x020B76A8,
        [0x020B715C],
        [
            (0x020B7240, 0x020B7265, "gMobiClipDeblockAlpha"),
            (0x020B7265, 0x020B728A, "gMobiClipDeblockBeta"),
            (0x020B728A, 0x020B728C, "gMobiClipDeblockPad"),
            (0x020B7698, 0x020B76A8, "gMobiClipDeblockTailWords"),
        ],
    ),
}


def load_block(name: str):
    start, end, entries, data = BLOCKS[name]
    image = OVERLAY.read_bytes()
    return start, end, entries, data, image[start - OVERLAY_BASE:end - OVERLAY_BASE]


def walk(name: str) -> dict:
    start, end, entries, data, raw = load_block(name)
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.detail = True
    code = set()
    pending = list(entries)
    calls = set()
    while pending:
        address = pending.pop()
        while True:
            if address in code:
                break
            if not start <= address < end:
                raise ValueError(f"{name}: path leaves the block at 0x{address:08x}")
            if any(lo <= address < hi for lo, hi, _ in data):
                raise ValueError(f"{name}: path runs into embedded DATA at 0x{address:08x}")
            word = raw[address - start:address - start + 4]
            insn = next(md.disasm(word, address), None)
            if insn is None:
                raise ValueError(f"{name}: undecodable word at 0x{address:08x}")
            code.add(address)
            conditional = insn.cc not in (arm.ARM_CC_AL, arm.ARM_CC_INVALID)
            mnemonic = insn.id
            if mnemonic in (arm.ARM_INS_B, arm.ARM_INS_BL):
                target = insn.operands[0].imm
                if mnemonic == arm.ARM_INS_BL:
                    calls.add(target)
                    pending.append(target)
                    address += 4
                    continue
                pending.append(target)
                if not conditional:
                    break
                address += 4
                continue
            writes_pc = arm.ARM_REG_PC in insn.regs_access()[1]
            if writes_pc:
                # pop {..., pc}, mov pc, lr, bx lr, ldr pc, [...]: the path ends here
                if not conditional:
                    break
            address += 4
    words = sorted(code)
    covered = len(words) * 4 + sum(hi - lo for lo, hi, _ in data)
    gaps = []
    cursor = start
    marks = sorted([(a, a + 4) for a in words] + [(lo, hi) for lo, hi, _ in data])
    for lo, hi in marks:
        if lo > cursor:
            gaps.append((cursor, lo))
        if lo < cursor:
            raise ValueError(f"{name}: overlap at 0x{lo:08x}")
        cursor = max(cursor, hi)
    if cursor < end:
        gaps.append((cursor, end))
    return {
        "name": name,
        "start": start,
        "end": end,
        "instructions": len(words),
        "embedded_data_bytes": sum(hi - lo for lo, hi, _ in data),
        "covered": covered,
        "size": end - start,
        "gaps": gaps,
        "calls": sorted(calls),
        "code": words,
    }


def main() -> None:
    names = [a for a in sys.argv[1:] if not a.startswith("--")] or sorted(BLOCKS)
    ok = True
    for name in names:
        result = walk(name)
        if "--json" in sys.argv:
            print(json.dumps({k: v for k, v in result.items() if k != "code"}, indent=2))
        tiled = not result["gaps"] and result["covered"] == result["size"]
        ok &= tiled
        print(
            f"{name}: 0x{result['start']:08x}-0x{result['end']:08x} {result['size']} bytes = "
            f"{result['instructions']} instructions + {result['embedded_data_bytes']} DATA bytes"
            + ("" if tiled else f"; GAPS {[(hex(a), hex(b)) for a, b in result['gaps']]}")
        )
    raise SystemExit(0 if ok else 1)


if __name__ == "__main__":
    main()
