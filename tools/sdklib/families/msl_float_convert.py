"""CodeWarrior soft-float compares and conversions (ARM fplib).

The compiler calls these for float/double comparisons and casts. Compares
return their answer in r0 and in the condition flags (written with
`msr CPSR_f`); conversions return a word in r0 or a pair in r0:r1 (low word
first). Floats travel as raw IEEE-754 bit patterns.
"""

import math
import struct

from verify_sdklib import Case, Routine

MASK = 0xFFFFFFFF
DOC = "docs/library/msl_float_convert.md"
INT_MIN, INT_MAX = -(1 << 31), (1 << 31) - 1
LL_MIN, LL_MAX = -(1 << 63), (1 << 63) - 1
CANONICAL_NAN32 = 0x7FFFFFFF
CANONICAL_NAN64 = (0xFFFFFFFF, 0x7FFFFFFF)

FLOAT_EDGES = (
    0x00000000, 0x00000001, 0x00000002, 0x007FFFFF, 0x00800000, 0x00800001, 0x33800000, 0x3EFFFFFF,
    0x3F000000, 0x3F000001, 0x3F7FFFFF, 0x3F800000, 0x3F800001, 0x3FC00000, 0x40000000, 0x40200000,
    0x40400000, 0x4B000000, 0x4B7FFFFF, 0x4B800000, 0x4EFFFFFF, 0x4F000000, 0x4F000001, 0x4F7FFFFF,
    0x4F800000, 0x5E800000, 0x5EFFFFFF, 0x5F000000, 0x5F000001, 0x7F7FFFFF, 0x7F800000, 0x7F800001,
    0x7FC00000, 0x7FFFFFFF)
FLOAT_EDGES = FLOAT_EDGES + tuple(b | 0x80000000 for b in FLOAT_EDGES)

DOUBLE_EDGE_HIGHS = (
    0x00000000, 0x00000001, 0x000FFFFF, 0x00100000, 0x36900000, 0x36A00000, 0x36A00001, 0x36AFFFFF,
    0x37900000, 0x37A00000, 0x37FFFFFF, 0x38000000, 0x380FFFFF, 0x38100000, 0x3FE00000, 0x3FEFFFFF,
    0x3FF00000, 0x3FF80000, 0x41DFFFFF, 0x41E00000, 0x41EFFFFF, 0x41F00000, 0x47EFFFFF, 0x47F00000,
    0x7FEFFFFF, 0x7FF00000, 0x7FF00001, 0x7FF80000, 0x7FFFFFFF)
DOUBLE_EDGE_LOWS = (0x00000000, 0x00000001, 0x0FFFFFFF, 0x10000000, 0x10000001, 0x20000000, 0x80000000, MASK)
DOUBLE_EDGES = tuple((lo, hi | sign) for hi in DOUBLE_EDGE_HIGHS for lo in DOUBLE_EDGE_LOWS
                     for sign in (0, 0x80000000))


# -- IEEE-754 helpers ---------------------------------------------------------
def single(bits: int) -> float:
    return struct.unpack("<f", struct.pack("<I", bits & MASK))[0]


def double(lo: int, hi: int) -> float:
    return struct.unpack("<d", struct.pack("<II", lo & MASK, hi & MASK))[0]


def double_words(value: float) -> tuple[int, int]:
    return struct.unpack("<II", struct.pack("<d", value))


def is_nan32(bits: int) -> bool:
    return (bits & 0x7FFFFFFF) > 0x7F800000


def is_nan64(lo: int, hi: int) -> bool:
    return math.isnan(double(lo, hi))


def round_to_single(value: int) -> int:
    """Round an integer to the nearest single, ties to even."""
    sign = 0x80000000 if value < 0 else 0
    magnitude = abs(value)
    if magnitude == 0:
        return 0
    exponent = magnitude.bit_length() - 1
    extra = exponent - 23
    if extra > 0:
        rest = magnitude & ((1 << extra) - 1)
        significand = magnitude >> extra
        half = 1 << (extra - 1)
        if rest > half or (rest == half and significand & 1):
            significand += 1
            if significand == 1 << 24:
                significand >>= 1
                exponent += 1
    else:
        significand = magnitude << -extra
    return sign | ((exponent + 127) << 23) | (significand & 0x7FFFFF)


def saturate_trunc(value: float, low: int, high: int) -> int:
    """Truncate toward zero, clamping out-of-range values (and infinities) to the limits."""
    if math.isinf(value):
        return high if value > 0 else low
    return max(low, min(high, math.trunc(value)))


def compare_flags(x: int, y: int) -> dict:
    """The N, Z, C, V a 32-bit `cmp x, y` leaves."""
    x &= MASK
    y &= MASK
    diff = (x - y) & MASK
    return {"n": diff >> 31, "z": int(diff == 0), "c": int(x >= y), "v": ((x ^ y) & (x ^ diff)) >> 31}


def order_key(bits: int) -> int:
    """Sign-magnitude float bits as a two's-complement integer (+0 and -0 both map to 0)."""
    magnitude = bits & 0x7FFFFFFF
    return -magnitude if bits >> 31 else magnitude


UNORDERED32 = {"n": 1, "z": 0, "v": 0}


# -- compare models -----------------------------------------------------------
def single_compare(relation, carry_when_true: bool, z_is_result: bool, nan_carry: int):
    """Models _fgeq/_fgr/_fls/_fleq: ordered N, Z, V are a signed compare of the order keys."""
    def model(a: int, b: int):
        if is_nan32(a) or is_nan32(b):
            flags = dict(UNORDERED32, c=nan_carry)
            if z_is_result:
                flags["z"] = 0
            return 0, flags
        result = int(relation(single(a), single(b)))
        flags = compare_flags(order_key(a), order_key(b))
        flags["c"] = result if carry_when_true else 1 - result
        if z_is_result:
            flags["z"] = result
        return result, flags
    return model


fgeq = single_compare(lambda x, y: x >= y, True, False, 0)
fgr = single_compare(lambda x, y: x > y, True, False, 0)
fls = single_compare(lambda x, y: x < y, False, False, 1)
fleq = single_compare(lambda x, y: x <= y, False, True, 1)


def feq(a: int, b: int):
    if is_nan32(a) or is_nan32(b):
        return 0, {"n": 1, "z": 0, "c": 0, "v": 0}
    if not (a | b) & 0x7FFFFFFF:
        return 1, {"n": 0, "z": 1, "c": (a | b) >> 31, "v": 0}
    return int(a == b), compare_flags(a, b)


def double_compare(relation, nan_carry: int):
    """Models _dgr/_dleq: Z = numeric equality, C = a >= b, except mixed-sign zeros give C = 0."""
    def model(alo: int, ahi: int, blo: int, bhi: int):
        if is_nan64(alo, ahi) or is_nan64(blo, bhi):
            return 0, {"z": 0, "c": nan_carry}
        x, y = double(alo, ahi), double(blo, bhi)
        both_zero = x == 0 and y == 0
        carry = 0 if both_zero and (ahi | bhi) >> 31 else int(x >= y)
        return int(relation(x, y)), {"z": int(x == y), "c": carry}
    return model


dgr = double_compare(lambda x, y: x > y, 0)
dleq = double_compare(lambda x, y: x <= y, 1)


# -- conversion models ----------------------------------------------------------
def ffix(a: int) -> int:
    if is_nan32(a):
        return INT_MIN if a >> 31 else INT_MAX
    return saturate_trunc(single(a), INT_MIN, INT_MAX)


def ffixu(a: int) -> int:
    if is_nan32(a):
        return MASK
    return saturate_trunc(single(a), 0, MASK)


def dfix(lo: int, hi: int) -> int:
    if is_nan64(lo, hi):
        return INT_MIN if hi >> 31 else INT_MAX
    return saturate_trunc(double(lo, hi), INT_MIN, INT_MAX)


def ll_sfrom_f(a: int) -> int:
    if is_nan32(a):
        return LL_MIN if a >> 31 else LL_MAX
    return saturate_trunc(single(a), LL_MIN, LL_MAX)


def signed32(word: int) -> int:
    return word - (1 << 32) if word >> 31 else word


def fflt(a: int) -> int:
    return round_to_single(signed32(a))


def ffltu(a: int) -> int:
    return round_to_single(a)


def ll_sto_f(lo: int, hi: int) -> int:
    value = (hi << 32) | lo
    return round_to_single(value - (1 << 64) if hi >> 31 else value)


def dflt(a: int) -> tuple[int, int]:
    return double_words(float(signed32(a)))


def f2d(a: int) -> tuple[int, int]:
    if is_nan32(a):
        return CANONICAL_NAN64
    return double_words(single(a))


def d2f(lo: int, hi: int) -> int:
    if is_nan64(lo, hi):
        return CANONICAL_NAN32
    value = double(lo, hi)
    try:
        return struct.unpack("<I", struct.pack("<f", value))[0]
    except OverflowError:
        return 0xFF800000 if value < 0 else 0x7F800000


# -- inputs ---------------------------------------------------------------------
def random_single(rng) -> int:
    pick = rng.randrange(4)
    if pick == 0:
        return rng.getrandbits(32)
    if pick == 1:   # magnitudes near the integer range
        return (rng.getrandbits(1) << 31) | (rng.randrange(0x7E, 0xC0) << 23) | rng.getrandbits(23)
    if pick == 2:   # denormals and tiny values
        return (rng.getrandbits(1) << 31) | (rng.randrange(0, 3) << 23) | rng.getrandbits(23)
    return rng.choice(FLOAT_EDGES) ^ rng.getrandbits(rng.randrange(1, 8))


def random_double(rng) -> tuple[int, int]:
    pick = rng.randrange(4)
    sign = rng.getrandbits(1) << 31
    if pick == 0:
        return rng.getrandbits(32), rng.getrandbits(32)
    if pick == 1:   # around the single and int32 ranges
        return rng.getrandbits(32), sign | (rng.randrange(0x360, 0x480) << 20) | rng.getrandbits(20)
    if pick == 2:   # specials with random payloads
        return rng.getrandbits(32) & rng.choice((0, 1, MASK)), sign | 0x7FF00000 | (rng.getrandbits(20) & rng.choice((0, MASK)))
    lo, hi = rng.choice(DOUBLE_EDGES)
    return lo ^ rng.getrandbits(rng.randrange(1, 32)), hi ^ rng.getrandbits(rng.randrange(1, 6))


def single_pairs(rng):
    for a in FLOAT_EDGES:
        for b in FLOAT_EDGES:
            yield a, b
    for _ in range(3000):
        a = random_single(rng)
        pick = rng.randrange(4)
        if pick == 0:
            b = a
        elif pick == 1:
            b = (a + rng.choice((-1, 1))) & MASK
        elif pick == 2:
            b = a ^ 0x80000000
        else:
            b = random_single(rng)
        yield (a, b) if rng.getrandbits(1) else (b, a)


def double_pairs(rng):
    edges = DOUBLE_EDGES[::3] + ((0, 0), (0, 0x80000000), (0, 0x7FF00000), (0, 0xFFF00000), (1, 0x7FF00000))
    for a in edges:
        for b in edges:
            yield a + b
    for _ in range(3000):
        a = random_double(rng)
        pick = rng.randrange(5)
        if pick == 0:
            b = a
        elif pick == 1:
            b = ((a[0] + rng.choice((-1, 1))) & MASK, a[1])
        elif pick == 2:
            b = (a[0], a[1] ^ 0x80000000)
        elif pick == 3:
            b = (a[0], (a[1] + rng.choice((-1, 1))) & MASK)
        else:
            b = random_double(rng)
        yield a + b if rng.getrandbits(1) else b + a


def single_values(rng):
    yield from FLOAT_EDGES
    for exponent in range(0x60, 0xC0):
        for sign in (0, 0x80000000):
            yield sign | (exponent << 23)
            yield sign | (exponent << 23) | 0x7FFFFF
            yield sign | (exponent << 23) | 0x400000
    for _ in range(4000):
        yield random_single(rng)


def double_values(rng):
    yield from DOUBLE_EDGES
    for exponent in list(range(0x360, 0x480)) + [0, 1, 0x7FE, 0x7FF]:
        for sign in (0, 0x80000000):
            hi = sign | (exponent << 20)
            yield 0, hi
            yield MASK, hi | 0xFFFFF
            yield 0x10000000, hi
            yield 0x10000001, hi
            yield 0x30000000, hi | 1
    for _ in range(4000):
        yield random_double(rng)


INT_EDGES = (0, 1, 2, 3, 0x7F, 0x80, 0xFFFFFF, 0x1000000, 0x1000001, 0x1000002, 0x1000003, 0x1FFFFFF,
             0x2000002, 0x2000006, 0x7FFFFF80, 0x7FFFFFBF, 0x7FFFFFC0, 0x7FFFFFFF, 0x80000000, 0x80000001,
             0x800000C0, 0xFFFFFF7F, 0xFFFFFF80, 0xFFFFFFFF, 0xFEFFFFFF, 0xFF000000, 0xFF000001)


def int_values(rng):
    yield from INT_EDGES
    for bits in range(1, 33):
        for _ in range(60):
            value = rng.getrandbits(bits) | (1 << (bits - 1))
            yield value
            yield (-value) & MASK
    for _ in range(1500):
        yield rng.getrandbits(32)


def long_values(rng):
    edges = (0, 1, MASK, 1 << 31, 1 << 32, (1 << 32) - 1, (1 << 32) + 1, 1 << 53, (1 << 53) + 1,
             (1 << 60) + (1 << 36), (1 << 60) + (1 << 36) + 1, (1 << 60) + (3 << 36), (1 << 63) - 1,
             (1 << 63) - (1 << 39), (1 << 63) - (1 << 39) - 1, 0xFFFFFF0000000000, 0xFFFFFF8000000000)
    for value in edges:
        yield value
        yield (-value) & ((1 << 64) - 1)
    for bits in range(1, 65):
        for _ in range(40):
            value = rng.getrandbits(bits) | (1 << (bits - 1))
            if bits > 25 and rng.getrandbits(1):    # ties and near-ties at the rounding position
                cut = bits - 24
                half = 1 << (cut - 1)
                value = (value >> cut << cut) | rng.choice((0, half, half - 1, half + 1))
            yield value
            yield (-value) & ((1 << 64) - 1)
    for _ in range(1000):
        yield rng.getrandbits(64)


# -- cases ------------------------------------------------------------------------
def single_compare_cases(model):
    def cases(rng):
        for a, b in single_pairs(rng):
            result, flags = model(a, b)
            yield Case((a, b), regs={0: result}, flags=flags)
    return cases


def double_compare_cases(model):
    def cases(rng):
        for alo, ahi, blo, bhi in double_pairs(rng):
            result, flags = model(alo, ahi, blo, bhi)
            yield Case((alo, ahi, blo, bhi), regs={0: result}, flags=flags)
    return cases


def word_cases(values, model):
    def cases(rng):
        for a in values(rng):
            yield Case((a,), regs={0: model(a)})
    return cases


def pair_result_cases(values, model):
    def cases(rng):
        for a in values(rng):
            lo, hi = model(a)
            yield Case((a,), regs={0: lo, 1: hi})
    return cases


def double_arg_cases(model):
    def cases(rng):
        for lo, hi in double_values(rng):
            yield Case((lo, hi), regs={0: model(lo, hi)})
    return cases


def ll_sfrom_f_cases(rng):
    for a in single_values(rng):
        value = ll_sfrom_f(a) & ((1 << 64) - 1)
        yield Case((a,), regs={0: value & MASK, 1: value >> 32})


def ll_sto_f_cases(rng):
    for value in long_values(rng):
        yield Case((value & MASK, value >> 32), regs={0: ll_sto_f(value & MASK, value >> 32)})


def calls(name: str) -> str:
    return "src/asm_stubs/calls/%s.c" % name


ROUTINES = [
    Routine("_fgeq", calls("_fgeq"), DOC, single_compare_cases(fgeq), index_name="func_020237cc"),
    Routine("_fgr", calls("_fgr"), DOC, single_compare_cases(fgr), index_name="func_02023828"),
    Routine("_fls", calls("_fls"), DOC, single_compare_cases(fls), index_name="func_020238ec"),
    Routine("_fleq", calls("_fleq"), DOC, single_compare_cases(fleq), index_name="func_02023884"),
    Routine("_feq", calls("_feq"), DOC, single_compare_cases(feq), index_name="func_02023948"),
    Routine("_dgr", calls("_dgr"), DOC, double_compare_cases(dgr), index_name="func_02023690"),
    Routine("_dleq", calls("_dleq"), DOC, double_compare_cases(dleq), index_name="func_02023728"),
    Routine("_ffix", calls("_ffix"), DOC, word_cases(single_values, ffix), index_name="func_020241c0"),
    Routine("_ffixu", calls("_ffixu"), DOC, word_cases(single_values, ffixu), index_name="func_020241f4"),
    Routine("_dfix", calls("_dfix"), DOC, double_arg_cases(dfix), index_name="func_02024234"),
    Routine("_ll_sfrom_f", calls("_ll_sfrom_f"), DOC, ll_sfrom_f_cases, index_name="func_02023a34"),
    Routine("_fflt", calls("_fflt"), DOC, word_cases(int_values, fflt), index_name="func_02023aac"),
    Routine("_ffltu", calls("_ffltu"), DOC, word_cases(int_values, ffltu), index_name="func_02023af4"),
    Routine("_ll_sto_f", "libs/msl/c/asm_stubs/calls/_ll_sto_f.s", DOC, ll_sto_f_cases, index_name="func_02023b3c", object_gate=True),
    Routine("_dflt", calls("_dflt"), DOC, pair_result_cases(int_values, dflt), index_name="func_02023650"),
    Routine("_f2d", calls("_f2d"), DOC, pair_result_cases(single_values, f2d), index_name="func_020239b0"),
    Routine("_d2f", calls("_d2f"), DOC, double_arg_cases(d2f), index_name="func_0202354c"),
]
