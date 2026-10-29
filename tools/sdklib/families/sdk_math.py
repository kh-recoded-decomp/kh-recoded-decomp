"""NitroSDK math routines written in assembly: MATHi_SHA1ProcessBlock and MATH_QSort.

MATHi_SHA1ProcessBlock is the SHA-1 compression function (FIPS 180-4, 6.1.2)
applied to the chaining value and the 64-byte block held in a SHA-1 context.
The model below is that compression written from the standard and checked
against hashlib on whole messages; the ROM is also run block after block over
padded messages and its final chaining value must equal hashlib's digest.

MATH_QSort sorts `num` elements of `width` bytes in place with a caller's
three-way comparison callback. It is an unstable quicksort, so the model is
Python's sort with the same comparator and only properties every correct sort
shares are checked: the result is a permutation of the input whose keys are in
order, and it equals Python's order exactly when all keys are distinct. The
callbacks are small ARM comparators written into scratch memory.
"""

import hashlib
import struct
from functools import cmp_to_key

from verify_sdklib import SCRATCH, STACK_TOP, Case, Routine

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_math.md"
SAVED = tuple(0xC0DE0400 + 0x11 * i for i in range(4, 13))      # sentinels for r4..r12


def poke(mem, address: int, data: bytes) -> None:
    buf, off = mem._find(address, len(data))
    buf[off:off + len(data)] = data


def preserved(cpu, first=4, last=12):
    if cpu.r[first:last + 1] != list(SAVED[:last - first + 1]):
        return "callee-saved r%d-r%d changed" % (first, last)
    if cpu.r[13] != STACK_TOP:
        return "sp = 0x%08x after return" % cpu.r[13]
    return None


# -- SHA-1 -------------------------------------------------------------------------------

SHA1_K = (0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6)
SHA1_IV = (0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0)
SHA1_ROUND_CONSTANTS = 0x0200ded4      # MATHi_SHA1RoundConstants, the four words before the routine
CTX_BLOCK = 0x14                        # context: u32 h[5], then u8 block[64]


def rotl(value: int, count: int) -> int:
    return ((value << count) | (value >> (32 - count))) & MASK


def sha1_compress(h: tuple, block: bytes) -> tuple:
    """One SHA-1 compression: the new chaining value after a 64-byte block."""
    w = list(struct.unpack(">16I", block))
    for t in range(16, 80):
        w.append(rotl(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1))
    a, b, c, d, e = h
    for t in range(80):
        if t < 20:
            f = (b & c) | (~b & d)
        elif t < 40:
            f = b ^ c ^ d
        elif t < 60:
            f = (b & c) | (b & d) | (c & d)
        else:
            f = b ^ c ^ d
        temp = (rotl(a, 5) + f + e + SHA1_K[t // 20] + w[t]) & MASK
        a, b, c, d, e = temp, a, rotl(b, 30), c, d
    return tuple((x + y) & MASK for x, y in zip(h, (a, b, c, d, e)))


def sha1_blocks(message: bytes) -> list:
    padded = message + b"\x80" + b"\0" * ((55 - len(message)) % 64) + struct.pack(">Q", 8 * len(message))
    return [padded[i:i + 64] for i in range(0, len(padded), 64)]


def sha1(message: bytes) -> bytes:
    h = SHA1_IV
    for block in sha1_blocks(message):
        h = sha1_compress(h, block)
    return struct.pack(">5I", *h)


def sha1_case(ctx: int, h: tuple, block: bytes, write_h: bool, label: str, digest: bytes | None = None):
    expected = sha1_compress(h, block)

    def setup(mem):
        if write_h:
            poke(mem, ctx, struct.pack("<5I", *h))
        poke(mem, ctx + CTX_BLOCK, block)

    def check(cpu):
        got = struct.unpack("<5I", cpu.mem.bytes(ctx, 20))
        if got != expected:
            return "h = %s, model %s" % (["%08x" % v for v in got], ["%08x" % v for v in expected])
        if cpu.mem.bytes(ctx + CTX_BLOCK, 64) != block:
            return "the context's block was modified"
        if digest is not None and struct.pack(">5I", *got) != digest:
            return "chained digest differs from hashlib"
        return preserved(cpu)
    return Case((ctx, 0, 0, 0) + SAVED, regs={0: ctx}, setup=setup, check=check, label=label)


def sha1_cases(rng):
    lengths = list(range(0, 130)) + [183, 184, 191, 192, 255, 256, 1000, 4095]
    lengths += [rng.randrange(1, 5000) for _ in range(40)]
    for n in lengths:                                   # model against hashlib on whole messages
        message = rng.randbytes(n)
        if sha1(message) != hashlib.sha1(message).digest():
            raise AssertionError("SHA-1 model differs from hashlib for a %d-byte message" % n)
    for i, n in enumerate((0, 1, 3, 55, 56, 63, 64, 65, 119, 120, 128, 300, 1000)):
        message = rng.randbytes(n) if i % 2 else bytes(n)
        ctx = SCRATCH + 4 * i
        h = SHA1_IV
        blocks = sha1_blocks(message)
        for j, block in enumerate(blocks):              # the ROM chains its own output
            last = j == len(blocks) - 1
            yield sha1_case(ctx, h, block, j == 0, "message %d block %d" % (n, j),
                            hashlib.sha1(message).digest() if last else None)
            h = sha1_compress(h, block)
    edges = (bytes(64), b"\xff" * 64, bytes(range(64)), b"\x80" + bytes(63))
    for block in edges:
        for h in (SHA1_IV, (0,) * 5, (MASK,) * 5):
            yield sha1_case(SCRATCH, h, block, True, "edge")
    for _ in range(1500):
        h = tuple(rng.getrandbits(32) for _ in range(5))
        yield sha1_case(SCRATCH + 4 * rng.randrange(256), h, rng.randbytes(64), True, "random")


# -- MATH_QSort --------------------------------------------------------------------------

COMPARATOR = SCRATCH + 0xF000
STACK_BUF = SCRATCH + 0xE000
ARRAY = SCRATCH + 0x100
GUARD = 32
# int cmp(void *a, void *b) { return *(u8 *)a - *(u8 *)b; }
BYTE_COMPARATOR = (0xE5D02000, 0xE5D13000, 0xE0420003, 0xE12FFF1E)
# int cmp(void *a, void *b) { s32 x = *(s32 *)a, y = *(s32 *)b; return x < y ? -1 : x > y; }
WORD_COMPARATOR = (0xE5902000, 0xE5913000, 0xE1520003, 0xB3E00000, 0x03A00000, 0xC3A00001, 0xE12FFF1E)


def byte_key(element: bytes) -> int:
    return element[0]


def word_key(element: bytes) -> int:
    return struct.unpack("<i", element[:4])[0]


def qsort_model(elements: list, key) -> list:
    """What MATH_QSort promises: the elements ordered by the comparator."""
    return sorted(elements, key=cmp_to_key(lambda a, b: key(a) - key(b)))


def qsort_stack_size(num: int) -> int:
    """A caller buffer of (ilog2(num) + 2) pointer pairs; the routine needs bitlen(num) pairs."""
    return ((num.bit_length() - 1) + 2) * 8


def qsort_case(rng, elements: list, width: int, misalign: int, comparator: str, use_buffer: bool, label: str):
    num = len(elements)
    head = ARRAY + misalign
    key = word_key if comparator == "word" else byte_key
    code = WORD_COMPARATOR if comparator == "word" else BYTE_COMPARATOR
    image = b"".join(elements)
    guard_before, guard_after = rng.randbytes(GUARD), rng.randbytes(GUARD)
    buffer_size = qsort_stack_size(num) if num > 1 else 0
    buffer_guard = rng.randbytes(GUARD)
    expected = qsort_model(elements, key)
    distinct = len({key(e) for e in elements}) == num

    def setup(mem):
        poke(mem, COMPARATOR, struct.pack("<%dI" % len(code), *code))
        poke(mem, head - GUARD, guard_before + image + guard_after)
        poke(mem, STACK_TOP, struct.pack("<I", STACK_BUF if use_buffer else 0))
        poke(mem, STACK_BUF + buffer_size, buffer_guard)

    def check(cpu):
        got = cpu.mem.bytes(head - GUARD, 2 * GUARD + len(image))
        if got[:GUARD] != guard_before or got[GUARD + len(image):] != guard_after:
            return "wrote outside the array"
        result = [got[GUARD + i * width:GUARD + (i + 1) * width] for i in range(num)]
        if distinct:
            if result != expected:
                return "order differs from the model"
        else:
            if sorted(result) != sorted(elements):
                return "result is not a permutation of the input"
            if [key(e) for e in result] != [key(e) for e in expected]:
                return "keys are not in order"
        if use_buffer and cpu.mem.bytes(STACK_BUF + buffer_size, GUARD) != buffer_guard:
            return "overran MATH_QSortStackSize(%d) bytes of stack buffer" % num
        return preserved(cpu, 4, 11)
    args = (head, num, width, COMPARATOR) + SAVED[:8]
    return Case(args, setup=setup, check=check, label=label)


def random_elements(rng, num: int, width: int, comparator: str, distinct: bool) -> list:
    if comparator == "word":
        keys = rng.sample(range(-(1 << 31), 1 << 31), num) if distinct else \
            [rng.choice((-(1 << 31), -1, 0, 1, (1 << 31) - 1, rng.randrange(-3, 4))) for _ in range(num)]
        return [struct.pack("<i", k) + rng.randbytes(width - 4) for k in keys]
    keys = rng.sample(range(256), num) if distinct else [rng.randrange(4) for _ in range(num)]
    return [bytes([k]) + rng.randbytes(width - 1) for k in keys]


def qsort_cases(rng):
    for raw_num in (0, 1, 0x80000000, MASK):            # num <= 1 as a signed value: nothing happens
        yield Case((ARRAY, raw_num, 4, COMPARATOR) + SAVED[:8],
                   setup=lambda mem: poke(mem, STACK_TOP, b"\0\0\0\0"),
                   check=lambda cpu: preserved(cpu, 4, 11), label="num %#x" % raw_num)
    yield Case((ARRAY, 5, 0, COMPARATOR) + SAVED[:8], setup=qsort_case(rng, [b"\x00"], 1, 0, "byte", False, "").setup,
               check=lambda cpu: preserved(cpu, 4, 11), label="width 0")
    for width in (1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20):
        for num in range(0, 65):
            for comparator in ("byte", "word") if width >= 4 and width % 4 == 0 else ("byte",):
                misalign = 0 if width % 4 == 0 else rng.randrange(4)
                for distinct in (True, False):
                    elements = random_elements(rng, num, width, comparator, distinct)
                    yield qsort_case(rng, elements, width, misalign, comparator, rng.random() < 0.5,
                                     "width %d num %d %s %s" % (width, num, comparator,
                                                                 "distinct" if distinct else "repeats"))
    patterns = {"sorted": lambda n: list(range(n)), "reversed": lambda n: list(range(n))[::-1],
                "equal": lambda n: [7] * n, "organ": lambda n: list(range(n // 2)) + list(range(n // 2, -1, -1))}
    for name, pattern in patterns.items():
        for num in (2, 3, 16, 100, 200, 256):
            elements = [bytes([k & 0xFF, i & 0xFF, i >> 8]) for i, k in enumerate(pattern(num))]
            yield qsort_case(rng, elements, 3, 1, "byte", True, "%s %d" % (name, num))
            words = [struct.pack("<iI", k, i) for i, k in enumerate(pattern(num))]
            yield qsort_case(rng, words, 8, 0, "word", False, "%s %d words" % (name, num))
    for _ in range(200):
        width = rng.choice((1, 2, 3, 4, 8, 12))
        comparator = "word" if width % 4 == 0 and rng.random() < 0.7 else "byte"
        distinct = rng.random() < 0.5
        num = rng.randrange(2, 257)
        elements = random_elements(rng, num, width, comparator, distinct)
        yield qsort_case(rng, elements, width, 0 if width % 4 == 0 else rng.randrange(4), comparator,
                         rng.random() < 0.5, "random width %d num %d" % (width, num))


ROUTINES = [
    Routine("MATHi_SHA1ProcessBlock", "src/asm_stubs/calls/MATHi_SHA1ProcessBlock.c", DOC, sha1_cases),
    Routine("func_0200dc4c", "libs/nitro/math/asm_stubs/auto/func_0200dc4c.c", DOC, qsort_cases),
]
