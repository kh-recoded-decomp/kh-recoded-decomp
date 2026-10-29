# NitroSDK geometry FIFO bursts

Hand-written ARM routines from the NitroSDK `gx` library that feed the
geometry engine's command FIFO. They live in ITCM, return with `bx lr` and
follow the ARM procedure call standard (arguments in `r0`-`r3`, `r4`-`r11`
and `sp` preserved, `r0`-`r3`, `ip` and the flags free to clobber) unless a
section says otherwise. Each section below is checked by
`tools/sdklib/verify_sdklib.py`, which runs the ROM's own instructions against
the Python model in `tools/sdklib/families/sdk_gx.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

The tests map the FIFO port as plain memory and log every store, so they check
which words reach the port and in what order, not what the geometry engine
does with them; the Hardware bullets say what that is.

### `GX_SendFifo48B`

- **Interface:** `void GX_SendFifo48B(const void *src, void *dst)`. `r0` =
  source (word-aligned, twelve words), `r1` = destination port. Returns `r0` =
  source + 48 and `r1` unchanged; `r2`, `r3` and `ip` hold the last three
  source words. No stack and no flags are used.
- **Behavior:** loads the source three words at a time with `ldmia r0!` and
  stores each group with `stmia r1` (no write-back): word *i* goes to
  `dst + 4 * (i % 3)`, so the stores are words 0 to 11 in order over the same
  three addresses. For an ordinary RAM destination only the last group (words
  9 to 11) remains. The source is never written.
- **Hardware:** meant for `GXFIFO` (0x04000400), the geometry command FIFO.
  Every word written anywhere in 0x04000400-0x0400043F enters the same FIFO,
  so the three addresses act as one port and the engine receives the twelve
  words in order. The caller first writes a command word there:
  `G3_LoadMtx43` writes 0x17 (`MTX_LOAD_4x3`) and `G3_MultMtx43` writes 0x19
  (`MTX_MULT_4x3`), then both pass an `MtxFx43` (twelve fx32 values) as the
  source. The FIFO port is
  write-only and uncached; a source in main RAM must already be visible to the
  CPU, which it always is for data the CPU wrote itself. A misaligned pointer
  is not caught: `ldm`/`stm` ignore address bits 1:0 on the ARM946E-S.
