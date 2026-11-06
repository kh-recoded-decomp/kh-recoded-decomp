# Entry-pool hit default, linked-actor drawing and actor-owner detachment

These names follow the owner layout and the actual native caller. The EntryPool and FieldObjectClass families remain separate. Existing C declarations are preserved; logical slot inputs below describe the native contract and do not introduce parameters into literal-return functions.

| EU identity | Proposed name | Active source before rename |
| --- | --- | --- |
| ov001:0x0208627c (Thumb, 0x4 bytes) | `EntryPool_DefaultHitQueryFalse` | `eu/src/overlays/ov001/auto/EntryPool_DefaultHitQueryFalse.c` |
| ov001:0x02086b14 (Thumb, 0x30 bytes) | `DrawLinkedFieldEntryActorPass` | `eu/src/overlays/ov001/calls/DrawLinkedFieldEntryActorPass.c` |
| ov001:0x02088b80 (Thumb, 0x6c bytes) | `ResetActorMotionAndDetachOwner` | `eu/src/overlays/ov001/calls/ResetActorMotionAndDetachOwner.c` |

## EntryPool default hit query

`CreateEntryPool` installs `EntryPool_DefaultHitQueryFalse` in pool +0x24. A pool owns an aligned array of entries; each entry points back to that pool at entry +4. The same header stores entry stride at +0x3c, count at +0x3e and entry storage at +0x40. `CreateKind4EntryPool` replaces this default slot with `CollideFieldObjectActor`.

The consumer is proved directly: `StepHitScan` states 3/4 take the list from `GetFieldEntryListHead` and process it through `ResolveNearestHitNode`. At native ov021:0x020aba78, that routine loads the pool from entry +4; at 0x020aba7c it loads pool +0x24; at 0x020aba82 it calls the function with `(entry, attackShape, &contact)`. Only nonzero results proceed to the facing/height filter and hit result selection. `ProbeNearestFacingTarget` invokes the same slot on the same entry list and also requires nonzero.

The default contains only `MOVS R0,#0; BX LR` (ROM bytes `00 20 70 47`). It reads no inputs and writes no output contact or other memory. It always reports no accepted hit. The native slot passes three arguments, while this implementation needs none and keeps its existing `int(void)` declaration. This records an erased native ABI; it does not claim that every existing C function-pointer declaration is a portable, compatible prototype.

This is not `FieldObject_QueryHit`: that other family obtains its callbacks from object +8 and uses query slot +0x30. Its class layout, callback and data contracts must not be copied onto EntryPool merely because both perform hit queries. No common enum for nonzero backend results is assigned.

Evidence sources:

- `eu/src/overlays/ov001/calls/CreateEntryPool.c` and shared `src/ov001/unclassified_helpers/CreateEntryPool_02086258.c`
- `eu/src/overlays/ov017/calls/CreateKind4EntryPool.c`
- `eu/src/overlays/ov017/calls/CollideFieldObjectActor.c`
- `eu/src/overlays/ov021/calls/StepHitScan.c` and shared `src/ov021/object_state/StepHitScan_020ac164.c`
- `eu/src/overlays/ov021/calls/ResolveNearestHitNode.c` and shared `src/ov021/object_state/ResolveNearestHitNode_020aba18.c`
- `eu/src/overlays/ov001/calls/ProbeNearestFacingTarget.c`
- `eu/src/overlays/ov001/FieldObjectCallbacks.h`

## Drawing the actor linked to a field entry

`DrawLinkedFieldEntryActorPass(actorSlot, pass)` is a draw callback whose first native input is the actor-slot header. It saves R0 at 0x02086b16 and calls `QueryLinkTarget` at 0x02086b1a without changing R0. The current C call erases that argument; the incoming slot remains the real lookup input.

`QueryLinkTarget` reads bytes kind/group/index at actorSlot +0x1a4. Kind 4 resolves `GetFieldEntryByPoolAndIndex(group, index)`; kind 2 resolves the separate field-object class family; other kinds return NULL. The binding is not inferred from the generic lookup: `RegisterFieldEntryPool` stores the registered pool index at pool +0x59; `LoadTriggerObjectPhase` passes that byte and entry index +0x33 to `SpawnFieldActor` with its kind-2 option off. `SpawnFieldActor` constructs attributes `{4, poolIndex, entryIndex, 0}`, and `ActorEntry_Init` copies them to slot +0x1a4.

The pool manager setup routine currently named `ResourceCache_Shutdown` obtains each list entry's actor slot from byte +0x32 and installs this callback using `Obj_SetWord1C8`. That setter writes slot +0x1c8. The main `UpdateActorSlotsAndBillboards` routine invokes this slot as `(slot, 0)` during the active/visible drawing traversal and `(slot, 1)` for the qualifying secondary pass. The historical shutdown/update labels do not establish the callback role; the writer and runner do.

The callback looks up its link for every pass. Only pass 0 with `GetFieldEntryDrawBlockMask() == 0` draws anything. It reads pool draw hook +0x38: if present, call the hook with the field entry; otherwise draw the actor node at slot +0x14. A nonzero pass draws nothing. The manager draw-block return is the raw mask `byte[+5] & 0x11`, not a normalized Boolean.

The installed path uses kind 4 and the EntryPool layout. This callback must not be applied to kind-2 class objects just because the shared lookup supports them. There is no NULL check after lookup on the actual drawing branch. The actor slot, the inner actor returned by `ActorRegistry_GetEntityByIndex` (slot +0x10), the entry, and the pool are four different pointer bases. The custom pool draw hook receives the entry. The callback itself allocates, frees and transfers ownership of nothing.

Evidence sources:

- `eu/src/overlays/ov001/calls/QueryLinkTarget.c` and shared `src/ov001/unclassified_helpers/QueryLinkTarget_02080a78.c`
- `eu/src/overlays/ov001/calls/RegisterFieldEntryPool.c`
- `eu/src/overlays/ov001/calls/SpawnFieldActor.c`
- `eu/src/overlays/ov017/calls/LoadTriggerObjectPhase.c` and shared `src/ov017/field_objects/LoadTriggerObjectPhase_020a2bd0.c`
- `eu/src/calls/ActorEntry_Init.c` and shared `src/arm9/shared_engine/ActorEntry_Init_020357d8.c`
- `eu/src/overlays/ov001/calls/ResourceCache_Shutdown.c`
- `eu/src/calls/Obj_SetWord1C8.c`
- `eu/src/calls/UpdateActorSlotsAndBillboards.c` and shared `src/arm9/shared_engine/UpdateActorSlotsAndBillboards_02035dd0.c`

## Resetting motion and detaching an actor owner

`ResetActorMotionAndDetachOwner(actor)` always clears the actor's timer region and movement/extras through `ClearActorTimerFields` and `ResetActorVelocityAndExtraSlots`. Its first word is an optional pointer to another actor object from the same scene actor-object table. If that word is NULL, it performs no reference-count or owner actor-slot lookup.

The paired writer is `AttachActorToOwner(newActor, owner, actorId)`: it sets child flags +0xef4 to 0x29, writes the child actor ID at +0xf00, increments owner +0xf04, optionally installs the owner's model callback, then stores the owner pointer in the child's first word. `ScriptCmd_AttachActorToParent` passes `scene.actorObjects[childId]` and `scene.actorObjects[parentId]`, proving the pointer domain. `ActorObject_Reset` initializes the first word and +0xf04 to zero and +0xf00 to the actual actor ID. Private names such as kind/state/pending are not the evidence for these roles.

For a non-NULL link, the reset/detach routine decrements owner +0xf04 by one. If the new count is zero, the owner's actor ID narrowed to 16 bits identifies an existing actor slot, and that slot's flags contain bit 4, it clears mask 0x18 (bits 0x08 and 0x10) in the inner actor's halfword at +4. It then clears the child's first word regardless of whether the actor-slot checks succeeded. Those animation/node bits retain their literal mask here; no UI or gameplay meaning is invented.

This decrements an owner-link counter; it does not free, destroy or transfer ownership of the owner allocation. There is no counter underflow check. The binder itself does not detach a previous owner before rebinding. Callers must respect that lifecycle.

The routine is used by actor resource cleanup, by the terminal motion-track path, and by `ResetActorFlags`. The last wrapper's current C call has no declared arguments, but its native incoming R0 is preserved through the call; it then writes flags 0x2000. That ABI spelling stays unchanged in this naming block.

Evidence sources:

- `eu/src/overlays/ov001/calls/AttachActorToOwner.c` and shared `src/ov001/actor_animation/func_ov001_02089ee4.c`
- `eu/src/overlays/ov001/calls/ScriptCmd_AttachActorToParent.c` and shared `src/ov001/scripted_actor_behavior/ScriptCmd_AttachActorToParent_0208c918.c`
- `eu/src/overlays/ov001/calls/ActorObject_Reset.c` and shared `src/ov001/scripted_actor_behavior/ActorObject_Reset_02089cac.c`
- `eu/src/overlays/ov001/calls/ClearActorTimerFields.c`
- `eu/src/overlays/ov001/calls/ResetActorVelocityAndExtraSlots.c`
- `eu/src/overlays/ov001/calls/ActorObject_ReleaseResources.c`
- `eu/src/overlays/ov001/calls/UpdateActorMotionTracks.c`
- `eu/src/overlays/ov001/calls/ResetActorFlags.c`


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/EntryPool_DefaultHitQueryFalse.c EntryPool_DefaultHitQueryFalse --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawLinkedFieldEntryActorPass.c DrawLinkedFieldEntryActorPass --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ResetActorMotionAndDetachOwner.c ResetActorMotionAndDetachOwner --thumb
bash tools/gate.sh
```
