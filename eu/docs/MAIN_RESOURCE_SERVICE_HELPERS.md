# MAIN resource and service helper names

This block covers 22 matched helpers. The heap/texture lifetime chain is in
[MODEL_RESOURCE_OWNERSHIP.md](MODEL_RESOURCE_OWNERSHIP.md). Other operations
retain their exact copy, submission, flag, list and update order. The names
state the observed operation rather than an unproved gameplay meaning.

## Interfaces and native boundaries

The old free/sound chain is in-place heap resizing. Its wrapper now exposes the
real third input and size return using the existing `HeapRecord` type. The
separate stream/audio and panel helpers below keep their real owners; equal
numeric fields in unrelated objects are not combined.

The container-list adapters pass a head view at container +0x10 and a node in
live r1. Their old single-argument C declarations omit that node. The actual
list helpers return void C results and the adapters retain residual-register
return declarations; no success or ownership return is inferred here. These
are documented native boundaries to recover consistently in a host port.

Queued screen/palette submission is distinct from copying RAM data or waiting
for upload completion. Panel and indexed-record masks are documented literally
where a higher-level state name has not been proved. This work does not rewrite
those protocols or synthesize additional method parameters.

Evidence paths are repository-relative; current helper source paths are relative
to `eu/`. Shared source filenames and obsolete categories remain historical;
read them through the current EU aliases.

### `QueuePanelScreenTransferAndUpdateSound`

Previously `func_020281c8`; 24 bytes, thumb. Source: `src/calls/QueuePanelScreenTransferAndUpdateSound.c`.

- Passes gPanelState +0x0c to the screen-transfer helper, then calls SoundMgr_Update. Evidence: `src/arm9/unclassified_helpers/func_020281b4.c`:7.
- The helper queues screen rawData and its byte count for VRAM transfer. Evidence: `src/arm9/display_registers/func_020284bc.c`:5.

Enqueues a screen copy; no queue flush occurs here. SoundMgr_Update is an observable second operation.

### `CopyPanelPageScreenRect`

Previously `func_0202845c`; 84 bytes, thumb. Source: `src/calls/CopyPanelPageScreenRect.c`.

- Selects page-2/default source and copies a clipped rectangle into RAM screen rawData using a 0x18-byte page record. Evidence: `src/arm9/panel_state/func_02028448.c`:25.
- The EU alias resolves the rectangle-copy call to NNS_G2dBGLoadScreenRect. Evidence: `eu/src/calls/CopyPanelPageScreenRect.c`:1.

If gPanelState +0xbc is zero, pages other than page 2 are skipped; the control field meaning remains unspecified. The destination is RAM screen data; no VRAM transfer is queued by this helper.

### `QueueScreenDataVramTransfer`

Previously `func_020284d0`; 20 bytes, thumb. Source: `src/calls/QueueScreenDataVramTransfer.c`.

- Queues type 0x0b, destination 0, source screen+0x0c and size screen+8, with screen read from context+0x5c. Evidence: `src/arm9/display_registers/func_020284bc.c`:5.
- The related typed view identifies screen+8 as szByte and screen+0x0c as rawData. Evidence: `src/arm9/panel_state/func_02028448.c`:3.

Submission does not prove completion. Keep transfer kind 0x0b numeric until its enum mapping is checked.

### `InitActiveRecordEntryFromTemplate`

Previously `func_02028dd8`; 40 bytes, thumb. Source: `src/calls/InitActiveRecordEntryFromTemplate.c`.

- Copies four bytes, sets second-halfword bit 0 and clears first-halfword bits 5..15. Evidence: `src/arm9/state_management/func_02028dc4.c`:5.
- The native matched RecordEntry view identifies active and levelProgress; kind, variant, level and category occupy the preserved bits. Evidence: `eu/src/calls/AddRecordItem.c`:3.
- Insertion uses the helper on an inactive entry, then sets its category. Evidence: `eu/src/calls/AddRecordItem.c`:50.
- The merge caller also uses this helper and separately restores level progress. Evidence: `eu/src/calls/ApplyRecordMerge.c`:1.

Initializes one four-byte RecordEntry, not the entire save. No capacity check or category assignment occurs inside this helper.

### `GetDisplaySetting`

Previously `func_02029f7c`; 16 bytes, arm. Source: `src/calls/GetDisplaySetting.c`.

- Returns data_02060388 +8. Evidence: `src/arm9/shared_engine/func_02029f68.c`:1.
- The established SetDisplaySetting setter writes that exact word under its existing control condition. Evidence: `src/arm9/shared_engine/SetDisplaySetting_02029f28.c`:1.

Uses the established getter/setter pair without inventing a visual meaning for the setting. Separate from main/sub brightness words.

### `SubmitResourcePaletteUpload`

Previously `func_0202d218`; 68 bytes, arm. Source: `src/calls/SubmitResourcePaletteUpload.c`.

- Calls the palette-upload hook with resource+ofsPlttData, low16(vramKey)<<3 and sizePltt<<3; then sets plttInfo.flag bit 0. Evidence: `src/arm9/runtime/func_0202d204.c`:1.
- NNSG3dResTex places plttInfo at +0x2c, sizePltt +0x30, flag +0x32, ofsPlttData +0x38. Evidence: `include/nnsys/g3d.h`:136.
- The typed caller allocates/assigns the palette key before calling this helper. Evidence: `src/arm9/library_nns_g3d/SetupResourceTextures_0202cedc.c`:65.
- The queue-mode helper selects the texture and palette upload hooks. Evidence: `src/arm9/core_small/func_0202c690.c`:1.

The flag is set immediately after the hook call; it does not prove queued/DMA completion. A typed NNSG3dResTex argument is justified.

### `ResizeExpandedHeapBlock`

Previously `FreeExpandedHeapBlock`; 352 bytes, arm. Source: `src/calls/ResizeExpandedHeapBlock.c`.

- Takes heap, existing block and size. Rounds to four bytes, returns equal size unchanged, and returns zero if adjacent space cannot satisfy growth. Evidence: `src/arm9/library_nitro_nns/func_02013164.c`:98.
- Growth consumes adjacent free storage; shrink recycles the tail and restores old size if recycling fails. Returns actual resulting block size. Evidence: `src/arm9/library_nitro_nns/func_02013164.c`:130.

The old name falsely describes a free. The pointer stays fixed; this is not a relocating realloc. Failed growth returns zero; unsuccessful shrink can return old size.

### `ResizeExpandedHeapBlockWithHeapRef`

Previously `NNS_SndPlayerPause_0202a294`; 16 bytes, arm. Source: `src/calls/ResizeExpandedHeapBlockWithHeapRef.c`.

- EU aliases the apparent sound callee to the expanded-heap resize implementation. Evidence: `eu/src/calls/ResizeExpandedHeapBlockWithHeapRef.c`:1.
- ROM loads R0 from [R0] and tail-branches to the resize target; R1 and R2 are preserved. Confirmed by the native ROM call and current EU aliases.
- Even with the old imported prototype, the consumed size is exposed as in_r2 and the first word is cast to a heap head. Confirmed by the native ROM call and current EU aliases.

This is not a sound API. The previous NNSSndHandle/BOOL prototype was accidental and incomplete. The defining EU wrapper now exposes heap reference, block pointer and requested byte count through HeapRecord.h and returns the resize byte-size word. The trim adapters retain legacy return spellings; their register propagation must be distinguished from source-level result contracts.

### `TrimArchiveBeforeTexturePayload`

Previously `func_0202d410`; 80 bytes, arm. Source: `src/calls/TrimArchiveBeforeTexturePayload.c`.

- Finds section 7 entry 0 and its texture block, then resizes to resTex+word[0x14]-archiveBase. Evidence: `src/arm9/runtime_data_utilities/func_0202d3fc.c`:5.
- Texture resource +0x14 is texInfo.ofsTex, the byte offset to ordinary texture payload. Evidence: `include/nnsys/g3d.h`:155.
- ROM constructs the new byte count in R2 and calls the in-place heap resize wrapper; R3 carries the old option word. Confirmed by the native ROM call and current EU aliases.

Returns early if section entry or texture block is absent. Resizes the allocation without copying bytes or rewriting the archive header size. The forwarded R3 option word is not consumed by the resize target. No transfer queue flush occurs; retained upload source lifetimes need caller-level review.

### `InitModelWithOptionalTextureTrim`

Previously `func_0202ed94`; 28 bytes, arm. Source: `src/calls/InitModelWithOptionalTextureTrim.c`.

- Stores the resource slot at model+0x74 and calls InitModelInstance(model,0,trimOption,1,extra). Evidence: `src/arm9/object_factory/func_0202ed80.c`:3.
- With a null textureHeader and nonzero trim option, the initializer trims after resource acquisition, then initializes rendering and animation bindings. Evidence: `src/arm9/model_animation/InitModelInstance_0202eb84.c`:79.

The wrapper third argument controls optional trimming, not a texture pointer. The extra argument is forwarded unchanged; full meaning remains unspecified.

### `InitModelUsingTextureHeader`

Previously `func_0202edb0`; 32 bytes, arm. Source: `src/calls/InitModelUsingTextureHeader.c`.

- Stores resource slot at model+0x74; passes supplied textureHeader with trimOption 0 and setup flag 1. Evidence: `src/arm9/object_factory/func_0202ed9c.c`:3.
- Argument 2 is forwarded to resource acquisition and bypasses the null-texture trimming path. Evidence: `src/arm9/model_animation/InitModelInstance_0202eb84.c`:79.
- The acquisition helper treats argument 2 as a textureHeader and may locate/copy its texture block header. Evidence: `src/arm9/archive_startup/func_0202c940.c`:19.

The supplied value is a header pointer, not a boolean texture flag. A cached block may be reused; not every call copies the supplied header. Do not merge resource counters at offsets 0,2,4.

### `TrimModelArchiveBeforeTexturePayload`

Previously `func_0202edd0`; 28 bytes, arm. Source: `src/calls/TrimModelArchiveBeforeTexturePayload.c`.

- Reads model+0x74 and forwards slot.data +0x0c, heap reference +8 and halfword +6 to the trim helper. Evidence: `src/arm9/shared_engine/func_0202edbc.c`:1.
- The destination operation resizes the allocation at the texture-payload boundary. Evidence: `src/arm9/runtime_data_utilities/func_0202d3fc.c`:5.

Does not upload textures or release the shared record reference. The current int return is residual R0 from a void-style chain; no logical success result is proven. Keep slot halfword +6 opaque.

### `SetModelMaterialColorScaleEnabled`

Previously `func_0202f5a4`; 36 bytes, arm. Source: `src/calls/SetModelMaterialColorScaleEnabled.c`.

- Sets or clears model/scene-node flag 0x40 from a boolean input. Evidence: `src/arm9/core_small/func_0202f590.c`:2.
- The draw path tests that bit and applies node->colorScale before drawing. Evidence: `eu/src/calls/SceneNode_Draw.c`:78.
- The immediate render path uses the same bit and color-scale field. Evidence: `src/ov001/shared_engine/SceneNode_DrawImmediate_0208f4f4.c`:52.

Enables the override without setting its value. All other flags are preserved.

### `SetModelMaterialColorScale`

Previously `Obj_SetHalfwordFC`; 8 bytes, arm. Source: `src/calls/SetModelMaterialColorScale.c`.

- Stores the low halfword of value to model+0xfc and returns the model address. Evidence: `src/arm9/leaf_research/func_0202f5b4.c`:1.
- The native matched view places colorScale at +0xfc. Evidence: `eu/src/calls/SceneNode_Draw.c`:7.
- The draw path applies colorScale when flag 0x40 is set. Evidence: `eu/src/calls/SceneNode_Draw.c`:82.

Does not enable the color-scale override flag. Do not propagate unused legacy extra parameters to new portable interfaces.

### `InitPersistentActorSlot`

Previously `func_0203670c`; 24 bytes, thumb. Source: `src/calls/InitPersistentActorSlot.c`.

- Clears slot+0x10 through ClearWordAndReturnTrue, then ORs slot.flags at +8 with 0x41. Evidence: `src/arm9/shared_engine/func_020366f8.c`:3.
- Initializes the embedded actor slot before optionally linking it as a root. Evidence: `src/ov041/unclassified_helpers/InitRecordOwnerSlots_020ce1a8.c`:13.
- Flag 0x40 exits conditional shutdown before model or base destruction. Evidence: `src/arm9/shared_engine/Obj_ConditionalShutdown_020368c8.c`:15.
- Registry-wide shutdown also excludes flag-0x40 slots. Evidence: `src/arm9/shared_engine/ShutdownAllActorSlots_0203666c.c`:36.

Persistent means excluded from these normal shutdown paths, not an immortal allocation. Initializes only the leading embedded word and two flags. The separate meaning of flag 0x01 remains unspecified.

### `LinkContainerListNode`

Previously `func_020367c4`; 16 bytes, arm. Source: `src/calls/LinkContainerListNode.c`.

- Forwards the list-head address at container+0x10 to LinkNodeAtListHead. Evidence: `src/arm9/shared_engine/func_020367b0.c`:1.
- ROM exposes the incoming R1 node and list-head address in R0. Confirmed by the native ROM call and current EU aliases.

Logical inputs are container and node; the one-argument C declaration omits live R1. No allocation or ownership transfer occurs. Residual R0 list-head address is not a success boolean.

### `UnlinkContainerListNode`

Previously `func_020367d4`; 16 bytes, arm. Source: `src/calls/UnlinkContainerListNode.c`.

- Forwards the list-head address at container+0x10 to UnlinkDoublyLinkedNode. Evidence: `src/arm9/shared_engine/func_020367c0.c`:1.
- ROM exposes the incoming R1 node and list-head address in R0. Confirmed by the native ROM call and current EU aliases.

Logical inputs are container and node; the one-argument C declaration omits live R1. Unlinks without freeing the node. Residual R0 list-head address is not a success boolean.

### `ApplyActorMovementAndUpdateSpatialIndex`

Previously `func_02038e80`; 58 bytes, thumb. Source: `src/calls/ApplyActorMovementAndUpdateSpatialIndex.c`.

- On successful movement update, applies the 12-byte position and reinserts an existing spatial node through the registry world tree. Evidence: `src/arm9/shared_engine/func_02038e6c.c`:14.
- EU aliases identify movement, position, registry and quad-tree callees. Evidence: `eu/src/calls/ApplyActorMovementAndUpdateSpatialIndex.c`:1.

False movement result leaves position/spatial membership unchanged. Forwarded argument remains opaque; no velocity or time unit is inferred. No complete Entity layout is asserted.

### `IsSoundHandleCurrentAndBound`

Previously `func_0204dc50`; 88 bytes, arm. Source: `src/calls/IsSoundHandleCurrentAndBound.c`.

- Uses high handle byte as a 0x20-byte slot index, requires nonzero flags and low24 ID equality, then tests player!=NULL. Evidence: `src/arm9/reviewed_helpers/func_0204dc3c.c`:5.
- Native view proves flags+0x14, ID+0x18, player+0x1c and 0x20-byte stride. Evidence: `eu/src/calls/AllocSoundHandleSlot.c`:5.
- Allocation assigns flags and a 24-bit serial ID. Evidence: `eu/src/calls/AllocSoundHandleSlot.c`:60.

Tests identity and bound player pointer, not active/audible playback. Original helper has no slot index bounds check. Checks nonzero flags, not specifically SOUND_SLOT_ACTIVE.

### `FreeObjectSlotBuffers`

Previously `func_0204eef4`; 42 bytes, thumb. Source: `src/calls/FreeObjectSlotBuffers.c`.

- Frees combined buffer +0x1c if present, otherwise independent buffers +0x14/+0x18; clears all three pointers. Evidence: `src/arm9/core_small/func_0204eee0.c`:4.
- Object slots embed this resource block at +4 and have stride 0x68. Evidence: `src/arm9/shared_engine/ObjManager_FreeSlot_0204f014.c`:3.
- Full slot release delegates buffer freeing here and handles unlink/bookkeeping separately. Evidence: `src/arm9/shared_engine/ObjManager_FreeSlot_0204f014.c`:20.
- List clearing also passes the embedded block at node+4. Evidence: `src/arm9/linked_list/FreeAndClearNodeList_0204ef0c.c`:5.

Argument is the embedded resource block, not the full slot or 0x8c-byte indexed-record pool. Combined ownership excludes separate frees. Does not free or unlink the slot container.

### `RefreshFirstSelectionPlayerStats`

Previously `func_0204f854`; 28 bytes, thumb. Source: `src/calls/RefreshFirstSelectionPlayerStats.c`.

- Calls ComputePlayerStats(gGameState,selection0,recompute=0,scaleParam=1). Evidence: `src/arm9/reviewed_helpers/func_0204f840.c`:7.
- False recompute reuses cached map bonusStats, then rebuilds final stats from level base and cached bonus. Evidence: `src/arm9/unclassified_helpers/ComputePlayerStats_02050b30.c`:74.
- Applies stat caps, mode-6 scaling and final HP adjustment. Evidence: `src/arm9/unclassified_helpers/ComputePlayerStats_02050b30.c`:146.

Selection 0 is proven; a specific player identity is not inferred. Does not rescan map chips. Callee mutates cached finalStats as well as output.

### `RefreshFirstSelectionAbilityTable`

Previously `func_0204fbb4`; 44 bytes, arm. Source: `src/calls/RefreshFirstSelectionAbilityTable.c`.

- Acquires cached map layout, rebuilds selection0 table+0x13c and releases the layout reference. Evidence: `src/arm9/overlay_selection/func_0204fba0.c`:14.
- Clears/rebuilds tagged entries from cached chip counts, active chips and available party abilities. Evidence: `src/arm9/unclassified_helpers/BuildAbilityTable_02050ea4.c`:49.

Selection 0 is proven; a specific player identity is not inferred. Temporary map acquisition is balanced. Does not recompute cached chip counts itself.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/calls/QueuePanelScreenTransferAndUpdateSound.c QueuePanelScreenTransferAndUpdateSound --thumb
python tools/verify_idx.py src/calls/CopyPanelPageScreenRect.c CopyPanelPageScreenRect --thumb
python tools/verify_idx.py src/calls/QueueScreenDataVramTransfer.c QueueScreenDataVramTransfer --thumb
python tools/verify_idx.py src/calls/InitActiveRecordEntryFromTemplate.c InitActiveRecordEntryFromTemplate --thumb
python tools/verify_idx.py src/calls/GetDisplaySetting.c GetDisplaySetting
python tools/verify_idx.py src/calls/SubmitResourcePaletteUpload.c SubmitResourcePaletteUpload
python tools/verify_idx.py src/calls/ResizeExpandedHeapBlock.c ResizeExpandedHeapBlock
python tools/verify_idx.py src/calls/ResizeExpandedHeapBlockWithHeapRef.c ResizeExpandedHeapBlockWithHeapRef
python tools/verify_idx.py src/calls/TrimArchiveBeforeTexturePayload.c TrimArchiveBeforeTexturePayload
python tools/verify_idx.py src/calls/InitModelWithOptionalTextureTrim.c InitModelWithOptionalTextureTrim
python tools/verify_idx.py src/calls/InitModelUsingTextureHeader.c InitModelUsingTextureHeader
python tools/verify_idx.py src/calls/TrimModelArchiveBeforeTexturePayload.c TrimModelArchiveBeforeTexturePayload
python tools/verify_idx.py src/calls/SetModelMaterialColorScaleEnabled.c SetModelMaterialColorScaleEnabled
python tools/verify_idx.py src/calls/SetModelMaterialColorScale.c SetModelMaterialColorScale
python tools/verify_idx.py src/calls/InitPersistentActorSlot.c InitPersistentActorSlot --thumb
python tools/verify_idx.py src/calls/LinkContainerListNode.c LinkContainerListNode
python tools/verify_idx.py src/calls/UnlinkContainerListNode.c UnlinkContainerListNode
python tools/verify_idx.py src/calls/ApplyActorMovementAndUpdateSpatialIndex.c ApplyActorMovementAndUpdateSpatialIndex --thumb
python tools/verify_idx.py src/calls/IsSoundHandleCurrentAndBound.c IsSoundHandleCurrentAndBound
python tools/verify_idx.py src/calls/FreeObjectSlotBuffers.c FreeObjectSlotBuffers --thumb
python tools/verify_idx.py src/calls/RefreshFirstSelectionPlayerStats.c RefreshFirstSelectionPlayerStats --thumb
python tools/verify_idx.py src/calls/RefreshFirstSelectionAbilityTable.c RefreshFirstSelectionAbilityTable
bash tools/gate.sh
```

All entrypoints receive the official ROM-index check. Integration also compares
affected production texts, resolved relocation targets/types and addends to the
saved baseline, and requires unchanged hashes for all 108 linked modules.
