# NitroSDK memory copy and fill kernels

Hand-written ARM routines from the NitroSDK MI and OS libraries that copy,
move and fill memory. Each section below is checked by
`tools/sdklib/verify_sdklib.py`, which runs the ROM's own instructions against
the Python model in `tools/sdklib/families/sdk_memory.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md). The tests cover lengths 0..256
and random larger ones, every source/destination alignment the routine
accepts, overlapping buffers in the direction each routine supports, and a
4 KB window of random guard bytes around the buffers that must come back
unchanged.

All of them are ARM code, return with `bx lr`, and keep `r4`-`r11` and `sp`
intact. Apart from `func_0200093c` they are linked into the ITCM block
(0x01FF8000), which crt0 copies into place before `main`. ITCM is the
ARM946E-S's zero-wait instruction memory: code there never misses the
instruction cache and never fetches over the main bus, so the bus carries only
the data being moved, and the code keeps running while main RAM itself is
being cleared or reloaded (the reset path). None of these routines do any
cache maintenance. Main RAM is write-back cached under the SDK's protection
unit setup, so a caller that hands the destination to DMA, the 3D engine or
the ARM7 must flush it (`DC_FlushRange`) first; conversely the CPU kernels are
the way to reach ITCM and DTCM, which DMA cannot access. Every routine runs
with interrupts enabled and is interruptible; it is not atomic.

A port can replace them with `memcpy`, `memmove`, `memset` and plain word
loops; the differences from C are listed under Behavior.

## Byte move (ITCM, 0x01FF8AD8-0x01FF90DC)

`func_01ff8ad8` (forward copy) and `func_01ff8dc8` (move) are the public
entries; the other ten symbols are pieces they branch to. Their argument order
is `(src, dst, size)`, source first, matching NitroSDK's `MI_CpuCopy8`
convention and the `MI_CpuCopy` / `MI_CpuMove` entries of later SDKs; the EU
symbol map does not name them. No SDK code in this ROM calls them: the only
internal caller is `func_01ff8dc8`, which branches to `func_01ff8ad8` for
downward moves. Game code calls them directly from Thumb (for example
`PollSaveSlotReads`, `LoadSlotIntoGame`, the `CopyWideString*` helpers and the
item-list panels call `func_01ff8ad8`; `MoveEquipmentSlot` and
`MoveSummarySlot` call `func_01ff8dc8`).

The pieces share one register interface:

- `r0` = source pointer, word-aligned (a start pointer for the forward
  pieces, an end pointer, one past the last byte, for the backward ones).
- `r1` = destination pointer rounded down to a word (`dst & ~3`); the real
  destination is `r1 + k`, where `k` is the piece's misalignment (0-3).
- `r2` = byte count. The misaligned pieces (`k` = 1-3) need `r2` >= 4; with
  fewer bytes they store bytes from before the source. The entries always
  pass at least 6.
- Each piece moves 32-byte blocks with `ldm`/`stm` of eight registers
  (saving `r4`-`r10` and `lr` on the stack for the loop, 32 bytes), then
  single words, then branches to the 0-7 byte tail (`func_01ff8d80` forward,
  `func_01ff9094` backward) with `r0`/`r1` at the remaining bytes and `r2`'s
  low three bits giving their count. The tail returns to the entry's caller.
- The misaligned pieces build each output word from two source words with
  shifts (`k` bytes of carry in `ip`). Their first store rewrites the whole
  aligned word at `r1`: they read it first and store its `k` bytes before the
  destination (forward) or `4 - k` bytes after the destination's end
  (backward) back unchanged. That read-modify-write is invisible in plain RAM.

Bus rules for every routine in this family: they use `ldrb`/`strb` for the
head and tail bytes and the misaligned pieces read and rewrite bytes next to
the destination, so they must not be used on VRAM, palette RAM or OAM (the
ARM9 drops 8-bit writes there) or on I/O registers, and not on memory another
bus master (DMA, ARM7) writes during the copy.

### `func_01ff8ad8`

- **Interface:** `r0` = source, `r1` = destination, `r2` = size in bytes
  (treated as signed; must be below 2^31). Returns `r0` = source + size and
  `r1` = destination + size (both unchanged for size 0). Clobbers `r2`, `r3`,
  `ip` and the flags; uses 32 bytes of stack when size > 8. Sizes 0-8 copy
  bytewise through a computed jump (`add pc, pc, r3, lsl #3` into eight
  `ldrb`/`strb` pairs). Larger sizes copy one byte, then a byte pair, to
  word-align the source, set `r1 = dst & ~3`, and branch to
  `func_01ff8b7c`/`func_01ff8bb8`/`func_01ff8c50`/`func_01ff8ce8` for
  destination misalignment 0/1/2/3, which return to the caller.
- **Behavior:** `memcpy(dst, src, size)` on bytes, with no alignment
  requirement on either pointer. It copies in ascending order, so overlapping
  buffers give `memmove` results when the destination is below the source;
  a destination above an overlapping source is not supported (the result
  depends on the block structure). Bytes outside the destination are left
  unchanged.
- **Hardware:** runs from ITCM (0x01FF8AD8); the source and destination may be
  main RAM, TCM, WRAM or cartridge-mapped RAM, but not VRAM, palette RAM, OAM
  or I/O (8-bit accesses and read-modify-write, see above). No cache
  maintenance, IRQs stay enabled.

### `func_01ff8b7c`

- **Interface:** forward piece, misalignment 0: `r0` = word-aligned source,
  `r1` = word-aligned destination, `r2` = count (any value >= 0). Returns
  `r0` = source + count, `r1` = destination + count. Clobbers `r2`, `r3` and
  the flags; pushes and pops `r4`-`r10`, `lr` (32 bytes). Ends by branching to
  `func_01ff8d80`.
- **Behavior:** copies `count` bytes upward: 32-byte blocks with
  `ldmia`/`stmia`, then words, then the 0-3 byte remainder through the tail.
  Safe for overlap with the destination below the source.
- **Hardware:** runs from ITCM; word and block transfers need the word
  alignment stated above (the ARM946E-S ignores address bits 1:0 of
  `ldm`/`stm`, so a misaligned pointer would move the wrong bytes).

### `func_01ff8bb8`

- **Interface:** forward piece, misalignment 1: `r0` = word-aligned source,
  `r1` = destination rounded down to a word (real destination `r1 + 1`),
  `r2` = count >= 4. Returns `r0` = source + count, `r1` = real destination +
  count. Clobbers `r2`, `r3`, `ip` and the flags; 32 bytes of stack. Before
  the tail it steps `r0` back one byte and adds one to `r2` so the tail
  re-copies the source byte still held in the carry.
- **Behavior:** copies `count` bytes upward to a destination one byte past a
  word boundary. Output word = previous carry | source word << 8; the first
  word's low byte is the destination's own preceding byte, read before the
  loop and stored back unchanged. Safe for overlap with the destination below
  the source.
- **Hardware:** runs from ITCM; reads and rewrites the byte just before the
  destination, so not for I/O, VRAM or memory written by another master.

### `func_01ff8c50`

- **Interface:** forward piece, misalignment 2: as `func_01ff8bb8` with the
  real destination at `r1 + 2`; count >= 4; steps `r0` back two bytes and
  adds two to `r2` before the tail. Returns `r0` = source + count, `r1` = real
  destination + count. Clobbers `r2`, `r3`, `ip`, flags; 32 bytes of stack.
- **Behavior:** copies `count` bytes upward to a halfword-aligned,
  non-word-aligned destination; output word = carry | source word << 16, the
  first word keeping the destination's two preceding bytes. Safe for overlap
  with the destination below the source.
- **Hardware:** runs from ITCM; rewrites the two bytes before the
  destination with their own value.

### `func_01ff8ce8`

- **Interface:** forward piece, misalignment 3: as `func_01ff8bb8` with the
  real destination at `r1 + 3`; count >= 4; steps `r0` back three bytes and
  adds three to `r2` before the tail. Returns `r0` = source + count, `r1` =
  real destination + count. Clobbers `r2`, `r3`, `ip`, flags; 32 bytes of
  stack.
- **Behavior:** copies `count` bytes upward; output word = carry | source
  word << 24, the first word keeping the destination's three preceding
  bytes. Safe for overlap with the destination below the source.
- **Hardware:** runs from ITCM; rewrites the three bytes before the
  destination with their own value.

### `func_01ff8d80`

- **Interface:** forward tail: `r0` = source, `r1` = destination (any
  alignment), `r2` = count, of which only bits 0-2 are used. Returns `r0` and
  `r1` advanced by `r2 & 7`; `r2` is unchanged. Clobbers `r3` and the flags; no
  stack. Reached by branch from the forward pieces; it returns to their
  caller.
- **Behavior:** copies `r2 & 7` bytes upward (4, then 2, then 1, by testing
  each bit), with `ldrb`/`strb`.
- **Hardware:** runs from ITCM; byte accesses only, so not for VRAM, palette
  RAM, OAM or I/O.

### `func_01ff8dc8`

- **Interface:** `r0` = source, `r1` = destination, `r2` = size in bytes
  (signed, below 2^31). Size 0 or source == destination returns at once with
  everything unchanged. Source above destination (signed compare) branches to
  `func_01ff8ad8` and returns `r0` = source + size, `r1` = destination + size.
  Otherwise it copies downward and returns `r0` = source, `r1` = destination.
  Clobbers `r2`, `r3`, `ip` and the flags; up to 32 bytes of stack. The
  downward path moves both pointers to the buffer ends; sizes 0-8 copy
  bytewise through a computed jump, larger sizes copy a byte pair, then a
  byte, to word-align the source end, set `r1 = end & ~3` and branch to
  `func_01ff8e84`/`func_01ff8ec0`/`func_01ff8f5c`/`func_01ff8ff8` for an
  end misalignment of 0/1/2/3.
- **Behavior:** `memmove(dst, src, size)` on bytes: correct for every
  overlap and every alignment. Bytes outside the destination are left
  unchanged.
- **Hardware:** runs from ITCM; the same memory restrictions as
  `func_01ff8ad8` (no VRAM, palette RAM, OAM or I/O). No cache maintenance.

### `func_01ff8e84`

- **Interface:** backward piece, misalignment 0: `r0` = word-aligned source
  end, `r1` = word-aligned destination end, `r2` = count >= 0. Returns `r0` =
  source end - count, `r1` = destination end - count (the buffer starts).
  Clobbers `r2`, `r3` and the flags; 32 bytes of stack. Ends by branching to
  `func_01ff9094`.
- **Behavior:** copies the `count` bytes below the two end pointers in
  descending order: 32-byte blocks with `ldmdb`/`stmdb`, then words, then the
  remainder through the tail. Safe for overlap with the destination above the
  source.
- **Hardware:** runs from ITCM; word-aligned pointers required for the
  block and word transfers.

### `func_01ff8ec0`

- **Interface:** backward piece, misalignment 1: `r0` = word-aligned source
  end, `r1` = destination end rounded down to a word (real end `r1 + 1`),
  `r2` = count >= 4. Returns `r0` = source start, `r1` = destination start.
  Clobbers `r2`, `r3`, `ip`, flags; 32 bytes of stack. Before the tail it
  adds 4 to `r1` and 3 to `r0` and `r2`, so the tail re-copies the three
  source bytes held in the carry.
- **Behavior:** copies `count` bytes downward to a destination ending one
  byte past a word boundary; output word = carry | source word >> 24, stored
  with `stmda`; the first word keeps the three bytes after the destination's
  end. Safe for overlap with the destination above the source.
- **Hardware:** runs from ITCM; rewrites the three bytes after the
  destination with their own value.

### `func_01ff8f5c`

- **Interface:** backward piece, misalignment 2: as `func_01ff8ec0` with the
  real end at `r1 + 2`; count >= 4; adds 4 to `r1` and 2 to `r0` and `r2`
  before the tail. Returns the buffer starts in `r0`/`r1`. Clobbers `r2`,
  `r3`, `ip`, flags; 32 bytes of stack.
- **Behavior:** copies `count` bytes downward; output word = carry | source
  word >> 16, the first word keeping the two bytes after the destination's
  end. Safe for overlap with the destination above the source.
- **Hardware:** runs from ITCM; rewrites the two bytes after the destination
  with their own value.

### `func_01ff8ff8`

- **Interface:** backward piece, misalignment 3: as `func_01ff8ec0` with the
  real end at `r1 + 3`; count >= 4; adds 4 to `r1` and 1 to `r0` and `r2`
  before the tail. Returns the buffer starts in `r0`/`r1`. Clobbers `r2`,
  `r3`, `ip`, flags; 32 bytes of stack.
- **Behavior:** copies `count` bytes downward; output word = carry | source
  word >> 8, the first word keeping the byte after the destination's end.
  Safe for overlap with the destination above the source.
- **Hardware:** runs from ITCM; rewrites the byte after the destination with
  its own value.

### `func_01ff9094`

- **Interface:** backward tail: `r0` = source end, `r1` = destination end
  (any alignment), `r2` = count, of which only bits 0-2 are used. Returns `r0`
  and `r1` lowered by `r2 & 7`; `r2` unchanged. Clobbers `r3` and the flags; no
  stack. Reached by branch from the backward pieces.
- **Behavior:** copies the `r2 & 7` bytes below the end pointers in
  descending order (4, then 2, then 1) with pre-decrement `ldrb`/`strb`.
- **Hardware:** runs from ITCM; byte accesses only, so not for VRAM, palette
  RAM, OAM or I/O.

## Byte fill (ITCM)

### `func_01ff88c4`

- **Interface:** `r0` = destination, `r1` = fill byte, `r2` = size in bytes
  (signed, below 2^31). Returns `r0` = destination + size. Clobbers `r1`,
  `r2`, `r3` and the flags; pushes `r4`-`r10` (28 bytes) only when at least 32
  bytes remain after alignment. Called from game code (for example
  `UpdateStageManager`, `ScriptCmd_SetProperty`, `Camera_InitManager`), always
  with value 0 in this ROM; the order `(dst, value, size)` matches
  NitroSDK's `MI_CpuFill8` and the later `MI_CpuFill`.
- **Behavior:** `memset(dst, value, size)`, no alignment requirement. Size 0
  returns at once; sizes 1-8 store bytes through a computed jump. Larger
  sizes widen the byte to a word, align the destination to 8 with a byte, a
  halfword and a word store, fill 32-byte blocks with `stmia` of eight
  registers, then words, then up to 3 bytes. Unlike `memset` the value is not
  truncated: `r1` must already be 0-255, because bits above 7 are mixed into
  the widened word and give a wrong pattern for sizes above 8. Nothing
  outside the destination is read or written.
- **Hardware:** runs from ITCM; uses 8- and 16-bit stores, so not for VRAM,
  palette RAM or OAM (8-bit writes are dropped there) or I/O. No cache
  maintenance.

## Word kernels (ITCM, and one crt0 copy)

These are the NitroSDK `MIi_` workers behind the public inline wrappers in
`nitro/mi/memory.h`: `MI_CpuFill32`/`MI_CpuClear32` call `MIi_CpuClear32`,
`MI_CpuCopy32` calls `MIi_CpuCopy32`, `MI_CpuSend32` calls `MIi_CpuSend32`,
`MI_CpuFillFast`/`MI_CpuClearFast` call `MIi_CpuClearFast` and
`MI_CpuCopyFast` calls `MIi_CpuCopyFast`. Their callers include `GX_Init`,
the `GX_Load*` VRAM loaders, `GXi_FlushCommandList`, the NNS G3D billboard
SBC commands and the card and save code. The wrappers' alignment assertions
exist only in debug builds; this ROM has none.

Shared rules: pointers must be word-aligned (the ARM946E-S ignores address
bits 1:0 for `ldm`/`stm`/`str`, so a misaligned pointer silently moves the
aligned-down word); the size is in bytes and should be a multiple of 4. The
loops run while the moving pointer is below start + size (signed compare),
so a size that is not a multiple of 4 is rounded up to whole words. The
"Fast" kernels move 32-byte blocks (eight registers, one ARM946E-S cache line)
and then single words; they need only word alignment, not 32-byte alignment,
though 32-byte-aligned buffers keep each block within one cache line. Because
they only use 32-bit accesses these are the kernels that are safe for VRAM,
palette RAM, OAM and I/O.

### `MIi_CpuClear32`

- **Interface:** `r0` = 32-bit fill value, `r1` = destination (word-aligned),
  `r2` = size in bytes. Returns `r0` unchanged and `r1` = destination +
  4 * ceil(size / 4). Clobbers `r1`, `ip` and the flags; no stack.
- **Behavior:** stores the value to ceil(size / 4) consecutive words; size 0
  stores nothing. Equivalent to a `u32` fill loop.
- **Hardware:** runs from ITCM; word stores only, so safe for VRAM, palette
  RAM, OAM and 32-bit I/O. No cache maintenance.

### `MIi_CpuCopy32`

- **Interface:** `r0` = source, `r1` = destination (both word-aligned),
  `r2` = size in bytes. Returns `r0` = source + 4n, `r1` = destination + 4n,
  where n = ceil(size / 4). Clobbers `r2` (last word copied), `ip` and the
  flags; no stack.
- **Behavior:** copies n words upward one at a time (`ldmia`/`stmia` of one
  register). Correct for overlap only when the destination is below the
  source.
- **Hardware:** runs from ITCM; word accesses only, so safe for VRAM,
  palette RAM and OAM as either side.

### `MIi_CpuSend32`

- **Interface:** `r0` = source (word-aligned), `r1` = fixed destination
  address, `r2` = size in bytes. Returns `r0` = source + 4n (n = ceil(size /
  4)) and `r1` unchanged. Clobbers `r2`, `ip` and the flags; no stack. The
  loop is controlled by the source pointer.
- **Behavior:** writes the n source words, in order, all to the same
  address: a port write, not a copy. Size 0 writes nothing. The tests log
  every store and require exactly the n source words at the port and no
  other memory change.
- **Hardware:** meant for write-only FIFO registers such as the geometry
  command FIFO (`GXFIFO`, 0x04000400), which `GXi_FlushCommandList` and the
  G3D command buffer feed through it. The destination must be a 32-bit
  port; I/O is uncached, so no flush is needed for the port, but a source in
  main RAM written by DMA must be invalidated first. Runs from ITCM.

### `MIi_CpuClearFast`

- **Interface:** `r0` = 32-bit fill value, `r1` = destination (word-aligned),
  `r2` = size in bytes. Returns `r0` unchanged, `r1` = destination +
  4 * ceil(size / 4). Clobbers `r1`, `r2`, `r3`, `ip` (`r2`/`r3` hold the
  value) and the flags; pushes and pops `r4`-`r9` (24 bytes).
- **Behavior:** fills floor(size / 32) blocks of 32 bytes with `stmia` of
  eight registers, then single words up to start + size; total
  ceil(size / 4) words, the same result as `MIi_CpuClear32`.
- **Hardware:** runs from ITCM; word-aligned destination, 32-bit stores only
  (safe for VRAM and OAM). No cache maintenance.

### `MIi_CpuCopyFast`

- **Interface:** `r0` = source, `r1` = destination (both word-aligned),
  `r2` = size in bytes. Returns `r0` = source + 4n, `r1` = destination + 4n
  (n = ceil(size / 4)). Clobbers `r2`, `r3`, `ip` and the flags; pushes and
  pops `r4`-`r10` (28 bytes).
- **Behavior:** copies 32-byte blocks with eight-register `ldmia`/`stmia`,
  then single words; total n words upward. Each block is fully loaded before
  it is stored, so overlap is correct when the destination is below the
  source; not when it is above.
- **Hardware:** runs from ITCM; word-aligned pointers, 32-bit accesses only.
  No cache maintenance.

### `func_0200093c`

- **Interface:** identical to `MIi_CpuClear32`: `r0` = value, `r1` =
  word-aligned destination, `r2` = size in bytes; returns `r1` = destination
  + 4 * ceil(size / 4); clobbers `r1`, `ip`, flags; no stack.
- **Behavior:** the same word fill as `MIi_CpuClear32`. It is crt0's private
  clear routine; `Entry` calls it three times while it sets up memory.
- **Hardware:** lives in main RAM (0x0200093C) inside crt0 because `Entry`
  runs it before the autoload has copied the ITCM block, when
  `MIi_CpuClear32` does not exist yet. Word stores only; runs with the cache
  and protection unit in whatever state crt0 has set up.

### `func_01ff840c`

- **Interface:** identical to `MIi_CpuClear32`: `r0` = value, `r1` =
  word-aligned destination, `r2` = size in bytes; returns `r1` = destination
  + 4 * ceil(size / 4); clobbers `r1`, `ip`, flags; no stack.
- **Behavior:** the same word fill as `MIi_CpuClear32`; a private copy linked
  with the reset code. Its only caller, `OSi_DoBoot`, uses it with value 0 to
  clear the shared system area at 0x02FFFD80, 0x02FFFF80 and 0x02FFFF9C
  before jumping to the new program.
- **Hardware:** lives in ITCM next to `OSi_DoBoot`, which runs during a
  software reset with IME off, handshaking with the ARM7 over IPC sync while
  the program in main RAM is being replaced, so neither may execute from main
  RAM. Word stores only.
