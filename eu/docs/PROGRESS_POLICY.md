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

## Library assembly

Some library functions were written in assembly by their authors: NitroSDK's
`asm` functions (cache and protection-unit control, interrupt masking, context
switches, copy/fill kernels, matrix helpers), the BIOS SWI veneers and the
CodeWarrior runtime helpers. Many use instructions C cannot express with this
compiler (`mcr`/`mrc`, `mrs`/`msr`, `swi`). They live under
`libs/**/asm_stubs/` as that original assembly, verify byte-exact and are shown
separately. They never count as C.

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

A receipt only applies while the source's SHA-256 is unchanged. These blocks are
reported in their own `Verified library` column and in a separate
"C + verified library" total; they never count inside the C figures.

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
