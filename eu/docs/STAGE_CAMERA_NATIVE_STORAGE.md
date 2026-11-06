# Stage-command and camera storage views

These 25 identifiers name concrete stage-command, animation, grid and camera data. Several logical views cross original physical object boundaries. The names and tables below describe those relationships while retaining the original active sources, physical sizes and every stored value. No layout or type repair is included.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Physical bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov041:20cf4b0 | `data_ov041_020cf4b0` | `gStageItemEbPowerScales` | 16 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf4a8.c` | `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c` |
| ov041:20cf4e0 | `data_ov041_020cf4e0` | `gStageRandomItemCommandCounts` | 16 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf4d8.c` | `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c` |
| ov041:20cf4f0 | `data_ov041_020cf4f0` | `gStageGroupItemEntryCountPowerScales` | 12 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf4f0.c` | `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c` |
| ov041:20cf554 | `data_ov041_020cf554` | `gStageGroupItemArgPowerScales` | 20 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf554.c` | `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c` |
| ov041:20cf568 | `data_ov041_020cf568` | `gStageSingleItemArgPowerScales` | 24 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf568.c` | `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c` |
| ov041:20cf594 | `data_ov041_020cf594` | `gStageRandomItemCommandChoices` | 64 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf580.c` | `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c` |
| ov041:20cf61c | `data_ov041_020cf61c` | `gStageActorAnimationTrackMap` | 144 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf61c.c` | `eu/src/overlays/ov041/calls/GetActorAnimTrack.c` |
| ov041:20cf6b8 | `data_ov041_020cf6b8` | `gStageSetupMemberSpawnOrder` | 36 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf6ac.c` | `eu/src/overlays/ov041/calls/InitMenuScene.c` |
| ov041:20cf720 | `data_ov041_020cf720` | `gStageDashRootNodeName` | 16 | `eu/src/overlays/ov041/data/RodataStrings_ov041_020cf720.c` | `eu/src/overlays/ov041/calls/EntryActionDash.c` |
| ov041:20cf760 | `data_ov041_020cf760` | `gStageSpawnActorRootNodeName` | 16 | `eu/src/overlays/ov041/data/RodataStrings_ov041_020cf760.c` | `eu/src/overlays/ov041/calls/SpawnStageEntryActor.c` |
| ov041:20cf790 | `data_ov041_020cf790` | `gStageSpawnPlayerRootNodeName` | 16 | `eu/src/overlays/ov041/data/RodataStrings_ov041_020cf790.c` | `eu/src/overlays/ov041/calls/SpawnPlayerStageEntryActor.c` |
| ov041:20cf7a0 | `data_ov041_020cf7a0` | `gStageEntryKindTiltValues` | 28 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf7a0.c` | `eu/src/overlays/ov041/calls/SpawnStageEntry.c` |
| ov041:20cf7bc | `data_ov041_020cf7bc` | `gStageGridRowZPositions` | 48 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf7a0.c` | `eu/src/overlays/ov041/calls/GetStageGridPosition.c` |
| ov041:20cf82c | `data_ov041_020cf82c` | `gStageGridColumnXPositions` | 96 | `eu/src/overlays/ov041/data/Rodata_ov041_020cf7ec.c` | `eu/src/overlays/ov041/calls/GetStageGridPosition.c` |
| ov041:20cff40 | `data_ov041_020cff40` | `gStageCommandTimers` | 8 | `eu/src/overlays/ov041/data/bss/Bss_ov041_020cff40.c` | `eu/src/overlays/ov041/calls/StageStateCommandMenu.c` |
| ov041:20cff48 | `data_ov041_020cff48` | `gStageEntryRenderCapturePrefix` | 24 | `eu/src/overlays/ov041/data/bss/Bss_ov041_020cff40.c` | `eu/src/overlays/ov041/calls/DrawStageEntryModels.c` |
| ov041:20cff60 | `data_ov041_020cff60` | `gStageEntryRenderCaptureTail` | 32 | `eu/src/overlays/ov041/data/bss/Bss_ov041_020cff40.c` | `eu/src/overlays/ov041/calls/UpdateTimedPressPanel.c` |
| ov044:20d0e10 | `data_ov044_020d0e10` | `gPanelCameraPathPresets` | 144 | `eu/src/ov044/data/Data_ov044_020d0de0.c` | `eu/src/overlays/ov044/calls/EnterPanelState.c` |
| ov044:20d0ea0 | `data_ov044_020d0ea0` | `gPanelCameraTransitionPathStorage` | 32 | `eu/src/ov044/data/Data_ov044_020d0ea0.c` | `eu/src/overlays/ov044/calls/StartPanelTransition.c` |
| ov046:20c33d0 | `data_ov046_020c33d0` | `gCameraModePresetHead` | 4 | `eu/src/ov046/data/Data_ov046_020c33d0.c` | `eu/src/overlays/ov046/calls/Camera_ComputeFollowDistance.c` |
| ov046:20c33d4 | `data_ov046_020c33d4` | `gCameraModePresetHeightHead` | 4 | `eu/src/ov046/data/Data_ov046_020c33d4.c` | `eu/src/overlays/ov046/calls/Camera_GetPresetHeight.c` |
| ov046:20c33d8 | `data_ov046_020c33d8` | `gCameraModePresetTail` | 296 | `eu/src/ov046/data/Data_ov046_020c33d4.c` | `eu/src/overlays/ov046/calls/Camera_GetModeDistance.c` |
| ov047:20c72a4 | `data_ov047_020c72a4` | `gCameraShakePresetAmountHead` | 4 | `eu/src/ov047/data/Rodata_ov047_020c72a4.c` | `eu/src/overlays/ov047/calls/Camera_UpdateFollowLookAt.c` |
| ov047:20c72a8 | `data_ov047_020c72a8` | `gCameraShakePresetTargetHead` | 4 | `eu/src/ov047/data/Rodata_ov047_020c72a8.c` | `eu/src/overlays/ov047/calls/Camera_SetTrackingMode.c` |
| ov047:20c72ac | `data_ov047_020c72ac` | `gCameraShakePresetTail` | 40 | `eu/src/ov047/data/Rodata_ov047_020c72a8.c` | `eu/src/overlays/ov047/calls/Camera_UpdateFollowLookAt.c` |

## Queued item commands, animation and grid

StartQueuedItemCommand is the direct consumer of the item tables. Commands 0xe4..0xe6 use both the command-arg multiplier and a multiplier selected by active primary entry count minus one. Commands 0xe1..0xe3 and 0xe7..0xea use their separate arg multiplier; 0xeb uses another table. Command 0xec chooses an ID from a four-word row using its count table and the existing random-range division. Numeric IDs identify the branches without assigning unsupported item names.

The source performs no bounds validation here. Preserve every stored entry, including count row 0 value 0xa000, group-scale row 0 value 0x15, unusual first power-scale values and -1 command sentinels. The naming does not establish all arg/row values as valid inputs and does not authorize normalizing those values.

The animation map is a three-by-24 sequence of two-byte body/effect track pairs for actor kinds 0xff,0xfe,0xfd, indexed by 0xff-kind. Body/effect columns have distinct consumers and negative track values mean no selection in the relevant caller. Preserve its current one-byte-plus-byte-array physical declaration.

The nine-member spawn-order permutation selects setup members before spawning. The three independent Root strings are used by dash-effect, actor-shadow and player-shadow dictionary lookup; their visible text is equal but each physical object remains 16 bytes. Entry-kind tilt data is byte-packed, while the two grid tables contain four rows of three Z positions and four rows of six X positions. GetStageGridPosition sets Y to zero.

## Shared command timers and render capture

gStageCommandTimers is exactly two BSS words. The first is reused as a wait timer by command-menu, queued-command and item states. The second counts held-R frames in the command menu and triggers when the value is greater than 30. It is not a generic session counter or an independent timer allocation.

The typed StageRenderCapture view starts at ov041:020cff48 and is 36 bytes on the NDS layout. Its original physical BSS objects are split:

| Physical object | Native range | Demonstrated logical portion | Remaining contract |
|---|---|---|---|
| gStageEntryRenderCapturePrefix | [020cff48,020cff60), 24 B | packed action-capture union state; entry reference at +0x10; cast timer at +0x14 | Per-action union meanings stay tied to their actual consumers. |
| gStageEntryRenderCaptureTail | [020cff60,020cff80), 32 B | first 12 B are panelOffset, logical offsets +0x18/+0x1c/+0x20 | Remaining 20 B are unspecified, not proved padding. |

DrawStageEntryModels stores the matched entry reference in the +0x10 word before model drawing. ModelRenderCallbackKindC reads that same reference through its partial tracked-node-manager view. This does not make the whole capture an actor pointer or a separately owned node manager.

UpdateTimedPressPanel writes the three panelOffset components and PlacePressPanel reads them when the player defends. The extracted Thumb ROM confirms the cross-object writes: at 020c44ba it stores at base+0x18, at 020c44ca at base+0x1c and at 020c44ce at base+0x20. The literal at 020c45f0 is 020cff48, giving effective addresses 020cff60/64/68. Keep both physical definitions and the strided typed view; do not reduce the logical structure to the prefix size or merge the BSS objects as part of naming.

## Panel-camera static and dynamic paths

Overlay044 stores six static PanelPath records at 020d0e10. Each record is 24 bytes: two VecFx32 values called start/end by the consumers. EnterPanelState copies the chosen record and derives camera axes from its end. SnapshotPanelPose and StepPanelTransition use the same logical table.

The following object at 020d0ea0 supplies logical path index 6. StartPanelTransition sets state to 6, copies exactly 24 transition bytes there and calls SnapshotPanelPose, which reads path[6].end. Thus the first 24 bytes are the dynamic seventh path; the physical object is still 32 bytes and its remaining 8 bytes have no additional role established here. It is not seven static presets, a second camera pointer or padding to discard.

## Mode and shake preset fragments

| Bank / logical base | Stride | Physical split | Demonstrated columns |
|---|---:|---|---|
| ov046:020c33d0 | 12 B | 4-byte head, 4-byte height head, 296-byte tail | +0 follow-distance input; +4 height getter; +8 mode-distance getter |
| ov047:020c72a4 | 12 B | 4-byte amount head, 4-byte target head, 40-byte tail | +0 amount subtracted; +4 initial target; +8 duration threshold |

The ov046 consumers prove a common stride and separate column uses; their legacy private type labels disagree about some unused field names. This document does not infer every column's units, a complete valid mode range or the role of every trailing word from the 304-byte physical concatenation.

The ov047 concatenation is exactly four 12-byte records. Camera_SetTrackingMode starts its view one word later and reads the middle column with the same stride; the update reads amount and duration from the unshifted view. Preserve the two heads, tail, pointer bases/addends and caller-selected index. No new bounds check or table deduplication is included.

## Per-object evidence and limits

### `gStageItemEbPowerScales`

Item command 0xeb multiplies its action power by this fx32 scale indexed by command arg.

Evidence: `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c`. Four stored words; no unchecked arg values are normalized or given named item levels.

### `gStageRandomItemCommandCounts`

Item 0xec uses count[arg]*1000 as the random range before choosing a command from its corresponding row.

Evidence: `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c`. Keep stored row0 value0xa000 and all bounds/preconditions unchanged; do not replace it with3 based on the other rows.

### `gStageGroupItemEntryCountPowerScales`

Commands 0xe4..0xe6 multiply power by the scale indexed by active primary entry count minus1.

Evidence: `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c`. Three stored fx32 values are separate from the command-arg power tables.

### `gStageGroupItemArgPowerScales`

Commands 0xe4..0xe6 select a power scale using command arg before the active-entry-count scale.

Evidence: `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c`. Preserve all five words including row0 value0x15; no arg validation or mathematical simplification is included.

### `gStageSingleItemArgPowerScales`

Commands 0xe1..0xe3 and 0xe7..0xea select the action power multiplier by command arg.

Evidence: `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c`. Six stored words remain exact, including both0x28cd values and the nonmonotone first entry.

### `gStageRandomItemCommandChoices`

Command 0xec selects a row of four stored command IDs and a random column from its corresponding count.

Evidence: `eu/src/overlays/ov041/calls/StartQueuedItemCommand.c`. Four physical rows include row0 special values and -1 sentinels. No claim that all rows/columns are valid input; preserve the exact range/truncation logic.

### `gStageActorAnimationTrackMap`

Kinds 0xfd..0xff index a three-row table of 24 two-byte body/effect track pairs; PlayActorEffectAnimation reads the effect column for kinds 0xff/0xfd.

Evidence: `eu/src/overlays/ov041/calls/GetActorAnimTrack.c`. Signed -1 track sentinels are retained. The existing physical one-byte-plus-byte-array declaration is not restructured.

The EU wrapper selects `src/ov041/animation/GetActorAnimTrack_020c3698.c`.

### `gStageSetupMemberSpawnOrder`

The nine-value permutation controls which setup->members entry is spawned at each of the nine iteration positions.

Evidence: `eu/src/overlays/ov041/calls/InitMenuScene.c`. A spawn order, not a sort key or a resource ID mapping.

The EU wrapper selects `src/ov041/unclassified_helpers/InitMenuScene_020bc5c0.c`.

### `gStageDashRootNodeName`

The dash effect looks up this Root name in the acting entry model dictionary before enabling its model-node variant.

Evidence: `eu/src/overlays/ov041/calls/EntryActionDash.c`. 16-byte physical string capacity is retained, not shortened to five bytes.

### `gStageSpawnActorRootNodeName`

Looks up Root in the spawned actor model dictionary and stores the index for its linked shadow.

Evidence: `eu/src/overlays/ov041/calls/SpawnStageEntryActor.c`. Separate physical Root string from dash/player-spawn names.

The EU wrapper selects `src/ov041/unclassified_helpers/SpawnStageEntryActor_020c18cc.c`.

### `gStageSpawnPlayerRootNodeName`

Looks up Root in the player actor model dictionary and stores the linked shadow node index.

Evidence: `eu/src/overlays/ov041/calls/SpawnPlayerStageEntryActor.c`. 16-byte physical string is distinct even though its visible content is equal to other Root strings.

### `gStageEntryKindTiltValues`

Entry kind indexes a packed byte value transformed as (0x5a-value)*0xb6 for its facing tilt; FaceStageEntryAcross uses the same table.

Evidence: `eu/src/overlays/ov041/calls/SpawnStageEntry.c`. Physical28bytes use u32 packing. Do not reinterpret as seven scalar angles or assign gameplay meanings to kinds.

The EU wrapper selects `src/ov041/unclassified_helpers/SpawnStageEntry_020c09cc.c`.

### `gStageGridRowZPositions`

Four rows of three fx32 coordinates provide the grid z coordinate selected by stage and row.

Evidence: `eu/src/overlays/ov041/calls/GetStageGridPosition.c`. Stage/row preconditions remain with callers; the x-coordinate table is a separate object.

The EU wrapper selects `src/ov041/unclassified_helpers/GetStageGridPosition_020c2b5c.c`.

### `gStageGridColumnXPositions`

Four rows of six fx32 coordinates provide the grid x coordinate selected by stage and column; y is set to 0.

Evidence: `eu/src/overlays/ov041/calls/GetStageGridPosition.c`. Keep24coordinates and their exact signs/rounding, separate from the row-z table.

The EU wrapper selects `src/ov041/unclassified_helpers/GetStageGridPosition_020c2b5c.c`.

### `gStageCommandTimers`

Word0 is a shared state wait timer; word1 counts held-R frames in the command menu and triggers the transition when greater than 30.

Evidence: `eu/src/overlays/ov041/calls/StageStateCommandMenu.c`. Exactly two physical BSS words; other stage states reuse word0 for waits, so do not call it a single menu delay only.

### `gStageEntryRenderCapturePrefix`

The 24-byte physical prefix contains the action-capture unions, entry pointer at +0x10 and cast timer at +0x14; draw records the entry and the render callback reads that word.

Evidence: `eu/src/overlays/ov041/calls/DrawStageEntryModels.c`. The logical StageRenderCapture continues12bytes into the next physical BSS object. Do not shrink the logical view to24 B or merge physical definitions.

### `gStageEntryRenderCaptureTail`

The first 12 bytes are StageRenderCapture.panelOffset at logical offset0x18, written by UpdateTimedPressPanel and used when placing the defending press panel.

Evidence: `eu/src/overlays/ov041/calls/UpdateTimedPressPanel.c`. Physical tail is32 B: only its first12 B are established by the logical capture view; remaining20 B stay unspecified and are not padding.

### `gPanelCameraPathPresets`

Six static 24-byte records each contain start/end VecFx32; state selection copies a path and computes camera axes from its end.

Evidence: `eu/src/overlays/ov044/calls/EnterPanelState.c`. The seventh logical path at index6 is runtime transition storage in the following physical object, not a missing seventh static record.

The EU wrapper selects `src/ov044/panel_state/EnterPanelState_020d0144.c`.

### `gPanelCameraTransitionPathStorage`

Sets panel state 6 and copies 24 transition bytes here before SnapshotPanelPose accesses path[6].end; the first 24 B are the seventh logical path record.

Evidence: `eu/src/overlays/ov044/calls/StartPanelTransition.c`. Physical object32 B includes8 B beyond the demonstrated24 B transition path. Keep extent and do not claim those extra bytes are padding or another record.

The EU wrapper selects `src/ov044/panel_state/StartPanelTransition_020d02c0.c`.

### `gCameraModePresetHead`

The first physical word starts the stride 12mode-parameter view used by follow-distance and mode-distance consumers.

Evidence: `eu/src/overlays/ov046/calls/Camera_ComputeFollowDistance.c`. The first-column follow-distance use is proved; the legacy pitch label in another view is not treated as an independent semantic fact.

The EU wrapper selects `src/ov046/shared_engine/Camera_ComputeFollowDistance_020c1a70.c`.

### `gCameraModePresetHeightHead`

The second physical word starts the height column; getter reads a word at this address plus index*12 and conditionally adds0x2000.

Evidence: `eu/src/overlays/ov046/calls/Camera_GetPresetHeight.c`. This is only the first height word physically; the logical strided view extends into the tail object.

### `gCameraModePresetTail`

Starts at the third word of the same mode-parameter view; the mode-distance getter reads column +8 with stride 12.

Evidence: `eu/src/overlays/ov046/calls/Camera_GetModeDistance.c`. Physical296B tail is retained. Record stride is proved, but a complete valid mode range and every trailing word role are not inferred from physical size.

### `gCameraShakePresetAmountHead`

The first word starts the stride 12shake-preset view; after a duration threshold the amount column reduces the current shake target.

Evidence: `eu/src/overlays/ov047/calls/Camera_UpdateFollowLookAt.c`. This head is one word only. Preserve the separate next word and tail that complete the logical four-record view.

The EU wrapper selects `src/ov047/camera/Camera_UpdateFollowLookAt_020c5548.c`.

### `gCameraShakePresetTargetHead`

Tracking mode 3 selects this column with stride 12 and stores its value in two tracking fields, initializing the shake state.

Evidence: `eu/src/overlays/ov047/calls/Camera_SetTrackingMode.c`. The table view is one-word-skewed from the amount view; do not create a separate independent table or rebind addends.

The EU wrapper selects `src/ov047/camera/Camera_SetTrackingMode_020c3558.c`.

### `gCameraShakePresetTail`

The first tail word is the duration column of record 0; the complete 48 B sequence forms four 12-byte amount/value/duration records.

Evidence: `eu/src/overlays/ov047/calls/Camera_UpdateFollowLookAt.c`. 40-byte physical tail is distinct from the two4-byte heads. Do not merge objects or assume a new callback/engine ABI.

## Reproducible review and validation boundary

Locate each native identity in `eu/config/arm9/overlays/ovNNN/symbols.txt` and its active physical source range in the same bank's `delinks.txt`. Read the EU wrapper before shared code so its renamed DATA bases and aliases are applied. The full render-capture layout is in `eu/src/overlays/ov041/StageEntryRender.h`; its panel offset is written/read in `eu/src/overlays/ov041/calls/UpdateTimedPressPanel.c`.

The 22 DATA objects agree with existing ELF bytes at the extracted native EU addresses. The three BSS objects have SHT_NOBITS extents within the native overlay BSS; this is an extent check, not a comparison of stored ROM bytes. Active source and direct evidence owners were checked in delinks. This review does not claim a new compilation or official gate result. Integration must preserve all module matches and physical object boundaries.


## Byte-exact validation

86 DATA identities retain their source paths, native sizes and storage.
100/102 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 163 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
