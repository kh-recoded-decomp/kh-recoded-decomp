# NitroSDK matrix helpers

Hand-written routines from the NitroSDK `mtx` library
(`libs/nitro/mtx/asm_stubs/auto/`) that fill or convert fixed-point
matrices, plus `MI_Zero36B` from `mi`, which NNS G3D uses to clear a 3x3
matrix. Each section below is checked by `tools/sdklib/verify_sdklib.py`,
which runs the ROM's own instructions against the Python models in
`tools/sdklib/families/sdk_mtx.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md). The ARM routines and the THUMB
ones are checked the same way: every case writes a matrix inside a 512-byte
window of random bytes and compares the whole window afterwards.

A port can replace each routine with the C assignments its Behavior bullet
lists.

## Shared context

- **Element type.** `fx32` is a signed 32-bit fixed-point number with 12
  fraction bits: 1.0 = 0x1000, -1.0 = 0xFFFFF000.
- **Layouts.** All matrices are row-major arrays of `fx32`; element `_rc`
  is row `r`, column `c`, at byte offset `4 * (r * columns + c)`.
  `MtxFx22` is 2x2 (16 bytes), `MtxFx33` 3x3 (36 bytes), `MtxFx44` 4x4
  (64 bytes). `MtxFx43` is four rows of three (48 bytes): rows 0-2 are the
  3x3 linear part and row 3 (`_30`, `_31`, `_32`) the translation, i.e. a
  4x4 affine matrix whose fourth column (0, 0, 0, 1.0) is implied. Vectors are
  rows multiplied from the left, as in the DS geometry engine.
- **Calling.** Arguments in `r0`-`r2`, no result. Every routine writes the
  whole destination matrix and nothing else; the pointer registers come back
  advanced past the data and `r1`-`r3`, `ip` are clobbered. None uses the
  stack except `MTX_Copy43To44_`. THUMB routines also clobber the condition
  flags; the ARM ones leave them alone.
- **Alignment.** Matrices are stored with `stm` and `str`, which on the
  ARM946E-S ignore address bits 1-0, so every matrix pointer must be 4-byte
  aligned; an unaligned pointer writes the aligned words below it.
- **Placement.** The `_` suffix marks the SDK's assembly versions behind the
  `MTX_*` inline wrappers. Some sit in ITCM for speed; none has a literal pool
  or an absolute address, so the code itself would run from any memory.

## Identity

### `MTX_Identity22_`

- **Interface:** `void MTX_Identity22_(MtxFx22 *m)`, ARM, 0x18 bytes at
  0x02005944. `r0` = matrix. Leaves `r0` = `m` + 16, `r1` = 0, `r2` =
  0x1000, `r3` = 0.
- **Behavior:** writes the 2x2 identity: `_00 = _11 = 0x1000`, `_01 = _10 =
  0`, in address order with two two-word stores.
- **Hardware:** none beyond the alignment above; ARM code in main RAM, plain
  stores through the data cache and write buffer.

### `MTX_Identity33_`

- **Interface:** `void MTX_Identity33_(MtxFx33 *m)`, ARM, 0x24 bytes at
  0x01FF90EC (ITCM). `r0` = matrix. Leaves `r0` = `m` + 32, `r1` = 0, `r2`
  = 0x1000, `r3` = 0.
- **Behavior:** writes the 3x3 identity: `_00 = _11 = _22 = 0x1000`, the
  other six elements 0. It stores `_22` (offset 0x20) first, then `_00`-`_21`
  in address order.
- **Hardware:** runs from ITCM; plain stores, alignment as above.

### `MTX_Identity43_`

- **Interface:** `void MTX_Identity43_(MtxFx43 *m)`, ARM, 0x28 bytes at
  0x01FF9480 (ITCM). `r0` = matrix. Leaves `r0` = `m` + 48, `r1` = 0, `r2`
  = 0x1000, `r3` = 0.
- **Behavior:** writes the 4x3 identity: `_00 = _11 = _22 = 0x1000`, every
  other element including the translation row `_30`-`_32` 0, in address
  order.
- **Hardware:** runs from ITCM; plain stores, alignment as above.

### `MTX_Identity44_`

- **Interface:** `void MTX_Identity44_(MtxFx44 *m)`, ARM, 0x2c bytes at
  0x020059BC. `r0` = matrix. Leaves `r0` = `m` + 64, `r1` = 0, `r2` =
  0x1000, `r3` = 0.
- **Behavior:** writes the 4x4 identity: `_00 = _11 = _22 = _33 = 0x1000`,
  the other twelve elements 0, in address order.
- **Hardware:** none beyond the alignment above; ARM code in main RAM.

## Conversion

### `MTX_Copy43To44_`

- **Interface:** `void MTX_Copy43To44_(const MtxFx43 *src, MtxFx44 *dst)`,
  ARM, 0x34 bytes at 0x01FF94A8 (ITCM). `r0` = source, `r1` = destination.
  Leaves `r0` = `src` + 48 and `r1` = `dst` + 64; clobbers `r2`, `r3`,
  `ip`. Saves and restores `r4` on the stack (4 bytes).
- **Behavior:** `dst` row `r` = `src` row `r` followed by a fourth element,
  0 for rows 0-2 and 0x1000 for row 3, so `dst` is the full affine 4x4 form.
  It reads and writes one row at a time in ascending order. The buffers must
  not overlap (the destination is larger, so writing it in place would
  overwrite source rows before they are read).
- **Hardware:** runs from ITCM; plain loads and stores, alignment as above.

### `MTX_Copy44To43_`

- **Interface:** `void MTX_Copy44To43_(const MtxFx44 *src, MtxFx43 *dst)`,
  ARM, 0x34 bytes at 0x020059E8. `r0` = source, `r1` = destination. Leaves
  `r0` = `src` + 64 and `r1` = `dst` + 48; clobbers `r2`, `r3`, `ip`; no
  stack.
- **Behavior:** `dst` row `r` = the first three elements of `src` row `r`,
  for rows 0-3; the source's fourth column is ignored, not checked to be
  (0, 0, 0, 1.0). It reads each row before writing it, in ascending order, so
  `dst == src` works and compacts the matrix in place; other overlaps are not
  supported.
- **Hardware:** none beyond the alignment above; ARM code in main RAM.

## Rotation

### `MTX_RotX43_`

- **Interface:** `void MTX_RotX43_(MtxFx43 *m, fx32 sin, fx32 cos)`, THUMB,
  0x1e bytes at 0x01FF9510 (ITCM), entered at 0x01FF9511 by `blx`/`bl` and
  returning with `bx lr`. `r0` = matrix, `r1` = sine, `r2` = cosine of the
  angle. Leaves `r0` = `m` + 48, `r1` = 0, `r3` = 0; clobbers the flags.
- **Behavior:** writes the rotation about the X axis with zero translation:
  `_00 = 0x1000`, `_11 = _22 = cos`, `_12 = sin`, `_21 = -sin`, all other
  elements 0. The sine and cosine are stored as given, not checked or
  normalized; `-sin` is the two's-complement negation, so 0x80000000 stays
  0x80000000 (C would overflow). It stores `_12` and `_21` first.
- **Hardware:** runs from ITCM; plain stores, alignment as above. The zero
  halfword after it (0x01FF952E) aligns the next routine.

### `MTX_RotY43_`

- **Interface:** `void MTX_RotY43_(MtxFx43 *m, fx32 sin, fx32 cos)`, THUMB,
  0x1a bytes at 0x01FF9530 (ITCM), entered at 0x01FF9531. `r0` = matrix,
  `r1` = sine, `r2` = cosine. Leaves `r0` = `m` + 48, `r1` = 0, `r3` = 0;
  clobbers the flags.
- **Behavior:** writes the rotation about the Y axis with zero translation:
  `_00 = _22 = cos`, `_11 = 0x1000`, `_02 = -sin`, `_20 = sin`, all other
  elements 0. Same argument handling as `MTX_RotX43_`. It stores `_20` first.
- **Hardware:** runs from ITCM; plain stores, alignment as above. The zero
  halfword after it (0x01FF954A) aligns the next ARM routine.

## Memory clear

### `MI_Zero36B`

- **Interface:** `void MI_Zero36B(void *dst)`, THUMB, 0xe bytes at
  0x01FF90DC (ITCM), entered at 0x01FF90DD. `r0` = destination. Leaves `r0`
  = `dst` + 36 and `r1`-`r3` = 0; clobbers the flags; no stack.
- **Behavior:** sets the 36 bytes at `dst` to zero with three three-word
  stores, i.e. `memset(dst, 0, 36)` for a word-aligned `dst`; NNS G3D calls
  it to clear an `MtxFx33`.
- **Hardware:** runs from ITCM; `dst` must be 4-byte aligned (`stmia`
  ignores address bits 1-0). The zero halfword after it (0x01FF90EA)
  aligns the next ARM routine.
