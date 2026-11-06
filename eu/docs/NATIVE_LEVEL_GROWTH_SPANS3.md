# Level-growth table native spans and unresolved attribute columns (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Logical table and native fragments

The level-growth storage is one 1200-byte physical span of 100 twelve-byte rows, partitioned into native symbols of 4,2,1,1 and 1192 bytes. The loader fills only 99 rows; the existing 100-row capacity must remain. A four-byte threshold prefix, first HP-base halfword and remaining table tail can be named from their consumers. The two independently represented attribute bytes remain numeric because independent game-role proof is missing.

LEVEL_GROWTH_TABLE_NATIVE_LAYOUT_AND_COLUMN_AUDIT.json records the source layout and the disagreement: ComputePlayerStats labels output+8 magic and+a defense, whereas Matrix/selection views label+8 defense and+a magic. No damage equation or real label/resource mapping has settled these columns. The first attribute at+6 has consistent strength/attack labels but still lacks independently recorded role evidence; no private typedef is copied as a canonical port header.

## Inventory and evidence

### `main:02060f1c` → `gLevelGrowthTableThresholdPrefix`

Previous label `data_02060f1c`; existing ELF size **4 bytes**. Source: `eu/src/data/bss/Bss_main_02060f1c.c`.

4-byte BSS prefix of the first row in a 1200-byte logical level-growth table with 100 twelve-byte records. The word is the threshold/value column of row 0.

LoadLevelTable loads 99 rows from ba/ch/sp.z and fills each twelve-byte row. GetEntryParam reads row(index+1).value for index < 49 and returns 0xffffffff otherwise. FindLevelForValue and ApplyPendingLevelUps use those words as level thresholds.

Limits: The visible threshold accessor skips row 0. Preserve the first word and the native split; do not shrink the logical table to the subset read by this accessor or assume currency/XP units beyond its actual callers.

Pinned references:

- `eu/src/calls/GetEntryParam.c` → `src/arm9/data_access/GetEntryParam_020500fc.c`; reference line(s) 8, 19.
- `eu/src/calls/LoadLevelTable.c` → `src/arm9/shared_engine/LoadLevelTable_0204f5f4.c`; reference line(s) 21, 32, 33, 34, 35, 36.
- `eu/src/data/bss/Bss_main_02060f1c.c`; reference line(s) 3.

### `main:02060f20` → `gLevelGrowthTableFirstHpBase`

Previous label `data_02060f20`; existing ELF size **2 bytes**. Source: `eu/src/data/bss/Bss_main_02060f20.c`.

2-byte BSS halfword at offset 4 of the first twelve-byte level-growth row.

LoadLevelTable narrows the loaded base word into this column. LoadLevelStats copies the indexed halfword to output+4. ComputePlayerStats combines it with bonus HP, SetupAllSelectionRecords writes the result into selection record 0, and ApplySelectionStatScaling uses record+4 as the HP cap for the preserved current HP at+2.

Limits: This fragment is only the first row HP-base halfword; indexed reads span subsequent rows. The attack/magic/defense byte-column order remains separate and is not fixed by this name.

Pinned references:

- `eu/src/calls/LoadLevelStats.c` → `src/arm9/shared_engine/LoadLevelStats_0204f804.c`; reference line(s) 22, 30, 31, 32, 33.
- `eu/src/data/bss/Bss_main_02060f20.c`; reference line(s) 3.

### `main:02060f24` → `gLevelGrowthTableTail`

Previous label `data_02060f24`; existing ELF size **1192 bytes**. Source: `eu/src/data/bss/Bss_main_02060f24.c`.

1192-byte BSS continuation starting at offset8 of row 0: first row final attribute/padding, followed by 99 complete twelve-byte rows. Together with the preceding 4+2+1+1 bytes it forms 100 physical rows.

LoadLevelTable writes rows 0..98 with twelve-byte stride; LoadLevelStats clamps requested index >= 99 to 98 and reads its HP/three attribute columns. Existing ELF sizes establish the full 100-row physical span ending 020613cc.

Limits: The loader does not fill physical row 99, and the demonstrated readers do not select it. Preserve that row and all padding; no unused-data conclusion or attribute-column meaning is inferred from this tail name.

Pinned references:

- `eu/src/data/bss/Bss_main_02060f24.c`; reference line(s) 3.


## Byte-exact validation

103 DATA identities retain their source paths, native sizes and storage.
405/410 affected official function checks pass; the remaining
5 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 474 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
