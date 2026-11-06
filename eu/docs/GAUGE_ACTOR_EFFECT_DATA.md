# Battle-gauge, actor resource and effect DATA

These 34 objects are named from active EU consumers: battle-gauge rendering/loading, selection overlay loading, actor resources and effect-source dispatch. The physical source files, declarations, extents, values and relocations stay unchanged. Equal values and close address suffixes are not used to merge storage or infer an owner.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Native bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov045:20c0764 | `data_ov045_020c0764` | `gBattleGaugeLayeredPanelScale` | 12 | `eu/src/ov045/data/Rodata_ov045_020c0764.c` | `eu/src/overlays/ov045/calls/DrawLayeredPanel.c` |
| ov045:20c0770 | `data_ov045_020c0770` | `gBattleGaugeLayeredPanelTranslation` | 12 | `eu/src/ov045/data/Rodata_ov045_020c0770.c` | `eu/src/overlays/ov045/calls/DrawLayeredPanel.c` |
| ov045:20c077c | `data_ov045_020c077c` | `gBattleGaugeRotatedSpriteScale` | 12 | `eu/src/ov045/data/Rodata_ov045_020c077c.c` | `eu/src/overlays/ov045/calls/DrawRotatedSprite.c` |
| ov045:20c0788 | `data_ov045_020c0788` | `gBattleGaugeRotatedSpriteTranslation` | 12 | `eu/src/ov045/data/Rodata_ov045_020c0788.c` | `eu/src/overlays/ov045/calls/DrawRotatedSprite.c` |
| ov045:20c0794 | `data_ov045_020c0794` | `gBattleGaugeMode3TextFrame` | 16 | `eu/src/ov045/data/Rodata_ov045_020c0788.c` | `eu/src/overlays/ov045/calls/RunSceneLoadStep.c` |
| ov045:20c07a4 | `data_ov045_020c07a4` | `gBattleGaugeTextFrame` | 16 | `eu/src/ov045/data/Rodata_ov045_020c07a4.c` | `eu/src/overlays/ov045/calls/RunSceneLoadStep.c` |
| ov045:20c07b4 | `data_ov045_020c07b4` | `gBattleGaugeBackgroundConfig` | 20 | `eu/src/ov045/data/Rodata_ov045_020c07a4.c` | `eu/src/overlays/ov045/calls/RunSceneLoadStep.c` |
| ov045:20c07c8 | `data_ov045_020c07c8` | `gBattleGaugeMode3BackgroundConfig` | 20 | `eu/src/ov045/data/Rodata_ov045_020c07c8.c` | `eu/src/overlays/ov045/calls/RunSceneLoadStep.c` |
| ov045:20c07dc | `data_ov045_020c07dc` | `gBattleGaugeLayeredPanelRotation` | 36 | `eu/src/ov045/data/Rodata_ov045_020c07c8.c` | `eu/src/overlays/ov045/calls/DrawLayeredPanel.c` |
| ov045:20c088c | `data_ov045_020c088c` | `gResultNoRewardPlaceholderText` | 20 | `eu/src/ov045/data/Data_ov045_020c088c.c` | `eu/src/overlays/ov045/calls/RunResultTallyStep.c` |
| ov051:20c73f0 | `data_ov051_020c73f0` | `gSelectionOverlayInitializers` | 48 | `eu/src/ov051/data/Rodata_ov051_020c73f0.c` | `eu/src/overlays/ov051/calls/LoadNextOverlayForSelection.c` |
| ov051:20c7420 | `data_ov051_020c7420` | `gSelectionOverlayIds` | 48 | `eu/src/ov051/data/Rodata_ov051_020c7420.c` | `eu/src/overlays/ov051/calls/LoadNextOverlayForSelection.c` |
| ov051:20c7460 | `data_ov051_020c7460` | `gTrackedSelectionOverlayStorage` | 32 | `eu/src/ov051/data/Data_ov051_020c7460.c` | `eu/src/overlays/ov051/calls/UnloadTrackedOverlay.c` |
| ov052:20d20e0 | `data_ov052_020d20e0` | `gActorConsumableMemberPriorityIds` | 8 | `eu/src/ov052/data/Rodata_ov052_020d20e0.c` | `eu/src/overlays/ov052/calls/UseFirstAvailableMember.c` |
| ov052:20d20e8 | `data_ov052_020d20e8` | `gActorGroundMovementFlag16Bonuses` | 8 | `eu/src/ov052/data/Rodata_ov052_020d20e8.c` | `eu/src/overlays/ov052/calls/UpdateGroundMovement.c` |
| ov052:20d20f0 | `data_ov052_020d20f0` | `gPlayerActorSpawnShapeOffset` | 12 | `eu/src/ov052/data/Rodata_ov052_020d20e8.c` | `eu/src/overlays/ov052/calls/InitPlayerActorModel_020c7460.c` |
| ov052:20d20fc | `data_ov052_020d20fc` | `gActorSlotModelResourceIds` | 16 | `eu/src/ov052/data/Rodata_ov052_020d20e8.c` | `eu/src/overlays/ov052/calls/LoadSlotModels.c` |
| ov052:20d210c | `data_ov052_020d210c` | `gActorGaugePointRateParameters` | 16 | `eu/src/ov052/data/Rodata_ov052_020d210c.c` | `eu/src/overlays/ov052/calls/UpdateDriveGaugeCharge.c` |
| ov054:20d3674 | `data_ov054_020d3674` | `gOverlay054EntryGroupResourceIds` | 28 | `eu/src/ov054/data/Rodata_ov054_020d3674.c` | `eu/src/overlays/ov054/calls/LoadOverlay054EntityResources.c` |
| ov054:20d3690 | `data_ov054_020d3690` | `gOverlay054SlotSoundArcIds` | 28 | `eu/src/ov054/data/Rodata_ov054_020d3690.c` | `eu/src/overlays/ov054/calls/LoadMenuSoundArcs.c` |
| ov054:20d36f8 | `data_ov054_020d36f8` | `gOverlay054Flag12CharacterPathFormat` | 40 | `eu/src/ov054/data/Ov054CharacterPathFormat.c` | `eu/src/overlays/ov054/calls/LoadOverlay054EntityResources.c` |
| ov056:20d7f6c | `data_ov056_020d7f6c` | `gLinkedShotLocalOffset` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7f6c.c` | `eu/src/overlays/ov056/calls/FireMarkedLinkedShot.c` |
| ov056:20d7f78 | `data_ov056_020d7f78` | `gOrbitUnitReferenceUp` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7f78.c` | `eu/src/overlays/ov056/calls/CircleActorAroundUnit.c` |
| ov056:20d7f84 | `data_ov056_020d7f84` | `gHomingArcGravityAxis` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7f84.c` | `eu/src/overlays/ov056/calls/UpdateHomingArcProjectile.c` |
| ov056:20d7f90 | `data_ov056_020d7f90` | `gSpinAttackRotationAxis` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7f90.c` | `eu/src/overlays/ov056/calls/UpdateSpinAttackUnit.c` |
| ov056:20d7f9c | `data_ov056_020d7f9c` | `gSpinSlamRotationAxis` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7f9c.c` | `eu/src/overlays/ov056/calls/UpdateSpinSlamProjectile.c` |
| ov056:20d7fa8 | `data_ov056_020d7fa8` | `gFallingProjectileGravityAxis` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7fa8.c` | `eu/src/overlays/ov056/calls/UpdateFallingProjectile.c` |
| ov056:20d7fb4 | `data_ov056_020d7fb4` | `gModelEntryOrientationUp` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7fb4.c` | `eu/src/overlays/ov056/calls/UpdateEntryRotations.c` |
| ov056:20d7fc0 | `data_ov056_020d7fc0` | `gTimedUnitEntryLocalOffset` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7fc0.c` | `eu/src/overlays/ov056/calls/UpdateTimedUnitEntries.c` |
| ov056:20d7fcc | `data_ov056_020d7fcc` | `gSpawnOffsetProjectileLocalOffset` | 12 | `eu/src/ov056/data/Rodata_ov056_020d7fcc.c` | `eu/src/overlays/ov056/calls/SpawnOffsetProjectile.c` |
| ov056:20d7fe0 | `data_ov056_020d7fe0` | `gEffectSourceKindResetHandlers` | 80 | `eu/src/ov056/data/Data_ov056_020d7fe0.c` | `eu/src/overlays/ov056/calls/DispatchSourceKindHandler.c` |
| ov056:20d8030 | `data_ov056_020d8030` | `gEffectSourceKindReleaseHandlers` | 80 | `eu/src/ov056/data/Data_ov056_020d8030.c` | `eu/src/overlays/ov056/calls/ReleaseSourceByKind.c` |
| ov056:20d8080 | `data_ov056_020d8080` | `gEffectSourceModeSpawnHandlers` | 80 | `eu/src/ov056/data/Data_ov056_020d8080.c` | `eu/src/overlays/ov056/calls/DispatchModeHandler.c` |
| ov056:20d80d0 | `data_ov056_020d80d0` | `gEffectSourceKindEventHandlers` | 80 | `eu/src/ov056/data/Data_ov056_020d80d0.c` | `eu/src/overlays/ov056/calls/DispatchSourceKindEvent.c` |

## Battle-gauge rendering and load configurations

DrawLayeredPanel copies three separate objects as base translation, base scale and a 3x3 rotation matrix. It adjusts translation.z by the sprite depth offset, writes scale/rotation/translation into the NNS global geometry state and flushes that state before submitting textured quads. DrawRotatedSprite has separate translation and scale templates; it replaces x/y scale with size<<7 and computes rotation dynamically. The distinct vectors remain distinct even where values match.

The two 16-byte text frames and two 20-byte background configurations belong to different loading paths. Mode 0 reaches loading steps 2/3; mode 3 reaches steps 8/9. Background configurations contain three numeric words and CopyTileRect/ClearTileRect function pointers. The legacy PoolConfig counts[5] declaration does not describe those callback words and should not be copied as a complete semantic layout into a port.

RunResultTallyStep selects the four-hyphen UTF-16 placeholder when no reward name is available. The physical symbol stores ten u16 values rather than only the five values needed for four hyphens plus NUL; its remaining stored zeros and 20-byte extent are retained.

## Selection overlay tables

LoadNextOverlayForSelection reads a selection code from GetOverlaySelectionRecord, scans slots 2 down to 0, checks the -1 ID sentinel and nonnull initializer, records the chosen ID and loads that overlay before invoking the corresponding initializer. Initializers and IDs are parallel tables with a consumer row width of three. Their physical objects each contain twelve words. The ID table retains its final zero row and all -1 words; zero must not be normalized to the unloaded sentinel.

gTrackedSelectionOverlayStorage is a 32-byte physical object. Only its first three words have the demonstrated tracking role; they start at -1 and UnloadTrackedOverlay restores a matching slot to -1. The remaining five stored zero words retain an unspecified contract. These are overlay IDs rather than heap-owned overlay instances. This block does not add bounds or alter the loader's precondition that a valid slot is available.

## Actor resources and aliases

The two member IDs are tried in their stored order and require a nonzero consumable-use count before ApplyItemRewardEffect. The movement-bonus table is selected by numeric player entry flag 0x10 and count minus one; the name assigns no named ability to that flag. The spawn-shape offset is passed with the ActorEntry_Init shape and is not documented as a world position or model-joint offset.

The four model resource IDs select record/source pairs at id and id+1. This EU table at ov052:020d20fc must not be confused with ConfigureCameraMode's shared-source label ending 020d20fc: that EU wrapper maps the latter to ov052:020d211c. Likewise, the ov056 vector at 020d7fc0 is not DispatchSourceKindHandler's table; that wrapper maps its old 020d7fc0 to EU020d7fe0. Names follow the resolved EU identity.

The four gauge rate parameters are divided and rounded before timer advancement; a positive produced gain is passed to AddGaugePoints with a negative sign. No charge-versus-drain gameplay state is assigned solely from the existing UpdateDriveGaugeCharge name.

Overlay054 has seven entry-group resource IDs and seven corresponding sound arc IDs. The resource consumer combines archive parameters with each ID and id+1. The path format ba/ch/%s/hjp.p.z is selected when numeric entry flag 0x0c is set; no named ability is inferred from that value or path abbreviation. The physical path object keeps its full 40-byte extent.

## Effect vectors and handler tables

The stored axes at ov056:020d7f78 through 020d7fb4 are separate positive-Y unit vectors. Consumers establish their individual roles: orbit cross products, gravity deltas, quaternion spin axes and model orientation construction. Gravity uses a negative scalar; the stored axis is not itself a downward vector. The linked-shot and timed-unit/projectile offsets are rotated relative to a field entry/actor before placement. Equal vector values do not make the physical symbols interchangeable.

| Handler table | Index and actual call | Conditional behavior / return use |
|---|---|---|
| gEffectSourceKindResetHandlers | signed source.kind at +0x3d; handler(source) | Calls only nonnull entries; dispatcher discards the result. |
| gEffectSourceKindReleaseHandlers | signed source.kind at +0x3d; handler(source) | Calls a nonnull kind helper, then always ReleaseSceneObject(source). |
| gEffectSourceModeSpawnHandlers | object mode at +4; handler(object,arg1,arg2) | No null check in this dispatcher; result discarded. |
| gEffectSourceKindEventHandlers | signed source.kind at +0x3d; handler(source,arg1,arg2) | No null check in this dispatcher; result discarded. |

Each table has twenty stored slots. The dispatcher bodies do not bound their indices. Preserve duplicate pointers, null entries and all callback arguments. The old data-file extern void Function(void) declarations only allow the pointer words to be emitted; they do not establish the callbacks' true argument lists, and they do not make residual r0 a logical result. The event-table pointer into overlay030 retains its own bank and exact native target.

| Index | Reset helper | Kind release helper | Mode spawn helper | Kind event helper |
|---:|---|---|---|---|
| 0 | `ResetCountsAndSlots` | NULL | `SpawnPairedEntryUnit` | `SpawnUnitProjectile` |
| 1 | `ResetCountsAndSlots` | `ReleaseEffectPool_020d450c` | `SpawnEffectUnitFromSpawner` | `SpawnUnitProjectile` |
| 2 | `ResetCountsAndSlots` | NULL | `SpawnPairedEntryUnit` | `SpawnUnitProjectile` |
| 3 | `ResetCountsAndSlots` | NULL | `SpawnEntityFromSpawner` | `StartGaugeRewardEffect` |
| 4 | `ResetActiveEntries` | `FreeSlotTrackerUnitSlots` | `SpawnSlotTrackerUnit` | `SpawnEffectParticle` |
| 5 | `ResetCountsAndSlots` | `FreeSlotBuffers` | `SpawnGroupedMultiPartUnit` | `SpawnSlotRequestProjectile` |
| 6 | NULL | NULL | `SpawnGroupedTrackerUnit` | `InitSlotOwnerFromDesc` |
| 7 | NULL | NULL | `SpawnGroupedTrackerUnit` | `InitSlotOwnerFromDesc` |
| 8 | NULL | NULL | `SpawnGroupedTrackerUnit` | `InitSlotOwnerFromDesc` |
| 9 | `ResetCountsAndSlots` | `FreeSlotBuffers_020d641c` | `SpawnGroupedAttackUnit` | `SpawnIndexedProjectile` |
| 10 | `ResetCountsAndSlots` | `FreeSlotBuffers_020d641c` | `SpawnGroupedAttackUnit` | `SpawnIndexedProjectile` |
| 11 | `ResetCountsAndSlots` | `FreeSlotBuffers_020d6788` | `SpawnScaledMultiPartUnit` | `SpawnTrailProjectile` |
| 12 | `ResetCountsAndSlots` | `FreeSceneModelSlotArray` | `SpawnBounceShooterUnit` | `SpawnRecordedProjectile` |
| 13 | `ResetActiveEntries` | `FreeSlotTrackerUnitSlots` | `SpawnSlotTrackerUnit` | `SpawnEffectParticle` |
| 14 | `ResetSlotStateAndNotify` | NULL | `SpawnArcUnitFromSpawner` | `InitSlotOwnerWithOrigin` |
| 15 | `ResetCountsAndSlots` | `FreeSlotBuffers_020d7060` | `SpawnPartRecordUnit` | `SpawnSlotProjectile` |
| 16 | `ResetCountsAndSlots` | NULL | `SpawnUnitFromSpawner` | `SpawnEntryProjectile` |
| 17 | `ResetCountsAndSlots` | `FreeSlotBuffers_020d788c` | `SpawnMultiPartUnit` | `SpawnEmitterSound` |
| 18 | `StopSlotsAndClearActive` | NULL | `SpawnTimedUnitFromSpawner` | `AttachEffectToEntry` |
| 19 | `ResetUnitCounts` | `ReleaseEffectPool` | `SpawnSpiralProjectile` | `func_ov030_020bcec0` |

## Per-object evidence and limits

### `gBattleGaugeLayeredPanelScale`

The layered-panel renderer copies this VecFx32 as its base scale and submits it to NNS_G3dGlbSetBaseScale.

Evidence: `eu/src/overlays/ov045/calls/DrawLayeredPanel.c`. Three fx32 coordinates; preserve the renderer-specific scale, not a shared unit vector.

The EU wrapper selects `src/ov045/graphics/DrawLayeredPanel_020c05a0.c`.

### `gBattleGaugeLayeredPanelTranslation`

The layered-panel renderer copies this VecFx32, subtracts sprite depthOffset from z and submits the resulting base translation.

Evidence: `eu/src/overlays/ov045/calls/DrawLayeredPanel.c`. The u16 physical declaration packs three fx32 values; no type change or unit reinterpretation.

The EU wrapper selects `src/ov045/graphics/DrawLayeredPanel_020c05a0.c`.

### `gBattleGaugeRotatedSpriteScale`

The rotated-sprite renderer copies this VecFx32; x/y are replaced by size<<7 while z keeps the stored value.

Evidence: `eu/src/overlays/ov045/calls/DrawRotatedSprite.c`. The initializer is a template rather than the final dynamic x/y scale.

The EU wrapper selects `src/ov045/graphics/DrawRotatedSprite_020c04c4.c`.

### `gBattleGaugeRotatedSpriteTranslation`

The rotated-sprite renderer copies this VecFx32 as the base translation submitted before drawing.

Evidence: `eu/src/overlays/ov045/calls/DrawRotatedSprite.c`. Keep this separate from the layered-panel translation even where components overlap.

The EU wrapper selects `src/ov045/graphics/DrawRotatedSprite_020c04c4.c`.

### `gBattleGaugeMode3TextFrame`

Load step9 copies the 16-byte TextFrame into the resultLayer initializer; this path follows mode3 resource loading.

Evidence: `eu/src/overlays/ov045/calls/RunSceneLoadStep.c`. Eight packed u16 frame values; no new per-field semantics are inferred.

### `gBattleGaugeTextFrame`

Load step3 copies this 16-byte TextFrame into the textLayer initializer after the mode0 background load.

Evidence: `eu/src/overlays/ov045/calls/RunSceneLoadStep.c`. Preserve all eight u16 values, including trailing zeros.

### `gBattleGaugeBackgroundConfig`

Load step2 copies this 20-byte background-container configuration and passes it to InitBackgroundContainer.

Evidence: `eu/src/overlays/ov045/calls/RunSceneLoadStep.c`. Three stored numeric words plus CopyTileRect/ClearTileRect pointers; do not infer every numeric field from the legacy PoolConfig counts name.

### `gBattleGaugeMode3BackgroundConfig`

Load step8 copies this 20-byte background-container configuration in the mode3 path before resource-file loading.

Evidence: `eu/src/overlays/ov045/calls/RunSceneLoadStep.c`. Keep its distinct values, callback relocations and binding; no new callback ABI is introduced.

### `gBattleGaugeLayeredPanelRotation`

The layered-panel renderer copies this identity MtxFx33 into the global base rotation before flushing geometry.

Evidence: `eu/src/overlays/ov045/calls/DrawLayeredPanel.c`. Nine fx32 words form a renderer-specific stored matrix; preserve the distinct object.

The EU wrapper selects `src/ov045/graphics/DrawLayeredPanel_020c05a0.c`.

### `gResultNoRewardPlaceholderText`

When rewardCount is zero, the result tally draws this UTF-16 four-hyphen placeholder instead of a reward name.

Evidence: `eu/src/overlays/ov045/calls/RunResultTallyStep.c`. Physical object is ten u16 values (20 bytes), including the terminator and stored trailing zeros.

### `gSelectionOverlayInitializers`

The loader indexes this table by selection and slot; it checks for nonnull, loads the paired overlay ID, then invokes the initializer.

Evidence: `eu/src/overlays/ov051/calls/LoadNextOverlayForSelection.c`. Physical extent is twelve pointers; consumer uses rows of three and does not bound selection here. Do not trim the final stored row or infer all selections are valid.

The EU wrapper selects `src/ov051/overlay_loading/LoadNextOverlayForSelection.c`.

### `gSelectionOverlayIds`

The loader indexes this parallel table by selection and slot, skips -1 entries, and writes the selected overlay ID into tracked storage.

Evidence: `eu/src/overlays/ov051/calls/LoadNextOverlayForSelection.c`. Twelve stored words include -1 sentinels and a trailing zero row. Preserve the exact selection/slot relationship and do not turn zeros into -1.

The EU wrapper selects `src/ov051/overlay_loading/LoadNextOverlayForSelection.c`.

### `gTrackedSelectionOverlayStorage`

The load helper records selected IDs in its first three words; unloading an ID clears the matching first-three slot back to -1.

Evidence: `eu/src/overlays/ov051/calls/UnloadTrackedOverlay.c`. Physical object is eight words (32 bytes); only the first three slots have this demonstrated role. Remaining five words stay unspecified.

The EU wrapper selects `src/ov051/overlay_loading/UnloadTrackedOverlay.c`.

### `gActorConsumableMemberPriorityIds`

Tries member IDs 0xb7 then 0xb8 in the actor list at +0x1070; the first present member with nonzero consumable uses is applied.

Evidence: `eu/src/overlays/ov052/calls/UseFirstAvailableMember.c`. This proves priority and use eligibility, not a gameplay item/ability name for either ID.

The EU wrapper selects `src/ov052/unclassified_helpers/UseFirstAvailableMember_020cc8bc.c`.

### `gActorGroundMovementFlag16Bonuses`

When player entry flag 0x10 is set, indexes these two fx32 bonuses by entry count minus 1 and scales movement/time-scaled speed.

Evidence: `eu/src/overlays/ov052/calls/UpdateGroundMovement.c`. 16 is the numeric flag ID, not a claimed named ability or difficulty. No bounds check is added.

The EU wrapper selects `src/ov052/actor_motion/UpdateGroundMovement_020ca918.c`.

### `gPlayerActorSpawnShapeOffset`

Copies this VecFx32 into the SpawnShape offset passed with its collision shape to ActorEntry_Init.

Evidence: `eu/src/overlays/ov052/calls/InitPlayerActorModel_020c7460.c`. Do not describe it as a world position or model-joint offset; it is the stored spawn-shape offset.

The EU wrapper selects `src/ov052/model_display/InitPlayerActorModel_020c7460.c`.

### `gActorSlotModelResourceIds`

Four resource IDs select model record/source pairs for four 0x104-byte model slots; the paired source ID is id+1.

Evidence: `eu/src/overlays/ov052/calls/LoadSlotModels.c`. This EU symbol is distinct from shared ConfigureCameraMode old address20d20fc, which maps to EU20d211c. Resolve aliases before identifying owner.

The EU wrapper selects `src/ov052/model_display/LoadSlotModels_020ca20c.c`.

### `gActorGaugePointRateParameters`

Copies four rate parameters, selects one, divides by 100 and converts it to timer gain; positive gain is sent to AddGaugePoints with a negative sign.

Evidence: `eu/src/overlays/ov052/calls/UpdateDriveGaugeCharge.c`. No charge-versus-drain gameplay meaning is inferred from the legacy function name. Preserve rounding and rate-selection behavior.

The EU wrapper selects `src/ov052/unclassified_helpers/UpdateDriveGaugeCharge_020cc910.c`.

### `gOverlay054EntryGroupResourceIds`

Seven IDs supply group resource parameters; for each selected group the paired palette resource is id+1.

Evidence: `eu/src/overlays/ov054/calls/LoadOverlay054EntityResources.c`. The consumer combines archive-backed IDs and masks to 9 bits. Do not call the first ID alone a palette or assign named rewards to table positions.

The EU wrapper selects `src/ov054/object_factory/LoadOverlay054EntityResources_020d2320.c`.

### `gOverlay054SlotSoundArcIds`

For each nonnegative slotEntries[i], queues table[i] as a sound arc; a separate fixed 0xc2 arc follows.

Evidence: `eu/src/overlays/ov054/calls/LoadMenuSoundArcs.c`. Seven stored arc IDs correspond to slots, not sound sequence IDs within an arc.

The EU wrapper selects `src/ov054/unclassified_helpers/LoadMenuSoundArcs_020d2688.c`.

### `gOverlay054Flag12CharacterPathFormat`

Formats ba/ch/%s/hjp.p.z with the character-name string when selection entry flag 0xc is set, then acquires the corresponding shared resource.

Evidence: `eu/src/overlays/ov054/calls/LoadOverlay054EntityResources.c`. 12 is the numeric flag ID. Retain all 40 physical bytes and the existing character-path format; no ability name is assigned to hjp.

The EU wrapper selects `src/ov054/object_factory/LoadOverlay054EntityResources_020d2320.c`.

### `gLinkedShotLocalOffset`

Rotates this stored offset around Y with the actor position and linked angle; the resulting position supplies the marker request and shot descriptor.

Evidence: `eu/src/overlays/ov056/calls/FireMarkedLinkedShot.c`. Three fx32 values; preserve the local-offset role and separate physical storage.

The EU wrapper selects `src/ov056/shared_engine/FireMarkedLinkedShot_020d2d1c.c`.

### `gOrbitUnitReferenceUp`

The positive Y unit vector supplies two cross products used to construct the orbit unit side/direction basis.

Evidence: `eu/src/overlays/ov056/calls/CircleActorAroundUnit.c`. This is one bank-specific reference axis, not a shared global basis object.

The EU wrapper selects `src/ov056/shared_engine/CircleActorAroundUnit_020d56e8.c`.

### `gHomingArcGravityAxis`

Scales this positive Y unit vector by a negative step-dependent amount to form the homing arc gravity delta.

Evidence: `eu/src/overlays/ov056/calls/UpdateHomingArcProjectile.c`. The stored axis is positive Y; gravity direction comes from the negative scalar.

The EU wrapper selects `src/ov056/shared_engine/UpdateHomingArcProjectile_020d5f7c.c`.

### `gSpinAttackRotationAxis`

Passes this positive Y unit axis to QuatFromAxisAngle for the spin attack rotation.

Evidence: `eu/src/overlays/ov056/calls/UpdateSpinAttackUnit.c`. No change to angle units or update-step scaling.

The EU wrapper selects `src/ov056/shared_engine/UpdateSpinAttackUnit_020d54dc.c`.

### `gSpinSlamRotationAxis`

Passes this positive Y unit axis and the time-scaled spin angle to QuatFromAxisAngle.

Evidence: `eu/src/overlays/ov056/calls/UpdateSpinSlamProjectile.c`. This equal-valued axis remains separate from other spin/gravity objects.

The EU wrapper selects `src/ov056/shared_engine/UpdateSpinSlamProjectile_020d7538.c`.

### `gFallingProjectileGravityAxis`

Scales this positive Y unit vector by negative owner gravity times step to obtain the falling delta.

Evidence: `eu/src/overlays/ov056/calls/UpdateFallingProjectile.c`. Do not replace the stored axis with a negative vector or alter rounding/order.

The EU wrapper selects `src/ov056/shared_engine/UpdateFallingProjectile_020d6b94.c`.

### `gModelEntryOrientationUp`

Crosses the positive Y reference with normalized entry direction to build xAxis, then derives yAxis and writes the orientation matrix.

Evidence: `eu/src/overlays/ov056/calls/UpdateEntryRotations.c`. Does not imply every model has world-up ownership, nor handle the parallel-vector case differently.

### `gTimedUnitEntryLocalOffset`

Rotates the offset by the bounded field entry facing and position before storing each active timed-unit entry position.

Evidence: `eu/src/overlays/ov056/calls/UpdateTimedUnitEntries.c`. Distinct from shared DispatchSourceKindHandler old20d7fc0, which maps to EU20d7fe0; no handler-table name is assigned to this vector.

The EU wrapper selects `src/ov056/unclassified_helpers/UpdateTimedUnitEntries_020d7ad0.c`.

### `gSpawnOffsetProjectileLocalOffset`

Rotates this stored offset into a spawn position relative to field entry position/facing, then adjusts Y by half the shape height.

Evidence: `eu/src/overlays/ov056/calls/SpawnOffsetProjectile.c`. Equal values to the timed-unit offset do not imply interchangeable storage or references.

The EU wrapper selects `src/ov056/shared_engine/SpawnOffsetProjectile_020d79e8.c`.

### `gEffectSourceKindResetHandlers`

Twenty handler slots are selected by signed source.kind at+0x3d; nonnull entries are invoked with source. The table installs reset/stop helpers.

Evidence: `eu/src/overlays/ov056/calls/DispatchSourceKindHandler.c`. Index validity belongs to callers. Preserve null slots6..8 and raw function-pointer relocations; no return semantics are consumed here.

The EU wrapper selects `src/ov056/unclassified_helpers/DispatchSourceKindHandler_020d7d54.c`.

### `gEffectSourceKindReleaseHandlers`

Twenty cleanup slots indexed by signed source.kind are invoked if nonnull before ReleaseSceneObject(source).

Evidence: `eu/src/overlays/ov056/calls/ReleaseSourceByKind.c`. A null slot still releases the scene object. Do not infer that every handler frees the entire source itself.

The EU wrapper selects `src/ov056/unclassified_helpers/ReleaseSourceByKind_020d7d20.c`.

### `gEffectSourceModeSpawnHandlers`

Twenty spawner handlers are selected by object mode at+4 and called with (object,arg1,arg2), without a null check.

Evidence: `eu/src/overlays/ov056/calls/DispatchModeHandler.c`. Preserve all 20 slots, duplicate pointers and the three actual arguments; callback result is discarded by this dispatcher.

The EU wrapper selects `src/ov056/unclassified_helpers/DispatchModeHandler_020d7d84.c`.

### `gEffectSourceKindEventHandlers`

Twenty event handlers are selected by signed source.kind at+0x3d and called with (source,arg1,arg2), without a null check.

Evidence: `eu/src/overlays/ov056/calls/DispatchSourceKindEvent.c`. One relocation targets a helper in overlay030; keep its exact pointer and bank identity. No named gameplay event meaning is inferred.

The EU wrapper selects `src/ov056/unclassified_helpers/DispatchSourceKindEvent_020d7db4.c`.

## Reproducible review and validation boundary

Locate the identity in `eu/config/arm9/overlays/ovNNN/symbols.txt` and the physical source range in the same bank's `delinks.txt`. All physical sources and direct EU evidence sources listed here are active delink inputs. Follow the EU wrapper aliases before reading a shared body.

For every object, its existing ELF symbol extent and its reconstructed R_ARM_ABS32 pointer words were compared against the extracted EU overlay at the native address. All 34 compared objects agree. This is a read-only evidence check of existing objects, not a new compilation or official gate result. Integration must still preserve the official matches, module hashes, physical extents, symbol bindings and relocation addends.


## Byte-exact validation

74 DATA identities retain their source paths, native sizes and storage.
All 191 affected official function checks pass. A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 259 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
