# MSL / CodeWarrior runtime helpers

Hand-written ARM routines from the CodeWarrior for DS runtime library. The
compiler emits calls to them for operations the ARM946E-S has no instruction
for. Each section below is checked by `tools/sdklib/verify_sdklib.py`, which
runs the ROM's own instructions against the Python model in
`tools/sdklib/families/`; see [PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

A port can replace every routine here with the host compiler's own `/`, `%`
and floating-point operators; only the edge cases listed under Behavior
differ from C.

## 32-bit division

### `_u32_div_f`

- **Interface:** `r0` = dividend, `r1` = divisor (both `u32`). Returns the
  quotient in `r0` and the remainder in `r1`. Clobbers `r2`, `r3` and the
  condition flags; uses no stack. A second entry, `_u32_div_not_0_f`
  (`_u32_div_f` + 8), skips the zero test for callers that know the divisor is
  non-zero.
- **Behavior:** unsigned truncating division. A zero divisor returns the
  dividend unchanged in `r0` and 0 in `r1` (no trap). A dividend smaller than
  the divisor returns quotient 0 and the dividend as remainder without
  entering the loop. Otherwise it normalizes the dividend with up to three
  shift steps (16, 8, 4 bits) and jumps into an unrolled shift-subtract
  sequence of `adcs`/`sublo` pairs, one per remaining quotient bit.
- **Hardware:** none; plain ARM integer instructions in main RAM, no
  interrupts, coprocessor or memory access.

### `_s32_div_f`

- **Interface:** `r0` = dividend, `r1` = divisor (both `s32`). Returns the
  quotient in `r0` and the remainder in `r1`. Clobbers `r2`, `r3`, `ip` and
  the condition flags; uses no stack.
- **Behavior:** C99 truncating signed division: the quotient is rounded
  toward zero and the remainder takes the dividend's sign. It divides the
  magnitudes with the same unrolled kernel as `_u32_div_f`, then negates the
  quotient when the operand signs differ and the remainder when the dividend
  is negative. A zero divisor returns the dividend unchanged and remainder 0.
  `INT_MIN / -1` returns `INT_MIN` with remainder 0 (the magnitude wraps).
- **Hardware:** none; plain ARM integer instructions in main RAM.
