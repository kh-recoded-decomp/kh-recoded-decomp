# Matrix drawing and refresh DATA

These 19 DATA objects are used by overlay075 category cycling, matrix drawing, cursor handling, status refresh and item-picking. Names describe actual operations and retain the native packed layouts. No stats field order, selector units or ABI is changed.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Native bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov075:20d140a | `data_ov075_020d140a` | `gMatrixCategoryCycleEntries` | 10 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1408.c` | `eu/src/overlays/ov075/calls/CycleNodeCategory.c` |
| ov075:20d14a0 | `data_ov075_020d14a0` | `gMatrixCursorTouchRect` | 8 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14a0.c` | `eu/src/overlays/ov075/calls/UpdateSlotCursor.c` |
| ov075:20d14a8 | `data_ov075_020d14a8` | `gMatrixRightLinkCellParams` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14a8.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14ac | `data_ov075_020d14ac` | `gMatrixUpLinkCellParams` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14ac.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14b0 | `data_ov075_020d14b0` | `gMatrixDownLinkCellParams` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14b0.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14b4 | `data_ov075_020d14b4` | `gMatrixMedalLightCellParams` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14b4.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14b8 | `data_ov075_020d14b8` | `gMatrixLeftLinkCellParams` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14b8.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14bc | `data_ov075_020d14bc` | `gMatrixCornerCellParams` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14bc.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14c0 | `data_ov075_020d14c0` | `gMatrixCellModelFrames` | 8 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14c0.c` | `eu/src/overlays/ov075/calls/InitMatrixMenu.c` |
| ov075:20d14c8 | `data_ov075_020d14c8` | `gMatrixCursorCellFrameValues` | 8 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14c8.c` | `eu/src/overlays/ov075/calls/UpdateSlotCursor.c` |
| ov075:20d14d0 | `data_ov075_020d14d0` | `gMatrixMenuObjectRotationTemplate` | 8 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14d0.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14d8 | `data_ov075_020d14d8` | `gMatrixClockHandRotationTemplate` | 8 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14d8.c` | `eu/src/overlays/ov075/calls/DrawMatrixMenu.c` |
| ov075:20d14f0 | `data_ov075_020d14f0` | `gMatrixEmptyNeighborIds` | 16 | `eu/src/overlays/ov075/data/Rodata_ov075_020d14f0.c` | `eu/src/overlays/ov075/calls/PropagateMatrixNodeVisit.c` |
| ov075:20d1510 | `data_ov075_020d1510` | `gMatrixMenuWindowStyle` | 16 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1510.c` | `eu/src/overlays/ov075/calls/InitMatrixMenu.c` |
| ov075:20d1520 | `data_ov075_020d1520` | `gMatrixEventRefreshRequestTemplate` | 24 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1520.c` | `eu/src/overlays/ov075/calls/UpdateMatrixEventAnimation.c` |
| ov075:20d1538 | `data_ov075_020d1538` | `gMatrixSelectionRefreshRequestTemplate` | 24 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1538.c` | `eu/src/overlays/ov075/calls/SelectMatrixNode.c` |
| ov075:20d1550 | `data_ov075_020d1550` | `gMatrixStatsPreviewRefreshTemplate` | 24 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1550.c` | `eu/src/overlays/ov075/calls/PreviewMatrixNodeStats_020c5d10.c` |
| ov075:20d1680 | `data_ov075_020d1680` | `gMatrixPickerIconGrid` | 4 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1680.c` | `eu/src/overlays/ov075/calls/MenuPanel_DrawItemRows_020d076c.c` |
| ov075:20d1728 | `data_ov075_020d1728` | `gMatrixPickerOwnerCategorySets` | 124 | `eu/src/overlays/ov075/data/Rodata_ov075_020d1728.c` | `eu/src/overlays/ov075/calls/UnlockableListPanel_Open.c` |

## Packed frame parameters and rotations

The legacy CellSize type has two u16 fields named width/height, but InitCellImageQuad establishes their actual use: image width is divided by the first value, and the resulting frame width is multiplied by the second value for the S texture offset. They therefore act as horizontal frame count and frame index in these calls, rather than pixel width and height.

| Matrix use | Stored pair | Actual neighbor/use evidence |
|---|---|---|
| left link | {4,0} | grid neighbor id-1 |
| up link | {4,1} | grid neighbor id-columns |
| right link | {4,2} | grid neighbor id+1 |
| down link | {4,3} | grid neighbor id+columns |
| medal light | {2,0} | local frame index becomes medalBits&1 |
| corner image | {4,0} | separate local corner-image frame selection |

The left-link and corner templates have equal values but remain distinct. Rotation templates store two s16 pivots and one s32 angle: the menu object starts with pivot (32,44), while the clock hand uses (31,31). Only local angles are changed from the corresponding menu values before drawing.

## Cursor and category records

The cursor touch rectangle supplies packed width/height/margins for strict inside/outside comparisons around (128,96). The five category-cycle entries contain a byte category ID and a byte threshold used to skip unavailable categories. The option-menu paths use the same IDs. No named progression level is inferred solely from the private saved-field label.

The cell model and cursor tables each store eight bytes indexed by the low three bits of a selector. Consumers shift the byte value left 12 before writing the relevant model/cursor field. Equal values do not establish shared storage, and the private scale/level field names do not establish units or a gameplay meaning for every selector.

gMatrixEmptyNeighborIds initializes four signed IDs to -1 before visit propagation fills eligible directions. It is a local neighbor-list template, not a packed visited-state mask.

## Refresh and picker contracts

The event and selection refresh templates each store 24 bytes and begin with value 4. The stat-preview template begins with value 1 and is filled with computed values before status refresh. Each remains separate even when bytes are equal. These names do not resolve the known legacy magic/defense field-order disagreement between stats views; field meanings require separate writer/consumer evidence.

The matrix item-row drawer includes the active EU slot-menu row implementation through its include search path and aliases its cell-grid object to ov075:020d1680. The four-byte grid is {1,2,0,0}. The owner-category array contains six complete 20-byte records (count plus four IDs), followed by one stored word: all 124 bytes are preserved. The owner index remains a caller precondition.

## Per-object evidence and limits

### `gMatrixCategoryCycleEntries`

Five packed two-byte entries supply node category ID and a selector threshold used when cycling categories; option-menu cycling reads the same IDs.

Evidence: `eu/src/overlays/ov075/calls/CycleNodeCategory.c`. The second byte gates a saved selector; no named progression level is inferred from a private level field.

The EU wrapper selects `src/ov075/unclassified_helpers/CycleNodeCategory_020cbb34.c`.

### `gMatrixCursorTouchRect`

The rectangle width/height/margins determine whether touch coordinates lie within the matrix cursor panel around (128,96).

Evidence: `eu/src/overlays/ov075/calls/UpdateSlotCursor.c`. Keep the 8-byte packed rectangle and strict comparisons; do not treat two u32 words as pixel coordinates.

The EU wrapper selects `src/ov075/unclassified_helpers/UpdateSlotCursor_020cc5a8.c`.

### `gMatrixRightLinkCellParams`

Right-neighbor links use the cell parameters {4,2}, selecting frame 2 of four horizontal frames.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. The legacy CellSize fields are frame count/index in InitCellImageQuad, not pixel width/height.

### `gMatrixUpLinkCellParams`

Up-neighbor links use cell parameters {4,1}, selecting frame 1 of four horizontal frames.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. Keep this separate from equal-valued data in other drawing contexts.

### `gMatrixDownLinkCellParams`

Down-neighbor links use cell parameters {4,3}, selecting frame 3 of four horizontal frames.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. No new texture subdivision or index normalization.

### `gMatrixMedalLightCellParams`

Copies the two-frame parameters then replaces the frame index with medalBits&1 before drawing medal lights.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. Only the local frame index changes; the stored template remains {2,0}.

### `gMatrixLeftLinkCellParams`

Left-neighbor links use cell parameters {4,0}, selecting frame 0 of four horizontal frames.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. Direction follows the actual neighboring cell index id-1, not table order or equal values.

### `gMatrixCornerCellParams`

The corner-image rendering path copies the {4,0} frame parameters and changes its local frame index when needed.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. Equal values to the left-link template remain separate physical objects.

### `gMatrixCellModelFrames`

Eight byte values indexed by cell selector&7 are shifted left 12 and applied to the cell model animation.

Evidence: `eu/src/overlays/ov075/calls/InitMatrixMenu.c`. No named character/stat column is inferred; preserve all eight bytes and their stored order.

The EU wrapper selects `src/ov075/matrix_menu/InitMatrixMenu_020c49cc.c`.

### `gMatrixCursorCellFrameValues`

Eight byte values indexed by current cell code&7 are shifted left 12 to update the cursor cell field when the high bit is clear.

Evidence: `eu/src/overlays/ov075/calls/UpdateSlotCursor.c`. This equal-valued table is a separate object from initialization frames; private scale naming is not treated as a unit contract.

The EU wrapper selects `src/ov075/unclassified_helpers/UpdateSlotCursor_020cc5a8.c`.

### `gMatrixMenuObjectRotationTemplate`

Copies pivot (32,44) and angle 0 before setting a local angle from menuRotation and drawing the menu object image.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. The physical 8-byte record contains two s16 pivots and one s32 angle; no type change.

### `gMatrixClockHandRotationTemplate`

Copies pivot(31,31) and angle 0, then calculates the local clock-hand angle from clockHour.

Evidence: `eu/src/overlays/ov075/calls/DrawMatrixMenu.c`. Preserve the existing integer division and 16-bit narrowing; no time-system interpretation is added.

### `gMatrixEmptyNeighborIds`

Four -1 IDs initialize the local neighbor list before matrix visit propagation fills eligible directions.

Evidence: `eu/src/overlays/ov075/calls/PropagateMatrixNodeVisit.c`. Template is four signed IDs, not packed flags or a visited bitmask.

### `gMatrixMenuWindowStyle`

Copies the 16-byte text-frame style used when opening matrix-menu windows.

Evidence: `eu/src/overlays/ov075/calls/InitMatrixMenu.c`. Resource character-base and layout values remain unchanged.

The EU wrapper selects `src/ov075/matrix_menu/InitMatrixMenu_020c49cc.c`.

### `gMatrixEventRefreshRequestTemplate`

Copies the 24-byte request passed to RefreshStatusMenuData after marking the matrix event/portal flag.

Evidence: `eu/src/overlays/ov075/calls/UpdateMatrixEventAnimation.c`. Only request role is proved; no complete stats field meanings or unused word interpretations are introduced.

### `gMatrixSelectionRefreshRequestTemplate`

Copies the 24-byte request passed to RefreshStatusMenuData from the selected-node flow.

Evidence: `eu/src/overlays/ov075/calls/SelectMatrixNode.c`. Separate from the event request despite equal stored values.

The EU wrapper selects `src/ov075/matrix_menu/SelectMatrixNode_020c4370.c`.

### `gMatrixStatsPreviewRefreshTemplate`

Copies the 24-byte preview/refresh request before filling computed values and invoking the existing status refresh path.

Evidence: `eu/src/overlays/ov075/calls/PreviewMatrixNodeStats_020c5d10.c`. Does not resolve the legacy defense/magic field-order disagreement; all field semantics beyond this operation remain separate evidence work.

The EU wrapper selects `src/ov075/matrix_menu/PreviewMatrixNodeStats_020c5d10.c`.

### `gMatrixPickerIconGrid`

The matrix picker reuses the item-row drawer with EU aliases and copies this {1,2,0,0} cell grid to draw icon frames.

Evidence: `eu/src/overlays/ov075/calls/MenuPanel_DrawItemRows_020d076c.c`. Four packed byte fields, not four scalar words. Shared EU drawer resolves through eu include search root.

The EU wrapper selects `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c`.

### `gMatrixPickerOwnerCategorySets`

The selected owner indexes category-set records; count and four category words are copied into the picker panel.

Evidence: `eu/src/overlays/ov075/calls/UnlockableListPanel_Open.c`. Physical 124 bytes contain six 20-byte complete sets plus one retained trailing word. Caller owner range is not validated here.

The EU wrapper selects `eu/../src/ov075/unclassified_helpers/func_ov075_020d0014.c`, `src/ov075/unclassified_helpers/func_ov075_020d0014.c`.

## Reproducible review and validation boundary

Locate each symbol in `eu/config/arm9/overlays/ov075/symbols.txt` and its active source range in the same bank's `delinks.txt`. Follow EU aliases and the EU include search root before interpreting shared code. Frame count/index behavior is demonstrated by `src/ov075/unclassified_helpers/InitCellImageQuad_020cd54c.c`; direction mapping is in the active DrawMatrixMenu body.

All 19 existing ELF symbol extents and bytes agree with the extracted native EU ROM. Both physical and direct evidence sources are active delink inputs. No new compilation or official gate result is claimed by this read-only review. Integration must preserve the module matches, physical DATA layout and pointer/addend relationships.


## Byte-exact validation

73 DATA identities retain their source paths, native sizes and storage.
67/69 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 120 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
