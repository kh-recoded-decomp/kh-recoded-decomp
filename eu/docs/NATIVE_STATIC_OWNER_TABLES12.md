# Callback lists, scene task descriptors and static selection tables (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Proven table roles

The VBlank callback-node word at+0x14 is invoked as code despite its inherited kind label. Its storage has eight32-byte records, not sixteen. Stage static tables are typed by their actual vector, selector and slot-default consumers. The results and ov037 descriptors are TaskObject classes; misleading native Movie/Comm/PXI callback labels do not change that ownership. Native declarations, padding, bytes, filenames and relocations stay unchanged.

## Inventory and evidence

### `main:020569d8` → `gVBlankCallbackListHeads`

Previous label `data_020569d8`; existing ELF size **8 bytes**. Source: `eu/src/data/bss/Bss_main_020569d8.c`.

8-byte BSS array of two native callback-list head words.

RegisterChannelEntry appends a node and publishes the head for the selected channel; UnregisterChannelEntry updates the head after removal. SelectActiveEntry selects a head, and OSi_VBlankInterruptHandler traverses the active list.

Limits: The physical head array contains two entries. No bounds check is introduced for the channel/index arguments, and unused native declarations do not establish four allocated channels.

Pinned references:

- `eu/src/calls/RegisterChannelEntry.c` → `src/arm9/nitro_os/RegisterChannelEntry_02000f84.c`; reference line(s) 17, 28, 48, 52.
- `eu/src/calls/SelectActiveEntry.c` → `src/arm9/nitro_os/SelectActiveEntry_020011a4.c`; reference line(s) 9, 19.
- `eu/src/calls/UnregisterChannelEntry.c` → `src/arm9/nitro_os/UnregisterChannelEntry_02001030.c`; reference line(s) 17, 26.
- `eu/src/data/bss/Bss_main_020569d8.c`; reference line(s) 4.

### `main:020569e0` → `gVBlankCallbackNodeStorage`

Previous label `data_020569e0`; existing ELF size **256 bytes**. Source: `eu/src/data/bss/Bss_main_020569d8.c`.

256-byte BSS storage for eight 32-byte callback nodes: inUse word 0, name[16] at 4, callback word 0x14, next pointer 0x18 and previous pointer 0x1c. Native channel row stride is four nodes (128 bytes).

RegisterChannelEntry selects a four-node row, finds an unused node, copies sixteen name bytes, stores its third argument at+0x14 and links it. OSi_VBlankInterruptHandler invokes node+0x14 as callback(void). UnregisterChannelEntry searches the same row by bounded name comparison.

Limits: The inherited field/parameter name kind is misleading: that word is called as a callback. Source declares [4][4], but the ELF allocation holds two rows of four; preserve 256 bytes and the native type in this rename-only block. Register has no full-row failure guard before using its final slot.

Pinned references:

- `eu/src/calls/RegisterChannelEntry.c` → `src/arm9/nitro_os/RegisterChannelEntry_02000f84.c`; reference line(s) 18, 29.
- `eu/src/calls/UnregisterChannelEntry.c` → `src/arm9/nitro_os/UnregisterChannelEntry_02001030.c`; reference line(s) 18, 27.
- `eu/src/data/bss/Bss_main_020569d8.c`; reference line(s) 3.

### `ov021:020b4ec8` → `gSelectionSlotPositions`

Previous label `data_ov021_020b4ec8`; existing ELF size **216 bytes**. Source: `eu/src/ov021/data/Rodata_ov021_020b4ea4.c`.

216 initialized bytes: two sets of nine native VecFx32 values (twelve bytes per vector).

GetSelectionSlotPosition obtains the selection record, uses its overlaySet byte as the outer index and caller slot as the inner index, then copies one vector to out.

Limits: No new coordinate-space name or bounds check is introduced. Preserve all eighteen vectors, including zero entries; this table is not an array of actor pointers.

Pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4ea4.c`; reference line(s) 3.
- `eu/src/overlays/ov021/calls/GetSelectionSlotPosition.c` → `src/ov021/unclassified_helpers/GetSelectionSlotPosition_020a91b8.c`; reference line(s) 9, 14.

### `ov021:020b4fc8` → `gModelSetAnimationTrackOrder`

Previous label `data_ov021_020b4fc8`; existing ELF size **20 bytes**. Source: `eu/src/ov021/data/Rodata_ov021_020b4fc8.c`.

20 initialized bytes: five u32 selectors in order 0,1,2,4,3.

ApplyModelSetAnimations copies this list and calls SetModelAnimationFrameWithSingleWrap for each selector on the primary model resource; it also applies to the non-NULL submodel when hasSub is nonzero.

Limits: This is the traversal order passed to the animation-track frame helper, not a list of file/resource IDs. Preserve the exact order and all five words.

Pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4fc8.c`; reference line(s) 3.
- `eu/src/overlays/ov021/calls/ApplyModelSetAnimations.c` → `src/ov021/object_state/ApplyModelSetAnimations_020a9c50.c`; reference line(s) 14, 26.

### `ov021:020b4fdc` → `gOrientedModelUpAxis`

Previous label `data_ov021_020b4fdc`; existing ELF size **12 bytes**. Source: `eu/src/ov021/data/Rodata_ov021_020b4fdc.c`.

12 initialized bytes, the fixed-point vector (0,0x1000,0).

DrawOrientedModel normalizes nonzero direction to forward, computes side=cross(thisAxis,forward), normalizes side and computes up=cross(forward,side) to fill its rotation matrix.

Limits: No new fallback is added for a direction parallel to the axis. Keep exact fixed-point bits and existing matrix construction order.

Pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4fdc.c`; reference line(s) 3.
- `eu/src/overlays/ov021/calls/DrawOrientedModel.c` → `src/ov021/animation/DrawOrientedModel_020ab370.c`; reference line(s) 19, 41.

### `ov021:020b5014` → `gEffectSlotDefaults`

Previous label `data_ov021_020b5014`; existing ELF size **24 bytes**. Source: `eu/src/ov021/data/Rodata_ov021_020b5014.c`.

24 initialized bytes: three native {timedParam,groupBase} word pairs: {3,4},{1,0},{1,9}.

SetupEffectSlots uses each slot groupBase to offset an effect selector passed to EnsureEffectGroup. For a timed selector, it passes timedParam to CreateTimedEntryPair and stores the returned handle.

Limits: The pairs configure three separate slots; they are not six pointers or animation timing units. Meaning beyond these caller roles remains unspecified.

Pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b5014.c`; reference line(s) 56.
- `eu/src/overlays/ov021/calls/SetupEffectSlots.c` → `src/ov021/shared_engine/SetupEffectSlots_020ad384.c`; reference line(s) 46, 52.

### `ov021:020b5124` → `gNearPlayerGroundSearchDirections`

Previous label `data_ov021_020b5124`; existing ELF size **96 bytes**. Source: `eu/src/ov021/data/Rodata_ov021_020b5124.c`.

96 initialized bytes: eight VecFx32 direction vectors.

ScriptOp_PlaceNearPlayerOnGround tries all eight directions. It scales each by the requested distance for horizontal placement tests, then casts downward at the candidate and returns a hit position; fallback is the current player position.

Limits: This is direction data, not a 96-byte query template. No normalization, direction reordering, ground-kind classification or guarantee of a successful placement is added.

Pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b5124.c`; reference line(s) 3.
- `eu/src/overlays/ov021/calls/ScriptOp_PlaceNearPlayerOnGround.c` → `src/ov021/script_ops/ScriptOp_PlaceNearPlayerOnGround_020b1714.c`; reference line(s) 44, 75, 83.

### `ov021:020b5184` → `gNearbyOpenCellSearchDirections`

Previous label `data_ov021_020b5184`; existing ELF size **96 bytes**. Source: `eu/src/ov021/data/Rodata_ov021_020b5184.c`.

96 initialized bytes: eight VecFx32 direction vectors.

ScriptOp_FindNearbyOpenCell scales these vectors by 0x3000 from a snapped cell center to generate candidate sphere tests, then performs downward collision queries for open candidates.

Limits: Preserve all eight vectors and search order. Do not infer unit length or merge this table with another equal-sized direction table.

Pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b5184.c`; reference line(s) 3.
- `eu/src/overlays/ov021/calls/ScriptOp_FindNearbyOpenCell.c` → `src/ov021/script_ops/ScriptOp_FindNearbyOpenCell_020b1374.c`; reference line(s) 80, 149, 159.

### `ov034:020be940` → `gResultsScreenTaskHandle`

Previous label `data_ov034_020be940`; existing ELF size **4 bytes**. Source: `eu/src/ov034/data/Data_ov034_020be940.c`.

4-byte initialized task handle with sentinel 0xffffffff.

CreateResultsScreenTask stores the TaskObject returned for the neighboring results-scene descriptor. The legacy MobiClip_SrcIsOpen/Close wrappers use this same task handle.

Limits: These wrapper names do not make the handle a movie decoder or file pointer. Preserve its native word and sentinel; callback identity is established by the descriptor.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020be940.c`; reference line(s) 5.
- `eu/src/overlays/ov034/calls/CreateResultsScreenTask.c` → `src/ov034/shared_engine/MobiClip_SrcOpen_020bddf0.c`; reference line(s) 3, 6.
- `eu/src/overlays/ov034/calls/MobiClip_SrcClose_020bde8c.c` → `src/ov034/shared_engine/MobiClip_SrcClose_020bde6c.c`; reference line(s) 3, 8, 9.
- `eu/src/overlays/ov034/calls/MobiClip_SrcIsOpen_020bde70.c` → `src/ov034/shared_engine/MobiClip_SrcIsOpen_020bde50.c`; reference line(s) 3, 8.

### `ov034:020be954` → `gResultsScreenTaskClass`

Previous label `data_ov034_020be954`; existing ELF size **20 bytes**. Source: `eu/src/ov034/data/Data_ov034_020be954.c`.

20-byte native class descriptor: class/subclass packed word 0x0002000e, InitResultsScene constructor+4, CloseResultsSession destructor+8, work size 0x6d98 at+0xc and NULL heapRef+0x10.

CreateResultsScreenTask passes this descriptor to CreateTaskObject and stores the returned task handle. The descriptor targets the results-scene initialization and release functions in bank034.

Limits: Keep all callback relocations and native source declarations. Constructor-returned update callback remains separate from descriptor+8.

Pinned references:

- `eu/src/ov034/data/Data_ov034_020be954.c`; reference line(s) 8.
- `eu/src/overlays/ov034/calls/CreateResultsScreenTask.c` → `src/ov034/shared_engine/MobiClip_SrcOpen_020bddf0.c`; reference line(s) 2, 6.

### `ov037:020bb6c0` → `gOv037SceneTaskHandle`

Previous label `data_ov037_020bb6c0`; existing ELF size **4 bytes**. Source: `eu/src/ov037/data/Data_ov037_020bb6c0.c`.

4-byte initialized task handle with sentinel 0xffffffff.

The ov037 task factory stores CreateTaskObject result using the neighboring descriptor. ReleasePxiChannel destroys the task and restores -1; IsPxiChannelActive passes the handle to Obj_GetWord28 and tests nonzero.

Limits: The inherited PXI names are not proof of a physical communication-channel handle. This is a TaskObject handle for the ov037 scene.

Pinned references:

- `eu/src/ov037/data/Data_ov037_020bb6c0.c`; reference line(s) 16.
- `eu/src/overlays/ov037/calls/IsPxiChannelActive.c` → `src/ov037/unclassified_helpers/IsPxiChannelActive_020babec.c`; reference line(s) 3, 10.
- `eu/src/overlays/ov037/calls/ReleasePxiChannel.c` → `src/ov037/unclassified_helpers/ReleasePxiChannel_020bac10.c`; reference line(s) 3, 8, 9.
- `eu/src/overlays/ov037/calls/CreateContinueSceneTask.c` → `src/ov037/reviewed_helpers/func_ov037_020bab78.c`; reference line(s) 3, 6.

### `ov037:020bb6c4` → `gOv037SceneTaskClass`

Previous label `data_ov037_020bb6c4`; existing ELF size **20 bytes**. Source: `eu/src/ov037/data/Data_ov037_020bb6c0.c`.

20-byte native class descriptor: packed class/subclass 0x0002000e, BeginCommSession constructor+4, ShutdownCommChannelAndAudio destructor+8, work size 0x24 and NULL heapRef.

The ov037 factory supplies this descriptor to CreateTaskObject. Its constructor publishes current scene work, copies request fields, sets up menu3d display, starts its child task and returns RunCommStepMachine.

Limits: Bank-scoped scene ownership is proven; no network role is inferred from inherited Comm/PXI callback labels. Preserve descriptor fields, callbacks and work size.

Pinned references:

- `eu/src/ov037/data/Data_ov037_020bb6c0.c`; reference line(s) 8.
- `eu/src/overlays/ov037/calls/CreateContinueSceneTask.c` → `src/ov037/reviewed_helpers/func_ov037_020bab78.c`; reference line(s) 2, 6.


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
