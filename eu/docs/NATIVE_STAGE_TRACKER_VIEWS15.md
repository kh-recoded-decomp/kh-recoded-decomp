# Tracker tiles, results-stage data and text/model storage (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

Tracker record+0x10 carries a tile-table ID despite a local priority label. Results labels use wide alpha/beta/gamma marks; the existing resource-set label is corrected to match its real consumer.
Stage records are40 bytes. The original ROM contains135 contiguous records and27 group sentinels from020bf990 through020c0ea7 inclusive. Naming physical slices does not merge them or legalize pointer-shaped relocation expressions inside integer records. The item-triple table feeds item-price-list construction; the local colors label does not describe its role.
Continue model translation belongs to the final row of the model matrix. The text-window work prefix is the start of a larger static owner; following same-address menu aliases remain a separate bank-binding issue.

## Per-symbol inventory

### `ov027:020ba384` → `gTrackerMainTileTableIds`

Previous `data_ov027_020ba384`; **4 bytes**; source `eu/src/ov027/data/Rodata_ov027_020ba384.c`.

4 initialized bytes {8,9,10,11}.

build_and_place_record_sprites selects this byte table when record kind<10, passes the value as CreateTrackerRecord argument8, which stores record+0x10. BlitWidgetToTileTable and ClearWidgetTileArea read that same word as the GetTileTableRow ID.

Limits: The local caller name priority is false. No new range guard is added: this review does not prove arbitrary kinds outside the native table bounds safe.

Evidence sources:

- `eu/src/ov027/data/Rodata_ov027_020ba384.c`; frozen lines 3.
- `eu/src/overlays/ov027/calls/build_and_place_record_sprites.c` → `src/ov027/runtime/build_and_place_record_sprites_020b77c0.c`; frozen lines 5, 13.
- `eu/src/overlays/ov027/calls/CreateTrackerRecord.c` → `src/ov027/overlay_handling/func_ov027_020b7e5c.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov027/calls/BlitWidgetToTileTable.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov027/calls/ClearWidgetTileArea.c`; full frozen body and its hash are in the plan.

### `ov027:020ba388` → `gTrackerSubTileTableIds`

Previous `data_ov027_020ba388`; **4 bytes**; source `eu/src/ov027/data/Rodata_ov027_020ba388.c`.

4 initialized bytes {24,25,26,27}.

For record kind>=10, build_and_place_record_sprites indexes this table by kind-10. The value follows the same CreateTrackerRecord+0x10 to GetTileTableRow path as the main table.

Limits: These are tile-table IDs, not native BG indices, sprite priorities or resource IDs. Preserve the unchecked native indexing.

Evidence sources:

- `eu/src/ov027/data/Rodata_ov027_020ba388.c`; frozen lines 3.
- `eu/src/overlays/ov027/calls/build_and_place_record_sprites.c` → `src/ov027/runtime/build_and_place_record_sprites_020b77c0.c`; frozen lines 4, 12.
- `eu/src/overlays/ov027/calls/CreateTrackerRecord.c` → `src/ov027/overlay_handling/func_ov027_020b7e5c.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov027/calls/BlitWidgetToTileTable.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov027/calls/ClearWidgetTileArea.c`; full frozen body and its hash are in the plan.

### `ov034:020be968` → `gResultsRankMarkBetaText`

Previous `data_ov034_020be968`; **4 bytes**; source `eu/src/ov034/data/Data_ov034_020be968.c`.

4 initialized bytes: wide U+03B2 followed by a zero halfword.

The three-pointer mark table stores this address in slot1. DrawResultsLabelText appends marks[rank-1] with the wide %s%s formatter before drawing. The native bytes are b2 03 00 00.

Limits: Beta names the literal code point, not a guessed mission-grade meaning. Keep the u32 native definition and wide halfword representation.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020be968.c`; frozen lines 5.
- `eu/src/overlays/ov034/data/tables/gResultsScreenResourceSet.c`; frozen lines 4, 9.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; full frozen body and its hash are in the plan.

### `ov034:020be96c` → `gResultsRankMarkAlphaText`

Previous `data_ov034_020be96c`; **4 bytes**; source `eu/src/ov034/data/Data_ov034_020be96c.c`.

4 initialized bytes: wide U+03B1 and zero terminator.

The mark table stores this address in slot0; the positive-rank branch appends it through marks[rank-1]. The native bytes are b1 03 00 00.

Limits: Alpha names the literal character. No bounds validation for rank is introduced and no portable string allocation replaces the native word.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020be96c.c`; frozen lines 5.
- `eu/src/overlays/ov034/data/tables/gResultsScreenResourceSet.c`; frozen lines 3, 8.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; full frozen body and its hash are in the plan.

### `ov034:020be970` → `gResultsRankMarkGammaText`

Previous `data_ov034_020be970`; **4 bytes**; source `eu/src/ov034/data/Data_ov034_020be970.c`.

4 initialized bytes: wide U+03B3 and zero terminator.

The mark table stores this address in slot2; DrawResultsLabelText passes the selected mark to Text_VSNPrintfWide through OS_SNPrintf_0202e094.

Limits: The private const char pointer types do not make this narrow text. Preserve bytes/relocations and avoid assigning a game-grade label solely from the glyph.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020be970.c`; frozen lines 5.
- `eu/src/overlays/ov034/data/tables/gResultsScreenResourceSet.c`; frozen lines 5, 10.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; full frozen body and its hash are in the plan.

### `ov034:020be9f8` → `gResultsStageLayoutPairsPrefix`

Previous `data_ov034_020be9f8`; **2 bytes**; source `eu/src/ov034/data/Data_ov034_020be9f8.c`.

2 initialized bytes: the first mapId halfword of a logical32-entry {u16 mapId,u16 layout} table.

SetupStageParams indexes this base with4-byte stride using the session layoutIndex; mapId comes from+0 and layout from+2. The complete table is128 bytes across this symbol and its126-byte tail.

Limits: Keep the two native objects. The consumer narrows layout into the destination signed byte; this rename does not change its conversions or infer names for layout IDs.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020be9f8.c`; frozen lines 16.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; frozen lines 107, 173, 174.

### `ov034:020be9fa` → `gResultsStageLayoutPairsTail`

Previous `data_ov034_020be9fa`; **126 bytes**; source `eu/src/ov034/data/Data_ov034_020be9f8.c`.

126 initialized bytes: the remainder of the32-entry4-byte layout/map table.

SetupStageParams has a separate decoded literal020be9fa for the layout halfword, matching the second half of gResultsStageLayoutPairsPrefix. Its source expresses both fields through the logical4-byte LayoutEntry view.

Limits: No independent63-entry semantic table exists here. Preserve native u16 storage, bytes, ordering and separate allocation identity.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020be9f8.c`; frozen lines 5.

### `ov034:020bea78` → `gResultsStageItemTriplesPrefix`

Previous `data_ov034_020bea78`; **104 bytes**; source `eu/src/ov034/data/Data_ov034_020bea78.c`.

104 initialized bytes at the start of the three-byte-per-kind item-ID table.

InitResultsScene builds a deduplicated item list from table[stageEntry.kind][0..2] and passes the result to BuildUniqueItemPriceList. SetupStageParams copies the same triple to parameter halfwords+0x1c/+0x1e/+0x20.

Limits: The private destination name colors is false; the items are not proved palette colors. This native104-byte prefix splits a triple and does not by itself define the whole table. The following76-byte physical slice remains outside this plan because its foreign aliases need a separate bank audit.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020bea78.c`; frozen lines 5.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; frozen lines 202, 335, 340.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; frozen lines 108, 211.

### `ov034:020beb2c` → `gResultsStageRewardPairs`

Previous `data_ov034_020beb2c`; **576 bytes**; source `eu/src/ov034/data/Data_ov034_020beae0.c`.

576 initialized bytes:36 rows of four {u16 item,u16 count} pairs.

SetupStageParams indexes by entry.rewardSet and copies four item IDs to parameter bytes+0x70..+0x73 and four counts to halfwords+0x14..+0x1b. The native row stride is16 bytes.

Limits: The source stores these pairs as u32 words; preserve that representation and item narrowing to u8. No item names, reward probabilities or bounds are inferred.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020beae0.c`; frozen lines 5.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; frozen lines 109, 214, 215.

### `ov034:020bf990` → `gResultsStageEntriesPrefix`

Previous `data_ov034_020bf990`; **2 bytes**; source `eu/src/ov034/data/Data_ov034_020bf990.c`.

2 initialized bytes at the start of the logical40-byte stage-entry stream.

SetupStageParams and InitResultsScene walk signed kind/group fields at40-byte stride, count -1 sentinels and select a stage/level entry. ROM from020bf990 to020c0ea8 is exactly135 records and contains27 end-of-group sentinels.

Limits: The native prefix contains only the first kind/padding bytes. Do not resize or convert the entire stream to a new C array in this rename; some current relocation labels inside the table come from coincidental address-shaped values.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020bf990.c`; frozen lines 72.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; frozen lines 201, 318, 335, 340.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; frozen lines 106, 151, 157, 160, 182, 194.

### `ov034:020bf992` → `gResultsStageEntriesInitialTail`

Previous `data_ov034_020bf992`; **782 bytes**; source `eu/src/ov034/data/Data_ov034_020bf990.c`.

782 initialized bytes at logical stage-stream offsets2..783.

SetupStageParams uses an additional literal020bf992 for the first values halfword. This slice continues the40-byte record stream beginning at020bf990, crossing record boundaries without introducing a new logical table.

Limits: Preserve the packed pointer-shaped native fields and relocations. The known stream continues through later native DATA objects; a fragment boundary is not a record boundary.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020bf990.c`; frozen lines 13.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; full frozen body and its hash are in the plan.

### `ov034:020bfda5` → `gResultsStageEntriesMiddleTail`

Previous `data_ov034_020bfda5`; **1991 bytes**; source `eu/src/ov034/data/Data_ov034_020bfca0.c`.

1991 initialized bytes, logical stream offsets0x415..0xbdb.

This physical slice lies inside the same135-record40-byte stream proved by SetupStageParams and all27 ROM group sentinels. Its start splits record26; the slice ends inside record75.

Limits: A raw same-address|1 word in ov016 is a foreign-bank reference, not evidence that these1991 bytes are executable or belong to ov016. Keep native packed relocation expressions. The immediately preceding261-byte physical slice and following2364-byte existing allocation are not renamed by this candidate.

Evidence sources:

- `eu/src/ov034/data/Data_ov034_020bfca0.c`; frozen lines 38.
- `eu/src/overlays/ov034/calls/SetupStageParams.c` → `src/ov034/unclassified_helpers/SetupStageParams_020bdf10.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; full frozen body and its hash are in the plan.

### `ov037:020bb650` → `gContinueModelInitialTranslation`

Previous `data_ov037_020bb650`; **12 bytes**; source `eu/src/ov037/data/Rodata_ov037_020bb648.c`.

12 RO bytes: VecFx32 {0,-0x300,0}.

LoadMenuModelResources copies this triple into context+0x114, which is model+0xa4 because model starts+0x70. SceneNode_Draw places MtxFx43 at model+0x80, so +0xa4/+0xa8/+0xac are its final translation row; it submits the matrix to G3 or copies it to the global base transform.

Limits: The private field name cameraOffset is false. This is the model matrix translation, not camera position or the following model scale vector at+0xb0. Preserve Q12 values and original u32[3] storage.

Evidence sources:

- `eu/src/ov037/data/Rodata_ov037_020bb648.c`; frozen lines 7.
- `eu/src/overlays/ov037/calls/LoadMenuModelResources.c` → `src/ov037/unclassified_helpers/LoadMenuModelResources_020bafbc.c`; frozen lines 13, 25.
- `eu/src/calls/SceneNode_Draw.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov037/calls/UpdateMenuSelection.c` → `src/ov037/unclassified_helpers/UpdateMenuSelection_020bb4bc.c`; full frozen body and its hash are in the plan.

### `ov036:020c3950` → `gTextWindowStaticWorkPrefix`

Previous `data_ov036_020c3950`; **1732 bytes**; source `eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c`.

1732 BSS bytes at the beginning of the logical0x68b4-byte text-window work area.

gTextWindowResourceTable is initialized to020c3950. The text-window task constructor clears0x68b4 bytes from that pointer, then initializes text-window state at offsets0x6458,0x64fc,0x682c and0x68a0. The full owner ends at020ca204.

Limits: The native1732-byte prefix is not the whole work allocation. Eight following physical BSS fragments share this logical owner but retain foreign same-RAM alias issues and are documented separately. Do not merge or resize any of them.

Evidence sources:

- `eu/src/overlays/ov036/data/bss/Bss_ov036_020c394c.c`; frozen lines 3.
- `eu/src/overlays/ov036/data/tables/gTextWindowResourceTable.c`; frozen lines 3, 6.
- `eu/src/overlays/ov036/calls/InitTextWindowTask.c`; full frozen body and its hash are in the plan.

### `ov034:020be974` → `gResultsRankMarkTexts`

Previous `gResultsScreenResourceSet`; **12 bytes**; source `eu/src/overlays/ov034/data/tables/gResultsScreenResourceSet.c`.

12 initialized bytes: three borrowed pointers to the wide alpha, beta and gamma marks, in that order.

DrawResultsLabelText exposes RankMarks marks[3], selects marks[rank-1] for positive rank and appends it using the wide %s%s formatter. Each target is a one-character UTF16 string, not a resource descriptor.

Limits: This corrects an existing descriptive name; it is outside the370 numeric baseline. Preserve the three native pointer relocations, lookup and lack of rank bounds checks.

Evidence sources:

- `eu/src/overlays/ov034/data/tables/gResultsScreenResourceSet.c`; full frozen body and its hash are in the plan.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; full frozen body and its hash are in the plan.


## Byte-exact validation

75 DATA identities retain their source paths, native sizes and storage.
141/144 affected official function checks pass; the remaining
3 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 199 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
