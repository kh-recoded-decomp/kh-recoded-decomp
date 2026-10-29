# MSL soft-float arithmetic

Hand-written ARM routines from the CodeWarrior for DS floating-point library
(ARM fplib). The ARM946E-S has no FPU, so the compiler calls these for `+`,
`-`, `*` and `/` on `float` and `double`, and MSL's `sqrt()` is `MSL_Sqrt`.
Each section below is checked by `tools/sdklib/verify_sdklib.py`, which runs
the ROM's own instructions against the Python model in
`tools/sdklib/families/msl_float_arith.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

Values travel as raw IEEE-754 bit patterns: a `float` in one register, a
`double` in a register pair with the low word first (`r0:r1` for the first
operand, `r2:r3` for the second; `r1`/`r3` hold the sign and exponent). The
result comes back in `r0` (float) or `r0:r1` (double). Every routine clobbers
the condition flags; none sets exception flags, traps or touches `errno`
except `MSL_Sqrt`.

The arithmetic is exact IEEE-754 binary32/binary64: the exact result rounded
to nearest, ties to even (the only rounding mode), with gradual underflow
(denormal operands and results are handled in full, never flushed to zero)
and overflow to a signed infinity. Signed zeros follow IEEE: `x - x` and
`x + (-x)` give `+0`, `-0 + -0` and `-0 - +0` give `-0`, and the sign of a
zero product or quotient is the XOR of the operand signs. The one departure
from IEEE is the NaN that comes back: the add, subtract and multiply routines
and `_fdiv` return one fixed NaN for every NaN result, whatever the operands'
payloads, while `_ddiv` and `MSL_Sqrt` propagate operand NaNs by their own
rules (described in their sections). A port can replace every routine with the
host's IEEE operators in round-to-nearest mode; only NaN bit patterns differ.

The fixed NaNs are positive with every payload bit set: `0x7fffffff` for
float and `0x7fffffff_ffffffff` for double. They are quiet NaNs, so code that
only tests `x != x` sees no difference from C.

## Single precision

`_fadd` and `_fsub` share their cores: each first compares the operand signs
and, when the operation is really the other one, flips the sign of `b` and
branches into the other routine's core at its second global entry
(`func_02024608` = `_fadd` + 0xc for a same-sign add, `func_02024838` =
`_fsub` + 0xc for a magnitude subtract). Both cores swap the operands so the
larger magnitude comes first, align with a sticky bit, and round from the
guard byte.

### `_fadd`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = a + b.
  Clobbers `r1`, `r2`, `r3`, `ip`; no stack. When the signs differ it flips
  b's sign and branches into `_fsub` at `func_02024838` (the result returns
  from there). `func_02024608` (`_fadd` + 0xc) is a global entry that skips
  the sign test; `_fsub` enters it with operands of equal sign.
- **Behavior:** IEEE binary32 addition, round to nearest even, gradual
  underflow, overflow to ±infinity. `inf + inf` of one sign is that infinity;
  `+inf + -inf` and any NaN operand return `0x7fffffff`.
- **Hardware:** none; integer ARM code in main RAM, no memory access,
  interrupts or coprocessor.

### `_fsub`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = a - b.
  Clobbers `r1`, `r2`, `r3`, `ip`; no stack. When the signs differ it flips
  b's sign and branches into `_fadd` at `func_02024608`. `func_02024838`
  (`_fsub` + 0xc) is a global entry that skips the sign test; `_fadd` and
  `_frsb` reach it with operands of equal sign.
- **Behavior:** IEEE binary32 subtraction, round to nearest even, gradual
  underflow, overflow to ±infinity. An exact zero difference is `+0`
  (`-0 - +0` is `-0`). `inf - inf` of one sign and any NaN operand return
  `0x7fffffff`.
  Six instructions at `_fsub` + 0x23c..0x254 (`0x02024a68`-`0x02024a80`)
  are dead code: they follow a `bx lr`, and no branch or literal in the
  ARM9 image reaches them. They repeat the denormal-result pack just above
  them without its sign `orr`. The inventory declares them unreachable and counts them apart.
- **Hardware:** none; integer ARM code in main RAM.

### `_frsb`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = b - a.
  Three `eor` instructions swap `r0` and `r1`, then execution falls through
  into `_fsub`, which immediately follows it; clobbers and stack as `_fsub`.
- **Behavior:** reverse subtraction, `_fsub(b, a)`, with `_fsub`'s rounding
  and NaN rules.
- **Hardware:** none; must stay directly in front of `_fsub` in memory.

### `_fmul`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = a * b.
  Clobbers `r1`, `r2`, `r3`, `ip`; no stack. Uses `umull` for the 24x24-bit
  product.
- **Behavior:** IEEE binary32 multiplication, round to nearest even,
  gradual underflow, overflow to ±infinity. `inf * finite non-zero` is a
  signed infinity; `0 * inf` and any NaN operand return `0x7fffffff`.
- **Hardware:** none; integer ARM code in main RAM.

### `_fdiv`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = a / b.
  Clobbers `r1`, `r2`, `r3`, `ip`; pushes and restores `lr` (4 bytes of
  stack). The 256-byte reciprocal seed table at `_fdiv` + 0xb4 (after the
  main path's `bx lr`, read with a PC-relative `ldrb`) is data inside the
  routine.
- **Behavior:** IEEE binary32 division, round to nearest even, gradual
  underflow, overflow to ±infinity; the quotient is correctly rounded.
  `x / 0` (x finite non-zero) and `inf / x`
  give a signed infinity; `x / inf` gives a signed zero; `0 / 0`,
  `inf / inf` and any NaN operand return `0x7fffffff`.
- **Hardware:** none; integer ARM code in main RAM. The table is addressed
  relative to the PC, so the code and table must move together.

### `_frdiv`

- **Interface:** `r0` = a, `r1` = b (float bits). Returns `r0` = b / a.
  Three `eor` instructions swap `r0` and `r1`, then execution falls through
  into `_fdiv`, which immediately follows it; clobbers and stack as `_fdiv`.
- **Behavior:** reverse division, `_fdiv(b, a)`, with `_fdiv`'s rounding and
  NaN rules.
- **Hardware:** none; must stay directly in front of `_fdiv` in memory.

## Double precision

`_dadd` and `_dsub` pair up the same way as their single-precision
counterparts, but each pushes `{r4, lr}` before the sign test, so the second
entries `func_02022b14` (`_dadd` + 0x10) and `func_02022e44` (`_dsub` + 0x10)
expect that frame already on the stack.

### `_dadd`

- **Interface:** `r0:r1` = a, `r2:r3` = b (double, low word first). Returns
  `r0:r1` = a + b. Clobbers `r2`, `r3`, `ip`; saves and restores `r4` and
  `lr` (8 bytes of stack). When the signs differ it flips b's sign and
  branches, frame still pushed, into `_dsub` at `func_02022e44`.
  `func_02022b14` (`_dadd` + 0x10) is a global entry that skips the push and
  the sign test.
- **Behavior:** IEEE binary64 addition, round to nearest even, gradual
  underflow, overflow to ±infinity. `inf + inf` of one sign is that infinity;
  `+inf + -inf` and any NaN operand return `0x7fffffff_ffffffff`.
  Four instructions at `_dadd` + 0x2e4..0x2f4 (`0x02022de8`-`0x02022df8`)
  are dead code: they follow a return, and no branch or literal in the ARM9
  image reaches them. They are a second copy of the NaN return just above
  them (`mvn r0, #0; bic r1, r0, #0x80000000; pop {r4, lr}; bx lr`). The inventory declares them unreachable and counts them apart.
- **Hardware:** none; integer ARM code in main RAM, stack only.

### `_dsub`

- **Interface:** `r0:r1` = a, `r2:r3` = b. Returns `r0:r1` = a - b.
  Clobbers `r2`, `r3`, `ip`; saves and restores `r4` and `lr` (8 bytes of
  stack). When the signs differ it flips b's sign and branches into `_dadd`
  at `func_02022b14`. `func_02022e44` (`_dsub` + 0x10) is a global entry that
  skips the push and the sign test.
- **Behavior:** IEEE binary64 subtraction, round to nearest even, gradual
  underflow, overflow to ±infinity. An exact zero difference is `+0`
  (`-0 - +0` is `-0`). `inf - inf` of one sign and any NaN operand return
  `0x7fffffff_ffffffff`.
- **Hardware:** none; integer ARM code in main RAM, stack only.

### `_drsb`

- **Interface:** `r0:r1` = a, `r2:r3` = b. Returns `r0:r1` = b - a. Six
  `eor` instructions swap the register pairs, then execution falls through
  into `_dsub`, which immediately follows it; clobbers and stack as `_dsub`.
- **Behavior:** reverse subtraction, `_dsub(b, a)`, with `_dsub`'s rounding
  and NaN rules.
- **Hardware:** none; must stay directly in front of `_dsub` in memory.

### `_dmul`

- **Interface:** `r0:r1` = a, `r2:r3` = b. Returns `r0:r1` = a * b.
  Clobbers `r2`, `r3`, `ip`; saves and restores `r4`-`r7` and `lr` (20 bytes
  of stack). Builds the 106-bit product from four `umull`s.
- **Behavior:** IEEE binary64 multiplication, round to nearest even,
  gradual underflow, overflow to ±infinity. `inf * finite non-zero` is a
  signed infinity; `0 * inf` and any NaN operand return
  `0x7fffffff_ffffffff`.
- **Hardware:** none; integer ARM code in main RAM, stack only.

### `_ddiv`

- **Interface:** `r0:r1` = a, `r2:r3` = b. Returns `r0:r1` = a / b.
  Clobbers `r2`, `r3`, `ip`; saves and restores `r4`-`r6` and `lr` (16 bytes
  of stack). The 256-byte reciprocal seed table at `_ddiv` + 0x138 (after the
  main path's returns, read with a PC-relative `ldrb`) is data inside the
  routine.
- **Behavior:** IEEE binary64 division, round to nearest even, gradual
  underflow, overflow to ±infinity; the table-seeded reciprocal estimate is
  corrected from the remainder, so the quotient is correctly rounded. `x / 0`
  (x finite non-zero) and `inf / x` give a signed infinity, `x / inf` a signed
  zero. Unlike the other routines it propagates NaNs, and its rules are its
  own ("quiet" means bit 51 set; quieting ORs `0x7ff80000` into the high
  word):
  - a is a signaling NaN: a quieted, whatever b is.
  - a is a quiet NaN: b if b is also a quiet NaN, otherwise a.
  - a is not a NaN and b is a quiet NaN: b.
  - a is not a NaN and b is a signaling NaN: a quiet NaN built from a. For
    a = ±0 or ±inf it is a quieted (a's sign, zero payload); for finite
    non-zero a it is positive, `0x7ff8...` ORed with a's 52 fraction bits,
    where a denormal's fraction is first normalized (shifted left until its
    leading one reaches the hidden-bit position, which is then dropped).
  - `0 / 0` and `inf / inf`: a quieted, i.e. `0x7ff80000_00000000` with a's
    sign.
- **Hardware:** none; integer ARM code in main RAM, stack only. The table is
  addressed relative to the PC, so the code and table must move together.

### `_drdiv`

- **Interface:** `r0:r1` = a, `r2:r3` = b. Returns `r0:r1` = b / a. Six
  `eor` instructions swap the register pairs, then execution falls through
  into `_ddiv`, which immediately follows it; clobbers and stack as `_ddiv`.
- **Behavior:** reverse division, `_ddiv(b, a)`, with `_ddiv`'s rounding
  and NaN rules (applied to the swapped operands, so the divisor is the
  original a).
- **Hardware:** none; must stay directly in front of `_ddiv` in memory.

## Square root

### `MSL_Sqrt`

- **Interface:** `r0:r1` = x (double, low word first). Returns `r0:r1` =
  sqrt(x). Clobbers `r2`, `r3`, `ip`; saves and restores `r4`-`r6` and `lr`
  (16 bytes of stack). On a domain error it stores 33 (`EDOM`) to the MSL
  `errno` variable (`gMslErrno`, `0x0205fdbc`); otherwise memory is
  untouched.
- **Behavior:** correctly rounded IEEE square root (bit-by-bit integer
  root with a sticky bit; a square root is never exactly halfway, so the
  result is the nearest double), denormal inputs included. `sqrt(+0)` = `+0`,
  `sqrt(-0)` = `-0` and `sqrt(+inf)` = `+inf`, with `errno` untouched. Every
  negative non-zero x (including `-inf` and negative denormals) and every NaN
  returns x with `0x7ff80000` ORed into the high word, so a negative operand
  gives a NaN that keeps its sign bit and fraction bits (`-1.0` gives
  `0xfff80000_00000000`), and a NaN operand comes back quieted with its
  payload. Both cases set `errno` = `EDOM`; C only requires that for
  negative x, not for a NaN argument.
- **Hardware:** one 32-bit store to `gMslErrno` in main RAM on a domain
  error; otherwise integer ARM code with stack access only.
