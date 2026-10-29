# NitroSDK math routines

Hand-written ARM routines from the NitroSDK `math` library (`dgt`/`sha1` and
`qsort.c`). Both follow the ARM procedure call standard: arguments in
`r0`-`r3` and then on the stack, `r4`-`r11` preserved, `r0`-`r3`, `ip` and the
flags free to clobber. Each section below is checked by
`tools/sdklib/verify_sdklib.py`, which runs the ROM's own instructions against
the Python model in `tools/sdklib/families/sdk_math.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

## Hashing

### `MATHi_SHA1ProcessBlock`

- **Interface:** `void MATHi_SHA1ProcessBlock(MATHSHA1Context *ctx)`; `r0` =
  context. Returns nothing (`r0` happens to come back unchanged). Clobbers
  `r1`-`r3` and the flags; preserves `r4`-`r12`. Uses 104 bytes of stack: a
  40-byte push of `r4`-`r12`, `lr` and a 64-byte ring of 16 message-schedule
  words. It reads the chaining value `h[0..4]` at `ctx+0x00` and the 64-byte
  block at `ctx+0x14` (the `MATHSHA1Context` layout `u32 h[5]; u8 block[64];`)
  and writes only `h`. It is reached directly and through
  `MATHi_SHA1ProcessBlockForOverlay` / the `MATHi_SHA1ProcessMessageBlockFunc`
  pointer.
- **Behavior:** one SHA-1 compression (FIPS 180-4 section 6.1.2): the block is
  read as sixteen big-endian words, expanded to 80 schedule words on the fly
  in the 16-word ring, run through the 80 rounds (Ch, Parity, Maj, Parity with
  constants `0x5a827999`, `0x6ed9eba1`, `0x8f1bbcdc`, `0xca62c1d6`) and added
  into `h` modulo 2^32. It does no padding or length counting; the callers
  feed it padded blocks. The block in the context is left untouched. There are
  no edge cases: every 64-byte block and chaining value is valid, and chaining
  it over a padded message from the standard initial value gives exactly
  `hashlib.sha1`'s digest.
- **Hardware:** none beyond memory: `ctx` must be word-aligned (both `h` and
  the block are read with `ldmia`). The four round constants are not in a
  literal pool of the routine: they are the 16-byte table
  `MATHi_SHA1RoundConstants` at `0x0200ded4`-`0x0200dee3`, immediately before
  the entry point, loaded with negative PC-relative `ldr`s (`[pc, #-0x80]`,
  `#-0x15c`, `#-0x1e4`, `#-0x278`), so the routine and that table must stay
  adjacent. Runs from main RAM; no interrupts, cache, DMA or coprocessor.

## Sorting

### `func_0200dc4c`

- **Interface:** `MATH_QSort(void *head, u32 num, u32 width,
  MATHCompareFunc comp, void *stackBuf)`; `r0` = first element, `r1` =
  element count, `r2` = element size in bytes, `r3` = comparison callback
  `s32 comp(void *a, void *b)`, and the fifth argument `stackBuf` in the word
  at `[sp]` on entry. Returns nothing. Preserves `r4`-`r11`; clobbers
  `r0`-`r3`, the flags and whatever the callback clobbers (`ip`). Called with
  `blx`, so the callback may be ARM or Thumb. Stack: a 36-byte push, one word
  holding the bit length of `width`, and, when `stackBuf` is NULL, a work area
  of `8 * bitlen(num)` bytes (`bitlen(num)` = floor(log2 num) + 1) plus a word
  recording its size, all released before returning.
- **Behavior:** sorts the array in place into ascending order as defined by
  `comp` (negative = first argument sorts before the second). It is a
  non-recursive quicksort, not stable: elements that compare equal may end up
  in any order. Each pass takes the pivot at byte offset
  `((right - left) >> bitlen(width)) * width` from the range's first element
  (the middle element when `width` is a power of two), swaps it to the front,
  partitions, swaps it into place, and pushes the two sub-ranges that have at
  least two elements as (first, last) pointer pairs on its work stack, the
  larger first, so the smaller is sorted next and the stack never holds more
  than `bitlen(num)` pairs. A two-element range is compared once and swapped if
  out of order. `num` is tested as a signed value: `num <= 1`, including any
  count of `0x80000000` or more, returns without calling `comp`. `width == 0`
  calls `comp` once and moves nothing. `comp` receives pointers into the array
  itself, sometimes both to the same element (the pivot), and must give a
  consistent total order; with an inconsistent comparator the result is some
  permutation of the input.
- **Hardware:** elements are exchanged in place with `swpb` byte by byte, or
  with `swp` word by word when `width` is a multiple of 4; in the second case
  `head` must be word-aligned. The swap instructions are only used as plain
  exchanges (their bus lock has no purpose here); a port uses an ordinary
  swap. A caller-supplied `stackBuf` must be word-aligned; the routine writes
  pointer pairs into it upward and needs at most `8 * bitlen(num)` bytes, the
  size it allocates itself for a NULL `stackBuf` (the verifier checks that a
  buffer of `8 * (floor(log2 num) + 2)` bytes is never overrun). Runs from main
  RAM; no interrupts, cache, DMA or coprocessor.
