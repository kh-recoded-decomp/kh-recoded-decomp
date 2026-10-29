"""CodeWarrior 64-bit division helpers (_ll_udiv, _ull_mod, _ll_sdiv, _ll_mod).

The compiler calls these for `/` and `%` on 64-bit integers. The dividend
arrives in r0:r1 and the divisor in r2:r3 (low word first); the quotient or
the remainder comes back in r0:r1. The model is C99 integer division on 64-bit
two's-complement values with the routines' three departures from C: a zero
divisor returns the dividend unchanged, INT64_MIN / -1 wraps to INT64_MIN, and
a signed division whose operands both fit in 32 bits goes through the 32-bit
helper, so INT32_MIN / -1 returns INT32_MIN sign-extended (not +2**31).
"""

from verify_sdklib import STACK_TOP, Case, Routine

MASK64 = (1 << 64) - 1
DOC = "docs/library/msl_div64.md"
SOURCE = "libs/msl/c/asm_stubs/calls/%s.s"
SAVED = tuple(0xC0DE0400 + 0x11 * i for i in range(4, 12))       # sentinels for r4..r11
DEAD_CODE = ((0x02023d28, 0x02023d30),)                          # unreachable `lsr r0, r1, r7; mov r1, #0`
EDGE32 = (0, 1, 2, 3, 7, 10, 0xFFFF, 0x10000, 0x7FFFFFFF, 0x80000000, 0x80000001, 0xFFFFFFFE, 0xFFFFFFFF)


def signed(value: int) -> int:
    value &= MASK64
    return value - (1 << 64) if value >> 63 else value


def fits_s32(value: int) -> bool:
    return -(1 << 31) <= signed(value) < (1 << 31)


def unsigned_divide(dividend: int, divisor: int, want_remainder: bool) -> int:
    """u64 `/` or `%`; a zero divisor returns the dividend."""
    if divisor == 0:
        return dividend
    return dividend % divisor if want_remainder else dividend // divisor


def signed_divide(dividend: int, divisor: int, want_remainder: bool) -> int:
    """s64 `/` or `%`, truncating toward zero, remainder takes the dividend's sign."""
    if divisor == 0:
        return dividend
    a, b = signed(dividend), signed(divisor)
    quotient = abs(a) // abs(b)
    if (a < 0) != (b < 0):
        quotient = -quotient
    remainder = a - quotient * b
    if fits_s32(dividend) and fits_s32(divisor) and not want_remainder:
        quotient = ((quotient & 0xFFFFFFFF) ^ 0x80000000) - 0x80000000     # 32-bit helper wraps
    return (remainder if want_remainder else quotient) & MASK64


def operand_pairs(rng):
    edges = set()
    for lo in EDGE32:
        for hi in (0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF):
            edges.add(hi << 32 | lo)
    edges = sorted(edges)
    for a in edges:
        for b in edges:
            yield a, b
    for bits in range(1, 65):
        for _ in range(30):
            a = rng.getrandbits(64)
            b = rng.getrandbits(bits) | (1 << (bits - 1))
            yield a, b
            yield b, a
            yield a >> rng.randrange(64), b
    for _ in range(2000):
        yield rng.getrandbits(rng.randrange(1, 65)), rng.getrandbits(rng.randrange(1, 65))


def preserved(cpu):
    if cpu.r[4:12] != list(SAVED):
        return "callee-saved r4-r11 changed: %s" % ["0x%08x" % v for v in cpu.r[4:12]]
    if cpu.r[13] != STACK_TOP:
        return "sp = 0x%08x after return" % cpu.r[13]
    return None


def make_cases(model, want_remainder: bool, signed_variants: bool):
    def cases(rng):
        for a, b in operand_pairs(rng):
            variants = ((a, b), ((-a) & MASK64, b), (a, (-b) & MASK64)) if signed_variants else ((a, b),)
            for x, y in variants:
                result = model(x, y, want_remainder)
                args = (x & 0xFFFFFFFF, x >> 32, y & 0xFFFFFFFF, y >> 32) + SAVED
                yield Case(args, regs={0: result & 0xFFFFFFFF, 1: result >> 32}, check=preserved,
                           label="%#x %s %#x" % (x, "%" if want_remainder else "/", y))
    return cases


# _ll_udiv is a 72-byte func_index entry spanning _ull_mod, so the entries
# check their branches into the shared body against the ROM image instead.
ROUTINES = [
    Routine("_ll_udiv", SOURCE % "_ll_udiv", DOC, make_cases(unsigned_divide, False, False), object_gate=True),
    Routine("_ull_mod", SOURCE % "_ull_mod", DOC, make_cases(unsigned_divide, True, False), object_gate=True),
    Routine("_ll_sdiv", SOURCE % "_ll_sdiv", DOC, make_cases(signed_divide, False, True), unreachable=DEAD_CODE),
    Routine("_ll_mod", SOURCE % "_ll_mod", DOC, make_cases(signed_divide, True, True), object_gate=True),
]
