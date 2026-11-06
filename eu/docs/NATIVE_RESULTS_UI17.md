# Results UI and shared shop DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The results screen exposes a two-pointer view across two separate native symbols. Its session-buffer parameters and TaskObject work retain different lifetimes. Extra shop entries use shared ItemInfo/name scratch, so a returned pointer or name is not owned by the caller.

Font paths are narrow strings; question-mark placeholders and numeric/label formats are wide halfword strings. Their padding and DATA section remain unchanged. The background container keeps its generic callback-slot contract; no init/draw/cleanup semantics are inferred from callback names.

## Inventory and evidence

### `ov034:020be8bc` → `gResultsObjectManagerConfig`

Previous label `data_ov034_020be8bc`; size **16 bytes**; source `eu/src/ov034/data/Rodata_ov034_020be8bc.c`.

16 RO bytes: four native object-manager configuration words.

InitResultsScreen copies this descriptor, overwrites its first word with the packed file key ending in index 0x15 and passes it to InitObjManagerAndMark.

Limits: Keep the overwritten static placeholder and the remaining three words; no undocumented graphics-field names are assigned.

Pinned references:

- `eu/src/ov034/data/Rodata_ov034_020be8bc.c`; line(s) 3.
- `eu/src/overlays/ov034/calls/InitResultsScreen.c`; line(s) 65, 137.

### `ov034:020be8cc` → `gResultsTileTableLayerIds`

Previous label `data_ov034_020be8cc`; size **16 bytes**; source `eu/src/ov034/data/Rodata_ov034_020be8cc.c`.

16 RO bytes: four word-sized tile-table IDs {8,9,10,11}.

InitResultsScene copies these IDs and supplies them to InitResultsTiles for its results-screen tile table.

Limits: They are tile-table layer IDs, not native BG register numbers, file IDs or callback pointers.

Pinned references:

- `eu/src/ov034/data/Rodata_ov034_020be8cc.c`; line(s) 3.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; line(s) 198, 230.

### `ov034:020be8dc` → `gResultsTextFrameConfig`

Previous label `data_ov034_020be8dc`; size **16 bytes**; source `eu/src/ov034/data/Rodata_ov034_020be8dc.c`.

16 RO bytes: eight native text-frame configuration halfwords.

InitResultsScreen supplies a copy to InitTextLayerAt on BG2 with tile-table row 10 and the loaded primary font, then marks that row dirty.

Limits: Keep the eight halfwords and original type; not all fields are colors or dimensions, and no new portable frame layout is declared here.

Pinned references:

- `eu/src/ov034/data/Rodata_ov034_020be8dc.c`; line(s) 20.
- `eu/src/overlays/ov034/calls/InitResultsScreen.c`; line(s) 63, 120.

### `ov034:020be8ec` → `gResultsBackgroundContainerConfig`

Previous label `data_ov034_020be8ec`; size **20 bytes**; source `eu/src/ov034/data/Rodata_ov034_020be8dc.c`.

20 RO bytes: capacities {7,0,7} followed by the two widget callback words.

InitResultsScreen passes this config to InitBackgroundContainer for its tag tracker. The callback relocations target DrawResultsWidgetOnLayer and ClearResultsWidgetOnLayer.

Limits: Parameter0c/parameter10 callback-slot semantics remain opaque until their invokers are proved; do not label them init/draw/cleanup solely from their targets.

Pinned references:

- `eu/src/ov034/data/Rodata_ov034_020be8dc.c`; line(s) 12.
- `eu/src/overlays/ov034/calls/InitResultsScreen.c`; line(s) 64, 126.

### `ov034:020be900` → `gResultsQuadIdentityRotation`

Previous label `data_ov034_020be900`; size **36 bytes**; source `eu/src/ov034/data/Rodata_ov034_020be8dc.c`.

36 RO bytes: native Q12 3x3 identity matrix.

DrawResultsTexturedQuad copies this matrix as its rotation seed before applying the quad/model transform and drawing.

Limits: Preserve all nine words and fixed-point identity values; this is not a 4x3 matrix.

Pinned references:

- `eu/src/ov034/data/Rodata_ov034_020be8dc.c`; line(s) 6.
- `eu/src/overlays/ov034/calls/DrawResultsTexturedQuad.c`; line(s) 16, 48.

### `ov034:020be980` → `gResultsMemberBonusValues`

Previous label `data_ov034_020be980`; size **120 bytes**; source `eu/src/ov034/data/Data_ov034_020be980.c`.

120 initialized DATA bytes: twenty records of two three-byte bonus rows.

ApplyResultsPartyBonus selects a row by member ID and whether its member-level byte is nonzero. It sums all three columns to scale bonusCount by total/100 for stageKind 0x1f, and separately sums masked columns from row 1 into bonusPoints.

Limits: Do not assign individual member/chip identities or a single percent unit to every consumer; the point-accumulation branch uses the same bytes directly.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020be980.c`; line(s) 7.
- `eu/src/overlays/ov034/calls/ApplyResultsPartyBonus.c` → `src/ov034/unclassified_helpers/ApplyResultsPartyBonus_020be258.c`; line(s) 22, 37, 49.

### `ov034:020c0eb8` → `gResultsFont10Path`

Previous label `data_ov034_020c0eb8`; size **24 bytes**; source `eu/src/ov034/data/Data_ov034_020c0eb8.c`.

24 initialized DATA bytes containing text/font_eu_10.nftr and zero padding.

InitResultsScreen passes this path to LoadUtf16FontResource for WORK->font.

Limits: The filename is a narrow path string; it does not itself contain UTF16 text or font glyph data. Keep all 24 bytes.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0eb8.c`; line(s) 5.
- `eu/src/overlays/ov034/calls/InitResultsScreen.c`; line(s) 59, 118.

### `ov034:020c0ed0` → `gResultsFont10sPath`

Previous label `data_ov034_020c0ed0`; size **24 bytes**; source `eu/src/ov034/data/Data_ov034_020c0ed0.c`.

24 initialized DATA bytes containing text/font_eu_10s.nftr and zero padding.

InitResultsScreen loads the alternate font from this path into WORK->fontAlt.

Limits: The suffix is preserved literally; no new claim about font dimensions or automatic fallback selection follows solely from its name.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0ed0.c`; line(s) 5.
- `eu/src/overlays/ov034/calls/InitResultsScreen.c`; line(s) 60, 119.

### `ov034:020c0f20` → `gResultsLockedLabelText`

Previous label `data_ov034_020c0f20`; size **28 bytes**; source `eu/src/ov034/data/Data_ov034_020c0f20.c`.

28 initialized DATA bytes: twelve wide question marks, terminator and an additional zero halfword.

RefreshResultsScreen draws this text for the name and selected description when IsResultsShopEntryUnlocked returns zero.

Limits: Keep all fourteen halfwords; the same placeholder is reused for two display fields and is not a narrow string.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0f20.c`; line(s) 5.
- `eu/src/overlays/ov034/calls/RefreshResultsScreen.c` → `src/ov034/unclassified_helpers/RefreshResultsScreen_020bb578.c`; line(s) 115, 495, 499.

### `ov034:020c0f3c` → `gResultsLockedPriceText`

Previous label `data_ov034_020c0f3c`; size **8 bytes**; source `eu/src/ov034/data/Data_ov034_020c0f3c.c`.

8 initialized DATA bytes: three wide question marks and terminator.

RefreshResultsScreen draws this right-aligned placeholder in the price position for a locked shop entry.

Limits: Retain the four-halfword allocation and distinguish it from the longer name/description placeholder.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0f3c.c`; line(s) 5.
- `eu/src/overlays/ov034/calls/RefreshResultsScreen.c` → `src/ov034/unclassified_helpers/RefreshResultsScreen_020bb578.c`; line(s) 116, 497.

### `ov034:020c0f44` → `gResultsPriceWideFormat`

Previous label `data_ov034_020c0f44`; size **8 bytes**; source `eu/src/ov034/data/Data_ov034_020c0f44.c`.

8 initialized DATA bytes: wide %d format, terminator and one extra zero halfword.

RefreshResultsScreen passes this format to OS_SNPrintf_0202e094 to render an unlocked entry price. The wrapper calls Text_VSNPrintfWide.

Limits: Preserve wide storage and padding despite the local const char declaration; formatter types are a separate native ABI issue.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0f44.c`; line(s) 9.
- `eu/src/overlays/ov034/calls/RefreshResultsScreen.c` → `src/ov034/unclassified_helpers/RefreshResultsScreen_020bb578.c`; line(s) 117, 504.

### `ov034:020c0f4c` → `gResultsRankLabelWideFormat`

Previous label `data_ov034_020c0f4c`; size **12 bytes**; source `eu/src/ov034/data/Data_ov034_020c0f44.c`.

12 initialized DATA bytes: wide %s%s format with two trailing zero halfwords.

DrawResultsLabelText combines the supplied label and the selected rank mark using OS_SNPrintf_0202e094 before drawing with font fallback.

Limits: The rank mark pointer is borrowed from the separate existing mark table. No new bounds check or rank identity is added.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0f44.c`; line(s) 5.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; line(s) 24, 36.

### `ov034:020c0f58` → `gResultsCountLabelWideFormat`

Previous label `data_ov034_020c0f58`; size **12 bytes**; source `eu/src/ov034/data/Data_ov034_020c0f58.c`.

12 initialized DATA bytes: terminated wide %s+%d format.

DrawResultsLabelText uses this format when count is positive, combining the current label text and count.

Limits: The native helper may reuse the same local output buffer as a formatting input; this rename does not rewrite that behavior.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020c0f58.c`; line(s) 5.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; line(s) 25, 40.

### `ov034:020c0fa0` → `gResultsScreenPointersPrefix`

Previous label `data_ov034_020c0fa0`; size **4 bytes**; source `eu/src/overlays/ov034/calls/InitResultsScene.c`.

4 BSS bytes: the parameter pointer at the start of the logical two-pointer ResultsScreen view.

InitResultsScene defines this word as ResultsParams*, allocating/borrowing session buffer 10. Most results helpers expose an eight-byte {params,work} view from the same address.

Limits: The work pointer is in the next separate four-byte symbol. Keep both native cells and distinguish the session parameter owner from TaskObject work.

Pinned references:

- `eu/src/overlays/ov034/ResultsScreen.h`; line(s) 6.
- `eu/src/overlays/ov034/calls/AdvanceResultsTransition.c` → `src/ov034/reviewed_helpers/AdvanceResultsTransition_020bb234.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/ClassifyResultsShopEntry.c` → `src/ov034/reviewed_helpers/ClassifyResultsShopEntry_020be4f8.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/ClearResultsFlagTwo.c` → `src/ov034/reviewed_helpers/ClearResultsFlagTwo_020bde24.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/ClearResultsWidgetOnLayer.c` → `src/ov034/reviewed_helpers/ClearResultsWidgetOnLayer_020bb070.c`; line(s) 13, 18.
- `eu/src/overlays/ov034/calls/CloseResultsScreen.c`; line(s) 22, 35, 39, 40, 41, 43, 44, 45, 46, 47.
- `eu/src/overlays/ov034/calls/CloseResultsSession.c`; line(s) 27, 57, 58, 59, 60, 61, 65, 66, 67, 82.
- `eu/src/overlays/ov034/calls/CommitResultsRewards.c` → `src/ov034/unclassified_helpers/CommitResultsRewards_020bd0a0.c`; line(s) 21, 36, 37, 38, 40.
- `eu/src/overlays/ov034/calls/DestroyResultsGraphics.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/DrawResultsLabelText.c` → `src/ov034/unclassified_helpers/DrawResultsLabelText_020bd010.c`; line(s) 22, 43.
- `eu/src/overlays/ov034/calls/DrawResultsWidgetOnLayer.c` → `src/ov034/reviewed_helpers/DrawResultsWidgetOnLayer_020bb04c.c`; line(s) 13, 18.
- `eu/src/overlays/ov034/calls/EnterResultsTierMode.c` → `src/ov034/reviewed_helpers/EnterResultsTierMode_020bb290.c`; line(s) 22, 28, 29, 30, 31, 32, 34, 35, 36, 38.
- `eu/src/overlays/ov034/calls/FinishResultsScreen.c` → `src/ov034/reviewed_helpers/FinishResultsScreen_020bdc3c.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/GetResultsShopItemInfo.c` → `src/ov034/reviewed_helpers/GetResultsShopItemInfo_020be418.c`; line(s) 33, 45, 60, 63, 64, 66, 68, 69, 71.
- `eu/src/overlays/ov034/calls/HandleResultsInput.c`; line(s) 93, 118, 119.
- `eu/src/overlays/ov034/calls/InitResultsScene.c`; line(s) 197, 273, 275, 276, 282, 292, 301, 303, 308, 309, 310, 312, 317, 323, 346, 348, 349, 351, 352, 357, 360, 361, 373, 378, 388, 401, 403, 408, 409, 411, 412.
- `eu/src/overlays/ov034/calls/InitResultsScreen.c`; line(s) 57, 98.
- `eu/src/overlays/ov034/calls/IsResultsInputEnabled.c` → `src/ov034/reviewed_helpers/IsResultsInputEnabled_020bde08.c`; line(s) 5, 6.
- `eu/src/overlays/ov034/calls/IsResultsShopEntryUnlocked.c` → `src/ov034/reviewed_helpers/IsResultsShopEntryUnlocked_020bdb70.c`; line(s) 25, 36, 38, 39.
- `eu/src/overlays/ov034/calls/MarkResultsComplete.c` → `src/ov034/reviewed_helpers/MarkResultsComplete_020bde3c.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/PollResultsScreen.c` → `src/ov034/reviewed_helpers/PollResultsScreen_020bdc18.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/RefreshResultsScreen.c` → `src/ov034/unclassified_helpers/RefreshResultsScreen_020bb578.c`; line(s) 113, 160, 161.
- `eu/src/overlays/ov034/calls/ResetResultsObjects.c` → `src/ov034/unclassified_helpers/ResetResultsObjects_020bce50.c`; line(s) 18, 29.
- `eu/src/overlays/ov034/calls/SetResultsMode.c` → `src/ov034/reviewed_helpers/SetResultsMode_020bb274.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/SetupResultsDisplay.c` → `src/ov034/display/SetupResultsDisplay_020bdc94.c`; line(s) 11, 31, 32, 33.
- `eu/src/overlays/ov034/calls/SetupResultsShopList.c`; line(s) 26, 35, 46, 47, 49, 51, 52, 53, 55, 56, 57.
- `eu/src/overlays/ov034/calls/StartResultsScreen.c` → `src/ov034/reviewed_helpers/StartResultsScreen_020bdbd0.c`; line(s) 3, 4.
- `eu/src/overlays/ov034/calls/UpdateResultsFade.c` → `src/ov034/reviewed_helpers/UpdateResultsFade_020bb094.c`; line(s) 16, 17.
- `eu/src/overlays/ov034/calls/UpdateResultsScreen.c`; line(s) 15.

### `ov034:020c0fa4` → `gResultsScreenWorkPointer`

Previous label `data_ov034_020c0fa4`; size **4 bytes**; source `eu/src/overlays/ov034/calls/InitResultsScene.c`.

4 BSS bytes: task-work pointer, second word of the ResultsScreen view.

InitResultsScene stores GetCurrentTaskWork, clears/initializes its work and UI state, and all screen helpers reach it through the same second word. CloseResultsSession clears the work pointer after cleanup.

Limits: This cell does not own a separately allocated ResultsWork buffer; task work and persistent parameter/session storage have different lifetimes.

Pinned references:

- `eu/src/overlays/ov034/calls/InitResultsScene.c`; line(s) 196, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 268, 269, 271, 277, 281, 282, 301, 312, 313, 347, 349, 350, 351, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 380, 381, 385, 387, 391, 397, 402, 405, 416, 419.

### `ov034:020c0fa8` → `gResultsShopNameTextBuffer`

Previous label `data_ov034_020c0fa8`; size **64 bytes**; source `eu/src/overlays/ov034/data/bss/Bss_ov034_020c0fa8.c`.

64 BSS bytes: thirty-two halfwords of shared formatted shop name text.

GetResultsShopItemInfo formats the extra-price name into this buffer with the wide formatter and returns an ItemInfo whose name points here.

Limits: The returned text is borrowed scratch and is overwritten by later calls. Preserve the 64-byte size and the supplied formatter limit 0x20.

Pinned references:

- `eu/src/overlays/ov034/calls/GetResultsShopItemInfo.c` → `src/ov034/reviewed_helpers/GetResultsShopItemInfo_020be418.c`; line(s) 34, 64, 69, 73.
- `eu/src/overlays/ov034/data/bss/Bss_ov034_020c0fa8.c`; line(s) 4.

### `ov034:020c0fe8` → `gResultsExtraShopItemInfoStorage`

Previous label `data_ov034_020c0fe8`; size **88 bytes**; source `eu/src/overlays/ov034/data/bss/Bss_ov034_020c0fa8.c`.

88 BSS bytes: shared ItemInfo-compatible scratch plus retained tail bytes.

GetResultsShopItemInfo writes iconId=-1, the formatted name pointer and a localized description pointer for nonstandard shop entries, then returns this address. Its visible ItemInfo view reaches offset 0x48.

Limits: The native allocation is 88 bytes, larger than the visible 72-byte view. Preserve the sixteen-byte tail and do not copy this shared returned pointer as an owned item record.

Pinned references:

- `eu/src/overlays/ov034/calls/GetResultsShopItemInfo.c` → `src/ov034/reviewed_helpers/GetResultsShopItemInfo_020be418.c`; line(s) 35, 65, 66, 70, 71, 73, 74.
- `eu/src/overlays/ov034/data/bss/Bss_ov034_020c0fa8.c`; line(s) 3.

Wide formatter binding: `eu/src/calls/OS_SNPrintf_0202e094.c` → `Text_VSNPrintfWide`. Native background-container allocation layout: `eu/src/overlays/ov027/calls/InitBackgroundContainer.c`.


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
