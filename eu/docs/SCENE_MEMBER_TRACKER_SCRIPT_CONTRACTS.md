# Additional scene, member, tracker and script contracts

Nine EU entrypoints now identify checked owners and native consumer contracts.
Eight replace numeric names; the area onLeave hook corrects an earlier
misleading descriptive name. Existing prototypes and layouts are preserved.

Session callbacks[2] are onLeave hooks, proven by LeaveFieldMenu's shared consumer. The three scene owners below each clear their own mask 0x2; the lifecycle role does not assign a stronger gameplay meaning to that mask. The area startup flag 0x1 and exit request 0x4000 are separately proven through writers/readers in overlay040 that refer to the exact same area-work global. These cross-overlay identities are essential. The gauge expression reads blink activity rather than fill, while extra-member and tracker-slot names follow their own constructors and consumers.

The declarations below reproduce the native source view after only the proposed name substitution. Generated word arguments, old private parameter labels and native pointer-width assumptions remain visible; the proven caller/writer contract is stated separately. Links use the current source paths; line labels refer to the reviewed source snapshot.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov021:020b0b0c` | THUMB | `func_ov021_020b0b0c` | `StageScriptExpr_GetHudGauge0BlinkActive` | [eu/src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c](../src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c) |
| `ov021:020ad8e4` | THUMB | `func_ov021_020ad8e4` | `GetExtraMemberIndex` | [eu/src/overlays/ov021/calls/GetExtraMemberIndex.c](../src/overlays/ov021/calls/GetExtraMemberIndex.c) |
| `ov021:020af21c` | THUMB | `func_ov021_020af21c` | `FreeSlotTrackerUnitSlots` | [eu/src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c](../src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c) |
| `ov030:020bb374` | THUMB | `func_ov030_020bb374` | `GetOv030SceneReferenceAxis` | [eu/src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c](../src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c) |
| `ov032:020bb49c` | THUMB | `func_ov032_020bb49c` | `GroupSceneOnLeaveClearFlag2` | [eu/src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c](../src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c) |
| `ov035:020ba978` | THUMB | `func_ov035_020ba978` | `IsAreaSceneStartupComplete` | [eu/src/overlays/ov035/calls/IsAreaSceneStartupComplete.c](../src/overlays/ov035/calls/IsAreaSceneStartupComplete.c) |
| `ov035:020ba9ac` | THUMB | `func_ov035_020ba9ac` | `RequestAreaSceneExit` | [eu/src/overlays/ov035/calls/RequestAreaSceneExit.c](../src/overlays/ov035/calls/RequestAreaSceneExit.c) |
| `ov036:020bc3f4` | ARM | `func_ov036_020bc3f4` | `Event2DSceneOnLeaveClearFlag2` | [eu/src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c](../src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c) |
| `ov035:020ba994` | THUMB | `ClearMovieContextReadyFlag` | `AreaSceneOnLeaveClearFlag2` | [eu/src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c](../src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c) |

## StageScriptExpr_GetHudGauge0BlinkActive

Identity: `ov021:020b0b0c`, THUMB, native extent 20 bytes. EU source: [eu/src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c](../src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c).

```c
u32 StageScriptExpr_GetHudGauge0BlinkActive(int self);
```

- Owner: Stage script result context; HUD gauge animation owner is separately obtained by the callee.
- Inputs: Stage-script context in R0; gauge index is the literal 0.
- Result and effects: Writes tag 1 at context +0x2c and the raw activity word at +0x30; returns opcode status 0.
- Lifetime: No allocation, ownership transfer or retained new pointer.

Evidence:

- Calls the gauge accessor with literal index 0 and copies the returned word into the tagged integer result. Source: [eu/src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c:5-13](../src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c).
- Accessor reads the word at HUD work +0x7c + index*0x18. Source: [eu/src/overlays/ov001/calls/GetHudGaugeBlinkActive.c:1-5](../src/overlays/ov001/calls/GetHudGaugeBlinkActive.c).
- GaugeAnim has 0x18-byte extent with active at +0x10; its array begins at HUD owner +0x6c. Source: [eu/src/overlays/ov001/calls/SetMenuGaugeActive.c:6-33](../src/overlays/ov001/calls/SetMenuGaugeActive.c).
- The matching writer sets active to 1 or 0 and initializes the tick/frame state when enabling. Source: [eu/src/overlays/ov001/calls/SetMenuGaugeActive.c:48-80](../src/overlays/ov001/calls/SetMenuGaugeActive.c).
- The active slot alternates its phase and redraws the gauge using modes 0/2 from elapsed ticks; this is blink-animation activity. Source: [eu/src/overlays/ov001/calls/AdvanceGaugeSlot.c:40-75](../src/overlays/ov001/calls/AdvanceGaugeSlot.c).

Contract limits:

- It is not the gauge's numeric fill/current value, HP, or a session-level readiness result.
- The copied activity word is retained raw; the expression itself does not normalize it to BOOL.

## GetExtraMemberIndex

Identity: `ov021:020ad8e4`, THUMB, native extent 18 bytes. EU source: [eu/src/overlays/ov021/calls/GetExtraMemberIndex.c](../src/overlays/ov021/calls/GetExtraMemberIndex.c).

```c
s32 GetExtraMemberIndex(int self);
```

- Owner: The member/cue-handler list used by the owning actor's +0x1070 subobject.
- Inputs: Pointer to the list prefix: pointer array +0, total count +4, current member +8 and optional extra member +0x0c.
- Result and effects: Returns total count - 1 if extra member +0x0c is nonzero; otherwise -1.
- Lifetime: Returns an index only; the list retains ownership of member pointers.

Evidence:

- Returns count-1 exactly when the optional pointer at +0x0c exists. Source: [eu/src/overlays/ov021/calls/GetExtraMemberIndex.c:3-10](../src/overlays/ov021/calls/GetExtraMemberIndex.c).
- The constructor's list prefix identifies handler array, count, current-state word and extraHandler at +0x0c. Source: [src/ov021/shared_engine/LoadSelectionCues_020ad744.c:26-36](../../src/ov021/shared_engine/LoadSelectionCues_020ad744.c).
- The constructor increments the total for an extra entry, appends it after the ordinary entries and stores that exact pointer in extraHandler. Source: [src/ov021/shared_engine/LoadSelectionCues_020ad744.c:81-98](../../src/ov021/shared_engine/LoadSelectionCues_020ad744.c).
- EU wrapper binds the caller's shared ad8c4 name to EU ad8e4. Source: [eu/src/overlays/ov052/calls/DispatchSlotAction.c:10-14](../src/overlays/ov052/calls/DispatchSlotAction.c).
- Caller checks the returned index with CanUseMemberSlot, saves it as the chosen slot and requests action mode 0x18. Source: [src/ov052/unclassified_helpers/DispatchSlotAction_020ced20.c:151-159](../../src/ov052/unclassified_helpers/DispatchSlotAction_020ced20.c).

Contract limits:

- This is the appended extra member, not the member currently selected at list +8.
- An inconsistent count of zero with a nonnull extra pointer is not guarded; native arithmetic is retained.
- No gameplay name is assigned to the extra member's IDs or categories.

## FreeSlotTrackerUnitSlots

Identity: `ov021:020af21c`, THUMB, native extent 16 bytes. EU source: [eu/src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c](../src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c).

```c
void FreeSlotTrackerUnitSlots(int arg0);
```

- Owner: TrackerUnit created by SpawnSlotTrackerUnit; its slot-array field is at +0x18c.
- Inputs: TrackerUnit pointer.
- Result and effects: Void; calls the heap free helper on the slot-array pointer.
- Lifetime: Releases the separately allocated slots array, not the enclosing unit. The field is not nulled.

Evidence:

- Frees the pointer at unit +0x18c. Source: [eu/src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c:1-4](../src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c).
- TrackerSlot is 0x24 bytes; the constructor's TrackerUnit view places its slot pointer at +0x18c. Source: [src/ov021/unclassified_helpers/SpawnSlotTrackerUnit_020aefb0.c:29-60](../../src/ov021/unclassified_helpers/SpawnSlotTrackerUnit_020aefb0.c).
- Allocates slotCount*sizeof(TrackerSlot), stores the pointer and initializes each ID to -1 and target to zero. Source: [src/ov021/unclassified_helpers/SpawnSlotTrackerUnit_020aefb0.c:99-108](../../src/ov021/unclassified_helpers/SpawnSlotTrackerUnit_020aefb0.c).
- The matching reader iterates the array at +0x18c using count +0x3e and clears active slot IDs/values. Source: [src/ov021/unclassified_helpers/ResetActiveEntries_020af20c.c:9-30](../../src/ov021/unclassified_helpers/ResetActiveEntries_020af20c.c).
- The owning cleanup calls this array-free helper for kind 4 before ReleaseSceneObject and freeing the enclosing allocation. Source: [eu/src/overlays/ov055/calls/ReleaseSceneObjectAndFreeWork.c:7-13](../src/overlays/ov055/calls/ReleaseSceneObjectAndFreeWork.c).

Contract limits:

- The enclosing SceneObject/unit resource release is a separate caller operation.
- No extra NULL, count or duplicate-free guard is added.

## GetOv030SceneReferenceAxis

Identity: `ov030:020bb374`, THUMB, native extent 20 bytes. EU source: [eu/src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c](../src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c).

```c
u32 GetOv030SceneReferenceAxis(void);
```

- Owner: Overlay030 field-scene work at data_ov030_020bd020.
- Inputs: No logical input; reads this scene's global work pointer.
- Result and effects: Borrowed VecFx32 address at work +0x24, or NULL when work is absent; native result type remains u32.
- Lifetime: The vector lives inside scene work and expires with that owner.

Evidence:

- Returns the address at the exact scene global +0x24, with NULL for absent work. Source: [eu/src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c:5-11](../src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c).
- The EU constructor wrapper binds the shared work global to data_ov030_020bd020 and its heap getter to current TaskObject work. Source: [eu/src/overlays/ov030/calls/InitMovieOverlayState_020ba400.c:1-18](../src/overlays/ov030/calls/InitMovieOverlayState_020ba400.c).
- Native structure places the VecFx32 after counter at work +0x24. Source: [src/ov030/movie/InitMovieOverlayState_020ba3e0.c:5-18](../../src/ov030/movie/InitMovieOverlayState_020ba3e0.c).
- Constructor initializes that exact vector to (0,0,0x1000). Source: [src/ov030/movie/InitMovieOverlayState_020ba3e0.c:67-75](../../src/ov030/movie/InitMovieOverlayState_020ba3e0.c).
- Camera scene code passes the returned vector to RejectFromAxis, whose implementation projects with dot and subtracts the axis component. Source: [eu/src/overlays/ov042/calls/UpdateCameraScene.c:1-344](../src/overlays/ov042/calls/UpdateCameraScene.c).
- Another consumer copies the same vector as its particle/motion initializer input; its private position label is not sufficient to call this a world position. Source: [src/ov042/camera/StartCameraParticle_020bd6fc.c:6-12](../../src/ov042/camera/StartCameraParticle_020bd6fc.c).

Contract limits:

- Initial unit Z is proven, but this review does not establish normalization after every possible writer.
- The vector is used as a reference axis and as copied motion input; it is not named camera focus, rendered eye or culling origin.
- The source's old upVector/position labels do not establish a universal camera layout.

## GroupSceneOnLeaveClearFlag2

Identity: `ov032:020bb49c`, THUMB, native extent 24 bytes. EU source: [eu/src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c](../src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c).

```c
void GroupSceneOnLeaveClearFlag2(void);
```

- Owner: Group field scene work in element 1 of data_ov032_020c0080; separate from the route context in element 0.
- Inputs: No logical input; installed as SessionState callbacks[2].
- Result and effects: Void callback; clears mask 0x2 of its scene flags at +6.
- Lifetime: No allocations are released and no pointers are returned.

Evidence:

- Clears only mask 0x2 of the scene work in the second global word. Source: [eu/src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c:1-11](../src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c).
- EU installer aliases the shared slot-2 callback to EU bb49c. Source: [eu/src/overlays/ov032/calls/InstallMovieCallbacks.c:1-14](../src/overlays/ov032/calls/InstallMovieCallbacks.c).
- Installer places that callback in index 2 of the session callback prefix. Source: [src/ov032/shared_engine/InstallMovieCallbacks_020bb79c.c:30-43](../../src/ov032/shared_engine/InstallMovieCallbacks_020bb79c.c).
- Session callback slot 2 is an optional onLeave(void) hook invoked only after slot 1 canLeave permits leaving. The caller discards its return word. Source: [src/ov001/field_manager/LeaveFieldMenu_02061fc0.c:59-71](../../src/ov001/field_manager/LeaveFieldMenu_02061fc0.c).

Contract limits:

- The lifecycle onLeave role is proven; a stronger gameplay meaning for scene flag 0x2 is not assigned.
- This callback clears no whole session/owner block and does not perform shutdown.

## IsAreaSceneStartupComplete

Identity: `ov035:020ba978`, THUMB, native extent 28 bytes. EU source: [eu/src/overlays/ov035/calls/IsAreaSceneStartupComplete.c](../src/overlays/ov035/calls/IsAreaSceneStartupComplete.c).

```c
BOOL IsAreaSceneStartupComplete(void);
```

- Owner: Area scene's gMovieContextState work shared explicitly with overlay040.
- Inputs: No logical input; reads the current area scene work.
- Result and effects: FALSE for absent work; otherwise TRUE exactly when initialization mask 0x1 is clear.
- Lifetime: Reads borrowed task work, without retaining or allocating it.

Evidence:

- The exact predicate tests work existence and flags +6 mask 0x1 clear. Source: [eu/src/overlays/ov035/calls/IsAreaSceneStartupComplete.c:1-10](../src/overlays/ov035/calls/IsAreaSceneStartupComplete.c).
- Area scene constructor obtains TaskObject work and initializes the halfword at +6 to 0x23, including mask 1. Source: [src/ov035/shared_engine/InitMovieSceneWork_020ba3e0.c:36-50](../../src/ov035/shared_engine/InitMovieSceneWork_020ba3e0.c).
- EU installer binds callback slot 1 to this exact predicate. Source: [eu/src/overlays/ov035/calls/InitMovieSourceOps.c:1-13](../src/overlays/ov035/calls/InitMovieSourceOps.c).
- Startup state uses the identical named global, waits for panel readiness, clears exactly mask 1, clears the task signal and advances to state 5. Source: [eu/src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c:8-20](../src/overlays/ov040/calls/AreaSceneState_WaitForPanelReady.c).

Contract limits:

- The cross-overlay writer is connected by identical global owner, not a coincident work offset.
- Startup completion means this explicit writer/flag transition, not completion of every child resource.
- AreaSceneOnLeaveClearFlag2 was not the writer for mask 1; it clears mask 2 and is corrected separately.

## RequestAreaSceneExit

Identity: `ov035:020ba9ac`, THUMB, native extent 24 bytes. EU source: [eu/src/overlays/ov035/calls/RequestAreaSceneExit.c](../src/overlays/ov035/calls/RequestAreaSceneExit.c).

```c
void RequestAreaSceneExit(u8 value);
```

- Owner: Area scene's gMovieContextState shared explicitly with overlay040's state handlers.
- Inputs: Mode byte, stored at work +0x1c and subsequently read signed by transition handlers.
- Result and effects: Void; sets request mask 0x4000 at flags +6.
- Lifetime: Requests a later state transition; does not free/unload the scene in this call.

Evidence:

- Stores the supplied mode byte and sets exactly flags mask 0x4000. Source: [eu/src/overlays/ov035/calls/RequestAreaSceneExit.c:1-8](../src/overlays/ov035/calls/RequestAreaSceneExit.c).
- The running state reads the identical global owner's 0x4000 mask, pauses field entries, sets highlight and returns state 14. Source: [eu/src/overlays/ov040/calls/UpdateAreaSceneState.c:62-68](../src/overlays/ov040/calls/UpdateAreaSceneState.c).
- The exit sequence waits for screen idle and begins fade-out using the signed mode byte at the same owner's +0x1c. Source: [eu/src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c:1-17](../src/overlays/ov040/calls/AreaSceneState_BeginFadeOut.c).
- The request operation is installed at session callback slot 3; it is not a movie-reader method. Source: [src/ov035/shared_engine/InitMovieSourceOps_020bad94.c:29-41](../../src/ov035/shared_engine/InitMovieSourceOps_020bad94.c).

Contract limits:

- Mask 0x4000 is a request consumed later, not a synchronous completion result.
- The numerical mode meanings are not named; u8 storage and later signed reads are retained.

## Event2DSceneOnLeaveClearFlag2

Identity: `ov036:020bc3f4`, ARM, native extent 36 bytes. EU source: [eu/src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c](../src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c).

```c
void Event2DSceneOnLeaveClearFlag2(void);
```

- Owner: Event2D work pointed to by the second word of data_ov036_020c3940.
- Inputs: No logical input; installed as SessionState callbacks[2].
- Result and effects: Void callback; clears mask 0x2 of its scene flags at +6.
- Lifetime: No allocations released and no borrowed pointer returned.

Evidence:

- Clears only mask 0x2 in the exact Event2D work owner. Source: [eu/src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c:1-8](../src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c).
- EU installer binds shared bc3d4 to this exact ARM function at EU bc3f4. Source: [eu/src/overlays/ov036/calls/InitPanelCallbackTable.c:1-11](../src/overlays/ov036/calls/InitPanelCallbackTable.c).
- Installer stores the function in callback index 2. Source: [src/ov036/panel_state/InitPanelCallbackTable_020bc4a8.c:19-30](../../src/ov036/panel_state/InitPanelCallbackTable_020bc4a8.c).
- Session callback slot 2 is an optional onLeave(void) hook invoked only after slot 1 canLeave permits leaving. The caller discards its return word. Source: [src/ov001/field_manager/LeaveFieldMenu_02061fc0.c:59-71](../../src/ov001/field_manager/LeaveFieldMenu_02061fc0.c).

Contract limits:

- The lifecycle onLeave role is proven; the numeric flag remains explicit.
- This does not clear the panel ScriptVm, text-window wait block or other actors with similar offsets.

## AreaSceneOnLeaveClearFlag2

Identity: `ov035:020ba994`, THUMB, native extent 24 bytes. EU source: [eu/src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c](../src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c).

```c
u32 AreaSceneOnLeaveClearFlag2(void);
```

- Owner: Area scene's gMovieContextState, not a video-reader context.
- Inputs: No logical input; installed as SessionState callbacks[2].
- Result and effects: Clears mask 0x2 at flags +6 and returns the resulting flags word in the native implementation; onLeave consumer discards that return.
- Lifetime: No allocation release, work clear or owner destruction.

Evidence:

- Clears mask 0x2, not the startup predicate's mask 0x1, and returns the updated flags word. Source: [eu/src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c:9-16](../src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c).
- EU aliases installer op2 to this function. Source: [eu/src/overlays/ov035/calls/InitMovieSourceOps.c:1-13](../src/overlays/ov035/calls/InitMovieSourceOps.c).
- The function is stored at session callback index 2. Source: [src/ov035/shared_engine/InitMovieSourceOps_020bad94.c:29-41](../../src/ov035/shared_engine/InitMovieSourceOps_020bad94.c).
- Session callback slot 2 is an optional onLeave(void) hook invoked only after slot 1 canLeave permits leaving. The caller discards its return word. Source: [src/ov001/field_manager/LeaveFieldMenu_02061fc0.c:59-71](../../src/ov001/field_manager/LeaveFieldMenu_02061fc0.c).

Contract limits:

- Corrects an existing misleading descriptive name and does not count as a numeric-function closure.
- This native u32 return is preserved, while the session callback's logical return is ignored.
- Does not clear the separate startup flag 0x1.


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetHudGauge0BlinkActive.c StageScriptExpr_GetHudGauge0BlinkActive --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetExtraMemberIndex.c GetExtraMemberIndex --thumb
python tools/verify_idx.py src/overlays/ov021/calls/FreeSlotTrackerUnitSlots.c FreeSlotTrackerUnitSlots --thumb
python tools/verify_idx.py src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c GetOv030SceneReferenceAxis --thumb
python tools/verify_idx.py src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c GroupSceneOnLeaveClearFlag2 --thumb
python tools/verify_idx.py src/overlays/ov035/calls/IsAreaSceneStartupComplete.c IsAreaSceneStartupComplete --thumb
python tools/verify_idx.py src/overlays/ov035/calls/RequestAreaSceneExit.c RequestAreaSceneExit --thumb
python tools/verify_idx.py src/overlays/ov036/calls/Event2DSceneOnLeaveClearFlag2.c Event2DSceneOnLeaveClearFlag2
python tools/verify_idx.py src/overlays/ov035/calls/AreaSceneOnLeaveClearFlag2.c AreaSceneOnLeaveClearFlag2 --thumb
bash tools/gate.sh
```
