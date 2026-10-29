# NitroSDK system routines

Hand-written ARM routines from the NitroSDK `os`, `gx` (CP), `mi` and `init`
libraries: the divider/square-root context switch, lock-ID allocation, two
interrupt/exception wrappers and the two LZ decoders. All are ARM code in main
RAM, return with `bx lr` and follow the ARM procedure call standard
(arguments in `r0`-`r3`, `r4`-`r11` and `sp` preserved, `r0`-`r3`, `ip` and
the flags free to clobber) unless a section says otherwise. Each section below
is checked by `tools/sdklib/verify_sdklib.py`, which runs the ROM's own
instructions against the Python model in `tools/sdklib/families/sdk_misc.py`;
see [PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

The tests map the I/O and system areas these routines touch as plain memory,
so they check what each routine reads and writes, not what the hardware does
in response; the Hardware bullets say what that is. The wrappers are tested
with their callees replaced by stubs that log every call. The LZ decoders are
fed streams from compressors written in the model from the format
descriptions below.

## Divider and square-root context

The ARM9's math unit lives at 0x04000280-0x040002BF: `DIVCNT` (0x280),
`DIV_NUMER` (0x290, 64-bit), `DIV_DENOM` (0x298, 64-bit), `DIV_RESULT`
(0x2A0), `DIVREM_RESULT` (0x2A8), `SQRTCNT` (0x2B0), `SQRT_RESULT` (0x2B4)
and `SQRT_PARAM` (0x2B8, 64-bit). The context is the SDK's `CPContext`, 0x1C
bytes: `u64 div_numer; u64 div_denom; u64 sqrt; u16 div_mode; u16 sqrt_mode;`.
Thread switches save and restore it so that every thread owns the unit:
`OS_SaveContext` / `OS_LoadContext`, the ITCM IRQ thread-switch handler
`OS_IrqHandler_ThreadSwitch` and the game's `DispObjList_Update` call these two routines.

### `CP_SaveContext`

- **Interface:** `void CP_SaveContext(CPContext *context)`; `r0` = context,
  word-aligned. Returns nothing; `r0` comes back as `context + 0x18`.
  Clobbers `r1`-`r3` and `ip`; the flags are untouched. Uses 4 bytes of stack
  (a push of `r4`).
- **Behavior:** copies `DIV_NUMER`, `DIV_DENOM` and `SQRT_PARAM` verbatim into
  `div_numer`, `div_denom` and `sqrt`, then stores `DIVCNT & 3` (the divide
  mode) in `div_mode` and `SQRTCNT & 1` (the square-root mode) in
  `sqrt_mode`, dropping the busy and divide-by-zero bits. The three result
  registers are not saved; restoring recomputes them.
- **Hardware:** reads the math unit with word `ldm` and halfword `ldrh`
  accesses (I/O, uncached). It does not wait for the busy bits (`DIVCNT` bit
  15, `SQRTCNT` bit 15): the operand registers keep the values written to them
  while a computation runs, so the save is valid at any moment. It does not
  disable interrupts.

### `CPi_RestoreContext`

- **Interface:** `void CPi_RestoreContext(const CPContext *context)`; `r0` =
  context, word-aligned. Returns nothing; `r0` comes back as
  `context + 0x10`. Clobbers `r1`-`r3` and `ip`; the flags are untouched.
  Uses 4 bytes of stack (a push of `r4`).
- **Behavior:** writes, in this order, `div_numer` and `div_denom` to
  `DIV_NUMER`/`DIV_DENOM` (four words), `div_mode` to `DIVCNT` and
  `sqrt_mode` to `SQRTCNT` (whole halfwords, as stored), then `sqrt` to
  `SQRT_PARAM` (two words). It reads nothing from the hardware.
- **Hardware:** writing `DIVCNT`, `DIV_NUMER` or `DIV_DENOM` starts a new
  division and writing `SQRTCNT` or `SQRT_PARAM` starts a new square root,
  setting the busy bit until the result is ready (GBATEK: 18 cycles for
  32/32, 34 for 64-bit divisions, 13 for the square root). Because the last
  write to each unit carries the restored operands and mode, the units end
  up recomputing the results the resumed thread was waiting for. The
  read-only bits of `DIVCNT`/`SQRTCNT` ignore the written values. The test
  maps the block as memory and checks only the stores.

## Lock IDs

### `OS_GetLockID`

- **Interface:** `s32 OS_GetLockID(void)`. Returns the new ID in `r0`, or
  `OS_LOCK_ID_ERROR` (-3, `0xFFFFFFFD`) when none is free. Clobbers `r1`-`r3`
  and the flags; uses no stack.
- **Behavior:** the ARM9's lock IDs are a 64-bit free map in two words at
  0x02FFFFB0 and 0x02FFFFB4, a set bit meaning free. It returns the lowest
  free ID: word 0 covers IDs 0x40-0x5F from bit 31 down to bit 0, word 1 IDs
  0x60-0x7F the same way, so the ID is `0x40 + clz(word0)` or
  `0x60 + clz(word1)`. It clears that bit. When both words are zero it
  returns -3 and writes nothing. Releasing an ID (setting its bit again) is
  another routine's job. Callers in this ROM: `GX_Init`, `CARDi_InitRom`,
  `FSi_InitRomArchive`, `InitSaveSystem` and `OS_ResetSystem`.
- **Hardware:** the map is in the system area at the top of main RAM,
  addressed through the 0x02FFxxxx mirror (on a 4 MB console the address
  aliases offset 0x3FFFB0 of main RAM). The update is a plain load, `clz`,
  `bic`, store with interrupts enabled, so it is not atomic: an interrupt
  handler that also allocates an ID between the load and the store could be
  given the same ID. All callers here run at initialization from thread code.

## Interrupt and exception wrappers

### `OSi_AlarmHandler`

- **Interface:** `void OSi_AlarmHandler(void *arg)`, an IRQ callback; `r0` is
  ignored and comes back unchanged. Pushes `r0` and `lr` (8 bytes of stack),
  calls `OSi_ArrangeTimer`, pops them and returns. `r1`-`r3`, `ip` and the
  flags are whatever `OSi_ArrangeTimer` leaves; `r4`-`r11` are preserved.
- **Behavior:** it only forwards to `OSi_ArrangeTimer`, which runs the alarms
  that are due and programs the hardware timer for the next one. Pushing `r0`
  alongside `lr` keeps `sp` 8-byte aligned across the call.
- **Hardware:** none of its own. `OSi_SetTimer` installs it as the interrupt
  handler of the alarm system's hardware timer, so it runs from the SDK's IRQ
  dispatcher, in IRQ context on the IRQ stack.

### `OSi_GetAndDisplayContext`

- **Interface:** no arguments of its own. Pushes `r0` and `lr` (8 bytes of
  stack), calls `OSi_SetExContext` and then `OSi_DisplayExContext`, pops them
  and returns with `r0` as it was on entry. The second callee receives
  whatever the first left in `r0`-`r3` and `ip`; on return those (except
  `r0`) and the flags are what the second leaves. `r4`-`r11` are preserved.
- **Behavior:** the exception handler's "capture, then report" step:
  `OSi_SetExContext` copies the registers of the faulting code into the
  exception context and `OSi_DisplayExContext` calls the user's exception
  callback with it, if one is installed, switching to system mode for the
  call. The wrapper itself only sequences the two calls.
- **Hardware:** none of its own. `OSi_ExceptionHandler` calls it in abort or
  undefined-instruction mode, after switching `sp` to its frame at the top of
  ITCM, so it runs on that small exception stack.

## LZ decompression

### `MI_ReadUncompLZ8`

- **Interface:** `s32 MI_ReadUncompLZ8(MIUncompContextLZ *context, const u8
  *data, u32 len)`; `r0` = context, `r1` = next input bytes, `r2` = how many.
  Returns the remaining output count (`context->destCount`) in `r0`: 0 when
  the output is complete, negative if the last reference ran past it.
  Preserves `r4`-`r11` (32 bytes of stack); clobbers `r1`-`r3` and the flags.
  The context (0x14 bytes: `u8 *destp; s32 destCount; u32 length; u16
  destTmp; u8 destTmpCnt, flags, flagIndex, lengthFlg, exFormat, pad`) is set
  up by `MI_InitUncompContextLZ` from the 4-byte header (`destCount` = size,
  `lengthFlg` = 3, `exFormat` = 1 when the header's low nibble is non-zero,
  everything else 0); the caller then passes the stream after the header in
  pieces of any size, including 0. `destTmp` and `destTmpCnt` are not used.
- **Behavior:** streaming LZ77 in Nintendo's type-0x10 format, or the
  extended type-0x11 format when `exFormat == 1`. A flag byte announces eight
  tokens, most significant bit first: 0 = one literal byte, 1 = a reference.
  A reference is a length field and then a byte that, with the low nibble of
  the field's last byte as its top four bits, gives `distance - 1`
  (distance 1-4096); it copies `length` bytes one at a time from `distance`
  bytes behind the write pointer, so overlapping copies repeat a pattern.
  Type 0x10: the field is one byte, length = high nibble + 3 (3-18). Type
  0x11: high nibble >= 2: one byte, length = nibble + 1 (3-16); 0: two bytes,
  length = 0x11 + the 8 bits after the nibble (17-272); 1: three bytes,
  length = 0x111 + the 16 bits after the nibble (273-65808). Every input
  byte is consumed in order, and the context remembers where the stream was
  cut: the current flag byte (`flags`, shifted so bit 7 is the next token's)
  and its remaining tokens (`flagIndex`), and inside a reference the length
  field read so far (`length` = bias + bits, kept as `count << 4 |
  distance_high`) with `lengthFlg` = length bytes still due (3 = none read,
  0 = field complete, displacement byte next). The output count is tested
  only between tokens: the call returns as soon as a token leaves `destCount`
  at exactly 0, or before a new flag group when `destCount <= 0`, so a
  reference that crosses the end is copied whole and further tokens of the
  same flag byte are still decoded. Unused input after the end is ignored.
  Nothing is validated: a distance reaching before the output start reads
  whatever lies there.
- **Hardware:** each output byte is stored with `swpb` (a locked read of the
  old destination byte, which is discarded, then a byte write), so the
  effect is an ordinary byte store; a port writes bytes. The destination must
  accept 8-bit writes (main RAM, shared WRAM or the TCMs), not VRAM, which
  ignores 8-bit writes from the ARM9. No cache maintenance: callers such as
  `FileLoader_ThreadMain` flush the destination themselves before DMA or
  another CPU reads it. Runs with interrupts enabled; one context must not be
  used by two threads at once.

### `MIi_UncompressBackward`

- **Interface:** `void MIi_UncompressBackward(void *bottom)`; `r0` = end of
  the compressed image, word-aligned. A NULL `bottom` returns at once. Returns
  `r0` = 0. Preserves `r4`-`r11` (16 bytes of stack for `r4`-`r7`);
  clobbers `r1`-`r3`, `ip` and the flags. Called by the crt0 entry (`Entry`)
  for the static ARM9 module and by `FS_StartOverlay` for compressed
  overlays.
- **Behavior:** in-place decoding of the SDK's backward LZ ("autoload"
  compression). The two words below `bottom` are the footer: `bottom[-8]`
  holds the compressed-region size in bits 0-23, measured down from `bottom`
  and including the footer, and the footer size (8 plus padding) in bits
  24-31; `bottom[-4]` is the size gain, so the data ends at `bottom + gain`.
  Bytes below the compressed region are an uncompressed head and are not
  touched. It reads downward from `bottom - footer size` and writes downward
  from `bottom + gain`: a flag byte, most significant bit first, 0 = one
  literal byte, 1 = a reference of two bytes read high then low, length =
  `(high >> 4) + 3` (3-18), copying each byte from `((high << 8 | low) &
  0xFFF) + 3` bytes above the byte being written (distance 3-4098). It stops
  after the token that brings the read pointer down to the start of the
  compressed region, even inside a flag group. The output overwrites the
  compressed bytes and the footer; the compressor keeps the write pointer
  above the read pointer by leaving enough of the head uncompressed. Nothing
  is validated, and the address comparisons are signed (harmless for RAM
  addresses).
- **Hardware:** after decoding, for every 32-byte line from the compressed
  start (rounded down to 32) up to `bottom + gain` (at least one line), it
  drains the write buffer (`mcr p15, 0, r0, c7, c10, 4` with `r0` = 0),
  invalidates the instruction-cache line (`c7, c5, 1`) and cleans and
  invalidates the data-cache line (`c7, c14, 1`), so the decompressed code
  reaches main RAM and instruction fetches see it. CP15 access needs a
  privileged mode (the SDK runs in system or supervisor mode). It lives in
  the uncompressed crt0 part of the static module, below anything it
  decompresses. `arm_exec.py` treats these c7 maintenance operations as
  no-ops and records them; the test compares the recorded sequence with the
  model's.
