"""CodeWarrior 32-bit division helpers (_u32_div_f, _s32_div_f).

The compiler calls these for `/` and `%` on 32-bit integers. Both return the
quotient in r0 and the remainder in r1.
"""

from verify_sdklib import Case, Routine

MASK = 0xFFFFFFFF
DOC = "docs/library/msl_runtime.md"
EDGES = (0, 1, 2, 3, 7, 10, 0xFF, 0x100, 0xFFFF, 0x10000, 0x7FFFFFFF, 0x80000000, 0x80000001, 0xFFFFFFFE, MASK)


def unsigned_divide(dividend: int, divisor: int) -> tuple[int, int]:
    """A zero divisor returns the dividend and a zero remainder."""
    if divisor == 0:
        return dividend, 0
    return dividend // divisor, dividend % divisor


def signed_divide(dividend: int, divisor: int) -> tuple[int, int]:
    """Truncating division on two's-complement words; a zero divisor returns the dividend."""
    negative_dividend = dividend >> 31
    magnitude = (-dividend) & MASK if negative_dividend else dividend
    divisor_magnitude = (-divisor) & MASK if divisor >> 31 else divisor
    quotient, remainder = unsigned_divide(magnitude, divisor_magnitude)
    if (dividend ^ divisor) >> 31:
        quotient = -quotient
    if negative_dividend:
        remainder = -remainder
    return quotient & MASK, remainder & MASK


def operand_pairs(rng):
    for a in EDGES:
        for b in EDGES:
            yield a, b
    for bits in range(1, 33):
        for _ in range(40):
            a = rng.getrandbits(32)
            b = rng.getrandbits(bits) | (1 << (bits - 1))
            yield a, b
            yield b, a
    for _ in range(2000):
        yield rng.getrandbits(32), rng.getrandbits(rng.randrange(1, 33))


def unsigned_cases(rng):
    for a, b in operand_pairs(rng):
        q, r = unsigned_divide(a, b)
        yield Case((a, b), regs={0: q, 1: r})


def signed_cases(rng):
    for a, b in operand_pairs(rng):
        for sa, sb in ((a, b), ((-a) & MASK, b), (a, (-b) & MASK)):
            q, r = signed_divide(sa, sb)
            yield Case((sa, sb), regs={0: q, 1: r})


ROUTINES = [
    Routine("_u32_div_f", "libs/msl/c/asm_stubs/calls/_u32_div_f.s", DOC, unsigned_cases),
    Routine("_s32_div_f", "libs/msl/c/asm_stubs/calls/_s32_div_f.s", DOC, signed_cases),
]
