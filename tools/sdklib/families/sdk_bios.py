"""NitroSDK BIOS call wrappers: the THUMB `swi` veneers in libs/nitro/os.

Each veneer is `swi #n` and `bx lr` (VBlankIntrWait first clears r2, Mod
moves the remainder into r0 afterwards), so the model of a veneer is the BIOS
function it reaches and the registers it passes. The BIOS itself is not part of
the ROM; the functions below describe what it does (GBATEK) closely enough to
replace a veneer with a host implementation, and serve as that port reference.

All eighteen veneers are THUMB code, run by arm_exec.py's THUMB path.
`veneer_cases` is their semantic gate: the SWI log (number, r0-r3) and the
registers, stack and (for Mod) flags after `bx lr`, with the BIOS left
unexecuted.

    python tools/sdklib/families/sdk_bios.py      # self-test the BIOS models
"""

from __future__ import annotations

import math
import struct

try:
    from verify_sdklib import STACK_TOP, Case
except ImportError:                     # run directly as a self-test
    STACK_TOP, Case = 0x023F0000, None

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_bios.md"
SOURCE = "libs/nitro/os/asm_stubs/auto/%s.c"
SAVED = tuple(0xB105_0400 + 0x11 * i for i in range(4, 13))      # sentinels for r4..r12


def _s32(value: int) -> int:
    value &= MASK
    return value - (1 << 32) if value >> 31 else value


# -- arithmetic -----------------------------------------------------------------------------
def bios_div(numerator: int, denominator: int) -> tuple[int, int, int]:
    """SWI 09h: (quotient, remainder, |quotient|) as r0, r1, r3; C99 truncating division.

    The BIOS does not return for a zero denominator, and the result for
    0x80000000 / -1 is not documented, so the model refuses both."""
    n, d = _s32(numerator), _s32(denominator)
    if d == 0:
        raise ValueError("Div by zero does not return")
    if n == -(1 << 31) and d == -1:
        raise ValueError("Div 0x80000000 / -1 is undocumented")
    q = abs(n) // abs(d) * (1 if (n < 0) == (d < 0) else -1)
    r = n - q * d
    return q & MASK, r & MASK, abs(q) & MASK


def bios_sqrt(value: int) -> int:
    """SWI 0Dh: floor(sqrt(r0)) of an unsigned 32-bit value, a 16-bit result in r0."""
    return math.isqrt(value & MASK)


def bios_crc16(initial: int, data: bytes) -> int:
    """SWI 0Eh: reflected CRC-16, polynomial 0xA001 (0x8005 bit-reversed), no final XOR."""
    crc = initial & 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if crc & 1 else crc >> 1
    return crc


# -- memory copy / fill ---------------------------------------------------------------------
def bios_cpu_set(mem: bytearray, src: int, dst: int, control: int) -> None:
    """SWI 0Bh on a flat byte image: bits 0-20 unit count, bit 24 fill, bit 26 32-bit units.

    Units go in ascending order; a fill repeats the unit at src."""
    count, fill, size = control & 0x1FFFFF, control >> 24 & 1, 4 if control >> 26 & 1 else 2
    if src % size or dst % size:
        raise ValueError("CpuSet needs %d-byte aligned addresses" % size)
    value = mem[src:src + size]
    for i in range(count):
        unit = value if fill else mem[src + i * size:src + i * size + size]
        mem[dst + i * size:dst + i * size + size] = unit


def bios_cpu_fast_set(mem: bytearray, src: int, dst: int, control: int) -> None:
    """SWI 0Ch: 32-bit units only, bits 0-20 word count, bit 24 fill; moved eight words at a time.

    Callers pass a multiple of 8; other counts are rounded up (GBATEK, GBA BIOS)."""
    count, fill = control & 0x1FFFFF, control >> 24 & 1
    if src % 4 or dst % 4:
        raise ValueError("CpuFastSet needs word-aligned addresses")
    bios_cpu_set(mem, src, dst, (-(-count // 8) * 8) | fill << 24 | 1 << 26)


# -- BitUnPack ------------------------------------------------------------------------------
def bios_bit_unpack(source: bytes, length: int, src_bits: int, dst_bits: int, offset_word: int) -> bytes:
    """SWI 10h: widen `length` bytes of src_bits-wide units (LSB first) to dst_bits-wide units.

    offset_word bits 0-30 are added to every non-zero unit, or to every unit when
    bit 31 is set. Output is packed LSB first into 32-bit words; only whole words
    are produced, and each result must fit dst_bits."""
    if src_bits not in (1, 2, 4, 8) or dst_bits not in (1, 2, 4, 8, 16, 32):
        raise ValueError("unit width")
    offset, zero_too = offset_word & 0x7FFFFFFF, offset_word >> 31
    words, acc, filled = bytearray(), 0, 0
    for byte in source[:length]:
        for shift in range(0, 8, src_bits):
            unit = byte >> shift & ((1 << src_bits) - 1)
            if unit or zero_too:
                unit += offset
            if unit >> dst_bits:
                raise ValueError("unit 0x%x overflows %d bits" % (unit, dst_bits))
            acc |= unit << filled
            filled += dst_bits
            if filled == 32:
                words += struct.pack("<I", acc)
                acc, filled = 0, 0
    return bytes(words)


# -- decompressors --------------------------------------------------------------------------
def header(stream: bytes, kind: int) -> int:
    """The 32-bit header: bits 4-7 the type, bits 8-31 the decompressed size in bytes."""
    word = struct.unpack_from("<I", stream)[0]
    if word >> 4 & 0xF != kind:
        raise ValueError("type %d, expected %d" % (word >> 4 & 0xF, kind))
    return word >> 8


def bios_lz77(stream: bytes, halfword_writes: bool = False) -> bytes:
    """SWI 11h/12h, type 1. A flag byte (MSB first) per eight tokens: 0 = literal byte,
    1 = two bytes, length-3 in bits 12-15, distance-1 in bits 0-11 (high nibble first).

    The 16-bit-write variant buffers byte pairs, so a reference to the byte just
    before the current one (distance 1) is not allowed there."""
    size, pos, out = header(stream, 1), 4, bytearray()
    while len(out) < size:
        flags = stream[pos]
        pos += 1
        for bit in range(8):
            if len(out) >= size:
                break
            if flags & 0x80 >> bit:
                hi, lo = stream[pos], stream[pos + 1]
                pos += 2
                length, distance = (hi >> 4) + 3, ((hi & 0xF) << 8 | lo) + 1
                if distance > len(out) or (halfword_writes and distance == 1):
                    raise ValueError("bad distance %d at output %d" % (distance, len(out)))
                for _ in range(length):
                    out.append(out[-distance])
            else:
                out.append(stream[pos])
                pos += 1
    return bytes(out[:size])


def bios_rl(stream: bytes) -> bytes:
    """SWI 14h/15h, type 3. Flag byte: bit 7 clear = (bits 0-6)+1 literal bytes follow;
    bit 7 set = one byte repeated (bits 0-6)+3 times."""
    size, pos, out = header(stream, 3), 4, bytearray()
    while len(out) < size:
        flag = stream[pos]
        pos += 1
        if flag & 0x80:
            out += bytes((stream[pos],)) * ((flag & 0x7F) + 3)
            pos += 1
        else:
            n = (flag & 0x7F) + 1
            out += stream[pos:pos + n]
            pos += n
    return bytes(out[:size])


def bios_huffman(stream: bytes) -> bytes:
    """SWI 13h, type 2; header bits 0-3 = symbol width (4 or 8 bits).

    Byte 4 is the tree size: (byte + 1) * 2 bytes of tree from offset 4, so the
    root node sits at offset 5 and the bitstream follows the tree. A node holds a
    6-bit offset and two end flags (bit 7 for child 0, bit 6 for child 1); its
    children are the pair at (node address & ~1) + offset * 2 + 2, and a child
    whose end flag is set is a symbol value, not a node. The bitstream is read in
    little-endian 32-bit words, most significant bit first (0 = child 0). Symbols
    are packed LSB first into 32-bit output words."""
    size, width = header(stream, 2), stream[0] & 0xF
    if width not in (4, 8):
        raise ValueError("symbol width %d" % width)
    bits_at = 4 + (stream[4] + 1) * 2
    out, acc, filled, node, word, left = bytearray(), 0, 0, 5, 0, 0
    while len(out) < size:
        if left == 0:
            word, left = struct.unpack_from("<I", stream, bits_at)[0], 32
            bits_at += 4
        left -= 1
        bit = word >> left & 1
        child = (node & ~1) + (stream[node] & 0x3F) * 2 + 2 + bit
        if stream[node] & (0x80 >> bit):
            acc |= stream[child] << filled
            filled += width
            if filled == 32:
                out += struct.pack("<I", acc)
                acc, filled = 0, 0
            node = 5
        else:
            node = child
    return bytes(out[:size])


# -- the veneers ----------------------------------------------------------------------------
# symbol: (THUMB swi number, r2 forced before the call, r0 <- r1 after it)
VENEERS = {
    "SoftReset": (0x00, None, False),
    "WaitByLoop": (0x03, None, False),
    "IntrWait": (0x04, None, False),
    "VBlankIntrWait": (0x05, 0, False),
    "Halt": (0x06, None, False),
    "Div": (0x09, None, False),
    "Mod": (0x09, None, True),
    "CpuSet": (0x0B, None, False),
    "CpuFastSet": (0x0C, None, False),
    "Sqrt": (0x0D, None, False),
    "GetCRC16": (0x0E, None, False),
    "IsDebugger": (0x0F, None, False),
    "BitUnPack": (0x10, None, False),
    "LZ77UnCompReadNormalWrite8bit": (0x11, None, False),
    "LZ77UnCompReadByCallbackWrite16bit": (0x12, None, False),
    "HuffUnCompReadByCallback": (0x13, None, False),
    "RLUnCompReadNormalWrite8bit": (0x14, None, False),
    "RLUnCompReadByCallbackWrite16bit": (0x15, None, False),
}


def veneer_cases(symbol: str):
    """One BIOS call with r0-r3 as passed (r2 cleared for VBlankIntrWait), nothing else
    touched, and after `bx lr` r0-r3 as the unexecuted BIOS left them (Mod: r0 = r1,
    with N and Z from it and C, V clear)."""
    number, forced_r2, remainder = VENEERS[symbol]

    def cases(rng):
        edges = [(0, 0, 0, 0), (MASK, MASK, MASK, MASK), (0x80000000, 1, 0x7FFFFFFF, 0x02380000)]
        for args in edges + [tuple(rng.getrandbits(32) for _ in range(4)) for _ in range(500)]:
            passed = args[:2] + ((args[2] if forced_r2 is None else forced_r2), args[3])
            after = ((passed[1],) + passed[1:]) if remainder else passed

            def check(cpu, passed=passed, after=after):
                log, cpu.swi_log[:] = list(cpu.swi_log), []        # the Cpu is shared by every case
                if log != [(number, passed)]:
                    return "SWI log %r, model %r" % (log, [(number, passed)])
                if tuple(cpu.r[0:4]) != after:
                    return "r0-r3 = %r after return, model %r" % (tuple(cpu.r[0:4]), after)
                if tuple(cpu.r[4:13]) != SAVED or cpu.r[13] != STACK_TOP:
                    return "r4-r12 or sp changed"
                return None

            flags = {"n": passed[1] >> 31, "z": int(passed[1] == 0), "c": 0, "v": 0} if remainder else {}
            yield Case(args + SAVED, flags=flags, check=check, label=symbol)

    return cases


if Case is None:
    ROUTINES = []
else:
    from verify_sdklib import Routine
    ROUTINES = [Routine(symbol, SOURCE % symbol, DOC, veneer_cases(symbol)) for symbol in VENEERS]


# -- self-test of the models ----------------------------------------------------------------
def _rl_compress(data: bytes) -> bytes:
    out, i, literal = bytearray(struct.pack("<I", 0x30 | len(data) << 8)), 0, bytearray()

    def flush():
        while literal:
            chunk = literal[:128]
            out.append(len(chunk) - 1)
            out.extend(chunk)
            del literal[:128]

    while i < len(data):
        run = 1
        while i + run < len(data) and run < 130 and data[i + run] == data[i]:
            run += 1
        if run >= 3:
            flush()
            out += bytes((0x80 | (run - 3), data[i]))
            i += run
        else:
            literal.append(data[i])
            i += 1
    flush()
    return bytes(out)


def _huffman_compress(data: bytes, width: int) -> bytes:
    """A balanced tree laid out breadth first, so every child offset fits 6 bits."""
    symbols = [b >> s & ((1 << width) - 1) for b in data for s in range(0, 8, width)]
    alphabet = sorted(set(symbols)) or [0]
    if len(alphabet) == 1:
        alphabet.append(alphabet[0] ^ 1)
    table, queue, codes = bytearray(2), [(alphabet, 1, "")], {}       # root at stream offset 5
    while queue:
        group, at, code = queue.pop(0)
        half = len(group) // 2
        pair = len(table)
        table += b"\0\0"
        offset = (pair - (at & ~1) - 2) // 2
        if offset > 0x3F:
            raise ValueError("tree too wide for the self-test encoder")
        flags = 0
        for k, part in enumerate((group[:half], group[half:])):
            if len(part) == 1:
                flags |= 0x80 >> k
                table[pair + k] = part[0]
                codes[part[0]] = code + str(k)
            else:
                queue.append((part, pair + k, code + str(k)))
        table[at] = offset | flags
    if len(table) % 2:
        table += b"\0"
    while (len(table)) % 4:
        table += b"\0\0"
    table[0] = len(table) // 2 - 1
    bits = "".join(codes[s] for s in symbols)
    bits += "0" * (-len(bits) % 32)
    stream = struct.pack("<I", 0x20 | width | len(data) << 8) + bytes(table)
    for i in range(0, len(bits), 32):
        stream += struct.pack("<I", int(bits[i:i + 32], 2))
    return stream


def self_test() -> None:
    import random
    import sys
    from pathlib import Path
    sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
    from families.sdk_misc import lz_compress
    rng = random.Random(0xB105)
    assert bios_div(-1234, 10) == ((-123) & MASK, (-4) & MASK, 123)          # GBATEK's example
    assert bios_sqrt(2) == 1 and bios_sqrt(MASK) == 0xFFFF
    assert bios_crc16(0xFFFF, b"123456789") == 0x4B37                         # CRC-16/MODBUS check
    for _ in range(300):
        data = bytes(rng.choice(b"aab\0\0\0xyz") for _ in range(rng.randrange(1, 600)))
        lz = struct.pack("<I", 0x10 | len(data) << 8) + lz_compress(data, False, rng)
        assert bios_lz77(lz) == data
        assert bios_rl(_rl_compress(data)) == data
        whole = data[:len(data) // 4 * 4] or b"abcd"
        for width in (4, 8):
            assert bios_huffman(_huffman_compress(whole, width)) == whole
    assert bios_bit_unpack(b"\x1b", 1, 2, 8, 0) == bytes((3, 2, 1, 0))
    assert bios_bit_unpack(b"\x1b", 1, 2, 8, 0x80000010) == bytes((0x13, 0x12, 0x11, 0x10))
    mem = bytearray(range(64)) + bytearray(64)
    bios_cpu_set(mem, 0, 64, 5)
    assert mem[64:74] == bytes(range(10)) and mem[74] == 0
    bios_cpu_fast_set(mem, 4, 64, 1 << 24 | 3)
    assert mem[64:96] == bytes((4, 5, 6, 7)) * 8
    print("sdk_bios models: self-test passed (%d veneers)" % len(VENEERS))


if __name__ == "__main__":
    self_test()
