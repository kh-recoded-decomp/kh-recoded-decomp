# NitroSDK BIOS call wrappers

Eighteen THUMB veneers from the NitroSDK `os` library
(`libs/nitro/os/asm_stubs/auto/`), each `swi #n` then `bx lr`, that call
functions of the ARM9 BIOS. The BIOS is not part of the game: a port replaces
each veneer with a host function that does what the Behavior bullet says. The
models in `tools/sdklib/families/sdk_bios.py` (division, square root, CRC-16,
CpuSet, BitUnPack and the LZ77, RL and Huffman decoders) are that reference.

**What is verified.** `verify_sdklib.py` runs each THUMB veneer in
`tools/mobiclip/arm_exec.py`, which records each THUMB `swi` in
`Cpu.swi_log` as (8-bit comment, r0-r3) and continues without running the
BIOS. Its `veneer_cases` checks that exactly one SWI with the veneer's number
is made, that r0-r3 reach it unchanged (r2 cleared for `VBlankIntrWait`), that
r0-r3 after `bx lr` are what the unexecuted BIOS left (for `Mod`, r0 = r1,
with N and Z from it and C and V clear), and that r4-r12 and sp are intact.
The BIOS behavior below is documentation and model, not something the gate
executes. The CRC-16 model was checked against the cartridge
header (`GetCRC16`); the decoders against compressors written from the same
format descriptions, the LZ77 one being the compressor that tests the ROM's own
`MI_ReadUncompLZ8` in [sdk_misc.md](sdk_misc.md).

Sources: "(GBATEK)" marks BIOS behavior as documented by GBATEK; "(ARM)" marks
ARMv5 architecture behavior. Anything not marked is read from the veneer bytes
or the model.

## Shared context

- **Calling.** Each veneer is THUMB code in main RAM, reached with `blx` from
  ARM or `bl` from THUMB, and returns with `bx lr`. It has no stack frame of its
  own. Arguments and results are the BIOS function's registers, listed per
  routine; as for any procedure call, callers treat `r0`-`r3`, `ip` and the
  flags as clobbered.
- **Function number.** In THUMB state the 8-bit `swi` immediate is the BIOS
  function number. ARM-state code must encode it in bits 16-23 (`swi
  #0xNN0000`) (GBATEK).
- **BIOS entry.** The ARM9 BIOS ROM is mapped at 0xFFFF0000 and the ARM9 uses
  the high exception vectors there (GBATEK). `swi` saves CPSR in SPSR_svc,
  switches to supervisor mode in ARM state with IRQs masked, puts the return
  address in `lr_svc` and jumps to the SWI vector, 0xFFFF0008 (ARM). The BIOS
  therefore needs a valid supervisor-mode stack, which the SDK's startup code
  sets up. A veneer must not be called from supervisor mode: the exception
  overwrites `lr_svc`, which is then the veneer's own `lr`, so its `bx lr`
  would return to itself (ARM).
- **Wait functions.** `Halt`, `IntrWait` and `VBlankIntrWait` return only after
  an interrupt; they need the interrupt enabled in IE and, for the last two, an
  IRQ handler that records it in the check-flags word at DTCM+0x3FF8 (GBATEK).

## Compressed-data formats and callbacks

Every compressed stream starts with a 32-bit little-endian header: bits 4-7
the type (1 = LZ77, 2 = Huffman, 3 = run-length), bits 8-31 the decompressed
size in bytes; for Huffman, bits 0-3 are the symbol width (GBATEK).

- **LZ77 (type 1).** A flag byte announces the next eight tokens, most
  significant bit first. A 0 bit is one literal byte. A 1 bit is a two-byte
  reference: the first byte's high nibble is length - 3 (3-18 bytes), its low
  nibble and the second byte are distance - 1 (12 bits, 1-4096 bytes back in the
  output) (GBATEK). A reference may be longer than its distance; it then
  repeats the bytes it is producing.
- **Run-length (type 3).** A flag byte: bit 7 clear means (bits 0-6) + 1
  literal bytes follow (1-128); bit 7 set means the next byte is repeated
  (bits 0-6) + 3 times (3-130) (GBATEK).
- **Huffman (type 2).** Byte 4 is the tree size: the tree occupies
  (byte + 1) * 2 bytes from offset 4, so the root node is at offset 5, and the
  bitstream follows the tree. A node byte holds a 6-bit offset (bits 0-5) and
  two end flags, bit 7 for child 0 and bit 6 for child 1. The children are the
  byte pair at (node address & ~1) + offset * 2 + 2; a child whose end flag is
  set holds a symbol value, otherwise it is the next node. The bitstream is read
  in 32-bit little-endian words, most significant bit first, 0 selecting child 0;
  after each symbol decoding restarts at the root. Symbols (4 or 8 bits) are
  packed least significant first into 32-bit output words (GBATEK).
- **Read Normal / Write8bit** variants read the stream directly from memory
  and store the output byte by byte. **Write16bit** variants store 16-bit units
  so the output can go to VRAM, which does not take 8-bit writes; Huffman
  stores 32-bit units (GBATEK).
- **ReadByCallback** variants (SWI 12h, 13h, 15h) read the stream through
  caller functions instead: `r2` is a user parameter and `r3` points to a table
  of five function pointers, each ARM or THUMB by address bit 0 (GBATEK):
  `+0x00 Open` (`r0` = source, `r1` = destination, `r2` = user parameter;
  returns the header word, or a negative error code to abort), `+0x04 Close`
  (optional, 0 = none; returns 0 or positive, or a negative error code),
  `+0x08 Get8bit`, `+0x0C Get16bit` (not used) and `+0x10 Get32bit` (used by
  Huffman only); the getters receive the current source address in `r0` and
  return the data in `r0`. These functions return in `r0` the decompressed
  length, or the negative error code from Open or Close (GBATEK). The NitroSDK
  names the table `MIReadStreamCallbacks` (init, terminate, read byte, read
  short, read word).

## System and timing

### `SoftReset`

- **Interface:** `void SoftReset(void)`, 4 bytes at 0x0200015a: `swi #0x00`,
  `bx lr`. No arguments; never returns, so the `bx lr` is never reached.
- **Behavior:** BIOS function 00h. Clears the 0x200 bytes holding the stacks
  and the BIOS IRQ vector and check flags, reinitializes the stack pointers and
  jumps to the ARM9 entry address stored at 0x027FFE24, the cartridge-header
  copy's ARM9 entry point (header offset 0x24) (GBATEK). A port restarts the
  program at its entry point.
- **Hardware:** relies on the header copy at 0x027FFE00 that the boot process
  leaves in main RAM (GBATEK); other hardware state is whatever the program
  left.

### `WaitByLoop`

- **Interface:** `void WaitByLoop(s32 count)`, 4 bytes at 0x02000232:
  `swi #0x03`, `bx lr`. `r0` = loop count; no result.
- **Behavior:** BIOS function 03h: a `subs r0, r0, #1` / `bgt` countdown loop
  run inside the BIOS, so its duration does not depend on the caller's cache or
  memory wait states (GBATEK). Because the test is a signed `bgt`, a count of 0
  or less runs the loop once. In this game it is a spin back-off: `OS_InitLock`
  and `OSi_DoLockByWord` call `WaitByLoop(0x400)` between lock attempts, so a
  port can use a short pause or a CPU yield.
- **Hardware:** the time per iteration is set by the ARM9 clock and BIOS ROM
  fetch timing (GBATEK); this document does not fix a cycle count.

### `IntrWait`

- **Interface:** `void IntrWait(BOOL discard, u32 mask)`, 4 bytes at
  0x0200035e: `swi #0x04`, `bx lr`. `r0` = discard flag, `r1` = interrupts to
  wait for, in IE/IF bit format. No result.
- **Behavior:** BIOS function 04h. Sets IME = 1, then halts until one of the
  `mask` interrupts has been recorded in the check-flags word at DTCM+0x3FF8,
  clears those bits there and returns (GBATEK). With `r0` = 1 it first discards
  the `mask` bits already set, so only a new interrupt ends the wait. With
  `r0` = 0 it is meant to return at once if one is already flagged, but on the
  ARM9 that mode is broken and always waits for at least one interrupt
  (GBATEK). A port blocks until its IRQ dispatch has flagged one of `mask`,
  then clears those flags.
- **Hardware:** never returns unless IE enables one of `mask` and the IRQ
  handler ORs each interrupt it acknowledges into DTCM+0x3FF8 besides clearing
  IF (GBATEK). Waits with the ARM9 halt described under `Halt`; leaves IME = 1.

### `VBlankIntrWait`

- **Interface:** `void VBlankIntrWait(void)`, 6 bytes at 0x020002fa:
  `movs r2, #0`, `swi #0x05`, `bx lr`. No arguments or result; `r2` is 0 on
  entry to the BIOS.
- **Behavior:** BIOS function 05h: `IntrWait(1, 1)`, i.e. discards an old
  V-blank flag and waits for the next V-blank interrupt (IE/IF bit 0) (GBATEK).
  The veneer always clears `r2` first; why the ARM9 BIOS wants that is not
  established here, and a port need not model it. A port waits for the next
  vertical blank.
- **Hardware:** needs the V-blank IRQ enabled in DISPSTAT (bit 3) and IE, and
  an IRQ handler that sets bit 0 of the check flags at DTCM+0x3FF8 (GBATEK).
  Leaves IME = 1, as `IntrWait`.

### `Halt`

- **Interface:** `void Halt(void)`, 4 bytes at 0x020005fc: `swi #0x06`,
  `bx lr`. No arguments or result.
- **Behavior:** BIOS function 06h: stops the ARM9 in a low-power state until an
  enabled interrupt is requested, i.e. until (IE AND IF) != 0; it does not use
  the check flags (GBATEK). A port waits for the next interrupt or event.
- **Hardware:** on the ARM9 the BIOS halts with the CP15 wait-for-interrupt
  operation (`mcr p15, 0, r0, c7, c0, 4`), which hangs if IME = 0 (GBATEK);
  IE must enable an interrupt that will occur.

### `IsDebugger`

- **Interface:** `BOOL IsDebugger(void)`, 4 bytes at 0x020002a0: `swi #0x0f`,
  `bx lr`. Returns `r0`.
- **Behavior:** BIOS function 0Fh: returns 0 on a retail console and non-zero
  on a debugger unit, which it tells apart by whether main RAM is 4 MB or 8 MB
  (GBATEK). A port returns 0.
- **Hardware:** probes main RAM to measure its size, so it is not a pure
  function (GBATEK).

## Arithmetic

### `Div`

- **Interface:** `s32 Div(s32 numerator, s32 denominator)`, 4 bytes at
  0x02000656: `swi #0x09`, `bx lr`. `r0` = numerator, `r1` = denominator.
  Returns the quotient in `r0`; the BIOS also leaves the remainder in `r1` and
  |quotient| in `r3` (GBATEK).
- **Behavior:** BIOS function 09h: signed division truncating toward zero, as
  C99 `/` and `%`: the remainder has the numerator's sign, e.g. -1234 / 10
  gives -123, remainder -4, |quotient| 123 (GBATEK). A zero denominator usually
  hangs in an endless loop (GBATEK); the result of 0x80000000 / -1 is not
  documented, and the model refuses both.
- **Hardware:** a software loop in the BIOS, not the divider at 0x04000280
  (GBATEK), so it does not disturb that unit's state; no memory access.

### `Mod`

- **Interface:** `s32 Mod(s32 numerator, s32 denominator)`, 6 bytes at
  0x020006b0: `swi #0x09`, `adds r0, r1, #0`, `bx lr`. Same arguments as
  `Div`; returns the remainder in `r0` (and in `r1`), with |quotient| left in
  `r3`. The `adds` sets N and Z from the remainder and clears C and V.
- **Behavior:** C99 `%` on signed 32-bit values: numerator - quotient *
  denominator with the quotient truncated toward zero, so the result has the
  numerator's sign (GBATEK). Zero and 0x80000000 / -1 as for `Div`.
- **Hardware:** as `Div`: BIOS software division, no memory access.

### `Sqrt`

- **Interface:** `u16 Sqrt(u32 value)`, 4 bytes at 0x0200071a: `swi #0x0d`,
  `bx lr`. `r0` = value; returns the root in `r0`. (The stub's `void(void)`
  prototype is a placeholder.)
- **Behavior:** BIOS function 0Dh: the integer square root, floor(sqrt(r0)),
  0-0xFFFF (GBATEK). For more precision a caller shifts the argument left by 2N
  and gets the root shifted left by N (GBATEK).
- **Hardware:** BIOS software, not the square-root unit at 0x040002B0; no
  memory access.

### `GetCRC16`

- **Interface:** `u16 GetCRC16(u16 initial, const void *data, u32 size)`, 4
  bytes at 0x020001c0: `swi #0x0e`, `bx lr`. `r0` = initial CRC, `r1` = data,
  `r2` = length in bytes. Returns the CRC in `r0`.
- **Behavior:** BIOS function 0Eh: the reflected CRC-16 with polynomial 0xA001
  (0x8005 bit-reversed), starting from `r0`, over the bytes in address order,
  no final XOR; GBATEK gives it as a byte loop with an eight-entry table
  (C0C1h ... A001h), which the model reproduces bit for bit (GBATEK). With
  initial 0xFFFF it is CRC-16/MODBUS, the cartridge-header checksum: over the
  header copy's bytes 0x000-0x15D the model gives this ROM's stored 0x7326, and
  over the logo 0x0C0-0x15B the stored 0xCF56.
- **Hardware:** `r1` and `r2` must be 2-byte aligned (GBATEK); reads the data
  with ordinary CPU loads.

## Memory copy and fill

### `CpuSet`

- **Interface:** `void CpuSet(const void *src, void *dst, u32 control)`, 4
  bytes at 0x02000788: `swi #0x0b`, `bx lr`. `r0` = source, `r1` =
  destination, `r2` = control word. No result.
- **Behavior:** BIOS function 0Bh. Control bits 0-20 are the number of units,
  bit 24 selects fill (1: every unit is the one at `src`) over copy (0), bit 26
  the unit size (0: 16-bit, 1: 32-bit); other bits should be 0 (GBATEK). The
  model copies in ascending order; behavior for overlapping buffers and for a
  zero count is not established here, so a port should treat it as `memcpy` /
  a fill of 2- or 4-byte units.
- **Hardware:** `src` and `dst` aligned to the unit size (GBATEK). CPU loads and
  stores, not DMA, so no cache maintenance is needed around it; 16-bit units
  make it usable on VRAM and palette RAM.

### `CpuFastSet`

- **Interface:** `void CpuFastSet(const void *src, void *dst, u32 control)`, 4
  bytes at 0x0200052e: `swi #0x0c`, `bx lr`. `r0` = source, `r1` =
  destination, `r2` = control word. No result.
- **Behavior:** BIOS function 0Ch: like `CpuSet` with 32-bit units only,
  moving eight words at a time; bits 0-20 are the word count, bit 24 selects
  fill (GBATEK). The count should be a multiple of 8; GBATEK documents rounding
  other counts up to a multiple of 8 on the GBA BIOS, which the model follows,
  but a port should accept multiples of 8 only.
- **Hardware:** word-aligned `src` and `dst` (GBATEK); CPU block transfers, no
  DMA or cache maintenance, safe for VRAM.

### `BitUnPack`

- **Interface:** `void BitUnPack(const void *src, void *dst, const
  SVCUnpackBitsParam *param)`, 4 bytes at 0x02000432: `swi #0x10`, `bx lr`.
  `r0` = source, `r1` = destination, `r2` = parameters: `+0 u16` source length
  in bytes, `+2 u8` source unit width (1, 2, 4 or 8 bits), `+3 u8` destination
  unit width (1, 2, 4, 8, 16 or 32 bits), `+4 u32` offset in bits 0-30 and in
  bit 31 the zero-data flag (GBATEK). No result.
- **Behavior:** BIOS function 10h: reads each source byte as units of the
  source width, least significant first, adds the offset to every non-zero unit
  (to every unit if bit 31 is set) and packs the results, least significant
  first, into 32-bit words at `dst` (GBATEK). The model produces whole words
  only and requires each result to fit the destination width; what the BIOS does
  with a trailing partial word or an overflowing unit is not established here.
- **Hardware:** `dst` word-aligned and written in 32-bit units (GBATEK), so it
  can target VRAM (font and tile expansion).

## Decompression

### `LZ77UnCompReadNormalWrite8bit`

- **Interface:** `void LZ77UnCompReadNormalWrite8bit(const void *src, void
  *dst)`, 4 bytes at 0x020000ea: `swi #0x11`, `bx lr`. `r0` = stream (header
  first), `r1` = destination. No result.
- **Behavior:** BIOS function 11h: decodes a type-1 LZ77 stream (format above)
  until the header's size has been written (GBATEK). Model: `bios_lz77`.
- **Hardware:** stores bytes, so `dst` must accept 8-bit writes (main RAM or
  WRAM, not VRAM); reads the stream directly (GBATEK).

### `LZ77UnCompReadByCallbackWrite16bit`

- **Interface:** `s32 LZ77UnCompReadByCallbackWrite16bit(const void *src, void
  *dst, const void *param, const MIReadStreamCallbacks *callbacks)`, 4 bytes at
  0x020003be: `swi #0x12`, `bx lr`. `r0` = source handle passed to the
  callbacks, `r1` = destination, `r2` = user parameter, `r3` = callback table
  (format above). Returns the decompressed length or a negative error in `r0`
  (GBATEK). (The stub's two-argument prototype is a placeholder.)
- **Behavior:** BIOS function 12h: the same LZ77 decoding, reading through the
  callbacks and storing 16-bit units. Because a byte is only stored with its
  pair, a reference with distance 1 (distance field 0) does not work here
  (GBATEK). Model: `bios_lz77(stream, halfword_writes=True)`.
- **Hardware:** `dst` 2-byte aligned and written in 16-bit units, so it can be
  VRAM (GBATEK); the callbacks run from the BIOS's call, may be ARM or THUMB and
  can read from any device (e.g. the cartridge).

### `HuffUnCompReadByCallback`

- **Interface:** `s32 HuffUnCompReadByCallback(const void *src, void *dst,
  const void *param, const MIReadStreamCallbacks *callbacks)`, 4 bytes at
  0x02000598: `swi #0x13`, `bx lr`. Registers as
  `LZ77UnCompReadByCallbackWrite16bit`. (The stub's `void(void)` prototype is a
  placeholder.)
- **Behavior:** BIOS function 13h: decodes a type-2 Huffman stream (format
  above) with 4- or 8-bit symbols, reading through the callbacks; it is the
  only function that uses `Get32bit` (GBATEK). Model: `bios_huffman`.
- **Hardware:** `dst` word-aligned, written in 32-bit units, VRAM-safe
  (GBATEK).

### `RLUnCompReadNormalWrite8bit`

- **Interface:** `void RLUnCompReadNormalWrite8bit(const void *src, void
  *dst)`, 4 bytes at 0x0200049a: `swi #0x14`, `bx lr`. `r0` = stream, `r1` =
  destination. No result.
- **Behavior:** BIOS function 14h: decodes a type-3 run-length stream (format
  above) until the header's size has been written (GBATEK). Model: `bios_rl`.
- **Hardware:** byte stores, so `dst` must not be VRAM; reads the stream
  directly (GBATEK).

### `RLUnCompReadByCallbackWrite16bit`

- **Interface:** `s32 RLUnCompReadByCallbackWrite16bit(const void *src, void
  *dst, const void *param, const MIReadStreamCallbacks *callbacks)`, 4 bytes at
  0x02000090: `swi #0x15`, `bx lr`. Registers as
  `LZ77UnCompReadByCallbackWrite16bit`. (The stub's two-argument prototype is
  a placeholder.)
- **Behavior:** BIOS function 15h: the same run-length decoding, reading
  through the callbacks and storing 16-bit units (GBATEK). Model: `bios_rl`.
- **Hardware:** `dst` 2-byte aligned and written in 16-bit units, VRAM-safe
  (GBATEK).
