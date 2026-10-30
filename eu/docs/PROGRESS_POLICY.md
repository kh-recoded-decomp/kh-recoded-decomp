# Progress policy

Progress is split into categories so contributors and external trackers can see
what has actually been decompiled into C.

## Real C decompilation

A function counts as real C decompilation only when it is implemented in C and
passes byte-exact verification against the original code
(`tools/verify_idx.py`), and the full build still links every module
byte-identical to the ROM (`tools/gate.sh`).

Functions ported from khdays-decomp (see [PORTING_FROM_DAYS.md](PORTING_FROM_DAYS.md))
are held to exactly the same standard: they are real C that recompiles to this
ROM's bytes, and each one is verified here, not assumed from the other project.

## Parameters the callers do not pass

A definition may keep a parameter that no caller supplies when the original
code's allocation proves the parameter existed. mwcc numbers incoming parameters
before every local and allocates in that order, so a value that the ROM colours
or spills as an incoming parameter cannot be reproduced by any local. Such a
parameter counts as real C only when all of these hold:

1. Every caller is checked: none sets the register deliberately (it holds a value
   left from earlier code, or the function is called through a pointer type that
   takes no such argument).
2. The parameter is assigned before any read, so no behavior depends on it.
3. The same source written with a local differs from the ROM only in the
   allocation the parameter explains, and the alternatives tried are recorded.
4. The source comment and the function's document state the above, so a port
   calls the function with its real inputs.

The cases accepted so far are `RunSceneLoadStep` (ov045,
[SCENE_LOAD_STEP.md](SCENE_LOAD_STEP.md)) and `LoadCarouselModels` (ov087,
[CAROUSEL_MODELS.md](CAROUSEL_MODELS.md)). This does not extend to other devices
that steer the compiler, such as invented absolute symbols for constants.

## Library assembly

Some library functions were written in assembly by their authors: NitroSDK's
`asm` functions (cache and protection-unit control, interrupt masking, context
switches, copy/fill kernels, matrix helpers), the BIOS SWI veneers and the
CodeWarrior runtime helpers. Many use instructions C cannot express with this
compiler (`mcr`/`mrc`, `mrs`/`msr`, `swi`). They live under
`libs/**/asm_stubs/` as that original assembly, verify byte-exact and are shown
separately. They never count as C.

An original assembly routine may instead count as real C when a readable C
implementation using compiler intrinsics reproduces every byte. Such units
explicitly select a supported GCC, Clang or ARMCC profile in the compiler map
and pass the same per-function verification and full gate. The ARMCC driver
records its executable variant and source/object hashes for each compilation.
The ARMCC `armv4t-interwork` profile selects an instruction subset compatible
with ARM946E-S and retains separate register-restore and `BX` return sequences.
It uses the same compiler and public calling convention; every native instruction
and linked module must still match the original.
Inline assembly, including assembly in included headers, remains excluded
from real-C progress regardless of the selected compiler.

C register-binding declarations, such as `register u32 mask __asm("r1");`,
are permitted for original assembly routines. They name a register without
supplying instructions. Only complete declarations naming a core register are
excluded from the assembly scan; instruction blocks and other assembly forms
remain excluded from real-C progress. These implementations must preserve the
callers' interface and pass the same byte, relocation and full-module gates.

## Verified library code (MobiClip)

The MobiClip movie library in ov022 (Actimagine, "Mobiclip SDK V1.1.1") is
hand-written ARM: the video decoder the player copies into its arena, the
colour converter, the deblocking filter, the FastAudio decoder, the coding-1
speech decoder, and the two run/level prefix tables the video decoder reads.
It returns with `mov pc, lr`, keeps tables between its routines and carries
values in r4-r11 across inner calls, so no compiler produces it and it can
never match as C.

A block of it counts as reconstructed library code only when
`tools/mobiclip/verify_mobiclip.py` issues its receipt, which requires every one
of these gates for the checked-in source:

1. **Source.** Every instruction is an ARM mnemonic with its own address label;
   raw bytes only appear inside named DATA regions; dispatch entries are
   symbolic relative words; `.incbin`, `.inst` and numeric opcode words are
   refused. GNU as must reproduce the ROM bytes at the block's addresses, and a
   partial link through the project's mwldarm must keep them. The run/level
   tables are 4096 `vlc bits, level, run, last` entries plus 256 residue bytes.
2. **Inventory.** The instructions reachable from the block's entry points and
   the declared DATA ranges tile the block exactly, with no gap or overlap.
3. **Semantics.** A portable implementation (`tools/mobiclip/`) reproduces the
   original code: complete movie streams decoded by `mobiclip_reference.py`
   equal FFmpeg frame for frame; the colour, deblocking, FastAudio and coding-1
   models agree with the ROM's own instructions run in `arm_exec.py`; and each
   block reproduces a capture of a real call taken from this ROM in DeSmuME
   (`capture_mobiclip_decoder.lua`, `capture_mobiclip_kernels.lua`). No movie
   in the game uses deblocking, FastAudio or coding 1, so the capture script
   forces those paths once each and restores the player's state afterwards.

A receipt only applies while the source's SHA-256 is unchanged. In PROGRESS.md
these blocks are reported in their own `Verified library` column and in a
separate "C + verified library" total; they never count inside the C figures.
The objdiff report published to decomp.dev counts them as matched code under
their own category, "MobiClip: verified library (hand-written ARM)", so a unit
whose remaining code is all verified library shows as complete there.

## Verified library code (NitroSDK and MSL)

The NitroSDK and CodeWarrior runtime routines that their authors wrote in
assembly (division and floating-point helpers, copy and fill kernels, context
switches) may be reported the same way, in the same `Verified library` column
and never inside the C figures. Matching bytes alone is not enough: a routine
counts only when `tools/sdklib/verify_sdklib.py` issues its receipt, which
requires all of these gates for the checked-in source:

1. **Source.** The asm stub holds instructions, not raw words, and rebuilds the
   ROM bytes and relocations exactly.
2. **Inventory.** The instructions reachable from the entry and the literal
   pools they load tile the routine's symbol range exactly. Instructions no
   path reaches are allowed only when declared, documented with the evidence
   that nothing branches to them, and counted separately in the receipt.
3. **Semantics.** A portable Python model (`tools/sdklib/families/`) and the
   ROM's own instructions, run in `tools/mobiclip/arm_exec.py`, agree on at least
   100 random and edge-case inputs, register results, flags and memory alike.
4. **Documentation.** The routine's section in `docs/library/` states its
   interface (registers, clobbers, stack and calling convention), its behavior
   (including edge cases where it differs from C) and its hardware dependencies,
   so a port can replace it without reading the assembly.

Receipts are kept in `library_receipts.json`. A receipt applies only while both
the source's and the documentation's SHA-256 are unchanged. Where GCC or Clang
reproduce such a routine from readable C, that C is preferred and counts as C
under the rules above; its section in `docs/library/` documents it the same way.

## Verified library code (DS Protect)

The DS Protect anti-piracy library in ov104 keeps its checks encrypted behind
hand-written ARM: seventeen dispatch trampolines that read `pc`, five static
initializers, the shared decrypt-call-encrypt dispatcher and the table decoder,
whose cache maintenance is an inline `mcr` block. No compiler produces this code,
so it is reported in the same `Verified library` column under the same four
gates, with its model in `tools/sdklib/families/dsprot.py` and its documentation
in `docs/library/dsprot.md`. The encrypted checks themselves are C and count as C.

## ASM stubs

Inline ASM or placeholder assembly for game code may be used temporarily while
researching a function. It may match the original bytes, but it does not count
as C-decompiled progress and belongs under `asm_stubs/`.

## Authorized CLZ exception

The user authorizes the same narrow exception used in khdays-decomp: a function
may retain inline assembly for the `clz` instruction while its surrounding
implementation is readable C. This does not authorize other inline assembly or
assembly placeholders for game code.

Such a function must still pass byte and relocation verification and the full
module gate. It is an authorized assembly exception, not pure C, and must be
reported separately without increasing real-C progress. Authorization alone
does not add verified bytes or change the report totals.

When such a function is NitroSDK library code rather than game code, it may be
reported as verified library code under the four gates above, never as C: its
model lives in `tools/sdklib/families/` and its documentation in
`docs/library/`. The wireless helper's `WH_StateInStartScan` (ov015, the SDK's
`MATH_CountLeadingZeros` inlined in `wh.c`) is the one case so far, documented
in `docs/library/sdk_wh.md`.

## Named functions

A function may have a known name (for example a NitroSDK name carried over from
khdays-decomp where the evidence is one-to-one) before it has a C
implementation. Names help research, but they do not count as progress.

## DATA

DATA progress covers the complete `.rodata`, `.ctor`, `.data` and `.bss` ranges
declared by every module. A byte only counts as reconstructed after a source file
owns that range and the full module gate proves the linked output byte-exact.

Named DATA symbols are reported separately. Identifying a variable or table helps
reverse engineering, but does not count any bytes as reconstructed.

The objdiff v2 report publishes the same totals as `totalData` and
`matchedData`, so decomp.dev shows DATA independently from code.

## Why this matters

Byte-exact matching is the technical verification gate, but public progress
only counts real C implementations, measured both by function count and, more
honestly, by code bytes.
