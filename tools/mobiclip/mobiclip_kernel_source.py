#!/usr/bin/env python3
"""Render a MobiClip in-place kernel as checked-in ARM mnemonic source.

Takes the code/DATA partition proved by mobiclip_kernel_inventory.py and
writes one labelled mnemonic per instruction (every branch and call target
symbolic), the embedded tables as named byte runs, and the block symbol the
player's code calls. The output is the starting point of the source; the
checked-in file is what verify_payload.py proves.

    python tools/mobiclip/mobiclip_kernel_source.py deblock MobiClip_DeblockFrame out.s [SPLIT:LABEL]

The blocks sit in ov022 .text; the deblocking filter runs on into .rodata, so
SPLIT names the address where the source switches to .rodata and LABEL the
global it defines there.
"""

from __future__ import annotations

import sys
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs
from capstone import arm

import mobiclip_kernel_inventory as inv

ROUTINE_NAMES = {
    "audio": {
        0x020AAC54: "MobiClip_AudioTransformDecode (entry: branch over the inner routines)",
        0x020AAC64: "MobiClip_AudioClearExcitation: zero the 128 excitation words",
        0x020AAC94: "MobiClip_AudioLongTermPredict: windowed copy of the history at the frame's lag",
        0x020AADE4: "MobiClip_AudioAddPulses2Bit: pulse modes 1-3, amplitudes -3g, -g, g, 3g",
        0x020AAE34: "MobiClip_AudioAddPulses3Bit: pulse mode 0, 42 pulses, amplitudes -7g..7g",
        0x020AAEC4: "MobiClip_AudioDecodeCoefficients: three codebook entries, then the Q15 step-up",
        0x020AB034: "MobiClip_AudioAddCodebookEntry: add eight s16 to r5-ip",
        0x020AB084: "MobiClip_AudioSynthesisFilter: 8th-order all-pole filter, Q14",
        0x020AB354: "MobiClip_AudioAverageCoefficients: r5-ip = (r5-ip + [r2]) / 2",
        0x020AB3C4: "MobiClip_AudioSynthesiseSubframes: four 32-sample subframes, interpolated coefficients",
        0x020AB434: "MobiClip_AudioResetChannel: gain, buffer toggle and filter history",
        0x020AB464: "MobiClip_AudioDecodeFrame: decode one frame, saturate 128 samples to s16",
        0x020AB4F4: "MobiClip_AudioReadFrameHeader: gain, codebook indices, pulse mode",
        0x020AB574: "MobiClip_AudioDecodeResetFrame: lag 127, start from the default coefficients",
        0x020AB5B4: "MobiClip_AudioDecodeNextFrame: rotate the excitation history and predict",
    },
    "colour": {
        0x020AA300: "MobiClip_BlitRows",
        0x020AA340: "outer loop: two destination rows",
        0x020AA348: "inner loop: sixteen columns as eight 2x2 quads",
        0x020AA890: "advance luma, chroma and both destination rows to the next row pair",
    },
    "fastaudio": {
        0x020ab614: "MobiClip_FastAudioDecode (entry: branch over the quantiser tables)",
        0x020AB898: "MobiClip_FastAudioParseBlock",
        0x020ABE44: "MobiClip_FastAudioExpandSubBlock",
        0x020AC020: "MobiClip_FastAudioDecodeBlockBody",
    },
    "deblock": {
        0x020B715C: "MobiClip_DeblockFrame",
        0x020B728C: "MobiClip_DeblockLumaVerticalEdges",
        0x020B73C4: "MobiClip_DeblockLumaHorizontalEdges",
        0x020B74B8: "MobiClip_DeblockChromaVerticalEdges",
        0x020B75C0: "MobiClip_DeblockChromaHorizontalEdges",
    },
}


def label(address: int) -> str:
    return "MobiClip_Code_%08X" % address


def render(name: str, symbol: str, comments: dict[str, str] | None = None,
           split: tuple[int, str] | None = None) -> str:
    result = inv.walk(name)
    start, end, _, data, raw = inv.load_block(name)
    code = set(result["code"])
    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.detail = True
    routines = ROUTINE_NAMES.get(name, {})
    comments = comments or {}
    out = [
        "    .syntax unified",
        "    .arch armv5te",
        "    .text",
        "    .arm",
        "    .align 2",
        f"    .global {symbol}",
        f"    .type {symbol}, %function",
        f"{symbol}:",
    ]
    address = start
    while address < end:
        if split and address == split[0]:
            out += [f"    .size {symbol}, {split[0] - start:#x}", '    .section .rodata,"a",%progbits', "    .arm",
                    "    .align 2", f"    .global {split[1]}", f"    .type {split[1]}, %object", f"{split[1]}:"]
        region = next(((lo, hi, tag) for lo, hi, tag in data if lo == address), None)
        if region:
            lo, hi, tag = region
            if tag in comments:
                out.append(f"    /* {comments[tag]} */")
            out += [f"    .global {tag}", f"    .type {tag}, %object", f"{tag}:"]
            chunk = raw[lo - start:hi - start]
            for i in range(0, len(chunk), 16):
                out.append("    .byte " + ", ".join("0x%02x" % b for b in chunk[i:i + 16]))
            address = hi
            continue
        if address not in code:
            raise ValueError(f"0x{address:08x} is neither code nor declared DATA")
        if address in routines:
            out.append(f"    /* {routines[address]} */")
        insn = next(md.disasm(raw[address - start:address - start + 4], address))
        text = f"{insn.mnemonic} {insn.op_str}".strip()
        if insn.id in (arm.ARM_INS_B, arm.ARM_INS_BL):
            text = f"{insn.mnemonic} {label(insn.operands[0].imm)}"
        out.append(f"{label(address)}:")
        out.append(f"    {text}")
        address += 4
    if split:
        out.append(f"    .size {split[1]}, . - {split[1]}")
    else:
        out.append(f"    .size {symbol}, . - {symbol}")
    return "\n".join(out) + "\n"


def main() -> None:
    if len(sys.argv) not in (4, 5):
        raise SystemExit(__doc__)
    name, symbol, output = sys.argv[1:4]
    split = None
    if len(sys.argv) == 5:
        address, tag = sys.argv[4].split(":")
        split = (int(address, 16), tag)
    Path(output).write_text(render(name, symbol, split=split), encoding="ascii", newline="\n")
    print(output)


if __name__ == "__main__":
    main()
