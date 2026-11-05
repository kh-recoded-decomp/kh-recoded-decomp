# Stage, camera and scene-task helper contracts

This block names the remaining 52 reviewed EU entrypoints in overlays 041–071 at the 00280f baseline. It preserves distinct owners, numerical presets/states and native ARM/Thumb entrypoints. The names describe body operations and established callers, not original source spellings. The per-function plan records the supporting source locations and existing object hashes. Source paths in the identity table below are relative to `eu/` and use the accepted names for this integration.

The native layouts below are partial views. They do not form one common actor/camera/task struct, and matching offsets in two owners do not make their meanings interchangeable. No signature or algorithm change is included. A later port should use the proven logical contract while reviewing the legacy private declarations separately.

## Stage lifecycle

`FinalizeAreaSceneInfoNoop` is the final hook after `BuildAreaSceneInfo` has filled pointers, count/tier information and shared sound-state information. The hook has no body effect; prior setup remains live. Its incoming info pointer propagates through the builder in r0, but the sole `StartOverlay41Phase` caller replaces it before use. Some pointers refer to borrowed area-manager storage, so this is not an allocation or resource-release callback.

`InitializeStageEntryOutState` initializes an entry directly into state 6, step 3. It disables actor slot mask 8 and clears HP at +0xdc and displayed HP at +0xe0. The typed StageEntry stride is 0x4b4; hit-resolution writers establish state 6 after HP reaches zero. The initializer is used for scene flag 0x80 and entry kind 0. It skips the earlier transition's animations, sounds, status clearing and new orb bursts; it does not clear maximum HP, every flag, old orbs or resources.

`UnlinkRecordOwnerRootSlot` applies to the embedded RecordOwner passed by scene initialization and shutdown. Its 128 entries of 0x38 bytes precede an ActorSlot at owner +0x1c00. Only that root-slot membership is unlinked. The scene embeds this owner at +0x53c, making its root slot scene +0x213c. The containing scene and its entry/resource lifetimes remain with their callers.

## Follow camera and panel camera

The ov042 follow-camera owner keeps flags at +0x38 separate from follow flags at +0x140. `GetCameraFlag800` returns the raw masked value 0x800 (or zero for a NULL global), not normalized TRUE. `SetCameraFollowLock` stores a raw word at +0x48; its nonzero guard stops follow tracking/target stepping while shake work still runs.

The follow limits are minY/maxY at +0xbc/+0xc0 and minX/maxX at +0xc4/+0xc8. Their setters invalidate cached player-position Z at +0x13c with 0x7fffffff so the vector-equality movement test detects change. The horizontal setter additionally handles finite/sentinel transitions, captures the current eye X and starts the existing 20-frame slide. The adjusted-bounds getter combines the limits with frustum side values and a nested entry collision extent; it does not simply expose the raw stored bounds. The nested extent's full owner remains opaque.

`StartCameraDriftShake` selects motion flag 0x10000, clears 0x8000 and initializes embedded motion at +0x148. The script caller supplies magnitude/duration. Frame update consumes the motion position at +0x158 as an offset to both eye and target. `IsCameraShakeActive` tests the motion state for either launched or drift shake; it is not a drift-only query and has no NULL guard.

The ov044 panel owner uses target at +0x14, eye/position at +0x20 and up at +0x2c, as established by the graphics and sound-listener APIs. `CommitPanelCameraFrame` returns early for flags +0x38 mask 2; otherwise its argument controls listener update before committing projection and cached axes. `CommitPanelProjectionAndViewAxes` forwards one camera pointer to the projection worker before the axis update. The old FX_Div-like two-integer template is not a valid host signature. `GetPanelCameraState` returns the borrowed global owner used by the initializer and update paths, despite its old integer view.

The three release Noops are registered submode release callbacks for ov042/043/044. The caller then unloads the overlay, resets mode and releases the common heap. The empty callback itself frees nothing. Other noops in those banks have different unresolved roles and remain outside this block.

## View planes, focus and event presets

`Camera_GetViewPlaneNormals` returns four side-plane normals at CameraManager +0x50, +0x5c, +0x68 and +0x74. The view-axis writer and both plane-set dot-product consumers prove this is a four-plane array, not a 3×3 basis or near/far-plane set. It aliases mutable camera state, is overwritten by later view updates and is valid only while that owner lives.

`Camera_UsesDefaultFocusInPreset19Or21` tests the conjunction of a NULL VecFx32 override pointer at +0xf4 and preset 19 or 21 at +0xe4. The focus getter's NULL branch returns managed actor 0's position. No player/path/combat identity is assigned to that default or to the two preset numbers. Older private pathActive/locked labels at +0xf4 must not be copied as BOOL fields.

The two ov049 initializers populate motion presets 2 and 3 for `PlayEventCameraKeys`. Both store angle 90<<12, with different distance/other scalar defaults and 0xa000/0x14000 values. The executor fills time, applies non-sentinel key overrides and converts the angle for view-relative motion. The initializers leave time untouched. They do not themselves rotate the camera by 90 degrees or establish a projection/FOV contract.

## Models, factories and storage

The two 16-byte resets in ov052/059 perform the same stores: zero words +0/+4/+0xc and byte +8, leaving padding +9..+0xb untouched. Their callers distinguish the slot-model block at actor +0x105c from the joint-blend block at +0x16f0. Both overlap other motion/draw-request views; neither resets an entire actor or only a generic animation frame.

The ov052 model-position getter follows actor +0x230 to the model and returns model +0xa8. It is a borrowed vector, separate from the actor's velocity and cached-position vectors. Its paired setter delegates the real model position operation, including any worker side effects.

The five registration wrappers install a constructor callback and do not construct or allocate an instance themselves. Ov053/054/059 constructors take variants; ov055/057 constructors take context. Existing erased void(void) factory declarations do not prove those creation signatures. Keep the registration and creation paths distinct.

The ov056 scene-model-slot helpers update group entries before advancing slot animation at owner +0x18c, or free the slot-array pointer at that same field. The free helper neither clears the field nor adds a NULL guard. Ov054 draws the actor before scene models. The two ov058 draw hooks test distinct effect-slot phases and use different owners/file indices; the raised-model worker writes anchor Y +0x2000. Identical draw bodies do not merge their storage or lifetimes.

`EntryList_RemoveByKey` operates on generic eight-byte list entries with a u8 count at +0x120: missing key returns 0, otherwise trailing entries move left and count decreases before returning 1. Preserve native u8 arithmetic and the existing capacity assumptions; no Actor-specific owner is inferred. The effect-slot comparator receives pointers to slot-pointer elements and subtracts the first model Z from the second model Z, yielding descending Z under the real signed comparator API. It is not camera-distance sorting, a stable sort or a new tie-breaking policy.

## Task and callback protocols

`SetGrabSweepStepScale` is a three-input member-update callback: it stores r2 into GrabWork +0x100. The linked pull-source consumer multiplies base acceleration by that value and accumulates/clamps pull speed. It is an update step scale, not model scale or resource cleanup.

The ov063 SceneTask forwards its nested EntryPool at +0x58. Task slot +0x24 steps entries with the supplied third argument, +0x28 draws active entries, and +0x30 marks their state bytes inactive (-1). The actual member dispatchers prove those roles despite misleading factory field labels. The pool has 0x154-byte entries behind a separate 0x3c control owner. Resetting entries is not freeing the pool; the task destructor releases its allocation separately.

Ov062/065 action-start callbacks resolve the selected actor, clear byte +0xa51, start a camera path and activate slot-model group 0. Their path offsets differ (+0x90 versus +0x9c). Both write status 0x18 and return a raw task result word at +0x3c; these values are not a newly inferred BOOL. Ov064 member cleanup clears phase byte +0x44 and stores -1 to loop handle +0x64 without explicitly freeing the member or resetting every timer/origin. Its separate sound-stop helper stops a valid sound slot then stores -1.

The ov070/071 ID predicates compare the ScriptTask first word with literal 0x10f/0x110. Constructors copy descriptor IDs through `InitScriptTask`; actual consumers select palette/projectile/hit/speed parameters. No idle/enraged/difficulty enum is recovered. Ov071's time-step callback stores r2 at +0x7c, initialized to 0x1000 and consumed by native timer, FX_Mul, gravity and spin/deceleration updates. It belongs to the allocated scene task, not the full gameplay actor.

The burst visitor increments its third-argument counter and returns TRUE, which the actual position-search dispatcher treats as early stop. Its caller only asks whether count is nonzero; it does not count every target. The side-wall visitor writes 1 through its third argument and returns literal 2. The owner consumes the written hit flag to abort correction, but the collision dispatcher's meaning for code 2 remains unresolved. Preserve that literal rather than naming it accept/reject/stop.

`UpdateGlobalActorGaugePanel` supplies two real arguments—panel at global actor +0x1524 and the owner itself—despite a unary cast in the old source. This plan documents the call and does not silently rewrite that ABI.

## Per-function identity and evidence

The evidence column points to the inspected implementation/caller origin. Shared-source address suffixes retain their reference-region names; the old identity and ARM/Thumb mode below identify EU. Detailed paired consumers and limitations are retained in the integration plan.

| Original EU symbol | Descriptive name | Mode / bytes | EU source | Primary evidence |
|---|---|---|---|---|
| `func_ov041_020bc520` | `FinalizeAreaSceneInfoNoop` | THUMB / 0x2 | `src/overlays/ov041/auto/FinalizeAreaSceneInfoNoop.c` | `src/ov041/unclassified_helpers/BuildAreaSceneInfo_020bc504.c:81` |
| `func_ov041_020c3678` | `InitializeStageEntryOutState` | THUMB / 0x40 | `src/overlays/ov041/calls/InitializeStageEntryOutState.c` | `eu/src/overlays/ov041/calls/StageEntryStateDefeated.c:95` |
| `func_ov041_020ce200` | `UnlinkRecordOwnerRootSlot` | THUMB / 0x10 | `src/overlays/ov041/calls/UnlinkRecordOwnerRootSlot.c` | `src/ov041/unclassified_helpers/InitRecordOwnerSlots_020ce1a8.c:22` |
| `func_ov042_020bd0f4` | `GetCameraFlag800` | THUMB / 0x1c | `src/overlays/ov042/calls/GetCameraFlag800.c` | `eu/src/overlays/ov042/calls/GetCameraFlag800.c:7` |
| `func_ov042_020bd5f4` | `SetCameraFollowLock` | THUMB / 0xc | `src/overlays/ov042/auto/SetCameraFollowLock.c` | `eu/src/overlays/ov042/calls/UpdateCameraScene.c:187` |
| `func_ov042_020bd620` | `SetCameraFollowMaxY` | THUMB / 0x20 | `src/overlays/ov042/calls/SetCameraFollowMaxY.c` | `eu/src/overlays/ov042/calls/UpdateCameraScene.c:236` |
| `func_ov042_020bd70c` | `GetCameraFollowFlags` | THUMB / 0x10 | `src/overlays/ov042/calls/GetCameraFollowFlags.c` | `eu/src/overlays/ov042/calls/UpdateCameraScene.c:239` |
| `func_ov042_020bd76c` | `StartCameraDriftShake` | THUMB / 0x40 | `src/overlays/ov042/calls/StartCameraDriftShake.c` | `src/ov001/shared_engine/ScriptCmd_StartCameraShake_02065778.c:21` |
| `func_ov042_020bd7ac` | `IsCameraShakeActive` | THUMB / 0x1c | `src/overlays/ov042/calls/IsCameraShakeActive.c` | `eu/src/overlays/ov042/calls/UpdateCameraScene.c:335` |
| `func_ov042_020bd7c8` | `SetCameraHorizontalFollowBounds` | THUMB / 0x68 | `src/overlays/ov042/calls/SetCameraHorizontalFollowBounds.c` | `eu/src/overlays/ov042/calls/UpdateCameraScene.c:237` |
| `func_ov042_020bd830` | `GetCameraAdjustedHorizontalBounds` | THUMB / 0x48 | `src/overlays/ov042/calls/GetCameraAdjustedHorizontalBounds.c` | `src/ov042/camera/BuildCameraFrustumColliders_020bd858.c:98` |
| `func_ov042_020bde3c` | `ReleaseOv042CameraNoop` | THUMB / 0x2 | `src/overlays/ov042/auto/ReleaseOv042CameraNoop.c` | `eu/src/overlays/ov021/calls/func_ov021_020af3a0.c:18` |
| `func_ov043_020bcce0` | `ReleaseOv043CameraNoop` | ARM / 0x4 | `src/overlays/ov043/auto/ReleaseOv043CameraNoop.c` | `eu/src/overlays/ov021/calls/func_ov021_020af3a0.c:21` |
| `func_ov044_020d00a0` | `CommitPanelProjectionAndViewAxes` | ARM / 0x10 | `src/overlays/ov044/calls/CommitPanelProjectionAndViewAxes.c` | `src/arm9/graphics/camera_commit_projection_0202a814.c:27` |
| `func_ov044_020d00b0` | `CommitPanelCameraFrame` | ARM / 0x60 | `src/overlays/ov044/calls/CommitPanelCameraFrame.c` | `src/ov044/panel_state/SetPanelFlagBit1_020d0120.c:9` |
| `func_ov044_020d0130` | `GetPanelCameraState` | ARM / 0x10 | `src/overlays/ov044/calls/GetPanelCameraState.c` | `eu/src/overlays/ov044/PanelState.h:16` |
| `func_ov044_020d069c` | `ReleaseOv044PanelCameraNoop` | ARM / 0x4 | `src/overlays/ov044/auto/ReleaseOv044PanelCameraNoop.c` | `eu/src/overlays/ov021/calls/func_ov021_020af3a0.c:24` |
| `func_ov046_020c170c` | `Camera_GetViewPlaneNormals` | THUMB / 0xc | `src/overlays/ov046/auto/Camera_GetViewPlaneNormals.c` | `src/arm9/spatial_queries/IsWithinPlaneSet_0203e958.c:48` |
| `func_ov046_020c2ad8` | `Camera_UsesDefaultFocusInPreset19Or21` | THUMB / 0x26 | `src/overlays/ov046/calls/Camera_UsesDefaultFocusInPreset19Or21.c` | `src/ov046/shared_engine/Camera_GetFocusPosition_020c1780.c:14` |
| `func_ov049_020c359c` | `InitEventCameraMotionPreset2` | THUMB / 0x1c | `src/overlays/ov049/calls/InitEventCameraMotionPreset2.c` | `eu/src/overlays/ov049/data/tables/gCameraMotionInitializers.c:13` |
| `func_ov049_020c35b8` | `InitEventCameraMotionPreset3` | THUMB / 0x1c | `src/overlays/ov049/calls/InitEventCameraMotionPreset3.c` | `eu/src/overlays/ov049/data/tables/gCameraMotionInitializers.c:14` |
| `func_ov052_020ca330` | `ResetSlotModelState` | THUMB / 0xc | `src/overlays/ov052/auto/ResetSlotModelState.c` | `src/ov052/model_display/SetSlotDisplayMode_020ca7d0.c:45` |
| `func_ov052_020ceb74` | `GetActorModelPosition` | THUMB / 0xa | `src/overlays/ov052/auto/GetActorModelPosition.c` | `src/ov052/unclassified_helpers/func_ov052_020ceb54.c:4` |
| `func_ov052_020ceb80` | `SetActorModelPosition` | THUMB / 0x10 | `src/overlays/ov052/calls/SetActorModelPosition.c` | `eu/src/overlays/ov052/calls/SetActorModelPosition.c:5` |
| `func_ov053_020d2200` | `RegisterOverlay053ActorFactory` | ARM / 0x14 | `src/overlays/ov053/calls/RegisterOverlay053ActorFactory.c` | `eu/src/overlays/ov053/calls/RegisterOverlay053ActorFactory.c:5` |
| `func_ov054_020d2200` | `RegisterOverlay054ActorFactory` | ARM / 0x14 | `src/overlays/ov054/calls/RegisterOverlay054ActorFactory.c` | `eu/src/overlays/ov054/calls/RegisterOverlay054ActorFactory.c:5` |
| `func_ov054_020d24fc` | `DrawOverlay054ActorAndSceneModels` | ARM / 0x10 | `src/overlays/ov054/calls/DrawOverlay054ActorAndSceneModels.c` | `src/ov054/object_factory/InitOverlay054Entity_020d21f4.c:92` |
| `func_ov055_020d3740` | `RegisterOverlay055EntityFactory` | ARM / 0x14 | `src/overlays/ov055/calls/RegisterOverlay055EntityFactory.c` | `eu/src/overlays/ov055/calls/RegisterOverlay055EntityFactory.c:5` |
| `func_ov056_020d3b3c` | `SetGrabSweepStepScale` | THUMB / 0x8 | `src/overlays/ov056/auto/SetGrabSweepStepScale.c` | `src/ov056/shared_engine/PullActorTowardSource_020d383c.c:53` |
| `func_ov056_020d4478` | `UpdateSceneGroupAndModelSlotAnimations` | THUMB / 0x18 | `src/overlays/ov056/calls/UpdateSceneGroupAndModelSlotAnimations.c` | `eu/src/overlays/ov056/calls/UpdateSceneGroupAndModelSlotAnimations.c:6` |
| `func_ov056_020d4aa0` | `FreeSceneModelSlotArray` | THUMB / 0x10 | `src/overlays/ov056/calls/FreeSceneModelSlotArray.c` | `eu/src/overlays/ov056/calls/FreeSceneModelSlotArray.c:2` |
| `func_ov056_020d6ed8` | `CountBurstTargetAndStopSearch` | THUMB / 0xa | `src/overlays/ov056/auto/CountBurstTargetAndStopSearch.c` | `src/ov056/shared_engine/UpdateBurstProjectile_020d6ec4.c:87` |
| `func_ov057_020d3f40` | `RegisterOverlay057EntityFactory` | ARM / 0x14 | `src/overlays/ov057/calls/RegisterOverlay057EntityFactory.c` | `eu/src/overlays/ov057/calls/RegisterOverlay057EntityFactory.c:5` |
| `func_ov058_020d7740` | `DrawSceneIntroEffectSlot` | ARM / 0x18 | `src/overlays/ov058/calls/DrawSceneIntroEffectSlot.c` | `src/ov058/unclassified_helpers/DrawSceneModels_020d8774.c:25` |
| `func_ov058_020d79a0` | `DrawSceneIntroRaisedModel` | ARM / 0x18 | `src/overlays/ov058/calls/DrawSceneIntroRaisedModel.c` | `src/ov058/unclassified_helpers/DrawSceneModels_020d8774.c:26` |
| `func_ov059_020c7480` | `RegisterOverlay059ActorFactory` | ARM / 0x14 | `src/overlays/ov059/calls/RegisterOverlay059ActorFactory.c` | `eu/src/overlays/ov059/calls/RegisterOverlay059ActorFactory.c:5` |
| `func_ov059_020c8578` | `MarkSideWallProbeHit` | THUMB / 0x8 | `src/overlays/ov059/auto/MarkSideWallProbeHit.c` | `src/ov059/unclassified_helpers/Actor_ResolveSideWall_020c8560.c:133` |
| `func_ov059_020c8b9c` | `ResetActorJointBlendState` | THUMB / 0xc | `src/overlays/ov059/auto/ResetActorJointBlendState.c` | `src/ov059/unclassified_helpers/Actor_SetJointBlendMode_020c8f9c.c:40` |
| `func_ov059_020cbdf0` | `ResetActorSlotTableIds` | THUMB / 0x10 | `src/overlays/ov059/calls/ResetActorSlotTableIds.c` | `eu/src/overlays/ov059/calls/ResetActorSlotTableIds.c:5` |
| `func_ov059_020cbea0` | `UpdateGlobalActorGaugePanel` | THUMB / 0x18 | `src/overlays/ov059/calls/UpdateGlobalActorGaugePanel.c` | `eu/src/overlays/ov059/calls/UpdateGlobalActorGaugePanel.c:6` |
| `func_ov059_020cdc6c` | `CompareEffectSlotZDescending` | THUMB / 0x10 | `src/overlays/ov059/calls/CompareEffectSlotZDescending.c` | `eu/src/overlays/ov059/calls/EffectGroup_Draw.c:88` |
| `func_ov059_020cf3b4` | `EntryList_RemoveByKey` | THUMB / 0x48 | `src/overlays/ov059/calls/EntryList_RemoveByKey.c` | `eu/src/overlays/ov059/calls/EntryList_RemoveByKey.c:6` |
| `func_ov062_020d8120` | `StartOv062SlotGroupCameraAction` | THUMB / 0x34 | `src/overlays/ov062/calls/StartOv062SlotGroupCameraAction.c` | `src/ov062/object_factory/CreateBossBattleObject_020d83dc.c:98` |
| `func_ov063_020d81a0` | `StepSceneTaskEffectEntries` | THUMB / 0xc | `src/overlays/ov063/calls/StepSceneTaskEffectEntries.c` | `src/ov021/object_state/InitEntryPool_020aa9c4.c:54` |
| `func_ov063_020d81ac` | `DrawSceneTaskEffectEntries` | THUMB / 0xc | `src/overlays/ov063/calls/DrawSceneTaskEffectEntries.c` | `src/ov021/object_state/InitEntryPool_020aa9c4.c:55` |
| `func_ov063_020d81b8` | `ResetSceneTaskEffectEntries` | THUMB / 0xc | `src/overlays/ov063/calls/ResetSceneTaskEffectEntries.c` | `src/ov021/object_state/InvokeMemberCleanupCallbacks_020ad908.c:17` |
| `func_ov064_020d86c4` | `ClearMarkedScenePhaseAndLoopHandle` | THUMB / 0xe | `src/overlays/ov064/calls/ClearMarkedScenePhaseAndLoopHandle.c` | `src/ov064/object_state/UpdateOv064BossSequence_020d8234.c:175` |
| `func_ov064_020d86d4` | `StopOverlay064ActorSound` | THUMB / 0x1a | `src/overlays/ov064/calls/StopOverlay064ActorSound.c` | `eu/src/overlays/ov064/calls/StopOverlay064ActorSound.c:5` |
| `func_ov065_020d8120` | `StartOv065SlotGroupCameraAction` | THUMB / 0x34 | `src/overlays/ov065/calls/StartOv065SlotGroupCameraAction.c` | `src/ov065/object_factory/CreateAuraBattleObject_020d8400.c:127` |
| `func_ov070_020d8120` | `IsOv070BossTaskId10F` | THUMB / 0x14 | `src/overlays/ov070/calls/IsOv070BossTaskId10F.c` | `src/ov070/object_factory/CreateOv070BossObject_020d8894.c:87` |
| `func_ov071_020d8120` | `IsOv071BossTaskId110` | THUMB / 0x12 | `src/overlays/ov071/calls/IsOv071BossTaskId110.c` | `src/ov071/object_factory/CreateOv071SceneTask_020d954c.c:66` |
| `func_ov071_020d8388` | `SetOv071BossTimeStep` | THUMB / 0x4 | `src/overlays/ov071/auto/SetOv071BossTimeStep.c` | `src/ov071/object_state/UpdateOv071BossState_020d836c.c:354` |

## Reproducible byte-exact validation

Run the existing tools from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov041/auto/FinalizeAreaSceneInfoNoop.c FinalizeAreaSceneInfoNoop --thumb
python tools/verify_idx.py src/overlays/ov041/calls/InitializeStageEntryOutState.c InitializeStageEntryOutState --thumb
python tools/verify_idx.py src/overlays/ov041/calls/UnlinkRecordOwnerRootSlot.c UnlinkRecordOwnerRootSlot --thumb
python tools/verify_idx.py src/overlays/ov042/calls/GetCameraFlag800.c GetCameraFlag800 --thumb
python tools/verify_idx.py src/overlays/ov042/auto/SetCameraFollowLock.c SetCameraFollowLock --thumb
python tools/verify_idx.py src/overlays/ov042/calls/SetCameraFollowMaxY.c SetCameraFollowMaxY --thumb
python tools/verify_idx.py src/overlays/ov042/calls/GetCameraFollowFlags.c GetCameraFollowFlags --thumb
python tools/verify_idx.py src/overlays/ov042/calls/StartCameraDriftShake.c StartCameraDriftShake --thumb
python tools/verify_idx.py src/overlays/ov042/calls/IsCameraShakeActive.c IsCameraShakeActive --thumb
python tools/verify_idx.py src/overlays/ov042/calls/SetCameraHorizontalFollowBounds.c SetCameraHorizontalFollowBounds --thumb
python tools/verify_idx.py src/overlays/ov042/calls/GetCameraAdjustedHorizontalBounds.c GetCameraAdjustedHorizontalBounds --thumb
python tools/verify_idx.py src/overlays/ov042/auto/ReleaseOv042CameraNoop.c ReleaseOv042CameraNoop --thumb
python tools/verify_idx.py src/overlays/ov043/auto/ReleaseOv043CameraNoop.c ReleaseOv043CameraNoop
python tools/verify_idx.py src/overlays/ov044/calls/CommitPanelProjectionAndViewAxes.c CommitPanelProjectionAndViewAxes
python tools/verify_idx.py src/overlays/ov044/calls/CommitPanelCameraFrame.c CommitPanelCameraFrame
python tools/verify_idx.py src/overlays/ov044/calls/GetPanelCameraState.c GetPanelCameraState
python tools/verify_idx.py src/overlays/ov044/auto/ReleaseOv044PanelCameraNoop.c ReleaseOv044PanelCameraNoop
python tools/verify_idx.py src/overlays/ov046/auto/Camera_GetViewPlaneNormals.c Camera_GetViewPlaneNormals --thumb
python tools/verify_idx.py src/overlays/ov046/calls/Camera_UsesDefaultFocusInPreset19Or21.c Camera_UsesDefaultFocusInPreset19Or21 --thumb
python tools/verify_idx.py src/overlays/ov049/calls/InitEventCameraMotionPreset2.c InitEventCameraMotionPreset2 --thumb
python tools/verify_idx.py src/overlays/ov049/calls/InitEventCameraMotionPreset3.c InitEventCameraMotionPreset3 --thumb
python tools/verify_idx.py src/overlays/ov052/auto/ResetSlotModelState.c ResetSlotModelState --thumb
python tools/verify_idx.py src/overlays/ov052/auto/GetActorModelPosition.c GetActorModelPosition --thumb
python tools/verify_idx.py src/overlays/ov052/calls/SetActorModelPosition.c SetActorModelPosition --thumb
python tools/verify_idx.py src/overlays/ov053/calls/RegisterOverlay053ActorFactory.c RegisterOverlay053ActorFactory
python tools/verify_idx.py src/overlays/ov054/calls/RegisterOverlay054ActorFactory.c RegisterOverlay054ActorFactory
python tools/verify_idx.py src/overlays/ov054/calls/DrawOverlay054ActorAndSceneModels.c DrawOverlay054ActorAndSceneModels
python tools/verify_idx.py src/overlays/ov055/calls/RegisterOverlay055EntityFactory.c RegisterOverlay055EntityFactory
python tools/verify_idx.py src/overlays/ov056/auto/SetGrabSweepStepScale.c SetGrabSweepStepScale --thumb
python tools/verify_idx.py src/overlays/ov056/calls/UpdateSceneGroupAndModelSlotAnimations.c UpdateSceneGroupAndModelSlotAnimations --thumb
python tools/verify_idx.py src/overlays/ov056/calls/FreeSceneModelSlotArray.c FreeSceneModelSlotArray --thumb
python tools/verify_idx.py src/overlays/ov056/auto/CountBurstTargetAndStopSearch.c CountBurstTargetAndStopSearch --thumb
python tools/verify_idx.py src/overlays/ov057/calls/RegisterOverlay057EntityFactory.c RegisterOverlay057EntityFactory
python tools/verify_idx.py src/overlays/ov058/calls/DrawSceneIntroEffectSlot.c DrawSceneIntroEffectSlot
python tools/verify_idx.py src/overlays/ov058/calls/DrawSceneIntroRaisedModel.c DrawSceneIntroRaisedModel
python tools/verify_idx.py src/overlays/ov059/calls/RegisterOverlay059ActorFactory.c RegisterOverlay059ActorFactory
python tools/verify_idx.py src/overlays/ov059/auto/MarkSideWallProbeHit.c MarkSideWallProbeHit --thumb
python tools/verify_idx.py src/overlays/ov059/auto/ResetActorJointBlendState.c ResetActorJointBlendState --thumb
python tools/verify_idx.py src/overlays/ov059/calls/ResetActorSlotTableIds.c ResetActorSlotTableIds --thumb
python tools/verify_idx.py src/overlays/ov059/calls/UpdateGlobalActorGaugePanel.c UpdateGlobalActorGaugePanel --thumb
python tools/verify_idx.py src/overlays/ov059/calls/CompareEffectSlotZDescending.c CompareEffectSlotZDescending --thumb
python tools/verify_idx.py src/overlays/ov059/calls/EntryList_RemoveByKey.c EntryList_RemoveByKey --thumb
python tools/verify_idx.py src/overlays/ov062/calls/StartOv062SlotGroupCameraAction.c StartOv062SlotGroupCameraAction --thumb
python tools/verify_idx.py src/overlays/ov063/calls/StepSceneTaskEffectEntries.c StepSceneTaskEffectEntries --thumb
python tools/verify_idx.py src/overlays/ov063/calls/DrawSceneTaskEffectEntries.c DrawSceneTaskEffectEntries --thumb
python tools/verify_idx.py src/overlays/ov063/calls/ResetSceneTaskEffectEntries.c ResetSceneTaskEffectEntries --thumb
python tools/verify_idx.py src/overlays/ov064/calls/ClearMarkedScenePhaseAndLoopHandle.c ClearMarkedScenePhaseAndLoopHandle --thumb
python tools/verify_idx.py src/overlays/ov064/calls/StopOverlay064ActorSound.c StopOverlay064ActorSound --thumb
python tools/verify_idx.py src/overlays/ov065/calls/StartOv065SlotGroupCameraAction.c StartOv065SlotGroupCameraAction --thumb
python tools/verify_idx.py src/overlays/ov070/calls/IsOv070BossTaskId10F.c IsOv070BossTaskId10F --thumb
python tools/verify_idx.py src/overlays/ov071/calls/IsOv071BossTaskId110.c IsOv071BossTaskId110 --thumb
python tools/verify_idx.py src/overlays/ov071/auto/SetOv071BossTimeStep.c SetOv071BossTimeStep --thumb
bash tools/gate.sh
```

All 52 official function checks pass. The fresh gate passes all 108 linked
modules; affected function bytes, resolved relocation targets/types and addends,
and all module hashes remain identical to the preserved pre-rename baseline.
Empty callback presence, borrowed storage and raw returns are preserved. No
C/DATA reconstruction credit or signature/algorithm change is part of this block.
