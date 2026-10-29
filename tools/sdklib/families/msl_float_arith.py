"""CodeWarrior soft-float arithmetic (_fadd .. _ddiv) and the MSL double square root.

The compiler calls these for `+ - * /` on float and double, and MSL's sqrt()
lands in MSL_Sqrt. A float travels in one register; a double in two, low word
first (r0 = low, r1 = high with the sign). The model below is IEEE-754 binary32
and binary64 arithmetic computed exactly with fractions and rounded to nearest,
ties to even, with gradual underflow; the routines' only departure from IEEE is
the NaN they return (NAN_FLOAT / NAN_DOUBLE, double_divide() and quiet_nan()).
"""

from fractions import Fraction
from math import isqrt

from verify_sdklib import Case, Routine, load_symbols

DOC = "docs/library/msl_float_arith.md"
SOURCE = "src/asm_stubs/calls/%s"
MASK = 0xFFFFFFFF
ERRNO = 0x0205FDBC
EDOM = 33


class Format:
    def __init__(self, exponent_bits: int, mantissa_bits: int):
        self.ebits = exponent_bits
        self.mbits = mantissa_bits
        self.bias = (1 << (exponent_bits - 1)) - 1
        self.emax = (1 << exponent_bits) - 1
        self.width = 1 + exponent_bits + mantissa_bits
        self.sign = 1 << (self.width - 1)
        self.inf = self.emax << mantissa_bits


FLOAT = Format(8, 23)
DOUBLE = Format(11, 52)
NAN_FLOAT = 0x7FFFFFFF               # every float NaN result
NAN_DOUBLE = 0x7FFFFFFFFFFFFFFF      # every double NaN result


def nan_of(fmt):
    return NAN_FLOAT if fmt is FLOAT else NAN_DOUBLE


def decode(fmt: Format, bits: int):
    """Returns (kind, sign, value): kind is 'nan', 'inf', 'zero' or 'num'."""
    sign = bits >> (fmt.width - 1)
    exponent = (bits >> fmt.mbits) & fmt.emax
    mantissa = bits & ((1 << fmt.mbits) - 1)
    if exponent == fmt.emax:
        return ("nan" if mantissa else "inf"), sign, None
    if exponent == 0 and mantissa == 0:
        return "zero", sign, Fraction(0)
    if exponent == 0:
        exponent = 1                          # denormal: no hidden bit
    else:
        mantissa |= 1 << fmt.mbits
    value = Fraction(mantissa) * Fraction(2) ** (exponent - fmt.bias - fmt.mbits)
    return "num", sign, value


def round_pack(fmt: Format, sign: int, value: Fraction) -> int:
    """Rounds a non-negative exact value to nearest-even, with gradual underflow and overflow to infinity."""
    if value == 0:
        return sign * fmt.sign
    exponent = value.numerator.bit_length() - value.denominator.bit_length()
    if Fraction(2) ** exponent > value:
        exponent -= 1
    exponent = max(exponent, 1 - fmt.bias)                     # denormals share the minimum exponent
    scaled = value / Fraction(2) ** (exponent - fmt.mbits)      # mantissa units
    integer, remainder = divmod(scaled.numerator, scaled.denominator)
    twice = 2 * remainder
    if twice > scaled.denominator or (twice == scaled.denominator and integer & 1):
        integer += 1
    if integer >> (fmt.mbits + 1):
        integer >>= 1
        exponent += 1
    biased = exponent + fmt.bias if integer >> fmt.mbits else 0
    if biased >= fmt.emax:
        return sign * fmt.sign | fmt.inf
    return sign * fmt.sign | biased << fmt.mbits | (integer & ((1 << fmt.mbits) - 1))


def add(fmt: Format, a: int, b: int) -> int:
    ka, sa, va = decode(fmt, a)
    kb, sb, vb = decode(fmt, b)
    if "nan" in (ka, kb):
        return nan_of(fmt)
    if ka == "inf" or kb == "inf":
        if ka == kb == "inf" and sa != sb:
            return nan_of(fmt)
        return (sa if ka == "inf" else sb) * fmt.sign | fmt.inf
    total = (-va if sa else va) + (-vb if sb else vb)
    if total == 0:
        return (sa & sb) * fmt.sign                  # x - x is +0; -0 + -0 is -0
    return round_pack(fmt, int(total < 0), abs(total))


def multiply(fmt: Format, a: int, b: int) -> int:
    ka, sa, va = decode(fmt, a)
    kb, sb, vb = decode(fmt, b)
    sign = sa ^ sb
    if "nan" in (ka, kb):
        return nan_of(fmt)
    if "inf" in (ka, kb):
        return nan_of(fmt) if "zero" in (ka, kb) else sign * fmt.sign | fmt.inf
    return round_pack(fmt, sign, va * vb)


def divide(fmt: Format, a: int, b: int) -> int:
    ka, sa, va = decode(fmt, a)
    kb, sb, vb = decode(fmt, b)
    sign = sa ^ sb
    if "nan" in (ka, kb):
        return nan_of(fmt)
    if ka == "inf":
        return nan_of(fmt) if kb == "inf" else sign * fmt.sign | fmt.inf
    if kb == "inf":
        return sign * fmt.sign
    if kb == "zero":
        return nan_of(fmt) if ka == "zero" else sign * fmt.sign | fmt.inf
    return round_pack(fmt, sign, va / vb)


QUIET = 1 << 51
QUIET_NAN_HIGH = 0x7FF8 << 48


def double_divide(a: int, b: int) -> int:
    """_ddiv: IEEE division, but NaN results follow the routine's own propagation rules."""
    ka, _, _ = decode(DOUBLE, a)
    kb, _, _ = decode(DOUBLE, b)
    if ka == "nan":
        if not a & QUIET:
            return a | QUIET                         # a signaling dividend is quieted
        return b if kb == "nan" and b & QUIET else a
    if kb == "nan":
        if b & QUIET:
            return b
        return QUIET_NAN_HIGH | dividend_fraction(a, ka)
    if (ka, kb) in (("inf", "inf"), ("zero", "zero")):
        return a | QUIET_NAN_HIGH                    # dividend's sign, quiet NaN
    return divide(DOUBLE, a, b)


def dividend_fraction(a: int, kind: str) -> int:
    """A finite dividend gives its fraction bits (a denormal's normalized ones) and loses its sign."""
    if kind in ("zero", "inf"):
        return a & DOUBLE.sign                       # zero or infinity keeps its sign
    fraction = a & ((1 << 52) - 1)
    if not (a >> 52) & DOUBLE.emax:
        fraction <<= 53 - fraction.bit_length()
    return fraction & ((1 << 52) - 1)


def square_root(bits: int) -> tuple[int, bool]:
    """MSL sqrt(): returns (result, sets errno to EDOM)."""
    kind, sign, value = decode(DOUBLE, bits)
    if kind == "zero" or (kind == "inf" and not sign):
        return bits, False                           # sqrt(-0) = -0, sqrt(+inf) = +inf
    if kind == "num" and not sign:
        # isqrt with a sticky half unit far below the rounding point; sqrt never ties
        scale = 1200
        product = value * Fraction(4) ** scale
        root = isqrt(product.numerator // product.denominator)
        exact = root * root * product.denominator == product.numerator
        return round_pack(DOUBLE, 0, Fraction(2 * root + (not exact), 2 << scale)), False
    return quiet_nan(bits), True


def quiet_nan(bits: int) -> int:
    """sqrt of a negative number or NaN keeps the operand's sign and payload and sets the quiet bit."""
    return bits | 0x7FF8000000000000


def split(value: int) -> tuple[int, int]:
    return value & MASK, value >> 32


def float_values():
    """Edge cases, then normal-range values, then fully random bit patterns."""
    magnitudes = (0, 1, 2, 3, 0x007FFFFF, 0x00400000, 0x00800000, 0x00800001, 0x00FFFFFF,
                  0x01000000, 0x0C000000, 0x33800000, 0x34000000, 0x3F000000, 0x3F7FFFFF,
                  0x3F800000, 0x3F800001, 0x3FC00000, 0x40000000, 0x40400000, 0x4B000000,
                  0x4B7FFFFF, 0x7E800000, 0x7F000000, 0x7F7FFFFE, 0x7F7FFFFF, 0x7F800000,
                  0x7F800001, 0x7FC00000, 0x7FFFFFFF)
    return [m | s for m in magnitudes for s in (0, 0x80000000)]


def double_values():
    magnitudes = (0, 1, 2, 3, 0x000FFFFFFFFFFFFF, 0x0008000000000000, 0x0000000100000000,
                  0x00000000FFFFFFFF, 0x0010000000000000, 0x0010000000000001, 0x001FFFFFFFFFFFFF,
                  0x0020000000000000, 0x3CA0000000000000, 0x3CB0000000000000, 0x3FE0000000000000,
                  0x3FEFFFFFFFFFFFFF, 0x3FF0000000000000, 0x3FF0000000000001, 0x3FF8000000000000,
                  0x4000000000000000, 0x4008000000000000, 0x4330000000000000, 0x433FFFFFFFFFFFFF,
                  0x7FD0000000000000, 0x7FE0000000000000, 0x7FEFFFFFFFFFFFFE, 0x7FEFFFFFFFFFFFFF,
                  0x7FF0000000000000, 0x7FF0000000000001, 0x7FF8000000000000, 0x7FFFFFFFFFFFFFFF,
                  0x7FF0000100000000)
    return [m | s for m in magnitudes for s in (0, 1 << 63)]


def random_operand(rng, fmt: Format, center: int | None = None, spread: int | None = None) -> int:
    mantissa = rng.getrandbits(fmt.mbits)
    if rng.random() < 0.1:
        mantissa &= ~((1 << rng.randrange(fmt.mbits)) - 1)       # trailing zeros make exact ties
    if center is None:
        exponent = rng.randrange(1, fmt.emax)
    else:
        exponent = min(max(center + rng.randint(-spread, spread), 1), fmt.emax - 1)
    return rng.getrandbits(1) * fmt.sign | exponent << fmt.mbits | mantissa


def operand_pairs(rng, fmt: Format, edges, operation: str):
    for a in edges:
        for b in edges:
            yield a, b
    for _ in range(8000):                    # close exponents: cancellation, ties, carries
        a = random_operand(rng, fmt)
        yield a, random_operand(rng, fmt, (a >> fmt.mbits) & fmt.emax, 2 if rng.random() < 0.5 else fmt.mbits + 4)
    for _ in range(8000):                    # results near the underflow and overflow limits
        target = rng.choice((0, fmt.mbits // 2, fmt.emax - 1))
        a = random_operand(rng, fmt, target, 3) if operation == "add" else random_operand(rng, fmt)
        ea = (a >> fmt.mbits) & fmt.emax
        if operation == "mul":
            center = target + fmt.bias - ea
        elif operation == "div":
            center = ea - target + fmt.bias
        else:
            center = ea
        b = random_operand(rng, fmt, center, 3)
        if rng.random() < 0.2:
            b &= fmt.sign | ((1 << fmt.mbits) - 1)               # denormal operand
        elif operation != "add" and rng.random() < 0.25:
            b &= ~((1 << fmt.mbits) - 1)                         # power of two: exact ties when denormal
        yield (b, a) if rng.random() < 0.5 and operation != "div" else (a, b)
    for _ in range(2000):                    # NaN (any payload, either sign) or infinity against anything
        special = rng.getrandbits(1) * fmt.sign | fmt.inf | rng.getrandbits(fmt.mbits) * (rng.random() < 0.8)
        other = rng.choice((random_operand(rng, fmt), rng.getrandbits(fmt.width), rng.choice(edges)))
        yield (special, other) if rng.random() < 0.5 else (other, special)
    for _ in range(8000):                    # normal range
        yield random_operand(rng, fmt), random_operand(rng, fmt)
    for _ in range(8000):                    # any bit pattern
        yield rng.getrandbits(fmt.width), rng.getrandbits(fmt.width)


def float_cases(model, operation):
    def cases(rng):
        for a, b in operand_pairs(rng, FLOAT, float_values(), operation):
            yield Case((a, b), regs={0: model(a, b)})
    return cases


def double_cases(model, operation):
    def cases(rng):
        for a, b in operand_pairs(rng, DOUBLE, double_values(), operation):
            lo, hi = split(model(a, b))
            yield Case(split(a) + split(b), regs={0: lo, 1: hi})
    return cases


def errno_check(expected: int):
    def check(cpu):
        value = cpu.mem.read(ERRNO, 4)
        return None if value == expected else "errno = %d, model %d" % (value, expected)
    return check


def reset_errno(mem):
    mem.write(ERRNO, 4, 0)


def sqrt_cases(rng):
    values = double_values()
    for _ in range(10000):
        values.append(random_operand(rng, DOUBLE) & ~DOUBLE.sign)
    for _ in range(3000):
        values.append(rng.getrandbits(52))                       # denormals
    for _ in range(3000):
        root = rng.getrandbits(26) | 1 << 25                     # exact squares
        values.append(round_pack(DOUBLE, 0, Fraction(root * root, 1 << rng.randrange(0, 60))))
    for _ in range(8000):
        values.append(rng.getrandbits(64))
    for x in values:
        result, domain_error = square_root(x)
        lo, hi = split(result)
        yield Case(split(x), regs={0: lo, 1: hi}, setup=reset_errno,
                   check=errno_check(EDOM if domain_error else 0))


def fadd(a, b): return add(FLOAT, a, b)
def fsub(a, b): return add(FLOAT, a, b ^ FLOAT.sign)
def fmul(a, b): return multiply(FLOAT, a, b)
def fdiv(a, b): return divide(FLOAT, a, b)
def dadd(a, b): return add(DOUBLE, a, b)
def dsub(a, b): return add(DOUBLE, a, b ^ DOUBLE.sign)
def dmul(a, b): return multiply(DOUBLE, a, b)
def ddiv(a, b): return double_divide(a, b)


def swapped(model):
    """_frsb/_drsb/_frdiv/_drdiv: operands exchanged, then the next routine."""
    return lambda a, b: model(b, a)


ROUTINES = [
    Routine("_fadd", SOURCE % "_fadd.s", DOC, float_cases(fadd, "add"), index_name="func_020245fc", object_gate=True),
    Routine("_fsub", SOURCE % "_fsub.s", DOC, float_cases(fsub, "add"), index_name="func_0202482c", object_gate=True,
            unreachable=((0x02024A68, 0x02024A80),)),    # dead code, see the docs
    Routine("_frsb", SOURCE % "_frsb.s", DOC, float_cases(swapped(fsub), "add")),
    Routine("_fmul", SOURCE % "_fmul.c", DOC, float_cases(fmul, "mul"), index_name="func_0202441c"),
    Routine("_fdiv", SOURCE % "_fdiv.c", DOC, float_cases(fdiv, "div"), index_name="func_02024ab0",
            data=((0x02024B64, 0x02024C64),)),           # reciprocal seed table
    Routine("_frdiv", SOURCE % "_frdiv.s", DOC, float_cases(swapped(fdiv), "div")),
    Routine("_dadd", SOURCE % "_dadd.s", DOC, double_cases(dadd, "add"), index_name="func_02022b04", object_gate=True,
            unreachable=((0x02022DE8, 0x02022DF8),)),    # dead code, see the docs
    Routine("_dsub", SOURCE % "_dsub.s", DOC, double_cases(dsub, "add"), index_name="func_02022e34", object_gate=True),
    Routine("_drsb", SOURCE % "_drsb.s", DOC, double_cases(swapped(dsub), "add")),
    Routine("_dmul", SOURCE % "_dmul.c", DOC, double_cases(dmul, "mul"), index_name="func_020231e8"),
    Routine("_ddiv", SOURCE % "_ddiv.c", DOC, double_cases(ddiv, "div"), index_name="func_02024e80",
            data=((0x02024FB8, 0x020250B8),)),           # reciprocal seed table
    Routine("_drdiv", SOURCE % "_drdiv.s", DOC, double_cases(swapped(ddiv), "div")),
    Routine("MSL_Sqrt", SOURCE % "MSL_Sqrt.c", DOC, sqrt_cases, index_name="func_02024280"),
]
# load_symbols() cannot read `function(arm,size=..,unknown)` entries yet (_frsb, _frdiv, _drsb, _drdiv)
_KNOWN = load_symbols()
ROUTINES = [routine for routine in ROUTINES if routine.symbol in _KNOWN]
