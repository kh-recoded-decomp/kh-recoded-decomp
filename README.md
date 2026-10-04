# Kingdom Hearts Re:coded matching decompilation (BK9E)

This project targets the North American Nintendo DS release, game code `BK9E`,
revision 0. It is a matching decompilation workspace. The original ROM and all
extracted game binaries and assets stay on the owner's machine and are ignored by Git.

## Current state

- The exact BK9E ROM is identified by SHA-256 before any extraction, build, or progress check.
- `dsd` 0.12.1 extracts ARM9, ITCM, DTCM, ARM7, 105 ARM9 overlays, and 805 data files.
- A baseline ROM can be repacked and matched byte for byte to the input ROM.
- ARM9 symbols, relocation metadata, and module profiles are initialized in `config/bk9e/arm9/`.
- A pinned compiler and ARMv5 relocation pipeline verify C functions independently. See [PROGRESS.md](PROGRESS.md) for freshly rebuilt coverage and [matches.json](matches.json) for behavior and uncertainty.

**Progress (2026-10-04): 60.3% verified ARM9 C/C++ code** (1,065,416 / 1,768,220 bytes,
9,108 functions) and 93,751 / 228,140 ARM9 data bytes reconstructed. See
[PROGRESS.md](PROGRESS.md) for the per-module breakdown.

The baseline rebuild proves that extraction and packing are reproducible. `link` goes further:
every registered C match is compiled to an object and linked with `mwldarm` in place of its
original bytes, the remaining code and data come from `dsd` delinked objects, and all 108 ARM9
modules plus the packed ROM must equal the original exactly. Functions whose objects cannot be
placed yet (shared data sections, ambiguous overlay targets) stay delinked and are listed in
`build/bk9e/link_skipped.txt`.

Data sections are reconstructed the same way. Each `.rodata`, `.data` or `.bss` range in
`data_matches.json` is C that `tools/data_match.py` compiles, relocates and compares byte for byte
(`.bss` by size and symbol layout), and `link` places it in the ROM. `tools/gen_bss.py` generates
`.bss` layout files (one sized global per known symbol) and `tools/gen_data_tables.py` generates
pointer tables whose every entry names its target, and `tools/gen_strings.py` generates string
objects; progress reports each of these separately from hand-typed data. ARM7 has been extracted but its function analysis has
not been bootstrapped by `dsd`.

## Quick start on Windows

Python 3.12 or newer is required. `setup` downloads a pinned Windows build of
[`dsd` 0.12.1](https://github.com/AetiasHax/ds-decomp/releases/tag/v0.12.1)
into the ignored `.tools/` directory and checks its SHA-256.

```powershell
python -m pip install -r requirements.txt
python tools/compile_match.py install
python tools/khrecoded.py setup --rom "C:\path\to\recoded.nds"
python tools/khrecoded.py check --profile full
python tools/khrecoded.py progress
```

The first command writes an ignored `local.json`, so subsequent commands find
the same ROM automatically. You can instead set `KH_RECODED_ROM` or pass `--rom`
each time. `khrecoded.cmd` is a Windows shortcut for the Python command.

## Check profiles

| Profile | What it checks | ROM needed |
|---|---|---|
| `ci` | ROM-free unit tests and committed module inventory | No |
| `quick` | `ci` checks, exact ROM identity, extraction inventory | Yes |
| `full` | `quick`, exact baseline ROM rebuild, all registered C/C++ matches, regenerated progress | Yes |
| `strict` | `full` plus the linked build: C objects and delinked objects linked into every module, `dsd check modules --fail`, exact ROM | Yes |

Run `python tools/khrecoded.py check --profile strict`. `build` repacks the extracted baseline into
`build/bk9e/rebuilt.nds`; `link` links the ROM from objects into `build/bk9e/linked.nds`. Both
verify exact equality with the original. dsd 0.12.1 zeroes two unused header bytes and recomputes
the header CRC, so both restore exactly those four header bytes before comparing.

## Progress and correctness

Run `python tools/khrecoded.py progress` to update [PROGRESS.md](PROGRESS.md)
and local `build/progress.json`. The report lists every module, including all
105 overlays. Its primary ARM9 denominator is the union of `dsd` code ranges;
function count and identified function bytes are secondary figures. ARM7 remains
an explicitly unanalysed target. Assets are tracked as extraction inventory,
not as decompiled code.

Only a function compiled from an authored file during the progress command and
byte-matched against the appropriate extracted module contributes C/C++ bytes.
All 109 reference binaries are independently pinned by SHA-256, so modified
extracted bytes cannot silently become a new matching target.
Shared middleware recovered as C is included, with its origin recorded.
Original SDK binaries and assembly add no C coverage. `matches.json` records
fixed compiler settings, linker bindings, and human-readable explanations.
Every relocation and literal-pool byte participates in the comparison; no byte
masks or size trimming are allowed. Understanding is reported separately from
matching, distinguishing proven gameplay roles from generic engine subsystems. A copied ROM, delinked object, renamed symbol, or unchanged binary
does not count. See [CONTRIBUTING.md](CONTRIBUTING.md).

The `dsd` repack initially differs at header offsets `0x6C–0x6D` and
`0x15E–0x15F`. The build script checks that **only** those four header bytes
changed, restores them from the exact-hash input ROM, and compares every byte
of the 256 MiB result. Any other difference fails the build.

## How functions get matched

Every counted function is C that rebuilds to the exact original bytes. Three routes produce it:

1. **Shared code from KH 358/2 Days** (`tools/days_port.py`). Re:coded reuses the Days
   engine and the same Nitro middleware. Every CC0 Days source is compiled with both pinned
   compilers, in ARM and Thumb state. A compiled Days function whose bytes equal a Re:coded
   function once relocated words (calls, pointers) are masked is a candidate. Each relocation is
   solved against the Re:coded instruction to find the real callee or global, the source is
   renamed to Re:coded addresses, and it is kept only if the rebuild matches every byte.
2. **Copies inside Re:coded** (`tools/twin_port.py`). Overlays carry duplicate helpers; a
   verified source is re-bound to each byte-identical copy and verified again.
3. **Manual matching** (`tools/match_tool.py`). `show` prints the target disassembly with
   resolved relocations, the Ghidra decompiler view (`tools/ghidra/DecompileTargetsBK9E.java`)
   and the most similar Days function; `try` compiles a candidate and prints an aligned diff;
   `stage` queues a verified match and `merge` adds it to `matches.json`.

`python tools/khrecoded.py progress` recompiles every registered function from scratch, so a
match counts only while its source still rebuilds exactly.

## Connected Ghidra analysis

A persistent project imports the function boundaries, ARM/Thumb modes, named
overlay address spaces, cross-references, and reviewed gameplay types. The first
connected investigation follows actor model transparency and related script
commands. See [analysis/README.md](analysis/README.md) for the project, evidence,
shared types, and next leads.

## Scope and future versions

There is one verified ROM profile: `BK9E` revision 0. Japanese, European, and
other revisions require their own ROMs, hashes, and independent extraction and
matching metadata. This project does not guess their profiles. The code targets
within BK9E include ARM9 main, ITCM, DTCM, all 105 overlays, and ARM7.

The proprietary game ROM, assets, and original toolchain are not included.
Contributors must supply their own copy of the game and any required compiler.

## License

The project's original code, tooling, and documentation are available under
the [MIT License](LICENSE), to the extent that contributors hold the relevant
rights. This permits reuse and modification with the copyright and license
notice retained.

This license grants no rights to the original game's ROM, assets, trademarks,
or proprietary SDK and compiler binaries. Third-party material retains its
existing license and copyright notices; importing it does not relicense it.
