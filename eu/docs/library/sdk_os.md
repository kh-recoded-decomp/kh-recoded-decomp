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

### `Entry`

- **Interface:** the ARM9 program's entry point (0x02000800, crt0's
  `_start`), jumped to by the BIOS or by `OSi_DoBoot` with interrupts masked.
  It never returns: it ends with `bx` to `main` with `lr = 0xFFFF0000` (the
  BIOS), in system mode on the system stack.
- **Behavior:** disables interrupts (writes 0x04000000, bit 0 clear, to
  `REG_IME`), waits for `VCOUNT` to read line 0 and calls the CP15 set-up
  (`func_02000A78`: protection regions, TCMs, caches). It sets the SVC stack
  to DTCM + 0x3FC0, the IRQ stack to DTCM + 0x3F7C (0x40 below, rounded) and,
  in system mode with the flags cleared, the system stack 0x800 bytes below
  the IRQ stack, rounded down to eight bytes (0x027E3778). It clears all of
  DTCM and the 1 KB of standard palette RAM, fills the 1 KB of OAM with
  0x00000200 words (every sprite hidden), decompresses the static module with
  `MIi_UncompressBackward(BuildInfo.compressedEnd)`, runs
  `INITi_DoAutoload`, clears .bss from `BuildInfo + 0x0C` up to
  `BuildInfo + 0x10` (unsigned, word steps) and flushes its cache lines as the
  autoload copier does. It clears the word at 0x02FFFF9C, stores
  `OS_IrqHandler` in the IRQ handler slot at the end of DTCM (0x027E3FFC),
  calls two empty start-up hooks and `RunGlobalConstructors`, and jumps to
  `main`.
- **Hardware:** `REG_IME` (0x04000208), `VCOUNT` (0x04000006), palette RAM
  (0x05000000), OAM (0x07000000) and DTCM; the stacks are the banked SVC, IRQ
  and system/user `sp`; CP15 cache maintenance as in `INITi_DoAutoload`. The
  BIOS reads the IRQ handler address from the last word of DTCM. A port
  replaces all of this with its own start-up before `main`.

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

### `OS_IrqHandler_ThreadSwitch`

- **Interface:** `void OS_IrqHandler_ThreadSwitch(void)`, ARM in ITCM
  (0x01FF81B0), reached in IRQ mode as the return address of the interrupt
  handler `OS_IrqHandler` called. The IRQ stack holds the `lr` that
  `OS_IrqHandler` pushed, then the BIOS's frame `r0`-`r3`, `r12`, `lr` of the
  interrupted code. It returns by popping that first `lr`, back into the BIOS,
  which restores the frame and returns from the interrupt.
- **Behavior:** wakes every thread waiting for an interrupt: each one in
  `OSi_IrqThreadQueue` (DTCM 0x027E00A0, linked at +0x80) becomes ready
  (state 1) with its queue fields cleared, the queue is emptied and a
  reschedule is requested. Without a pending reschedule
  (`OSi_ThreadInfo.isNeedRescheduling`) it returns. Otherwise it clears the
  request and, in IRQ mode with IRQ and FIQ disabled, picks the first ready
  thread of the priority-ordered thread list (linked at +0x68). If there is
  none, or it is the current thread, it returns with FIQ enabled again.
  Otherwise it calls the switch callback, if any, with the old and new
  threads, makes the new thread current and switches: the old context gets
  the SPSR as its CPSR, `r0`-`r3`, `r12` and the return address from the
  BIOS frame, `r4`-`r11` and the user-bank `sp` and `lr` as they are, and the
  SVC `sp`; the divider context is saved with `CP_SaveContext` and the new
  one restored with `CPi_RestoreContext`. It loads the new SVC `sp`, puts the
  new CPSR in the IRQ SPSR (flags and control fields), loads the user-bank
  `r0`-`r14` from the new context and rewrites the BIOS frame with the new
  `r0`-`r3`, `r12` and resume address, so that the BIOS's return lands in the
  new thread.
- **Hardware:** the IRQ and SVC banked stacks and the IRQ SPSR are the
  ARM9's; the divider context belongs to the math unit. A port switches
  threads with its own scheduler at the same points: after an interrupt
  handler, when a reschedule was requested.

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

## Thread contexts

`OSContext` is 0x64 bytes: `u32 cpsr; u32 r[13]; u32 sp; u32 lr; u32
pc_plus4; u32 sp_svc; CPContext cp_context;` (the divider context, see
[sdk_misc.md](sdk_misc.md)). Threads switch by saving one context and loading
another.

### `OS_SaveContext`

- **Interface:** `BOOL OS_SaveContext(OSContext *context)`, ARM, standard
  procedure call; callable from any privileged mode. Like `setjmp` it returns
  0 now and 1 when the context is later loaded.
- **Behavior:** saves the divider context with `CP_SaveContext`
  (`context + 0x48`), then stores the CPSR as it is, switches to SVC mode
  with IRQ and FIQ disabled just long enough to store the SVC-mode `sp` in
  `sp_svc`, and returns to the caller's mode. It stores `r0`-`r14` of the
  current mode with `r0` replaced by 1 (the value a resumed context returns),
  so `r1` holds `context + 4` and `r2` the saved CPSR, and stores as
  `pc_plus4` the address after its own final `bx lr` plus four, so that
  loading the context resumes at that `bx lr` with `r0 = 1`. The flags and
  mode are unchanged on return.
- **Hardware:** `CP_SaveContext` reads the divider and square-root unit.
  Switching through SVC mode uses the banked SVC stack pointer; a port keeps
  one stack pointer per thread instead.

### `OS_LoadContext`

- **Interface:** `void OS_LoadContext(OSContext *context)`, ARM, from any
  privileged mode. It does not return to its caller: it continues the saved
  thread.
- **Behavior:** restores the divider context with `CPi_RestoreContext`
  (`context + 0x48`), switches to SVC mode with IRQ and FIQ disabled, puts
  the saved CPSR in the SVC SPSR, loads the SVC `sp` from `sp_svc` and the SVC
  `lr` from `pc_plus4`, loads the user-bank `r0`-`r14` from the context (so a
  context saved in an exception mode gets its `sp` and `lr` in the user bank,
  not its own), and returns with `subs pc, lr, #4`, which copies the SPSR to
  the CPSR and continues at `pc_plus4 - 4` in the saved mode with the saved
  flags and interrupt masks.
- **Hardware:** `CPi_RestoreContext` writes the divider and square-root
  unit; the mode switch, SPSR and banked registers are the ARM9's own.

## Exceptions

`OSi_ExContext` (0x02056E20) receives the state of the code an abort or
undefined-instruction exception interrupted; `OSi_ExceptionState`
(0x02056DF0) holds the debugger hook, the argument and the address of the
game's exception handler.

### `OSi_ExceptionHandler`

- **Interface:** `void OSi_ExceptionHandler(void)`, ARM, installed as the
  BIOS's exception hook and entered in the exception's mode. It never
  returns: it ends in a wait loop. The instructions after the loop (restore
  and `bx lr`) are unreachable and declared so in the inventory.
- **Behavior:** calls the debugger hook in `OSi_ExceptionState` first when
  one is set (`movne lr, pc; bxne`, so the saved `lr` is then the address
  after that call). It pushes `r0`-`r3`, `sp` and `lr` to the top of ITCM
  (0x01FFFFE8-0x01FFFFFF), makes that its stack, and in abort or undefined
  mode calls `OSi_GetAndDisplayContext` with `r0 = sp & 1` and `r1` the mode.
  It then waits forever: in a one-instruction loop when there is no debugger
  hook, in a `nop` loop otherwise. The test stops at the first loop and
  checks which way it goes.
- **Hardware:** none beyond the exception modes and the ITCM it uses as a
  stack, chosen because main RAM may be what faulted. A port reports the fault
  and stops.

### `OSi_SetExContext`

- **Interface:** `void OSi_SetExContext(u32 arg)`, ARM, called with `r12`
  pointing at the six words `OSi_ExceptionHandler` pushed (`r0`-`r3`, the
  exception-mode `sp`, `lr`) and `r4`-`r11` still those of the interrupted
  code. Returns to its caller in its caller's mode with its CPSR restored.
- **Behavior:** fills `OSi_ExContext`: `arg` at 0x6C, the pushed `r0`-`r3`
  at 0x04-0x10, `r4`-`r11` at 0x14-0x30, and from the BIOS's four-word
  exception frame at the pushed `sp` (bit 0 cleared) the CPSR of the
  interrupted code at 0x00, its `r12` at 0x34, its `pc` at 0x40 and the first
  word at 0x64. It then switches to the interrupted mode (with IRQ disabled
  and the T bit cleared) to store that mode's `sp` and `lr` at 0x38 and 0x3C,
  reads that mode's SPSR into a register it never uses, and switches back.
  The other words of the context are left as they are. The interrupted mode
  must be privileged: from user mode the switch back would be refused by the
  CPU, which the SDK never meets because games run in system mode.
- **Hardware:** the mode switches use the ARM9's banked registers. In system
  mode the SPSR read is UNPREDICTABLE on ARM; the emulator reads 0 and
  records it, and the result is dead.

### `OSi_DisplayExContext`

- **Interface:** `void OSi_DisplayExContext(void)`, ARM, a C function with an
  inline assembly block, called in the exception's mode after
  `OSi_SetExContext`. Returns normally.
- **Behavior:** does nothing when no game handler is installed
  (`OSi_ExceptionState + 0x0C` is null). Otherwise it switches to system mode
  with IRQ disabled but keeps the exception-mode stack, saving the system
  `sp` and the CPSR on it, enables the protection unit, calls the handler
  with `OSi_ExContext` and the argument from `OSi_ExceptionState + 4`,
  disables the protection unit, restores the system `sp` and returns to the
  exception mode. The restored flags are those of its own `handler != 0`
  test, not the caller's.
- **Hardware:** `OS_EnableProtectionUnit` and `OS_DisableProtectionUnit` set
  and clear the protection-unit bit of the CP15 control register around the
  handler; the test replaces them with logging stubs.
