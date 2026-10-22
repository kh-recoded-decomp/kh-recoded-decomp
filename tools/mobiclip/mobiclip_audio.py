#!/usr/bin/env python3
"""Semantic model of MobiClip audio coding 1 (ov022 0x020aac54, MobiClip_AudioTransformDecode).

Coding 1 is a small CELP-style speech codec. Every call decodes one frame of 10-20
bytes into 128 samples and returns the number of bytes it consumed; the player adds
that to its stream cursor. All state lives in the channel record (0x14f8 bytes):

    +0x0000  stream pointer (read, not advanced)     +0x0004  output pointer
    +0x0008  reflection vector of the last frame (8 words, the next frame's base)
    +0x0028, +0x0048  predictor coefficients of the last two frames (8 words each)
    +0x0068  excitation gain                          +0x006c  history buffer toggle
    +0x0070  codebook indices 0, 1, 2 and pulse mode (bytes)
    +0x0074  synthesis output pointer                 +0x0078  filter history (8 words)
    +0x00c0, +0x04c0  two history buffers of 256 words: [previous | current] excitation;
                      the first half of the other one receives the synthesised samples
    +0x08c0, +0x0cc0, +0x10c0  three codebooks of 64 entries x 8 s16
    +0x14c0  gain multipliers (8 s16, Q13)            +0x14d0  default reflection vector
    +0x14f0  initial gain                             +0x14f4  output stride in bytes

A frame starts with two halfwords. Word 0: lag (bits 15-9), gain index (8-6),
codebook index 0 (5-0). Word 1: pulse phase (15-14), pulse mode (13-12), codebook
indices 1 (11-6) and 2 (5-0). Lag 127 restarts the channel, lag 126 starts from
silence, any other lag copies a windowed stretch of the previous two frames'
excitation (weights 1/16 .. 7/16 at the ends, 1/2 in between). Pulses follow:
mode 0 packs 42 three-bit amplitudes (-7g .. 7g, every third sample) into eight
halfwords; modes 1, 2 and 3 pack two-bit amplitudes (-3g, -g, g, 3g) into five,
four or three halfwords, every third, fourth or fifth sample. The reflection
vector is the base plus one entry of each codebook; a Q15 step-up recursion turns
it into eight predictor coefficients, which are interpolated with the last
frame's over four 32-sample subframes of an all-pole synthesis filter (Q14).
The 128 samples are saturated to s16 and stored at the output stride.

Everything wraps at 32 bits exactly as the ARM code does. `--selftest` runs the
ROM's own instructions (arm_exec.py) next to this model on random channel records
and frame chains and compares every byte of the record and every output sample;
`--capture` replays a DeSmuME capture of a forced call
(capture_mobiclip_kernels.lua writes audio_transform_<n>.json).
"""

from __future__ import annotations

import argparse
import json
import random
import struct
from pathlib import Path

import region

ENTRY, END = region.AUDIO_TRANSFORM
RECORD_SIZE = 0x14F8
FRAME_BYTES = (20, 14, 12, 10)                  # gMobiClipAudioFrameBytes, by pulse mode
PULSE_LAYOUT = {1: (5, 3), 2: (4, 4), 3: (3, 5)}  # gMobiClipAudioPulseLayout: halfwords, step

PREV_VECTOR, SLOT_A, SLOT_B = 0x08, 0x28, 0x48
GAIN, TOGGLE, INDICES, OUT_CURSOR, HISTORY = 0x68, 0x6C, 0x70, 0x74, 0x78
BUFFERS, CODEBOOKS, GAIN_TABLE, DEFAULT_VECTOR, INITIAL_GAIN, STRIDE = 0xC0, 0x8C0, 0x14C0, 0x14D0, 0x14F0, 0x14F4


def s32(value: int) -> int:
    value &= 0xFFFFFFFF
    return value - (1 << 32) if value & 0x80000000 else value


class Record:
    """Word/halfword view of a channel record, wrapping like the ARM code."""

    def __init__(self, data: bytes, base: int):
        self.mem = bytearray(data)
        self.base = base

    def word(self, offset: int) -> int:
        return struct.unpack_from("<i", self.mem, offset)[0]

    def set_word(self, offset: int, value: int) -> None:
        struct.pack_into("<i", self.mem, offset, s32(value))

    def words(self, offset: int, count: int) -> list[int]:
        return list(struct.unpack_from(f"<{count}i", self.mem, offset))

    def set_words(self, offset: int, values) -> None:
        struct.pack_into(f"<{len(values)}i", self.mem, offset, *(s32(v) for v in values))

    def s16(self, offset: int) -> int:
        return struct.unpack_from("<h", self.mem, offset)[0]


def _buffer(index: int) -> int:
    return BUFFERS + 0x400 * index


def _long_term_predict(rec: Record, current: int, lag: int) -> None:
    src = rec.words(_buffer(current ^ 1) + 4 * (127 - lag), 128)
    out = []
    for i, value in enumerate(src):
        weight = min(i + 1, 128 - i)
        out.append(s32(value) >> 1 if weight >= 8 else s32(value * weight) >> 4 if weight > 1 else value >> 4)
    rec.set_words(_buffer(current) + 0x200, out)


def _add_pulses(rec: Record, current: int, frame: bytes, phase: int, mode: int, gain: int) -> None:
    excitation = _buffer(current) + 0x200
    halfwords = struct.unpack_from("<8H", frame.ljust(20, b"\0"), 4)

    def add(position: int, amplitude: int) -> None:
        offset = excitation + 4 * position
        rec.set_word(offset, rec.word(offset) + amplitude)

    if mode == 0:
        step2 = s32(gain << 1)
        bias = s32(s32(s32(-gain) - s32(step2 << 1)) - step2)       # -7g
        position, low_bits = phase, 0
        for word in halfwords:
            for shift in (13, 10, 7, 4, 1):
                add(position, step2 * ((word >> shift) & 7) + bias)
                position += 3
            low_bits = (low_bits << 1) | (word & 1)
        for shift in (5, 2):
            add(position, step2 * ((low_bits >> shift) & 7) + bias)
            position += 3
        return
    count, step = PULSE_LAYOUT[mode]
    step2 = s32(gain << 1)
    bias = s32(s32(-gain) - step2)                                     # -3g
    position = phase
    for word in halfwords[:count]:
        for shift in (14, 12, 10, 8, 6, 4, 2, 0):
            add(position, step2 * ((word >> shift) & 3) + bias)
            position += step


def _read_frame_header(rec: Record, current: int, frame: bytes) -> None:
    word0, word1 = struct.unpack_from("<2H", frame)
    rec.mem[INDICES] = word0 & 0x3F
    gain = s32(rec.s16(GAIN_TABLE + 2 * ((word0 >> 6) & 7)) * rec.word(GAIN)) >> 13
    rec.set_word(GAIN, gain)
    rec.mem[INDICES + 1] = (word1 >> 6) & 0x3F
    rec.mem[INDICES + 2] = word1 & 0x3F
    mode = (word1 >> 12) & 3
    rec.mem[INDICES + 3] = mode
    _add_pulses(rec, current, frame, (word1 >> 14) & 3, mode, gain)


def _coefficients(rec: Record, base: int) -> list[int]:
    vector = rec.words(base, 8)
    for book in range(3):
        entry = CODEBOOKS + 0x400 * book + 16 * rec.mem[INDICES + book]
        vector = [s32(v + rec.s16(entry + 2 * i)) for i, v in enumerate(vector)]
    rec.set_words(PREV_VECTOR, vector)
    a = list(vector)
    for m in range(1, 8):
        k, old = a[m], a[:m]
        for i in range(m):
            a[i] = s32(old[i] + (s32(old[m - 1 - i] * k) >> 15))
    return [s32(-(value >> 1)) for value in a]


def _average(x: list[int], y: list[int]) -> list[int]:
    return [s32(p + q) >> 1 for p, q in zip(x, y)]


def _synthesise(rec: Record, coefficients: list[int], excitation: int, count: int) -> None:
    history = rec.words(HISTORY, 8)
    cursor = rec.word(OUT_CURSOR) - rec.base
    for group in range(0, count, 8):
        for j in range(8):
            acc = rec.word(excitation + 4 * (group + j)) << 14
            for i, a in enumerate(coefficients):
                acc += a * history[(j - 1 - i) % 8]
            history[j] = s32(acc) >> 14
            rec.set_word(cursor, history[j])
            cursor += 4
    rec.set_words(HISTORY, history)
    rec.set_word(OUT_CURSOR, rec.base + cursor)


def decode_frame(record: bytes, frame: bytes, base: int):
    """Decode one frame. Returns (record after the call, 128 saturated samples, bytes consumed)."""
    rec = Record(record, base)
    lag = struct.unpack_from("<H", frame)[0] >> 9
    if lag == 127:
        rec.set_word(GAIN, rec.word(INITIAL_GAIN))
        rec.set_word(TOGGLE, 1)
        rec.set_words(HISTORY, [0] * 8)
        rec.set_words(_buffer(1) + 0x200, [0] * 128)
        _read_frame_header(rec, 1, frame)
        coefficients = _coefficients(rec, DEFAULT_VECTOR)
        rec.set_words(SLOT_B, coefficients)
        output = _buffer(0)
        rec.set_word(OUT_CURSOR, base + output)
        _synthesise(rec, coefficients, _buffer(1) + 0x200, 128)
    else:
        current = rec.word(TOGGLE)
        rec.mem[_buffer(current):_buffer(current) + 0x200] = rec.mem[_buffer(current ^ 1) + 0x200:_buffer(current ^ 1) + 0x400]
        if lag == 126:
            rec.set_words(_buffer(current) + 0x200, [0] * 128)
        else:
            _long_term_predict(rec, current, lag)
        _read_frame_header(rec, current, frame)
        coefficients = _coefficients(rec, PREV_VECTOR)
        new, previous = (SLOT_B, SLOT_A) if current == 1 else (SLOT_A, SLOT_B)
        output = _buffer(current ^ 1)
        rec.set_word(OUT_CURSOR, base + output)
        rec.set_words(new, coefficients)
        excitation = _buffer(current) + 0x200
        middle = _average(coefficients, rec.words(previous, 8))
        for subframe, coefs in enumerate((_average(middle, rec.words(previous, 8)), middle,
                                          _average(middle, coefficients), coefficients)):
            _synthesise(rec, coefs, excitation + 0x80 * subframe, 32)
    rec.set_word(TOGGLE, rec.word(TOGGLE) ^ 1)
    samples = [max(-0x8000, min(0x7FFF, value)) for value in rec.words(output, 128)]
    return bytes(rec.mem), samples, FRAME_BYTES[rec.mem[INDICES + 3]]


# -- the ROM's own instructions ------------------------------------------------------

RECORD_AT, FRAME_AT, OUTPUT_AT, STACK_AT = 0x02200000, 0x02210000, 0x02220000, 0x02240000


def run_original(record: bytes, frame: bytes, stride: int = 2):
    """Run 0x020aac54 inside arm_exec.py. Returns (record after, samples, bytes consumed)."""
    from arm_exec import Cpu, Memory
    mem = Memory()
    mem.map(ENTRY, region.ov022_bytes(ENTRY, END))
    rec = mem.map(RECORD_AT, record)
    struct.pack_into("<2I", rec, 0, FRAME_AT, OUTPUT_AT)
    struct.pack_into("<I", rec, STRIDE, stride)
    mem.map(FRAME_AT, frame.ljust(32, b"\0"))
    out = mem.map(OUTPUT_AT, size=128 * stride)
    mem.map(STACK_AT - 0x1000, size=0x1000)
    consumed = Cpu(mem).call(ENTRY, [RECORD_AT], sp=STACK_AT)
    samples = [struct.unpack_from("<h", out, i * stride)[0] for i in range(128)]
    return bytes(rec), samples, consumed


def prepare(record: bytes, stride: int = 2) -> bytes:
    rec = bytearray(record)
    struct.pack_into("<2I", rec, 0, FRAME_AT, OUTPUT_AT)
    struct.pack_into("<I", rec, STRIDE, stride)
    return bytes(rec)


def random_record(rng: random.Random, wild: bool = False) -> bytes:
    """A channel record with plausible magnitudes, or arbitrary words when `wild`."""
    rec = Record(bytes(rng.randrange(256) for _ in range(RECORD_SIZE)), RECORD_AT)

    def fill(offset, count, low, high):
        if not wild:
            rec.set_words(offset, [rng.randint(low, high) for _ in range(count)])

    fill(PREV_VECTOR, 8, -20000, 20000)
    fill(SLOT_A, 16, -16000, 16000)
    fill(GAIN, 1, 0, 4000)
    rec.set_word(TOGGLE, rng.randrange(2))
    fill(HISTORY, 8, -20000, 20000)
    fill(BUFFERS, 512, -30000, 30000)
    if not wild:
        struct.pack_into("<1536h", rec.mem, CODEBOOKS, *(rng.randint(-3000, 3000) for _ in range(1536)))
        struct.pack_into("<8h", rec.mem, GAIN_TABLE, *(rng.randint(0, 16384) for _ in range(8)))
    fill(DEFAULT_VECTOR, 8, -20000, 20000)
    fill(INITIAL_GAIN, 1, 0, 4000)
    return prepare(bytes(rec.mem))


def random_frame(rng: random.Random, lag: int | None = None) -> bytes:
    frame = bytearray(rng.randrange(256) for _ in range(20))
    if lag is None:
        lag = rng.choice([127, 126] + [rng.randrange(126)] * 4)
    word0 = (lag << 9) | (struct.unpack_from("<H", frame)[0] & 0x1FF)
    struct.pack_into("<H", frame, 0, word0)
    return bytes(frame)


def _compare(record: bytes, frame: bytes, label: str) -> bytes:
    want = run_original(record, frame)
    got = decode_frame(record, frame, RECORD_AT)
    if want[2] != got[2]:
        raise AssertionError(f"{label}: consumed {got[2]} bytes, the ROM {want[2]}")
    if want[1] != got[1]:
        index = next(i for i, (a, b) in enumerate(zip(want[1], got[1])) if a != b)
        raise AssertionError(f"{label}: sample {index} rom {want[1][index]} model {got[1][index]}")
    if want[0] != got[0]:
        index = next(i for i, (a, b) in enumerate(zip(want[0], got[0])) if a != b)
        raise AssertionError(f"{label}: record byte {index:#x} rom {want[0][index]:#04x} model {got[0][index]:#04x}")
    return want[0]


def selftest(count: int, seed: int, chain: int = 6) -> None:
    rng = random.Random(seed)
    paths = {"restart": 0, "silence": 0, "predicted": 0}
    for trial in range(count):
        wild = trial % 4 == 3
        record = random_record(rng, wild)
        for step in range(chain):
            frame = random_frame(rng, 127 if step == 0 and trial % 2 == 0 else None)
            lag = struct.unpack_from("<H", frame)[0] >> 9
            paths["restart" if lag == 127 else "silence" if lag == 126 else "predicted"] += 1
            record = _compare(record, frame, f"trial {trial} frame {step}")
    total = sum(paths.values())
    print(f"random records: {total} frames in {count} chains byte-exact against the ROM routine "
          f"({paths['restart']} restart, {paths['silence']} silence, {paths['predicted']} predicted)")


def replay_capture(path: str) -> None:
    """Check a DeSmuME capture of a forced coding-1 call (record, frame, record after, output)."""
    manifest_path = Path(path)
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    base_dir = manifest_path.parent
    before = (base_dir / manifest["before_channel"]).read_bytes()
    frame = (base_dir / manifest["frame"]).read_bytes()
    after = (base_dir / manifest["after_channel"]).read_bytes()
    output = (base_dir / manifest["output"]).read_bytes()
    stride = int(manifest["stride"])
    record, samples, consumed = decode_frame(before, frame, int(manifest["channel"], 0))
    observed = [struct.unpack_from("<h", output, i * stride)[0] for i in range(128)]
    if record != after:
        index = next(i for i, (a, b) in enumerate(zip(record, after)) if a != b)
        raise AssertionError(f"capture: record byte {index:#x} model {record[index]:#04x} hardware {after[index]:#04x}")
    if samples != observed:
        raise AssertionError("capture: output samples differ from the hardware")
    if consumed != int(manifest["consumed"]):
        raise AssertionError(f"capture: consumed {consumed} bytes, the hardware {manifest['consumed']}")
    lag = struct.unpack_from("<H", frame)[0] >> 9
    print(f"{manifest_path.name}: lag {lag}, mode {record[INDICES + 3]}: record, 128 samples and "
          f"{consumed} consumed bytes match the hardware")


def capture_inputs(directory: Path, seed: int = 7) -> None:
    """Write the records and frames capture_mobiclip_kernels.lua feeds the forced calls."""
    rng = random.Random(seed)
    directory.mkdir(parents=True, exist_ok=True)
    for index, lag in enumerate((127, 37, 126)):
        record = bytearray(random_record(rng))
        struct.pack_into("<2I", record, 0, 0, 0)               # the script keeps the live pointers
        (directory / f"audio_transform_input_{index}.bin").write_bytes(bytes(record) + random_frame(rng, lag))
    print(f"wrote 3 inputs to {directory}")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--selftest", action="store_true")
    ap.add_argument("--capture", nargs="*", help="replay DeSmuME capture manifests (audio_transform_*.json)")
    ap.add_argument("--inputs", help="write the forced-call inputs for the capture script to this directory")
    ap.add_argument("--count", type=int, default=40)
    ap.add_argument("--seed", type=int, default=1)
    args = ap.parse_args()
    if args.inputs:
        capture_inputs(Path(args.inputs))
    if args.selftest:
        selftest(args.count, args.seed)
    for path in args.capture or []:
        replay_capture(path)


if __name__ == "__main__":
    main()
