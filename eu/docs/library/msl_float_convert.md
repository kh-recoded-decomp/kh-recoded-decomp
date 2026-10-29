# MSL soft-float compares and conversions

Hand-written ARM routines from the CodeWarrior for DS floating-point library
(ARM fplib). The ARM946E-S has no FPU, so the compiler calls these for
`float`/`double` comparisons and casts. Each section below is checked by
`tools/sdklib/verify_sdklib.py`, which runs the ROM's own instructions against
the Python model in `tools/sdklib/families/msl_float_convert.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

Values travel as raw IEEE-754 bit patterns: a `float` in one register, a
`double` in a register pair with the low word first (`r0:r1` for the first
argument, `r2:r3` for the second). 64-bit integers use the same pair order.
None of the routines touches the stack or memory, and all clobber the
condition flags unless the flags are the result.

The compares answer twice: a 0/1 result in `r0`, and condition flags written
with `msr CPSR_f` (or left by the final `cmp`) so the caller can branch
straight after the `bl`. Their contract is the condition each section names;
any flag not listed under it is incidental, and the model pins it only so the
verification is exact. A NaN operand makes every compare false, `-0` and `+0`
compare equal, and infinities order normally.

A port can replace every routine with the host compiler's own comparison and
cast operators. The differences from C/IEEE are listed under Behavior:
conversions to integer saturate instead of being undefined, and a NaN
converted between `float` and `double` becomes a fixed positive quiet NaN.

## Single-precision compares

These five share one shape: an unordered test (`x << 1 > 0xff000000` means
NaN), then a signed compare of the two operands mapped from sign-magnitude to
two's complement (`-(x & 0x7fffffff)` for negative `x`), which makes `-0`
equal `+0`. For ordered operands N, Z and V are the flags of that signed
compare, so the signed conditions `ge`/`gt`/`lt`/`le` also hold. For a NaN
operand N = 1, Z = 0, V = 0.

### `_fgeq`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = (a >= b) and
  C = (a >= b); the caller branches with `bcs`/`bcc`. Clobbers `r1`, `r3`,
  `ip`; no stack.
- **Behavior:** IEEE `a >= b`. Unordered (either NaN): `r0` = 0, C = 0.
  `-0 >= +0` is true.
- **Hardware:** none; integer ARM code in main RAM, no memory access,
  interrupts or coprocessor.

### `_fgr`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = (a > b) and
  C = (a > b); Z = (a == b) from the compare, so `bhi` also works. Clobbers
  `r1`, `r3`, `ip`; no stack.
- **Behavior:** IEEE `a > b`. Unordered: `r0` = 0, C = 0. `+0 > -0` is false.
- **Hardware:** none; integer ARM code in main RAM.

### `_fls`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = (a < b) and
  C = !(a < b); the caller branches with `bcc` for "less". Clobbers `r1`,
  `r3`, `ip`; no stack.
- **Behavior:** IEEE `a < b`. Unordered: `r0` = 0, C = 1 (not less). Note
  that the signed `lt` condition (N != V) is true for a NaN operand, so only
  the carry is a safe test. `-0 < +0` is false.
- **Hardware:** none; integer ARM code in main RAM.

### `_fleq`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = (a <= b),
  Z = (a <= b) and C = !(a <= b); the caller branches with `bls`/`bhi`.
  Clobbers `r1`, `r3`, `ip`; no stack.
- **Behavior:** IEEE `a <= b`. Unordered: `r0` = 0, Z = 0, C = 1 (`hi`, not
  less-or-equal). Because Z is rewritten it no longer means "equal".
- **Hardware:** none; integer ARM code in main RAM.

### `_feq`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = (a == b) and
  Z = (a == b); the caller branches with `beq`/`bne`. Clobbers `r3`, `ip`;
  `r1` is preserved; no stack.
- **Behavior:** IEEE `a == b`: `+0 == -0` is true, a NaN is unequal to
  everything including itself. Incidental flags: two zeros give N = 0,
  C = 1 when either is `-0`, V = 0; other ordered pairs leave the flags of
  `cmp a, b` on the raw bit patterns; a NaN gives N = 1, C = 0, V = 0.
- **Hardware:** none; integer ARM code in main RAM.

## Double-precision compares

Unordered means an all-ones exponent with a non-zero fraction in either word.
Two non-negative operands are compared as 64-bit unsigned bit patterns
(`cmp hi; cmpeq lo`); otherwise, unless both are zeros, the operands are
compared in reverse order, which orders negative values correctly. Ordered
results therefore leave Z = (a == b) and C = (a >= b), except that two zeros
with at least one `-0` give Z = 1, C = 0. N and V are left over from the
internal word compares and carry no meaning; the model does not check them.

### `_dgr`

- **Interface:** `r0:r1` = a, `r2:r3` = b (double, low word first). Returns
  `r0` = (a > b); the flags give `hi` exactly when a > b. Clobbers `ip`;
  `r1`-`r3` are preserved; no stack.
- **Behavior:** IEEE `a > b`. Unordered: `r0` = 0, Z = 0, C = 0 (`ls`).
  `+0 > -0` is false.
- **Hardware:** none; integer ARM code in main RAM.

### `_dleq`

- **Interface:** `r0:r1` = a, `r2:r3` = b (double, low word first). Returns
  `r0` = (a <= b); the flags give `ls` exactly when a <= b. Clobbers `ip`;
  `r1`-`r3` are preserved; no stack.
- **Behavior:** IEEE `a <= b`. Unordered: `r0` = 0, Z = 0, C = 1 (`hi`).
  `-0 <= +0` and `+0 <= -0` are true.
- **Hardware:** none; integer ARM code in main RAM.

## Conversions to integer

All round toward zero, as a C cast does. Where C leaves the result undefined
(out of range, infinity, NaN) these saturate by the input's sign bit.

### `_ffix`

- **Interface:** `r0` = float bits. Returns the `s32` in `r0`. Clobbers `r1`,
  `r2`; no stack.
- **Behavior:** `(int)x`, truncating. |x| < 1 (including zeros and denormals)
  gives 0. Values >= 2^31, +Inf and NaNs with the sign bit clear give
  `0x7fffffff`; values <= -2^31, -Inf and NaNs with the sign bit set give
  `0x80000000`.
- **Hardware:** none; integer ARM code in main RAM.

### `_ffixu`

- **Interface:** `r0` = float bits. Returns the `u32` in `r0`. Clobbers `r1`,
  `r2`; no stack.
- **Behavior:** `(unsigned)x`, truncating. Every negative value, `-0` and -Inf
  gives 0 (C converts via modular wrap or leaves it undefined; this clamps).
  Values >= 2^32, +Inf and every NaN (either sign) give `0xffffffff`.
- **Hardware:** none; integer ARM code in main RAM.

### `_dfix`

- **Interface:** `r0:r1` = double (low word first). Returns the `s32` in `r0`.
  Clobbers `r2`, `r3`; `r1` is preserved; no stack. The constant 0x41e
  (1023 + 31) is in a literal word at the routine's end.
- **Behavior:** `(int)x`, truncating; the low word only contributes its top
  11 bits, which is all an in-range result can use. |x| < 1 gives 0.
  Saturation is the same as `_ffix`: `0x7fffffff` for >= 2^31, +Inf and
  positive NaNs, `0x80000000` for <= -2^31, -Inf and negative NaNs.
- **Hardware:** none; integer ARM code in main RAM.

### `_ll_sfrom_f`

- **Interface:** `r0` = float bits. Returns the `s64` in `r0:r1` (low word
  first). Clobbers `r2`, `r3`, `ip`; no stack.
- **Behavior:** `(long long)x`, truncating. |x| < 1 gives 0. Values >= 2^63,
  +Inf and positive NaNs give `0x7fffffffffffffff`; values <= -2^63, -Inf and
  negative NaNs give `0x8000000000000000`. For negative inputs the arithmetic
  right shift rounds down, and the routine adds 1 when bits were lost, so the
  result is truncated toward zero.
- **Hardware:** none; integer ARM code in main RAM.

## Conversions from integer

All are correctly rounded to nearest, ties to even, and exact when the value
fits. Zero converts to `+0`.

### `_fflt`

- **Interface:** `r0` = `s32`. Returns float bits in `r0`. Clobbers `r1`-`r3`;
  no stack. `_ll_sto_f` enters it at `_fflt` + 12 with the flags set from
  `r0` and the sign in `r2`.
- **Behavior:** `(float)i`, round to nearest even. `INT_MIN` gives -2^31.
- **Hardware:** none; integer ARM code in main RAM; uses `clz` (ARMv5).

### `_ffltu`

- **Interface:** `r0` = `u32`. Returns float bits in `r0`. Clobbers `r1`-`r3`,
  `ip`; no stack.
- **Behavior:** `(float)u`, round to nearest even; `0xffffffff` gives 2^32.
- **Hardware:** none; integer ARM code in main RAM; uses `clz` (ARMv5).

### `_ll_sto_f`

- **Interface:** `r0:r1` = `s64` (low word first). Returns float bits in `r0`.
  Clobbers `r1`-`r3`, `ip`; no stack. When the magnitude fits in 32 bits it
  branches into `_fflt` + 12 and returns from there.
- **Behavior:** `(float)ll`, a single rounding to nearest even: bits below the
  top 32 of the magnitude are folded into a sticky bit, so there is no double
  rounding. `LLONG_MIN` gives -2^63.
- **Hardware:** none; integer ARM code in main RAM; uses `clz` (ARMv5).

### `_dflt`

- **Interface:** `r0` = `s32`. Returns the double in `r0:r1` (low word first).
  Clobbers `r2`, `r3`, `ip`; no stack.
- **Behavior:** `(double)i`, always exact. `INT_MIN` gives -2^31.
- **Hardware:** none; integer ARM code in main RAM; uses `clz` (ARMv5).

## Float/double conversions

### `_f2d`

- **Interface:** `r0` = float bits. Returns the double in `r0:r1` (low word
  first). Clobbers `r2`, `r3`, `ip`; no stack. The +Inf high word
  `0x7ff00000` is a literal word at the routine's end.
- **Behavior:** `(double)f`, exact for zeros, denormals (normalized with
  `clz`), normals and infinities. Differs from IEEE for NaNs: every NaN,
  whatever its sign and payload, becomes `0x7fffffff_ffffffff` (positive,
  quiet, all-ones fraction).
- **Hardware:** none; integer ARM code in main RAM; uses `clz` (ARMv5).

### `_d2f`

- **Interface:** `r0:r1` = double (low word first). Returns float bits in
  `r0`. Clobbers `r1`-`r3`, `ip`; no stack.
- **Behavior:** `(float)d`, round to nearest even, with IEEE gradual
  underflow: results below 2^-126 round to single denormals, values at or
  below 2^-150 become signed zero (exactly 2^-150 is a tie and rounds to
  zero), and double denormals become signed zero. Values that round past the
  largest single give signed infinity. Differs from IEEE for NaNs: every NaN
  becomes `0x7fffffff` (positive, quiet, all-ones fraction).
- **Hardware:** none; integer ARM code in main RAM.
