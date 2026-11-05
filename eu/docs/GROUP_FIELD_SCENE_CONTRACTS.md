# Group field scene lifecycle and member helpers

This document records 11 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The group field scene uses its own TaskObject descriptor and startup-flag writer. Its state dispatcher treats signed negative handler results as retaining the current state and flag 0x8000 as requesting immediate dispatch. The save-and-exit state saves actor spawn data before releasing field/session context and restoring VRAM/heap state. Task work and child/group allocations remain separate owners.

The group accessor follows field-object +4 to its context, then returns context +0xcc plus the signed member-work group index times 0x1e0. The member-work accessor returns field-object +0xec. Both return borrowed storage, with no range or NULL validation. The owner +4/context view must not be applied to unrelated actor types.

Resuming movement changes specific packed counters: group +8 bits 6..15 become zero, bits 22..31 become 90, and the member movement word +0x30 becomes 0x1000. Other packed bits are retained. Consumers decrement these counters per update; a wall-clock duration is not established.

Hop velocity is computed from the row-definition speed and one of 16 horizontal directions, with constant Y = -0x8f. It is a velocity/delta rather than an absolute position. The four-way weighted helper reads four byte weights at row +0x1b and returns an index or -1 through its callee, despite its current void declaration. Preserve the existing inclusive cumulative comparison until a separate behavior change is intended.

Member-work bit 13 records a linked-child spawn event. Unlinking adjusts neighbors without clearing it, so the getter is a retained spawn-marker predicate, not proof of current chain membership. The normal update step is 0x1000; a nonzero mode suppresses the documented subset of scene updates while retaining party/actor-callback updates.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov032:020bb2a4` | THUMB | `func_ov032_020bb2a4` | `GroupSceneState_SaveActorPosesAndExit` | [eu/src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c](../src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c) |
| `ov032:020bb36c` | THUMB | `func_ov032_020bb36c` | `DrawOv032FieldScene` | [eu/src/overlays/ov032/calls/DrawOv032FieldScene.c](../src/overlays/ov032/calls/DrawOv032FieldScene.c) |
| `ov032:020bb388` | THUMB | `func_ov032_020bb388` | `UpdateOv032FieldScene` | [eu/src/overlays/ov032/calls/UpdateOv032FieldScene.c](../src/overlays/ov032/calls/UpdateOv032FieldScene.c) |
| `ov032:020bb468` | THUMB | `func_ov032_020bb468` | `CreateOv032FieldSceneTask` | [eu/src/overlays/ov032/calls/CreateOv032FieldSceneTask.c](../src/overlays/ov032/calls/CreateOv032FieldSceneTask.c) |
| `ov032:020bb480` | THUMB | `func_ov032_020bb480` | `IsOv032SceneStartupComplete` | [eu/src/overlays/ov032/calls/IsOv032SceneStartupComplete.c](../src/overlays/ov032/calls/IsOv032SceneStartupComplete.c) |
| `ov032:020bbc5c` | THUMB | `func_ov032_020bbc5c` | `ResumeGroupMovementWithLockCounter` | [eu/src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c](../src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c) |
| `ov032:020bbc80` | THUMB | `func_ov032_020bbc80` | `GetObjectGroup` | [eu/src/overlays/ov032/calls/GetObjectGroup.c](../src/overlays/ov032/calls/GetObjectGroup.c) |
| `ov032:020bbc98` | THUMB | `func_ov032_020bbc98` | `GetGroupMemberWork` | [eu/src/overlays/ov032/auto/GetGroupMemberWork.c](../src/overlays/ov032/auto/GetGroupMemberWork.c) |
| `ov032:020bbca0` | THUMB | `func_ov032_020bbca0` | `ComputeGroupHopVelocity` | [eu/src/overlays/ov032/calls/ComputeGroupHopVelocity.c](../src/overlays/ov032/calls/ComputeGroupHopVelocity.c) |
| `ov032:020bbf40` | THUMB | `func_ov032_020bbf40` | `PickRowFourWayWeightedIndex` | [eu/src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c](../src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c) |
| `ov032:020bf47c` | THUMB | `func_ov032_020bf47c` | `HasGroupChainSpawnMarker` | [eu/src/overlays/ov032/calls/HasGroupChainSpawnMarker.c](../src/overlays/ov032/calls/HasGroupChainSpawnMarker.c) |

## GroupSceneState_SaveActorPosesAndExit

Identity: `ov032:020bb2a4`, THUMB, native extent 172 bytes (including any configured pool). Previous symbol: `func_ov032_020bb2a4`.

EU entrypoint: [eu/src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c](../src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c).

```c
unsigned int GroupSceneState_SaveActorPosesAndExit(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for permitted panel transition unless flag0x10 bypasses it, saves actor spawn data, releases field/session context, restores VRAM/heap state and immediately advances to state17. Source: [eu/src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c:1-62](../src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c:1-62](../src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c).
- Scene dispatcher stores nonnegative handler result and repeats for0x8000. Source: [eu/src/overlays/ov032/calls/RunSceneStateMachine_020ba7b0.c:1-6](../src/overlays/ov032/calls/RunSceneStateMachine_020ba7b0.c).

## DrawOv032FieldScene

Identity: `ov032:020bb36c`, THUMB, native extent 26 bytes (including any configured pool). Previous symbol: `func_ov032_020bb36c`.

EU entrypoint: [eu/src/overlays/ov032/calls/DrawOv032FieldScene.c](../src/overlays/ov032/calls/DrawOv032FieldScene.c).

```c
void DrawOv032FieldScene(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates active camera mode with argument1, draws visible scene slots and event callbacks, updates actor billboards and invokes the final field draw hook. Source: [eu/src/overlays/ov032/calls/DrawOv032FieldScene.c:1-15](../src/overlays/ov032/calls/DrawOv032FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov032/calls/DrawOv032FieldScene.c:1-15](../src/overlays/ov032/calls/DrawOv032FieldScene.c).
- Own scene frame dispatcher selects update and draw from flags. Source: [eu/src/overlays/ov032/calls/RunSceneStateMachine_020ba7b0.c:1-6](../src/overlays/ov032/calls/RunSceneStateMachine_020ba7b0.c).

## UpdateOv032FieldScene

Identity: `ov032:020bb388`, THUMB, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov032_020bb388`.

EU entrypoint: [eu/src/overlays/ov032/calls/UpdateOv032FieldScene.c](../src/overlays/ov032/calls/UpdateOv032FieldScene.c).

```c
void UpdateOv032FieldScene(s32 keepAlive);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Always updates party entries and actor callbacks. When mode is zero also updates scene animation, field objects, stage and prize orbs. Source: [eu/src/overlays/ov032/calls/UpdateOv032FieldScene.c:1-21](../src/overlays/ov032/calls/UpdateOv032FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov032/calls/UpdateOv032FieldScene.c:1-21](../src/overlays/ov032/calls/UpdateOv032FieldScene.c).

Contract limits:

- The fixed timestep is0x1000 (one fx32 unit), not a channel mask.

## CreateOv032FieldSceneTask

Identity: `ov032:020bb468`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov032_020bb468`.

EU entrypoint: [eu/src/overlays/ov032/calls/CreateOv032FieldSceneTask.c](../src/overlays/ov032/calls/CreateOv032FieldSceneTask.c).

```c
void CreateOv032FieldSceneTask(int arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates this overlay's own scene TaskObject descriptor and stores the returned task handle. Source: [eu/src/overlays/ov032/calls/CreateOv032FieldSceneTask.c:1-5](../src/overlays/ov032/calls/CreateOv032FieldSceneTask.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [src/ov032/shared_engine/MobiClip_SrcOpen_020bb448.c:1-7](../../src/ov032/shared_engine/MobiClip_SrcOpen_020bb448.c).

Contract limits:

- This is field scene task creation; the inherited MobiClip source filename does not establish video behavior.

## IsOv032SceneStartupComplete

Identity: `ov032:020bb480`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov032_020bb480`.

EU entrypoint: [eu/src/overlays/ov032/calls/IsOv032SceneStartupComplete.c](../src/overlays/ov032/calls/IsOv032SceneStartupComplete.c).

```c
BOOL IsOv032SceneStartupComplete(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false if own work is absent; otherwise returns true when startup flag0x1 is clear. Source: [eu/src/overlays/ov032/calls/IsOv032SceneStartupComplete.c:1-15](../src/overlays/ov032/calls/IsOv032SceneStartupComplete.c).
- This overlay's own startup-completion state clears exactly flag0x1 before entering its running state. Source: [src/ov032/object_group/CompleteGroupTransition_020baad0.c:1-22](../../src/ov032/object_group/CompleteGroupTransition_020baad0.c).

Contract limits:

- Evidence is from each own scene, not from matching offsets in other owners.

## ResumeGroupMovementWithLockCounter

Identity: `ov032:020bbc5c`, THUMB, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov032_020bbc5c`.

EU entrypoint: [eu/src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c](../src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c).

```c
u32 ResumeGroupMovementWithLockCounter(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Clears packed counter bits6..15 at group+8, sets bits22..31 to90 and restores member movement value+0x30 to0x1000. Source: [eu/src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c:1-16](../src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c).
- Counter at bits6..15 ticks down and calls this helper when it expires with movement value0; bits22..31 also tick down. Source: [src/ov032/unclassified_helpers/TickFieldObjectCounters_020bf790.c:1-55](../../src/ov032/unclassified_helpers/TickFieldObjectCounters_020bf790.c).
- Also used after completing the respawn movement state. Source: [eu/src/overlays/ov032/calls/UpdateRespawningGroupMember.c:1-134](../src/overlays/ov032/calls/UpdateRespawningGroupMember.c).

Contract limits:

- Preserves the other packed state bits. Counter units are update ticks, not proven wall time.

## GetObjectGroup

Identity: `ov032:020bbc80`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov032_020bbc80`.

EU entrypoint: [eu/src/overlays/ov032/calls/GetObjectGroup.c](../src/overlays/ov032/calls/GetObjectGroup.c).

```c
u8 * GetObjectGroup(void *param0);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns owner+4 context group array at+0xcc indexed by signed member work+2, stride0x1e0. Source: [eu/src/overlays/ov032/calls/GetObjectGroup.c:1-9](../src/overlays/ov032/calls/GetObjectGroup.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov032/calls/GetObjectGroup.c:1-9](../src/overlays/ov032/calls/GetObjectGroup.c).
- EU wrapper maps helper to native ObjectGroup getter and separate member-work getter. Source: [eu/src/overlays/ov032/calls/ApplyGroupLeaderHit.c:1-14](../src/overlays/ov032/calls/ApplyGroupLeaderHit.c).
- Native caller uses returned group for group members and group action state. Source: [src/ov032/object_group/ApplyGroupLeaderHit_020bfba4.c:1-154](../../src/ov032/object_group/ApplyGroupLeaderHit_020bfba4.c).

Contract limits:

- Negative or out-of-range index is not checked.

## GetGroupMemberWork

Identity: `ov032:020bbc98`, THUMB, native extent 6 bytes (including any configured pool). Previous symbol: `func_ov032_020bbc98`.

EU entrypoint: [eu/src/overlays/ov032/auto/GetGroupMemberWork.c](../src/overlays/ov032/auto/GetGroupMemberWork.c).

```c
u8 * GetGroupMemberWork(void *param0);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns field object's member-work pointer at+0xec. Source: [eu/src/overlays/ov032/auto/GetGroupMemberWork.c:1-2](../src/overlays/ov032/auto/GetGroupMemberWork.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [src/ov032/leaf_research/func_ov032_020bbc78.c:1-5](../../src/ov032/leaf_research/func_ov032_020bbc78.c).
- EU wrapper maps helper to the member-work accessor. Source: [eu/src/overlays/ov032/calls/ApplyGroupLeaderHit.c:1-14](../src/overlays/ov032/calls/ApplyGroupLeaderHit.c).
- Caller uses returned GroupMemberWork with its exact group accessor. Source: [src/ov032/object_group/ApplyGroupLeaderHit_020bfba4.c:1-154](../../src/ov032/object_group/ApplyGroupLeaderHit_020bfba4.c).

## ComputeGroupHopVelocity

Identity: `ov032:020bbca0`, THUMB, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov032_020bbca0`.

EU entrypoint: [eu/src/overlays/ov032/calls/ComputeGroupHopVelocity.c](../src/overlays/ov032/calls/ComputeGroupHopVelocity.c).

```c
void ComputeGroupHopVelocity(void *work,int index,int angle,int *position);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Builds16-way horizontal velocity from row definition speed and direction index; writes constant Y=-0x8f. Source: [eu/src/overlays/ov032/calls/ComputeGroupHopVelocity.c:1-20](../src/overlays/ov032/calls/ComputeGroupHopVelocity.c).
- Writes its output into moveDelta and passes it as hop velocity. Source: [eu/src/overlays/ov032/calls/UpdateRespawningGroupMember.c:1-134](../src/overlays/ov032/calls/UpdateRespawningGroupMember.c).
- Evaluates direction indices0..15 with the same helper. Source: [src/ov032/unclassified_helpers/FindFarthestOpenDirection_020bcb74.c:1-30](../../src/ov032/unclassified_helpers/FindFarthestOpenDirection_020bcb74.c).
- Horizontal magnitude comes from first row-definition word. Source: [src/ov032/leaf_research/func_ov032_020bbc30.c:1-8](../../src/ov032/leaf_research/func_ov032_020bbc30.c).

Contract limits:

- Output is a velocity/delta, not an absolute world position. No valid-range checks are added.

## PickRowFourWayWeightedIndex

Identity: `ov032:020bbf40`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov032_020bbf40`.

EU entrypoint: [eu/src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c](../src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c).

```c
void PickRowFourWayWeightedIndex(void *param0, s32 param1);
```

The native void declaration hides a returned chosen index or -1 from the weighted chooser. No prototype change is included in this rename plan.

Demonstrated behavior and evidence:

- Looks up the row definition and performs a weighted draw over its four bytes at+0x1b. Source: [eu/src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c:1-9](../src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c:1-9](../src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c).
- EU alias selects the count-and-weight random chooser. Source: [eu/src/overlays/ov032/calls/PickWeightedIndex.c:1-3](../src/overlays/ov032/calls/PickWeightedIndex.c).
- Returns the chosen index or-1; sums byte weights and samples the total. Source: [src/ov032/unclassified_helpers/PickWeightedIndex_020bbe84.c:1-33](../../src/ov032/unclassified_helpers/PickWeightedIndex_020bbe84.c).

Contract limits:

- The selected direction/index interpretation requires its caller; preserves the original inclusive cumulative comparison.

Additional native ABI observations:

- Current wrapper is void and ignores returned R0. Actual leaf tail-call may expose the chosen index to callers; verify before changing return type.

## HasGroupChainSpawnMarker

Identity: `ov032:020bf47c`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov032_020bf47c`.

EU entrypoint: [eu/src/overlays/ov032/calls/HasGroupChainSpawnMarker.c](../src/overlays/ov032/calls/HasGroupChainSpawnMarker.c).

```c
u32 HasGroupChainSpawnMarker(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns normalized bit13 of the object's member-work word+8. Source: [eu/src/overlays/ov032/calls/HasGroupChainSpawnMarker.c:1-9](../src/overlays/ov032/calls/HasGroupChainSpawnMarker.c).
- Sets bit0x2000 after linking a newly spawned chain child to its predecessor. Source: [src/ov032/object_group/SpawnRowChainMembers_020bd288.c:1-116](../../src/ov032/object_group/SpawnRowChainMembers_020bd288.c).
- Unlink adjusts the linked-list neighbors without clearing this marker. Source: [src/ov032/object_group/UnlinkGroupMember_020bd518.c:1-62](../../src/ov032/object_group/UnlinkGroupMember_020bd518.c).

Contract limits:

- A retained spawn marker is not proof of current chain membership.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c GroupSceneState_SaveActorPosesAndExit --thumb
python tools/verify_idx.py src/overlays/ov032/calls/DrawOv032FieldScene.c DrawOv032FieldScene --thumb
python tools/verify_idx.py src/overlays/ov032/calls/UpdateOv032FieldScene.c UpdateOv032FieldScene --thumb
python tools/verify_idx.py src/overlays/ov032/calls/CreateOv032FieldSceneTask.c CreateOv032FieldSceneTask --thumb
python tools/verify_idx.py src/overlays/ov032/calls/IsOv032SceneStartupComplete.c IsOv032SceneStartupComplete --thumb
python tools/verify_idx.py src/overlays/ov032/calls/ResumeGroupMovementWithLockCounter.c ResumeGroupMovementWithLockCounter --thumb
python tools/verify_idx.py src/overlays/ov032/calls/GetObjectGroup.c GetObjectGroup --thumb
python tools/verify_idx.py src/overlays/ov032/auto/GetGroupMemberWork.c GetGroupMemberWork --thumb
python tools/verify_idx.py src/overlays/ov032/calls/ComputeGroupHopVelocity.c ComputeGroupHopVelocity --thumb
python tools/verify_idx.py src/overlays/ov032/calls/PickRowFourWayWeightedIndex.c PickRowFourWayWeightedIndex --thumb
python tools/verify_idx.py src/overlays/ov032/calls/HasGroupChainSpawnMarker.c HasGroupChainSpawnMarker --thumb
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
