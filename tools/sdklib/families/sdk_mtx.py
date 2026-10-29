"""NitroSDK matrix helpers: identity, 4x3/4x4 conversion, X/Y rotation, 36-byte clear.

Matrices are row-major arrays of fx32 (s32 fixed point, 1.0 = 0x1000):
MtxFx22 is 2x2, MtxFx33 3x3, MtxFx43 four rows of three (the 3x3 linear
part, then the translation row), MtxFx44 4x4. Each model builds the matrix as
a list of rows the way C code would assign the elements. Every case fills a
512-byte window at SCRATCH with random bytes, runs the routine on a matrix
inside it, and compares the whole window, so a store outside the matrix (a
guard byte) is caught; r4-r11 and sp must come back unchanged.
"""

from arm_exec import Memory
from verify_sdklib import SCRATCH, STACK_TOP, Case, Routine

MASK = 0xFFFFFFFF
ONE = 0x1000
DOC = "docs/library/sdk_mtx.md"
SOURCE = "libs/nitro/mtx/asm_stubs/auto/%s.c"
WINDOW = 0x200
SAVED = tuple(0x5EED_0400 + 0x11 * i for i in range(4, 12))      # sentinels for r4..r11
EDGES = (0, 1, ONE, (-ONE) & MASK, 0x7FFFFFFF, 0x80000000, MASK, 0xB50, (-0xB50) & MASK)


# -- models ---------------------------------------------------------------------
def identity(rows: int, cols: int) -> list:
    """1.0 on the diagonal, 0 elsewhere; a 4x3 matrix gets a zero translation row."""
    return [[ONE if r == c else 0 for c in range(cols)] for r in range(rows)]


def copy43_to44(m43: list) -> list:
    """Append the fourth column (0, 0, 0, 1.0): the affine 4x3 matrix as a full 4x4."""
    return [row + [ONE if r == 3 else 0] for r, row in enumerate(m43)]


def copy44_to43(m44: list) -> list:
    """Drop the fourth column, whatever it holds."""
    return [row[:3] for row in m44]


def rot_x43(sin: int, cos: int) -> list:
    """Rotation about X by the angle whose sine and cosine are given; zero translation."""
    return [[ONE, 0, 0], [0, cos, sin], [0, -sin, cos], [0, 0, 0]]


def rot_y43(sin: int, cos: int) -> list:
    """Rotation about Y; zero translation."""
    return [[cos, 0, -sin], [0, ONE, 0], [sin, 0, cos], [0, 0, 0]]


def zero36() -> list:
    """Nine zero words: a cleared MtxFx33 (or any 36 bytes)."""
    return [[0] * 3 for _ in range(3)]


# -- case plumbing --------------------------------------------------------------
def to_bytes(matrix: list) -> bytes:
    return b"".join((v & MASK).to_bytes(4, "little") for row in matrix for v in row)


def from_bytes(data: bytes, rows: int, cols: int) -> list:
    words = [int.from_bytes(data[i:i + 4], "little") for i in range(0, len(data), 4)]
    return [words[r * cols:(r + 1) * cols] for r in range(rows)]


def window_case(rng, args, expect, label):
    """Random window, routine run, whole window compared with `expect(window)`."""
    before = bytearray(rng.randbytes(WINDOW))
    after = bytearray(before)
    expect(after)

    def setup(mem: Memory) -> None:
        buf, off = mem._find(SCRATCH, WINDOW)
        buf[off:off + WINDOW] = before

    def check(cpu) -> str | None:
        got = cpu.mem.bytes(SCRATCH, WINDOW)
        if got != after:
            bad = next(i for i in range(WINDOW) if got[i] != after[i])
            return "byte at +0x%x = 0x%02x, model 0x%02x" % (bad, got[bad], after[bad])
        if tuple(cpu.r[4:12]) != SAVED or cpu.r[13] != STACK_TOP:
            return "r4-r11 or sp changed"
        return None

    return Case(tuple(args) + (0,) * (4 - len(args)) + SAVED, setup=setup, check=check, label=label)


def offsets(rng, size, count=200):
    """Word-aligned matrix offsets in the window: both ends first, then random ones."""
    last = (WINDOW - size) // 4
    yield 0
    yield 4 * last
    for _ in range(count):
        yield 4 * rng.randrange(last + 1)


def store_cases(make, rows, cols):
    """Routines that only write a matrix built from (sin, cos)."""
    size = 4 * rows * cols

    def cases(rng):
        pairs = [(s, c) for s in EDGES for c in EDGES]
        edge_count = len(pairs)
        pairs += [(rng.getrandbits(32), rng.getrandbits(32)) for _ in range(1000)]
        for k, (s, c) in enumerate(pairs):
            for dst in offsets(rng, size, 1) if k < edge_count else [4 * rng.randrange((WINDOW - size) // 4 + 1)]:
                image = to_bytes(make(_s32(s), _s32(c)))

                def expect(window, dst=dst, image=image):
                    window[dst:dst + size] = image

                yield window_case(rng, (SCRATCH + dst, s, c), expect, "dst +0x%x" % dst)

    return cases


def _s32(value: int) -> int:
    value &= MASK
    return value - (1 << 32) if value >> 31 else value


def fixed_cases(make, rows, cols):
    """Routines that write a constant matrix (identity, zero)."""
    size = 4 * rows * cols
    image = to_bytes(make())

    def cases(rng):
        for dst in offsets(rng, size, 300):
            def expect(window, dst=dst):
                window[dst:dst + size] = image

            yield window_case(rng, (SCRATCH + dst,), expect, "dst +0x%x" % dst)

    return cases


def convert_cases(convert, src_shape, dst_shape, in_place=False):
    """Routines that read one matrix and write another; disjoint buffers (and dst == src)."""
    src_size = 4 * src_shape[0] * src_shape[1]
    dst_size = 4 * dst_shape[0] * dst_shape[1]

    def cases(rng):
        placements = []
        for _ in range(400):
            src = 4 * rng.randrange((WINDOW - src_size) // 4 + 1)
            dst = 4 * rng.randrange((WINDOW - dst_size) // 4 + 1)
            if src + src_size <= dst or dst + dst_size <= src:
                placements.append((src, dst))
        placements[:0] = [(0, WINDOW - dst_size), (WINDOW - src_size, 0)]
        if in_place:
            placements += [(4 * k, 4 * k) for k in range(0, (WINDOW - src_size) // 4 + 1, 7)]
        for src, dst in placements:
            def expect(window, src=src, dst=dst):
                matrix = from_bytes(bytes(window[src:src + src_size]), *src_shape)
                window[dst:dst + dst_size] = to_bytes(convert(matrix))

            yield window_case(rng, (SCRATCH + src, SCRATCH + dst), expect, "src +0x%x dst +0x%x" % (src, dst))

    return cases


ROUTINES = [
    Routine("MTX_Identity22_", SOURCE % "MTX_Identity22_", DOC, fixed_cases(lambda: identity(2, 2), 2, 2)),
    Routine("MTX_Identity33_", SOURCE % "MTX_Identity33_", DOC, fixed_cases(lambda: identity(3, 3), 3, 3)),
    Routine("MTX_Identity43_", SOURCE % "MTX_Identity43_", DOC, fixed_cases(lambda: identity(4, 3), 4, 3)),
    Routine("MTX_Identity44_", SOURCE % "MTX_Identity44_", DOC, fixed_cases(lambda: identity(4, 4), 4, 4)),
    Routine("MTX_Copy43To44_", SOURCE % "MTX_Copy43To44_", DOC, convert_cases(copy43_to44, (4, 3), (4, 4))),
    Routine("MTX_Copy44To43_", SOURCE % "MTX_Copy44To43_", DOC,
            convert_cases(copy44_to43, (4, 4), (4, 3), in_place=True)),
    Routine("MTX_RotX43_", SOURCE % "MTX_RotX43_", DOC, store_cases(rot_x43, 4, 3)),
    Routine("MTX_RotY43_", SOURCE % "MTX_RotY43_", DOC, store_cases(rot_y43, 4, 3)),
    Routine("MI_Zero36B", "libs/nitro/mi/asm_stubs/auto/MI_Zero36B.c", DOC, fixed_cases(zero36, 3, 3)),
]
