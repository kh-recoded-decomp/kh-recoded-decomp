# Remaining early-overlay object and panel contracts

This block records all 135 safe early-overlay proposals still pending in the
configuration at commit 00280f0886, after the separate 114-function
integration and excluding ov015 work. There are 130 Thumb and five ARM identities.
Names are supported by bodies, native register flow, actual callbacks or
same-owner writers/consumers. They do not claim original source spelling.

Each row gives its bank, native address, mode, accepted name, EU wrapper path,
logical signature, effect, boundary and concrete evidence. Shared included bodies
must be interpreted through their EU aliases. The validation section records the
existing official checks; descriptive names do not add reconstruction credit.

The logical signatures describe real inputs/results. Inherited unprototyped calls,
false SDK templates and omitted R0 arguments are not safe portable contracts.
Native return values must remain raw where demonstrated: position/resource
pointers, callback addresses, flag masks and issued-request results are not all
booleans. A command return 1 advances its interpreter; it does not generally
prove allocation or animation completion. A zero polling result and its repeat
side effects must be retained. The known field-command table uses the MAIN
ScriptVm_RunFrame protocol documented in `FIELD_SCRIPT_EXTENSIONS.md`;
the overlay-local tables listed as evidence here are not assigned unproved
group/opcode numbers.

The following sections separate owners. Similar helper names and coincident
offsets do not establish a common host layout. Partial structs are views, rather
than full allocation-size or capacity declarations. A host port must preserve
native narrowing, sign extension, fixed-point rounding, sentinels and explicit
callback/resource lifetimes while separating host pointers from encoded data.


## Session field requests and side-result commit

These operations mutate the field session and its pending request/save state.
Queuing is distinct from loading an overlay. Scene/subscene identifiers, a
pending payload and packed leader placement have separate roles. Flag 14 below
means mask 0x4000, while flag 0x20 is another session mask. The set-then-clear
variant preserves all preceding side effects; neither flag is assigned a
new-game/resume meaning.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x02064884 | THUMB | `QueueStage900AndSaveLeaderPlacement` | `src/overlays/ov001/calls/QueueStage900AndSaveLeaderPlacement.c` | `void(u32 pendingValue)`. Queues ConfigureFieldTracks(900,-4,1,-1), writes caller payload to session+0x218, stores managed actor0 position/bias-adjusted angle using packed placement helper and sets global state-1. Boundary: Payload meaning beyond stored pendingValue not established. Keep the fixed stage/subscene and call order. Old u32 position return is a VecFx32 pointer. | Called by field script wrapper65ce4. |
| ov001:0x0206493c | THUMB | `QueueFieldFromSavedSceneIds` | `src/overlays/ov001/calls/QueueFieldFromSavedSceneIds.c` | `void(void)`. If global2-bit option1a00 nonzero stores difficulty preset, reads global saved scene/subscene ids at 330b/3315 width 10, queues them with(1,0), sets session flags0x20 and0x4000. Boundary: Flag 14 deeper lifecycle meaning remains unassigned. This does not itself load a ROM overlay. | Called by script wrapper65db0 and alternate64998. |
| ov001:0x02064998 | THUMB | `QueueSavedFieldAndClearFlag14` | `src/overlays/ov001/calls/QueueSavedFieldAndClearFlag14.c` | `void(void)`. Calls QueueFieldFromSavedSceneIds then clears session flag 0x4000. Boundary: Preserve the initial set then clear and all side effects of base helper. No assertion flag 14 means resume/newgame. | Ov087 func020c7b84 uses this alternate path. |
| ov001:0x02065ce4 | THUMB | `ScriptCmd_QueueStage900AndSavePlacement` | `src/overlays/ov001/calls/ScriptCmd_QueueStage900AndSavePlacement.c` | `int(void *vm, ScriptOperand *operands)`. Reads one integer operand, forwards payload to QueueStage900AndSaveLeaderPlacement, returns 1. Boundary: Old Ov002_EnterPhase callee label is misleading, real body is field transition/placement. | gFieldScriptCommandHandlers; direct shared wrapper body. |
| ov001:0x02065db0 | THUMB | `ScriptCmd_QueueFieldFromSavedSceneIds` | `src/overlays/ov001/calls/ScriptCmd_QueueFieldFromSavedSceneIds.c` | `int(void)`. Calls no-argument field transition helper and returns 1. Boundary: Old FS_UnloadOverlayImage/FS_EndOverlay labels are false SDK templates. No arguments needed by real callee. | gFieldScriptCommandHandlers; actual callee6493c. |
| ov007:0x020a0670 | THUMB | `ScriptCmd_CommitSideResult` | `src/overlays/ov007/calls/ScriptCmd_CommitSideResult.c` | `int(void *vm, ScriptOperand *operands)`. Reads one integer operand, calls CommitSideResult(side), returns 1. Boundary: Commit function is void, not int. Side meaning beyond two branches is unassigned. | gFieldActorScriptCommandHandlers entry6. |

## Field-effect pool

The owner is `data_ov001_020a0484`. Its 0x3694-byte allocation contains
160 inline effect records, stride 0x54, beginning at +0x214. The 0x18-byte
free-slot mask and PZ resource pointer +0x210 are separate allocations; the
embedded task/list starts at +0x3c. Releasing an effect returns its slot to the
mask rather than freeing inline storage. The active-list predicate requires an
initialized pool. Script polling retains its wake/suspend side effects.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x020663e4 | THUMB | `EnsureFieldEffectPool` | `src/overlays/ov001/calls/EnsureFieldEffectPool.c` | `void(void)`. If global pool absent, allocates0x3694 and clears it, allocates0x18 free-slot mask initialized all1, clears guard bit 0xa0, initializes embedded task+0x3c, clears suspended flag, sets capacity 160, loads PZ resource. Boundary: Idempotent while pool exists. Allocation failures are not checked. +0x210 is resource pointer, not inline effect storage. | FindFreeEffectSlot/SpawnEffect/UpdatePrizeOrbs use same global; actual LoadPzResource stores resource pointer+0x210. |
| ov001:0x02066454 | THUMB | `DestroyFieldEffectPool` | `src/overlays/ov001/calls/DestroyFieldEffectPool.c` | `void(void)`. If pool nonNULL, frees free-mask, PZ resource+0x210, unlinks embedded task+0x3c, frees pool and clears global. Boundary: Does not individually free160 effect records; they are inline inside the outer allocation. Texture handles are borrowed separately. | ShutdownFieldSession calls it. |
| ov001:0x020664f0 | THUMB | `TrySpawnFieldEffect` | `src/overlays/ov001/calls/TrySpawnFieldEffect.c` | `Effect *(int type, int variant, const VecFx32 *position, int motionType)`. Finds free slot by requested effect type; returns null if slot<0, otherwise forwards slot,type,variant,position,motionType to SpawnEffect and returns effect. Boundary: Inherited declaration omits type in FindFreeEffectSlot call; it is a real input. Real result is Effect*, not arbitrary u32. Preserve no-slot failure behavior. | Callers GrantEntryUnlockReward, SpawnRewardOrbs, SpawnDropsPerTenUnits, RollSpecialItemDrop and ScriptCmd_SetProperty. |
| ov001:0x0206674c | THUMB | `ReleaseFieldEffectSlot` | `src/overlays/ov001/calls/ReleaseFieldEffectSlot.c` | `void(Effect *effect)`. When effect.task+0x24 nonNULL, unlinks effect from task, unlinks root if active list became empty, clears effect.task, marks effect.slot+0x2d free in pool mask. Boundary: Does not free effect allocation because records are inline. Repeated call on already-null task is no-op. | UpdatePrizeOrbs and SuspendTaskAndSetFlag call it. |
| ov001:0x0206685c | THUMB | `HasActiveFieldEffects` | `src/overlays/ov001/calls/HasActiveFieldEffects.c` | `BOOL(void)`. Returns normalizedboolean for pool active-list pointer at+0x4c being nonNULL. Boundary: Requires initialized pool; unlike EnsureFieldEffectPool no NULL global guard. | SpawnEffect and task creation/link setup identify list as embedded task+0x10 at pool+0x3c. |
| ov001:0x02065448 | THUMB | `ScriptCmd_EnsureFieldEffectPool` | `src/overlays/ov001/calls/ScriptCmd_EnsureFieldEffectPool.c` | `int(void)`. Calls EnsureFieldEffectPool then returns 1. Boundary: Old FS_UnloadOverlayImage label is a false SDK template. VM argument is not real callee input. | gFieldScriptCommandHandlers and wrapper alias resolves to 663e4. |
| ov001:0x02065b8c | THUMB | `ScriptCmd_WaitForFieldEffectsThenSuspend` | `src/overlays/ov001/calls/ScriptCmd_WaitForFieldEffectsThenSuspend.c` | `int(void)`. Calls WakeNearbyIdleNodes(0), returns 0 if active effects remain; otherwise calls StartIdleSceneObjects, SuspendTaskAndSetFlag and returns 1. Boundary: Preserve wake call even while polling. Suspension helper may release nodes when session.phase==-3; do not drop its side effects. | gFieldScriptCommandHandlers. |

## Scene-entry context and caption selection

The owner is `data_ov001_020a048c`, separate from the field session. Its
current-entry byte +0x0d is signed, with -1 as a sentinel. Scene slots begin
at +0x18 with stride 0x108 and count 16. At slot +0x104, mask 0x80 means
initialized and mask 1 controls drawing; these are independent conditions.
The caption adapter in ov007 is included because its native result chain reads
this entry index and resolves the corresponding caption resource. Its second
input remains an untyped command-state owner; no opcode role is inferred.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0206747c | THUMB | `DestroySceneEntryContext` | `src/overlays/ov001/calls/DestroySceneEntryContext.c` | `void(void)`. Shuts down scene slots/actors, releases message resource+4, releases layer/context data, frees outer global scene context and setsNULL. Boundary: No outer NULL guard in original. Distinct from ShutdownSceneContext, which retains the outer allocation. | ShutdownFieldSession calls it. |
| ov001:0x02067a6c | THUMB | `ReleaseAllSceneSlotResources` | `src/overlays/ov001/calls/ReleaseAllSceneSlotResources.c` | `void(void)`. For 16 scene slots atcontext+0x18 stride 0x108, releases initialized nodes when flags+0x104 bit 0x80 set, then zeroes full flag byte. Boundary: Uninitialized slots are left untouched; releases resource nodes, not entire context. | Called by ShutdownSceneContext, FinishAreaTransition, StageStateFinish. |
| ov001:0x02067cd0 | THUMB | `SetSceneSlotDrawingEnabled` | `src/overlays/ov001/calls/SetSceneSlotDrawingEnabled.c` | `void(int slot, BOOL enabled)`. For selected scene slot, sets mask 1 when enabled nonzero and clears it otherwise. Boundary: Index bounds not checked. Mask 1 controls draw eligibility; preserve other flag bits. | DrawVisibleSceneSlots draws iff mask 1 AND initialized mask 0x80. |
| ov001:0x02065550 | THUMB | `ScriptCmd_SetSceneSlotDrawingEnabled` | `src/overlays/ov001/calls/ScriptCmd_SetSceneSlotDrawingEnabled.c` | `int(void *vm, ScriptOperand *operands)`. Reads two integer operands and forwards slot/enabled to scene-slot drawing toggle, returns 1. Boundary: Nonzero truth is used by target, not merely low bit. | gFieldScriptCommandHandlers and actual target67cd0. |
| ov001:0x02067ed4 | THUMB | `GetCurrentSceneEntryIndex` | `src/overlays/ov001/calls/GetCurrentSceneEntryIndex.c` | `int(void)`. Returns signed current-entry byte+0xd from global scene context. Boundary: Signed-1 sentinel and int sign extension are required. This is not global stage id or context mode. | SceneEntryContext.h names fieldcurrentEntry; CreateSceneContext initializes-1; scene loading indexes table with it. |
| ov007:0x020a08a4 | ARM | `ShowCurrentSceneEntryCaptionAndSetFlag2` | `src/overlays/ov007/calls/ShowCurrentSceneEntryCaptionAndSetFlag2.c` | `int(u32 unused, void *commandState)`. Sets flag 2 in byte+0x0f of second argument; gets current scene-entry index, passes to GetSceneEntryResourceId, passes returned value to SetFieldCaptionText, returns 0. Boundary: Dispatch/callback role is not demonstrated by currently identified tables; name only describes body, no opcode claim. Real result flow must be explicit in portable C; second argument flag byte is not evidence for a SceneContext type. | Original ROM disassembly is three consecutive BLX with r0 result forwarded; current no-arg prototypes erase the chain. |

## Stage-event release and handler state

Release/disable policy, optional stage-group triggering and actor-slot priority
updates are separate effects; they must not become an unconditional delete.
The handler-state setter writes record word 0 and mask 4 at halfword +6.
`UpdateStageEvent` reads that same word as the index into
`gStageScriptStateHandlers`, whose EU DATA identity is ov001:0x020a0298.
Its current local field name `kind` does not make this a second kind setter:
the separate SetStageEventKind API addresses another field. Nonzero handler
results can change the current dispatch state; this is not a queued-state word.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x02065388 | THUMB | `ScriptCmd_ReleaseOrDisableStageEvent` | `src/overlays/ov001/calls/ScriptCmd_ReleaseOrDisableStageEvent.c` | `int(void *vm, ScriptCommand *command)`. Reads three integer operands; delegates release/disable and optional group event, optionally maps first id with LookupStagePairValue, decrements actor-slot priority by 1 when resulting index>=0; returns 1. Boundary: Second operand controls two distinct lookups with opposite conditions in caller/callee. Do not fold those or drop final actor priority update. | gFieldScriptCommandHandlers and real helper688d4. |
| ov001:0x020688d4 | THUMB | `ReleaseOrDisableStageEvent` | `src/overlays/ov001/calls/ReleaseOrDisableStageEvent.c` | `void(u32 eventId, int hasValue, int disable)`. When hasValue0 derives id from LookupPairValue_0206881c; in field session state 6 tries group event; then disables stage events if flag nonzero, otherwise releases hold bit 1, using low16 id. Boundary: Not an unconditional delete or event completion. Preserve TryTriggerGroupEvent before final release/disable. | Called by ScriptCmd_ReleaseOrDisableStageEvent, RunSpawnCommand and RestoreActiveRecordItems. |
| ov001:0x020925e4 | THUMB | `SetStageEventHandlerState` | `src/overlays/ov001/calls/SetStageEventHandlerState.c` | `void(StageEvent *event, s32 state)`. Replaces record word0 with the handler-state value and sets halfword+6 mask 4. Boundary: This changes the current dispatch state, not a separate queued state. Keep distinct from SetStageEventKind, which writes the secondary byte+0xc. Native r0 remains the input pointer; observed callers do not establish a logical pointer-return API. | UpdateStageEvent uses the same word0 directly as its handler table index; nonzero handler return is passed to this setter, and the update clears mask 4 after dispatch. InitializeActorStats and event release/hit paths set specific states through the same helper. |

## Class-backed field objects in ov001

These objects use the class manager `data_ov001_020a04f8`. Object +8 is its
class pointer, +0x0c is instance work, position is +0x40 and actor index is
byte +0x38. Class state and instance work are not interchangeable merely because
a legacy local calls either one work. Shape storage at object +0x18, data
buffers +0xa0, class model records and a heap touch-handler pointer +0x74 have
different lifetimes. The type-11 model scans stop after the first matching
nonempty class. The paired touch callbacks unlink and free in different steps.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x020814dc | THUMB | `SetFieldObjectPositionPlusOffset` | `src/overlays/ov001/calls/SetFieldObjectPositionPlusOffset.c` | `void(FieldObject *object, const VecFx32 *offset)`. Adds object position at +0x40 to the supplied vector and stores the result at object +0x78. Boundary: The destination is a separate vector, not the base position. Its broader target/velocity semantics are not asserted. | ScriptOp_SetObjectVector resolves class/index, reads three fixed-point operands into a vector and calls this helper. |
| ov001:0x02081d6c | THUMB | `DisableTargetViewForSavedFlag` | `src/overlays/ov001/calls/DisableTargetViewForSavedFlag.c` | `void(FieldObject *object)`. For object byte +0x59 equal to 1, tests saved bit 0x580 plus byte +0x5a and disables the field object when that bit is set. Boundary: Do not generalize to all field-object types. Preserve the original byte interpretation and saved-bit arithmetic. | CreateTargetViewClass installs this as hook16; FieldObject_SetEnabled(FALSE) updates packed save state and underlying actor enabled state. |
| ov001:0x02081fac | THUMB | `DrawProjectionViewFieldObject` | `src/overlays/ov001/calls/DrawProjectionViewFieldObject.c` | `void(FieldObject *object)`. Draws the object model at work+0x14 using its class projection at +0x84 and signed half extents from class +0xbc/+0xc0. Boundary: The model uses object->work, while projection/half extents use object->objectClass. Existing local variable named work points to the class and is misleading. | CreateProjectionViewClass installs this as draw hook15, initializes the projection and stores width/depth halves in those exact fields. |
| ov001:0x02082730 | THUMB | `GetFieldObjectActorSlotFlag8` | `src/overlays/ov001/calls/GetFieldObjectActorSlotFlag8.c` | `BOOL(const FieldObject *object)`. Reads object actor index byte +0x38 and tail branches to ActorSlot_IsFlag8SetByIndex, preserving its BOOL return. Boundary: Inherited C definition incorrectly says void. This is a slot flag query, not object allocation or unconditional activation. | ROM disassembly is saved. PlaceRecordPanels in ov031 uses the returned BOOL in a condition. The callee resolves an actor slot and queries Container_HasFlag3. |
| ov001:0x02082888 | THUMB | `ReloadFirstType11FieldObjectModels` | `src/overlays/ov001/calls/ReloadFirstType11FieldObjectModels.c` | `void(void)`. Finds the first nonempty registered field-object class whose first object classType is11; releases its attached models and loads the four model resources again. Boundary: Stops after the first matching class. Existing cursor terminology does not establish a cursor gameplay role for every caller. | Object class manager getters 0207f040/50/60 establish lookup; ReleaseAttachedModels and LoadCursorModels operate on four model records at class+0x84. Playback/panel transition callbacks call this helper. |
| ov001:0x020828d4 | THUMB | `ReleaseFirstType11FieldObjectModels` | `src/overlays/ov001/calls/ReleaseFirstType11FieldObjectModels.c` | `void(void)`. Finds the same first nonempty type 11 class and releases its four attached models. Boundary: Does not release all classes, unregister objects or reload resources. | Paired with 02082888 in playback/panel exit paths. ReleaseAttachedModels checks the first model resource before releasing all four records. |
| ov001:0x02084d84 | THUMB | `ReleaseFieldObjectDataAndShape` | `src/overlays/ov001/calls/ReleaseFieldObjectDataAndShape.c` | `void(FieldObject *object)`. Releases data buffers at object+0xa0, calls the empty/default helper for work+0x1a8, then releases object shape data. Boundary: FSi_DefaultStepDoneA is a return 1 no-op, not a proven shadow destructor. This helper does not free the object or class. | CreateGridWidget installs this in class hook6; Obj_FreeDataBuffers handles nested data and 0207f26c releases shape.data at object+0x18. |
| ov001:0x02085ca4 | THUMB | `CreateSpawnerFieldObject` | `src/overlays/ov001/calls/CreateSpawnerFieldObject.c` | `FieldObject *(FieldObjectClass *class, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, s32 value6c, u16 value5c, const VecFx32 *position)`. Creates an object, stores position/save-bit parameters, initializes collision/probe data and origin, installs the spawner update callback, and sets object flag 0x4000. Boundary: The two extra values are stored at +0x6c/+0x5c. Their broader meaning remains opaque; BuildCollisionShape has a synthetic unused ninth argument in current declarations. Preserve actual narrowing. | ScriptCmd_CreateFieldObjectFx provides the seven arguments; ResetFallingObjectSpawner installs TickSpawnerObject, which advances the class spawner timer for this object. |
| ov001:0x02085d74 | THUMB | `ReleaseFieldObjectTouchHandler` | `src/overlays/ov001/calls/ReleaseFieldObjectTouchHandler.c` | `void(FieldObject *object)`. Frees the handler pointer at object+0x74 and clears that field. Boundary: The inherited onTouchStart label does not imply this helper starts input. The operation is release-and-clear and it adds no NULL check. | AttachTouchHandler allocates a 20-byte MakeCommandRecord at +0x74 and installs this helper in callback slot+0x68. |
| ov001:0x02085d84 | THUMB | `DispatchFieldObjectTouchCommandAndUnlinkHandler` | `src/overlays/ov001/calls/DispatchFieldObjectTouchCommandAndUnlinkHandler.c` | `void(FieldObject *object)`. Extracts the signed11-bit command from packed word+0x58, forwards it to the active actor-command adapter, then unlinks the object handler at+0x74. Boundary: The unlink does not free the handler; the paired release callback frees and clears it. Preserve command forwarding before unlink, unknown commands as no-op in the adapter, and overlay/context preconditions. | AttachTouchHandler installs this callback and creates the20-byte handler. The ov059 adapter maps commands0x1f8..0x1fb to command types0..3; Actor_SetCommandType updates its current command slot and focuses menu entries0xdd..0xe0. UnlinkPendingNode removes the handler from the ov031 pending list. |

## Elevator classes and objects in ov006

Elevator script constructors register class pointers in the same class table.
The descriptor's class count is not a type enum, and its second vector is an
offset added to position, not Euler rotation. Object position +0x40 and center
+0x58 are borrowed vectors. The disabled gate in the center getter is distinct
from an assumption that an elevator is stationary. Animation state/frame are
shown by their update consumer; open/close meanings are not invented.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov006:0x020a0540 | THUMB | `ScriptCmd_CreateElevatorClass` | `src/overlays/ov006/calls/ScriptCmd_CreateElevatorClass.c` | `int(void *vm, ScriptOperand *operands)`. Reads group-table index, class object count and ElevatorDesc fields from 14 operands, creates elevator class, stores resulting class pointer at selected global group index, returns 1. Boundary: Inherited second local kind is actually class count per real callee. Values narrow into descriptor s16/u8 as original. Do not infer names of stopA/B/C beyond current structure evidence. | gOv006Handlers table entry0. |
| ov006:0x020a0604 | THUMB | `ScriptCmd_CreateElevatorObject` | `src/overlays/ov006/calls/ScriptCmd_CreateElevatorObject.c` | `int(void *vm, ScriptOperand *operands)`. Resolves group class, slot, raw packed save-bit operand, position and center offset xyz, constructs object, returns 1. Boundary: Raw operand2 bypasses VM reader. Last vector is positional offset added to position, not Euler rotation despite current local rotation label. Callee narrows slot to 8bits, count to 8bits. | gOv006Handlers entry2 and other script tables. |
| ov006:0x020a0708 | THUMB | `RestartElevatorStateAnimation` | `src/overlays/ov006/calls/RestartElevatorStateAnimation.c` | `void(ElevatorObject *object)`. Zeroes frame+0x68, rebinds actor animation to signed state+0x53 at frame0, clears animation flag 1; state 1 plays sound0x19e,0 and sets saved mask 4 unless object flags0x10 set. Boundary: Existing local timer/animBlend names are misleading: frame/state are demonstrated by real consumer. No fabricated open/close semantics for animation groups. | TryActivateElevatorSlot sets state 1 then calls; UpdateStaticElevator calls after changing state 0/1/2/3. |
| ov006:0x020a0a58 | THUMB | `GetElevatorObjectPosition` | `src/overlays/ov006/auto/GetElevatorObjectPosition.c` | `VecFx32 *(ElevatorObject *object)`. Returns borrowed VecFx32 at object+0x40. Boundary: No copy/null check; maintain caller object lifetime. | CreateElevatorObject writes position exactly at+0x40. |
| ov006:0x020a0c0c | THUMB | `GetElevatorCenterIfEnabled` | `src/overlays/ov006/calls/GetElevatorCenterIfEnabled.c` | `VecFx32 *(ElevatorObject *object)`. Returns null when object disabled bit at+0x6d is set, otherwise pointer to center at+0x58. Boundary: Do not infer stationary-vs-moving merely from one constructor alias; concrete condition is disabled bit. Center is borrowed. | CreateElevatorObject sets center to position+offset at+0x58. |

## Grid indexing in ov006

The grid dimensions/index arithmetic and cell storage are separate views.
The column count is signed s16 at +0x0e; cell records are four bytes at the
table pointer +0x24. Reading a cell's first byte does not prove whether it is a
height, flags or a cell type. Neither helper adds range validation.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov006:0x020a1338 | THUMB | `GetGridRowMajorIndex` | `src/overlays/ov006/auto/GetGridRowMajorIndex.c` | `int(const GridInfo *grid, int row, int column)`. Returns column + row * signed16 grid.columns at+0x0e. Boundary: No bounds check. Preserve signed columns/row/column and arithmetic order. | ResolveSegmentNodes maps link(from,to) to node indices with this helper; RunGridPathCommand uses as path goal. |
| ov006:0x020a14e0 | THUMB | `GetFieldGridCellValue` | `src/overlays/ov006/auto/GetFieldGridCellValue.c` | `u8(const FieldGrid *grid, int cellIndex)`. Returns first byte of selected4-byte cell record from table pointer+0x24. Boundary: Byte meaning beyond cell value is not proven; do not call it flags/type/height. No index check. | Ghidra EU xref: SampleGridCellValue in ov021 calls getter. |

## Wander-object position in ov007

This class hook follows object +0x0c to the actor and returns actor +0xb8.
It is not the raised copy used by GetRaisedOwnerPosition. Borrowed position
storage must remain tied to that actor's lifetime.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov007:0x020a100c | ARM | `GetWanderActorPosition` | `src/overlays/ov007/auto/GetWanderActorPosition.c` | `VecFx32 *(WanderObject *object)`. Returns entity pointer at object+0x0c, then borrowed VecFx32 at entity+0xb8. Boundary: Legacy four arbitrary u32 arguments are synthetic; only objectr0 is real input. Return pointer is actor-owned, not raised copy. | CreateWanderActorClass hook10 uses getter. |

## Event target and scene-entry trigger work in ov007

The layer/channel outputs belong to EventTargetWork and are respectively
signed s16 and unsigned byte. The flag-0x40 trigger belongs to its task/trigger
work and also checks the current scene-entry index. Its ov035 flag is an
observed mask, not a recovered movie-ready condition. Delay processing can
replace the trigger's update callback.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov007:0x020a1b28 | THUMB | `GetEventTargetLayerAndChannel` | `src/overlays/ov007/calls/GetEventTargetLayerAndChannel.c` | `void(const EventTargetWork *object, s32 *outLayer, u32 *outChannel)`. Sign-extends signed16 layer at+0xac into output0 and zero-extends channel byte+0xae into output1. Boundary: Both outputs required. Existing caller variable eventId does not justify treating signed layer as generic event id. | UpdateEventTargetMode local EventTargetWork identifies same offsets as layerId/channel and passes to ScriptCmd_ResetScreenLayer. |
| ov007:0x020a1ba0 | THUMB | `EvaluateSceneEntryFlag40Trigger` | `src/overlays/ov007/calls/EvaluateSceneEntryFlag40Trigger.c` | `int(EventTrigger *trigger)`. Zeroes result byte10, rejects when expected signed entry12 differs from current scene entry; if suppress field14 is0 and ov035 flag 6 mask 40 set, sets result1; invokes UpdateEventTriggerDelay and returns result only when that helper permits. Boundary: Meaning of field14/ov035mask40 unassigned; current alreadyRun/priority templates conflict. Do not call flag movie ready or callback an elapsed-time timer. UpdateEventTriggerDelay can rewrite update callback. | InitTaskCallbacks installs as update; ResetTaskUpdateCallback reinstalls it and clears result. |

## Special-action work in ov010

`gSpecialActionWork` is a separate, reusable 0x9c-byte heap allocation.
Its actor/entity input is stored at +0x20, message/effect resources at +0x2c
and camera path at +0x3c. Resource/sprite setup is reused when already allocated,
but initialization still resets state and the path. State 2 retains its numeric
identity rather than a fabricated action label. RestartObjectEffect consumes the
real work pointer even where an inherited no-argument view hides it.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov010:0x020a0cf8 | THUMB | `EnterSpecialActionState2` | `src/overlays/ov010/calls/EnterSpecialActionState2.c` | `void(SpecialActionWork *work)`. Writes special-action state 2, clears words4/24/28, targetIndex18=-1, clears session flags3716/3717. Boundary: No arbitrary Actor object: real owner is special-action work. State 2 gameplay label not proven, so numeric state is retained. | Entity_HandleSpecialAction passes gSpecialActionWork after mode callback returns 0x1e. |
| ov010:0x020a0d20 | THUMB | `ResetSpecialActionState` | `src/overlays/ov010/calls/ResetSpecialActionState.c` | `void(SpecialActionWork *work)`. Sets work state 0, calls RestartObjectEffect(work), clears3713/3716/3717. Boundary: Inherited RestartObjectEffect(void) omits real work input; port must pass it explicitly. This helper resets effect/group state, not outer deallocation. | ReleaseSpecialActionWork calls this before releasing resource/camera path. |
| ov010:0x020a17c0 | THUMB | `InitSpecialActionWork` | `src/overlays/ov010/calls/InitSpecialActionWork.c` | `void(Entity *entity)`. Allocates0x9c if absent, loads effect resource and sprites once; resets fields, stores actor/entity input at+0x20, clears3716/3717 and loads camera path at+0x3c. Boundary: Reuses resource/sprite setup when already allocated but resets state and camera path each invocation. Existing unsignedint return declarations for alloc/resource are placeholders. | LoadOverlay053EntityResources passes entity. |
| ov010:0x020a1978 | THUMB | `IsSpecialActionStateNonzero` | `src/overlays/ov010/calls/IsSpecialActionStateNonzero.c` | `BOOL(void)`. Returns FALSE if global absent; otherwise returns normalizedboolean for first state word nonzero. Boundary: Only state!=0 is demonstrated; no generalized completion/availability guarantee. | UpdateActionCommand uses predicate with player-control condition. |

## Entry-pool objects and interactions in ov016-020

These object families use the separate pool manager `data_ov001_020a04fc`.
The pool accessor uses entries +0x40 and u16 stride +0x3c. It does not share
the class-backed object's +0x44/+0x48 layout. In the ov016 family, position
is +0x38, actor index +0x32 and state flags +0xc0; other overlay-specific views
must retain their own layouts. Interaction-block mask 0x20 in manager byte +5
suppresses the observed hit/collection/activation callbacks; it does not pause
every update or draw operation.

Spawn wrappers must preserve the pool index returned by the common reader,
including across the extra-vector reader. Raw packed operands bypassing VM
resolution remain raw. The extra vector is only a three-word storage grouping;
its spatial meaning in mode 5 remains unproved. Kind-3 collision is a box and
the real builder has eight inputs; a legacy ninth argument is not a priority.

The ov016 node-8 animation track +0x48 and auxiliary track +0x58 are distinct
16-byte records. Completion callbacks at +0x68 are enabled by mask 0x80 and
invoked before reward/disable; setting a null callback while leaving that mask
enabled is not a proved safe use. Parent/previous-chain traversals preserve
self-inclusion, last-versus-first selection, signed indices and their distinct
+0x56/+0x58 links. They add no cycle guard.

The ov017 drop ray has the exact direction `(0,-0x64000,0)`, or -100 in
FX32 units on Y, rather than a normalized downward vector. Its offset/bias
calculation cannot be replaced by normalization without changing the operation.
Callback slot names inherited from templates do not establish lifecycle:
the grid pool's slot +0x38 draws, while +4 computes the drop offset.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x02065200 | THUMB | `ScriptCmd_UnpauseFieldEntriesIfFlag20Clear` | `src/overlays/ov001/calls/ScriptCmd_UnpauseFieldEntriesIfFlag20Clear.c` | `int(void)`. If session flag 0x20 clear, unpauses field entries and returns 1; otherwise returns 0. Boundary: Do not call the flag a generalized readiness predicate. Preserve false return while mask set. | gFieldScriptCommandHandlers and actual SetFieldEntriesPaused body propagates pause state to field actors/sprites. |
| ov001:0x02087650 | THUMB | `SetFieldObjectInteractionsBlocked` | `src/overlays/ov001/calls/SetFieldObjectInteractionsBlocked.c` | `void(BOOL blocked)`. Sets or clears entry-manager byte5 mask 0x20, which suppresses object hit/activation/collection handlers. Boundary: Does not pause updates, rendering or every possible script operation. The established scope is the observed field-object interaction callbacks; no reference-counted nesting. | Six callback families in ov016–019 check getter02087674 before applying damage, hit counters, collection rewards or activation. Transition entry callers set1; resume callers clear0. |
| ov001:0x02087674 | THUMB | `GetFieldObjectInteractionBlockMask` | `src/overlays/ov001/auto/GetFieldObjectInteractionBlockMask.c` | `u32(void)`. Returns raw entry-manager byte5 mask 0x20 used to suppress field-object hit, collection and activation processing. Boundary: Logical signature has no inputs even where inherited declarations pass an event/object/hit. Return is0 or0x20, not normalized1. | HandleFieldObjectHit, HandleFieldObjectHit_020a50a4, FieldDrop_OnCollect, HandleFieldObjectActivation, FieldObject_TakeDamage and HandleLinkHit return before their effects when this mask is nonzero. |
| ov016:0x020a2020 | THUMB | `ScriptCmd_SpawnFieldObjectTree` | `src/overlays/ov016/calls/ScriptCmd_SpawnFieldObjectTree.c` | `int(void *vm, ScriptOperand *operands)`. Reads shared entity spawn parameters, uses their returned pool index to select a pool, spawns the object tree, returns 1. Boundary: Inherited C omits the returned index at the pool call; it is real input and must be explicit in portable source. Original extra caller registers are not parameters. | Script command table data_ov016_020a6e60 slot 2; ScriptCmd_ReadEntityParams returns its first consumed integer. |
| ov016:0x020a2084 | THUMB | `ReadFieldObjectSpawnExtraVector` | `src/overlays/ov016/calls/ReadFieldObjectSpawnExtraVector.c` | `void(SpawnDesc *desc, void *vm, ScriptOperand **cursor)`. Consumes three fx32 operands into descriptor words +0x50,+0x54,+0x58, updating the operand cursor. Boundary: Vector is storage grouping only; spatial meaning of these mode 5 values is not established. Preserve 3 operand reads and ordering. | Called by the extended spawn command and ScriptCmd_ApplyEntityColorVecParams. |
| ov016:0x020a20ac | THUMB | `ScriptCmd_SpawnFieldObjectTreeWithExtraVector` | `src/overlays/ov016/calls/ScriptCmd_SpawnFieldObjectTreeWithExtraVector.c` | `int(void *vm, ScriptOperand *operands)`. Reads shared spawn parameters, appends three fx32 operands, selects the original pool index, spawns, returns 1. Boundary: Inherited C overwrites context with return of a void reader/omits argument, although original register flow preserves the index. Do not port that undefined C contract. | Script table slot 18. |
| ov016:0x020a2244 | THUMB | `ScriptCmd_SetFieldObjectFlag22` | `src/overlays/ov016/calls/ScriptCmd_SetFieldObjectFlag22.c` | `int(void *vm, ScriptOperand *operands)`. Consumes pool index then object index, resolves object, ORs 0x400000 in stateFlags +0xc0, returns 1. Boundary: Bit controls a per-pool visibility/height pass, but full gameplay meaning is not established. Keep explicit bit 22 operation, not a fabricated role. | Script table slot 24. |
| ov016:0x020a2284 | THUMB | `ScriptCmd_FreeFieldResourceCache` | `src/overlays/ov016/calls/ScriptCmd_FreeFieldResourceCache.c` | `int(void)`. Frees global field resource cache slots and returns 1. Boundary: Callee is void(void), not void(void *p); incoming script VM is unused by the real implementation. No ownership transfer of that VM. | Script table slot 22. |
| ov016:0x020a232c | THUMB | `UpdateFieldObjectDrawFlagFromPreviousLink` | `src/overlays/ov016/calls/UpdateFieldObjectDrawFlagFromPreviousLink.c` | `void(FieldObject *object)`. Sets drawFlags0x10 when signed previous-link index +0x90 is -1, otherwise clears it. Boundary: Compare exactly -1, not any negative value. The complete render role of mask 0x10 is intentionally not asserted. | LinkStackedFieldObjects calls this for linked objects, with its local view identifying +0x90 as linkPrev. |
| ov016:0x020a2578 | THUMB | `ReinsertFieldObjectActorInQuadTree` | `src/overlays/ov016/calls/ReinsertFieldObjectActorInQuadTree.c` | `void(FieldObject *object)`. Gets the object actor, sets its embedded node flag and conditionally reinserts its spatial node when registry exists, actor bit 8 set and bit 0x10 clear. Boundary: Large ActorNode array expressions are legacy synthetic layout; do not preserve fictitious actor[1] ownership in a port. | Called after movement by MoveFieldObjectWithCollision, LowerFieldObjectStep, SwayAndDropFieldObject and UpdatePathMovement. |
| ov016:0x020a25b8 | THUMB | `BuildFieldObjectBoxCollision` | `src/overlays/ov016/calls/BuildFieldObjectBoxCollision.c` | `void(FieldObject *object, BOOL allocate)`. Builds kind 3 collision shape at object +0x10 around position +0x38, three sizes0x1800, angle0, allocation controlled by second parameter. Boundary: Inherited caller declares 9 args but real BuildCollisionShape takes8; trailing4 is not a real priority/stride. Preserve allocation-vs-update behavior. | SpawnFieldObjectTree passes1; SetFieldUnitPosition passes0 when actor/shape flag is set. |
| ov016:0x020a2688 | THUMB | `SetFieldObjectActorEnabled` | `src/overlays/ov016/calls/SetFieldObjectActorEnabled.c` | `void(FieldObject *object, BOOL enabled)`. Synchronizes highlight flags, actor position when enabling, actor record-slot state bit 0x100, and object stateFlags bit 0. Boundary: Does not change hidden stateFlags0x10 itself, and is broader than just visibility. No fabricated always-reset semantics. | SetFieldObjectHidden calls with 0 when hiding and1 when showing; model load/animation synchronization also use it. |
| ov016:0x020a298c | THUMB | `FinishFieldObjectAndMaybeGrantReward` | `src/overlays/ov016/calls/FinishFieldObjectAndMaybeGrantReward.c` | `void(FieldObject *object, BOOL grantReward)`. Propagates stack state, invokes registered callback when stateFlags0x80 set, optionally grants reward and increments session counter0x1c, then disables actor. Boundary: Callback is invoked before reward and disable, not cleared here, and is not NULL-checked once enabled. Parameter called doReset is reward choice, not blanket object reset. StackFieldObjectChain receives object in r0 despite old void(void) declaration. | EnterFieldUnitPhase5 and InitializeFieldEffect call it; PairFieldObjects passesFALSE. |
| ov016:0x020a2b28 | THUMB | `InitFieldObjectNode8AnimTrack` | `src/overlays/ov016/calls/InitFieldObjectNode8AnimTrack.c` | `void(FieldObject *object)`. Initializes object animation track at+0x48 with node index 8, speed0x1000, animation id0. Boundary: 8 is node index, not count; legacy buffer[8] is too short, real AnimTrack occupies16 bytes. | EnterFieldUnitPhase5 calls it. |
| ov016:0x020a2b98 | THUMB | `UpdateFieldObjectAuxAnimTrack` | `src/overlays/ov016/calls/UpdateFieldObjectAuxAnimTrack.c` | `BOOL(FieldObject *object)`. When stateFlags0x8000 is set, advances track at+0x58, clears mask on completion and returns completion result; otherwise returns FALSE. Boundary: Auxiliary track at+0x58 is distinct from node8 track+0x48. Advance helper ignores obj and currently ignores track.speed; preserve actual unit tick. | UpdateFieldObject calls every applicable tick. |
| ov016:0x020a2c2c | THUMB | `StartFieldObjectActorAnimation1` | `src/overlays/ov016/calls/StartFieldObjectActorAnimation1.c` | `void(FieldObject *object)`. Rebinds actor animation group to 1 at frame0, clears animation flag 1, sets object stateFlags0x20. Boundary: Re-resolves actor twice as original. 1 is concrete animation group selection, not an invented destroy/open action. | EnterFieldUnitPhase5 and InitializeFieldEffect call it. |
| ov016:0x020a2c64 | THUMB | `UpdateFieldObjectActorAnimation` | `src/overlays/ov016/calls/UpdateFieldObjectActorAnimation.c` | `void(FieldObject *object)`. If stateFlags0x20, advances actor animation by 0x1000, clears the mask when finished, stores GetMaximumFieldValue result at object+0xc4. Boundary: Meaning of stored+c4 value not further established; no promise this is a duration rather than frame/field reading. | Called by SweepFieldObjectBounce and UpdateFieldUnitAnimPhase. |
| ov016:0x020a34e8 | THUMB | `ScaleFieldObjectVelocityBy85Percent` | `src/overlays/ov016/calls/ScaleFieldObjectVelocityBy85Percent.c` | `void(VecFx32 *velocity)`. Scales each signed32 vector component by 85 then signed-divides by 100. Boundary: Preserve signed multiply/divide ordering and truncation; replacing with fixed-point multiply/float can round differently. Original signed32 multiplication can overflow outside expected values; do not silently widen if preserving original semantics. | MoveFieldObjectWithCollision passes &object->velocity when keepVelocity is false. |
| ov016:0x020a6974 | THUMB | `SetFieldObjectCompletionCallback` | `src/overlays/ov016/calls/SetFieldObjectCompletionCallback.c` | `void(FieldObject *object, void (*callback)(FieldObject *))`. Stores callback at+0x68, ORs stateFlags0x80. Boundary: Does not accept NULL safely when invoked because enable flag remains set; no automatic callback clear. Callback argument is the same FieldObject. | ApplyGroupMemberKind, SpawnGroupMemberGrid, SpawnRowChainMembers install UnlinkGroupMember. |
| ov016:0x020a6a10 | THUMB | `GetFieldObjectHiddenMask` | `src/overlays/ov016/auto/GetFieldObjectHiddenMask.c` | `u32(const FieldObject *object)`. Returns raw stateFlags0x10. Boundary: Returns 0 or16, not normalizedBOOL1. Retain raw return even when old declaration in callers isBOOL. | SetFieldObjectHidden sets/clears exactly0x10 and uses this getter to decide actor flag 8. |
| ov016:0x020a6de4 | THUMB | `DispatchIndexedFieldObjectCollision` | `src/overlays/ov016/calls/DispatchIndexedFieldObjectCollision.c` | `int(int poolIndex, int objectIndex, CollisionBody *other, void *context)`. Uses first two arguments as pool/object index, resolves object and dispatches collision using third/fourth arguments; forwards collision result. Boundary: Inherited definition wrongly says unused1/unused2 and void; logical return is int and inputs matter. Ghidra uses imported void prototype, so raw bytes/caller/callee prove return, not decompiler type. | TriggerNextStageEvent passes scriptKind/scriptArg as selectors and branches on return. |
| ov016:0x020a6df8 | THUMB | `ApplyIndexedFieldGroupLeaderHit` | `src/overlays/ov016/calls/ApplyIndexedFieldGroupLeaderHit.c` | `int(int poolIndex, int objectIndex, int arg)`. Uses first two arguments as pool/object index, applies group-leader hit with third argument and returns 1. Boundary: First two args are not unused. No bounds/null guards added. | DispatchStageEventArg passes record.slotGroup/slotIndex/arg. |
| ov017:0x020a288c | THUMB | `DrawGridObjectActorQuads` | `src/overlays/ov017/calls/DrawGridObjectActorQuads.c` | `void(FieldObject *object)`. Resolves actor and draws textured grid quads with cell size0x1800, signed dimensions+0x49/+0x4a, actor resource+0x84, alpha0x1f; last flag is context mode!=6. Boundary: Do not infer callback lifecycle from current synthetic pool field names; body renders. | CreateGridEntryPool installs at callback slot 14 (+0x38). |
| ov017:0x020a28cc | THUMB | `UpdateGridObjectDropOffsetFromRay` | `src/overlays/ov017/calls/UpdateGridObjectDropOffsetFromRay.c` | `void(GridObject *object)`. Zeros drop offset+0x4c, casts ray from position using constant direction and length0x1800; hit vertical gap within[0x19a,0x7800] sets offset to hitY-posY+0x1e0. Boundary: Do not normalize ray direction or alter gap bounds/bias; callback field labels are not verified lifecycle evidence. | CreateGridEntryPool callback slot 1 (+4), despite synthetic name draw. |
| ov017:0x020a2e84 | THUMB | `DiscardKind4MessageNodesKeepingPinned` | `src/overlays/ov017/calls/DiscardKind4MessageNodesKeepingPinned.c` | `void(MessageOwner *object)`. Forwards object to DiscardMessageNodes with second argument1. Boundary: Old NNSSndStrm/stream callback enum is a false library template; value is simplyTRUE for real MessageOwner. Preserve sentinel handling in callee, not an unconditional full list free. | CreateKind4EntryPool callback slot 4 (+0x10). |
| ov017:0x020a51e8 | THUMB | `FindLastInactiveObjectInParentChain` | `src/overlays/ov017/calls/FindLastInactiveObjectInParentChain.c` | `FieldObject *(FieldObject *object)`. Walks self then signed parent-index+0x56 links, remembers last object whose signed state+0x50 is neither1 nor2, returns null if none. Boundary: Self-inclusive and last qualifying object, unlike FindInactiveAncestor. No cycle guard or NULL guard in original. | LoadStageObjectPhase and UpdateFallingBlock use as support/chain query. |
| ov017:0x020a525c | THUMB | `PropagateStackHeightWrapper` | `src/overlays/ov017/calls/PropagateStackHeightWrapper.c` | `void(FieldObject *object)`. Forwards object to PropagateStackHeight. Boundary: Inherited empty parameter list/pointer return is legacy; real contract is void(FieldObject *). | FieldDrop_OnCollect calls(target,self); second argument is unused by real callee. |
| ov017:0x020a5a98 | THUMB | `SyncKind7ActorFlagToActiveState` | `src/overlays/ov017/calls/SyncKind7ActorFlagToActiveState.c` | `void(FieldObject *object)`. Reads ActorSlot_IsFlag8SetByIndex for actor id+0x32, passes raw result to CacheEntry_SetActive. Boundary: Preserve raw flag result; active setter interprets it. No invented visibility/collision meaning for actor flag 8 beyond existing accessor. | CreateKind7EntryPool callback slot 3. |
| ov017:0x020a5e08 | THUMB | `FindLastInactiveObjectInParentChainWrapper` | `src/overlays/ov017/calls/FindLastInactiveObjectInParentChainWrapper.c` | `FieldObject *(FieldObject *object)`. Forwards to self-inclusive last-inactive parent-chain query. Boundary: Legacy parameterless definition still forwards incoming r0; returned pointer and input object are real. It can returnNULL, even though caller assumes a valid chain in this path. | UpdateOwnerFall uses returned object.slotIndex for targetIndex. |
| ov017:0x020a5e10 | THUMB | `FindRootObjectWrapper` | `src/overlays/ov017/calls/FindRootObjectWrapper.c` | `FieldObject *(FieldObject *object)`. Forwards object to FindRootObject and returns root object. Boundary: This root traversal uses+0x58, distinct from+0x56 parent traversal of last-inactive helper. Do not merge records solely on similar names. | UpdateOwnerFall passes target and queries root flag 4. |
| ov018:0x020a2234 | THUMB | `ReleaseKind6ObjectAttachment` | `src/overlays/ov018/calls/ReleaseKind6ObjectAttachment.c` | `void(FieldObject *object)`. If attachment+0x48 nonNULL, releases/detaches, frees and clears it; when field session state 7, unlinks embedded pending node+a8. Boundary: Does not free parent object; node unlink only in state 7. | CreateKind6EntryPool callback slot 4. |
| ov018:0x020a2260 | THUMB | `ReleaseKind6ObjectChannelAndResources` | `src/overlays/ov018/calls/ReleaseKind6ObjectChannelAndResources.c` | `void(FieldObject *object)`. Destroys entry group using signed channel+0x470, then releases four resource states+0x138/+0x23c/+0x340/+0x444 guarded by paired pointers. Boundary: Do not conflate with attachment destructor or assume parent deallocation; func_0202eb08 remains numerically named so exact resource type is unproven. | CreateKind6EntryPool callback slot 5. |
| ov019:0x020a23c0 | THUMB | `SettleLinkHeightAtZeroOffset` | `src/overlays/ov019/calls/SettleLinkHeightAtZeroOffset.c` | `void(LinkedObject *object)`. Calls SettleLinkHeight(object,0). Boundary: Old NNS_FndInitListWithOffset0 path is a false SDK classification. No NNS list initialization here. | HandleLinkHit passes(link,self), but wrapper only uses first parameter. |
| ov020:0x020a1e30 | THUMB | `ScriptCmd_SpawnPanelBlock` | `src/overlays/ov020/calls/ScriptCmd_SpawnPanelBlock.c` | `int(void *vm, ScriptOperand *operands)`. Consumes pool index/object id/slot, raw packed operand, position xyz/extra fx32, signed size integers, calls SpawnPanelBlock, returns 1. Boundary: Raw operand3 is not resolved through VM; low16 and high8 narrowing follow callee signature. Preserve operand evaluation order and signed sizes. | gPanelObjectScriptCommandHandlers has the handler. |
| ov020:0x020a2898 | ARM | `FindLastLiveBlockInPreviousChain` | `src/overlays/ov020/calls/FindLastLiveBlockInPreviousChain.c` | `Block *(Block *block)`. Walks self then signed previous index+0x56, remembers last block without flag 0x8000, returns null if none. Boundary: Self-inclusive, returns last rather than first. Live means precisely flag 0x8000 clear; broader lifecycle role not asserted. | LoadStackedBlockPhase and UpdateStackedBlock use as support. |
| ov020:0x020a2914 | ARM | `SettleBlockGroundWrapper` | `src/overlays/ov020/calls/SettleBlockGroundWrapper.c` | `void(Block *block)`. Forwards first object to recursive SettleBlockGround. Boundary: Inherited pointer return/parameterless source is legacy; logical result isvoid. | ActivatePanel calls(result,panel); second argument ignored. |
| ov020:0x020a2edc | ARM | `DrawPanelBlockVisibleParts` | `src/overlays/ov020/calls/DrawPanelBlockVisibleParts.c` | `void(PanelBlock *block)`. Draws attached scene node+0x48 if flags+0x54 bit 0x20, and actor scene node if bit 0x40. Boundary: Two independent tests; no attachment NULL check when enabled. Do not infer both parts share lifetime. | CreatePanelEntryPool installs callback slot 14. |

## Actor movement and stage-actor position

Actor movement reset, actor-script waiting and stage-actor position are
separate contracts. A target-move parameter is not proved to be a duration, and
waiting for one primary motion track does not wait for all animation. The stage
actor position getter returns actor +0x2c0; it does not use managed-actor +0xbc
or the wander actor's +0xb8. These views must not be merged into one host type.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0208a480 | THUMB | `ResetActorVelocityAndExtraSlots` | `src/overlays/ov001/calls/ResetActorVelocityAndExtraSlots.c` | `void(Actor *actor)`. Clears actor velocity via Actor_SetVelocity(NULL), zeroes four movement/control words at +0x858/+0x848/+0x844/+0x840, then clears three 12-byte extra slots. Boundary: The helper does not clear all actor flags or release resources. Preserve body-velocity update side effect. | Actor_SetVelocity zeroes actor and movement-body velocity. ActorObject_ClearExtraSlot clears actor+0x870 + index*0xc; placement and motion completion callers use this reset. |
| ov001:0x0208a44c | THUMB | `IsActorScriptWaitSatisfied` | `src/overlays/ov001/calls/IsActorScriptWaitSatisfied.c` | `BOOL(const ScriptActor *actor, int mode)`. For mode 0, checks target-move parameter +0x858 is0. For every other mode, checks primary motion frame+0xd4 is-1 and its name byte+0xdc is0. Boundary: Do not label +0x858 as duration: the script move-target caller supplies its fixed-point speed there. The animation test covers the primary track only, not every track or model state. | ScriptCmd_WaitActorReady is the real consumer: it resolves an actor, forwards mode and returns 1 only on this predicate, otherwise0 to keep waiting. SetTargetPosition writes target vector+0x840, parameter+0x858 and option+0x85c; MotionActor tracks start+0xd0. |
| ov001:0x02090f2c | THUMB | `GetStageActorPosition` | `src/overlays/ov001/auto/GetStageActorPosition.c` | `VecFx32 *(StageActor *actor)`. Returns the address actor+0x2c0. Boundary: Returns borrowed mutable storage with no NULL check. It does not resolve an actor ID or copy a vector. | Vector operand resolution, target-facing dot products and horizontal offset commands in ov021 read this as VecFx32; ov056 CircleActorAroundUnit passes it directly to VEC_Subtract. |

## Rotation matrix and 3D node-state callback

The matrix helper builds fixed-point X, then Y, then Z concatenations.
Its sine-table indexing, reflected cosine index and per-operation rounding are
part of the native operation. The other function is a one-input NNSG3dRS SBC
callback, installed by Actor_InstallNodeStateCallback for command 6/timing 3.
It preserves the same render-state pointer across part rotation and node-matrix
capture. The inherited 2D cell-animation/sequence signature is not its contract.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x020895ac | THUMB | `BuildXyzRotationMatrix33` | `src/overlays/ov001/calls/BuildXyzRotationMatrix33.c` | `void(MtxFx33 *out, int xAngle, int yAngle, int zAngle)`. Initializes the output identity matrix, then concatenates X, Y and Z rotations in that order using the fixed-point sine table. Boundary: Preserve axis concatenation order, table index shifts and fixed-point rounding. Do not replace with a float Euler matrix without a port-level equivalence decision. | RotationTweenStep calls this with each interpolated component narrowed to u16. ROM preserves incoming out in r0 for the first MTX_Identity33_ despite the current omitted argument declaration. |
| ov001:0x0208985c | THUMB | `ApplyPartRotationAndCaptureNodeCallback` | `src/overlays/ov001/calls/ApplyPartRotationAndCaptureNodeCallback.c` | `void(NNSG3dRS *renderState)`. Runs ApplyPartRotationToGeometry for the render state, then runs the selected-node matrix capture/copy path with the same render-state pointer. Boundary: Inherited definition and borrowed NNSG2dCellAnimation/sequence types are false. Do not retain a logical second argument or confuse this with 2D cell animation. | Actor_InstallNodeStateCallback installs it as an SBC callback for command6/timing3. ROM saves r0 across the first call and restores it for CopySessionResourceBuffer. Both real callees consume one input. |

## Field-camera tween work

Both updaters use `gActorChannelContext`. They decrement the remaining
counter before testing for exactly zero; an endpoint copy/angle selection occurs
only on that result. The pose updater handles five scalars and three vectors,
while the heading updater writes a sine/cosine pair. Preserve each interpolation
mode, table lookup and integer/fixed-point operation rather than substituting a
generic floating interpolation.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0208b5d0 | THUMB | `UpdateFieldCameraPoseTween` | `src/overlays/ov001/calls/UpdateFieldCameraPoseTween.c` | `void(void)`. Decrements the field-camera tween counter. On completion copies the 0x38-byte target pose and clears tween mode; otherwise interpolates five scalars and three vectors. Boundary: Counter decrements unconditionally and endpoint copy occurs only when it becomes exactly0. Do not replace the entire function with a generic floating interpolation. | UpdateFieldCamera selects this for mode 6. EvaluateInterpolationCurve mode 5 and ScaleAroundPivot implement the scalar curve; VEC_Subtract/VEC_MultAdd interpolate the vectors. |
| ov001:0x0208b6ec | THUMB | `UpdateFieldCameraHeadingTween` | `src/overlays/ov001/calls/UpdateFieldCameraHeadingTween.c` | `void(void)`. Decrements the camera heading tween counter, selects final or eased angle, and writes its fixed-point sine/cosine pair to the first two pose words. Boundary: Preserve angle>>4 table lookup, cosine reflected index and exact completion behavior. Mode word clears when the decremented counter reaches0. | UpdateFieldCamera selects this for mode 7. EvaluateInterpolationCurve mode 3 and ScaleAroundPivot generate the intermediate turn index. |

## Relocated stage-resource name table

The last resource group is a pointer table after relocation. The supplied
element index is one-based and group count must be positive. The returned name
is borrowed; the getter neither resolves relocation nor validates the index.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0208f040 | THUMB | `GetStageResourceNameByIndex` | `src/overlays/ov001/calls/GetStageResourceNameByIndex.c` | `const char *(const StageResourceTable *table, int oneBasedIndex)`. Reads an element from the last resource group pointer table using index-1. Boundary: No bounds or NULL checks. The resource must already be relocated, groupCount must be positive, and input index is one-based. | RelocateResourceTable makes the last group entries absolute pointers. FindStageAttachPoint, GetRouteWaypointPlacement and ProcessStageCues use the result as a node/name string. |

## Stage linked-list views

List-head and list-node views both store their link at +8, but have different
null preconditions. The first getter tolerates a null list, whereas the next
getter requires a valid node. Neither getter transfers ownership or frees nodes.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0208f2a4 | THUMB | `GetStageListFirstOrNull` | `src/overlays/ov001/calls/GetStageListFirstOrNull.c` | `StageListNode *(const StageList *list)`. Returns list+8 pointer, or NULL when the list is NULL. Boundary: Offset8 belongs to the list head view here; do not infer ownership or free nodes through this getter. | DrawVisibleStageQuads, FindNearestCommandEntry and ReleaseEventLinkedEntries use it to begin traversal paired with 0208f2b4. |
| ov001:0x0208f2b4 | THUMB | `GetStageListNext` | `src/overlays/ov001/calls/GetStageListNext.c` | `StageListNode *(const StageListNode *node)`. Returns node+8 pointer, including NULL at the end. Boundary: The node argument itself is not NULL-checked. List-head and node layouts share offset8 but are distinct logical types. | The same traversal callers pair it with GetStageListFirstOrNull in their next-node step. |

## Stage-controller scale override

The controller stores a scalar override at +0x14. Its update consumer copies
a nonzero override into three actor scale components; zero disables the override,
rather than forcing zero model scale. Later scale tweening can alter the vector,
so update order remains significant.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x020983c4 | THUMB | `SetStageControllerUniformScale` | `src/overlays/ov001/auto/SetStageControllerUniformScale.c` | `void(StageController *controller, fx32 scale)`. Stores the scalar override at controller+0x14. Boundary: A stored0 disables this controller override, rather than forcing the model to zero scale. Active scale tweening can subsequently alter the actor vector; preserve update order. | UpdateActorController_02098124 copies a nonzero +0x14 value into actor scale vector components +0x2f0/+0x2f4/+0x2f8. UpdateModelScaleTween multiplies that vector by its factor and writes the model node scale. All observed setters pass attachment.scale.x. |

## Subscene panel work: map and list interfaces

The owner is `data_ov001_020a04e8`. Requested mode +0xd8 and loaded mode
+0xdc are distinct; the loaded-overlay table is `{23,24,25,23,26}`.
Mode 0 maps to ov023 and mode 2 to ov025. Panel phase +0x30, readiness word
+0x38, input-active word +0x40 and cached/live list parameters are different
gates. The map gate at EU ov001:0x0207a8fc requires loaded mode 0 and phase
3, 4 or 6. It does not require mode 2. List operations retain their individual
readiness, phase-6 or loaded-mode-only gates.

The cached list depth byte +0x102 is not a language code: downstream rebuild
logic compares path depth-1 with this limit. A live list override does not write
that cached byte. The cached slot values +0xe4 are u16-derived opaque values,
without a proved item/quantity/graphics interpretation.

Ownership also differs within this work: six highlight colors at +0xf4 and the
packed-message view +0x20 are inline. The entry-name array +0x110 and selected
name +0x1c are owned heap copies, borrowed through getters and invalidated by
teardown. The packed view owns a nested file buffer. The generic text pointer
+0x18 remains byte-typed because an empty UTF-16 fallback does not prove every
nonempty payload's encoding. A nonzero freed pointer or stored task handle is
not evidence of continued liveness.

Two existing ov025 callee names remain misleading and are outside this block:
ResetMenuLayerTransforms actually uploads SUB BG2/BG3 screen bytes; the parameter
0x1000 is a byte count, not a scale. DrawNumberInPanelSlot passes a text pointer
to the drawing API, with no demonstrated numeric formatting. The adapter names
below reflect the actual operations without enlarging this rename scope.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0207b1a8 | THUMB | `GetSubsceneTextOrEmpty` | `src/overlays/ov001/calls/GetSubsceneTextOrEmpty.c` | `u8 *(void)`. Returns the pointer stored at subscene work+0x18, or the shared empty string storage when either work or that pointer is NULL. Boundary: Borrowed pointer with no allocation. The stored payload encoding and caption/filename/message role remain unproved; keep the existing byte-pointer ABI. Do not infer UTF-16 solely from an empty fallback. | FieldTextFormats.h declares the shared empty fallback as u16[2]; that establishes the fallback storage, not the encoding or element type of every stored nonempty pointer. |
| ov001:0x0207b3f4 | THUMB | `GetLoadedSubsceneMode` | `src/overlays/ov001/calls/GetLoadedSubsceneMode.c` | `u32(void)`. Returns subscene work +0xdc, or 0xffffffff when there is no work. Boundary: The sentinel and raw numeric mode values must remain intact. Do not infer UI destination names. | ReloadSubsceneOverlayAfterFade resets +0xdc to -1 before loading; RequestPanelModeChange compares this current mode with requested mode at +0xd8. |
| ov001:0x0207b588 | THUMB | `GetSubsceneSlotValue` | `src/overlays/ov001/calls/GetSubsceneSlotValue.c` | `u32(s32 slot)`. Reads the live ov025 slot entry only when loaded mode is 2 and readiness +0x38 is nonzero; otherwise reads cached +0xe4[slot]. Boundary: No local bounds check exists on the cache path. No item, quantity or graphics meaning is proved for the value. | The ov025 LookupChannelEntry body uses selector 0..3 and an 8-byte entry table, returning its u16 value or -1. RequestPanelModeChange caches four such values before leaving mode 2. |
| ov001:0x0207b604 | THUMB | `GetSubsceneTaskObject` | `src/overlays/ov001/calls/GetSubsceneTaskObject.c` | `TaskObject *(void)`. Returns the task pointer stored at offset 0 of the global subscene work. Boundary: No NULL guard on the global work. A stored task handle is not proof that a task remains live. | UnloadSubsceneOverlayAndDestroyTask reads the same offset, passes it to the task destroy wrapper and clears it. |
| ov001:0x0207b610 | THUMB | `GetSubsceneReadyValue` | `src/overlays/ov001/auto/GetSubsceneReadyValue.c` | `u32(void)`. Returns the raw readiness word at subscene work +0x38. Boundary: Returns the full word, not normalized BOOL. The exact state meanings beyond zero/nonzero remain unknown. | RequestPanelModeChange and the mode-2 adapters require this word to be nonzero before calling ov025 functionality. |
| ov001:0x0207b61c | THUMB | `IsSubscenePanelState6` | `src/overlays/ov001/calls/IsSubscenePanelState6.c` | `BOOL(void)`. Returns whether subscene panel state +0x30 equals 6. Boundary: State 6 has not been given a gameplay name. Global work must exist. | The comparison is explicit and is also used as a precondition in ActivatePanelEntity wrapper 0207b77c. |
| ov001:0x0207b6b0 | THUMB | `RequestSubsceneMode0Or1FromMode4` | `src/overlays/ov001/calls/RequestSubsceneMode0Or1FromMode4.c` | `BOOL(void)`. If requested mode +0xd8 is 4, requests mode 1 when field session state is 10 and mode 0 otherwise, through the style-2 wrapper; returns 1 without a request for any other requested mode. Boundary: The +0x108 write precedes a possible rejected request, and RequestPanelModeChange may overwrite that word. This checks requested mode, not loaded mode. | RequestPanelModeWithStyle2 writes +0x108 = 2 then forwards the integer argument to RequestPanelModeChange. |
| ov001:0x0207b228 | THUMB | `SetSubsceneBgSetupCallback` | `src/overlays/ov001/auto/SetSubsceneBgSetupCallback.c` | `void(void (*callback)(void))`. Stores the callback pointer at subscene work+0x2c. Boundary: This setter does not invoke the callback. Its exact invocation timing is not established in the inspected consumers; preserve borrowed function-pointer lifetime across overlay teardown. | InitMenuResourceCache, CreateBoardScreen and InitMenuScreen pass actual SetupMenuSubBgLayers/SetupSubScreenBgLayers/SetupSubBgLayers functions. Those zero-argument functions configure SUB BG mode, control registers and priorities. Corresponding destructors clear the pointer. |
| ov001:0x0207b484 | THUMB | `GetPanelFormationType` | `src/overlays/ov001/calls/GetPanelFormationType.c` | `u8(void)`. Returns subscene panel formation byte+0x103, or0 if no panel work exists. Boundary: Do not assign gameplay labels to enum1/2. Absent-panel0 is a getter sentinel, not a documented third formation mode. | Panel_SetFormationType writes the same byte and conditionally calls ApplyFormationSlots. TogglePanelFormation toggles1/2; ApplyFormationSlots selects different slot animation sequences and panel modes. SelectNextSessionState snapshots this value and LeaveFieldMenu restores it. |
| ov001:0x0207b6fc | THUMB | `GetPanelInputActive` | `src/overlays/ov001/auto/GetPanelInputActive.c` | `u32(void)`. Returns the raw panel input-active word at+0x40. Boundary: No NULL guard and no normalization. This is the panel touch/input tracking flag, not session readiness at+0x38 or state+0x30. | SetPanelInputActive and ClearPanelInputActive write TRUE/FALSE at this exact offset. UpdatePanelScene samples touch only while nonzero and clears it through the paired helper after touch release; UpdateMenuScreen also queries it. |
| ov001:0x0207b21c | THUMB | `GetPanelItemHighlightPalette` | `src/overlays/ov001/auto/GetPanelItemHighlightPalette.c` | `u16 *(void)`. Returns the address of six item-highlight palette colors embedded at panel+0xf4. Boundary: Borrowed inline storage, not a newly allocated background or complete palette. No global NULL guard; do not free it or treat it as an entire resource. | SetPanelItemHighlight writes this array with RGB555 values0x001f/0x35ad and updates a separate bitmask. LoadMenuBackground copies exactly12 bytes from this getter into the unpacked palette at+0x1c2 before uploading SUB palette data. |
| ov001:0x0207b40c | THUMB | `SetPanelMapEntry` | `src/overlays/ov001/calls/SetPanelMapEntry.c` | `void(u32 resourceIndex, u32 entryId)`. Stores resource selection and entry ID at panel+0x50/+0x54; when the map is usable, immediately forwards them to PrepareMenuScreenEntry. Boundary: These are menu resource/entry selectors, not x/y coordinates. Store occurs even when the immediate map call is skipped. Original ROM proves the panel pointer is passed in r0 to the gate despite an empty-argument declaration. | The actual native gate0207a8fc requires loaded mode 0 and phase3,4or6. The mode table selects overlay23. PrepareMenuScreenEntry uses the first input to select one of eight resource files or its fallback and stores the second for FindChainEntryById. |
| ov001:0x0207b430 | THUMB | `RequestPanelMapReset` | `src/overlays/ov001/calls/RequestPanelMapReset.c` | `void(void)`. Stores reset sentinel-2 at panel+0x50 and immediately invokes ResetMapMenuScreen only when the mode 0 map gate permits. Boundary: The second selection word+0x54 is preserved. This can defer the reset until the map overlay is created; no completion result or automatic mode change is returned. | StartMenuOverlayWindow later consumes this same selection: sentinel-2 selects ResetMapMenuScreen, -1 skips entry setup, other values call PrepareMenuScreenEntry. ResetMapMenuScreen resets renderer slots/scroll state and queues its screen resource. |
| ov001:0x0207b4c4 | THUMB | `UpdatePanelMapRangePosition` | `src/overlays/ov001/calls/UpdatePanelMapRangePosition.c` | `void(s32 minimum, s32 maximum, s32 value)`. When loaded mode 0 and phase3/4/6 permit, forwards the range/value to the map position remapper. Boundary: No axis or gameplay units are asserted. The helper adds no clamp; a valid nonzero range denominator is a native precondition. Keep signed/fixed-point arithmetic and the additional map-word gate. | UpdateMenuRangePosition additionally requires map word+0x34 nonzero, then stores 0x21000 + FX_Div(FX_Mul(0xbe000,value-minimum),maximum-minimum) at map+0x7fa8. Camera-trigger and scene-record callers supply this three-value range. |
| ov001:0x0207b4e8 | THUMB | `MarkPanelMapTransformDirty` | `src/overlays/ov001/calls/MarkPanelMapTransformDirty.c` | `void(void)`. If the loaded mode 0 map gate permits, sets map+0x2c to 1 so its transform will be refreshed. Boundary: This requests refresh rather than uploading or redrawing synchronously. It does not alter the map entry, scale or center values itself. | RefreshScaledMenuScreen consumes that exact+0x2c flag: it writes the inverse-scale/center affine state through G2x_SetBGyAffine_, updates the sprite manager, then clears the flag. ResumeFieldFromPause is the adapter caller. |
| ov001:0x0207b520 | THUMB | `RequestTemporaryPanelListDisplay` | `src/overlays/ov001/calls/RequestTemporaryPanelListDisplay.c` | `void(void)`. Requests a temporary mode 2 list display: sets panel timer+0x100 to 1 if another mode is loaded; if mode 2 is already loaded, optionally advances its row when ready and sets timer2. Boundary: The timer is a u16 update counter, not a proved seconds duration. Timer2 is stored even when list readiness is0. Exact gameplay meaning of flag 0x3709/02064784 remains unassigned; preserve those side effects and failed-mode-request behavior. | UpdatePanelConfirmTimer treats timer1 as a request to enter mode 2. For timer>=2 it increments on updates and, at 0x71 or later, tries to return to mode 0or1 according to session state. The body also sets saved flag 0x3709 when02064784()==0 and that flag was clear. |
| ov001:0x0207b570 | THUMB | `ResetPanelListToFirstEntryIfReady` | `src/overlays/ov001/calls/ResetPanelListToFirstEntryIfReady.c` | `void(void)`. Only when loaded mode 2 and panel readiness+0x38 are nonzero, resets the embedded menu list to its first entry. Boundary: Readiness is the panel gate, not a busy==0 test. The underlying reset carries callbacks and scrolling effects; it is not just an index store. | The ov025 adapter passes work+0x64f4 to ResetListToFirstEntry; the body selects index 0, rebuilds the path, positions cells, clamps a scroll target and invokes onChange when present. ResetGaugeDisplay calls this adapter. |
| ov001:0x0207b5f4 | THUMB | `ReloadPanelListBgScreens` | `src/overlays/ov001/calls/ReloadPanelListBgScreens.c` | `void(void)`. When loaded mode 2, reloads the two menu-list tile screens into SUB BG2 and BG3. Boundary: No scale or affine transform is changed. The apparent third scale argument0x1000 is a byte count. This adapter does not additionally check panel readiness+0x38 or phase6. | The inherited ResetMenuLayerTransforms gets tile-table rows0x1a/0x1b and calls gSubBgScreenLoaders entries GXS_LoadBG2Scr/GXS_LoadBG3Scr with(source,offset0,size0x1000). The callee guards menu!=NULL and initialized word+0x64e4. |
| ov001:0x0207b654 | THUMB | `GetCachedPanelListDepthLimit` | `src/overlays/ov001/calls/GetCachedPanelListDepthLimit.c` | `u8(void)`. Returns panel cached byte+0x102, which initializes the mode 2 list depth limit. Boundary: This is not a language getter. It returns the cached selection-derived limit, which can differ temporarily from a live list override via0207b668. No NULL guard or gameplay level interpretation is established. | InitPanelScene caches GetPrimarySelectionByte1E there; UpdatePanelScene refreshes it when the primary selection value changes. InitMenuScreen passes it as ListViewConfig.mode to InitSlotListView, which stores list+0x7c. The path rebuild compares row/node depth-1 against that byte. |
| ov001:0x0207b668 | THUMB | `SetPanelListDepthLimitAndRefreshLabel` | `src/overlays/ov001/calls/SetPanelListDepthLimitAndRefreshLabel.c` | `void(u32 depthLimit)`. When mode 2 is loaded and panel readiness is nonzero, refreshes the list label, then updates the live list depth limit and rebuilds it. Boundary: Does not update panel cached byte+0x102. The label helper draws a value from manager+0x1334 with a text API; its inherited DrawNumberInPanelSlot name does not prove numeric formatting. Preserve narrowing, order and callbacks. | Original ROM confirms label refresh precedes the setter. The target ApplyModeAndNotify stores input low byte at list+0x7c, preserves path pointers for the rebuild and invokes optional onChange. Rebuild logic uses that byte to gate row/node depth. |
| ov001:0x0207b688 | THUMB | `GetPanelListPathNodeId` | `src/overlays/ov001/calls/GetPanelListPathNodeId.c` | `u32(u32 pathIndex)`. Returns the selected live list path node ID when mode 2 is loaded and ready, otherwise0xffff. Boundary: No path index or path-pointer guard is added by the real getter. Observed caller indices are zero-based. Node ID is distinct from parent/child row indices at node+6/+8. | The ov025 target reads u16 at list->path[pathIndex]+4, where path is the three-pointer array at list+0x70. SelectSlotTitleLine uses this ID to select a title table entry, falling back to saved IDs on0xffff. |
| ov001:0x0207b708 | THUMB | `GetPanelEntryName` | `src/overlays/ov001/calls/GetPanelEntryName.c` | `const u16 *(s32 index)`. Returns the indexed UTF-16 name pointer from the panel-owned pointer array at+0x110. Boundary: Borrowed allocated string, invalidated by panel teardown; no local bounds or NULL checks. The function returns an array element, not the address of a pointer slot. | BuildEntryNameList allocates the pointer array and individual UTF-16 copies from source records, storing count+0x10c. UpdateMenuScreen passes this getter to DrawTaggedTextWithFontFallback for a valid selected entry. FreeBufferArray releases each string and the array. |
| ov001:0x0207b764 | THUMB | `GetPanelSelectedRecordName` | `src/overlays/ov001/calls/GetPanelSelectedRecordName.c` | `const u16 *(void)`. Returns the copied selected-record name stored at panel+0x1c. Boundary: Borrowed allocation. Native cleanup does not clear the+0x1c field, so its nonzero value after release is not liveness evidence. No global NULL guard. | LoadModeNameAndMessages resolves the primary selection slot, allocates/copies its UTF-16 name or an empty two-unit fallback. DrawRemainingCountText passes this pointer as a string format argument. ReleaseSubscenePanelBuffers frees the name. |
| ov001:0x0207b770 | THUMB | `GetPanelMessageView` | `src/overlays/ov001/auto/GetPanelMessageView.c` | `const PackedResourceView *(void)`. Returns the embedded12-byte packed-message view at panel+0x20. Boundary: The view is inline, while its file field owns the loaded buffer. The accessor transfers neither ownership. ReleaseSubscenePanelBuffers releases the underlying file; it is not merely a getter for a pointer cell. | LoadModeNameAndMessages calls LoadPackedFileView on that exact address for resource key8. GetPackedFileEntry and FormatPackedWideText consume it; PackedResource.h establishes file/count/payload fields at 0/4/8. |
| ov001:0x0207b77c | THUMB | `TryStartPanelListScroll` | `src/overlays/ov001/calls/TryStartPanelListScroll.c` | `BOOL(void)`. If loaded mode is2 and panel phase is6, marks menu work+0x64f0 active and starts the embedded list scrolling toward-256; otherwise returns 0. Boundary: No entity is allocated or created. Return 1 means the request was issued, not animation completion. This gate uses phase6, not readiness+0x38. Keep the manager-active side effect, which suppresses later automatic counter reset. | ActivatePanelEntity sets+0x64f0 and ResetFieldsToDefault writes list scrollTarget+0x98=-256 and scrolling+0x9c=1. UpdateListScrollAnimation consumes those fields and moves current scroll toward target. Native ROM returns 1 after the call. |

## Counter HUD task work

The owner is `data_ov001_020a04ec`, task-owned work of 0x910 bytes.
Resources +8/+0x0c, embedded model initialization flags +0x108 and per-frame
draw flags +0x104 have separate lifetimes/roles. Constructors return update
callback pointers; their current-task accessor does not allocate. Releasing
nested resources or clearing the global does not free outer task work.
Accepted deltas are not universally seconds, and a successful delta request
can leave its accumulator unchanged during fade state 2.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0207b7e4 | THUMB | `LoadCounterHudResource` | `src/overlays/ov001/calls/LoadCounterHudResource.c` | `void(void **out, const char *resourceName)`. Formats a localized ui_btl resource path into a 32-byte buffer, opens its message container, and stores the returned handle. Boundary: Keep matching unused argument positions if required. The formatting buffer bound is 32 bytes; the helper does not prove successful loading. | InitCounterHudWork calls it for adnum and w resources, writing handles at +8 and +0xc. |
| ov001:0x0207b818 | THUMB | `InitCounterHudWork` | `src/overlays/ov001/calls/InitCounterHudWork.c` | `TaskUpdateFn(void)`. Retrieves current task work, clears 0x910 bytes, installs the global pointer, loads the two resources, sets +0xe8/+0xec to fixed-point positions and returns UpdateAndDrawCounterHud. Boundary: The surrounding task owns the 0x910-byte block. The returned value is a callback pointer, not a task result or allocated buffer. | GetRunningTaskWork is independently proved to return current task->work, not allocate a heap. CounterHud.h and UpdateAndDrawCounterHud consume this same layout. |
| ov001:0x0207b868 | THUMB | `ReleaseCounterHudWork` | `src/overlays/ov001/calls/ReleaseCounterHudWork.c` | `void(void)`. Releases the resource handles at +0xc then +8 through the pointer-clearing/freeing wrapper, then clears the global pointer. Boundary: Does not free the outer task work and does not replace the separate model cleanup helper. | The aliased NNS_SndPlayerPause_0207b80c delegates to ZeroHalfThenFree; this is not a sound pause operation. Paired resource acquisition is in InitCounterHudWork. |
| ov001:0x0207ba1c | THUMB | `DrawCounterHudDigitAtScaledOffset` | `src/overlays/ov001/calls/DrawCounterHudDigitAtScaledOffset.c` | `void(fx32 offset, fx32 scale, HudDigit *digit, u32 color)`. Draws the supplied digit texture at x = HUD baseX + FX_Mul(offset, scale), y = 0x13000 with the supplied scale and color. Boundary: The third argument is a record pointer, not a digit number. Preserve per-call fixed-point multiplication and position rounding. | DrawScaledTextureQuad consumes its third argument as a texture record pointer, with width, height and texture parameters; CounterHud digit records have the same layout. |
| ov001:0x0207d3ac | THUMB | `SetCounterHudEnabledIfActive` | `src/overlays/ov001/calls/SetCounterHudEnabledIfActive.c` | `BOOL(u32 value)`. When work exists and main state is nonzero, stores value to enabled +0xf0 and returns 1; otherwise returns 0. Boundary: The full raw input word is stored. The guard is nonzero state, not specifically state 1 or 3. | UpdateAndDrawCounterHud tests +0xf0 before invoking the counter and state callbacks. |
| ov001:0x0207d3cc | THUMB | `AccumulateCounterHudDelta` | `src/overlays/ov001/calls/AccumulateCounterHudDelta.c` | `BOOL(s32 delta)`. Accepts a nonzero delta only in main state 1 or 3. Adds it to +0x11c unless fade state +4 is 2, then returns 1. Boundary: A successful return can leave the accumulator unchanged in fade state 2. Do not label delta as seconds globally. | Counter HUD state handlers consume +0x11c; field timer update is a caller, but other value units are not proved. |
| ov001:0x0207d468 | THUMB | `SetCounterHudFadeEnabled` | `src/overlays/ov001/calls/SetCounterHudFadeEnabled.c` | `BOOL(u32 value)`. Stores the raw value at +0xf8 when HUD work exists and returns whether work exists. Boundary: Does not reset fade state, initialize models, or normalize the stored value. | UpdateAndDrawCounterHud checks the same word to run fade-state callbacks and suppress normal drawing via draw flag 0x80. |
| ov001:0x0207d680 | THUMB | `ReleaseCounterHudModels` | `src/overlays/ov001/calls/ReleaseCounterHudModels.c` | `void(void)`. Conditionally releases embedded models selected by init flags at +0x108, then clears enabled, fadeEnabled and init flags. Boundary: Preserve release order +0x808 before +0x704 for mask 0x80. Init flags +0x108 are separate from per-frame draw flags at +0x104. Resources +8/+0xc and outer work are not released here. | CounterHud.h places models at +0x1b8/+0x2bc/+0x3d8/+0x4dc/+0x600/+0x704/+0x808; corresponding masks are 2, 4, 0x10 and 0x80. |

## Arrow-prompt task work

The owner is `data_ov001_020a04f0`, task-owned work of 0x4c bytes.
Its full-prompt visible +4, timed update +8 and input-active +0x0c words are
independent. Start/finish/flash timestamps are frame counters; the timer updater
converts frame deltas to milliseconds using the established 30-fps counter.
The random helper deliberately consumes a range-10 draw before returning the
range-4 draw; removing the discarded call changes deterministic RNG state.
Queued transfer sources retain their required lifetime until consumption.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x0207d828 | THUMB | `QueueArrowPromptFlashTiles` | `src/overlays/ov001/calls/QueueArrowPromptFlashTiles.c` | `void(ArrowPrompt *prompt, const void *tiles)`. Queues a VRAM transfer with kind 7, destination 0x5400 and size 0x300, invokes record 0x134, then records the current frame counter at +0x14. Boundary: Do not reinterpret the frame counter as milliseconds. The queued transfer must retain appropriate source lifetime. | UpdateArrowPromptTimer treats +0x14 as flash start and closes record 0x134 after 500 ms using the 30 fps frame counter. |
| ov001:0x0207d860 | THUMB | `NextRandomArrowDirection` | `src/overlays/ov001/calls/NextRandomArrowDirection.c` | `u32(void)`. Performs a range-10 random draw and discards it, then returns the range-4 random draw in r0. Boundary: Inherited definition says void, but real caller and ROM prove a return value. Preserve the first discarded RNG call because it changes deterministic random state. | Original ROM disassembly saved in disasm_func_ov001_0207d860.txt shows r0 returned unchanged after the second call. OpenArrowPrompt consumes this return into directions[2]. |
| ov001:0x0207dc68 | THUMB | `InitArrowPromptWork` | `src/overlays/ov001/calls/InitArrowPromptWork.c` | `TaskUpdateFn(const u8 *paletteSource)`. Retrieves and clears current task work (0x4c), installs the global, loads BG characters/frames, copies two 0x20-byte palette blocks from source +0x1a0/+0x1c0 and returns UpdateBlinkPanel. Boundary: Source must cover the two palette blocks. The outer work is owned by the task. Existing callback name UpdateBlinkPanel is broader than this arrow prompt role. | OpenArrowPrompt, UpdateArrowPromptTimer and UpdateBlinkPanel all consume global data_ov001_020a04f0. GetRunningTaskWork does not allocate. |
| ov001:0x0207dcbc | THUMB | `ReleaseArrowPromptWork` | `src/overlays/ov001/calls/ReleaseArrowPromptWork.c` | `void(void)`. Frees buffers at work +0x30/+0x34/+0x38 and clears the global pointer. Boundary: No global NULL guard and no outer work free. Preserve all three free operations and their order. | InitArrowPromptWork allocates +0x30/+0x34; later prompt setup owns the optional third buffer at +0x38. All consumers share global data_ov001_020a04f0. |
| ov001:0x0207df6c | THUMB | `StartArrowPromptTimedCounters` | `src/overlays/ov001/calls/StartArrowPromptTimedCounters.c` | `void(u32 timeLimitMs, u8 secondCounter)`. Clears displayed first counter, stores the second counter byte, captures start frame, clears finish frame, stores time limit, opens record 0x12e, renders the counters and enables timed updates at +8. Boundary: The second argument is a counter byte, not a BOOL flag. This does not enable the full arrow prompt visible flag at +4. | ShowTwoDigitCounters renders the first two bytes as independent decimal counters. UpdateArrowPromptTimer converts frame deltas to milliseconds before comparing time limit +0x1c. |
| ov001:0x0207dfb4 | THUMB | `HideArrowPromptTimedCounters` | `src/overlays/ov001/calls/HideArrowPromptTimedCounters.c` | `void(void)`. Clears timed update flag +8, clears a 4x2 tile region on layer 0xb at (0xe,0), then closes records 0x134 and 0x12e. Boundary: Does not clear full prompt visible +4 or input-active +0xc; do not use as a complete prompt destructor. | UpdateBlinkPanel uses +8 for timer-only updates when full prompt visibility +4 is zero. The paired starter is 0207df6c. |

## HUD gauge blink state

This getter uses `data_ov001_020a04cc`, not CounterHud +04ec or the
later HUD-node owner +04f4. Its indexed 24-byte blink record is distinct from
the displayed gauge current/maximum fields. The returned active word is raw,
not normalized.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x02075248 | THUMB | `GetHudGaugeBlinkActive` | `src/overlays/ov001/calls/GetHudGaugeBlinkActive.c` | `u32(int index)`. Returns the raw active word of the indexed HUD gauge blink animation at global04cc+0x6c+index*0x18+0x10. Boundary: No NULL or index check; do not confuse with displayed gauge current/maximum at +0xb4, or CounterHud global04ec. The getter does not normalize its returned word. | SetMenuGaugeActive writes active1/0 and initializes timing for this exact 24-byte record. AdvanceGaugeSlot toggles its frame/phase at an interval and redraws filled cells in modes0/2. Expr021b0b0c reads index 0 as a tagged scalar. |

## Session script-entry gate

This gate belongs to the installed session callback protocol. It combines an
optional slot-7 callback with the separate actor-entry-0 flag policy. A missing
slot-7 callback does not block. Passing this one gate does not prove every
session resource is ready or every stored task is live.

| EU identity | Mode | Name | New EU source | Contract and native boundary | Writer/caller/consumer evidence |
|---|---|---|---|---|---|
| ov001:0x02062c64 | THUMB | `IsSessionScriptEntryReady` | `src/overlays/ov001/calls/IsSessionScriptEntryReady.c` | `BOOL(void)`. Requires an optional session slot 7 readiness callback to return nonzero and requires actor entry0 flag 2 to be inactive. A missing readiness callback does not block. Boundary: This is one script-entry gate, not proof of all session readiness or a live task. Preserve absent-callback behavior and the separate actor-entry gate. | TryRaiseSessionScriptFlags calls it before raising script run flag 0x80. SelectNextSessionState also requires it on the IsSessionLinked path before choosing next state 7. IsEntryFlag2Active resolves the entry callback and applies saved flag 0x3525 policy. |

## Evidence paths rechecked beyond the candidate bodies

The listed bodies and their EU aliases establish each candidate.
Additional producer/consumer sources include:

- `src/overlays/ov001/calls/Actor_InstallNodeStateCallback.c`: registers the
  one-input 3D callback for SBC command 6/timing 3, with render-object user data.
- `src/overlays/ov001/calls/UpdateStageEvent.c` and
  `src/overlays/ov001/data/tables/gStageScriptStateHandlers.c`: same-owner word-0
  handler dispatch and nonzero-result state change, with EU table at 0x020a0298.
- `src/overlays/ov001/calls/IsPanelMapUpdateAllowed.c`: native map gate is loaded
  mode 0 and phase 3/4/6, rather than the list's loaded mode 2.
- `src/overlays/ov023/calls/LoadMenuBackground.c`: copies exactly 12 bytes from
  the highlight palette getter into palette offset +0x1c2 before upload.
- `src/overlays/ov025/calls/ResetMenuLayerTransforms.c` and
  `src/overlays/ov025/data/tables/gSubBgScreenLoaders.c`: screen sources and
  BG2/BG3 copy callbacks; no affine transform or scale operation in that path.
- `libs/nitro/nns/calls/GetRunningTaskWork.c`: returns the current task's existing
  work, establishing constructor/cleanup ownership without a heap allocation.

Native disassemblies retained with the research also establish saved pool/parent
indices, pointer/BOOL callback returns, the single SBC input, two RNG calls,
caption R0 forwarding and exact field-effect task/list operations. Ghidra's
imported prototype is not used to override a contradictory caller or instruction
return sequence. Logical type repairs remain separate validated changes.

## Remaining evidence boundaries

At the preceding published checkpoint `00280f0886`, the original 1,583-identity
review separated 636 published names, 587 supported proposals awaiting
integration and 360 semantic holds. This block integrates 135 supported proposals,
including 15 older holds closed by later writer/consumer evidence. An old hold
list is not the current semantic status. Overlay015 proposals are reviewed and
validated separately; no name in this block belongs to that overlay.

The remaining holds require concrete callback registrations/return consumers,
same-owner field writers, lifetime evidence, state/flag transitions or associated
DATA formats. A byte-exact match alone does not establish these meanings.

## Reproducible byte-exact validation

Run the existing tools from `eu/` with the native modes shown:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldObjectPositionPlusOffset.c SetFieldObjectPositionPlusOffset --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DisableTargetViewForSavedFlag.c DisableTargetViewForSavedFlag --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawProjectionViewFieldObject.c DrawProjectionViewFieldObject --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldObjectActorSlotFlag8.c GetFieldObjectActorSlotFlag8 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReloadFirstType11FieldObjectModels.c ReloadFirstType11FieldObjectModels --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFirstType11FieldObjectModels.c ReleaseFirstType11FieldObjectModels --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldObjectDataAndShape.c ReleaseFieldObjectDataAndShape --thumb
python tools/verify_idx.py src/overlays/ov001/calls/CreateSpawnerFieldObject.c CreateSpawnerFieldObject --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldObjectTouchHandler.c ReleaseFieldObjectTouchHandler --thumb
python tools/verify_idx.py src/overlays/ov001/calls/BuildXyzRotationMatrix33.c BuildXyzRotationMatrix33 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ApplyPartRotationAndCaptureNodeCallback.c ApplyPartRotationAndCaptureNodeCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetActorVelocityAndExtraSlots.c ResetActorVelocityAndExtraSlots --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdateFieldCameraPoseTween.c UpdateFieldCameraPoseTween --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdateFieldCameraHeadingTween.c UpdateFieldCameraHeadingTween --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetStageResourceNameByIndex.c GetStageResourceNameByIndex --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetStageListFirstOrNull.c GetStageListFirstOrNull --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetStageListNext.c GetStageListNext --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetStageActorPosition.c GetStageActorPosition --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ScriptCmd_SpawnFieldObjectTree.c ScriptCmd_SpawnFieldObjectTree --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ReadFieldObjectSpawnExtraVector.c ReadFieldObjectSpawnExtraVector --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ScriptCmd_SpawnFieldObjectTreeWithExtraVector.c ScriptCmd_SpawnFieldObjectTreeWithExtraVector --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ScriptCmd_SetFieldObjectFlag22.c ScriptCmd_SetFieldObjectFlag22 --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ScriptCmd_FreeFieldResourceCache.c ScriptCmd_FreeFieldResourceCache --thumb
python tools/verify_idx.py src/overlays/ov016/calls/UpdateFieldObjectDrawFlagFromPreviousLink.c UpdateFieldObjectDrawFlagFromPreviousLink --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ReinsertFieldObjectActorInQuadTree.c ReinsertFieldObjectActorInQuadTree --thumb
python tools/verify_idx.py src/overlays/ov016/calls/BuildFieldObjectBoxCollision.c BuildFieldObjectBoxCollision --thumb
python tools/verify_idx.py src/overlays/ov016/calls/SetFieldObjectActorEnabled.c SetFieldObjectActorEnabled --thumb
python tools/verify_idx.py src/overlays/ov016/calls/FinishFieldObjectAndMaybeGrantReward.c FinishFieldObjectAndMaybeGrantReward --thumb
python tools/verify_idx.py src/overlays/ov016/calls/InitFieldObjectNode8AnimTrack.c InitFieldObjectNode8AnimTrack --thumb
python tools/verify_idx.py src/overlays/ov016/calls/UpdateFieldObjectAuxAnimTrack.c UpdateFieldObjectAuxAnimTrack --thumb
python tools/verify_idx.py src/overlays/ov016/calls/StartFieldObjectActorAnimation1.c StartFieldObjectActorAnimation1 --thumb
python tools/verify_idx.py src/overlays/ov016/calls/UpdateFieldObjectActorAnimation.c UpdateFieldObjectActorAnimation --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ScaleFieldObjectVelocityBy85Percent.c ScaleFieldObjectVelocityBy85Percent --thumb
python tools/verify_idx.py src/overlays/ov016/calls/SetFieldObjectCompletionCallback.c SetFieldObjectCompletionCallback --thumb
python tools/verify_idx.py src/overlays/ov016/auto/GetFieldObjectHiddenMask.c GetFieldObjectHiddenMask --thumb
python tools/verify_idx.py src/overlays/ov016/calls/DispatchIndexedFieldObjectCollision.c DispatchIndexedFieldObjectCollision --thumb
python tools/verify_idx.py src/overlays/ov016/calls/ApplyIndexedFieldGroupLeaderHit.c ApplyIndexedFieldGroupLeaderHit --thumb
python tools/verify_idx.py src/overlays/ov017/calls/DrawGridObjectActorQuads.c DrawGridObjectActorQuads --thumb
python tools/verify_idx.py src/overlays/ov017/calls/UpdateGridObjectDropOffsetFromRay.c UpdateGridObjectDropOffsetFromRay --thumb
python tools/verify_idx.py src/overlays/ov017/calls/DiscardKind4MessageNodesKeepingPinned.c DiscardKind4MessageNodesKeepingPinned --thumb
python tools/verify_idx.py src/overlays/ov017/calls/FindLastInactiveObjectInParentChain.c FindLastInactiveObjectInParentChain --thumb
python tools/verify_idx.py src/overlays/ov017/calls/PropagateStackHeightWrapper.c PropagateStackHeightWrapper --thumb
python tools/verify_idx.py src/overlays/ov017/calls/SyncKind7ActorFlagToActiveState.c SyncKind7ActorFlagToActiveState --thumb
python tools/verify_idx.py src/overlays/ov017/calls/FindLastInactiveObjectInParentChainWrapper.c FindLastInactiveObjectInParentChainWrapper --thumb
python tools/verify_idx.py src/overlays/ov017/calls/FindRootObjectWrapper.c FindRootObjectWrapper --thumb
python tools/verify_idx.py src/overlays/ov018/calls/ReleaseKind6ObjectAttachment.c ReleaseKind6ObjectAttachment --thumb
python tools/verify_idx.py src/overlays/ov018/calls/ReleaseKind6ObjectChannelAndResources.c ReleaseKind6ObjectChannelAndResources --thumb
python tools/verify_idx.py src/overlays/ov019/calls/SettleLinkHeightAtZeroOffset.c SettleLinkHeightAtZeroOffset --thumb
python tools/verify_idx.py src/overlays/ov020/calls/ScriptCmd_SpawnPanelBlock.c ScriptCmd_SpawnPanelBlock --thumb
python tools/verify_idx.py src/overlays/ov020/calls/FindLastLiveBlockInPreviousChain.c FindLastLiveBlockInPreviousChain
python tools/verify_idx.py src/overlays/ov020/calls/SettleBlockGroundWrapper.c SettleBlockGroundWrapper
python tools/verify_idx.py src/overlays/ov020/calls/DrawPanelBlockVisibleParts.c DrawPanelBlockVisibleParts
python tools/verify_idx.py src/overlays/ov001/calls/QueueStage900AndSaveLeaderPlacement.c QueueStage900AndSaveLeaderPlacement --thumb
python tools/verify_idx.py src/overlays/ov001/calls/QueueFieldFromSavedSceneIds.c QueueFieldFromSavedSceneIds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/QueueSavedFieldAndClearFlag14.c QueueSavedFieldAndClearFlag14 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_QueueStage900AndSavePlacement.c ScriptCmd_QueueStage900AndSavePlacement --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_QueueFieldFromSavedSceneIds.c ScriptCmd_QueueFieldFromSavedSceneIds --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_UnpauseFieldEntriesIfFlag20Clear.c ScriptCmd_UnpauseFieldEntriesIfFlag20Clear --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ReleaseOrDisableStageEvent.c ScriptCmd_ReleaseOrDisableStageEvent --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseOrDisableStageEvent.c ReleaseOrDisableStageEvent --thumb
python tools/verify_idx.py src/overlays/ov001/calls/EnsureFieldEffectPool.c EnsureFieldEffectPool --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroyFieldEffectPool.c DestroyFieldEffectPool --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TrySpawnFieldEffect.c TrySpawnFieldEffect --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldEffectSlot.c ReleaseFieldEffectSlot --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HasActiveFieldEffects.c HasActiveFieldEffects --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_EnsureFieldEffectPool.c ScriptCmd_EnsureFieldEffectPool --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_WaitForFieldEffectsThenSuspend.c ScriptCmd_WaitForFieldEffectsThenSuspend --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroySceneEntryContext.c DestroySceneEntryContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseAllSceneSlotResources.c ReleaseAllSceneSlotResources --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetSceneSlotDrawingEnabled.c SetSceneSlotDrawingEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetSceneSlotDrawingEnabled.c ScriptCmd_SetSceneSlotDrawingEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetCurrentSceneEntryIndex.c GetCurrentSceneEntryIndex --thumb
python tools/verify_idx.py src/overlays/ov006/calls/ScriptCmd_CreateElevatorClass.c ScriptCmd_CreateElevatorClass --thumb
python tools/verify_idx.py src/overlays/ov006/calls/ScriptCmd_CreateElevatorObject.c ScriptCmd_CreateElevatorObject --thumb
python tools/verify_idx.py src/overlays/ov006/calls/RestartElevatorStateAnimation.c RestartElevatorStateAnimation --thumb
python tools/verify_idx.py src/overlays/ov006/auto/GetElevatorObjectPosition.c GetElevatorObjectPosition --thumb
python tools/verify_idx.py src/overlays/ov006/calls/GetElevatorCenterIfEnabled.c GetElevatorCenterIfEnabled --thumb
python tools/verify_idx.py src/overlays/ov006/auto/GetGridRowMajorIndex.c GetGridRowMajorIndex --thumb
python tools/verify_idx.py src/overlays/ov006/auto/GetFieldGridCellValue.c GetFieldGridCellValue --thumb
python tools/verify_idx.py src/overlays/ov007/calls/ScriptCmd_CommitSideResult.c ScriptCmd_CommitSideResult --thumb
python tools/verify_idx.py src/overlays/ov007/calls/ShowCurrentSceneEntryCaptionAndSetFlag2.c ShowCurrentSceneEntryCaptionAndSetFlag2
python tools/verify_idx.py src/overlays/ov007/auto/GetWanderActorPosition.c GetWanderActorPosition
python tools/verify_idx.py src/overlays/ov007/calls/GetEventTargetLayerAndChannel.c GetEventTargetLayerAndChannel --thumb
python tools/verify_idx.py src/overlays/ov007/calls/EvaluateSceneEntryFlag40Trigger.c EvaluateSceneEntryFlag40Trigger --thumb
python tools/verify_idx.py src/overlays/ov010/calls/EnterSpecialActionState2.c EnterSpecialActionState2 --thumb
python tools/verify_idx.py src/overlays/ov010/calls/ResetSpecialActionState.c ResetSpecialActionState --thumb
python tools/verify_idx.py src/overlays/ov010/calls/InitSpecialActionWork.c InitSpecialActionWork --thumb
python tools/verify_idx.py src/overlays/ov010/calls/IsSpecialActionStateNonzero.c IsSpecialActionStateNonzero --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSubsceneTextOrEmpty.c GetSubsceneTextOrEmpty --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetLoadedSubsceneMode.c GetLoadedSubsceneMode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSubsceneSlotValue.c GetSubsceneSlotValue --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSubsceneTaskObject.c GetSubsceneTaskObject --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetSubsceneReadyValue.c GetSubsceneReadyValue --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsSubscenePanelState6.c IsSubscenePanelState6 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestSubsceneMode0Or1FromMode4.c RequestSubsceneMode0Or1FromMode4 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/LoadCounterHudResource.c LoadCounterHudResource --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitCounterHudWork.c InitCounterHudWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseCounterHudWork.c ReleaseCounterHudWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawCounterHudDigitAtScaledOffset.c DrawCounterHudDigitAtScaledOffset --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetCounterHudEnabledIfActive.c SetCounterHudEnabledIfActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AccumulateCounterHudDelta.c AccumulateCounterHudDelta --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetCounterHudFadeEnabled.c SetCounterHudFadeEnabled --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseCounterHudModels.c ReleaseCounterHudModels --thumb
python tools/verify_idx.py src/overlays/ov001/calls/QueueArrowPromptFlashTiles.c QueueArrowPromptFlashTiles --thumb
python tools/verify_idx.py src/overlays/ov001/calls/NextRandomArrowDirection.c NextRandomArrowDirection --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitArrowPromptWork.c InitArrowPromptWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseArrowPromptWork.c ReleaseArrowPromptWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StartArrowPromptTimedCounters.c StartArrowPromptTimedCounters --thumb
python tools/verify_idx.py src/overlays/ov001/calls/HideArrowPromptTimedCounters.c HideArrowPromptTimedCounters --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsSessionScriptEntryReady.c IsSessionScriptEntryReady --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetHudGaugeBlinkActive.c GetHudGaugeBlinkActive --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldObjectInteractionsBlocked.c SetFieldObjectInteractionsBlocked --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldObjectInteractionBlockMask.c GetFieldObjectInteractionBlockMask --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IsActorScriptWaitSatisfied.c IsActorScriptWaitSatisfied --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageEventHandlerState.c SetStageEventHandlerState --thumb
python tools/verify_idx.py src/overlays/ov001/auto/SetStageControllerUniformScale.c SetStageControllerUniformScale --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DispatchFieldObjectTouchCommandAndUnlinkHandler.c DispatchFieldObjectTouchCommandAndUnlinkHandler --thumb
python tools/verify_idx.py src/overlays/ov001/auto/SetSubsceneBgSetupCallback.c SetSubsceneBgSetupCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetPanelFormationType.c GetPanelFormationType --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetPanelInputActive.c GetPanelInputActive --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetPanelItemHighlightPalette.c GetPanelItemHighlightPalette --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetPanelMapEntry.c SetPanelMapEntry --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestPanelMapReset.c RequestPanelMapReset --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdatePanelMapRangePosition.c UpdatePanelMapRangePosition --thumb
python tools/verify_idx.py src/overlays/ov001/calls/MarkPanelMapTransformDirty.c MarkPanelMapTransformDirty --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RequestTemporaryPanelListDisplay.c RequestTemporaryPanelListDisplay --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetPanelListToFirstEntryIfReady.c ResetPanelListToFirstEntryIfReady --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReloadPanelListBgScreens.c ReloadPanelListBgScreens --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetCachedPanelListDepthLimit.c GetCachedPanelListDepthLimit --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetPanelListDepthLimitAndRefreshLabel.c SetPanelListDepthLimitAndRefreshLabel --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetPanelListPathNodeId.c GetPanelListPathNodeId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetPanelEntryName.c GetPanelEntryName --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetPanelSelectedRecordName.c GetPanelSelectedRecordName --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetPanelMessageView.c GetPanelMessageView --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryStartPanelListScroll.c TryStartPanelListScroll --thumb
bash tools/gate.sh
python tools/test_rename_symbol.py -v
```

All 135 official function checks pass. The fresh gate passes all 108 linked
modules; affected function bytes, resolved relocation targets/types and addends,
and all module hashes match the preserved baseline. Fourteen renamer regression
tests cover the existing scope, C/C++/BOM handling and batch preflight failures.
Batch mode validates all symbols and destinations before writing, and reads each
source/library/config file once. Shared-region aliases retain their existing
interpretation; no native verifier or matching policy is changed.
