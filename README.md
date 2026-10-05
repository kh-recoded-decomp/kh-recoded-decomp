# Kingdom Hearts Re:coded decompilation

A matching decompilation of *Kingdom Hearts Re:coded* (Nintendo DS, US `BK9E`).
Every counted function is C that compiles to the original bytes exactly.

## Multi-region merge

This project is merging with [Yokimitsuro/khrecoded-decomp](https://github.com/Yokimitsuro/khrecoded-decomp)
(EU `BK9P`) into one decomp for both regions: shared `src/`, per-region configs and toolchains.
It started as [ricky074game/kh-recoded-decomp](https://github.com/ricky074game/kh-recoded-decomp) (US),
maintained by [@ricky074game](https://github.com/ricky074game) and [@Yokimitsuro](https://github.com/Yokimitsuro).
EU support is in progress; the numbers below are US.

> **No ROM, assets or original binaries are included.** You need your own legally
> obtained copy of the game to build or verify anything.

## Progress

| | Matched | Total | % |
|---|---:|---:|---:|
| **ARM9 code (C bytes)** | **1,222,994** | 1,768,220 | **69.2%** |
| ARM9 core + autoloads | 296,938 | 370,004 | 80.3% |
| ARM9 overlays (105) | 926,056 | 1,398,216 | 66.2% |
| Functions | 9,603 | 10,359 | 92.7% |
| Data bytes (.rodata/.data/.bss) | 93,751 | 228,140 | 41.1% |

Updated 2026-10-05. Per-module numbers are in [PROGRESS.md](PROGRESS.md).

- Only C that rebuilds byte-for-byte counts. Assembly, SDK binaries and renamed symbols count for nothing.
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

## Toolchain

- [dsd](https://github.com/AetiasHax/ds-decomp) 0.12.1: extraction and delinking
- CodeWarrior `mwccarm` 4.0 build 1036 and 3.0 build 139, `mwldarm`
- Ghidra for reference decompiles
- [khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp) (CC0): shared engine code from *358/2 Days* is ported where the bytes match

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). Every match must pass byte-exact verification.

## License

Original code and tooling: [MIT](LICENSE). No rights are granted to the game, its
assets, trademarks, or the proprietary SDK and compiler.
