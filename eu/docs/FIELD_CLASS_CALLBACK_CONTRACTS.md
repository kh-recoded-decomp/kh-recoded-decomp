# Field-object class callbacks and state handlers (ov007-011)

These 29 EU names follow owner constructors, native dispatch and actual
consumers. Existing prototypes, registered hooks and raw results are preserved.
Original identities distinguish overlays sharing native RAM addresses.

## Identity table

EU compilation sources are relative to `eu/`; evidence paths are relative to repository root. For a shared source, the EU wrapper aliases determine the actual callee and identity.

| EU identity/mode | Proposed name | EU source | Evidence source |
|---|---|---|---|
| ov007:020a0680 thumb | `ScriptCmd_SetAreaSceneDefinitionParams` | `src/overlays/ov007/calls/ScriptCmd_SetAreaSceneDefinitionParams.c` | `eu/src/overlays/ov007/data/tables/gFieldActorScriptCommandHandlers.c` |
| ov007:020a0894 thumb | `ScriptCmd_ResetAreaSceneSelectionFlags` | `src/overlays/ov007/calls/ScriptCmd_ResetAreaSceneSelectionFlags.c` | `eu/src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c` |
| ov008:020a0948 thumb | `ChildSpawner_GetPosition` | `src/overlays/ov008/auto/ChildSpawner_GetPosition.c` | `eu/src/overlays/ov008/calls/CreateChildSpawnerObject.c` |
| ov008:020a0974 thumb | `ChildSpawner_ApplyHitTrue` | `src/overlays/ov008/auto/ChildSpawner_ApplyHitTrue.c` | `eu/src/overlays/ov008/calls/CreateChildSpawnerClass.c` |
| ov008:020a0978 thumb | `ChildSpawner_QueryHitFalse` | `src/overlays/ov008/auto/ChildSpawner_QueryHitFalse.c` | `eu/src/overlays/ov008/calls/CreateChildSpawnerClass.c` |
| ov008:020a0d70 thumb | `DelayedGimmick_OnEnabledChangedNoop` | `src/overlays/ov008/auto/DelayedGimmick_OnEnabledChangedNoop.c` | `eu/src/overlays/ov008/calls/CreateGimmickClass.c` |
| ov008:020a0d74 thumb | `DelayedGimmick_GetPosition` | `src/overlays/ov008/auto/DelayedGimmick_GetPosition.c` | `eu/src/overlays/ov008/calls/CreateDelayedGimmickObject.c` |
| ov008:020a0da0 thumb | `DelayedGimmick_GetClassHitResult` | `src/overlays/ov008/auto/DelayedGimmick_GetClassHitResult.c` | `eu/src/overlays/ov008/calls/CreateGimmickClass.c` |
| ov008:020a0da8 thumb | `DelayedGimmick_QueryHitFalse` | `src/overlays/ov008/auto/DelayedGimmick_QueryHitFalse.c` | `eu/src/overlays/ov008/calls/CreateGimmickClass.c` |
| ov009:020a0908 thumb | `SwitchObject_OnEnabledChangedNoop` | `src/overlays/ov009/auto/SwitchObject_OnEnabledChangedNoop.c` | `eu/src/overlays/ov009/calls/FieldObjectClass_Create.c` |
| ov009:020a096c thumb | `SwitchObject_QueryHitFalse` | `src/overlays/ov009/auto/SwitchObject_QueryHitFalse.c` | `eu/src/overlays/ov009/calls/FieldObjectClass_Create.c` |
| ov009:020a0ab0 thumb | `SwitchObject_UpdateFallAndProximityChannel` | `src/overlays/ov009/calls/SwitchObject_UpdateFallAndProximityChannel.c` | `eu/src/overlays/ov009/calls/FieldObject_SetSwitchState.c` |
| ov009:020a0ad8 thumb | `SwitchObject_UpdateFallInState1` | `src/overlays/ov009/calls/SwitchObject_UpdateFallInState1.c` | `eu/src/overlays/ov009/calls/FieldObject_SetSwitchState.c` |
| ov009:020a0ae4 thumb | `SwitchObject_UpdateFallInState2` | `src/overlays/ov009/calls/SwitchObject_UpdateFallInState2.c` | `eu/src/overlays/ov009/calls/FieldObject_SetSwitchState.c` |
| ov009:020a0c3c thumb | `SetSwitchObjectStateForwarder` | `src/overlays/ov009/calls/SetSwitchObjectStateForwarder.c` | `src/ov009/shared_engine/ScriptCmd_SetObjectElementState_020a05f8.c` |
| ov010:020a07b4 thumb | `ShapedObject_OnEnabledChangedNoop` | `src/overlays/ov010/auto/ShapedObject_OnEnabledChangedNoop.c` | `eu/src/overlays/ov010/calls/FieldObjectClass_CreateShaped.c` |
| ov010:020a07b8 thumb | `ShapedObject_GetPosition` | `src/overlays/ov010/auto/ShapedObject_GetPosition.c` | `eu/src/overlays/ov010/calls/FieldObject_CreateWithShape_020a0958.c` |
| ov010:020a0828 thumb | `ShapedObject_GetClassHitResult` | `src/overlays/ov010/auto/ShapedObject_GetClassHitResult.c` | `eu/src/overlays/ov010/calls/FieldObjectClass_CreateShaped.c` |
| ov010:020a0830 thumb | `ShapedObject_QueryHitFalse` | `src/overlays/ov010/auto/ShapedObject_QueryHitFalse.c` | `eu/src/overlays/ov010/calls/FieldObjectClass_CreateShaped.c` |
| ov010:020a0a84 thumb | `FrontViewObject_OnEnabledChangedNoop` | `src/overlays/ov010/auto/FrontViewObject_OnEnabledChangedNoop.c` | `eu/src/overlays/ov010/calls/FieldObjectClass_CreateFrontView.c` |
| ov010:020a0a88 thumb | `FrontViewObject_GetPosition` | `src/overlays/ov010/auto/FrontViewObject_GetPosition.c` | `eu/src/overlays/ov010/calls/FieldObject_CreateAtOrigin.c` |
| ov010:020a0a8c thumb | `FrontViewObject_SetPositionNoop` | `src/overlays/ov010/auto/FrontViewObject_SetPositionNoop.c` | `src/ov001/scripted_actor_behavior/ScriptOp_CallObjectVectorHook_02080368.c` |
| ov010:020a0a90 thumb | `FrontViewObject_GetClassHitResult` | `src/overlays/ov010/auto/FrontViewObject_GetClassHitResult.c` | `eu/src/overlays/ov010/calls/FieldObjectClass_CreateFrontView.c` |
| ov010:020a0a98 thumb | `FrontViewObject_QueryHitFalse` | `src/overlays/ov010/auto/FrontViewObject_QueryHitFalse.c` | `eu/src/overlays/ov010/calls/FieldObjectClass_CreateFrontView.c` |
| ov011:020a096c thumb | `SpawnObject_OnEnabledChangedNoop` | `src/overlays/ov011/auto/SpawnObject_OnEnabledChangedNoop.c` | `src/ov011/field_objects/FieldObject_Create_020a0fa4.c` |
| ov011:020a0970 thumb | `SpawnObject_GetPosition` | `src/overlays/ov011/auto/SpawnObject_GetPosition.c` | `src/ov011/field_objects/FieldObject_CreateAt_020a1054.c` |
| ov011:020a0ee8 thumb | `SpawnObject_BeforeSpawnUpdateZero` | `src/overlays/ov011/auto/SpawnObject_BeforeSpawnUpdateZero.c` | `eu/src/overlays/ov011/calls/FieldObject_SetState.c` |
| ov011:020a0f18 thumb | `SpawnObject_AfterSpawnAnimationUpdateZero` | `src/overlays/ov011/auto/SpawnObject_AfterSpawnAnimationUpdateZero.c` | `eu/src/overlays/ov011/calls/FieldObject_SetState.c` |
| ov011:020a0fc0 thumb | `SpawnObject_GetTargetPosition` | `src/overlays/ov011/auto/SpawnObject_GetTargetPosition.c` | `src/ov011/field_objects/FieldObject_Create_020a0fa4.c` |

## Owners, fields and lifetime

These objects store their class pointer at object+8 and a borrowed VecFx32 position at object+0x40. Constructors write that same position. The class callback offsets below belong to this interface; they must not be copied onto EntryPool objects, whose owner is at +4 and position at +0x38.

| Owner | Class/entry size | Constructor evidence |
|---|---|---|
| ChildSpawner | 0x88 / 0x2a8 | `CreateChildSpawnerClass`; `CreateChildSpawnerObject` initializes 24 child slots |
| DelayedGimmick | 0x84 / 0x78 | `CreateGimmickClass`; factory initializes phase, delay timer, duration and open offset |
| SwitchObject | 0x84 / 0x60 | `FieldObjectClass_Create`; state handler selected by `FieldObject_SetSwitchState` |
| ShapedObject | 0x88 / 0x58 | `FieldObjectClass_CreateShaped` takes native kind/shape/size/value parameters |
| FrontViewObject | 0x84 / 0x5c | `FieldObjectClass_CreateFrontView`; constructor registers extra draw and no-op vector setter |
| SpawnObject (ov011) | 0x18c / 0x68 | `FieldObject_Create_020a0fc4` creates the class; `FieldObject_CreateAt` initializes per-object command/state fields |

The getter result `object+0x40` is an interior pointer owned by the object. No allocation or transfer occurs. The class+0x50 scalar read by hit-result callbacks is distinct from object+0x50, which belongs to packed save-bit fields in this family. Private legacy names such as archive/heap/file command, onTouch and _fp_init are not semantic evidence.

## Dispatch ABI and returned values

| Class offset | Reader and real contract | Limits |
|---|---|---|
| +0x20 | `FieldObject_SetEnabled`: hook(object,enabled) after transition work | The empty hook does not cancel packed-bit or world-registration changes. Incoming R0 survives an empty BX LR. |
| +0x24 | `CallFieldObjectHook24`; vector VM command passes `(object,&VecFx32)` | FrontView hook does no work; other owner setters are independent. |
| +0x28 | `FieldObject_GetPosition`: callback(object), borrowed VecFx32* | No null/ownership promise beyond the dispatcher behavior. |
| +0x2c | `FieldObject_ApplyHit`: guarded `(object,message)` -> raw u32 | ChildSpawner returns1; delayed/shaped/front-view return class+0x50. No damage/handled bit interpretation asserted. |
| +0x30 | `FieldObject_QueryHit`: guarded `(object,shape,contact)` -> BOOL | Listed literal-FALSE leaves do not write contact and do not prove absence of other collision geometry. |
| +0x34 | `CallFieldObjectHook13IfPresent`: callback(object) or0 | Target consumers read a borrowed VecFx32*. Distinct from the +0x28 registration and its guard. |

The source plan only renames functions and paths. It does not silently replace legacy declarations with guessed prototypes or merge identical functions. A logical void hook may preserve a native register word; that alone does not create a fluent API.

Switch state handlers are installed explicitly at object+0x14: state 0 updates fall and may trigger channel(0,1,0), while states1 and2 each run the same fall worker and return0. Their addresses remain separate. The scalar0 is not interpreted as completion or failure. The state setter also accepts2 from respawn logic; the VM forwarder only supplies a normalized0/1 operand.

The switch forwarder is a literal-pool interworking thunk: `LDR R3; BX R3; .word 0x020a0654`, where the target is the ARM state setter. It preserves object/state in R0/R1. Decoding its literal as Thumb instructions would be misleading.

SpawnObject state 0 precedes BeginSpawn. State1 runs the nonempty animation updater; that updater can set state 2 using the exact frame-plus-0x1000 equality. The proposed before/after callbacks themselves return literal 0 without work. The names do not infer an idle, done or task-destruction contract.

## Script commands

The ov007 VM table uses alternating handler/metadata words. The two reviewed commands occupy physical words8 and22. SetAreaSceneDefinitionParams evaluates three integer operands and delegates to native u8/u16/u16 stores; ResetAreaSceneSelectionFlags still evaluates its one operand even though the worker ignores it. Both return literal 1. Do not remove that operand evaluation when porting: VM resolution may have effects.

## Per-function evidence and limits

### `ScriptCmd_SetAreaSceneDefinitionParams`

VM table physical word8 reads three 8-byte integer operands in order and delegates to SetAreaSceneDefinitionParams(mode,width,height), then returns literal 1. The worker stores u8 mode+1e and u16 dimensions+46/+48.

Keep operand evaluation/order and native worker narrowing. No new parameters or validation. It is unrelated to the same raw RAM pointer in bank010.

### `ScriptCmd_ResetAreaSceneSelectionFlags`

VM table physical word22 evaluates one integer operand, calls ResetAreaSceneSelectionFlags, and returns literal 1. Worker clears packed bits3702/379b/3723/3724 and writes10bits3791=0.

Decoded integer is still evaluated/passed in native R0, but the worker uses no argument; do not invent an area index or phase parameter.

### `ChildSpawner_GetPosition`

Returns object+40h, the VecFx32 position initialized by the exact owner factory. Constructor registers this function in class+28h; FieldObject_GetPosition invokes it as callback(object).

Borrowed interior pointer; no allocation, null guard or ownership transfer. Do not confuse object+40h with an actor model position or with the separate class+34h callback.

### `ChildSpawner_ApplyHitTrue`

Child-spawner constructor installs literal 1 callback in class+2ch, the guarded FieldObject_ApplyHit(object,message) raw-u32 result slot.

No hit message or input is read. Preserve1 without interpreting handled/damage/stop semantics; this is not an SDK DefaultStepDone function.

### `ChildSpawner_QueryHitFalse`

Constructor installs this literal-FALSE callback in class+30h. FieldObject_QueryHit calls(object,shape,contact) only after its IsObjectFlagClear guard, and forwards the BOOL.

Reads no input or contact output, changes no memory. This rejects this query callback; it does not prove the owner has no geometry or all collision disabled.

### `DelayedGimmick_OnEnabledChangedNoop`

Exact owner constructor registers the empty hook in class+20h. FieldObject_SetEnabled calls it as(object,enabled) after a real enabled transition, packed save-bit write and conditional actor/world registration.

Not touch/idle/FP initialization despite legacy labels. Empty hook preserves native R0 and does not cancel common enabled-state side effects. Separate from EntryPool+18h.

### `DelayedGimmick_GetPosition`

Returns object+40h, the VecFx32 position initialized by the exact owner factory. Constructor registers this function in class+28h; FieldObject_GetPosition invokes it as callback(object).

Borrowed interior pointer; no allocation, null guard or ownership transfer. Do not confuse object+40h with an actor model position or with the separate class+34h callback.

### `DelayedGimmick_GetClassHitResult`

Registered class+2ch callback returns the raw 32-bit word at object->class(+8)->word50h. Actual FieldObject_ApplyHit supplies(object,message); leaf ignores the message. Constructors set the word to0, shaped params.value, and10h respectively.

Scalar hit result, not an archive/file pointer or owned object. No interpretation of its bits or normalization to BOOL. +50h is a class field here, not the object save-bit offset.

### `DelayedGimmick_QueryHitFalse`

Constructor installs this literal-FALSE callback in class+30h. FieldObject_QueryHit calls(object,shape,contact) only after its IsObjectFlagClear guard, and forwards the BOOL.

Reads no input or contact output, changes no memory. This rejects this query callback; it does not prove the owner has no geometry or all collision disabled.

### `SwitchObject_OnEnabledChangedNoop`

Exact owner constructor registers the empty hook in class+20h. FieldObject_SetEnabled calls it as(object,enabled) after a real enabled transition, packed save-bit write and conditional actor/world registration.

Not touch/idle/FP initialization despite legacy labels. Empty hook preserves native R0 and does not cancel common enabled-state side effects. Separate from EntryPool+18h.

### `SwitchObject_QueryHitFalse`

Constructor installs this literal-FALSE callback in class+30h. FieldObject_QueryHit calls(object,shape,contact) only after its IsObjectFlagClear guard, and forwards the BOOL.

Reads no input or contact output, changes no memory. This rejects this query callback; it does not prove the owner has no geometry or all collision disabled.

### `SwitchObject_UpdateFallAndProximityChannel`

SetSwitchState installs this callback for state 0. It first updates falling physics; only if session mask20h is clear and IsNearFirstEntity(object) is true it calls ConfigureChannelSlot(0,1,0), then returns literal 0.

Preserve short-circuit ordering, physics call and literal 0. No gameplay/channel-event name is assigned to the numeric arguments.

### `SwitchObject_UpdateFallInState1`

SetSwitchState installs this distinct callback for state 1. Native code forwards the input object to FieldObject_UpdateFall, then returns literal 0.

Identical generated bodies remain separate state-handler identities. No heap return, completion flag or auto-transition is inferred from0.

### `SwitchObject_UpdateFallInState2`

SetSwitchState installs this distinct callback for state 2. Native code forwards the input object to FieldObject_UpdateFall, then returns literal 0.

Identical generated bodies remain separate state-handler identities. No heap return, completion flag or auto-transition is inferred from0.

### `SetSwitchObjectStateForwarder`

Literal-pool tail thunk LDR R3; BX R3;020a0654 forwards to ARM FieldObject_SetSwitchState. The VM caller resolves class/element, converts the third operand to BOOL and supplies object/state.

Preserve incoming R0/R1 and worker register result; no owned-pointer return. No PXI/FIFO initialization is present. Worker also accepts state 2 from other real callers.

### `ShapedObject_OnEnabledChangedNoop`

Exact owner constructor registers the empty hook in class+20h. FieldObject_SetEnabled calls it as(object,enabled) after a real enabled transition, packed save-bit write and conditional actor/world registration.

Not touch/idle/FP initialization despite legacy labels. Empty hook preserves native R0 and does not cancel common enabled-state side effects. Separate from EntryPool+18h.

### `ShapedObject_GetPosition`

Returns object+40h, the VecFx32 position initialized by the exact owner factory. Constructor registers this function in class+28h; FieldObject_GetPosition invokes it as callback(object).

Borrowed interior pointer; no allocation, null guard or ownership transfer. Do not confuse object+40h with an actor model position or with the separate class+34h callback.

### `ShapedObject_GetClassHitResult`

Registered class+2ch callback returns the raw 32-bit word at object->class(+8)->word50h. Actual FieldObject_ApplyHit supplies(object,message); leaf ignores the message. Constructors set the word to0, shaped params.value, and10h respectively.

Scalar hit result, not an archive/file pointer or owned object. No interpretation of its bits or normalization to BOOL. +50h is a class field here, not the object save-bit offset.

### `ShapedObject_QueryHitFalse`

Constructor installs this literal-FALSE callback in class+30h. FieldObject_QueryHit calls(object,shape,contact) only after its IsObjectFlagClear guard, and forwards the BOOL.

Reads no input or contact output, changes no memory. This rejects this query callback; it does not prove the owner has no geometry or all collision disabled.

### `FrontViewObject_OnEnabledChangedNoop`

Exact owner constructor registers the empty hook in class+20h. FieldObject_SetEnabled calls it as(object,enabled) after a real enabled transition, packed save-bit write and conditional actor/world registration.

Not touch/idle/FP initialization despite legacy labels. Empty hook preserves native R0 and does not cancel common enabled-state side effects. Separate from EntryPool+18h.

### `FrontViewObject_GetPosition`

Returns object+40h, the VecFx32 position initialized by the exact owner factory. Constructor registers this function in class+28h; FieldObject_GetPosition invokes it as callback(object).

Borrowed interior pointer; no allocation, null guard or ownership transfer. Do not confuse object+40h with an actor model position or with the separate class+34h callback.

### `FrontViewObject_SetPositionNoop`

Front-view constructor installs empty class+24h callback. CallFieldObjectHook24 forwards(object,argument); the real vector VM command resolves the object, builds a VecFx32 and passes its address. Other owners write their position through this slot, while this owner does no work.

No position/actor synchronization occurs in this hook. Preserve nonnull registration and native incoming R0; do not label the class as immovable through every other API.

### `FrontViewObject_GetClassHitResult`

Registered class+2ch callback returns the raw 32-bit word at object->class(+8)->word50h. Actual FieldObject_ApplyHit supplies(object,message); leaf ignores the message. Constructors set the word to0, shaped params.value, and10h respectively.

Scalar hit result, not an archive/file pointer or owned object. No interpretation of its bits or normalization to BOOL. +50h is a class field here, not the object save-bit offset.

### `FrontViewObject_QueryHitFalse`

Constructor installs this literal-FALSE callback in class+30h. FieldObject_QueryHit calls(object,shape,contact) only after its IsObjectFlagClear guard, and forwards the BOOL.

Reads no input or contact output, changes no memory. This rejects this query callback; it does not prove the owner has no geometry or all collision disabled.

### `SpawnObject_OnEnabledChangedNoop`

Exact owner constructor registers the empty hook in class+20h. FieldObject_SetEnabled calls it as(object,enabled) after a real enabled transition, packed save-bit write and conditional actor/world registration.

Not touch/idle/FP initialization despite legacy labels. Empty hook preserves native R0 and does not cancel common enabled-state side effects. Separate from EntryPool+18h.

### `SpawnObject_GetPosition`

Returns object+40h, the VecFx32 position initialized by the exact owner factory. Constructor registers this function in class+28h; FieldObject_GetPosition invokes it as callback(object).

Borrowed interior pointer; no allocation, null guard or ownership transfer. Do not confuse object+40h with an actor model position or with the separate class+34h callback.

### `SpawnObject_BeforeSpawnUpdateZero`

Literal0 state callback installed by SetState(0), which sets object flags30h. Factory initializes state 0; BeginSpawn changes to1, whose nonempty animation updater may switch to2.

No state change or memory work in this function. Name describes its position in this proven FSM, not a recovered gameplay idle/wait behavior. No completion semantics assigned to0.

### `SpawnObject_AfterSpawnAnimationUpdateZero`

Literal0 state callback installed by SetState(2). AdvanceToAnimEnd sets state 2 when frame+1000h equals animation duration after its increment.

The callback itself does not advance animation, reset position or finish a task. Preserve exact equality and native transition in the separate nonempty worker.

### `SpawnObject_GetTargetPosition`

Returns the same object+40h VecFx32 interior pointer, registered in this owner class+34h. CallFieldObjectHook13IfPresent passes object; GetWaitTargetPosition consumes this hook for target kind 2.

Different registration/address from SpawnObject_GetPosition at+28h. No class+28h guard is imported; this hook result remains borrowed.

## Reproducible evidence

```powershell
Get-Content eu/src/overlays/ov001/FieldObjectCallbacks.h
Get-Content eu/src/overlays/ov001/calls/FieldObject_SetEnabled.c
Get-Content eu/src/overlays/ov008/calls/CreateGimmickClass.c
Get-Content eu/src/overlays/ov009/calls/FieldObject_SetSwitchState.c
Get-Content eu/src/overlays/ov011/calls/FieldObject_SetState.c
Get-Content eu/src/overlays/ov007/data/tables/gFieldActorScriptCommandHandlers.c
```


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov007/calls/ScriptCmd_SetAreaSceneDefinitionParams.c ScriptCmd_SetAreaSceneDefinitionParams --thumb
python tools/verify_idx.py src/overlays/ov007/calls/ScriptCmd_ResetAreaSceneSelectionFlags.c ScriptCmd_ResetAreaSceneSelectionFlags --thumb
python tools/verify_idx.py src/overlays/ov008/auto/ChildSpawner_GetPosition.c ChildSpawner_GetPosition --thumb
python tools/verify_idx.py src/overlays/ov008/auto/ChildSpawner_ApplyHitTrue.c ChildSpawner_ApplyHitTrue --thumb
python tools/verify_idx.py src/overlays/ov008/auto/ChildSpawner_QueryHitFalse.c ChildSpawner_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov008/auto/DelayedGimmick_OnEnabledChangedNoop.c DelayedGimmick_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov008/auto/DelayedGimmick_GetPosition.c DelayedGimmick_GetPosition --thumb
python tools/verify_idx.py src/overlays/ov008/auto/DelayedGimmick_GetClassHitResult.c DelayedGimmick_GetClassHitResult --thumb
python tools/verify_idx.py src/overlays/ov008/auto/DelayedGimmick_QueryHitFalse.c DelayedGimmick_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov009/auto/SwitchObject_OnEnabledChangedNoop.c SwitchObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov009/auto/SwitchObject_QueryHitFalse.c SwitchObject_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov009/calls/SwitchObject_UpdateFallAndProximityChannel.c SwitchObject_UpdateFallAndProximityChannel --thumb
python tools/verify_idx.py src/overlays/ov009/calls/SwitchObject_UpdateFallInState1.c SwitchObject_UpdateFallInState1 --thumb
python tools/verify_idx.py src/overlays/ov009/calls/SwitchObject_UpdateFallInState2.c SwitchObject_UpdateFallInState2 --thumb
python tools/verify_idx.py src/overlays/ov009/calls/SetSwitchObjectStateForwarder.c SetSwitchObjectStateForwarder --thumb
python tools/verify_idx.py src/overlays/ov010/auto/ShapedObject_OnEnabledChangedNoop.c ShapedObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov010/auto/ShapedObject_GetPosition.c ShapedObject_GetPosition --thumb
python tools/verify_idx.py src/overlays/ov010/auto/ShapedObject_GetClassHitResult.c ShapedObject_GetClassHitResult --thumb
python tools/verify_idx.py src/overlays/ov010/auto/ShapedObject_QueryHitFalse.c ShapedObject_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov010/auto/FrontViewObject_OnEnabledChangedNoop.c FrontViewObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov010/auto/FrontViewObject_GetPosition.c FrontViewObject_GetPosition --thumb
python tools/verify_idx.py src/overlays/ov010/auto/FrontViewObject_SetPositionNoop.c FrontViewObject_SetPositionNoop --thumb
python tools/verify_idx.py src/overlays/ov010/auto/FrontViewObject_GetClassHitResult.c FrontViewObject_GetClassHitResult --thumb
python tools/verify_idx.py src/overlays/ov010/auto/FrontViewObject_QueryHitFalse.c FrontViewObject_QueryHitFalse --thumb
python tools/verify_idx.py src/overlays/ov011/auto/SpawnObject_OnEnabledChangedNoop.c SpawnObject_OnEnabledChangedNoop --thumb
python tools/verify_idx.py src/overlays/ov011/auto/SpawnObject_GetPosition.c SpawnObject_GetPosition --thumb
python tools/verify_idx.py src/overlays/ov011/auto/SpawnObject_BeforeSpawnUpdateZero.c SpawnObject_BeforeSpawnUpdateZero --thumb
python tools/verify_idx.py src/overlays/ov011/auto/SpawnObject_AfterSpawnAnimationUpdateZero.c SpawnObject_AfterSpawnAnimationUpdateZero --thumb
python tools/verify_idx.py src/overlays/ov011/auto/SpawnObject_GetTargetPosition.c SpawnObject_GetTargetPosition --thumb
bash tools/gate.sh
```
