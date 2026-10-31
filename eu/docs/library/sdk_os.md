# NitroSDK start-up and OS assembly

Hand-written ARM routines from the NitroSDK `init` (crt0) and `os` libraries
that run during start-up and around interrupts. Unless a section says
otherwise they are ARM code, return with `bx lr` and follow the ARM procedure
call standard. Each section below is checked by
`tools/sdklib/verify_sdklib.py`, which runs the ROM's own instructions against
the Python model in `tools/sdklib/families/sdk_os.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

The tests map the I/O and system areas these routines touch as plain memory,
so they check what each routine reads and writes, not what the hardware does
in response; the Hardware bullets say what that is. Routines that end by
jumping to another routine are tested with that target replaced by a stub.

## crt0

### `INITi_DoAutoload`

- **Interface:** `void INITi_DoAutoload(void)`, ARM, called once by `Entry`
  before `main`. It takes no arguments and does not return through `lr`: it
  ends with a branch to `AutoloadCallback` (0x02000A74), which returns to
  `INITi_DoAutoload`'s caller. Clobbers `r0`-`r7` and the flags.
- **Behavior:** reads the three-word descriptor at 0x02000B88 (`BuildInfo`):
  the start and end of the autoload list and the address of the packed block
  images. Each list entry is three words, destination, size and .bss size.
  For each entry it copies words from the image cursor to the destination
  while `destination - end` is negative, so a size that is not a multiple of
  four copies the last partial word whole; the cursor advances by the words
  copied. It then stores zero words from where the copy stopped while the
  address is below `copy end + .bss size` (unsigned). Last it walks the
  32-byte cache lines from `destination & ~0x1F` while the line address is
  below the clear end as a signed compare, at least once, and for each line
  drains the write buffer, invalidates the instruction-cache line and cleans
  and invalidates the data-cache line. An empty list does nothing but the
  final branch.
- **Hardware:** CP15 c7 operations per cache line: drain write buffer
  (c7,c10,4), invalidate I-cache line by address (c7,c5,1) and clean and
  invalidate D-cache line by address (c7,c14,1). The flush makes the copied
  code visible to instruction fetch, so a port that copies the same blocks
  needs no equivalent beyond an ordinary copy.

## Interrupts

### `OS_IrqHandler`

- **Interface:** `void OS_IrqHandler(void)`, ARM in ITCM (0x01FF8158), entered
  in IRQ mode from the IRQ vector stub with the interrupted code's state saved
  by the BIOS. It pushes `lr`, then either returns at once or jumps to the
  handler with `lr` set to `OS_IrqHandler_ThreadSwitch`, which pops the saved
  `lr` and returns when the handler is done. Clobbers `r0`-`r3`, `ip` and the
  flags.
- **Behavior:** returns without touching anything when `REG_IME` is zero or
  no source is both enabled in `REG_IE` and pending in `REG_IF`. Otherwise it
  picks the lowest-numbered source that is both (the `clz` loop clears the
  highest remaining bit until none is left; the last one cleared is the
  lowest), acknowledges only that source by
  writing its bit to `REG_IF`, and jumps to entry `n` of the 32-word handler
  table `OS_IRQTable` at the start of DTCM (0x027E0000). One interrupt is
  serviced per entry; others stay pending and raise the IRQ again.
- **Hardware:** reads `REG_IME` (0x04000208), `REG_IE` (0x04000210) and
  `REG_IF` (0x04000214) and writes `REG_IF`; writing a 1 bit to `REG_IF`
  clears that pending flag on the hardware. A port dispatches its own
  interrupt sources to the same handler table in the same priority order.

## Reboot

### `OSi_DoBoot`

- **Interface:** `void OSi_DoBoot(void)`, ARM in ITCM (0x01FF833C), the last
  step of a system reset. It never returns: it ends with `bx` to the new
  program's ARM9 entry point with `lr` set to that same address, `r0`-`r10`
  loaded from 0x02FFFF80 and `r11` zero.
- **Behavior:** disables interrupts by writing 0x04000000 (bit 0 clear) to
  `REG_IME`, clears the DTCM interrupt-check word at
  0x027E3FFC and waits until the ARM7 reports state 1 in the low nibble of
  `REG_IPCSYNC`. It answers with 0x100 (state 1 sent to the ARM7), then wipes
  the shared system area with the ITCM fill routine: 0x02FFFD80-0x02FFFDFF
  (keeping the word at 0x02FFFF9C by moving it to 0x02FFFD9C),
  0x02FFFF80-0x02FFFF97, the halfword at 0x02FFFF98 and 0x02FFFF9C-0x02FFFFFF.
  It waits until the ARM7's state is no longer 1, clears `REG_IPCSYNC`'s low
  halfword, reads the ARM9 entry point from the copied card header
  (0x02FFFE24), loads `r0`-`r10` from 0x02FFFF80 (now mostly zero) and jumps.
- **Hardware:** writes `REG_IME` (0x04000208); polls and writes the
  inter-processor sync register `REG_IPCSYNC` (0x04000180), whose low nibble
  is the ARM7's state and bits 8-11 the state sent to it, so the two CPUs
  restart in step; 0x02FFxxxx is the mirror of the top of main RAM where the
  BIOS keeps the card header and boot parameters. A port restarts its own
  program instead.

### `OSi_ReloadRomData`

- **Interface:** `void OSi_ReloadRomData(BOOL isFirstBoot)`, ARM in ITCM
  (0x01FF8420), a C function whose body is an inline assembly block; standard
  procedure call, `r4` preserved. Called during a system reset, before
  `OSi_DoBoot`.
- **Behavior:** takes the card offset of the running program from
  0x02FFFC2C (zero when `isFirstBoot` is non-zero). If that offset is at least
  0x8000 it re-reads the 0x160-byte card header to 0x02FFFE00 through
  `Boot_ReadRom(src, dst, size)`. It then reloads the ARM9 binary (header
  fields 0x20 ROM offset, 0x28 RAM address, 0x2C size, plus the program
  offset) and the ARM7 binary (fields 0x30, 0x38, 0x3C), each only when its
  size is positive as a signed value. When the ARM9 block starts inside the
  first 0x8000 bytes (signed compare), the secure area, which cannot be read
  again, is skipped: the read starts at 0x8000 and the destination and size
  are adjusted by the same amount. Last it cleans the whole data cache by set
  and index (four segments of 32 lines), invalidates both caches and drains
  the write buffer.
- **Hardware:** the reads go through the card interface in `Boot_ReadRom`;
  CP15 clean D-cache line by index (c7,c10,2), invalidate D-cache (c7,c6,0),
  invalidate I-cache (c7,c5,0) and drain write buffer (c7,c10,4) make the
  reloaded code visible. 0x02FFFxxx is the system area in the main RAM
  mirror.
