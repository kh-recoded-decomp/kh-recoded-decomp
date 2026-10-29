# SDK and runtime routines rebuilt as C

These routines were written in assembly by their authors and are now
readable C that GCC 12.2.1 compiles to the original bytes (see the profiles
in [CONTRIBUTING.md](../../CONTRIBUTING.md)). They count as C. The register
bindings, fences and optimization profiles in their sources exist only to
reproduce the original instruction selection; a port can drop all of them and
keep the plain C, or call its own library equivalent where one is noted.

## Memory

### `MI_CpuFill8`

- **Interface:** `MI_CpuFill8(void *dst, u8 value, u32 size)`; `r0` = dst,
  `r1` = fill byte (only bits 0-7 are used), `r2` = byte count. Returns
  nothing. Clobbers `r0`-`r3`, `r12` and the flags; uses no stack.
- **Behavior:** `memset(dst, value, size)`. It never issues a byte store: an
  odd leading or trailing byte is written by reading the containing halfword,
  replacing one byte and writing the halfword back; the middle is filled with
  halfword and word stores. `size == 0` writes nothing.
- **Hardware:** safe on VRAM, palette and OAM, which ignore 8-bit CPU writes;
  that is why it avoids byte stores. The read-modify-write of edge halfwords is
  not atomic, so a concurrent writer to the neighbouring byte (an interrupt
  handler, DMA) can lose its update. Lives in ITCM.

### `MI_CpuCopy8`

- **Interface:** `MI_CpuCopy8(const void *src, void *dst, u32 size)`; `r0` =
  src, `r1` = dst, `r2` = byte count. Returns nothing. Clobbers `r0`-`r3`,
  `r12` and the flags; uses no stack.
- **Behavior:** `memcpy(dst, src, size)` for non-overlapping buffers, copying
  forward. Like `MI_CpuFill8` it never stores a single byte: odd destination
  edges use halfword read-modify-write, and when source and destination differ
  in alignment parity it reads aligned halfwords and shifts bytes across them.
  Otherwise the middle moves as halfwords and words. `size == 0` copies nothing.
- **Hardware:** safe on VRAM, palette and OAM destinations (no 8-bit writes);
  edge halfword updates are not atomic. Lives in ITCM.

### `MIi_CpuCopy16Backward`

- **Interface:** `MIi_CpuCopy16Backward(const void *src, void *dst, u32 size)`;
  `r0` = src, `r1` = dst, `r2` = byte count (a multiple of 2). Clobbers
  `r0`-`r2`, `r12` and the flags.
- **Behavior:** copies `size` bytes as halfwords from the highest address
  down, so it is correct when `dst` overlaps `src` from above
  (`memmove` with `dst > src`). Both pointers must be halfword aligned; an odd
  `size` leaves the last byte uncopied.
- **Hardware:** halfword accesses only, so it works on VRAM. Lives in ITCM.

## Geometry engine

### `GXi_NopClearFifo128_`

- **Interface:** `GXi_NopClearFifo128_(void *fifo)`; `r0` = address of the
  geometry command FIFO port (`REG_GXFIFO`, 0x04000400). Clobbers `r0`-`r3`,
  `r12`.
- **Behavior:** writes 128 zero words to the port as 32 four-word stores. A
  zero word is the geometry NOP command, so this pushes any half-written packed
  command through and leaves the FIFO with no pending parameters. Its caller,
  `G3X_ClearFifo`, passes `0x04000400` and then polls `REG_GXSTAT` bit 27 until
  the geometry engine is idle.
- **Hardware:** direct writes to the 3D geometry FIFO; the CPU stalls while the
  FIFO is full. A port with no command FIFO replaces it with nothing.

## Threads and startup

### `OS_InitContext`

- **Interface:** `OS_InitContext(OSContext *context, u32 entry, u32 stackTop)`;
  `r0` = context, `r1` = thread entry address (bit 0 set for a Thumb entry),
  `r2` = top of the thread's stack. Clobbers `r1`, `r2` and the flags.
- **Behavior:** prepares a context that `OS_LoadContext` will resume as a new
  thread. It stores `entry + 4` as the resume address (the loader returns with
  `subs pc, lr, #4`), `stackTop` as the SVC stack pointer, and
  `stackTop - 0x40` (the SVC stack area), rounded down to 8 bytes, as the
  thread stack pointer. CPSR becomes System mode, with the Thumb bit when bit 0
  of `entry` is set. `r0`-`r12` and `lr` are zeroed.
- **Hardware:** writes only memory. The context layout (CPSR, r0-r12, sp, lr,
  pc+4, SVC sp) is the one `OS_SaveContext`/`OS_LoadContext` and the IRQ
  thread switch use, and the mode and Thumb bits are ARM CPSR values.

### `INITi_InitCp15`

- **Interface:** `INITi_InitCp15(void)` (symbol `func_02000a78`), called once
  from the crt0 entry before the autoload copy. No arguments or result;
  clobbers `r0` and `r1`.
- **Behavior:** configures the ARM946E-S system control coprocessor:
  1. clears control-register bits `0xF9005` (protection unit, caches and both
     TCMs off);
  2. invalidates the instruction and data caches and drains the write buffer;
  3. programs the eight protection regions (base | size | enable):

     | Region | Value | Base | Size | Contents |
     |---|---|---|---|---|
     | 0 | `0x04000033` | `0x04000000` | 64 MB | I/O, palette, VRAM, OAM |
     | 1 | `0x02000031` | `0x02000000` | 32 MB | main memory |
     | 2 | `0x027FF017` | `0x027FF000` | 4 KB | main-memory work area |
     | 3 | `0x08000035` | `0x08000000` | 128 MB | GBA slot |
     | 4 | DTCM base \| `0x1B` | `SDK_AUTOLOAD_DTCM_START` | 16 KB | DTCM |
     | 5 | `0x0100002F` | `0x01000000` | 16 MB | ITCM |
     | 6 | `0xFFFF001D` | `0xFFFF0000` | 32 KB | BIOS |
     | 7 | `0x02FFF017` | `0x02FFF000` | 4 KB | shared ARM7/ARM9 work area |

  4. places ITCM at 0 with a 32 MB virtual size and DTCM at
     `SDK_AUTOLOAD_DTCM_START` with 16 KB;
  5. makes regions 1, 3 and 6 instruction- and data-cacheable and regions 1
     and 3 write-buffered, and sets the access permissions
     (instruction `0x05101011`, data `0x15111111`: privileged read/write
     everywhere except BIOS, which is read-only);
  6. sets control-register bits `0x5707D`: protection unit, data and
     instruction caches, write buffer, high exception vectors at `0xFFFF0000`,
     round-robin replacement, DTCM and ITCM on.
- **Hardware:** CP15 only (`mcr`/`mrc` through GCC's ARM builtins); must run
  in a privileged mode with caches off, before anything is copied into the
  TCMs. A port drops it, keeping only the memory map in the table for
  reference.

## Runtime

### `_ll_mul`

- **Interface:** CodeWarrior runtime helper for 64-bit `*`; `r0:r1` = left
  (low:high), `r2:r3` = right. Returns the product in `r0:r1`. Saves `r4`,
  `r5` and `lr` on the stack.
- **Behavior:** the low 64 bits of the product, so the same helper serves
  signed and unsigned operands: `lo(a)*lo(b) + ((lo(a)*hi(b) + hi(a)*lo(b)) << 32)`.
- **Hardware:** none; `umull`/`mla` integer arithmetic.
