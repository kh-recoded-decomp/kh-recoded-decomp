# EU title and panel data contracts

These names identify the data copied or indexed by the EU title and panel code. All original storage widths, values, padding, section placement and pointer relocations remain part of the native contract. Screen-resource tables, widget IDs, message IDs, category IDs and packed record offsets are different domains even where their integer values overlap.

## Identity and source map

| EU identity | Name | Storage | Definition |
| --- | --- | --- | --- |
| ov000 `0x02063798` | `gTitleBlankPaletteColor` | 4 bytes (rodata) | `src/ov000/data/Rodata_ov000_02063798.c` |
| ov000 `0x0206379c` | `gTitleCursorLayerPairTemplate` | 8 bytes (rodata) | `src/ov000/data/Rodata_ov000_02063798.c` |
| ov000 `0x020637a4` | `gTitleNoticeTextFrame` | 16 bytes (rodata) | `src/ov000/data/Rodata_ov000_02063798.c` |
| ov000 `0x020637b4` | `gTitlePanelLayerSourceIds` | 16 bytes (rodata) | `src/ov000/data/Rodata_ov000_020637b4.c` |
| ov000 `0x020637c4` | `gTitlePanelLayerManagerConfig` | 16 bytes (rodata) | `src/ov000/data/Rodata_ov000_020637c4.c` |
| ov000 `0x020637d4` | `gTitlePanelBgArchiveIndices` | 80 bytes (rodata) | `src/ov000/data/Rodata_ov000_020637c4.c` |
| ov000 `0x02063870` | `gTitleScreenTaskClass` | 20 bytes (data) | `src/ov000/data/Data_ov000_02063860.c` |
| ov000 `0x02063a00` | `gTitleNoticeBackgroundColor` | 4 bytes (bss) | `src/overlays/ov000/data/bss/Bss_ov000_02063a00.c` |
| ov002 `0x0206ac94` | `gOv002MenuLabelMessageIds` | 16 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ac94.c` |
| ov002 `0x0206aca4` | `gOv002MenuModeMessageIds` | 16 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206aca4.c` |
| ov002 `0x0206acb4` | `gOv002MenuLabelWidgetIds` | 16 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206acb4.c` |
| ov002 `0x0206acc4` | `gOv002MenuMainBgConfig` | 20 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206acb4.c` |
| ov002 `0x0206acd8` | `gOv002MenuSubBgConfig` | 20 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206acd8.c` |
| ov002 `0x0206acec` | `gOv002MenuMainObjConfig` | 24 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206acd8.c` |
| ov002 `0x0206ad04` | `gOv002MenuSubObjConfig` | 24 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ad04.c` |
| ov002 `0x0206ad1c` | `gOv002MenuTopRowsFrameScreenIds` | 32 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ad04.c` |
| ov002 `0x0206ad3c` | `gOv002MenuBodyFrameScreenIds` | 32 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ad3c.c` |
| ov002 `0x0206ad5c` | `gOv002MenuNextBgFrame` | 32 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ad5c.c` |
| ov002 `0x0206ad7c` | `gMenuCharacterHighByteMap` | 16 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ad7c.c` |
| ov002 `0x0206ad8c` | `gMenuRecordCategoryTallyGroups` | 20 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ad7c.c` |
| ov002 `0x0206adde` | `gMenuCategory12VariantFilter` | 46 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206adde.c` |
| ov002 `0x0206ae0c` | `gMenuPreferredItemOrder` | 24 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ae0c.c` |
| ov002 `0x0206ae24` | `gMenuRandomRecordExclusions` | 76 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ae0c.c` |
| ov002 `0x0206ae70` | `gMenuRandomFillCategoryOrder` | 76 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ae70.c` |
| ov002 `0x0206aebc` | `gMenuRecordCategoryBaseOffsets` | 80 bytes (rodata) | `src/ov002/data/Rodata_ov002_0206ae70.c` |
| ov002 `0x0206af0c` | `gMenuDefaultCategoryRecordIds` | 80 bytes (rodata) | `src/overlays/ov002/data/tables/RecordCategoryIconTables.c` |
| ov013 `0x02074a08` | `gOv013MenuMainBgConfig` | 20 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a08.c` |
| ov013 `0x02074a1c` | `gOv013PanelSubBgConfig` | 20 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a1c.c` |
| ov013 `0x02074a30` | `gOv013RecordMainBgConfig` | 20 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a30.c` |
| ov013 `0x02074a44` | `gOv013RecordMainObjConfig` | 24 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a30.c` |
| ov013 `0x02074a5c` | `gOv013MenuMainObjConfig` | 24 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a5c.c` |
| ov013 `0x02074a8c` | `gOv013PanelSubObjConfig` | 24 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a8c.c` |
| ov013 `0x02074aa4` | `gOv013PageHeaderScreenIds` | 32 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074a8c.c` |
| ov013 `0x02074ac4` | `gOv013PageBodyScreenIds` | 32 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074ac4.c` |
| ov013 `0x02074ae4` | `gOv013NextPageBgFrame` | 32 bytes (rodata) | `src/ov013/data/Rodata_ov013_02074ae4.c` |
| ov014 `0x0206f800` | `gRecordPanelProgressGroupTotals` | 8 bytes (rodata) | `src/overlays/ov014/data/tables/PanelCategoryTables.c` |
| ov014 `0x0206f86c` | `gRecordPanelMainBgConfig` | 20 bytes (rodata) | `src/ov014/data/Rodata_ov014_0206f860.c` |
| ov014 `0x0206f880` | `gRecordPanelSubBgConfig` | 20 bytes (rodata) | `src/ov014/data/Rodata_ov014_0206f880.c` |
| ov014 `0x0206f894` | `gRecordPanelMainObjConfig` | 24 bytes (rodata) | `src/ov014/data/Rodata_ov014_0206f880.c` |
| ov014 `0x0206f8ac` | `gRecordPanelSubObjConfig` | 24 bytes (rodata) | `src/ov014/data/Rodata_ov014_0206f8ac.c` |

## Consumers and boundaries

### `gTitleBlankPaletteColor`

A zero-initialized palette colour template. FinishTitlePanel loads exactly its first two bytes into palette offset 0 on both main and sub engines.

Physical storage is one u32; only the first RGB555 u16 is consumed here. It is distinct from the BSS colour used by ShowTitleNotice.

Evidence: `src/overlays/ov000/calls/FinishTitlePanel.c`.

### `gTitleCursorLayerPairTemplate`

Two-word template copied by HighlightPanelCursorLayer. Word 0 is 0x8000; word 1 is replaced by cursorIndex * 0x14000 + 0x68000 before IndexedRecord_SetPair applies it to the back layer.

The pair operation and owning title cursor are proved; the private field names offset/size do not independently establish units or geometric meaning.

Evidence: `src/overlays/ov000/calls/HighlightPanelCursorLayer.c`.

### `gTitleNoticeTextFrame`

Eight-u16 text-frame template copied by ShowTitleNotice and passed to InitTextLayerDefault for BG3. Values are {1,0,30,21,1,13,0,6}.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov000/calls/ShowTitleNotice.c`.

### `gTitlePanelLayerSourceIds`

Four source IDs {0,1,2,3} copied by InitPanelLayers and passed in order when creating the four selectable title panel layers.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov000/calls/InitPanelLayers.c`.

### `gTitlePanelLayerManagerConfig`

Four-word title layer-manager initialization template. InitPanelLayers replaces its header with the main resource key before passing the local copy to InitObjManager.

The layer-manager owner is proved by use; no names are invented for the remaining configuration words.

Evidence: `src/overlays/ov000/calls/InitPanelLayers.c`.

### `gTitlePanelBgArchiveIndices`

Five four-s32 rows: main screen/character index, sub screen/character index, main palette index and sub palette index. LoadPanelBgGraphics iterates all five and passes them to GetBgDataFromArchive.

-1 entries are preserved and passed through. Some resulting screen palettes are subsequently borrowed from row 0; the table does not own loaded buffers.

Evidence: `src/overlays/ov000/calls/LoadPanelBgGraphics.c`.

### `gTitleScreenTaskClass`

Five-word task descriptor containing flags 0x00110008, InitTitleScreen, TeardownCurrentHeap, work size 0x66ec and a NULL final word.

This name identifies the constructor/destructor and declared work size; no further meaning is assigned to the packed flags or final word.

Evidence: `src/overlays/ov000/calls/InitTitleScreen.c`.

### `gTitleNoticeBackgroundColor`

Zero BSS storage used by ShowTitleNotice as the source of a two-byte load at main BG palette offset 0.

Physical storage is four bytes; only one u16 colour is read by this caller. It has static lifetime and no heap owner.

Evidence: `src/overlays/ov000/calls/ShowTitleNotice.c`.

### `gOv002MenuLabelMessageIds`

Four message IDs {12,13,14,15} drawn by DrawMenuLabels next to the four menu widgets. Message 13 has a highlight-dependent colour.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/DrawMenuLabels.c`.

### `gOv002MenuModeMessageIds`

Four selected-mode message IDs {16,17,18,19}. DrawMenuLabels indexes the table with the selected menu index for the bottom caption.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/DrawMenuLabels.c`.

### `gOv002MenuLabelWidgetIds`

Four widget IDs {1,2,3,4}. DrawMenuLabels resolves each widget position before drawing its corresponding label.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/DrawMenuLabels.c`.

### `gOv002MenuMainBgConfig`

Five-word background-container configuration copied by InitMenuContext and applied to mainBg with InitBackgroundContainer. Its two callback words are preserved.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/InitMenuContext.c`.

### `gOv002MenuSubBgConfig`

Five-word background-container configuration copied by InitMenuContext and applied to subBg with InitBackgroundContainer. Its two callback words are preserved.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/InitMenuContext.c`.

### `gOv002MenuMainObjConfig`

Six-word main object-resource template. InitMenuContext replaces the cell/animation keys from its message resource, initializes mainObj and loads 0x14 widget descriptors.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/InitMenuContext.c`.

### `gOv002MenuSubObjConfig`

Six-word sub-screen object-resource template. InitMenuContext replaces the resource keys before initializing the sub-screen widget container.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/InitMenuContext.c`.

### `gOv002MenuTopRowsFrameScreenIds`

Eight screen-entry IDs {20..27}. AnimateMenuBgFrames selects one by frame and copies two 12-tile rows to sub BG1 offsets beginning at 0x28.

The table selects the two-row top region, whereas the other frame table selects a seven-row body. Both use frame indices 0..7.

Evidence: `src/overlays/ov002/calls/AnimateMenuBgFrames.c`.

### `gOv002MenuBodyFrameScreenIds`

Eight screen-entry IDs {10..17}. AnimateMenuBgFrames selects one by frame and copies seven 12-tile rows to sub BG1 rows 13..19.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/AnimateMenuBgFrames.c`.

### `gOv002MenuNextBgFrame`

Eight next-frame indices {1,2,3,4,5,6,7,0}. AnimateMenuBgFrames advances the frame through this cycle when its delay reaches zero, then sets delay to 2.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov002/calls/AnimateMenuBgFrames.c`.

### `gMenuCharacterHighByteMap`

Byte map used to replace the high byte of a character code while preserving its low byte. UnmapCharHighByte searches the first 13 entries for the inverse map.

Physical definition is four u32 words (16 bytes), but consumers read bytes. Thirteen entries are searched; remapping itself has no new bounds check. No character-encoding standard is inferred.

Evidence: `src/overlays/ov002/calls/RemapCharHighByte.c`, `src/overlays/ov002/calls/UnmapCharHighByte.c`.

### `gMenuRecordCategoryTallyGroups`

Packed signed-byte mapping from record categories to the four progress tally groups. TallyFlagGroups counts set record bits between category boundaries and adds each subtotal to the mapped output group.

Physical definition is five u32 words; the live interpretation is bytes. The category-18 skip and 0xff table value remain literal behavior; no nonexistent fifth output is invented.

Evidence: `src/overlays/ov002/calls/TallyFlagGroups.c`.

### `gMenuCategory12VariantFilter`

Packed byte filter applied only to category 12 when BuildSelectionViewRecords flag2 is set. A nonzero byte at recordId % 10000 suppresses that variant.

Physical definition is 23 u16 words (46 bytes), not 23 boolean entries. The record-domain validity comes from callers/assets; this block adds no range guard or gameplay label.

Evidence: `src/overlays/ov002/calls/BuildSelectionViewRecords.c`.

### `gMenuPreferredItemOrder`

Six-s32 initial permutation {1,0,2,3,5,4}. RankPreferredItems copies it to the output, uses it to map item IDs into counts, then stably sorts the output by descending observed counts.

Counts are derived from flagged table-B records; this does not establish a new item taxonomy. The existing record-slot acquisition/release sequence is unchanged.

Evidence: `src/overlays/ov002/calls/RankPreferredItems.c`.

### `gMenuRandomRecordExclusions`

Nineteen s32 record IDs rejected by IsMenuRecordAllowedByRandomFilter; all other IDs return true.

This is an exclusion list for that filter, not a complete list of invalid or unavailable records.

Evidence: `src/overlays/ov002/calls/IsMenuRecordAllowedByRandomFilter.c`.

### `gMenuRandomFillCategoryOrder`

Nineteen category selectors traversed by FillCategoryRecords when no preset is supplied. The caller applies per-position/category random gates before selecting available records.

The order is significant: gates refer to indices 8 and 18 as well as category values. Do not sort it or equate table index with category ID.

Evidence: `src/overlays/ov002/calls/FillCategoryRecords.c`.

### `gMenuRecordCategoryBaseOffsets`

Twenty signed base offsets used by LookupTableOffset and category record/flag operations. LookupTableOffset adds the supplied offset except for -1, and maps input category indices >=20 to index 16.

The -1 sentinel and caller-specific boundary handling must be preserved. The name describes table-offset arithmetic, not a newly inferred resource type.

Evidence: `src/overlays/ov002/calls/LookupTableOffset.c`, `src/overlays/ov002/calls/ApplyRecordsToPackedFields.c`, `src/overlays/ov002/calls/GetRecordFlagState.c`.

### `gMenuDefaultCategoryRecordIds`

Twenty default category record IDs copied into SelectionView.recordIds when no selection is attached. ResetSelectionView otherwise resolves IDs from the supplied selection.

Zero entries are retained as actual table values; the 22-slot view has only its first 20 IDs filled by this default table.

Evidence: `src/overlays/ov002/calls/ResetSelectionView.c`.

### `gOv013MenuMainBgConfig`

Five-word configuration copied by InitMenuScreenGraphics into the main background container for the wxc/wla resource.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/InitMenuScreenGraphics.c`.

### `gOv013PanelSubBgConfig`

Five-word configuration copied by InitPanelSubScreenGraphics into the sub background container.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/InitPanelSubScreenGraphics.c`.

### `gOv013RecordMainBgConfig`

Five-word configuration copied by InitRecordScreenGraphics into the main background container for the record/player-card view.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/InitRecordScreenGraphics.c`.

### `gOv013RecordMainObjConfig`

Six-word object template copied by InitRecordScreenGraphics. It substitutes cell/animation resource keys, initializes mainObj and loads 13 widget descriptors.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/InitRecordScreenGraphics.c`.

### `gOv013MenuMainObjConfig`

Six-word object template copied by InitMenuScreenGraphics. It substitutes cell/animation resource keys, initializes mainObj and loads 25 widget descriptors.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/InitMenuScreenGraphics.c`.

### `gOv013PanelSubObjConfig`

Six-word object template copied by InitPanelSubScreenGraphics. It substitutes cell/animation resource keys, initializes subObj and loads 92 widget descriptors.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/InitPanelSubScreenGraphics.c`.

### `gOv013PageHeaderScreenIds`

Eight screen-entry IDs {20..27}. AnimatePanelPageScreens selects one by page and copies two seven-tile rows into main BG1 offsets 0x1a and 0x5a.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/AnimatePanelPageScreens.c`.

### `gOv013PageBodyScreenIds`

Eight screen-entry IDs {10..17}. AnimatePanelPageScreens copies ten 12-tile rows from the selected entry into main BG1 rows 6..15.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/AnimatePanelPageScreens.c`.

### `gOv013NextPageBgFrame`

Eight next-page indices {1,2,3,4,5,6,7,0}. AnimatePanelPageScreens advances the page through the cycle when delay is zero, then sets delay to 2.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov013/calls/AnimatePanelPageScreens.c`.

### `gRecordPanelProgressGroupTotals`

Four u16 denominators {207,308,283,110}. InitRecordPanel divides the four tallied record groups by these values when producing percentage widgets.

These are progress-group totals used as denominators, not category entry counts. The fourth group may include the separately accumulated bonusCount before division.

Evidence: `src/overlays/ov014/calls/InitRecordPanel.c`, `src/overlays/ov002/calls/TallyFlagGroups.c`.

### `gRecordPanelMainBgConfig`

Five-word configuration copied by InitRecordPanel into bgMain and passed to InitBackgroundContainer.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov014/calls/InitRecordPanel.c`.

### `gRecordPanelSubBgConfig`

Five-word configuration copied by InitRecordPanel into bgSub. The last two words hold BindPanelEntryScreen and QueryPanelEntry callbacks.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov014/calls/InitRecordPanel.c`.

### `gRecordPanelMainObjConfig`

Six-word object template copied by InitRecordPanel. It substitutes cell/animation resource keys, initializes objMain and loads 20 widget descriptors.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov014/calls/InitRecordPanel.c`.

### `gRecordPanelSubObjConfig`

Six-word object template copied by InitRecordPanel. It substitutes cell/animation resource keys, initializes objSub and loads eight widget descriptors.

Static source data is copied or borrowed by the consumer; changing a local copy does not mutate this template. Existing storage type, padding and values must remain unchanged.

Evidence: `src/overlays/ov014/calls/InitRecordPanel.c`.

## Existing aliases

Two numeric aliases already have descriptive names at the same configured address: `data_ov013_020749f4` aliases `gRecordSelectionBgConfig`, and `data_ov013_02074a74` aliases `gRecordSelectionObjConfig`. Their active definitions already use the descriptive names. They are not additional unknown owners; preserve any alias required by existing references until link/relocation validation supports removing it.

## Porting notes

The configuration templates are copied locally before resource IDs are substituted. A port should retain that distinction so changing a local resource key cannot mutate a shared template. Tables consumed as bytes must not be indexed using their historical u32/u16 declaration element size. In particular, the character high-byte map has 13 inverse-search entries in 16 bytes, the category tally mapping is byte-packed in 20 bytes, and the category-12 variant filter occupies 46 bytes.

The two eight-frame animations use separate identity spaces and different engines/rectangles: ov002 writes sub BG1, and ov013 writes main BG1. Their similar literal cycles do not authorize sharing mutable frame state or merging resource tables.


## Byte-exact validation

65 DATA identities retain their source paths, native sizes and storage.
51/52 affected official function checks pass; the remaining
1 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 102 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
