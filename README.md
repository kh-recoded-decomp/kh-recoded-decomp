# Kingdom Hearts Re:coded decompilation

A matching decompilation of *Kingdom Hearts Re:coded* (Nintendo DS, US `BK9E`).
Every counted function is C that compiles to the original bytes exactly.

## Multi-region merge

One decomp for both regions, merged from [ricky074game/kh-recoded-decomp](https://github.com/ricky074game/kh-recoded-decomp)
(US `BK9E`) and [Yokimitsuro/khrecoded-decomp](https://github.com/Yokimitsuro/khrecoded-decomp) (EU `BK9P`),
maintained by [@ricky074game](https://github.com/ricky074game) and [@Yokimitsuro](https://github.com/Yokimitsuro).

> **No ROM, assets or original binaries are included.** You need your own legally
> obtained copy of the game to build or verify anything.

## Progress

<!-- regions:start -->
| Region | C code bytes | % | Functions |
|---|---:|---:|---:|
| **US** `BK9E` | 1,381,172 / 1,768,220 | **78.1%** | 9,793 / 10,359 |
| **EU** `BK9P` | 1,357,440 / 1,658,216 | **81.9%** | 9,803 / 10,422 |
| US verified original assembly (not C) | 22,618 | 1.3% | 164 |
| **Shared** (same function, matched in both) | 1,305,320 | 78.7% of EU | 9,191 |

8,025 shared functions are stored once in `src/` and built for both regions; 1,166 still have separate EU copies. 602 matched functions are US-only so far and 612 are EU-only. EU numbers come from `eu/tools/audit_progress.py`; per-module EU detail is in [eu/PROGRESS.md](eu/PROGRESS.md).
<!-- regions:end -->

US detail:

| | Matched | Total | % |
|---|---:|---:|---:|
| **ARM9 code (C bytes)** | **1,381,172** | 1,768,220 | **78.1%** |
| ARM9 core + autoloads | 306,356 | 370,004 | 82.8% |
| ARM9 overlays (105) | 1,074,816 | 1,398,216 | 76.9% |
| Functions | 9,793 | 10,359 | 94.5% |
| Data bytes (.rodata/.data/.bss) | 228,100 | 228,140 | 99.98% |

Updated 2026-10-09. Per-module numbers are in [PROGRESS.md](PROGRESS.md).

- Only C that rebuilds byte-for-byte counts as C. Original SDK/MSL assembly that rebuilds byte-for-byte is listed in its own row (`asm_matches.json`) and never added to the C numbers.
- Data counts when the C data objects link byte-exact. Most of it is generated arrays and pointer tables still waiting for real types and names.
- `link` rebuilds all 108 ARM9 modules from objects and packs a ROM identical to the original.
- ARM7 is extracted but not analysed yet, so it is not counted.

## Quick start (Windows)

Python 3.12+.

```powershell
python -m pip install -r requirements.txt
python tools/compile_match.py install
python tools/khrecoded.py setup --rom "C:\path\to\recoded.nds"
python tools/khrecoded.py check --profile full
python tools/khrecoded.py progress
```

Matching a single function:

```powershell
python tools/match_tool.py show ov001 func_ov001_02070e98    # target asm + Ghidra view
python tools/match_tool.py try ov001 func_ov001_02070e98 src/ov001/.../File_02070e98.c
```

| Command | What it does |
|---|---|
| `khrecoded.py progress` | Recompiles every match from scratch and updates PROGRESS.md |
| `khrecoded.py link` | Links C objects + delinked objects into a byte-exact ROM |
| `khrecoded.py check --profile ci` | ROM-free checks (what CI runs) |
| `khrecoded.py check --profile strict` | Everything, including the full linked ROM |

EU (`BK9P`) builds from the same checkout. Shared functions compile from `src/`; EU-only code lives in [`eu/`](eu/):

```powershell
python tools/khrecoded.py eu setup --rom "C:\path\to\recoded_eu.nds"
python tools/khrecoded.py eu gate        # links all 108 EU modules and checks them against the ROM
python tools/khrecoded.py eu progress
```

## Toolchain

- [dsd](https://github.com/AetiasHax/ds-decomp) 0.12.1: extraction and delinking
- CodeWarrior `mwccarm` 4.0 build 1036 and 3.0 build 139, `mwldarm`
- Ghidra for reference decompiles
- [khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp) (CC0): shared engine code from *358/2 Days* is ported where the bytes match

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Every match must pass byte-exact verification.

## License

Original code and tooling: [MIT](LICENSE). The EU code in [`eu/`](eu/) was released under
[CC0](eu/LICENSE) by Yokimitsuro; see [eu/THIRD_PARTY_NOTICES.md](eu/THIRD_PARTY_NOTICES.md) for shared code.
No rights are granted to the game, its assets, trademarks, or the proprietary SDK and compiler.
