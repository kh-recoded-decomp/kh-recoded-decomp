# Report, page-menu and gauge DATA

These 19 objects are named from active task creation, page-menu line rendering and item/enemy/theater report consumers. Names preserve the exact physical records and string fragments. Stored constants, global mutations, code pointers and pointer/addend relationships are unchanged.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Physical bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov045:20c0820 | `data_ov045_020c0820` | `gBattleGaugeTaskDescriptor` | 20 | `eu/src/ov045/data/Data_ov045_020c0820.c` | `eu/src/overlays/ov001/calls/OpenResultScreen.c` |
| ov078:20c5024 | `data_ov078_020c5024` | `gPageMenuLineLayoutPrefix` | 256 | `eu/src/ov078/data/Data_ov078_020c4fe0.c` | `eu/src/overlays/ov078/calls/InitPageMenu.c` |
| ov078:20c5124 | `data_ov078_020c5124` | `gPageMenuLineLayoutTail` | 68 | `eu/src/ov078/data/Data_ov078_020c5124.c` | `eu/src/overlays/ov078/calls/DrawPageHeader.c` |
| ov095:20c1714 | `data_ov095_020c1714` | `gItemReportTabTileRows` | 8 | `eu/src/overlays/ov095/data/Rodata_ov095_020c1714.c` | `eu/src/overlays/ov095/calls/LoadMenuBackgrounds_020bf570.c` |
| ov095:20c1728 | `data_ov095_020c1728` | `gItemReportPanelTileRows` | 28 | `eu/src/overlays/ov095/data/Rodata_ov095_020c1728.c` | `eu/src/overlays/ov095/calls/LoadMenuBackgrounds_020bf570.c` |
| ov095:20c1744 | `data_ov095_020c1744` | `gItemReportGroupGridRowStarts` | 36 | `eu/src/overlays/ov095/data/Rodata_ov095_020c1744.c` | `eu/src/overlays/ov095/calls/InitGridMenu.c` |
| ov099:20c2274 | `data_ov099_020c2274` | `gEnemyViewerOrientationCorrectionQuat` | 16 | `eu/src/ov099/data/Rodata_ov099_020c2274.c` | `eu/src/overlays/ov099/calls/ApplyQuaternionCorrectionToMatrix_020c185c.c` |
| ov099:20c22b4 | `data_ov099_020c22b4` | `gEnemyViewerScrollListConfig` | 44 | `eu/src/ov099/data/Data_ov099_020c22b4.c` | `eu/src/overlays/ov099/calls/InitEnemyViewerScreen.c` |
| ov099:20c2344 | `data_ov099_020c2344` | `gEnemyReportDetailTextPathHead` | 28 | `eu/src/ov099/data/Data_ov099_020c2344.c` | `eu/src/overlays/ov099/calls/InitViewerTextLayers.c` |
| ov099:20c23ac | `data_ov099_020c23ac` | `gEnemyViewerSlotBank1Layouts` | 144 | `eu/src/ov099/data/Data_ov099_020c23ac.c` | `eu/src/overlays/ov099/calls/CreateViewerSlotObjs.c` |
| ov099:20c257c | `data_ov099_020c257c` | `gEnemyViewerSlotBank0Layouts` | 504 | `eu/src/ov099/data/Data_ov099_020c23ac.c` | `eu/src/overlays/ov099/calls/CreateViewerSlotObjs.c` |
| ov099:20c27a4 | `data_ov099_020c27a4` | `gEnemyReportRatePairFormatStyle2` | 36 | `eu/src/ov099/data/Data_ov099_020c279c.c` | `eu/src/overlays/ov099/calls/DrawEntryStatsPanels.c` |
| ov099:20c27c8 | `data_ov099_020c27c8` | `gEnemyReportRatePairFormatDefault` | 36 | `eu/src/ov099/data/Data_ov099_020c27c8.c` | `eu/src/overlays/ov099/calls/DrawEntryStatsPanels.c` |
| ov099:20c27ec | `data_ov099_020c27ec` | `gEnemyViewerModeScales` | 160 | `eu/src/ov099/data/Data_ov099_020c27c8.c` | `eu/src/overlays/ov099/calls/ApplyViewerModelPose.c` |
| ov103:20c049c | `data_ov103_020c049c` | `gTheaterReportStateHandlers` | 16 | `eu/src/ov103/data/Rodata_ov103_020c049c.c` | `eu/src/overlays/ov103/calls/RunSceneStateHandler.c` |
| ov103:20c04d4 | `data_ov103_020c04d4` | `gTheaterReportBackgroundFileIndices` | 44 | `eu/src/ov103/data/Data_ov103_020c04d4.c` | `eu/src/overlays/ov103/calls/LoadEntryBackground_020bf0c4.c` |
| ov103:20c0500 | `data_ov103_020c0500` | `gTheaterReportListConfig` | 44 | `eu/src/ov103/data/Data_ov103_020c0500.c` | `eu/src/overlays/ov103/calls/InitTheaterReportScreen.c` |
| ov103:20c055c | `data_ov103_020c055c` | `gTheaterReportTextPathHead` | 16 | `eu/src/ov103/data/Data_ov103_020c055c.c` | `eu/src/overlays/ov103/calls/InitTextLayers_020bf1bc.c` |
| ov103:20c0608 | `data_ov103_020c0608` | `gTheaterReportSlotLayouts` | 240 | `eu/src/ov103/data/Data_ov103_020c05c4.c` | `eu/src/overlays/ov103/calls/CreateTheaterReportSlotEntries.c` |

## Task and state-handler descriptors

OpenResultScreen and OpenFieldSubScreenLayer load overlay 45 before passing gBattleGaugeTaskDescriptor to CreateTaskObject. Its five words retain the packed header, InitBattleGaugeContext pointer, ShutdownScene pointer, work size 0x1a4c and final NULL. No constructor ownership or callback ABI is inferred solely from the data-file extern declarations.

The theater report state table contains four code pointers. RunSceneStateHandler selects by phase and invokes a nonnull handler with scene. Presence of the state 0 callback differs from a null table slot. These DATA names do not infer a logical return contract from a legacy void declaration or convert residual r0 into BOOL. Code-pointer Thumb/ARM state and all relocation addends are preserved.

## One line-layout view across two physical objects

The page-menu renderer uses nine 36-byte layout records beginning at 020c5024. The drawing view supplies charBase, tileX/tileY, width/height, textX/textY, color and flags. Initialization computes character-base starts by accumulation; DrawPageHeader changes width fields for lines 7/8 to 4 for one drawing path and restores 2 afterward.

| Physical object | Native range | Logical portion |
|---|---|---|
| gPageMenuLineLayoutPrefix | [020c5024,020c5124), 256 B | records 0..6 plus first word of record 7 |
| gPageMenuLineLayoutTail | [020c5124,020c5168), 68 B | remaining eight words of record 7 plus complete record 8 |

The tail is not an independent complete HeaderStyle. Its old partial view reaches the two width fields of the same line table. Preserve direct global mutations, physical boundaries and the 36-byte stride. Do not move these templates into immutable/shared storage or change the temporary width updates as part of naming.

## Item-report row coordinates

Two tab-screen row offsets and seven panel-screen row offsets select the existing background rectangle-copy rows. They are not resource IDs. The nine group row starts are added to i/13 when registering grid cells, whereas pixelY uses a separate base and row*16. These grid indices remain distinct from pixel coordinates and per-group item counts.

## Viewer layouts, scale and formats

Enemy viewer bank 1 uses six 24-byte slot layouts and bank 0 uses 21. The same records provide x/y scroll baselines for thumbs and ticks. Bank values are actual CreateSlotObj arguments, without assigning main/sub display ownership. The theater report has its own twelve 20-byte layouts; its stride 0x14 must not be replaced by the enemy viewer's24-byte type.

The correction quaternion is multiplied with the normalized rotation quaternion before matrix reconstruction and scaling. No unproved axis/angle/handedness label is assigned to its values. The forty mode-scale values are applied to all three scale axes; no named enemy mapping is inferred for mode indices.

The two tagged UTF-16 rate-pair formats preserve every control unit, percent token, parenthesis and stored trailing zero. The branch selecting style 2 is documented numerically; no human-language name is assigned. The control unit before the parenthesis differs in the other branch, so equal visible punctuation does not authorize merging or normalizing the strings.

## Paths split across original string objects

| Full path consumed by text loader | Head object | Following original tail | Pointer-table relationship |
|---|---|---|---|
| ui/report/text/&/enemy_detail.s.z | gEnemyReportDetailTextPathHead, 28 B at 020c2344 | sOv099_LSZ_020c2360, 8 B containing l.s.z and zeros | gEnemyReportTextPaths[1] points to head |
| ui/report/text/&/theater.s.z | gTheaterReportTextPathHead, 16 B at 020c055c | sOv103_TheaterSZ_020c056c, 16 B containing /theater.s.z and zeros | gTheaterReportTextPaths[0] points to head |

Neither head is NUL-terminated. The loader receives the head address and reads through the adjacent original tail. Keep adjacency, capacities and the existing pointer tables. Naming the head does not make it an independently complete C string or authorize deduplicating the common prefix.

## Per-object evidence and limits

### `gBattleGaugeTaskDescriptor`

20-byte descriptor selects gauge init/shutdown and work size 0x1a4c.

Evidence: `eu/src/overlays/ov001/calls/OpenResultScreen.c`. Preserve the packed header, fifth NULL word and callback ABI; no thread/ownership fields are invented.

### `gPageMenuLineLayoutPrefix`

Begins nine 36-byte line records; initializer accumulates char-base offsets and drawing uses geometry/text fields.

Evidence: `eu/src/overlays/ov078/calls/InitPageMenu.c`. Physical 256 B ends after record 7 first word; remaining 68 B are in the next physical object.

The EU wrapper selects `src/ov078/unclassified_helpers/InitPageMenu_020c4260.c`.

### `gPageMenuLineLayoutTail`

Contains last eight words of line 7 and complete line 8; header drawing temporarily changes the stored width fields.

Evidence: `eu/src/overlays/ov078/calls/DrawPageHeader.c`. Not a separate complete HeaderStyle; keep cross-object view, direct mutations and physical 68 B.

The EU wrapper selects `src/ov078/unclassified_helpers/DrawPageHeader_020c4b18.c`.

### `gItemReportTabTileRows`

Two tab-screen tile-row offsets select rectangle-copy rows.

Evidence: `eu/src/overlays/ov095/calls/LoadMenuBackgrounds_020bf570.c`. Rows 2/10 are not item/resource IDs; preserve exact x/width/height arguments.

The EU wrapper selects `src/ov095/panel_state/LoadMenuBackgrounds_020bf550.c`.

### `gItemReportPanelTileRows`

Seven panel-screen tile-row offsets select rectangle-copy rows.

Evidence: `eu/src/overlays/ov095/calls/LoadMenuBackgrounds_020bf570.c`. Keep all seven offsets and source/destination x 0xd/0xe arguments.

The EU wrapper selects `src/ov095/panel_state/LoadMenuBackgrounds_020bf550.c`.

### `gItemReportGroupGridRowStarts`

Nine group row starts are added to i/13 when registering cells.

Evidence: `eu/src/overlays/ov095/calls/InitGridMenu.c`. Grid row indices remain separate from pixelY positions and group item counts.

The EU wrapper selects `src/ov095/panel_state/InitGridMenu_020beb00.c`.

### `gEnemyViewerOrientationCorrectionQuat`

Multiplies the normalized input rotation quaternion by this correction before reconstructing/scaling the matrix.

Evidence: `eu/src/overlays/ov099/calls/ApplyQuaternionCorrectionToMatrix_020c185c.c`. No axis/angle/handedness name is inferred from values {0,b50,b50,0}.

The EU wrapper selects `src/ov099/unclassified_helpers/ApplyQuaternionCorrectionToMatrix_020c183c.c`.

### `gEnemyViewerScrollListConfig`

44-byte configuration passed to InitScrollList.

Evidence: `eu/src/overlays/ov099/calls/InitEnemyViewerScreen.c`. Keep 11 words and all -1 fields without inferring padding or ownership.

### `gEnemyReportDetailTextPathHead`

gEnemyReportTextPaths[1] points to 28-byte prefix of ui/report/text/&/enemy_detail.s.z.

Evidence: `eu/src/overlays/ov099/calls/InitViewerTextLayers.c`. Prefix has no NUL; keep adjacent 8-byte l.s.z tail at 020c2360 and pointer/addend.

### `gEnemyViewerSlotBank1Layouts`

Six 24-byte layouts create slot bank 1 and supply scroll coordinates.

Evidence: `eu/src/overlays/ov099/calls/CreateViewerSlotObjs.c`. Bank1 is the actual argument, without assigning main/sub display ownership.

The EU wrapper selects `src/ov099/unclassified_helpers/CreateViewerSlotObjs_020c0648.c`.

### `gEnemyViewerSlotBank0Layouts`

Twenty-one 24-byte layouts create slot bank 0 and supply scroll/visibility coordinates.

Evidence: `eu/src/overlays/ov099/calls/CreateViewerSlotObjs.c`. Keep all 21 records and duplicate IDs; no display-engine label is assigned.

The EU wrapper selects `src/ov099/unclassified_helpers/CreateViewerSlotObjs_020c0648.c`.

### `gEnemyReportRatePairFormatStyle2`

Exact tagged UTF16 format used for two rate arguments when style/locale getter equals 2.

Evidence: `eu/src/overlays/ov099/calls/DrawEntryStatsPanels.c`. Keep control units 1/2, %.2f%% patterns, parentheses and trailing zeros; no language-name inference.

The EU wrapper selects `src/ov099/panel_state/DrawEntryStatsPanels_020bf818.c`.

### `gEnemyReportRatePairFormatDefault`

Other branch formats the same rate pair with a different tagged UTF16 pattern.

Evidence: `eu/src/overlays/ov099/calls/DrawEntryStatsPanels.c`. Control unit before parenthesis differs from style 2; no visible-text normalization/deduplication.

The EU wrapper selects `src/ov099/panel_state/DrawEntryStatsPanels_020bf818.c`.

### `gEnemyViewerModeScales`

Forty fx32 mode values are assigned to all three model scale axes.

Evidence: `eu/src/overlays/ov099/calls/ApplyViewerModelPose.c`. No enemy/character mapping or new bounds check is inferred for mode indices.

The EU wrapper selects `src/ov099/unclassified_helpers/ApplyViewerModelPose_020c1d5c.c`.

### `gTheaterReportStateHandlers`

Four handlers selected by phase are invoked with scene when nonnull.

Evidence: `eu/src/overlays/ov103/calls/RunSceneStateHandler.c`. State0 callback presence differs from NULL; no logical return contract is inferred solely from void declarations.

The EU wrapper selects `src/ov103/panel_state/RunSceneStateHandler_020beb98.c`.

### `gTheaterReportBackgroundFileIndices`

Eleven per-entry file indices select loaded report backgrounds.

Evidence: `eu/src/overlays/ov103/calls/LoadEntryBackground_020bf0c4.c`. Keep stored 0..10 sequence; do not remove array or infer movie identifiers.

The EU wrapper selects `src/ov103/panel_state/LoadEntryBackground_020bf0a4.c`.

### `gTheaterReportListConfig`

44-byte configuration passed to SetupListPanel.

Evidence: `eu/src/overlays/ov103/calls/InitTheaterReportScreen.c`. Keep all 11 words and -1 fields; no complete initializer field layout is invented.

### `gTheaterReportTextPathHead`

gTheaterReportTextPaths[0] points to 16-byte prefix followed by /theater.s.z at 020c056c.

Evidence: `eu/src/overlays/ov103/calls/InitTextLayers_020bf1bc.c`. No NUL in prefix; retain adjacent 16-byte tail capacity and pointer relationships.

### `gTheaterReportSlotLayouts`

Twelve 20-byte layouts create bank 0 slots and supply scroll-cap/tick coordinates.

Evidence: `eu/src/overlays/ov103/calls/CreateTheaterReportSlotEntries.c`. This is stride 0x14, distinct from enemy viewer 24-byte layouts.

## Reproducible review and validation boundary

Use each bank's `eu/config/arm9/overlays/ovNNN/symbols.txt` and `delinks.txt` for identities and active owners. Follow EU wrapper aliases before shared code. Text-path chains are explicit in `eu/src/overlays/ov099/data/tables/PointerTables_ov099_020c22a0.c` and `eu/src/overlays/ov103/data/tables/PointerTables_ov103_020c04c0.c`, and their respective text-layer initializers.

All 19 existing ELF symbol extents and reconstructed R_ARM_ABS32 bytes agree with native extracted EU ROM. Physical and direct evidence sources are active delink inputs. No new compilation or official gate result is claimed. Integration must preserve the module matches, physical objects and their strided/sequential address relationships.


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
