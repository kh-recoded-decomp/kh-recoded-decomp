# Contributing

Thanks for helping decompile *Kingdom Hearts Re:coded*! The workflow is simple:
pick a function, write C that compiles to the **exact same bytes** as the
original, and open a PR.

## The one rule: byte-exact

A function is only accepted when it passes byte-exact verification
(`tools/verify_idx.py` must print `>>> MATCH <<<`) and the full build still
links every module byte-identical to the ROM (`bash tools/gate.sh`).

Byte-exact matching is not the same thing as C decompilation progress: inline
ASM can match the original bytes but never counts as C. See
[docs/PROGRESS_POLICY.md](docs/PROGRESS_POLICY.md).

When contributing, please say whether a function is:

- real C matched
- non-matching C (work in progress, under `nonmatching/`)
- ASM stub
- a symbol/name-only improvement

## Claiming work

Functions are grouped by **module** (`main`, `itcm`, `ov000` ... `ov104`).
To avoid duplicated effort, check [PROGRESS.md](PROGRESS.md) and mention the
module you are working on in an issue before starting. Collisions are harmless
(only matching code is merged), claiming just saves wasted effort.

## Setup

You must provide your own legally-obtained copy of the game. Nothing
copyrighted is distributed here.

### Reference ROM

This project targets one specific dump. If your `recoded.nds` does not match
these hashes, addresses will not line up.

| | |
|---|---|
| File | `recoded.nds` (place it in the repository root) |
| Size | 268,435,456 bytes (256 MiB) |
| Region | EU (gamecode `BK9P`, maker `GD` = Square Enix) |
| SHA-1 | `b9d45dcd654265fc7b8ba83f1bb3c15f011d6acf` |
| SHA-256 | `44e8420cffac48382a49fbfa2b6bbf2c0318a29cd446ee75dd67a28a17deab09` |
| MD5 | `605567dc2a710b2fdbd40853b1a04239` |

### Toolchain

1. **Python 3** with `pip install capstone pyelftools ninja`.
2. **dsd 0.12.1**: download `dsd-windows-x86_64.exe` (or your platform's
   build) from [AetiasHax/ds-decomp v0.12.1](https://github.com/AetiasHax/ds-decomp/releases/tag/v0.12.1)
   and place it at `tools/dsd.exe`.
3. **CodeWarrior for DS**: `mwccarm` 3.0 build 139 under
   `tools/mwccarm/3.0_patch4/` and `mwldarm` 2.0 SP2p4 under
   `tools/mwccarm/2.0/sp2p4/`, with the license file at
   `tools/mwccarm/license.dat`. The paths live in `tools/project.py`.
4. **Arm GNU Toolchain 12.2.1**, with `arm-none-eabi-as` and
   `arm-none-eabi-gcc` on `PATH`. The assembler handles `.s` sources. GCC is
   used only by original assembly routines converted to byte-exact C,
   including hardware intrinsics. Each unit selects `gcc/12.2.1` or one of
   its profiles in `config/arm9/file_compilers.json`. Set `ARM_NONE_EABI_GCC`
   to select a GCC executable outside `PATH`; its version is checked before
   compiling.
5. **Clang 22.1.3** for explicitly selected original assembly routines whose
   hardware intrinsics produce byte-exact C. These units select `clang/22.1.3`
   in `config/arm9/file_compilers.json`. Set `ARM_NONE_EABI_CLANG` to choose
   the executable; otherwise the driver checks `PATH` and Visual Studio's
   bundled x64 LLVM directory. The driver checks the version before compiling.
6. **ARM Compiler 5.06 update 7, build 960**, for explicitly selected original
   assembly routines whose native C intrinsics match the ROM. These units select
   `armcc/5.06u7`. Set `ARMCC5` to the executable, or place the local installation
   under `tools/armcc/5.06u7/ARM/ARMCC/bin/armcc.exe`. Existing
   `ARM_PRODUCT_PATH` and `ARM_TOOL_VARIANT` settings are preserved; the MDK
   directory layout defaults to its `ARM/sw/mappings` and `mdk_lite` settings.
   The driver requires native ELF output and records compiler, source and object
   hashes beside each output. No object conversion or instruction patching is
   performed by the ARMCC driver. The existing common linker preparation still
   normalizes `.text` alignment metadata from four to two; instruction bytes
   are unchanged.

The ARMCC driver accepts the original build-960 executable (SHA-256
`52fcff95b164ef766b7ba8931b6fc4cc9504018db94d7f10f8b62107df74f963`) and the
locally requested CPU/ELF capability variant
(`90366b3b7879aa7d2909cbade2c25b9cbfc2bae352100fd9915471b7f7f8b597`). The latter
is a modified executable: its 18 changed bytes affect the CPU entitlement and
restricted object-format checks. Its code-generation implementation is retained.
The selected variant is included in every compilation receipt. Compiler binaries
are local dependencies and are not distributed in this repository.

`MI_SwapWord` uses ARMCC's native `__swp` intrinsic with a typedef-only SDK
header. Its C implementation and included header contain no assembly.

GCC and Clang units remain subject to the same per-function verifier and full module
gate. They use ARM946E-S, soft float and the GNU APCS ABI; GNU relocation
encoding keeps their objects compatible with the existing mwldarm linker.
Clang uses the assembler alongside the selected Arm GNU GCC 12.2.1 executable
to emit the same GNU relocation format. No compiler runtime library is linked.
Unwind tables are disabled; Clang also selects the DWARF exception model to
avoid EHABI's implicit `.ARM.exidx` entries, which mwldarm cannot relocate.
Other C units use their per-file CodeWarrior compiler selections.

The GCC selections `gcc/12.2.1/scratch-r0`, `scratch-r1` and `scratch-r2`
(all with the same version prefix) are restricted to original assembly leaf
routines and tail-call wrappers. Each reserves the other argument registers
with `-ffixed-rN` and disables temporary-expression replacement with
`-fno-tree-ter`, preserving the original scratch register and operand order.
These profiles do not change the function signatures or calling convention.

The `gcc/12.2.1/operand-order` selection uses `-fno-tree-ter` without reserving
registers. It preserves the address arithmetic in original cache-maintenance
loops. These implementations take the starting address as a 32-bit unsigned
value, with the same ARM argument representation as the original pointer.

The `gcc/12.2.1/wait-state` selection reserves r2 and r3 and disables
temporary-expression replacement. `OSi_CancelDma0` then retains the scanline
in r0, the saved IME in r1 and the hardware base in ip. Its 64-bit result
packs the final scanline into the low word and the saved IME into the high
word; its caller declares that result consistently and discards it.

The `gcc/12.2.1/fifo-zeros` selection disables the second CSE pass and
post-reload CSE without reserving registers. `GXi_NopClearFifo128_` binds four
zero values to r1, r2, r3 and r12 and stores them as 32 four-word groups; the
two passes would otherwise merge the separate zero initializations.

The `gcc/12.2.1/mode-select` selection disables dominator optimization, value
range propagation and code sinking without reserving registers.
`OS_InitContext` then keeps the masked program-counter bit as the result of the
original flag-setting `ands` before selecting the initial processor mode.

The `clang/22.1.3/source-order` selection disables scheduling after register
allocation. It preserves the original order of CPSR writes and result masks
in interrupt-control routines.

`OS_RestoreInterrupts` and `OS_RestoreInterrupts_IrqAndFiq` expose the original
leaf routines' three register results as `OSInterruptState`: the previous
interrupt mask, previous CPSR and updated CPSR. Their Clang `swiftcall`
definitions and MWCC DSi `value_in_regs` declarations pass the argument in r0
and return those fields in r0-r2. All callers discard the result and retain
their exact ROM bytes. The shared header keeps their declarations consistent
with the definitions. This compatibility is specific to this signature, not a general interchange
of the two calling conventions. Callers previously using older CodeWarrior
versions explicitly select dsi/1.1 to support `value_in_regs`; existing DSi
selections remain in place. `CARDi_NotifyEvent` and `FS_RegisterArchiveName`
also use `#pragma ipa file` to retain the original list-head address loads.

EU wrappers include `os_interrupt_state.h` before their shared source. Those
sources omit their legacy scalar declaration when this header is present;
the US build retains its original declarations and preprocessed code.
Filesystem wait helpers that call the interrupt API live in
`libs/nitro/fs/fs_wait_internal.h`, so other filesystem units do not need the
register-result calling convention.

### Extract and index

```sh
tools/dsd.exe rom extract --rom recoded.nds --output-path dsd_extract/
python tools/configure.py            # delinks, dsd delink + lcf, build.ninja
python tools/rebuild_index.py --write
```

`config/` is already committed; do **not** run `dsd init` again, it would
overwrite the symbol names. `bash tools/rebuild_rom.sh` checks that the
extraction round-trips (only the 4 header CRC bytes may differ).

## Building and verifying

```sh
bash tools/gate.sh        # configure, compile, link, dsd check modules
bash tools/build_rom.sh   # pack build/recoded.nds and compare with the ROM
```

`gate.sh` deletes the previous module images, compiles every matched source,
links the whole ARM9 program (`ninja build/arm9.elf`) and hashes every linked
module against the ROM. The expected result is `GATE PASSED (108/108 ...)`.
The packed ROM differs from the reference only in 4 non-functional CRC bytes
(0x6C/0x6D secure-area CRC and 0x15E/0x15F header CRC).

## Decompiling a function

1. Get its data and the verify command:
   ```sh
   python tools/getcand.py func_XXXXXXXX
   ```
2. Write C to `src/auto/<name>.c` (no calls or data references) or
   `src/calls/<name>.c`; overlay functions go under
   `src/overlays/ovNNN/{auto,calls}/`, library functions under
   `libs/<library>/<module>/{auto,calls}/`. One function per file, the file
   named after the function.
3. Run the printed verify command until it reports `>>> MATCH <<<`. Most game
   code in this ROM is THUMB (`--thumb`).
4. Run `bash tools/gate.sh`, then `python tools/progress.py` and
   `python tools/update_readme.py`, and open a PR with the new sources and the
   regenerated `PROGRESS.md` / `README.md`.

`config/**/delinks.txt` is generated by `tools/gen_delinks.py` (run by
`configure.py`); never edit it by hand. Rename symbols in
`config/**/symbols.txt` as you understand them.

### Reusing khdays-decomp

Many library and engine functions are identical in *358/2 Days*. Before
decompiling by hand, check whether khdays-decomp already has the function:
`tools/port_days.py` ports every such function automatically and verifies each
one. See [docs/PORTING_FROM_DAYS.md](docs/PORTING_FROM_DAYS.md).

### decomp.me

```sh
python tools/decompme.py func_XXXXXXXX --verify
```

prints the compiler flags, target assembly and context for a
[decomp.me](https://decomp.me) scratch (platform Nintendo DS, compiler
**3.0 build 139 (MW 2.0sp2p4)**).

## Notes

- Compile flags are pinned in `tools/project.py`; do not change them casually.
- Keep C minimal and readable.
- Never commit the ROM, extracted data, build output or the toolchain.

## Scope reminder

This is a matching decompilation, not a port. Do not add ROM data, assets, or
any copyrighted material to the repository.
