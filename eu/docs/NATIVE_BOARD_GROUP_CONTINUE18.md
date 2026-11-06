# Board, group and continue-menu DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The board uses six static node positions, runtime task work and a borrowed session cursor. Graphics-file pointers remain alive as sources of queued transfers until the explicit release path. The native pointer storage retains its opaque tail. Group helpers use byte patterns, weighted result codes and partial palette segments; their source word declarations do not establish a larger element width.

The ground probe delta is a fixed downward displacement, not a unit direction. Its misleading local length field is actually overwritten at the radius slot by the real segment-query adapter. Continue-menu message tables contain indices and configuration, not font/palette ownership.

## Inventory and evidence

### `ov024:020b7384` → `gBoardDirectionScreenOffsets`

Previous label `data_ov024_020b7384`; size **32 bytes**; source `eu/src/ov024/data/Rodata_ov024_020b7360.c`.

32 RO bytes: four pairs of signed screen-coordinate offsets.

BuildBoardLayout selects the pair by cursor.directions[i] and adds it to the board node position before CreateDefaultObjectSlot, then rotates the sprite by the same direction times -0x4000.

Limits: These coordinates are passed as integer positions; fixed-point conversion is applied separately by cursor-position readers. Keep the four directional pairs.

Direct/base-view references:

- `eu/src/ov024/data/Rodata_ov024_020b7360.c`; line(s) 6.
- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 103, 213.

### `ov024:020b73a4` → `gBoardNodeScreenX0`

Previous label `data_ov024_020b73a4`; size **4 bytes**; source `eu/src/ov024/data/Rodata_ov024_020b73a4.c`.

4 RO bytes: first X coordinate of the six-node screen-position table.

BuildBoardLayout, GetCursorScreenPos and UpdateBoardScreen access six X/Y pairs from this base. Cursor/goal position readers add the runtime origin and shift by 12.

Limits: This first word is not the entire table. The remaining eleven words reside in the following 44-byte object.

Direct/base-view references:

- `eu/src/ov024/data/Rodata_ov024_020b73a4.c`; line(s) 28.
- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 100, 220, 221, 234, 235.
- `eu/src/overlays/ov024/calls/GetCursorScreenPos.c` → `src/ov024/unclassified_helpers/GetCursorScreenPos_020b7288.c`; line(s) 27, 32, 33.
- `eu/src/overlays/ov024/calls/UpdateBoardScreen.c` → `src/ov024/unclassified_helpers/UpdateBoardScreen_020b6df4.c`; line(s) 89, 189, 190.

### `ov024:020b73a8` → `gBoardNodeScreenPositionTail`

Previous label `data_ov024_020b73a8`; size **44 bytes**; source `eu/src/ov024/data/Rodata_ov024_020b73a4.c`.

44 RO bytes: first node Y coordinate followed by five complete X/Y pairs.

Together with the four-byte prefix this forms six eight-byte node positions. The board layout and cursor readers reach these values through the c73a4 base and eight-byte stride.

Limits: Keep the native split; do not infer eleven separate nodes from the eleven-word definition.

Direct/base-view references:

- `eu/src/ov024/data/Rodata_ov024_020b73a4.c`; line(s) 22.
- `eu/src/ov024/data/Rodata_ov024_020b73a4.c`; line(s) 28.
- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 100, 220, 221, 234, 235.
- `eu/src/overlays/ov024/calls/GetCursorScreenPos.c` → `src/ov024/unclassified_helpers/GetCursorScreenPos_020b7288.c`; line(s) 27, 32, 33.
- `eu/src/overlays/ov024/calls/UpdateBoardScreen.c` → `src/ov024/unclassified_helpers/UpdateBoardScreen_020b6df4.c`; line(s) 89, 189, 190.

### `ov024:020b73d4` → `gBoardNodeLinkDirections`

Previous label `data_ov024_020b73d4`; size **72 bytes**; source `eu/src/ov024/data/Rodata_ov024_020b73a4.c`.

72 RO bytes: six rows of three signed direction selectors, including -1 sentinels.

BuildBoardLayout uses each selector to test cursor.links[node][direction] and, for nonnegative linked entries, choose the rotated cell sprite resource.

Limits: The table is a drawing/link selector map, not the mutable board adjacency state. Preserve negative entries and six-by-three indexing.

Direct/base-view references:

- `eu/src/ov024/data/Rodata_ov024_020b73a4.c`; line(s) 14.
- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 101, 211.

### `ov024:020b741c` → `gBoardGapConnectorConfigs`

Previous label `data_ov024_020b741c`; size **128 bytes**; source `eu/src/ov024/data/Rodata_ov024_020b73a4.c`.

128 RO bytes: eight records {node,linkedNode,linkDirection,sprite}.

BuildBoardLayout uses each record when the destination node is empty but the referenced neighboring link is active, then creates a connector sprite at the destination node with resource sprite+0x5b.

Limits: No world-space geometry or gameplay movement path is inferred from this UI connector table.

Direct/base-view references:

- `eu/src/ov024/data/Rodata_ov024_020b73a4.c`; line(s) 3.
- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 102, 212.

### `ov024:020b74a0` → `gBoardScreenTaskDescriptor`

Previous label `data_ov024_020b74a0`; size **20 bytes**; source `eu/src/ov024/data/Data_ov024_020b74a0.c`.

20 initialized DATA bytes: class/subclass 0x000e0018, CreateBoardScreen, DestroyBoardScreen, work size 0x6700 and final NULL.

The panel-mode descriptor table and results-screen code pass this record to CreateTaskObject, including argument 0x7b for the standalone mode. CreateBoardScreen obtains/clears its 0x6700-byte task work and returns StartBoardScreen.

Limits: The descriptor, TaskObject handle and 12-byte board globals are separate objects. Preserve the constructor-return state-pointer ABI even though the DATA file declares callback symbols as void.

Direct/base-view references:

- `eu/src/ov024/data/Data_ov024_020b74a0.c`; line(s) 8.
- `eu/src/overlays/ov001/data/tables/gPanelModeDataPointers.c`; line(s) 4, 10.
- `eu/src/overlays/ov034/calls/CloseResultsScreen.c`; line(s) 23, 44.
- `eu/src/overlays/ov034/calls/UpdateResultsScreen.c`; line(s) 4, 21.

### `ov024:020b7540` → `gBoardScreenGlobals`

Previous label `data_ov024_020b7540`; size **12 bytes**; source `eu/src/overlays/ov024/data/bss/Bss_ov024_020b7540.c`.

12 BSS bytes: board task-work pointer, ready word and session-buffer cursor pointer.

CreateBoardScreen stores current task work and SessionBuffer_GetAddress(10). BuildBoardLayout clears/sets ready while rebuilding resources and objects; cursor helpers read the same state/cursor. DestroyBoardScreen releases owned resources and clears the leading pointer.

Limits: The ready word is not a heap handle. The globals do not contain the 0x6700-byte task work or own the borrowed session buffer.

Direct/base-view references:

- `eu/src/overlays/ov024/calls/BlitBoardWidgetAndFinishPendingTeardown.c`; line(s) 13, 18, 19, 21.
- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 98, 137, 138, 140, 143, 145, 147, 148, 152, 153, 155, 159, 160, 162, 163, 164, 170, 171, 172, 173, 179, 187, 188, 189, 190, 194, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 218, 219, 220, 221, 222, 223, 224, 232, 233, 234, 235, 236, 239, 240.
- `eu/src/overlays/ov024/calls/ClearBoardWidgetTileArea.c`; line(s) 8, 12.
- `eu/src/overlays/ov024/calls/CreateBoardScreen.c`; line(s) 54, 91, 93, 94, 98, 99, 104, 108, 111, 117, 118, 120, 122, 123, 126, 127, 129, 130, 131, 132, 133, 134, 135, 136, 137, 139, 142, 146, 148, 149, 150, 151, 152, 153.
- `eu/src/overlays/ov024/calls/DestroyBoardScreen.c` → `src/ov024/unclassified_helpers/DestroyBoardScreen_020b6d78.c`; line(s) 15, 29, 32, 35, 36, 37, 38, 42, 43, 45.
- `eu/src/overlays/ov024/calls/GetCursorScreenPos.c` → `src/ov024/unclassified_helpers/GetCursorScreenPos_020b7288.c`; line(s) 26, 32, 33, 34.
- `eu/src/overlays/ov024/calls/ReleaseSubObjectIfActive.c` → `src/ov024/unclassified_helpers/ReleaseSubObjectIfActive_020b5800.c`; line(s) 3, 7, 8, 9.
- `eu/src/overlays/ov024/calls/RerollBoardSlots.c` → `src/ov024/board_setup/RerollBoardSlots_020b5f0c.c`; line(s) 37, 65, 89.
- `eu/src/overlays/ov024/calls/ResetBoardCursor.c` → `src/ov024/unclassified_helpers/ResetBoardCursor_020b72e4.c`; line(s) 10, 21, 22.
- `eu/src/overlays/ov024/calls/SetupBoardTextLayer.c` → `src/ov024/unclassified_helpers/SetupBoardTextLayer_020b664c.c`; line(s) 26, 43, 47, 48, 49, 50, 52, 56, 58.
- `eu/src/overlays/ov024/calls/StartBoardScreen.c` → `src/ov024/unclassified_helpers/StartBoardScreen_020b6b40.c`; line(s) 16, 29, 32, 35, 38.
- `eu/src/overlays/ov024/calls/TeardownContextState.c` → `src/ov024/unclassified_helpers/TeardownContextState_020b6730.c`; line(s) 3, 9, 10, 11, 12, 14.
- `eu/src/overlays/ov024/calls/UpdateBoardHelpText.c`; line(s) 39, 57, 58, 59, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 79, 82, 86, 87, 90, 91, 94, 96, 97, 100, 101, 102, 103, 106, 107, 109, 112, 113, 116, 117, 118, 119, 121, 124.
- `eu/src/overlays/ov024/calls/UpdateBoardScreen.c` → `src/ov024/unclassified_helpers/UpdateBoardScreen_020b6df4.c`; line(s) 88, 136, 137, 138, 141, 146, 147, 148, 149, 153, 155, 160, 173, 175, 178, 179, 186, 188, 189, 190, 191, 192, 195, 196, 201, 202, 204, 205, 206, 207, 208, 209, 210, 211, 212, 216, 218, 227, 229, 230, 233, 234, 235, 240, 241.
- `eu/src/overlays/ov024/data/bss/Bss_ov024_020b7540.c`; line(s) 4.

### `ov024:020b754c` → `gBoardNodeGraphicsBufferStorage`

Previous label `data_ov024_020b754c`; size **52 bytes**; source `eu/src/overlays/ov024/data/bss/Bss_ov024_020b7540.c`.

52 BSS bytes whose first six words are node graphics-file buffer pointers; 28 trailing bytes remain opaque.

CreateBoardScreen initializes six pointer slots. BuildBoardLayout fills slots for present nodes and queues VRAM transfers from loaded character data. ReleaseOverlayResourceSlots frees each non-NULL slot and clears it.

Limits: Keep all 52 bytes and the explicit release lifetime; the queued transfer source is not freed immediately after registration. Do not shrink storage to six pointers.

Direct/base-view references:

- `eu/src/overlays/ov024/calls/BuildBoardLayout.c`; line(s) 99, 177, 181, 192.
- `eu/src/overlays/ov024/calls/CreateBoardScreen.c`; line(s) 55, 96.
- `eu/src/overlays/ov024/calls/ReleaseOverlayResourceSlots.c` → `src/ov024/resource_loading/ReleaseOverlayResourceSlots_020b5dc0.c`; line(s) 3, 10, 11, 12.
- `eu/src/overlays/ov024/data/bss/Bss_ov024_020b7540.c`; line(s) 3.

### `ov032:020bfef8` → `gChallengeConditionCounterIndices`

Previous label `data_ov032_020bfef8`; size **128 bytes**; source `eu/src/ov032/data/Rodata_ov032_020bfef8.c`.

128 RO bytes: thirty-two signed counter-index words.

UpdateChallengeProgress indexes this table by conditionType for its counter-driven cases, reads the selected session counter and compares against the adjusted goal to set progress/success state.

Limits: Calendar/time-only cases use separate RTC paths. Individual challenge names and counter units are not assigned from numeric condition IDs.

Direct/base-view references:

- `eu/src/ov032/data/Rodata_ov032_020bfef8.c`; line(s) 3.
- `eu/src/overlays/ov032/calls/UpdateChallengeProgress.c` → `src/ov032/unclassified_helpers/UpdateChallengeProgress_020bb57c.c`; line(s) 42, 56.

### `ov032:020bff78` → `gGroupTileColumnPatterns`

Previous label `data_ov032_020bff78`; size **20 bytes**; source `eu/src/ov032/data/Rodata_ov032_020bff78.c`.

20 RO bytes: four five-byte column color-index patterns.

DrawTileColumnPattern selects one row by pattern and writes its five entries with SetTilePixel4bpp at y=2..6 for the supplied X coordinate.

Limits: Preserve the byte view and all patterns; the u32 definition is only the native storage representation, not five 32-bit colors.

Direct/base-view references:

- `eu/src/ov032/data/Rodata_ov032_020bff78.c`; line(s) 3.
- `eu/src/overlays/ov032/calls/DrawTileColumnPattern.c` → `src/ov032/object_group/DrawTileColumnPattern_020bb98c.c`; line(s) 3, 10.

### `ov032:020bff8c` → `gGroupPoseChoiceCodes`

Previous label `data_ov032_020bff8c`; size **8 bytes**; source `eu/src/ov032/data/Rodata_ov032_020bff8c.c`.

8 RO bytes: result codes {2,11,7,0,6,5,16,1}.

SelectGroupMemberPose indexes these codes for idle random choices or a cooldown cycle. RollRowDropItem uses the same code set after a weighted selection and adjustment of the final weight.

Limits: The shared codes are not assigned item/fruit names. Preserve both consumers and the byte order despite the two-word source definition.

Direct/base-view references:

- `eu/src/ov032/data/Rodata_ov032_020bff8c.c`; line(s) 8.
- `eu/src/overlays/ov032/calls/RollRowDropItem.c` → `src/ov032/object_group/RollRowDropItem_020bbecc.c`; line(s) 14, 33.
- `eu/src/overlays/ov032/calls/SelectGroupMemberPose.c` → `src/ov032/object_group/SelectGroupMemberPose_020bd02c.c`; line(s) 34, 49, 55.

### `ov032:020bff94` → `gRowStepChanceWeights`

Previous label `data_ov032_020bff94`; size **24 bytes**; source `eu/src/ov032/data/Rodata_ov032_020bff8c.c`.

24 RO bytes read as pairs of failWeight/passWeight bytes.

RollRowStepChance chooses a pair via the row definition sequence; failWeight==0 returns TRUE, passWeight==0 returns FALSE, otherwise it tests passWeight >= random_next_scaled(passWeight+failWeight).

Limits: Preserve the inclusive comparison and final zero pair. Do not replace the native procedure with a nominal percentage test or remove bytes deemed padding.

Direct/base-view references:

- `eu/src/ov032/data/Rodata_ov032_020bff8c.c`; line(s) 3.
- `eu/src/overlays/ov032/calls/RollRowStepChance.c` → `src/ov032/object_group/RollRowStepChance_020bc190.c`; line(s) 25, 32.

### `ov032:020bffac` → `gGroupGroundProbeDelta`

Previous label `data_ov032_020bffac`; size **12 bytes**; source `eu/src/ov032/data/Rodata_ov032_020bffac.c`.

12 RO bytes: Q12 delta vector {0,-100*0x1000,0}.

ProbeGroundBelow passes this vector as query.delta to QueryModelSegmentCollision and uses the returned hit ratio to reconstruct the hit point with AddScaledVector.

Limits: This is not a unit direction. The separate local field called length is at the radius offset and is zeroed by the segment-query adapter; do not scale the stored delta by that misleading name.

Direct/base-view references:

- `eu/src/ov032/data/Rodata_ov032_020bffac.c`; line(s) 3.
- `eu/src/overlays/ov032/calls/ProbeGroundBelow.c` → `src/ov032/object_group/ProbeGroundBelow_020bc6fc.c`; line(s) 18, 25.

### `ov032:020bffd0` → `gGroupModelForwardAxis`

Previous label `data_ov032_020bffd0`; size **12 bytes**; source `eu/src/ov032/data/Rodata_ov032_020bffd0.c`.

12 RO bytes: Q12 vector {0,0,0x1000}.

DrawGroupMemberModel transforms this axis by the member rotation, obtains yaw from FX_Atan2Idx(x,z), and uses that yaw for the following geometry orientation.

Limits: It is a local model-axis seed, not an actor position or the active camera direction.

Direct/base-view references:

- `eu/src/ov032/data/Rodata_ov032_020bffd0.c`; line(s) 3.
- `eu/src/overlays/ov032/calls/DrawGroupMemberModel.c`; line(s) 78, 120.

### `ov032:020c0064` → `gGroupPrimaryPaletteSegment`

Previous label `data_ov032_020c0064`; size **10 bytes**; source `eu/src/ov032/data/Data_ov032_020c0064.c`.

10 initialized DATA bytes: five native palette halfwords.

UploadGroupPaletteSegment selects this address when alternate==0 and queues a 10-byte VRAM transfer of kind 0x0f to offset 0x184.

Limits: Keep the writable DATA section and five halfwords. This is a partial palette segment, not a complete palette allocation.

Direct/base-view references:

- `eu/src/ov032/data/Data_ov032_020c0064.c`; line(s) 10.
- `eu/src/overlays/ov032/calls/UploadGroupPaletteSegment.c` → `src/ov032/object_group/UploadGroupPaletteSegment_020bb8d4.c`; line(s) 3, 14.

### `ov032:020c006e` → `gGroupAlternatePaletteStorage`

Previous label `data_ov032_020c006e`; size **18 bytes**; source `eu/src/ov032/data/Data_ov032_020c0064.c`.

18 initialized DATA bytes: nine palette/storage halfwords.

UploadGroupPaletteSegment chooses this base for nonzero alternate and queues only the first 10 bytes to the same destination as the primary segment.

Limits: Preserve the remaining eight bytes without claiming they are unused or a second transfer. The native allocation is larger than the upload selected by this function.

Direct/base-view references:

- `eu/src/ov032/data/Data_ov032_020c0064.c`; line(s) 5.
- `eu/src/overlays/ov032/calls/UploadGroupPaletteSegment.c` → `src/ov032/object_group/UploadGroupPaletteSegment_020bb8d4.c`; line(s) 4, 12.

### `ov037:020bb66c` → `gContinueMenuTextFrameConfig`

Previous label `data_ov037_020bb66c`; size **16 bytes**; source `eu/src/ov037/data/Rodata_ov037_020bb66c.c`.

16 RO bytes: eight native text-frame configuration halfwords.

DrawMenuTexts copies this configuration, replaces Y and height from the menu row offset, initializes a text layer on BG2 and draws the current entry texts. It later modifies the local frame for a separate title layer.

Limits: The local palette label at +8 is not adopted as a complete field contract. Preserve all eight halfwords and rely on the real text-layer constructor for a portable layout.

Direct/base-view references:

- `eu/src/ov037/data/Rodata_ov037_020bb66c.c`; line(s) 12.
- `eu/src/overlays/ov037/calls/DrawMenuTexts.c` → `src/ov037/unclassified_helpers/DrawMenuTexts_020bb0c8.c`; line(s) 47, 67.

### `ov037:020bb690` → `gContinueTitleMessageBases`

Previous label `data_ov037_020bb690`; size **32 bytes**; source `eu/src/ov037/data/Rodata_ov037_020bb66c.c`.

32 RO bytes: eight signed word-sized message-index bases {4,6,9,11,13,15,17,23}.

DrawMenuTexts selects a base by GetCtxModeByte, adds GetContinueTitleIndex when nonnegative and passes the combined index to GetPackedFileEntry for the localized continue-menu text file.

Limits: These are message-index bases, not pointers or complete title IDs. Keep native indexing assumptions and the independent negative title-index test.

Direct/base-view references:

- `eu/src/ov037/data/Rodata_ov037_020bb66c.c`; line(s) 3.
- `eu/src/overlays/ov037/calls/DrawMenuTexts.c` → `src/ov037/unclassified_helpers/DrawMenuTexts_020bb0c8.c`; line(s) 48, 77.

Additional segment-query layout proof: `eu/src/collision/CollisionQueries.h` and `eu/src/calls/QueryModelSegmentCollision.c`. The task descriptor constructor return follows the existing `CreateTaskObject` / `Obj_Construct` contract.


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
