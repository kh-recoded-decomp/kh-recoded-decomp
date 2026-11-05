# Field-object, session, resource and VM callback contracts

These 50 EU overlay 001 Thumb names follow native constructors, dispatch
readers and resource lifetimes. Twelve VM no-ops are named by proven
group/opcode/phase. Nop describes behavior without asserting an original
reserved or unimplemented purpose. Sources are relative to `eu/`; logical
signatures explain the inherited native views without changing public layouts.

## Two callback families and exact dispatch slots

The class-based field-object family stores its class pointer at object +0x08
and position at +0x40. Its callbacks are different from the entry-pool family,
which stores its owner at +0x04. Do not reuse a callback table merely because
old partial views name both objects `FieldObject`.

| Class slot | Proven reader and contract |
|---|---|
| +0x20, hook 8 | `FieldObject_SetEnabled`: `(object, enabled)`, invoked after enabled state changes and related save/world updates; return ignored |
| +0x28, hook 10 | `FieldObject_GetPosition`: `(object)` to borrowed `VecFx32 *`, null if callback absent |
| +0x2c, hook 11 | `FieldObject_ApplyHit`: raw status from `(object, hitMessage)`, behind `IsObjectFlagClear` |
| +0x30, hook 12 | `FieldObject_QueryHit`: Boolean from `(object, shape, contact)`, behind `IsObjectFlagClear` |

The empty enabled-change callbacks are proved by constructor registration and
that real reader. The capsule/patrol/scaled false query callbacks leave contact
output untouched; returning false here does not establish that those objects
lack collision geometry. The scaled position helper returns object-owned +0x40
storage. Its hit helper returns class +0x50, initialized to 0x10, as raw status;
the value is not a work-buffer pointer or universally Boolean acceptance.

State/update at object +0x14 is a separate callback. The two idle functions
return null; `UpdateFieldObjectStates` retains the old callback unless a new
nonnull continuation is returned. The event-camera idle function likewise
returns null through `Obj_UpdateAll`, after `FinishEventCameraCut` resets the
camera and installs it. A port must preserve continuation semantics instead of
treating zero as a task-completion signal.

## Explicit no-op branches

The open/close callbacks for panel screen selector 1 are empty. Their script
wrappers still decode operands, perform their own gate and advance only as
specified by those wrappers. These functions do not create or destroy a panel.
Minigame task destruction dispatches mode 1 to one empty cleanup function and
modes 2/3 to another. Neither clears global work nor shared sprites or score;
outer task storage belongs to the scheduler. These names state actual callback
roles, not hypothetical missing implementations.

## Script no-ops and command completion

`InitOverlayObjectSystem` registers actor commands in handler group 1.
`CreateFieldObjectManager` registers field-object commands in group 4. Each
listed Nop consists only of `return 1`: it reads no operands and mutates no
state. The MAIN VM consumer treats run result 1 as command advance and resume
result 1 as completion of the suspended command. A paired always-advance run
normally does not install its resume callback, but both native addresses and
table entries remain distinct.

Nop means demonstrated executable behavior. It does not mean these opcodes were
historically reserved, unimplemented, deprecated or unused by script assets.
Their opcode suffixes are hexadecimal and their run/resume role is explicit.
No asset-level intent is assigned solely to eliminate an address-based name.

| Group | Opcode | Role | Name | Paired native handler at snapshot |
|---|---|---|---|---|
| 1 | 0x1 | run | `ScriptCmd_ActorNop01` | `NULL` |
| 1 | 0x6 | run | `ScriptCmd_ActorNop06` | `ScriptResume_ActorNop06` |
| 1 | 0x6 | resume | `ScriptResume_ActorNop06` | `ScriptCmd_ActorNop06` |
| 1 | 0x1c | run | `ScriptCmd_ActorNop1C` | `NULL` |
| 1 | 0x1d | run | `ScriptCmd_ActorNop1D` | `NULL` |
| 1 | 0x2f | run | `ScriptCmd_ActorNop2F` | `NULL` |
| 1 | 0x30 | run | `ScriptCmd_ActorNop30` | `NULL` |
| 1 | 0x3b | run | `ScriptCmd_ActorNop3B` | `NULL` |
| 1 | 0x4a | run | `ScriptCmd_ActorNop4A` | `ScriptResume_ActorNop4A` |
| 1 | 0x4a | resume | `ScriptResume_ActorNop4A` | `ScriptCmd_ActorNop4A` |
| 4 | 0x14 | run | `ScriptCmd_FieldObjectNop14` | `NULL` |
| 4 | 0x15 | run | `ScriptCmd_FieldObjectNop15` | `NULL` |

## Actor scene, draw gates and preserved ABI inputs

The class-manager draw getter exposes mask 0x01 and guards the main pass of
`DrawLinkedActorPass`; its old visibility-oriented caller actually writes a
suppression bit. The entry-pool draw getter returns mask 0x11, possibly 1, 16 or
17, independently of conditional update-pause mask 0x40 and interaction mask
0x20. Neither result should become an invented all-rendering Boolean.

The skip bridge updates registered flagged actors and then the active field
camera channel. Both real callees have no inputs and no logical return value;
the old numerator/denominator and integer-result spelling must not become a new
animation-scale API. In contrast, the balloon-style bridge really forwards
actor ID in R0, though its old declaration erased that input. Its Boolean
style policy uses partner/lock flags and saved-camera projected Y comparisons;
it is not a pointer or a general world-space ordering relation.

The tracked draw helper handles five IDs with 0xffffffff sentinels and low-16
actor lookup. It installs an explicit projection, clears stale slots lacking
flag 0x02, draws surviving scene nodes and restores/selects the camera channel.
Clearing a stale tracking slot does not free the actor. The panel-opening state
waits for screen idle and a successful panel open, then retains only cached
brightness values exactly -16 or +16; other cached values become zero. Its
+0x7a4/+0x7b8 records are brightness snapshots, not axes, and null means retain
the waiting task function.

The eight two-byte actor bindings at +0x3b4 refer to stage sound slots. Release
checks a live slot handle and matches both stored keys, or matches all only
when both input keys are 0xffff. The slot destructor stops a bound current sound
sequence and clears its keys/handle, then the caller clears the local binding.
This is sound ownership, despite an older script caller's attachment label.
A specific key pair stops after its first released match.

Variant level is another distinct domain: the setter writes only a byte at
actor +0x0b, sets variant-enabled mask 0x4000 at +0x06, and returns the entire
input word. It does not replace the independently computed actor stats level.
Initialization in session mode 10 and boss-gauge threshold updates are the
observed consumers; no additional gameplay form names are inferred.

## Session snapshots, counters and menu ownership

Snapshotting managed actor state initializes a 16-byte output, copies actor
+0x105c when actor word +0x1dc is nonzero, and stores that exact raw word as the
result. The session buffers begin at +0x2778 with stride 16; the three observed
result words are +0x27a8/+0x27ac/+0x27b0. These are not three counters or
normalized Booleans. Their higher-level state meaning remains unassigned.
An inherited four-element results view would overlap the separate selector at
+0x27b4; it is not proof of four valid snapshot results. The loop has no added
bounds check and does not clear entries it did not visit.

The actual session counter getter instead reads +0x2938 + 4*index, paired with
`AddSessionCounter` and its 29-element array. No new bounds check or per-index
business enum is added. Menu destruction at +0x27e8 destroys the task handle
created by `CreateSessionNameMenu` and resets it to -1, while leaving the
separate name-string table's ownership alone. Native 0x02063c66 forwards the
loaded handle in R0 despite an erased no-argument C declaration.

The timer stop helper pairs `MarkSessionIntroDone`: it stops the elapsed timer
only when session +0x214 mask 0x8000 was set, then clears that bit. The session
state-9 helper releases/deactivates the active task with flush enabled, runs
the one-shot pending callback and flushes an entry refresh, returning controller
state 4. Its return is a next-state index, not a success Boolean. The subscene-9
destructor clears global work after obtaining the running task context; it does
not independently free scheduler-owned task storage.

## Inventory and pending-text script bridges

The inventory getter's real input is an item index in R0 and its real result is
a u16 count. The underlying API uses cached u16 storage for IDs 0..127 and saved
byte storage for other indices. The decrement helper reads only the request's
first halfword, queries presence and calls the direct saved-byte decrementer.
Do not silently clamp or reconcile the two storage domains, consume unused
request fields or adopt the old FIFO-ready name. The script presence test
forwards the integer decoder's result through R0, even though its C call erases
that argument.

The pending-dialog script command at group 1 opcode 0x33 advances immediately
when VM skip-request +0x628 is nonzero. Otherwise it forwards the VM and current
balloon/window pointer at display +0x50 to the existing pending-text command,
which splits buffered text, converts it and opens or updates the balloon until
completion. It decodes no additional operands. Group 1 opcode 0x5c starts the
panel list operation only in loaded mode 2 and panel phase 6. Failure returns
zero and retains the command; success does not promise the scroll has finished.

## Loaded entry file and two different request lists

Stage context +0 holds the loaded em file. Its loader relocates entries, data
and section pointers before giving it to the stage service. The getter returns
that borrowed file without a copy or lifetime extension. Existing ItemContext
or LevelTable names are partial views, not a complete portable schema.

The single pending request is at context +0x04/+0x06: a halfword ID and signed
kind byte. Construction and clear write kind -1; the conditional setter writes
kind followed by ID only while kind is negative. `UpdateFieldTask` matches kind
0 and ID. This is separate from the 64 trigger pairs beginning at +0x08 and
their count at +0x108. Preserve narrowing, order and the absence of validation.

Mapped drops use the loaded 12-byte entry ID, optionally remap under request
code 900, then resolve the byte mapping. Mapping 0x28 means no call; otherwise
`RollEnemyDrop` receives the level, mapped drop-record selector, position and
reduced=true. The core divides chance by eight in that mode and may produce no
drop. The mapping values are drop-record selectors, despite an inherited price
label in the builder; no item-price behavior is invented.

## Class callbacks and idle updates

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x02080ba8 (Thumb) | `BaseFieldObject_OnEnabledChangedNoop`; `src/overlays/ov001/auto/BaseFieldObject_OnEnabledChangedNoop.c` | `void(void)`. Empty implementation of class operation +0x20. | The constructor installs this function in hook8. FieldObject_SetEnabled reads that exact slot and calls (object,enabled) only after an enabled-state change. Boundary: Callback ABI supplies object/Boolean, both unused. No touch-event or allocation role is inferred from old private labels. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassFromDesc.c`, `eu/src/overlays/ov001/calls/FieldObject_SetEnabled.c`. |
| ov001:0x020816a8 (Thumb) | `WorkSlotObject_OnEnabledChangedNoop`; `src/overlays/ov001/auto/WorkSlotObject_OnEnabledChangedNoop.c` | `void(void)`. Empty implementation of class operation +0x20. | The constructor installs this function in hook8. FieldObject_SetEnabled reads that exact slot and calls (object,enabled) only after an enabled-state change. Boundary: Callback ABI supplies object/Boolean, both unused. No touch-event or allocation role is inferred from old private labels. Evidence sources: `eu/src/overlays/ov001/calls/CreateWorkSlotObjectClass.c`, `eu/src/overlays/ov001/calls/FieldObject_SetEnabled.c`. |
| ov001:0x02084dcc (Thumb) | `ContactFieldObject_OnEnabledChangedNoop`; `src/overlays/ov001/auto/ContactFieldObject_OnEnabledChangedNoop.c` | `void(void)`. Empty implementation of class operation +0x20. | The constructor installs this function in hook8. FieldObject_SetEnabled reads that exact slot and calls (object,enabled) only after an enabled-state change. Boundary: Callback ABI supplies object/Boolean, both unused. No touch-event or allocation role is inferred from old private labels. Evidence sources: `eu/src/overlays/ov001/calls/CreateGridWidget.c`, `eu/src/overlays/ov001/calls/FieldObject_SetEnabled.c`. |
| ov001:0x02086088 (Thumb) | `ScaledFieldObject_OnEnabledChangedNoop`; `src/overlays/ov001/auto/ScaledFieldObject_OnEnabledChangedNoop.c` | `void(void)`. Empty implementation of class operation +0x20. | The constructor installs this function in hook8. FieldObject_SetEnabled reads that exact slot and calls (object,enabled) only after an enabled-state change. Boundary: Callback ABI supplies object/Boolean, both unused. No touch-event or allocation role is inferred from old private labels. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassType16.c`, `eu/src/overlays/ov001/calls/FieldObject_SetEnabled.c`. |
| ov001:0x02082c74 (Thumb) | `CapsuleFieldObject_QueryHitFalse`; `src/overlays/ov001/auto/CapsuleFieldObject_QueryHitFalse.c` | `BOOL(void)`. Always return false for class operation +0x30. | Constructor installs hook12; FieldObject_QueryHit invokes this slot with object/shape/contact after IsObjectFlagClear, returning its Boolean. Boundary: Arguments are unused and output contact stays untouched. False is this explicit query result, not a guarantee that the object has no collision shape. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassType7.c`, `eu/src/overlays/ov001/calls/FieldObject_QueryHit.c`, `eu/src/overlays/ov001/FieldObjectCallbacks.h`. |
| ov001:0x02083c5c (Thumb) | `PatrolFieldObject_QueryHitFalse`; `src/overlays/ov001/auto/PatrolFieldObject_QueryHitFalse.c` | `BOOL(void)`. Always return false for class operation +0x30. | Constructor installs hook12; FieldObject_QueryHit invokes this slot with object/shape/contact after IsObjectFlagClear, returning its Boolean. Boundary: Arguments are unused and output contact stays untouched. False is this explicit query result, not a guarantee that the object has no collision shape. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassType9.c`, `eu/src/overlays/ov001/calls/FieldObject_QueryHit.c`, `eu/src/overlays/ov001/FieldObjectCallbacks.h`. |
| ov001:0x020860d4 (Thumb) | `ScaledFieldObject_QueryHitFalse`; `src/overlays/ov001/auto/ScaledFieldObject_QueryHitFalse.c` | `BOOL(void)`. Always return false for class operation +0x30. | Constructor installs hook12; FieldObject_QueryHit invokes this slot with object/shape/contact after IsObjectFlagClear, returning its Boolean. Boundary: Arguments are unused and output contact stays untouched. False is this explicit query result, not a guarantee that the object has no collision shape. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassType16.c`, `eu/src/overlays/ov001/calls/FieldObject_QueryHit.c`, `eu/src/overlays/ov001/FieldObjectCallbacks.h`. |
| ov001:0x0208608c (Thumb) | `ScaledFieldObject_GetPosition`; `src/overlays/ov001/auto/ScaledFieldObject_GetPosition.c` | `VecFx32 *(FieldObject *object)`. Return borrowed address object +0x40. | CreateFieldObjectClassType16 installs hook10; FieldObject_GetPosition reads class +0x28 and returns this vector; RespawnScaledFieldObject/SetPanelPosition use object +0x40 as position. Boundary: No allocation/check or copy. The native int spelling is a pointer carrier; lifetime is object-owned. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassType16.c`, `eu/src/overlays/ov001/calls/FieldObject_GetPosition.c`, `eu/src/overlays/ov001/calls/RespawnScaledFieldObject.c`, `eu/src/overlays/ov001/calls/SetPanelPosition.c`. |
| ov001:0x020860cc (Thumb) | `ScaledFieldObject_GetClassHitResult`; `src/overlays/ov001/auto/ScaledFieldObject_GetClassHitResult.c` | `u32(FieldObject *object)`. Return class word +0x50 from object->class+8. | Type16 constructor installs hook11 and initializes class +0x50=0x10. FieldObject_ApplyHit dispatches class +0x2c and returns raw result. Boundary: The hit message is unused; result is a raw backend status, not a pointer despite inherited helper names. No uniform Boolean accept/reject claim. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectClassType16.c`, `eu/src/overlays/ov001/calls/FieldObject_ApplyHit.c`. |
| ov001:0x02080a9c (Thumb) | `FieldObject_IdleUpdate`; `src/overlays/ov001/auto/FieldObject_IdleUpdate.c` | `void *(void)`. Return null update continuation. | Constructor writes object state/update +0x14. UpdateFieldObjectStates calls it with object and replaces the state function only when result is nonnull. Boundary: Object argument is ignored. Null retains the installed function; it neither destroys the object nor reports task completion. Evidence sources: `eu/src/overlays/ov001/calls/FieldObject_CreateWithShape.c`, `eu/src/overlays/ov001/calls/FieldObject_CreateWithUpdater.c`, `eu/src/overlays/ov001/calls/UpdateFieldObjectStates.c`. |
| ov001:0x02081fa8 (Thumb) | `SaveBitFieldObject_IdleUpdate`; `src/overlays/ov001/auto/SaveBitFieldObject_IdleUpdate.c` | `void *(void)`. Return null update continuation. | Constructor writes object state/update +0x14. UpdateFieldObjectStates calls it with object and replaces the state function only when result is nonnull. Boundary: Object argument is ignored. Null retains the installed function; it neither destroys the object nor reports task completion. Evidence sources: `eu/src/overlays/ov001/calls/FieldObject_CreateWithSaveBits.c`, `eu/src/overlays/ov001/calls/UpdateFieldObjectStates.c`. |

## Panel script protocol and destructor

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x02071aa4 (Thumb) | `OpenFieldPanelScreen1Noop`; `src/overlays/ov001/auto/OpenFieldPanelScreen1Noop.c` | `void(void)`. Empty open callback for script screen selector 1. | ScriptCmd_OpenFieldPanelScreen decodes screen/argument, waits for field panel shown, and selects this callback in case1. Boundary: Does not open a task, allocate or decode more operands. Name states selector/protocol, without claiming an unproved screen purpose. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_OpenFieldPanelScreen.c`. |
| ov001:0x02071aa8 (Thumb) | `CloseFieldPanelScreen1Noop`; `src/overlays/ov001/auto/CloseFieldPanelScreen1Noop.c` | `void(void)`. Empty close callback for script screen selector 1. | ScriptCmd_CloseFieldPanelScreen selects it in case1 after its panel/counter gate. Boundary: Does not destroy resources or alter display; distinct native identity from the other three actual cleanup wrappers. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_CloseFieldPanelScreen.c`. |
| ov001:0x02066ca0 (Thumb) | `ClearSubScene9WorkOnDestroy`; `src/overlays/ov001/calls/ClearSubScene9WorkOnDestroy.c` | `void(void)`. Read running task work for ABI context, then clear global subscene9 work0488. | gSubScene9TaskDescriptor installs destructor; paired SubScene9_Create_02066c80 stores current work and initializes tween. Boundary: No explicit work free/tween destroy; scheduler owns allocation. Incoming task argument unused by actual GetRunningTaskWork API. Evidence sources: `eu/src/overlays/ov001/calls/SubScene9_Create_02066c80.c`, `eu/src/overlays/ov001/data/tables/gSubScene9TaskDescriptor.c`. |
| ov001:0x0208efe0 (Thumb) | `ScriptCmd_TryStartPanelListScroll`; `src/overlays/ov001/calls/ScriptCmd_TryStartPanelListScroll.c` | `int(void)`. Normalize TryStartPanelListScroll result to 0/1. | Group1 opcode 0x5c run handler; callee requires loaded subscene mode 2 and phase 6, activates panel entity and returns 1. Boundary: No operands; wrong mode/state returns 0 and retains script command. No new guarantee about scroll completion. Evidence sources: `eu/src/overlays/ov001/calls/TryStartPanelListScroll.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |

## Minigame cleanup callbacks

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x0207e2c8 (Thumb) | `CleanupFallingPieceMinigameNoop`; `src/overlays/ov001/auto/CleanupFallingPieceMinigameNoop.c` | `void(void)`. Empty cleanup branch for minigame mode 1. | Task descriptor installs DispatchByContextMode as destructor; mode 1 dispatches here, while InitContextForMode selects UpdateFallingPieces for mode 1. Boundary: Destructor ABI passes context but it is unused; function does not clear global work, sprites or scores. Outer task lifetime belongs to scheduler. Evidence sources: `eu/src/overlays/ov001/calls/DispatchByContextMode.c`, `eu/src/overlays/ov001/calls/InitContextForMode.c`, `eu/src/overlays/ov001/data/tables/gSceneMinigameTaskDescriptor.c`. |
| ov001:0x0207e2cc (Thumb) | `CleanupSpinningPromptMinigameNoop`; `src/overlays/ov001/auto/CleanupSpinningPromptMinigameNoop.c` | `void(void)`. Empty cleanup branch shared by minigame modes2/3. | Descriptor destructor DispatchByContextMode routes modes2/3 here; initializer selects UpdateSpinningMode for both. Boundary: Context unused; no resource release/global clear. Do not infer separate destructor behaviors for the two modes. Evidence sources: `eu/src/overlays/ov001/calls/DispatchByContextMode.c`, `eu/src/overlays/ov001/calls/InitContextForMode.c`, `eu/src/overlays/ov001/data/tables/gSceneMinigameTaskDescriptor.c`. |

## Event camera idle callback

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x0208b7a4 (Thumb) | `EventCamera_IdleTaskUpdate`; `src/overlays/ov001/auto/EventCamera_IdleTaskUpdate.c` | `void *(void)`. Return null task-update continuation. | FinishEventCameraCut clears manager active and installs this function via Obj_SetWord14 after camera reset; TaskObject update convention retains handler on null. Boundary: No task destruction; camera remains inactive. ABI arguments are unused. Evidence sources: `eu/src/overlays/ov001/calls/FinishEventCameraCut.c`, `eu/src/calls/Obj_UpdateAll.c`. |

## Draw-mask accessors

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x0207ef90 (Thumb) | `GetFieldObjectDrawBlockMask`; `src/overlays/ov001/auto/GetFieldObjectDrawBlockMask.c` | `u32(void)`. Return class-manager byte +0x14 masked with 0x01. | SetOverlayLayerVisible writes this bit; DrawLinkedActorPass returns before its main draw branch when getter is nonzero. Boundary: Name follows actual suppression behavior despite visible label. This guards pass0, not every shadow/draw path; no owner-null check. Evidence sources: `eu/src/overlays/ov001/calls/SetOverlayLayerVisible.c`, `eu/src/overlays/ov001/calls/DrawLinkedActorPass.c`. |
| ov001:0x020870e4 (Thumb) | `GetFieldEntryDrawBlockMask`; `src/overlays/ov001/auto/GetFieldEntryDrawBlockMask.c` | `u32(void)`. Return pool-manager byte+5 masked with 0x11. | The installed pool-linked actor draw callback 02086b14 skips its draw branch for nonzero; setters of bits 0x01/0x10 also suppress pool updates. Boundary: Raw mask can be1,16 or17, not normalized. Does not include conditional update-pause0x40 or interaction bit 0x20. Evidence sources: `eu/src/overlays/ov001/calls/func_ov001_02086b14.c`, `eu/src/overlays/ov001/calls/SetCachePaused.c`. |

## Actor scene, sound and dialog operations

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x02088aa4 (Thumb) | `UpdateSkipActorsAndCameraChannel`; `src/overlays/ov001/calls/UpdateSkipActorsAndCameraChannel.c` | `void(void)`. Update flagged actor motion, then update active camera channel. | Real NotifyFlaggedActors has no inputs and updates registered actor slots; ActorChannel_UpdateIfActive updates field camera only when active. ScriptVm_FinishSkip invokes this wrapper while running skipped frames. Boundary: Inherited numerator/denominator parameters and int result have no logical role in these void callees. No new animation scale or returned completion value. Evidence sources: `eu/src/overlays/ov001/calls/NotifyFlaggedActors.c`, `eu/src/overlays/ov001/calls/ActorChannel_UpdateIfActive.c`, `eu/src/calls/ScriptVm_FinishSkip.c`. |
| ov001:0x02088b48 (Thumb) | `GetActorSpeechBalloonStyle`; `src/overlays/ov001/calls/GetActorSpeechBalloonStyle.c` | `BOOL(int actorId)`. Delegate actor index to IsPartnerAheadOfActor and return its Boolean. | Both actor speech and choice-balloon openers store result as balloonStyle. Real callee projects leader/partner Y with saved camera and handles partner/lock flags. Boundary: Native R0 actor index is real input despite erased C call. Style is 0/1 policy, not a pointer or general world-space ahead test. Evidence sources: `eu/src/overlays/ov001/calls/IsPartnerAheadOfActor.c`, `eu/src/overlays/ov001/calls/OpenActorSpeechBalloon.c`, `eu/src/overlays/ov001/calls/OpenScriptChoiceBalloon.c`, `eu/src/overlays/ov001/calls/QueryWithTemporaryCamera.c`. |
| ov001:0x02091ae8 (Thumb) | `ReleaseActorSoundSlotsByKey`; `src/overlays/ov001/calls/ReleaseActorSoundSlotsByKey.c` | `void(StageActor *actor, u16 firstKey, u16 secondKey)`. Inspect eight local two-byte bindings at actor +0x3b4; release active stage sound slots matching key pair, or all when both keys0xffff; clear local binding after release. | GetStageEntrySlot resolves one-based sound slots; ReleaseSlotResource stops a current bound sound sequence and clears slot keys/handle. Enemy-hit/resource teardown pass wildcard keys; script command passes a pair. Boundary: No attachment-model ownership claim. Both wildcards release all; a specific pair returns after first released match. Preserve active-handle checks and native ID forwarding erased in C. Evidence sources: `eu/src/overlays/ov001/calls/ReleaseSlotResource.c`, `eu/src/overlays/ov001/calls/GetStageEntrySlot.c`, `eu/src/overlays/ov001/calls/ApplyHitToEnemyGroup.c`, `eu/src/overlays/ov001/calls/ReleaseActorResources.c`, `eu/src/overlays/ov021/calls/ScriptCmd_RemovePlayerAttachment.c`. |
| ov001:0x020925f0 (Thumb) | `SetStageActorVariantLevel`; `src/overlays/ov001/calls/SetStageActorVariantLevel.c` | `u32(StageActor *actor, u32 value)`. Store low byte of value at actor +0xb, set flags halfword+6 mask 0x4000 and return full input value. | InitializeActorStats defines same flag as variantEnabled and byte as variantLevel; mode 10 initializes it. ApplyHitToEnemyGroup changes it for boss-gauge HP thresholds. Boundary: This is variant/phase level, not unconditional stat-level replacement. Stored byte is narrowed, return is not. No guessed gameplay form names. Evidence sources: `eu/src/overlays/ov001/calls/InitializeActorStats.c`, `eu/src/overlays/ov001/calls/ApplyHitToEnemyGroup.c`. |
| ov001:0x020882d8 (Thumb) | `WaitForFieldPanelAndCacheExtremeBrightness`; `src/overlays/ov001/calls/WaitForFieldPanelAndCacheExtremeBrightness.c` | `TaskUpdate(void)`. Wait for screen mode idle and successful OpenFieldPanel; cache main/sub brightness only when absolute value 16, otherwise zero; return event-script updater on success or null while waiting. | OpenFieldPanel starts panel tween/suspends menu/backs up VRAM and returns success. TryFinishIntroSequence installs this state; next callback runs event script and refreshes scene. Boundary: Fields at manager +0x7a4/+0x7b8 are brightness snapshots, not axes. Null retains state; does not mean task complete. Evidence sources: `eu/src/overlays/ov001/calls/OpenFieldPanel.c`, `eu/src/overlays/ov001/calls/TryFinishIntroSequence.c`, `eu/src/overlays/ov001/calls/CmdOpenDialog_02088580.c`. |
| ov001:0x020887a4 (Thumb) | `DrawTrackedActorSceneSlots`; `src/overlays/ov001/calls/DrawTrackedActorSceneSlots.c` | `void(void)`. If any of five actor IDs at manager +0x3f08 exist, set explicit projection, prune slots missing flag 2, draw surviving scene nodes, then restore/select actor camera channel. | RefreshMenuPage calls this before other scene updates. ActorSlot flags validate IDs; SceneNode_Draw renders actor animation node; projection/channel helpers bracket drawing. Boundary: Five-slot list,0xffffffff sentinel,low16 lookup. No allocation or ownership transfer; do not interpret stale-slot pruning as actor destruction. Evidence sources: `eu/src/overlays/ov001/calls/RefreshMenuPage.c`, `eu/src/calls/SceneNode_Draw.c`. |
| ov001:0x0208dc54 (Thumb) | `ScriptCmd_ShowPendingActorDialogText`; `src/overlays/ov001/calls/ScriptCmd_ShowPendingActorDialogText.c` | `int(ScriptVm *vm)`. If VM skip-request word +0x628 nonzero, return 1; otherwise forward vm and display balloon +0x50 to pending-text command and return its result. | Group1 opcode 0x33 run handler. ScriptCmd_ShowPendingDialogText checks window phase, splits pending text, convertsUTF-16 and opens/updates balloon until complete. Boundary: No extra operand decoding; zero means VM retains command, one advances. The second delegated argument is current balloon/window context, not an invented script operand buffer. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_ShowPendingDialogText.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |

## Managed actor snapshots

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x02064d88 (Thumb) | `SnapshotManagedActorStateBlocks`; `src/overlays/ov001/calls/SnapshotManagedActorStateBlocks.c` | `void(void)`. For every managed actor, initialize/copy a16-byte block into session 2778+16*i and store raw result at 27a8+4*i. | CopyActiveBlockIfPresent initializes output then copies actor +0x105c only when actor word +0x1dc is nonzero; returns that exact word. Scene shutdown callers request this snapshot. Boundary: Raw result words are not three counters or normalized Booleans. Higher-level block meaning is not established; do not add bounds or clear unvisited entries. Evidence sources: `eu/src/overlays/ov052/calls/CopyActiveBlockIfPresent.c`, `eu/src/overlays/ov028/calls/ShutdownFieldAndSaveActorPoses.c`. |

## Session counters, timer and pending work

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x02063b68 (Thumb) | `GetSessionCounter`; `src/overlays/ov001/calls/GetSessionCounter.c` | `s32(int index)`. Return session counter at +0x2938+4*index. | AddSessionCounter updates the same29-element array with per-index limits and side effects; ClearSessionSlots resets it; results/challenge consumers read it. Boundary: No getter bounds/null check, no new per-index gameplay enum; signedword return retained. Evidence sources: `eu/src/overlays/ov001/calls/AddSessionCounter.c`, `eu/src/overlays/ov001/calls/ClearSessionSlots.c`, `eu/src/overlays/ov032/calls/UpdateChallengeProgress.c`. |
| ov001:0x02063c54 (Thumb) | `DestroySessionNameMenu`; `src/overlays/ov001/calls/DestroySessionNameMenu.c` | `void(void)`. Destroy session menu task +0x27e8 if handle!=-1, then write-1. | CreateSessionNameMenu stores CreateTaskObject result there. Native 0x02063c66 passes loaded handle in R0 to DestroyTaskObjectWrapper despite no-arg C declaration. Boundary: Does not free the separate name-string array; task destructor owns its resources. No new handle0 guard or returned value. Evidence sources: `eu/src/overlays/ov001/calls/CreateSessionNameMenu.c`, `eu/src/overlays/ov001/calls/ShowSessionNameEntry.c`, `eu/src/calls/DestroyTaskObjectWrapper.c`. |
| ov001:0x02064d44 (Thumb) | `StopPostIntroElapsedTimerIfActive`; `src/overlays/ov001/calls/StopPostIntroElapsedTimerIfActive.c` | `void(void)`. If session flags +0x214 mask 0x8000 set, stop post-intro elapsed timer then clear the bit. | MarkSessionIntroDone starts same timer on clear-to-set. ScriptCmd_ToggleSessionBit15 chooses start/stop using its decoded Boolean. Boundary: No change when flag clear; no elapsed-value reset beyond timer helper. Bit 15 is hex mask 0x8000, not state decimal15. Evidence sources: `eu/src/overlays/ov001/calls/MarkSessionIntroDone.c`, `eu/src/overlays/ov001/calls/ScriptCmd_ToggleSessionBit15.c`, `eu/src/overlays/ov001/auto/StopPostIntroElapsedTimer.c`. |
| ov001:0x02062654 (Thumb) | `ReleaseSessionTaskAndFlushPendingWork`; `src/overlays/ov001/calls/ReleaseSessionTaskAndFlushPendingWork.c` | `s32(void)`. Release session task with flush true, run one pending callback, flush pending entry refresh and return next state 4. | gSessionScriptStateHandlers installs state 9. ReleaseSessionHandle releases/deactivates task, raises state flag/resumes timers for flush true, clears active handle; RunPendingCallback clears callbackslot before invoking. Boundary: Does not free session or invoke a generalized scene exit. Return 4 is controller next state, not Boolean success. Evidence sources: `eu/src/overlays/ov001/calls/ReleaseSessionHandle.c`, `eu/src/overlays/ov001/calls/RunPendingCallback.c`, `eu/src/overlays/ov001/calls/FlushPendingEntryRefresh.c`, `eu/src/overlays/ov001/data/tables/gSessionScriptStateHandlers.c`. |

## Inventory count bridges

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x02064a30 (Thumb) | `GetScriptInventoryEntryCount`; `src/overlays/ov001/calls/GetScriptInventoryEntryCount.c` | `u16(int itemId)`. Forward index to GetByteCounterOrDefault. | Item-count decrement wrapper reads request itemId through this helper; script presence test forwards ScriptVm_ReadOperandInt result. Callee reads cachedu16 counts for 0..127, otherwise savedu8 storage, returnsu16. Boundary: Actual R0 input and scalar result are hidden by void*/no-arg shim. No FIFO/readiness or ownership claim; preserve callee index domains. Evidence sources: `eu/src/calls/GetByteCounterOrDefault.c`, `eu/src/overlays/ov001/calls/ScriptCmd_AdjustItemCount.c`, `eu/src/overlays/ov001/calls/ScriptCmd_StoreFifoReady.c`. |
| ov001:0x02064aa8 (Thumb) | `DecrementInventoryEntryCountIfPresent`; `src/overlays/ov001/calls/DecrementInventoryEntryCountIfPresent.c` | `void(const ItemRequest *request)`. If queried count for first request halfword is nonzero, call DecrementByteCounter for that ID. | ScriptCmd_AdjustItemCount invokes once per negative amount; request contains itemId/params, but helper consumes only itemId. Boundary: Getter uses cachedu16 for 0..127 while decrementer directly changes savedu8; do not silently clamp or change that distinction. No full inventory-record removal or remaining-request-field use. Evidence sources: `eu/src/overlays/ov001/calls/ScriptCmd_AdjustItemCount.c`, `eu/src/calls/GetByteCounterOrDefault.c`, `eu/src/calls/DecrementByteCounter.c`. |

## Loaded entry file and requests

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x0206894c (Thumb) | `GetPendingStageEventRequest`; `src/overlays/ov001/calls/GetPendingStageEventRequest.c` | `StageEventRequest *(void)`. Return borrowed context 0490+4, containing halfword eventID and signed-byte kind. | QueueStageEventRequestIfEmpty writes these fields; CreateStageDataAndStart initializes kind=-1 and ClearQueueFlag restores it. UpdateFieldTask compares kind 0 and eventID for matching. Boundary: No ownership transfer or allocation; do not confuse with separate64-pair trigger queue beginning+8. Evidence sources: `eu/src/overlays/ov001/calls/CreateStageDataAndStart.c`, `eu/src/overlays/ov001/calls/ClearQueueFlag.c`, `eu/src/overlays/ov001/calls/UpdateFieldTask.c`. |
| ov001:0x02068968 (Thumb) | `QueueStageEventRequestIfEmpty`; `src/overlays/ov001/calls/QueueStageEventRequestIfEmpty.c` | `void(u8 kind, u16 eventId)`. Only when context+6 signedbyte isnegative, store kind then eventID+4. | CreateStageDataAndStart/ClearQueueFlag use-1 sentinel; getter and UpdateFieldTask consume this single request. ScriptCmd_SetProperty queues kind 0 with objectId-1. Boundary: Single overwrite-protected slot, not the64-pair list. Preserve narrowing/storeorder and no validation of kind/eventID. Evidence sources: `eu/src/overlays/ov001/calls/CreateStageDataAndStart.c`, `eu/src/overlays/ov001/calls/ClearQueueFlag.c`, `eu/src/overlays/ov001/calls/UpdateFieldTask.c`, `eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c`. |
| ov001:0x020689a4 (Thumb) | `GetLoadedStageEntryFile`; `src/overlays/ov001/calls/GetLoadedStageEntryFile.c` | `StageEntryFile *(void)`. Return borrowed loaded file pointer stored at context 0490+0. | LoadLevelTableFile loads the em resource, relocates entry/data/section pointers, stores it at word 0 and passes it to BeginStageEntriesIfActive. Area-group exclusion reads that same header/file. Boundary: No ownership transfer or context check. Do not adopt old ItemContext/LevelTable labels as a complete portable schema. Evidence sources: `eu/src/overlays/ov001/calls/LoadLevelTableFile.c`, `eu/src/overlays/ov040/calls/IsStageObjectExcludedFromAreaGroups.c`. |
| ov001:0x02068a74 (Thumb) | `RollStageEntryMappedDrop`; `src/overlays/ov001/calls/RollStageEntryMappedDrop.c` | `void(int entryIndex, const VecFx32 *position, int level)`. Map loaded 12-byte entryID through optional mode 900 remap and byte mapping; unless mapping==0x28, call RollEnemyDrop(level,mappedRecord,position,true). | ApplyHitToEnemyGroup invokes on enemy defeat. RollEnemyDrop uses reduced=true todivide chance byeight and spawns reward effect; loadedfile suppliesentry IDs. Boundary: No index/file guard or guarantee of drop. Mapping values are drop-record selectors, not item prices despite inherited BuildUniqueItemPriceList labels. Evidence sources: `eu/src/overlays/ov001/calls/LoadLevelTableFile.c`, `eu/src/overlays/ov001/calls/LookupMappedByteValue.c`, `eu/src/overlays/ov032/calls/GetGroupIndexedValue.c`, `eu/src/overlays/ov001/calls/RollEnemyDrop.c`, `eu/src/overlays/ov001/calls/ApplyHitToEnemyGroup.c`. |

## Actor VM no-op entrypoints

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x0208c764 (Thumb) | `ScriptCmd_ActorNop01`; `src/overlays/ov001/auto/ScriptCmd_ActorNop01.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x01 installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208d5c0 (Thumb) | `ScriptCmd_ActorNop06`; `src/overlays/ov001/auto/ScriptCmd_ActorNop06.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x06 installs this as run, partner ScriptResume_ActorNop06. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208d5c4 (Thumb) | `ScriptResume_ActorNop06`; `src/overlays/ov001/auto/ScriptResume_ActorNop06.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x06 installs this as resume, partner ScriptCmd_ActorNop06. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208debc (Thumb) | `ScriptCmd_ActorNop1C`; `src/overlays/ov001/auto/ScriptCmd_ActorNop1C.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x1c installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208dd08 (Thumb) | `ScriptCmd_ActorNop1D`; `src/overlays/ov001/auto/ScriptCmd_ActorNop1D.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x1d installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208e4ac (Thumb) | `ScriptCmd_ActorNop2F`; `src/overlays/ov001/auto/ScriptCmd_ActorNop2F.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x2f installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208e4b0 (Thumb) | `ScriptCmd_ActorNop30`; `src/overlays/ov001/auto/ScriptCmd_ActorNop30.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x30 installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208e778 (Thumb) | `ScriptCmd_ActorNop3B`; `src/overlays/ov001/auto/ScriptCmd_ActorNop3B.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x3b installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208dab8 (Thumb) | `ScriptCmd_ActorNop4A`; `src/overlays/ov001/auto/ScriptCmd_ActorNop4A.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x4a installs this as run, partner ScriptResume_ActorNop4A. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x0208dabc (Thumb) | `ScriptResume_ActorNop4A`; `src/overlays/ov001/auto/ScriptResume_ActorNop4A.c` | `int(void)`. Return 1 with no operand reads or side effects. | InitOverlayObjectSystem registers table group 1. gActorScriptCommandHandlers opcode 0x4a installs this as resume, partner ScriptCmd_ActorNop4A. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/InitOverlayObjectSystem.c`, `eu/src/overlays/ov001/data/tables/gActorScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |

## Field-object VM no-op entrypoints

| EU identity | Name and source relative to `eu/` | Logical contract | Evidence and boundary |
|---|---|---|---|
| ov001:0x020801a8 (Thumb) | `ScriptCmd_FieldObjectNop14`; `src/overlays/ov001/auto/ScriptCmd_FieldObjectNop14.c` | `int(void)`. Return 1 with no operand reads or side effects. | CreateFieldObjectManager registers table group 4. gFieldObjectScriptCommandHandlers opcode 0x14 installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectManager.c`, `eu/src/overlays/ov001/data/tables/gFieldObjectScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |
| ov001:0x020801ac (Thumb) | `ScriptCmd_FieldObjectNop15`; `src/overlays/ov001/auto/ScriptCmd_FieldObjectNop15.c` | `int(void)`. Return 1 with no operand reads or side effects. | CreateFieldObjectManager registers table group 4. gFieldObjectScriptCommandHandlers opcode 0x15 installs this as run, partner NULL. ScriptVm_RunFrame interprets 1 as advance/complete. Boundary: Nop describes demonstrated behavior, not an original name or a reserved/unimplemented intent. Native entrypoint remains distinct. A paired always-advance run handler does not normally install its resume, but that descriptor entry is preserved. Evidence sources: `eu/src/overlays/ov001/calls/CreateFieldObjectManager.c`, `eu/src/overlays/ov001/data/tables/gFieldObjectScriptCommandHandlers.c`, `eu/src/calls/ScriptVm_RunFrame.c`. |

## Scope and remaining evidence

This block changes names only. It does not repair erased prototypes, add state
checks, normalize raw status, broaden array bounds, change native layouts,
remove no-op entrypoints, or interpret zero uniformly across callbacks. Separate
ABI/type changes need their own native object comparison and official gate.

Missing descriptor consumers, field writers and data enumerations remain
explicit evidence boundaries; unknown gameplay meanings are left unassigned.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/BaseFieldObject_OnEnabledChangedNoop.c BaseFieldObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/WorkSlotObject_OnEnabledChangedNoop.c WorkSlotObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ContactFieldObject_OnEnabledChangedNoop.c ContactFieldObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScaledFieldObject_OnEnabledChangedNoop.c ScaledFieldObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/CapsuleFieldObject_QueryHitFalse.c CapsuleFieldObject_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov001/auto/PatrolFieldObject_QueryHitFalse.c PatrolFieldObject_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScaledFieldObject_QueryHitFalse.c ScaledFieldObject_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScaledFieldObject_GetPosition.c ScaledFieldObject_GetPosition --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScaledFieldObject_GetClassHitResult.c ScaledFieldObject_GetClassHitResult --thumb
python tools/verify_idx.py src/overlays/ov001/auto/FieldObject_IdleUpdate.c FieldObject_IdleUpdate --thumb
python tools/verify_idx.py src/overlays/ov001/auto/SaveBitFieldObject_IdleUpdate.c SaveBitFieldObject_IdleUpdate --thumb
python tools/verify_idx.py src/overlays/ov001/auto/OpenFieldPanelScreen1Noop.c OpenFieldPanelScreen1Noop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/CloseFieldPanelScreen1Noop.c CloseFieldPanelScreen1Noop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/CleanupFallingPieceMinigameNoop.c CleanupFallingPieceMinigameNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/CleanupSpinningPromptMinigameNoop.c CleanupSpinningPromptMinigameNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/EventCamera_IdleTaskUpdate.c EventCamera_IdleTaskUpdate --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldObjectDrawBlockMask.c GetFieldObjectDrawBlockMask --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldEntryDrawBlockMask.c GetFieldEntryDrawBlockMask --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdateSkipActorsAndCameraChannel.c UpdateSkipActorsAndCameraChannel --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetActorSpeechBalloonStyle.c GetActorSpeechBalloonStyle --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseActorSoundSlotsByKey.c ReleaseActorSoundSlotsByKey --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageActorVariantLevel.c SetStageActorVariantLevel --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SnapshotManagedActorStateBlocks.c SnapshotManagedActorStateBlocks --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSessionCounter.c GetSessionCounter --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroySessionNameMenu.c DestroySessionNameMenu --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetScriptInventoryEntryCount.c GetScriptInventoryEntryCount --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DecrementInventoryEntryCountIfPresent.c DecrementInventoryEntryCountIfPresent --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearSubScene9WorkOnDestroy.c ClearSubScene9WorkOnDestroy --thumb
python tools/verify_idx.py src/overlays/ov001/calls/WaitForFieldPanelAndCacheExtremeBrightness.c WaitForFieldPanelAndCacheExtremeBrightness --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawTrackedActorSceneSlots.c DrawTrackedActorSceneSlots --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ShowPendingActorDialogText.c ScriptCmd_ShowPendingActorDialogText --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_TryStartPanelListScroll.c ScriptCmd_TryStartPanelListScroll --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StopPostIntroElapsedTimerIfActive.c StopPostIntroElapsedTimerIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetPendingStageEventRequest.c GetPendingStageEventRequest --thumb
python tools/verify_idx.py src/overlays/ov001/calls/QueueStageEventRequestIfEmpty.c QueueStageEventRequestIfEmpty --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseSessionTaskAndFlushPendingWork.c ReleaseSessionTaskAndFlushPendingWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetLoadedStageEntryFile.c GetLoadedStageEntryFile --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RollStageEntryMappedDrop.c RollStageEntryMappedDrop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop01.c ScriptCmd_ActorNop01 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop06.c ScriptCmd_ActorNop06 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptResume_ActorNop06.c ScriptResume_ActorNop06 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop1C.c ScriptCmd_ActorNop1C --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop1D.c ScriptCmd_ActorNop1D --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop2F.c ScriptCmd_ActorNop2F --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop30.c ScriptCmd_ActorNop30 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop3B.c ScriptCmd_ActorNop3B --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_ActorNop4A.c ScriptCmd_ActorNop4A --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptResume_ActorNop4A.c ScriptResume_ActorNop4A --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_FieldObjectNop14.c ScriptCmd_FieldObjectNop14 --thumb
python tools/verify_idx.py src/overlays/ov001/auto/ScriptCmd_FieldObjectNop15.c ScriptCmd_FieldObjectNop15 --thumb
bash tools/gate.sh
```
