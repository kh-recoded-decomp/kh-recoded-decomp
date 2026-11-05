# Actor motion, entry requests and related owner contracts

This block covers the 34 entrypoints in the combined actor-operations naming plan. The main actors in overlays 052 and 059, derived enemy work in 058, generic entry lists, scene-intro work and ScriptTask entries are separate owners. Matching addresses or similar private typedefs do not establish interchangeable layouts.

The names describe the observed operations and caller relationships. They do not claim original source spellings or identify opaque gameplay states. EU source paths below use the current names. The verification section gives
the existing per-function and full-module integration checks.

## Native owner boundaries

All offsets below are native Nintendo DS offsets. These are partial views, not complete host structures or allocation sizes.

| Owner | Fields established here | Boundaries |
|---|---|---|
| Individual overlay052 actor | Model pointer +0x230; action ID +0x75c, frame +0x760, blend table +0x764, animation-event word +0x768; state flags +0x9ac; velocity +0x9c8; cached slot-3 position +0xa00. | The velocity and cached position are separate vectors. The model position is on the model object, not either actor vector. |
| Individual overlay059 actor | Model pointer +0x230 and the animation bookkeeping above; status flags +0x928; player index +0x930; pending/latch +0x934/+0x938; movement storage starts at +0x970; control bookkeeping word +0x1704. | Actor +0x234 mask 4 is not proved to be a held-button flag. State at +0x1dc and extended mode at +0x944 are distinct views. |
| Overlay058 enemy | Target-kind discriminator +0x1048; AI mode at +0x1258 and flags at +0x125c. Arrival mask is 0x1000 in those AI flags. | Clearing a target kind does not clear every payload byte. A local targetReached label does not make the discriminator a BOOL. |
| Overlay071 SceneTask | Four group IDs at +0x40..+0x46; packed signed entry indices at +0x80. | The cleanup dispatcher passes `(container, currentEntry)`. The function's second argument is SceneTask work, not an individual actor. |
| Generic EntryList | Eight-byte entries from +0x60; u8 count at +0x120. | Seeker work and reward owners embed this view at different offsets. No full capacity or whole-owner layout is recovered here. |
| Shared scene-intro owner | Signed mode byte at +0; separate phase at +0x30. | Neither is the enemy AI mode at +0x1258. |

The singleton ActorManager's embedded script VM is a different owner. Its scratch/skip fields must not be substituted for the individual actor animation or movement fields just because numerical offsets overlap.

## Animation and movement storage

The real blend-call order is actor, table, track, blend index and blend-frame count. The first wrapper below clears action ID to -1; the second stores category code 0x12. Both clear the animation-event word. That bookkeeping does not by itself stop animation advancement or select an arbitrary table entry zero.

The movement initializer uses a partial record beginning with two VecFx32 values, an elapsed word at +0x18, speed halfword at +0x1c, timer at +0x20 and signed mode at +0x24. Live actor users interpret the two vectors as velocity and drift/delta. They are not proved world positions by the local position/destination names. The initializer deliberately leaves the timer untouched.

The separate StepTimer is eight bytes: elapsed32, a middle halfword and duration16. The ordinary and carry consumers give the middle halfword different interpretations. Preserve the native narrowing, comparison against duration shifted by 12 and each consumer's signedness.

## Group-entry spawn requests are not animation-track states

The shared reset and spawn helpers consume a 0x2c-byte group-entry request. Existing `TrackState` and `ResetAnimationTrackState` spellings describe this poorly. The actual InitEntryFromDesc consumer establishes the following request fields:

| Request offset | Field used by the consumer |
|---|---|
| +0x00 | Actor/anchor selector byte; also the requested index when the group uses fixed slots. |
| +0x04 | Position or relative offset vector, interpreted according to mode. |
| +0x10 / +0x12 | Scale halfword / angle halfword. |
| +0x14 | Blend rate. |
| +0x18 / +0x1c / +0x20 | Mode-specific parameter words. |
| +0x24 / +0x25 | Signed blend index / mode bytes. |
| +0x26 | Flags halfword. |
| +0x28 / +0x2a | Signed sound archive / sound index halfwords. |

The sweep lifecycle uses actor group +0x1816 and relative mode 1. Contact effects use the distinct group +0x181a and mode 0. A local request is consumed synchronously by InitializeEntryGroupSlot; group policy chooses the fixed requested slot or the first inactive entry. That call returns a slot index or -1, not a hit-status flag. Deactivating an entry is separate from freeing the containing group.

For the seven radial-effect entries, the eight-byte motion record is elapsed plus angle. The paired step worker proves those roles; the caller's angle/radius labels do not. Its two angle products use the same stored angle, while its radius changes. This supports radial growth rather than a demonstrated spiral. Preserve the separately rounded products instead of algebraically combining them.

## Collision callback argument and return contracts

CollisionQuery +0x48, +0x50 and +0x58 are distinct callback pairs. The misleading `filter` field in the Seeker private view follows twenty words and therefore begins at +0x50, not +0x48.

InitMoverFromParams copies query +0x50/+0x54 into mover +0xbc/+0xc0. DispatchContactCallbacks invokes that decision callback as `(entry, plane, userData, sweep, moving, planes, entries, index)`. In this callback family, r1 is ContactPlane* and r3 is CollSweep*. The sweep delta is at +0x20.

The object decision callback is separate: `(object, moverOwner, plane, objectUserData, sweep, moving, planes, entries, index)`. Actor_Init binds the actor as objectUserData for Actor_SpawnSweepContactEffect. Its fifth input is the sweep; reading its shape-data pointer obtains the first shape reference vector. This is not a separately computed surface hit point.

A decision result of 1 allows RecordContactPlane to continue ordinary recording; other values return immediately from that path. RecordHitContact advances the plane index for 1 and stops its current traversal path for 2. ResolvePlaneContacts also stops on 2. These facts do not justify replacing every callback with a BOOL or merging the decision callback with the later post-resolution notification.

Actor_DispatchSharedControlAction has an independent contract: it always returns integer 0. Actor_UpdateJumpCommandInput returns its probe result, currently FALSE. Preserve these values even where a more intuitive action-performed result might seem useful.

## Entrypoints and per-function evidence

Evidence paths are repository-root relative. Each EU implementation below is identified by its original overlay-qualified address and its intended post-rename source path. Shared source filenames remain useful provenance even where their old typedefs or symbol spellings are misleading.

### Overlay052 actor and timer operations

#### `FilterEntityEventAndClearInhibitFlag`

Previous `func_ov052_020c9648`; native THUMB, 84 bytes. EU source: `eu/src/overlays/ov052/calls/FilterEntityEventAndClearInhibitFlag.c`.

Returns false for events 10, 14 and 27, or when the 64-bit state flags contain mask 0x04000000. It clears that mask on every path, including rejected events. Preserve the upper 32 flag bits and the clear-after-test behavior.

Evidence: `eu/src/overlays/ov052/calls/FilterEntityEventAndClearInhibitFlag.c:8`.

#### `UpdateEntityFadeAndPostUpdate`

Previous `func_ov052_020c97c4`; native THUMB, 144 bytes. EU source: `eu/src/overlays/ov052/calls/UpdateEntityFadeAndPostUpdate.c`.

When mask 0x20820 is clear, handles mask 0x10 by calling the state callback with 10 and then clearing the mask, followed by the existing fade update. The optional post-update callback runs outside that guard. Moving it inside the guard changes behavior.

Evidence: `eu/src/overlays/ov052/calls/UpdateEntityFadeAndPostUpdate.c:20`.

#### `ApplyPendingEntityMotion`

Previous `func_ov052_020c9854`; native THUMB, 64 bytes. EU source: `eu/src/overlays/ov052/calls/ApplyPendingEntityMotion.c`.

Checks mask 0x20800 and the pending-count halfword at command +2, then calls ApplyLinkedObjectMotion and the existing post-motion hook in that order. The command pointer is at actor +0x1d4. This does not establish the complete command allocation or permit deleting the hook.

Evidence: `eu/src/overlays/ov052/calls/ApplyPendingEntityMotion.c:18`.

#### `AddActorVelocity`

Previous `func_ov052_020ccfa0`; native ARM, 28 bytes. EU source: `eu/src/overlays/ov052/calls/AddActorVelocity.c`.

Adds the supplied vector in place to overlay052 actor velocity at +0x9c8. UpdateDriftState independently treats this vector as velocity and changes its X/Z components. It is not the model position at model +0xa8 or the cached slot-3 position at actor +0xa00.

Evidence: `eu/src/overlays/ov052/calls/AddActorVelocity.c:6`; `eu/src/overlays/ov052/calls/UpdateDriftState.c`; `eu/src/overlays/ov052/calls/ConfigureCameraMode.c`.

#### `InstallActorJointMatrixCaptureCallback`

Previous `func_ov052_020d073c`; native THUMB, 44 bytes. EU source: `eu/src/overlays/ov052/calls/InstallActorJointMatrixCaptureCallback.c`.

Stores the actor context at model +0x50, resets the render callback at model +0x24, then installs CaptureContextJointMtx with the existing 0, 6 and 3 arguments. These offsets identify the fields actually used; they do not describe the entire model object.

Evidence: `eu/src/overlays/ov052/calls/InstallActorJointMatrixCaptureCallback.c:7`.

#### `InitStepTimer`

Previous `func_ov052_020ccab0`; native THUMB, 10 bytes. EU source: `eu/src/overlays/ov052/auto/InitStepTimer.c`.

Writes elapsed32 = 0, the middle halfword = 0 and duration16 = the supplied duration into an eight-byte record. Duration narrows to u16. AdvanceStepTimer and the carry variant use the middle halfword differently; preserve those uses instead of imposing one universal count or remainder type.

Evidence: `src/ov052/unclassified_helpers/AdvanceStepTimer_020ccac8.c:13`; `src/ov052/unclassified_helpers/AdvanceTimerWithCarry_020cca9c.c`; `src/ov052/unclassified_helpers/ResetActorCombatState_020ccae8.c`.

#### `GetCachedSlot3WorldPosition`

Previous `func_ov052_020ccfbc`; native ARM, 8 bytes. EU source: `eu/src/overlays/ov052/auto/GetCachedSlot3WorldPosition.c`.

Returns actor +0xa00 as a borrowed VecFx32. DrawActor fills this cache from GetSlot3WorldPosition, and InstallActorCallbacks installs this accessor as the origin getter at +0x224. It can be stale until the render writer runs; it is distinct from computing the current slot position.

Evidence: `src/ov052/model_display/DrawActor_020ccd24.c:48`; `src/ov052/unclassified_helpers/InstallActorCallbacks_020cce6c.c`; `src/ov052/actor_motion/FindDashWallTarget_020c8040.c`.

#### `BlendActorTrackAndClearActionId`

Previous `func_ov052_020ce188`; native THUMB, 32 bytes. EU source: `eu/src/overlays/ov052/calls/BlendActorTrackAndClearActionId.c`.

Calls SetBlendTableAndBlendTrack with the real table, track, blend-index and blend-frame arguments, then writes action ID -1 at +0x75c and clears the animation-event word at +0x768. Clearing this ID is not a request to stop all animation advancement.

Evidence: `eu/src/overlays/ov052/calls/BlendActorTrackAndClearActionId.c:5`; `eu/src/overlays/ov052/calls/SetBlendTableAndBlendTrack.c`; `eu/src/overlays/ov052/calls/ChangeActorState.c`.

#### `GetOv052ActorVelocity`

Previous `func_ov052_020ceb90`; native THUMB, 12 bytes. EU source: `eu/src/overlays/ov052/calls/GetOv052ActorVelocity.c`.

The defining EU helper now exposes `VecFx32 *GetOv052ActorVelocity(void *actor)`,
returning the borrowed +0x9c8 velocity vector. The three generated unused argument
slots are removed from its definition without changing its 12-byte result. The qualified name distinguishes the existing GetActorVelocity in overlay017. The pointer aliases live actor storage; it neither computes a position nor transfers ownership.

Evidence: `eu/src/overlays/ov052/calls/GetOv052ActorVelocity.c:2`; `eu/src/overlays/ov052/calls/UpdateDriftState.c`.

### Overlay059 control, motion, group entries and lists

#### `InitMotionTargetState`

Previous `func_ov059_020c934c`; native THUMB, 72 bytes. EU source: `eu/src/overlays/ov059/calls/InitMotionTargetState.c`.

Zeros the first two vectors and elapsed word, sets the speed halfword to 0x2000 and the signed mode byte to -1. It does not clear the timer word or the whole record. In live movement users the vectors serve velocity and drift/delta roles; the private position/destination labels are not proof of world-space positions.

Evidence: `eu/src/overlays/ov059/calls/InitMotionTargetState.c:16`.

#### `HandleMotionTargetEvent`

Previous `func_ov059_020c9394`; native THUMB, 100 bytes. EU source: `eu/src/overlays/ov059/calls/HandleMotionTargetEvent.c`.

Always clears speed. It resets mode to -1 except for event 12, then applies the existing event-specific changes: event 1 sets elapsed to 0x333; 2 and 3 set mode and clear timer; 4 clears the first vector Y component and selects mode 3. Unrecognized events still perform the initial reset.

Evidence: `eu/src/overlays/ov059/calls/HandleMotionTargetEvent.c:14`.

#### `SetActorCommandTypeFromCommandId`

Previous `func_ov059_020cd384`; native THUMB, 84 bytes. EU source: `eu/src/overlays/ov059/calls/SetActorCommandTypeFromCommandId.c`.

Maps command IDs 0x1f8 through 0x1fb to stored command types 0 through 3 on the global overlay059 actor. Other IDs are ignored. The numerical mapping does not establish names for the four gameplay commands.

Evidence: `eu/src/overlays/ov059/calls/SetActorCommandTypeFromCommandId.c:6`.

#### `EntryList_FindByPair`

Previous `func_ov059_020cf46c`; native THUMB, 66 bytes. EU source: `eu/src/overlays/ov059/calls/EntryList_FindByPair.c`.

Searches eight-byte entries starting at list +0x60 using the u8 count at +0x120. It accepts kind 2 entries whose two u16 keys match and returns the first index, otherwise -1. This is a generic EntryList helper used by different owners, not an Actor method or a recovered full-capacity API.

Evidence: `eu/src/overlays/ov059/calls/EntryList_FindByPair.c:3`; `src/ov059/unclassified_helpers/EntryList_FindByKey_020cf3e8.c:17`; `src/ov059/unclassified_helpers/EntryList_FindByValue_020cf41c.c:13`.

#### `PlayActorTrackAsExtraAction`

Previous `func_ov059_020cca14`; native THUMB, 32 bytes. EU source: `eu/src/overlays/ov059/calls/PlayActorTrackAsExtraAction.c`.

Calls Actor_PlayAnimation with the real five inputs, stores bookkeeping action ID 0x12 at +0x75c and clears +0x768. Actor_ChangeMotion treats 0x12 as the first extra-action category code. The supplied table, track and blend index still select playback; the wrapper does not force extra-table element zero.

Evidence: `eu/src/overlays/ov059/calls/PlayActorTrackAsExtraAction.c:5`; `eu/src/overlays/ov059/calls/Actor_PlayAnimation.c`; `eu/src/overlays/ov059/calls/Actor_ChangeAnimation.c`.

#### `Actor_UpdateState5RootMotion`

Previous `func_ov059_020c9748`; native THUMB, 344 bytes. EU source: `eu/src/overlays/ov059/calls/Actor_UpdateState5RootMotion.c`.

Installed specifically by Actor_ChangeState case 5. It clears velocity, copies the root-motion delta, and can latch status mask 2 after frame 9 when the control/target conditions hold. It finishes at frame 15 with that latch or frame 18 without it, also respecting animation end. It then repeats state 5 and notifies the follow-up callback, or returns to state 1; loss of actor mask 4 selects state 3.

Evidence: `src/ov059/unclassified_helpers/Actor_ChangeState_020cbff8.c:244`; `eu/src/overlays/ov059/calls/Actor_ChangeState.c`; `eu/src/overlays/ov059/calls/Actor_UpdateState5RootMotion.c`.

#### `Actor_DispatchSharedControlAction`

Previous `func_ov059_020c98a0`; native THUMB, 252 bytes. EU source: `eu/src/overlays/ov059/calls/Actor_DispatchSharedControlAction.c`.

Dispatches shared control record IDs 1 through 4 into the proven pending/latch, target-link, state-marking and field-menu operations. It always returns integer 0, even after performing an operation. Existing callers test this value, so do not change it to an action-performed result or silently remove their guard.

Evidence: `eu/src/overlays/ov059/calls/Actor_DispatchSharedControlAction.c:53`; `eu/src/overlays/ov059/calls/Actor_SelectInputState.c`; `src/ov059/unclassified_helpers/Actor_SelectInputState_020ca22c.c:28`.

#### `Actor_LatchSharedControlId1Trigger`

Previous `func_ov059_020c999c`; native THUMB, 80 bytes. EU source: `eu/src/overlays/ov059/calls/Actor_LatchSharedControlId1Trigger.c`.

When record ID 1 is present, record mask 0x400 at +0xe is clear and actor latch +0x938 is clear, sets that latch and clears actor word +0x1704. It does not set the separate pending byte +0x934. The role of +0x1704 beyond its actual users is not inferred from a timer label.

Evidence: `eu/src/overlays/ov059/calls/Actor_LatchSharedControlId1Trigger.c:21`; `eu/src/overlays/ov059/calls/Actor_TryEnterState5.c`; `src/ov059/unclassified_helpers/Actor_TryEnterState5_020ca700.c:25`.

#### `Actor_UpdateSweepEffectLifecycle`

Previous `func_ov059_020c9a74`; native THUMB, 280 bytes. EU source: `eu/src/overlays/ov059/calls/Actor_UpdateSweepEffectLifecycle.c`.

Starts or finishes the persistent sweep-effect entry in group +0x1816. Start creates slot 0 only while inactive, sets actor mask 0x4000 at +0x171c, clears +0x1720 and sends a relative-mode spawn request with sound 0xcd:0. A finish request waits for the last animation frame, then removes the quadtree node, changes entry state/flags and fades that sound. Before the last frame it clears entry mask 4.

Evidence: `src/ov059/unclassified_helpers/Actor_UpdateSweepHits_020c9d14.c:312`; `eu/src/overlays/ov059/calls/Actor_UpdateChargeCommand.c`; `src/ov059/unclassified_helpers/Actor_UpdateChargeCommand_020c9b6c.c:46`.

#### `Actor_SpawnSweepContactEffect`

Previous `func_ov059_020ca208`; native THUMB, 68 bytes. EU source: `eu/src/overlays/ov059/calls/Actor_SpawnSweepContactEffect.c`.

This object contact-decision callback receives the actor as fourth argument and CollSweep* as fifth. It copies the first VecFx32 from sweep->shape.data into a mode-0 spawn request for group +0x181a, with sound 0xcd:1, and returns 1. That vector is the moving shape reference point/centre/start, not a computed surface intersection. The request is copied synchronously; it does not retain the local request address.

Evidence: `src/ov059/unclassified_helpers/Actor_Init_020cba3c.c:162`; `eu/src/overlays/ov059/calls/Actor_Init.c`; `eu/src/overlays/ov059/calls/Actor_SpawnSweepContactEffect.c`.

#### `Actor_UpdateJumpCommandInput`

Previous `func_ov059_020ca31c`; native THUMB, 64 bytes. EU source: `eu/src/overlays/ov059/calls/Actor_UpdateJumpCommandInput.c`.

Called before gravity processing by Actor_UpdateJump with its JumpState. It fetches the control record, conditionally invokes the existing always-FALSE probe for phases 1/2 outside actor mode 8, always updates the charge command, and returns the probe result. The second argument is not a hit event. Preserve the probe, checks and returned guard without inventing an ability identity.

Evidence: `src/ov059/unclassified_helpers/Actor_UpdateJump_020ca33c.c:71`; `eu/src/overlays/ov059/calls/Actor_UpdateJump.c`; `src/ov059/unclassified_helpers/Actor_UpdateJump_020ca33c.c:9`.

#### `InitRadialEffectMotion`

Previous `func_ov059_020cac3c`; native THUMB, 28 bytes. EU source: `eu/src/overlays/ov059/calls/InitRadialEffectMotion.c`.

Initializes an eight-byte motion record with elapsed = -0x1000 and angle = index * 0x861 - 0x3244. Actor_InitOrbitSlots supplies seven consecutive records, one per group entry. Orbit_StepSpiralOffset increments elapsed first, eases over 0x1b000 and converts the second word through the sine-table angle scale. The caller-local angle/radius names do not describe these two words, and the existing worker name does not establish spiral motion.

Evidence: `src/ov059/unclassified_helpers/Orbit_StepSpiralOffset_020cac38.c:7`; `eu/src/overlays/ov059/calls/Actor_InitOrbitSlots.c`; `src/ov059/unclassified_helpers/Actor_InitOrbitSlots_020cab6c.c:26`.

#### `DoubleSeekerContactDistance`

Previous `func_ov059_020cec50`; native THUMB, 10 bytes. EU source: `eu/src/overlays/ov059/auto/DoubleSeekerContactDistance.c`.

Registered in the misleadingly named filter member that actually begins at query +0x50. The decision dispatcher passes ContactPlane* as the second argument, so this shifts plane.distance left by one and returns 1. NULL is the third userData argument. It does not modify a mask or query flags, and the separate +0x58 callback performs velocity reflection.

Evidence: `src/ov059/unclassified_helpers/Seeker_Update_020cde6c.c:330`; `eu/src/overlays/ov059/calls/Seeker_Update.c`; `src/ov059/unclassified_helpers/Seeker_Update_020cde6c.c:35`.

### Overlay058 enemy and scene-intro views

#### `IsEnemyTargetOutsideRaisedBand`

Previous `func_ov058_020d4968`; native ARM, 116 bytes. EU source: `eu/src/overlays/ov058/calls/IsEnemyTargetOutsideRaisedBand.c`.

For target kinds 2 and 3, returns false only when the supplied target Y lies in [actor Y +0x1000, actor Y +0x2000). Other target kinds return true. The half-open bounds and absence of an X/Z test are part of the contract.

Evidence: `eu/src/overlays/ov058/calls/IsEnemyTargetOutsideRaisedBand.c:11`.

#### `AcquireEnemyTargetWithFallback`

Previous `func_ov058_020d49dc`; native ARM, 120 bytes. EU source: `eu/src/overlays/ov058/calls/AcquireEnemyTargetWithFallback.c`.

Copies a preferred target when the query succeeds and its kind is not 4. Otherwise it tries the nearest eligible team target using selector 3 and returns whether one was found. The old ReadActiveMenuState label does not establish a menu owner, and the numerical selectors are not assigned gameplay names.

Evidence: `eu/src/overlays/ov058/calls/AcquireEnemyTargetWithFallback.c:20`.

#### `UpdateEnemyPlayerFacingMode`

Previous `func_ov058_020d4ffc`; native ARM, 64 bytes. EU source: `eu/src/overlays/ov058/calls/UpdateEnemyPlayerFacingMode.c`.

Changes AI mode 4 back to 1 before the facing query, then sets mode 4 if IsFacedByPlayer succeeds and returns that predicate result. The direction output is a discarded local. Modes other than 4 are preserved on failure.

Evidence: `eu/src/overlays/ov058/calls/UpdateEnemyPlayerFacingMode.c:16`.

#### `ProcessEnemyAiRequest`

Previous `func_ov058_020d503c`; native ARM, 144 bytes. EU source: `eu/src/overlays/ov058/calls/ProcessEnemyAiRequest.c`.

Handles request 3 by setting mask 0x100000 and starting the launch path; request 2 uses the existing status/AI guards, target acquisition and pending-action assignment before setting mask 0x80000. It clears the request even for unrecognized values. Preserve the guard and update order.

Evidence: `eu/src/overlays/ov058/calls/ProcessEnemyAiRequest.c:23`.

#### `GetSceneIntroSequenceMode`

Previous `func_ov058_020d895c`; native ARM, 16 bytes. EU source: `eu/src/overlays/ov058/calls/GetSceneIntroSequenceMode.c`.

Returns the signed mode byte of the shared scene-intro owner, not an enemy AI field. UpdateSceneIntroSequence dispatches this mode and related presentation users consult it. Mode at offset zero is distinct from phase at +0x30; not every numeric value has a recovered gameplay name.

Evidence: `src/ov058/unclassified_helpers/UpdateSceneIntroSequence_020d81a4.c:82`; `eu/src/overlays/ov058/calls/UpdateEnemyApproachState.c`; `eu/src/overlays/ov054/calls/UpdateRewardActorPhase.c`.

#### `Enemy_ClearTargetKindAndArrivalFlag`

Previous `func_ov058_020d546c`; native ARM, 28 bytes. EU source: `eu/src/overlays/ov058/calls/Enemy_ClearTargetKindAndArrivalFlag.c`.

Clears the target-kind byte at +0x1048 and AI arrival mask 0x1000 at +0x125c. UpdateEnemyCombatAi sets that mask on arrival and HasReachedMoveTarget consumes it for kind 1. The helper retains the remaining target payload. Its raw template leaves actor +0x1000 in r0; that does not define a new public subobject API.

Evidence: `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c:264`; `src/ov058/unclassified_helpers/HasReachedMoveTarget_020d483c.c:49`; `src/ov058/unclassified_helpers/UpdateEnemyTargetTracking_020d4b64.c`.

#### `UpdateEnemyDistanceGatedAiMode`

Previous `func_ov058_020d4a54`; native ARM, 304 bytes. EU source: `eu/src/overlays/ov058/calls/UpdateEnemyDistanceGatedAiMode.c`.

Uses distance to managed reference actor 0, AI-generated command movement flags and the status query to update modes 1/3. It retains the 0x80000 exclusion, conditional 0x80 latch and 0x1e000 delay, the target-kind-dependent distance margin, and the near-case input/anchor reset. The command flags are not physical controller buttons.

Evidence: `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c:201`; `eu/src/overlays/ov058/calls/UpdateEnemyDistanceGatedAiMode.c`; `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c:137`.

#### `Enemy_SpawnEvent1EEffectAndDetachCollider`

Previous `func_ov058_020d50cc`; native ARM, 180 bytes. EU source: `eu/src/overlays/ov058/calls/Enemy_SpawnEvent1EEffectAndDetachCollider.c`.

Invokes event 0x1e, clears the AI/target-arrival state, sets status mask 0x60000, spawns a common group entry at the enemy position and retains its returned slot index, clears the AI timer and removes model/object +0x230 from the quadtree. Registry group index 7 is not given a resource identity. Event meaning remains numerical, and no enemy allocation is freed.

Evidence: `src/ov058/unclassified_helpers/ChangeEnemyState_020d65c4.c:139`; `eu/src/overlays/ov058/calls/ChangeEnemyState.c`; `eu/src/overlays/ov058/calls/CheckEnemyContactAbove.c`.

### Related camera, wrapper and SceneTask owners

#### `SetEntityModeWithSceneReset`

Previous `func_ov054_020d250c`; native ARM, 52 bytes. EU source: `eu/src/overlays/ov054/calls/SetEntityModeWithSceneReset.c`.

Calls ResetSceneModelState only for type 2 and subtype 0, then calls SetEntityModeEnabled for every input with the original arguments. Keep the unconditional delegate and do not broaden the reset to other numerical mode values.

Evidence: `eu/src/overlays/ov054/calls/SetEntityModeWithSceneReset.c:6`.

#### `ReleaseSceneObjectAndFreeWork`

Previous `func_ov055_020d3aec`; native ARM, 48 bytes. EU source: `eu/src/overlays/ov055/calls/ReleaseSceneObjectAndFreeWork.c`.

Reads the child pointer from wrapper work +0x50. Child byte +0x3d equal to 4 selects an additional teardown, followed by ReleaseSceneObject and freeing the pointed child. It does not free the wrapper allocation or clear its pointer. The code rereads work +0x50 between calls; do not introduce a cached pointer without checking delegate effects.

Evidence: `eu/src/overlays/ov055/calls/ReleaseSceneObjectAndFreeWork.c:7`.

#### `DeactivateOv071TaskEntriesAndManager`

Previous `func_ov071_020d8290`; native THUMB, 208 bytes. EU source: `eu/src/overlays/ov071/calls/DeactivateOv071TaskEntriesAndManager.c`.

The member-list container is the unused first argument; the current SceneTask is second. For each signed slot byte at task +0x80 other than -1, invokes group-entry cleanup and writes 0xff. Cleanup deactivates the entry and can stop its attached sound. The four calls use group halfwords +0x40, +0x42, +0x42 and +0x46: preserve the repeated +0x42. It then calls the existing gauge reset and SetManagerEnabled(0), without freeing the task.

Evidence: `eu/src/overlays/ov071/calls/DeactivateOv071TaskEntriesAndManager.c:7`; `src/ov071/object_factory/CreateOv071SceneTask_020d954c.c:69`; `src/ov021/object_state/DeactivateCurrentMember_020ad8d8.c`.

#### `FilterPathCameraContactByMotionAndFacing`

Previous `func_ov050_020c35cc`; native THUMB, 50 bytes. EU source: `eu/src/overlays/ov050/calls/FilterPathCameraContactByMotionAndFacing.c`.

Installed at query +0x50 by UpdatePathCameraCollision. The fourth argument is CollSweep*, not an actor: +0x20 is its delta. It returns 0 when plane.time <= 0 and abs(dot(delta,normal)) <0x10, or when the facing test rejects the contact; otherwise 1. The threshold depends on unnormalized motion magnitude, so it is not purely an angular test.

Evidence: `src/ov050/shared_engine/UpdatePathCameraCollision_020c35e0.c:157`; `eu/src/overlays/ov050/calls/UpdatePathCameraCollision.c`; `eu/src/overlays/ov050/calls/FilterPathCameraContactByMotionAndFacing.c`.

## Integration checks and limits

The combined plan keeps every native entrypoint separate. GetOv052ActorVelocity avoids the existing overlay017 GetActorVelocity name. DeactivateOv071TaskEntriesAndManager explicitly names its SceneTask owner and entry deactivation rather than treating its slots as audio-only state. InitRadialEffectMotion names the observed radial update rather than inheriting an unsupported spiral label. Generic EntryList operations retain a generic owner name.

The source-level callback declarations that remain erased are native DS adapters, not complete host ABIs. Preserve actual argument flow, signed byte sentinels, 64-bit flag operations, borrowed-pointer lifetime and callback order before replacing them with host types. An opaque gameplay value may keep a numerical name when its operation is known but its broader role is not.

Use the repository's existing per-function verifier and full gate from `eu/`.
The commands below cover every entrypoint in this block.

```sh
python tools/verify_idx.py src/overlays/ov052/calls/FilterEntityEventAndClearInhibitFlag.c FilterEntityEventAndClearInhibitFlag --thumb
python tools/verify_idx.py src/overlays/ov052/calls/UpdateEntityFadeAndPostUpdate.c UpdateEntityFadeAndPostUpdate --thumb
python tools/verify_idx.py src/overlays/ov052/calls/ApplyPendingEntityMotion.c ApplyPendingEntityMotion --thumb
python tools/verify_idx.py src/overlays/ov052/calls/AddActorVelocity.c AddActorVelocity
python tools/verify_idx.py src/overlays/ov052/calls/InstallActorJointMatrixCaptureCallback.c InstallActorJointMatrixCaptureCallback --thumb
python tools/verify_idx.py src/overlays/ov054/calls/SetEntityModeWithSceneReset.c SetEntityModeWithSceneReset
python tools/verify_idx.py src/overlays/ov055/calls/ReleaseSceneObjectAndFreeWork.c ReleaseSceneObjectAndFreeWork
python tools/verify_idx.py src/overlays/ov058/calls/IsEnemyTargetOutsideRaisedBand.c IsEnemyTargetOutsideRaisedBand
python tools/verify_idx.py src/overlays/ov058/calls/AcquireEnemyTargetWithFallback.c AcquireEnemyTargetWithFallback
python tools/verify_idx.py src/overlays/ov058/calls/UpdateEnemyPlayerFacingMode.c UpdateEnemyPlayerFacingMode
python tools/verify_idx.py src/overlays/ov058/calls/ProcessEnemyAiRequest.c ProcessEnemyAiRequest
python tools/verify_idx.py src/overlays/ov059/calls/InitMotionTargetState.c InitMotionTargetState --thumb
python tools/verify_idx.py src/overlays/ov059/calls/HandleMotionTargetEvent.c HandleMotionTargetEvent --thumb
python tools/verify_idx.py src/overlays/ov059/calls/SetActorCommandTypeFromCommandId.c SetActorCommandTypeFromCommandId --thumb
python tools/verify_idx.py src/overlays/ov059/calls/EntryList_FindByPair.c EntryList_FindByPair --thumb
python tools/verify_idx.py src/overlays/ov071/calls/DeactivateOv071TaskEntriesAndManager.c DeactivateOv071TaskEntriesAndManager --thumb
python tools/verify_idx.py src/overlays/ov052/auto/InitStepTimer.c InitStepTimer --thumb
python tools/verify_idx.py src/overlays/ov052/auto/GetCachedSlot3WorldPosition.c GetCachedSlot3WorldPosition
python tools/verify_idx.py src/overlays/ov058/calls/GetSceneIntroSequenceMode.c GetSceneIntroSequenceMode
python tools/verify_idx.py src/overlays/ov052/calls/BlendActorTrackAndClearActionId.c BlendActorTrackAndClearActionId --thumb
python tools/verify_idx.py src/overlays/ov059/calls/PlayActorTrackAsExtraAction.c PlayActorTrackAsExtraAction --thumb
python tools/verify_idx.py src/overlays/ov059/calls/Actor_UpdateState5RootMotion.c Actor_UpdateState5RootMotion --thumb
python tools/verify_idx.py src/overlays/ov059/calls/Actor_DispatchSharedControlAction.c Actor_DispatchSharedControlAction --thumb
python tools/verify_idx.py src/overlays/ov059/calls/Actor_LatchSharedControlId1Trigger.c Actor_LatchSharedControlId1Trigger --thumb
python tools/verify_idx.py src/overlays/ov059/calls/Actor_UpdateSweepEffectLifecycle.c Actor_UpdateSweepEffectLifecycle --thumb
python tools/verify_idx.py src/overlays/ov059/calls/Actor_SpawnSweepContactEffect.c Actor_SpawnSweepContactEffect --thumb
python tools/verify_idx.py src/overlays/ov058/calls/Enemy_ClearTargetKindAndArrivalFlag.c Enemy_ClearTargetKindAndArrivalFlag
python tools/verify_idx.py src/overlays/ov058/calls/UpdateEnemyDistanceGatedAiMode.c UpdateEnemyDistanceGatedAiMode
python tools/verify_idx.py src/overlays/ov058/calls/Enemy_SpawnEvent1EEffectAndDetachCollider.c Enemy_SpawnEvent1EEffectAndDetachCollider
python tools/verify_idx.py src/overlays/ov059/calls/Actor_UpdateJumpCommandInput.c Actor_UpdateJumpCommandInput --thumb
python tools/verify_idx.py src/overlays/ov059/calls/InitRadialEffectMotion.c InitRadialEffectMotion --thumb
python tools/verify_idx.py src/overlays/ov050/calls/FilterPathCameraContactByMotionAndFacing.c FilterPathCameraContactByMotionAndFacing --thumb
python tools/verify_idx.py src/overlays/ov059/auto/DoubleSeekerContactDistance.c DoubleSeekerContactDistance --thumb
python tools/verify_idx.py src/overlays/ov052/calls/GetOv052ActorVelocity.c GetOv052ActorVelocity --thumb
bash tools/gate.sh
```

Integration preserves the baseline and compares affected production texts,
resolved relocation targets/types and addends, then requires unchanged hashes
for all 108 linked modules. No actor AI, collision callback, effect trajectory or
entry lifecycle algorithm is rewritten. Names and logical field contracts are
supported by the callers/consumers listed above in addition to byte equality.
