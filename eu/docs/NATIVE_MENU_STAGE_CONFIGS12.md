# Menu and field configuration DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The menu owns its tile table and two background containers. Its state callbacks, native SP2 filename tags and wide play-time format remain distinct allocations. The ov030 tables supply initial selection items and speed ratios; their inherited Movie/level labels do not establish resource or progression roles. The ov040 probe consumes a start pointer and delta vector through the real collision API.

## Inventory and evidence

### `ov039:020be750` → `gMenuKeyRepeatConfig`

Previous label `data_ov039_020be750`; size **4 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be750.c`.

4 initialized bytes: two signed halfwords {12, 2}.

InitOverlayState copies this pair and passes it to InitKeyRepeatState for its input state. That callee clears 0x1a bytes and stores the two nonnegative values in record halfwords 1 and 2; negative values select defaults 15 and 4.

Limits: This names the configuration, without claiming a wall-clock duration or assigning units to the two counts.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be750.c`; line(s) 27.
- `eu/src/overlays/ov039/calls/InitOverlayState.c`; line(s) 64, 101.

### `ov039:020be754` → `gMenuMainBgLayerIds`

Previous label `data_ov039_020be754`; size **12 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be750.c`.

12 initialized bytes: three 32-bit tile-table layer IDs {9, 10, 11}.

LoadBgLayerSet3 copies the IDs and gMainBgScreenLoaders. For each ID it clears the tile row, obtains its current buffer and uploads that buffer with the corresponding main-engine loader.

Limits: These are tile-table layer IDs, not file IDs or engine register numbers. The size passed to the upload remains the runtime row size.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be750.c`; line(s) 23.
- `eu/src/overlays/ov039/calls/LoadBgLayerSet3.c` → `src/ov039/widget_layers/LoadBgLayerSet3_020bab8c.c`; line(s) 13, 21.

### `ov039:020be760` → `gMenuSubBgLayerIds`

Previous label `data_ov039_020be760`; size **16 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be750.c`.

16 initialized bytes: four 32-bit tile-table layer IDs {24, 25, 26, 27}.

LoadBgLayerSet4 copies these IDs and gOv039SubBgScreenLoaders and uploads the four corresponding tile-table row buffers.

Limits: Keep the separate main/sub mappings and the original loader order.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be750.c`; line(s) 19.
- `eu/src/overlays/ov039/calls/LoadBgLayerSet4.c` → `src/ov039/widget_layers/LoadBgLayerSet4_020bac24.c`; line(s) 13, 21.

### `ov039:020be770` → `gMenuBackgroundContainerConfig`

Previous label `data_ov039_020be770`; size **20 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be750.c`.

20 initialized bytes: capacities {48, 32, 16}, followed by two native function-pointer words.

InitOverlayState passes a copy to InitBackgroundContainer for both mainTracker and subTracker. The callee allocates entryCapacity * 0x38, spriteCapacity * 0x30 and tagCapacity * 16 bytes. The last two words relocate to DrawWidgetOnScreenLayer and ClearWidgetOnScreenLayer.

Limits: The callback invokers and the contract of generic parameter0c/parameter10 are not established here; do not infer init/draw/cleanup slot semantics from the two callee names.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be750.c`; line(s) 11.
- `eu/src/overlays/ov039/calls/InitOverlayState.c`; line(s) 63, 100.

### `ov039:020be784` → `gMenuImageFileTags`

Previous label `data_ov039_020be784`; size **28 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be750.c`.

28 initialized bytes holding nine three-byte string slots and one final padding byte.

LoadSlotImagePair copies the table, selects tags[kind + 1] and formats both shared and language-specific SP2 paths. It opens the resulting pair into slots[slot] and slots[slot + 1].

Limits: The accepted kind range is a caller responsibility; the function adds no bounds check. Preserve duplicate tags, the fixed three-byte stride and final byte.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be750.c`; line(s) 6.
- `eu/src/overlays/ov039/calls/LoadSlotImagePair.c` → `src/ov039/widget_layers/LoadSlotImagePair_020bb754.c`; line(s) 12, 20.

### `ov039:020be7a0` → `gMenuTileTableLayerIds`

Previous label `data_ov039_020be7a0`; size **28 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be7a0.c`.

28 initialized bytes: seven 32-bit IDs {9, 10, 11, 24, 25, 26, 27}.

InitOverlayState copies this table into a TileTableDesc with count 7, width 32, height 32 and rowLength 0, then calls InitTileTableFrom for its tileTable.

Limits: This combined configuration is independent of the two upload subsets stored at be754 and be760; do not merge native objects.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be7a0.c`; line(s) 26.
- `eu/src/overlays/ov039/calls/InitOverlayState.c`; line(s) 65, 102.

### `ov039:020be7bc` → `gMenuRuntimeStateHandlers`

Previous label `data_ov039_020be7bc`; size **40 bytes**; source `eu/src/ov039/data/Rodata_ov039_020be7a0.c`.

40 initialized bytes: ten native function-pointer slots; slot 0 is NULL.

The state dispatcher at EU ov039:020bb708 indexes this table with GetStateC9C4, tests the selected pointer for NULL and invokes it without arguments. Other slots refer to update, initialization, loading, exit and shutdown state adapters.

Limits: No bounds check is present. The native dispatcher forwards the selected handler return in r0, while later callers may overwrite it; do not impose a single portable return type from the local void prototype.

Pinned references:

- `eu/src/ov039/data/Rodata_ov039_020be7a0.c`; line(s) 13.
- `eu/src/overlays/ov039/calls/DispatchMenuPhaseUpdate.c` → `src/ov039/reviewed_helpers/func_ov039_020bb6e8.c`; line(s) 2, 5.

### `ov039:020be9e4` → `gMenuPlayTimeFormatStorage`

Previous label `data_ov039_020be9e4`; size **60 bytes**; source `eu/src/ov039/data/Data_ov039_020be9e4.c`.

60 initialized bytes: the first 15 halfwords contain the terminated wide format %02d:%02d:%02d, followed by 15 zero halfwords.

FormatPlayTimeText clamps seconds to 3599999, derives hours/minutes/seconds and calls OS_SNPrintf_0202e094 with this format. The EU wrapper aliases Text_VSNPrintf to Text_VSNPrintfWide, proving the halfword representation despite its local char pointer declaration.

Limits: Keep all 60 bytes and the writable DATA section. This rename does not fix the char prototype, change formatting width, shorten the padding or alter the clamped seconds returned by the formatter.

Pinned references:

- `eu/src/ov039/data/Data_ov039_020be9e4.c`; line(s) 5.
- `eu/src/overlays/ov039/calls/FormatPlayTimeText.c` → `src/ov039/unclassified_helpers/FormatPlayTimeText_020be64c.c`; line(s) 4, 11.

### `ov030:020bcf64` → `gDraggedActorSpeedBonusRatios`

Previous label `data_ov030_020bcf64`; size **8 bytes**; source `eu/src/ov030/data/Rodata_ov030_020bcf64.c`.

8 initialized bytes: two Q12 words {0x000000d8, 0x00000333}.

UpdateDraggedActorState copies this pair when player entry flag 0x10 is set, selects count - 1, adds FX_Mul(speed, bonus) to speed and passes bonus + 0x1000 to ApplyTimeScaledSpeed.

Limits: Only the mechanical ratio usage is proved. No item or ability name is assigned, and the original unchecked count-based selection remains.

Pinned references:

- `eu/src/ov030/data/Rodata_ov030_020bcf64.c`; line(s) 8.
- `eu/src/overlays/ov030/calls/UpdateDraggedActorState.c` → `src/ov030/shared_engine/UpdateDraggedActorState_020bb5a0.c`; line(s) 69, 125.

### `ov030:020bcf6c` → `gDragSceneDefaultSelectionItems`

Previous label `data_ov030_020bcf6c`; size **32 bytes**; source `eu/src/ov030/data/Rodata_ov030_020bcf64.c`.

32 initialized bytes: four native pairs {(0xd9, 1), (0xdb, 1), (0xda, 1), (0xdc, 1)}.

InitMovieSelectionItems copies all four pairs to the first selection record list, narrowing each first word to a signed halfword and each second word to a byte. It increments count to 4 and initializes selection to -1.

Limits: The legacy Movie and level labels do not prove movie resources or RPG level semantics for this list. Keep both words per source item and do not shrink the static table to the narrower runtime fields.

Pinned references:

- `eu/src/ov030/data/Rodata_ov030_020bcf64.c`; line(s) 3.
- `eu/src/overlays/ov030/calls/InitMovieSelectionItems.c` → `src/ov030/movie/InitMovieSelectionItems_020bc424.c`; line(s) 36, 45.

### `ov040:020be1c0` → `gAreaMeshResetValueTemplate`

Previous label `data_ov040_020be1c0`; size **4 bytes**; source `eu/src/ov040/data/Rodata_ov040_020be1c0.c`.

4 initialized bytes {8, 0, 0, 0}.

ResetAreaMeshValues copies this template for each area mesh, replaces byte 1 with the mesh index and passes it to SetWorldMeshEntryValueByName using the formatted area name.

Limits: The value is a packed native mesh-entry update, not a BOOL. The game role of each remaining byte is not inferred.

Pinned references:

- `eu/src/ov040/data/Rodata_ov040_020be1c0.c`; line(s) 7.
- `eu/src/overlays/ov040/calls/ResetAreaMeshValues.c` → `src/ov040/unclassified_helpers/ResetAreaMeshValues_020bcc60.c`; line(s) 21, 40.

### `ov040:020be1c4` → `gAreaRewardQueryDelta`

Previous label `data_ov040_020be1c4`; size **12 bytes**; source `eu/src/ov040/data/Rodata_ov040_020be1c0.c`.

12 initialized bytes: VecFx32-compatible words {0, -100 * 0x1000, 0}.

FindActorRewardValue copies this triple and places its address in the second pointer word of the query. QueryModelSegmentCollision consumes that prefix as MoverCastParams, where word 1 is delta; it sets radius to zero and forwards to QueryModelCollision.

Limits: The local ActorQuery.actorId and NameTriple.names labels are misleading: word 0 is the start pointer and word 1 is the delta pointer. The source input remains a native word in this rename block; no ID or actor ownership semantics are inferred from the legacy parameter name.

Pinned references:

- `eu/src/ov040/data/Rodata_ov040_020be1c0.c`; line(s) 3.
- `eu/src/overlays/ov040/calls/FindActorRewardValue.c` → `src/ov040/shared_engine/FindActorRewardValue_020bd9fc.c`; line(s) 33, 40.

The collision query layout is additionally proved by `eu/src/collision/CollisionQueries.h` and `eu/src/calls/QueryModelSegmentCollision.c`. The background-container allocation sizes are established by `eu/src/overlays/ov027/calls/InitBackgroundContainer.c` and its header. The wide formatter binding is in `eu/src/calls/OS_SNPrintf_0202e094.c`.


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
