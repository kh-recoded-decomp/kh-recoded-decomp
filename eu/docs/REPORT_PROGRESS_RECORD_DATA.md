# Report progress data contracts

The report-top menu (overlay 091) and trophy-report menu (overlay 093) compute progress from packed global fields, selected bit groups and a completion-check table. The names below follow the actual operation and switch selector. They do not assign gameplay meanings to numeric progress IDs. Keep all active source filenames, physical definitions, binding, alignment and values. No new compile or official gate is claimed here.

| Identity | Name | Bytes | Active source |
|---|---|---:|---|
| `data_ov091_020c285c` | `gReportTopProgress4FlagIds` | 20 | `eu/src/overlays/ov091/data/Rodata_ov091_020c285c.c` |
| `data_ov091_020c2848` | `gReportTopProgress17TwoBitFieldOffsets` | 20 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2848.c` |
| `data_ov091_020c2870` | `gReportTopProgress18FlagIds` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c285c.c` |
| `data_ov091_020c28b0` | `gReportTopProgress19FlagIds` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c28b0.c` |
| `data_ov091_020c2910` | `gReportTopProgress20FlagIds` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2910.c` |
| `data_ov091_020c2890` | `gReportTopProgress21FlagIds` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2890.c` |
| `data_ov091_020c2930` | `gReportTopProgress21SevenBitFieldOffsets` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2930.c` |
| `data_ov091_020c28d0` | `gReportTopProgress0FlagRangeStarts` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c28d0.c` |
| `data_ov091_020c28f0` | `gReportTopProgress0FlagRangeLengths` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c28f0.c` |
| `data_ov091_020c2950` | `gReportTopTotalCounterFieldSpecs` | 48 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2930.c` |
| `data_ov091_020c2980` | `gReportTopBooleanProgressFlagIds` | 144 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2930.c` |
| `data_ov091_020c2ad8` | `gReportTopBooleanProgressFieldLimits` | 64 | `eu/src/overlays/ov091/data/Data_ov091_020c2ad8.c` |
| `data_ov091_020c2b5c` | `gReportTopProgressTargets` | 120 | `eu/src/overlays/ov091/data/Data_ov091_020c2ad8.c` |
| `data_ov091_020c2e08` | `gReportTopCompletionChecksHead` | 1784 | `eu/src/overlays/ov091/data/Data_ov091_020c2e08.c` |
| `data_ov091_020c3500` | `gReportTopCompletionChecksTail` | 128 | `eu/src/overlays/ov091/data/Data_ov091_020c3500.c` |
| `data_ov093_020c3c60` | `gTrophyReportProgress4FlagIds` | 20 | `eu/src/ov093/data/Rodata_ov093_020c3c60.c` |
| `data_ov093_020c3c88` | `gTrophyReportProgress17TwoBitFieldOffsets` | 20 | `eu/src/ov093/data/Rodata_ov093_020c3c88.c` |
| `data_ov093_020c3d74` | `gTrophyReportProgress18FlagIds` | 32 | `eu/src/ov093/data/Rodata_ov093_020c3d74.c` |
| `data_ov093_020c3cd4` | `gTrophyReportProgress19FlagIds` | 32 | `eu/src/overlays/ov093/data/tables/gEntryGridBatchBoundaries.c` |
| `data_ov093_020c3cf4` | `gTrophyReportProgress20FlagIds` | 32 | `eu/src/ov093/data/Rodata_ov093_020c3cf4.c` |
| `data_ov093_020c3d54` | `gTrophyReportProgress21FlagIds` | 32 | `eu/src/ov093/data/Rodata_ov093_020c3d54.c` |
| `data_ov093_020c3d94` | `gTrophyReportProgress21SevenBitFieldOffsets` | 32 | `eu/src/ov093/data/Rodata_ov093_020c3d94.c` |
| `data_ov093_020c3d14` | `gTrophyReportProgress0FlagRangeStarts` | 32 | `eu/src/ov093/data/Rodata_ov093_020c3d14.c` |
| `data_ov093_020c3d34` | `gTrophyReportProgress0FlagRangeLengths` | 32 | `eu/src/ov093/data/Rodata_ov093_020c3d34.c` |
| `data_ov093_020c3db4` | `gTrophyReportTotalCounterFieldSpecs` | 48 | `eu/src/ov093/data/Rodata_ov093_020c3d94.c` |
| `data_ov093_020c3de4` | `gTrophyReportBooleanProgressFlagIds` | 144 | `eu/src/ov093/data/Rodata_ov093_020c3d94.c` |
| `data_ov093_020c3fd4` | `gTrophyReportBooleanProgressFieldLimits` | 64 | `eu/src/ov093/data/Data_ov093_020c3fd4.c` |
| `data_ov093_020c40b0` | `gTrophyReportProgressTargets` | 120 | `eu/src/ov093/data/Data_ov093_020c4084.c` |
| `data_ov093_020c45dc` | `gTrophyReportCompletionChecksHead` | 1668 | `eu/src/ov093/data/Data_ov093_020c4128.c` |
| `data_ov093_020c4c60` | `gTrophyReportCompletionChecksTail` | 244 | `eu/src/ov093/data/Data_ov093_020c4c60.c` |

## Direct consumers and selectors

Overlay 091 uses `eu/src/overlays/ov091/calls/UpdateEntryProgress.c`; its completion checks are also read by `eu/src/overlays/ov091/calls/ComputeCompletionPercent.c`. Overlay 093 uses the EU aliases in `eu/src/overlays/ov093/calls/BuildAchievementList.c` with `src/ov093/panel_state/BuildAchievementList_020c0fb0.c`. Apply its `redefine-sym` lines and chained EU mappings; a same-address old token is not necessarily the table at that EU address.

| Suffix in each menu family | Proven operation |
|---|---|
| `Progress4FlagIds` | Five global packed flag IDs; progress ID 4 counts set bits and computes count*100/5. |
| `Progress17TwoBitFieldOffsets` | Five global packed offsets; progress ID 17 sums five 2-bit fields and computes sum*100/15. |
| `Progress18FlagIds` | Eight global packed flag IDs; progress ID 18 counts set bits and computes count*100/8. |
| `Progress19FlagIds` | Eight global packed flag IDs; progress ID 19 counts set bits and computes count*100/8. |
| `Progress20FlagIds` | Eight global packed flag IDs; progress ID 20 counts set bits and computes count*100/8. |
| `Progress21FlagIds` | Eight global packed flag IDs; progress ID 21 tests each flag before reading the corresponding 7-bit field. |
| `Progress21SevenBitFieldOffsets` | Eight packed offsets; progress ID 21 counts fields in inclusive range 0..14 only when the corresponding flag is set, then computes count*100/8. |
| `Progress0FlagRangeStarts` | Eight start bit offsets; progress ID 0 scans each range using the paired lengths, counts set flags and computes count*100/111. |
| `Progress0FlagRangeLengths` | Eight unsigned lengths paired with start bit offsets for progress ID 0. |
| `TotalCounterFieldSpecs` | Six {bitOffset,bitWidth} records. Type-0 total rows 1..5 read the indexed packed counter; row 0 uses its own 40-field sum. |
| `BooleanProgressFlagIds` | 36 global packed bit IDs indexed by the definition id for type-2 boolean progress, subject to special row 13 and optional field limits. |
| `BooleanProgressFieldLimits` | Eight {bitOffset,max} pairs; type-2 rows 28..35 require the 17-bit field to be <= max after the main predicate succeeds. |
| `ProgressTargets` | 30 target values indexed by definition id. Type 1 uses progress>=target, while type 2 uses booleanProgress==target. |
| `CompletionChecksHead` | Begins the 239 logical {kind,value} records used by the progress-ID-5 completion scan. The table continues in the next physical object. |
| `CompletionChecksTail` | Completes the 239 logical {kind,value} records read from the preceding physical object base; not an independent row-definition table. |

`TotalCounterFieldSpecs` is six pairs, although total row 0 does not index its first pair. Its row-0 path sums forty 17-bit fields beginning at bit `0x680` and clamps separately. For type-2 progress, row 13 uses the special field `0x9f0 == 100`; rows 28..35 can additionally be rejected by the per-row 17-bit field limit. Preserve these exceptions. Target tests are `>=` for percentage progress and `==` for boolean progress.

## Completion checks cross physical objects

Both loops process exactly 239 records of two 32-bit words (1912 bytes). Their physical splits differ:

| Overlay | Head | Tail | Logical boundary |
|---|---:|---:|---|
| 091 | 1784 B at `0x020c2e08` | 128 B at `0x020c3500` | Head contains records 0..222; tail contains 223..238. |
| 093 | 1668 B at `0x020c45dc` | 244 B at `0x020c4c60` | Head ends after record 208 kind; tail begins with record 208 value and continues through 238. |

Overlay 091 kind 5 checks whether `value` occurs among up to 32 non-`-1` results of `GetUnlockedSlotValue`. Kind 6 maps values 6/8/10/12/14 to bits `0xbeb`..`0xbef`. Its kinds 0/1/2/3/4/7/8 treat `value` as a packed global flag ID. Overlay 093 uses kinds 1 and 2 for the owned-slot and special-value tests; kinds 0/3/4/5/6/7/8 directly test flags. These kind encodings must stay separate even where logical operations coincide.

The byte-array member names in `ReportUnlockTables` do not define semantic record boundaries. The native extent and loop stride prove the complete table, including its following physical object. Preserve the definitions and adjacency; do not shrink, merge or reclassify tails as padding.

The active source `eu/src/overlays/ov093/data/tables/gEntryGridBatchBoundaries.c` contains the eight flag IDs used by progress ID 19. Its filename is retained for stable source identity; the symbol name follows its proven consumer rather than the legacy filename.

## Reproducing the evidence

Use the consumer paths above with `eu/config/arm9/overlays/ov091/delinks.txt` and `eu/config/arm9/overlays/ov093/delinks.txt` to select the active sources in the identity table. Each existing ELF symbol has the listed physical size, no interior relocations, and bytes matching the corresponding native module range in `eu/dsd_extract/arm9_overlays/ov091.bin` or `ov093.bin`. Bases and code sizes are recorded in `eu/dsd_extract/arm9_overlays/overlays.yaml`. Integration must still run the official project checks.


## Byte-exact validation

98 DATA identities retain their source paths, native sizes and storage.
All 103 affected official function checks pass. A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 180 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
