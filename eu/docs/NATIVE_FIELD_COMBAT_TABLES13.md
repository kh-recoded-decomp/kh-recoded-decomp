# Field combat tables and hit geometry DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The two ledge-grab tables describe vertical and rotated lateral placement. Three separate surface mappings supply sequence-archive numbers, proved by the actor sound callers and SpawnSoundSlot → NNS_SndArcPlayerStartSeqArcEx. Neither inherited Width nor Kind/Palette labels establish the game role by themselves.

The three hit-geometry globals are shared writable storage. Copying the returned shape into an entry does not copy or own its geometry. The command factory table also retains a separately tracked cross-bank relocation-label issue at entry 5.

## Inventory and evidence

### `ov021:020b4dcc` → `gStatusGuardEntryFlagIds`

Previous label `data_ov021_020b4dcc`; size **56 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4dcc.c`.

56 RO bytes: fourteen signed word-sized player-entry flag IDs, with -1 sentinels.

TryApplyStatusEffect indexes this table by attack status. A -1 entry means no per-status guard check; otherwise IsPlayerEntryFlagSet blocks the status when that entry flag is set. The independent flag 0x53 bypasses status processing before this table.

Limits: No individual named status or ability is assigned from numeric IDs. Index bounds and the original status dispatch remain unchanged.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4dcc.c`; line(s) 10.
- `eu/src/overlays/ov021/calls/TryApplyStatusEffect.c` → `src/ov021/object_state/TryApplyStatusEffect_020a78fc.c`; line(s) 37, 59.

### `ov021:020b4e50` → `gLedgeGrabVerticalOffsets`

Previous label `data_ov021_020b4e50`; size **12 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4e50.c`.

12 RO bytes: three signed Q12 offsets returned as the first output of GetTableValuePair.

TryGrabLedge selects by actor sizeClass and subtracts this value from ledge-top Y to place the candidate position. IsLedgeClimbSpaceClear selects the same index and adds the offset to the candidate Y for its clearance boxes.

Limits: The index is a native caller-supplied three-way category; concrete character names are not proved here. Preserve both nullable outputs and the original unchecked indexing of the accessor.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4e50.c`; line(s) 9.
- `eu/src/overlays/ov021/calls/GetTableValuePair.c` → `src/ov021/unclassified_helpers/GetTableValuePair_020a91e8.c`; line(s) 7, 12.

### `ov021:020b4e44` → `gLedgeGrabLateralOffsets`

Previous label `data_ov021_020b4e44`; size **12 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4e44.c`.

12 RO bytes: three signed Q12 offsets returned as the second output of GetTableValuePair.

TryGrabLedge places this value in local offset.x, clears offset.y/z, rotates that vector by the wall-normal yaw and adds it to the candidate target. The vertical offset is handled independently.

Limits: This is a signed lateral placement offset, not a width/radius despite one local caller variable being named width. No universal axis in world coordinates is asserted after rotation.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4e44.c`; line(s) 3.
- `eu/src/overlays/ov021/calls/GetTableValuePair.c` → `src/ov021/unclassified_helpers/GetTableValuePair_020a91e8.c`; line(s) 8, 13.

### `ov021:020b4e5c` → `gSurfaceSoundArchiveIdsKind0Or3`

Previous label `data_ov021_020b4e5c`; size **36 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4e50.c`.

36 RO bytes: eighteen native halfwords selected for lookup kinds 0 and 3.

LookupKindTableValue chooses this table for kinds 0/3. PlayActorContextSound and Actor_PlaySurfaceSound use its result as the first argument of SpawnSoundSlot; that helper forwards it as seqArcNo to NNS_SndArcPlayerStartSeqArcEx, with the separate caller argument as sequence index.

Limits: The native object has eighteen halfwords while the local KindTable declares seventeen and accepts index <=17 without a lower-bound check. Preserve all bytes and document that source-view issue separately; no sound material names or host array bounds are inferred.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4e50.c`; line(s) 3.
- `eu/src/overlays/ov021/calls/LookupKindTableValue.c` → `src/ov021/unclassified_helpers/LookupKindTableValue_020a8fc8.c`; line(s) 7, 21.

### `ov021:020b4e80` → `gSurfaceSoundArchiveIdsKind2`

Previous label `data_ov021_020b4e80`; size **36 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4e80.c`.

36 RO bytes: eighteen native halfwords selected for lookup kind 2, including -1 sentinels.

LookupKindTableValue selects this mapping for kind 2. Its actor sound callers suppress playback when the returned archive number is negative; nonnegative results reach the seqArcNo input of the sound archive player.

Limits: Do not replace -1 by zero: SpawnSoundSlot uses archive zero as a special default-archive request. The eighteen-halfword native object and seventeen-element local view remain unchanged.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4e80.c`; line(s) 3.
- `eu/src/overlays/ov021/calls/LookupKindTableValue.c` → `src/ov021/unclassified_helpers/LookupKindTableValue_020a8fc8.c`; line(s) 8, 27.

### `ov021:020b4ea4` → `gSurfaceSoundArchiveIdsKind1`

Previous label `data_ov021_020b4ea4`; size **36 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4ea4.c`.

36 RO bytes: eighteen native halfwords selected for lookup kind 1, including -1 sentinels.

LookupKindTableValue selects this mapping for kind 1, and the actor context/surface sound paths feed its nonnegative result to SpawnSoundSlot as the sequence-archive number.

Limits: The selector values identify dispatch cases only; concrete character/action labels and individual surface names are not established. Keep sentinels and original storage.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4ea4.c`; line(s) 20.
- `eu/src/overlays/ov021/calls/LookupKindTableValue.c` → `src/ov021/unclassified_helpers/LookupKindTableValue_020a8fc8.c`; line(s) 9, 33.

### `ov021:020b4ff8` → `gScaledHitDamageRates`

Previous label `data_ov021_020b4ff8`; size **12 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b4ff8.c`.

12 RO bytes: three Q12 scale rates {0x0b00, 0x0d80, 0x1000}.

ApplyHitToTarget_020ac33c copies these rates when hit.scaled and canScale are both true, indexes by clamp(GetClampedPaletteSlot()-1,0,2), and computes hit.damage=FX_Mul(hit.damage,rate).

Limits: The legacy Palette label does not establish a graphics role for the selector. Name the demonstrated damage scaling only; no difficulty names or percent rounding are imposed.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b4ff8.c`; line(s) 3.
- `eu/src/overlays/ov021/calls/ApplyHitToTarget_020ac33c.c` → `src/ov021/object_state/ApplyHitToTarget_020ac33c.c`; line(s) 101, 207.

### `ov021:020b502c` → `gStageCommandOverlayFactories`

Previous label `data_ov021_020b502c`; size **96 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b5014.c`.

96 RO bytes: twelve pairs of native callback pointer and overlay ID.

DispatchCommandHandler maps opcodes 0xbe..0xc9 and aliases 0x10f..0x111 to these pairs, stores the selected overlay ID in owner+0x10, loads that overlay and invokes its callback with four native arguments.

Limits: The unsupported-opcode path leaves index=-1 and is not changed. Entry 5 has an incorrect relocation label data_ov061_020d8569: its associated ID is 0x42 (66), whose Thumb function is CreateOv066SceneObject at 020d8568. That cross-bank relocation correction is a separate follow-up, not part of this DATA name proposal.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b5014.c`; line(s) 29.
- `eu/src/overlays/ov021/calls/DispatchCommandHandler.c` → `src/ov021/shared_engine/DispatchCommandHandler_020ad508.c`; line(s) 20, 25.

### `ov021:020b508c` → `gEffectGroupResourceConfigs`

Previous label `data_ov021_020b508c`; size **152 bytes**; source `eu/src/ov021/data/Rodata_ov021_020b5014.c`.

152 RO bytes: nineteen pairs of resource file index and native parameter.

EnsureEffectGroup reads this pair for a slot only when its group ID is -1, builds start/end resource keys from file indices index and index+1 in archive selector 3, copies the second word into desc.param, creates the group and stores its ID.

Limits: The second word is retained as a parameter with observed values 1/3; its unit or flag meaning is not established. This is not a table of function pointers or object allocation sizes.

Direct pinned references:

- `eu/src/ov021/data/Rodata_ov021_020b5014.c`; line(s) 16.
- `eu/src/overlays/ov021/calls/EnsureEffectGroup.c` → `src/ov021/shared_engine/EnsureEffectGroup_020acb6c.c`; line(s) 25, 32.

### `ov021:020b5268` → `gUnitNodeDataPathFormat`

Previous label `data_ov021_020b5268`; size **16 bytes**; source `eu/src/ov021/data/Data_ov021_020b5268.c`.

16 initialized DATA bytes containing the terminated narrow format ba/ch/%s/ci.b.z.

InitUnitResources formats a path using its kind-selected category name, loads the resulting file with flags 0x11, passes it to BuildUnitNodes and frees the file after that call.

Limits: Keep its writable DATA section and exact 16-byte size. The parallel cp.b.z file is used by RelocateUnitMotionData; these two resource paths remain distinct.

Direct pinned references:

- `eu/src/ov021/data/Data_ov021_020b5268.c`; line(s) 5.
- `eu/src/overlays/ov021/calls/InitUnitResources.c` → `src/ov021/unclassified_helpers/InitUnitResources_020aa264.c`; line(s) 16, 41.

### `ov021:020b5658` → `gFieldHitSphereStorage`

Previous label `data_ov021_020b5658`; size **16 bytes**; source `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5658.c`.

16 BSS bytes: the center vector and radius storage for the sphere branch of BuildEntryHitShape.

The sphere constructor writes center/radius into this global storage and returns a CollisionShape view that borrows it. BuildEntryHitShape then computes swept bounds and copies the shape/sweep into the output record.

Limits: The record copy preserves a pointer to shared geometry; a later use of the sphere branch overwrites it. The local by-value constructor declaration represents the native struct-return ABI, not a different buffer ownership contract.

Direct pinned references:

- `eu/src/overlays/ov021/calls/BuildEntryHitShape.c` → `src/ov021/object_state/BuildEntryHitShape_020aaad4.c`; line(s) 47, 94.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5658.c`; line(s) 4.

### `ov021:020b5668` → `gFieldHitCylinderStorage`

Previous label `data_ov021_020b5668`; size **44 bytes**; source `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5658.c`.

44 BSS bytes: three VecFx32 values (start/end/normalized direction), length and radius for the cylinder branch.

BuildEntryHitShape forms a vertical end point, normalizes the start-to-end vector and supplies this storage to InitCylinderShape. That constructor records shape kind 4 and computes bounds through gCollisionBoundsDispatch[4].

Limits: The CollisionShape output borrows this global. Keep all 44 bytes and native field order; it is not a 44-byte query or per-entry allocation.

Direct pinned references:

- `eu/src/overlays/ov021/calls/BuildEntryHitShape.c` → `src/ov021/object_state/BuildEntryHitShape_020aaad4.c`; line(s) 49, 119.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5658.c`; line(s) 3.

### `ov021:020b5694` → `gFieldHitCapsuleStorage`

Previous label `data_ov021_020b5694`; size **44 bytes**; source `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5694.c`.

44 BSS bytes: start/end/normalized axis vectors, length and radius for the capsule branch.

BuildEntryHitShape derives the end from desc.length and velocity, normalizes the axis and supplies this storage to InitCapsuleShape. The constructor records shape kind 3 and computes bounds with gCollisionBoundsDispatch[3].

Limits: Capsule and cylinder storage remain separate globals even though their native layouts are equal. Output geometry is borrowed and overwritten by subsequent construction.

Direct pinned references:

- `eu/src/overlays/ov021/calls/BuildEntryHitShape.c` → `src/ov021/object_state/BuildEntryHitShape_020aaad4.c`; line(s) 48, 105.
- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b5694.c`; line(s) 3.

## Additional proof paths

- `eu/src/overlays/ov052/calls/TryGrabLedge.c`.
- `eu/src/overlays/ov052/calls/IsLedgeClimbSpaceClear.c`.
- `eu/src/overlays/ov052/calls/PlayActorContextSound.c`.
- `eu/src/overlays/ov059/calls/Actor_PlaySurfaceSound.c`.
- `eu/src/calls/SpawnSoundSlot.c`.
- `eu/libs/nns/snd/calls/NNS_SndArcPlayerStartSeqArcEx.c`.
- `eu/src/calls/MakeSphereShape.c`.
- `eu/src/calls/InitCylinderShape.c`.
- `eu/src/calls/InitCapsuleShape.c`.

The fixed published config at 136e4466 identifies `ov066:020d8568` as Thumb `CreateOv066SceneObject`; the same address with bit 0 set is mistakenly labelled DATA in ov061. DispatchCommandHandler establishes the selected overlay ID before invocation, so the loaded bank resolves this callback. Changing that relocation label requires its own unchanged official checks and is not hidden inside the table rename.


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
