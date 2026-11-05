# Field-pool requests, callbacks and duration modes

This block names 15 previously held EU ov017 functions from real constructor assignments, paired writers/consumers, VM tables and native argument/return flow. Grid pool category 8, request manager category 4 and collectible/linked category 7 are separate owners. The existing prototypes and algorithms are preserved.

## Callback offsets rather than private labels

All three pools use the common callback layout, independently established by ov001 dispatchers. Owner +0x0c is invoked after actor-slot scanning for entry flag 4; +0x18 is the active-state hook after common inactive-bit/world-registration work; +0x1c forwards entry and hit/push event and returns the callback result. Entry/pool destruction and drawing occupy other slots.

CreateGridEntryPool installs the empty actor-slot refresh and active hooks, plus a literal-TRUE event callback at +0x1c. Its private onRemove/onInit/onEnter labels are misleading. The empty callbacks do not erase surrounding actor-slot/activation effects. The event leaf reads no input and changes no memory; preserve its returned 1 without assigning collision accept/reject/stop semantics. The kind4 pool has its own separate empty actor-slot refresh hook. Empty hooks preserve the incoming register word, and dispatchers can propagate it; this plan does not invent a normalized BOOL or owned/fluent pointer result.

The script table contains 23 function/metadata pairs; physical word 14 is the otherwise empty command named ScriptCmd_FieldPoolNoop. Its body returns literal 1 and performs no state work. The library DefaultStepDone spelling does not establish an SDK role. Keep the registration and native result.

## Position duration mode and per-request context

The category4 manager word +0x1ec is a raw default path-duration mode, as established by the VM setter, paired getter, position-request builder and real state/step workers. Mode 0 copies the supplied fixed-point value as duration; mode 1 computes distance divided by the supplied value. The computed +4 duration is then consumed by StepLinearPathMotion. The setter preserves the whole 32-bit word; InitPool1Entry later narrows it to a signed high halfword. Unsupported modes receive no new validation or default behavior.

The same 20-byte Pool1 record contains a separate low halfword used by the stepper as easing. Some private declarations call these id/type or easing/hold; the high halfword also affects the existing zero-duration wait path. Do not swap the low easing selector with the manager's duration mode, or treat the final script integer as another duration solely because of an old parameter label. The constructor's private pendingList pointer view at +0x1ec is misleading: the proven operation here is a raw mode word, not an allocation.

Pool0 is a different wait-duration array. SetFieldWaitDuration stores the requested fixed-point limit into a freshly appended slot. ResetFieldEntryWaitTimer instead clears the request context's first word (object +0x70), supplied through gPoolValueHandlers[0] and DispatchListHeadCallback. AdvancePool0Timer adds pending overflow plus 0x1000 and compares that context word against the Pool0 limit. A limit of zero returns FALSE rather than completing immediately. These are distinct storage and operations; no bounds checks or count-width changes are added.

## Fall requests and linked entry records

InitFieldFallRequestListHead clears a newly appended Pool4 slot to NULL. The getter exposes that slot as a list-head pointer; UpdateOwnerFall iterates its nodes. This initializer does not free nodes or safely clear an arbitrary populated list.

ProcessFieldFallResetRequest is action 0 in the pending fall-request table. Native arguments are request node, fall state, owner and target entity; the body ignores the second argument. Only when target state is 2 and the owner predicate permits does it reset the target, set its flag 5, copy request +8 position and refresh/dispatch the target's list head. Independently, inactive camera shake clears that flag and returns TRUE; active shake returns FALSE. The enclosing worker clears node.pending only on TRUE. Completion therefore does not prove that the optional reset branch ran. Preserve guard/delegate order and literal return behavior.

InitLinkedEntryForwarder uses `PUSH {r3,lr}; BL InitLinkedEntry; POP {r3,pc}`. It forwards four words; the worker stores an eight-byte record `{u8 kind; u8 flags; u16 value; nextPointer}` and sets the existing flag bits/link relation. It is a direct call wrapper, not a literal-pool tail thunk, and does not format text. Legacy Text_VSNPrintf/format-string parameter views are false. Narrowing occurs in the worker; no owned-pointer result is inferred from the wrapper's emitted r0.

## Collection hook and category7 masks

FieldDrop_OnCollectOwnerAncestorNoop is called during collection only when FindInactiveOwnerAncestor returns a target. Its inputs are that ancestor and the drop object. It is separate from the earlier ordinary-ancestor stack-height propagation path. The body modifies/frees neither object. The caller overwrites its residual r0 before common flag/reward work. It does not prove a visual effect or a successful propagation operation.

GetKind7HiddenMask returns halfword +0x54 AND 8. The paired hidden setter writes that bit and changes status/actor visibility; the return is raw 0/8 despite BOOL-like consumer declarations. GetKind7Flag4 returns 0/4 from the same owner field. Ancestor/fall/switch consumers establish the owner and operation, but not a gameplay meaning for bit 4, so its name remains literal. Do not reinterpret either as complete flags or transfer these masks to category4 owners.

## Identities and evidence

Paths below are relative to `eu/` after integration. Shared source suffixes retain reference-region names; original identities and modes identify EU. The plan keeps detailed source/ROM evidence and existing object snapshots for each row.

| Original EU identity | Descriptive name | Mode / bytes | Planned EU source | Evidence |
|---|---|---|---|---|
| `ScriptCmd_FieldPoolNoop` | `ScriptCmd_FieldPoolNoop` | THUMB / 0x4 | `src/overlays/ov017/auto/ScriptCmd_FieldPoolNoop.c` | `eu/src/overlays/ov017/data/tables/gPoolScriptCommandHandlers.c` |
| `GridObject_OnSetActiveNoop` | `GridObject_OnSetActiveNoop` | THUMB / 0x2 | `src/overlays/ov017/auto/GridObject_OnSetActiveNoop.c` | `src/ov001/unclassified_helpers/CacheEntry_SetActive_02087258.c` |
| `GridObject_EntryEventTrue` | `GridObject_EntryEventTrue` | THUMB / 0x4 | `src/overlays/ov017/auto/GridObject_EntryEventTrue.c` | `src/ov017/unclassified_helpers/CreateGridEntryPool_020a2a40.c` |
| `GridObject_OnActorSlotRefreshNoop` | `GridObject_OnActorSlotRefreshNoop` | THUMB / 0x2 | `src/overlays/ov017/auto/GridObject_OnActorSlotRefreshNoop.c` | `src/ov001/field_objects/FieldObject_ApplyActorSlotIndex_02086384.c` |
| `Kind4Object_OnActorSlotRefreshNoop` | `Kind4Object_OnActorSlotRefreshNoop` | THUMB / 0x2 | `src/overlays/ov017/auto/Kind4Object_OnActorSlotRefreshNoop.c` | `src/ov017/unclassified_helpers/CreateKind4EntryPool_020a3a28.c` |
| `SetKind4PathDurationMode` | `SetKind4PathDurationMode` | THUMB / 0x8 | `src/overlays/ov017/auto/SetKind4PathDurationMode.c` | `src/ov017/script_commands/ScriptCmd_SetManagerValue_020a2628.c` |
| `GetKind4PathDurationMode` | `GetKind4PathDurationMode` | THUMB / 0x8 | `src/overlays/ov017/auto/GetKind4PathDurationMode.c` | `src/ov017/unclassified_helpers/ComputePool1Progress_020a42b0.c` |
| `ResetFieldEntryWaitTimer` | `ResetFieldEntryWaitTimer` | THUMB / 0x6 | `src/overlays/ov017/auto/ResetFieldEntryWaitTimer.c` | `src/ov017/unclassified_helpers/AdvancePool0Timer_020a4278.c` |
| `ProcessFieldFallResetRequest` | `ProcessFieldFallResetRequest` | THUMB / 0x52 | `src/overlays/ov017/calls/ProcessFieldFallResetRequest.c` | `src/ov017/unclassified_helpers/UpdateOwnerFall_020a48cc.c` |
| `InitLinkedEntryForwarder` | `InitLinkedEntryForwarder` | THUMB / 0x8 | `src/overlays/ov017/calls/InitLinkedEntryForwarder.c` | `src/ov017/field_objects/InitLinkedEntry_020a4254.c` |
| `SetFieldWaitDuration` | `SetFieldWaitDuration` | THUMB / 0x4 | `src/overlays/ov017/auto/SetFieldWaitDuration.c` | `src/ov017/unclassified_helpers/AppendPool0Value_020a3ec4.c` |
| `InitFieldFallRequestListHead` | `InitFieldFallRequestListHead` | THUMB / 0x6 | `src/overlays/ov017/auto/InitFieldFallRequestListHead.c` | `src/ov017/unclassified_helpers/UpdateOwnerFall_020a48cc.c` |
| `FieldDrop_OnCollectOwnerAncestorNoop` | `FieldDrop_OnCollectOwnerAncestorNoop` | THUMB / 0x2 | `src/overlays/ov017/auto/FieldDrop_OnCollectOwnerAncestorNoop.c` | `eu/src/overlays/ov017/calls/FieldDrop_OnCollect.c` |
| `GetKind7HiddenMask` | `GetKind7HiddenMask` | THUMB / 0xa | `src/overlays/ov017/auto/GetKind7HiddenMask.c` | `eu/src/overlays/ov017/calls/SetKind7EntryHidden.c` |
| `GetKind7Flag4` | `GetKind7Flag4` | THUMB / 0xa | `src/overlays/ov017/auto/GetKind7Flag4.c` | `src/ov017/field_objects/IsActiveAncestorChain_020a50e4.c` |


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov017/auto/ScriptCmd_FieldPoolNoop.c ScriptCmd_FieldPoolNoop --thumb
python tools/verify_idx.py src/overlays/ov017/auto/GridObject_OnSetActiveNoop.c GridObject_OnSetActiveNoop --thumb
python tools/verify_idx.py src/overlays/ov017/auto/GridObject_EntryEventTrue.c GridObject_EntryEventTrue --thumb
python tools/verify_idx.py src/overlays/ov017/auto/GridObject_OnActorSlotRefreshNoop.c GridObject_OnActorSlotRefreshNoop --thumb
python tools/verify_idx.py src/overlays/ov017/auto/Kind4Object_OnActorSlotRefreshNoop.c Kind4Object_OnActorSlotRefreshNoop --thumb
python tools/verify_idx.py src/overlays/ov017/auto/SetKind4PathDurationMode.c SetKind4PathDurationMode --thumb
python tools/verify_idx.py src/overlays/ov017/auto/GetKind4PathDurationMode.c GetKind4PathDurationMode --thumb
python tools/verify_idx.py src/overlays/ov017/auto/ResetFieldEntryWaitTimer.c ResetFieldEntryWaitTimer --thumb
python tools/verify_idx.py src/overlays/ov017/calls/ProcessFieldFallResetRequest.c ProcessFieldFallResetRequest --thumb
python tools/verify_idx.py src/overlays/ov017/calls/InitLinkedEntryForwarder.c InitLinkedEntryForwarder --thumb
python tools/verify_idx.py src/overlays/ov017/auto/SetFieldWaitDuration.c SetFieldWaitDuration --thumb
python tools/verify_idx.py src/overlays/ov017/auto/InitFieldFallRequestListHead.c InitFieldFallRequestListHead --thumb
python tools/verify_idx.py src/overlays/ov017/auto/FieldDrop_OnCollectOwnerAncestorNoop.c FieldDrop_OnCollectOwnerAncestorNoop --thumb
python tools/verify_idx.py src/overlays/ov017/auto/GetKind7HiddenMask.c GetKind7HiddenMask --thumb
python tools/verify_idx.py src/overlays/ov017/auto/GetKind7Flag4.c GetKind7Flag4 --thumb
bash tools/gate.sh
```
