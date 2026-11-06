# khrecoded-decomp

EU (`BK9P`) is actively maintained in the shared
[kh-recoded-decomp/kh-recoded-decomp](https://github.com/kh-recoded-decomp/kh-recoded-decomp)
repository alongside US (`BK9E`). This directory preserves the EU history and
attribution; send issues and contributions to the shared repository.

**EU ARM9 matching is complete: 100.00% C + verified library code, with all
108 linked modules byte-identical to the ROM.** Real C accounts for 95.98% of
the code bytes; the separately verified libraries account for 4.02%.
Reconstructed DATA is 100.00%. These figures exclude ARM7 and do not imply
that all semantic names, structures or documentation are complete.

Work now focuses on evidence-based names and interfaces for a future port.
See [the naming evidence](docs/SYMBOL_EVIDENCE.md) and
[the porting guide](docs/PORTING_GUIDE.md). The original DS behavior remains
byte-exact while names and recovered types are improved.
Use the [system index](docs/README.md) and
[source-tree map](docs/SOURCE_LAYOUT.md) to find active implementations and
follow their shared regional bodies.

> ### Disclaimer
> This repository does **NOT** contain the game ROM, any game assets, or any of
> the original binary/assembly. **An existing, legally-obtained copy of the game
> is required** to extract and build it.
>
> This repository is a **matching decompilation only**. It does not contain or
> produce a playable build or any redistributable game binary. All trademarks and
> the original game are property of their respective owners.

## Status

<!-- progress:start -->
| Category | Count | Meaning |
|---|---:|---|
| Real C matched functions | **10,489** / 10,625 (98.7%) | Functions implemented in C and verified byte-exact |
| Real C matched **bytes** | **1,699,782** / 1,771,024 (95.98%) | Original code bytes reproduced by compiled C |
| Assembly matched functions | **0** (0 bytes) | Original SDK, BIOS and DS Protect assembly, verified byte-exact; never counted as C |
| Verified library functions (not C) | **136** (71,242 bytes) | MobiClip, NitroSDK, MSL and DS Protect; verified separately from C |
| C + verified library **bytes** | **1,771,024** / 1,771,024 (**100.00%**) | Combined byte-exact code coverage; library bytes do not increase the C percentage |
| Reconstructed DATA bytes | **223,456** / 223,456 (100.00%) | Verified byte-exact .rodata, .data, .ctor and .bss reconstructed from source |
| Named DATA symbols | **1,842** / 2,331 (79.02%) | Identified DATA names; naming alone does not count as reconstructed DATA |
| Named, not decompiled | **0** | Functions with a known name (SDK, NitroSystem, ...) but no source yet |
| Total known functions | **10,625** | Functions in the dsd symbol tables |
| Region | EU (`BK9P`) |  |
| Compiler | CodeWarrior `mwccarm` 3.0 build 139 | Same toolchain and flags as khdays-decomp |
<!-- progress:end -->

The counts come from `python tools/audit_progress.py`; per-module
progress is in [PROGRESS.md](PROGRESS.md). C and verified library coverage are
reported separately; see [docs/PROGRESS_POLICY.md](docs/PROGRESS_POLICY.md).

The full build links every module and checks it against the ROM: **all 108
modules** (main, ITCM, DTCM and 105 overlays) are byte-identical, and the ROM
packed from them differs from the original only in the 4 header CRC bytes.

## Relationship to khdays-decomp

Re:coded shares the NitroSDK, NitroSystem and MSL libraries, the MobiClip
middleware and part of its engine with *Kingdom Hearts 358/2 Days*, whose
decompilation lives at
[khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp). Both games are
built with the same compiler and flags, so a function whose code is identical
in both ROMs can reuse the Days C directly.
[`tools/port_days.py`](tools/port_days.py) does that mechanically: it compiles
the Days source, checks it against this ROM, remaps every referenced symbol to
the address used here and keeps the file only if `tools/verify_idx.py` reports
a byte-exact match. See [docs/PORTING_FROM_DAYS.md](docs/PORTING_FROM_DAYS.md).

Overlay 104 contains DS Protect 1.28. Its function names and implementation are
cross-checked against the [1.28 branch of taxicat1/dsprot](https://github.com/taxicat1/dsprot/tree/1.28),
which identifies BK9E, BK9J and BK9P as using that version in overlay 104.

## Repository layout

The native build keeps overlay IDs and stable compilation paths. The
[source-tree map](docs/SOURCE_LAYOUT.md) explains the two active DATA layouts,
shared US/EU wrappers, per-file settings and preserved historical sources.
The [system index](docs/README.md) groups the contracts by function, following
the evidence-based organization used as a reference in khdays-decomp.

```text
src/auto/, src/calls/        real C for main/ITCM/DTCM (leaf functions / functions with calls)
src/overlays/ovNNN/...       real C for each overlay
libs/<library>/<module>/...  NitroSDK, NitroSystem, MSL and MobiClip functions
.../asm_stubs/...            original library assembly (never counted as C)
config/                      dsd project config (symbols / delinks / relocs per module)
tools/                       Python tooling (build, verification, porting, reports)
docs/                        project documentation
```

The ROM, the extracted data (`dsd_extract/`), build artifacts and the
proprietary toolchain are intentionally **not** tracked; see `.gitignore`.

## Building / verifying

You need your own copy of the game plus the toolchain (see
[CONTRIBUTING.md](CONTRIBUTING.md) for setup). To verify a single function:

```sh
python tools/getcand.py func_XXXXXXXX        # disassembly, relocations, verify command
python tools/verify_idx.py <file.c> func_XXXXXXXX [--thumb]
```

A green `>>> MATCH <<<` means your C reproduces the original exactly. To check
the whole program:

```sh
bash tools/gate.sh        # configure, compile, link, dsd check modules
bash tools/build_rom.sh   # pack build/recoded.nds and compare with the ROM
```

## Toolchain

- [`dsd`](https://github.com/AetiasHax/ds-decomp) 0.12.1 - DS ROM extraction / delinking
- `mwccarm` 3.0 build 139 (CodeWarrior for Nintendo DS 2.0 SP2p4) - the matching compiler
- `mwldarm` (CodeWarrior 2.0 SP2p4) - the linker
- `arm-none-eabi-as` (GNU binutils) - for the few `.s` runtime sources
- Python 3 with `capstone`, `pyelftools` and `ninja`

See the [Nintendo DS decompilation guide](https://decomp.wiki/platforms/nintendo-ds).

## Contributing

Contributions are welcome; see **[CONTRIBUTING.md](CONTRIBUTING.md)**. Every
matching function must pass byte-exact verification.

## License

Original contributions made specifically to this repository are dedicated to
the public domain under [CC0 1.0](LICENSE). Portions of the C source,
decompilation metadata and tooling were imported or adapted from
[ricky074game/kh-recoded-decomp](https://github.com/ricky074game/kh-recoded-decomp)
and remain available under that project's MIT license. See
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md) for the attribution, scope and
full license text.

These licenses apply only to contributors' own work; the original game and its
assets remain the property of their owners.
