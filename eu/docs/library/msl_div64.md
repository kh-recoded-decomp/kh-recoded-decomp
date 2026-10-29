# MSL 64-bit division

Hand-written ARM routines from the CodeWarrior for DS runtime library that the
compiler calls for `/` and `%` on `long long` and `unsigned long long`. Each
section below is checked by `tools/sdklib/verify_sdklib.py`, which runs the
ROM's own instructions against the Python model in
`tools/sdklib/families/msl_div64.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

All four take the dividend in `r0:r1` and the divisor in `r2:r3`, low word
first (`r0` = bits 0-31, `r1` = bits 32-63), and return their 64-bit result in
`r0:r1`. They save `r4`-`r7`, `fp` (`r11`), `ip` (`r12`) and `lr` with one
28-byte push and restore them on every exit, so the only registers changed
are `r0`-`r3` and the flags; `sp` is unchanged on return. Calls they make
(`_u32_div_not_0_f`, `_s32_div_f`) happen inside that frame.

The four entries are one shared body. `r4` is the mode word: bit 0 set selects
the remainder, bit 31 set means the result is negated at the end. The entries
only set `r4` and branch into it at three global labels:

- `__ull_div_common` (`_ull_mod` + 8): unsigned body; tests the divisor for
  zero, divides two 32-bit operands with `_u32_div_not_0_f` and otherwise
  jumps to `__ll_div_magnitude_common`.
- `__ll_div_signed_entry` (`_ll_sdiv` + 16): signed body; tests the divisor
  for zero, divides two 32-bit-range operands with `_s32_div_f`, otherwise
  takes the magnitudes and falls into `__ll_div_magnitude_common`.
- `__ll_div_magnitude_common` (`_ll_sdiv` + 0x74): shift-subtract division of
  two unsigned 64-bit magnitudes with a 65-bit partial remainder (`r0:r1:r7`),
  the quotient in `ip:fp`; returns the quotient or the remainder and negates
  it when `r4` is negative.

A port can replace every routine with the host compiler's 64-bit `/` and `%`;
only the zero-divisor and `INT32_MIN / -1` cases listed under Behavior differ
from C.

## 64-bit division

### `_ll_udiv`

- **Interface:** `r0:r1` = dividend, `r2:r3` = divisor (both `u64`). Returns
  the quotient in `r0:r1`. Clobbers `r2`, `r3` and the flags; preserves
  `r4`-`r12`; 28 bytes of stack. The routine is three instructions: it pushes
  the frame, sets the mode word to 0 and branches to `__ull_div_common` inside
  `_ull_mod`, which returns for it.
- **Behavior:** unsigned truncating division, `a / b`. A zero divisor returns
  the dividend unchanged in `r0:r1` (no trap). When both high words are zero it
  divides the low words with `_u32_div_not_0_f` and returns a zero high word;
  otherwise it runs the 64-bit shift-subtract loop. A zero dividend returns 0.
- **Hardware:** none; plain ARM integer instructions in main RAM, touching only
  its own stack frame (no interrupts, coprocessor or other memory).

### `_ull_mod`

- **Interface:** `r0:r1` = dividend, `r2:r3` = divisor (both `u64`). Returns
  the remainder in `r0:r1`. Clobbers `r2`, `r3` and the flags; preserves
  `r4`-`r12`; 28 bytes of stack. Its body from `+8` on is the global entry
  `__ull_div_common` that `_ll_udiv` also uses; with both high words zero it
  calls `_u32_div_not_0_f`, otherwise it branches to
  `__ll_div_magnitude_common` inside `_ll_sdiv`, which returns for it.
- **Behavior:** unsigned remainder, `a % b`. A zero divisor returns the
  dividend unchanged (no trap). The 64-bit loop leaves the remainder shifted
  left by the divisor's normalisation count; it shifts it back right before
  returning, so the result is the exact remainder.
- **Hardware:** none; plain ARM integer instructions in main RAM.

### `_ll_sdiv`

- **Interface:** `r0:r1` = dividend, `r2:r3` = divisor (both `s64`). Returns
  the quotient in `r0:r1`. Clobbers `r2`, `r3` and the flags; preserves
  `r4`-`r12`; 28 bytes of stack. Its symbol range holds the whole shared body:
  `__ll_div_signed_entry` (+16, entered by `_ll_mod`) and
  `__ll_div_magnitude_common` (+0x74, entered by `_ull_mod`). Two words at
  `0x02023d28`-`0x02023d2f` (`lsr r0, r1, r7; mov r1, #0`, right after an
  unconditional branch) are unreachable dead code: the `bge` that would use
  them targets the identical `mov r1, #0` at `0x02023d54` instead. The
  verifier declares them unreachable and counts them apart, since no input
  can execute them.
- **Behavior:** C99 truncating signed division, rounded toward zero. Mode word
  = sign of `dividend ^ divisor`, so the quotient is negated when the signs
  differ. A zero divisor returns the dividend unchanged. When both operands
  fit in `s32` (high word equal to the sign of the low word) it uses
  `_s32_div_f` and sign-extends the 32-bit quotient: `INT32_MIN / -1`
  (`0xffffffff80000000 / -1`) therefore returns `0xffffffff80000000`
  (-2147483648) rather than C's +2147483648. Wider operands are divided as
  magnitudes; `INT64_MIN / -1` wraps to `INT64_MIN`.
- **Hardware:** none; plain ARM integer instructions in main RAM.

### `_ll_mod`

- **Interface:** `r0:r1` = dividend, `r2:r3` = divisor (both `s64`). Returns
  the remainder in `r0:r1`. Clobbers `r2`, `r3` and the flags; preserves
  `r4`-`r12`; 28 bytes of stack. Four instructions: push, mode word =
  `dividend_high | 1`, branch to `__ll_div_signed_entry` inside `_ll_sdiv`,
  which returns for it.
- **Behavior:** C99 signed remainder: `a - (a / b) * b` with truncating
  division, so the result takes the dividend's sign (mode word bit 31 is the
  dividend's sign). A zero divisor returns the dividend unchanged. Operands
  that both fit in `s32` use `_s32_div_f`'s remainder, sign-extended;
  `INT32_MIN % -1` and `INT64_MIN % -1` return 0, as in C.
- **Hardware:** none; plain ARM integer instructions in main RAM.
