# Slot and item menu DATA contracts

These 34 identifiers describe concrete slot/item menu resources, packed drawing templates, category filters, threshold tables, prompt definitions and shared hint state. The original physical objects and files are preserved, including records that participate in sequential logical views. No field-type or prototype correction is included.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Physical bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov076:20cd0c0 | `data_ov076_020cd0c0` | `gSlotMenuModelResourceIds` | 24 | `eu/src/ov076/data/Rodata_ov076_020cd0b8.c` | `eu/src/overlays/ov076/calls/SlotMenu_InitModels.c` |
| ov076:20cd0d8 | `data_ov076_020cd0d8` | `gSlotMenuExtraModelResourceIds` | 8 | `eu/src/ov076/data/Rodata_ov076_020cd0d8.c` | `eu/src/overlays/ov076/calls/SlotMenu_InitModels.c` |
| ov076:20cd0e0 | `data_ov076_020cd0e0` | `gSlotFusionRateStorage` | 68 | `eu/src/ov076/data/Rodata_ov076_020cd0d8.c` | `eu/src/overlays/ov076/calls/SlotMenu_FuseSlotRecords.c` |
| ov076:20cd124 | `data_ov076_020cd124` | `gSlotPickerCategoryFilterCodes` | 8 | `eu/src/ov076/data/Rodata_ov076_020cd124.c` | `eu/src/overlays/ov076/calls/MenuPanel_ApplyCategoryFilter.c` |
| ov076:20cd12c | `data_ov076_020cd12c` | `gSlotPickerIconGrid` | 4 | `eu/src/ov076/data/Rodata_ov076_020cd12c.c` | `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c` |
| ov076:20cd130 | `data_ov076_020cd130` | `gSlotMenuTierThresholds` | 16 | `eu/src/ov076/data/Rodata_ov076_020cd12c.c` | `eu/src/overlays/ov076/calls/IsRecordCapacityReached.c` |
| ov076:20cd150 | `data_ov076_020cd150` | `gSlotMenuFrameTiles` | 20 | `eu/src/ov076/data/Rodata_ov076_020cd140.c` | `eu/src/overlays/ov076/calls/BuildSlotMenuFrameTilemap.c` |
| ov076:20cd164 | `data_ov076_020cd164` | `gSlotMenuImageQuadRotation` | 36 | `eu/src/ov076/data/Rodata_ov076_020cd140.c` | `eu/src/overlays/ov076/calls/DrawImageQuad_020c9a78.c` |
| ov076:20cd188 | `data_ov076_020cd188` | `gSlotMenuThresholdRankMap` | 40 | `eu/src/ov076/data/Rodata_ov076_020cd140.c` | `eu/src/overlays/ov076/calls/ApplySlotMenuThresholdRankBonus.c` |
| ov076:20cd1b0 | `data_ov076_020cd1b0` | `gSlotPickerOwnerCategorySets` | 124 | `eu/src/ov076/data/Rodata_ov076_020cd140.c` | `eu/src/overlays/ov076/calls/ItemSelectionPanel_Open.c` |
| ov076:20cd22c | `data_ov076_020cd22c` | `gSlotPickerDefaultCategorySet` | 16 | `eu/src/ov076/data/Rodata_ov076_020cd22c.c` | `eu/src/overlays/ov076/calls/MenuPanel_ApplyCategoryFilter.c` |
| ov076:20cd23c | `data_ov076_020cd23c` | `gSlotMenuModulatedQuadRotation` | 36 | `eu/src/ov076/data/Rodata_ov076_020cd22c.c` | `eu/src/overlays/ov076/calls/DrawMenuImageModulated_020ccf34.c` |
| ov076:20cd280 | `data_ov076_020cd280` | `gSlotMenuBrowsePrompt` | 12 | `eu/src/ov076/data/Data_ov076_020cd280.c` | `eu/src/overlays/ov076/calls/SlotMenu_OpenEmptySlot.c` |
| ov076:20cd2a4 | `data_ov076_020cd2a4` | `gSlotMenuEditResetPrompt` | 12 | `eu/src/ov076/data/Data_ov076_020cd2a4.c` | `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c` |
| ov076:20cd2b0 | `data_ov076_020cd2b0` | `gSlotMenuSecondColumnPrompt` | 12 | `eu/src/ov076/data/Data_ov076_020cd2b0.c` | `eu/src/overlays/ov076/calls/SlotMenu_HandleSlotSelect.c` |
| ov076:20cd2bc | `data_ov076_020cd2bc` | `gSlotMenuEquippedRecordPromptHead` | 12 | `eu/src/ov076/data/Data_ov076_020cd2bc.c` | `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c` |
| ov076:20cd2c8 | `data_ov076_020cd2c8` | `gSlotMenuEquippedRecordPromptTail` | 12 | `eu/src/ov076/data/Data_ov076_020cd2c8.c` | `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c` |
| ov076:20cd2d4 | `data_ov076_020cd2d4` | `gSlotMenuThirdColumnPromptHead` | 12 | `eu/src/ov076/data/Data_ov076_020cd2d4.c` | `eu/src/overlays/ov076/calls/SlotMenu_HandleSlotSelect.c` |
| ov076:20cd2e0 | `data_ov076_020cd2e0` | `gSlotMenuThirdColumnPromptTail` | 12 | `eu/src/ov076/data/Data_ov076_020cd2e0.c` | `eu/src/overlays/ov076/calls/SlotMenu_HandleSlotSelect.c` |
| ov076:20cd2ec | `data_ov076_020cd2ec` | `gSlotMenuFusionResultPromptHead` | 12 | `eu/src/ov076/data/Data_ov076_020cd2ec.c` | `eu/src/overlays/ov076/calls/SlotMenu_OpenSlotPanel.c` |
| ov076:20cd2f8 | `data_ov076_020cd2f8` | `gSlotMenuFusionResultPromptTail` | 12 | `eu/src/ov076/data/Data_ov076_020cd2f8.c` | `eu/src/overlays/ov076/calls/SlotMenu_OpenSlotPanel.c` |
| ov076:20cd400 | `data_ov076_020cd400` | `gSlotMenuSharedState` | 12 | `eu/src/overlays/ov076/calls/SlotMenu_DrawHintText.c` | `eu/src/overlays/ov076/calls/SlotMenu_DrawHintText.c` |
| ov077:20ca11c | `data_ov077_020ca11c` | `gItemScreenHelpPrompt` | 12 | `eu/src/ov077/data/Rodata_ov077_020ca11c.c` | `eu/src/overlays/ov077/calls/OpenHelpMessageOrActivate.c` |
| ov077:20ca128 | `data_ov077_020ca128` | `gItemScreenRefreshRequestStorage` | 44 | `eu/src/ov077/data/Rodata_ov077_020ca11c.c` | `eu/src/overlays/ov077/calls/UsePartySlotItem.c` |
| ov077:20ca154 | `data_ov077_020ca154` | `gItemPickerCategoryFilterCodes` | 8 | `eu/src/ov077/data/Rodata_ov077_020ca154.c` | `eu/src/overlays/ov077/calls/MenuPanel_ApplyCategoryFilter_020c6c68.c` |
| ov077:20ca15c | `data_ov077_020ca15c` | `gItemPickerIconGrid` | 4 | `eu/src/ov077/data/Rodata_ov077_020ca15c.c` | `eu/src/overlays/ov077/calls/MenuPanel_DrawItemRows_020c9870.c` |
| ov077:20ca160 | `data_ov077_020ca160` | `gItemScreenTierThresholds` | 16 | `eu/src/ov077/data/Rodata_ov077_020ca15c.c` | `eu/src/overlays/ov077/calls/IsPartyLevelSufficient_020c7a98.c` |
| ov077:20ca180 | `data_ov077_020ca180` | `gItemScreenFrameTiles` | 20 | `eu/src/ov077/data/Rodata_ov077_020ca170.c` | `eu/src/overlays/ov077/calls/BuildItemScreenFrameTilemap.c` |
| ov077:20ca194 | `data_ov077_020ca194` | `gItemScreenSpriteQuadRotation` | 36 | `eu/src/ov077/data/Rodata_ov077_020ca170.c` | `eu/src/overlays/ov077/calls/DrawSpriteRegionQuad.c` |
| ov077:20ca1b8 | `data_ov077_020ca1b8` | `gItemScreenThresholdRankMap` | 40 | `eu/src/ov077/data/Rodata_ov077_020ca170.c` | `eu/src/overlays/ov077/calls/ApplyItemScreenThresholdRankBonus.c` |
| ov077:20ca1e0 | `data_ov077_020ca1e0` | `gItemPickerOwnerCategorySets` | 124 | `eu/src/ov077/data/Rodata_ov077_020ca170.c` | `eu/src/overlays/ov077/calls/ItemListPanel_Open.c` |
| ov077:20ca25c | `data_ov077_020ca25c` | `gItemPickerDefaultCategorySet` | 16 | `eu/src/ov077/data/Rodata_ov077_020ca25c.c` | `eu/src/overlays/ov077/calls/MenuPanel_ApplyCategoryFilter_020c6c68.c` |
| ov077:20ca26c | `data_ov077_020ca26c` | `gItemScreenPackedQuadRotation` | 36 | `eu/src/ov077/data/Rodata_ov077_020ca25c.c` | `eu/src/overlays/ov077/calls/DrawItemScreenImageFromPackedArgs.c` |
| ov077:20ca3a0 | `data_ov077_020ca3a0` | `gItemScreenSharedState` | 12 | `eu/src/overlays/ov077/calls/ItemScreen_DrawHintText.c` | `eu/src/overlays/ov077/calls/ItemScreen_DrawHintText.c` |

## Stored extents and partial templates

The slot model resource array keeps its -1 sentinel; the separate extra-resource pair remains distinct. gSlotFusionRateStorage is physically 68 bytes, while the copied rate view is two rows of six 32-bit parameters (48 bytes). The remaining 20 bytes are preserved without assigning more rate entries or padding. Similarly, gItemScreenRefreshRequestStorage is 44 bytes with a demonstrated 24-byte refresh request at its start and 20 bytes outside that view.

The two frame tile tables each store 20 bytes. The builders use nine u16 values as three rows of left/middle/right tiles, leaving one additional stored u16 beyond the 18-byte logical table. Keep that physical extent and the independent equal-valued matrices for normal, modulated and packed image draw paths.

## Category filters and thresholds

Each category-code object contains eight signed bytes despite its u32 physical declaration. A nonnegative code selects one category; -1 uses the panel's custom category set; another negative code uses the default IDs 4,5,6 with count 3 and invert FALSE. The default-set objects have a fourth stored zero word. Owner-category tables store six complete 20-byte records (count plus four IDs), followed by one retained word. Caller index preconditions stay unchanged.

The four-word tier thresholds and five-pair rank maps consume the u16 at SelectionPackedValueBlock+0x0a under mode/session guards. Legacy level/capacity field names do not prove that value's units. The rank-map path preserves the <= threshold comparison, rank saturation at 4 and value write through SetParamHalf18. No new gameplay ability, difficulty or stat layout is inferred.

## Prompt definitions and sequential records

OpenHintPrompt and AdvanceHintPrompt prove a 12-byte logical prompt record. Byte 0 is flagIndex, byte 1 messageIndex, byte 2 signed alignment; cursor placement also writes s16 x/y fields at +4/+6, and the separate word at +8 is an optional onOpen hook. Other bytes retain their partial-view contract. The first packed word can resemble an ITCM address numerically; it is read as these byte fields, not called as a function pointer.

OpenHintPrompt stores the definition, argument, finish hook and final state word. AdvanceHintPrompt reads that same final state word as promptsLeft, decrements it and advances promptDef by one 12-byte record while prompts remain. It sets the completed prompt flag at flagIndex+0xf50. The last record invokes the finish hook with the stored argument. The legacy void* parameter declaration in the opening helper does not establish ownership or a pointer lifetime for the count value.

| Logical sequence | First physical object | Next physical object | Count |
|---|---|---|---:|
| equipped-record edit prompt | gSlotMenuEquippedRecordPromptHead at 020cd2bc | gSlotMenuEquippedRecordPromptTail at 020cd2c8 | 2 |
| third-column prompt | gSlotMenuThirdColumnPromptHead at 020cd2d4 | gSlotMenuThirdColumnPromptTail at 020cd2e0 | 2 |
| fusion-result prompt | gSlotMenuFusionResultPromptHead at 020cd2ec | gSlotMenuFusionResultPromptTail at 020cd2f8 | 2 |

The browse, edit-reset and second-column prompts use one record. The item-screen help prompt is also one record and keeps its const declaration. Cursor helpers modify alignment/coordinates of the mutable slot prompt records without changing physical boundaries.

SlotMenu_ShowResultMessage makes a separate cross-object read: its EU base is 020cd2e0 and offset+12 reaches 020cd2ec. That byte is the following fusion-result prompt's flagIndex, used with 0xf50. Preserve this relationship rather than shortening, reordering or deduplicating prompt records. Naming the physical head/tail objects does not make them separate owned prompt allocations.

## Shared menu reference and hint colors

The active SlotMenu_DrawHintText and ItemScreen_DrawHintText sources each define one exact 12-byte BSS struct: word0 is used as the current menu reference by initialization/shutdown views; colors[2] begins at +4. The draw helpers set colors to 0xf2/0xfa and pass the address of that color array as tagged-text callback context. Native ELF symbol size is 12, not the larger aligned module BSS range.

The metadata labels at ov076:020cd404 and ov077:020ca3a4 identify the interior color arrays at parent+4. They have no separate C allocation or ELF symbol definition. Their alias audit is separate from this owner rename block; do not generate another colors array, duplicate storage or change the parent object to a pointer scalar.

## Per-object evidence and limits

### `gSlotMenuModelResourceIds`

Six IDs select model resources for the slot-menu model setup.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_InitModels.c`. First stored ID is -1; preserve its sentinel and the consumer branch instead of normalizing it.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_InitModels_020c6954.c`.

### `gSlotMenuExtraModelResourceIds`

Copies the pair of extra model-resource IDs 9/10 for additional model setup.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_InitModels.c`. Distinct from the preceding six-entry resource array.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_InitModels_020c6954.c`.

### `gSlotFusionRateStorage`

The first 48 bytes are copied as two rows of six integer rate parameters for slot fusion.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_FuseSlotRecords.c`. Physical 68 B contains 20 B beyond that demonstrated rate view. Keep the trailing constants unchanged without treating them as more rates or padding.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_FuseSlotRecords_020c851c.c`.

### `gSlotPickerCategoryFilterCodes`

Eight signed bytes map picker modes to a category or negative set-selector code.

Evidence: `eu/src/overlays/ov076/calls/MenuPanel_ApplyCategoryFilter.c`. Packed u32 definition is read as signed bytes; preserve -1 custom-set and other-negative default-set behavior.

The EU wrapper selects `src/ov076/unclassified_helpers/MenuPanel_ApplyCategoryFilter_020c9c14.c`.

### `gSlotPickerIconGrid`

Copies packed cell grid {1,2,0,0} while drawing slot-picker item icons.

Evidence: `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c`. Four byte fields; no extra allocation or four-word interpretation.

### `gSlotMenuTierThresholds`

Copies four thresholds used by the mode/session-gated tier check over SelectionPackedValueBlock+0xa.

Evidence: `eu/src/overlays/ov076/calls/IsRecordCapacityReached.c`. Legacy level/capacity labels do not establish units of that u16; retain all four words and the actual comparisons.

The EU wrapper selects `src/ov076/unclassified_helpers/IsRecordCapacityReached_020caa44.c`.

### `gSlotMenuFrameTiles`

Nine u16 tile values form three left/middle/right frame rows used to build the slot-menu tilemap.

Evidence: `eu/src/overlays/ov076/calls/BuildSlotMenuFrameTilemap.c`. Physical 20 B retains an additional stored u16 beyond the 18-byte logical frame table; do not shrink it.

### `gSlotMenuImageQuadRotation`

Copies the identity 3x3 base rotation for image-quad rendering.

Evidence: `eu/src/overlays/ov076/calls/DrawImageQuad_020c9a78.c`. Separate physical matrix from modulated rendering and other overlays.

The EU wrapper selects `src/ov076/unclassified_helpers/DrawImageQuad_020c9a58.c`.

### `gSlotMenuThresholdRankMap`

Five threshold/value pairs select and adjust a rank, clamp it to 4, then pass the value to SetParamHalf18.

Evidence: `eu/src/overlays/ov076/calls/ApplySlotMenuThresholdRankBonus.c`. The source u16 at packed-block+0xa has unresolved units; no named ability/level semantics or altered <= comparison.

### `gSlotPickerOwnerCategorySets`

Owner selects count-plus-four-category records copied to the picker panel.

Evidence: `eu/src/overlays/ov076/calls/ItemSelectionPanel_Open.c`. Physical 124 B contains six complete 20-byte sets and one trailing word; preserve caller owner preconditions.

The EU wrapper selects `eu/../src/ov076/unclassified_helpers/MenuPanel_Open_020cc0e4.c`, `src/ov076/unclassified_helpers/MenuPanel_Open_020cc0e4.c`.

### `gSlotPickerDefaultCategorySet`

For a negative selector other than -1, filters category IDs 4,5,6 using count 3 and invert FALSE.

Evidence: `eu/src/overlays/ov076/calls/MenuPanel_ApplyCategoryFilter.c`. Four words are stored; the fourth zero is retained beyond the three demonstrated category IDs.

The EU wrapper selects `src/ov076/unclassified_helpers/MenuPanel_ApplyCategoryFilter_020c9c14.c`.

### `gSlotMenuModulatedQuadRotation`

Copies the identity 3x3 rotation in modulated menu-image rendering.

Evidence: `eu/src/overlays/ov076/calls/DrawMenuImageModulated_020ccf34.c`. Equal values do not make it interchangeable with the normal image-quad matrix.

The EU wrapper selects `src/ov076/unclassified_helpers/DrawMenuImageModulated_020ccf14.c`.

### `gSlotMenuBrowsePrompt`

One 12-byte prompt definition is shared by browse/empty-slot flows; cursor movement recognizes its address for special scroll placement.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_OpenEmptySlot.c`. First packed word is flag/message/alignment bytes, not an ITCM function pointer. Coordinates/alignment are mutable through the cursor helper.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_OpenEmptySlot_020c4f7c.c`.

### `gSlotMenuEditResetPrompt`

One 12-byte prompt is opened with the point-limit check and the finish transition to edit state.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c`. The finish callback role comes from prompt lifecycle, not its old ResetToBrowse name.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_UpdateEditScreen_020c546c.c`.

### `gSlotMenuSecondColumnPrompt`

One prompt uses the second-column predicate and slot-view finish hook; its coordinates are updated for that cursor location.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_HandleSlotSelect.c`. Preserve one-prompt count and typed callback arguments; no bool meaning is assigned to residual hook return.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_HandleSlotSelect_020c8b60.c`.

### `gSlotMenuEquippedRecordPromptHead`

First record of a two-prompt sequence gated by selected-record-equipped when retrying the edit flow.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c`. AdvanceHintPrompt increments the definition pointer by12 to the next physical object; keep both objects contiguous.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_UpdateEditScreen_020c546c.c`.

### `gSlotMenuEquippedRecordPromptTail`

Second 12-byte prompt of the equipped-record sequence; cursor placement updates its own coordinate fields.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_UpdateEditScreen.c`. Its consumer is the count2 sequence headed at 020cd2bc, not an independent onOpen function address.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_UpdateEditScreen_020c546c.c`.

### `gSlotMenuThirdColumnPromptHead`

First record of the two-prompt sequence with third-column predicate and confirmation finish hook.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_HandleSlotSelect.c`. Preserve the 12-byte stride into the following physical tail.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_HandleSlotSelect_020c8b60.c`.

### `gSlotMenuThirdColumnPromptTail`

Second prompt follows the third-column head; it also provides the base used by result-message code to read the following prompt flagIndex at +12.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_HandleSlotSelect.c`. That+12 read reaches 020cd2ec, the next physical prompt. Do not trim/reorder records or silently change this address relationship.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_HandleSlotSelect_020c8b60.c`.

### `gSlotMenuFusionResultPromptHead`

First record of a two-prompt sequence whose check reads the special fusion result and whose finish hook enters edit state.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_OpenSlotPanel.c`. Its first flagIndex byte is also read through the preceding prompt+12 by SlotMenu_ShowResultMessage.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_OpenSlotPanel_020c8934.c`.

### `gSlotMenuFusionResultPromptTail`

Second 12-byte record of the fusion-result prompt sequence; cursor helper updates its coordinates.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_OpenSlotPanel.c`. Count2 is stored in prompt state and decremented by AdvanceHintPrompt; it is not an untyped ownership pointer.

The EU wrapper selects `src/ov076/unclassified_helpers/SlotMenu_OpenSlotPanel_020c8934.c`.

### `gSlotMenuSharedState`

Exact 12-byte BSS object combines current menu reference at +0 and the two tag-text colors at +4/+8.

Evidence: `eu/src/overlays/ov076/calls/SlotMenu_DrawHintText.c`. Direct definition is a 12-byte struct inside the active draw source. Do not use the overlay BSS alignment range as its object size.

### `gItemScreenHelpPrompt`

One 12-byte prompt definition supports help-message opening and its finish callback.

Evidence: `eu/src/overlays/ov077/calls/OpenHelpMessageOrActivate.c`. Packed flag/message/alignment fields are not a function address; onOpen is the separate word at +8.

The EU wrapper selects `src/ov077/unclassified_helpers/OpenHelpMessageOrActivate_020c4b50.c`.

### `gItemScreenRefreshRequestStorage`

The first 24 bytes are copied as refresh arguments when assigning/using a party-slot item.

Evidence: `eu/src/overlays/ov077/calls/UsePartySlotItem.c`. Physical 44 B has 20 B outside that demonstrated request view; retain them without assigning more request fields or padding.

The EU wrapper selects `src/ov077/unclassified_helpers/UsePartySlotItem_020c5dd8.c`.

### `gItemPickerCategoryFilterCodes`

Eight signed bytes map picker modes to a category or negative set selector.

Evidence: `eu/src/overlays/ov077/calls/MenuPanel_ApplyCategoryFilter_020c6c68.c`. Distinct copy of the slot-picker codes; preserve exact signed-byte interpretation.

The EU wrapper selects `src/ov077/unclassified_helpers/MenuPanel_ApplyCategoryFilter_020c6c48.c`.

### `gItemPickerIconGrid`

The shared EU item-row drawer uses this packed {1,2,0,0} grid for item-picker icon frames.

Evidence: `eu/src/overlays/ov077/calls/MenuPanel_DrawItemRows_020c9870.c`. Four-byte physical object and EU aliases are preserved.

The EU wrapper selects `eu/src/overlays/ov076/calls/MenuPanel_DrawItemRows.c`.

### `gItemScreenTierThresholds`

Four thresholds support the mode/session-gated tier comparison against packed-block+0xa.

Evidence: `eu/src/overlays/ov077/calls/IsPartyLevelSufficient_020c7a98.c`. Private level naming does not establish the packed value units; no gameplay level contract is inferred.

The EU wrapper selects `src/ov077/unclassified_helpers/IsPartyLevelSufficient_020c7a78.c`.

### `gItemScreenFrameTiles`

Nine u16 values form three left/middle/right rows for frame tilemap construction.

Evidence: `eu/src/overlays/ov077/calls/BuildItemScreenFrameTilemap.c`. Physical 20 B preserves the extra stored u16 beyond the 18-byte logical row table.

### `gItemScreenSpriteQuadRotation`

Copies identity 3x3 rotation when drawing the sprite region quad.

Evidence: `eu/src/overlays/ov077/calls/DrawSpriteRegionQuad.c`. Separate physical matrix from the other item-image drawing path.

The EU wrapper selects `src/ov077/unclassified_helpers/DrawSpriteRegionQuad_020c6a8c.c`.

### `gItemScreenThresholdRankMap`

Five threshold/value pairs choose and clamp a rank before the selected value is written through SetParamHalf18.

Evidence: `eu/src/overlays/ov077/calls/ApplyItemScreenThresholdRankBonus.c`. Same values as another bank do not establish shared storage; keep <= and rank saturation behavior.

### `gItemPickerOwnerCategorySets`

Owner selects count-plus-four-category records copied into the item-picker custom filter.

Evidence: `eu/src/overlays/ov077/calls/ItemListPanel_Open.c`. Keep all 124 B including the final stored word and caller index precondition.

The EU wrapper selects `eu/../src/ov077/unclassified_helpers/MenuPanel_Open_020c9118.c`, `src/ov077/unclassified_helpers/MenuPanel_Open_020c9118.c`.

### `gItemPickerDefaultCategorySet`

The default negative selector filters IDs 4,5,6 with count 3 and invert FALSE.

Evidence: `eu/src/overlays/ov077/calls/MenuPanel_ApplyCategoryFilter_020c6c68.c`. The fourth stored zero remains present and is not assigned an additional category role.

The EU wrapper selects `src/ov077/unclassified_helpers/MenuPanel_ApplyCategoryFilter_020c6c48.c`.

### `gItemScreenPackedQuadRotation`

Copies identity 3x3 rotation in the packed-argument image renderer.

Evidence: `eu/src/overlays/ov077/calls/DrawItemScreenImageFromPackedArgs.c`. Preserve this object independently of the sprite-region renderer matrix.

### `gItemScreenSharedState`

Exact 12-byte BSS object combines the current item-screen reference with two tagged-text colors at +4/+8.

Evidence: `eu/src/overlays/ov077/calls/ItemScreen_DrawHintText.c`. The first word is accessed through pointer views in init/shutdown; the whole object is not a pointer scalar or 32 B array.

## Reproducible review and validation boundary

Use the bank's `eu/config/arm9/overlays/ovNNN/symbols.txt` and `delinks.txt` to identify each active physical owner. Follow EU aliases and include search roots before shared code. Prompt progression is demonstrated in `src/ov076/unclassified_helpers/OpenHintPrompt_020cbba0.c` and `src/ov076/unclassified_helpers/AdvanceHintPrompt_020caf8c.c`; the result-message base/addend is selected by the EU wrapper.

All 32 DATA objects agree with the existing ELF symbol extents/bytes at the extracted native EU ROM addresses. The two shared-state objects have SHT_NOBITS size 12 and extents within native BSS; this is not a stored ROM-byte comparison. Physical and direct evidence sources are active delink inputs. No new compilation or official gate result is claimed. Integration must preserve the module matches, complete physical extents and sequential/cross-object address relationships.


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
