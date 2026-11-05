# Stage script, camera and effect-source services

This document records 60 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

This overlay contains several owners. The stage interpreter, input records, camera dispatcher, effect task and entry source are separate interfaces. Equal offsets in these owners do not establish a shared structure.

## Stage interpreter

The instruction header occupies four bytes, followed by operands. `GetStageScriptOpcode` forms code base + code offset + PC, and `GetStageScriptOperands` advances past the header. The two data-offset entrypoints use the data buffer at context +0x0c and retain separate native identities. These pointers borrow the active script allocation; the helpers do not allocate, validate offsets or extend its lifetime.

The result protocol is defined by `RunScriptThread`, and differs from the field/panel ScriptVm protocol:

| Handler result | Interpreter action |
| --- | --- |
| 0 or 8 | Advance by instruction length and continue; zero length finishes with result 4. |
| 1 | Set PC to jumpTarget and yield. |
| 2 | Set PC to jumpTarget and continue. |
| 3 | Yield without advancing PC. |
| 4 | Reset registerIndex and stop. |
| 5 | Advance PC; if nested, pop the return address and yield; otherwise finish with 4. |
| 6 | Advance PC, push the return address, jump to jumpTarget and continue. |
| 7 | Store jumpTarget in the selected register, reset registerIndex and yield without changing PC. |

Tagged integer results use tag 1. Fixed-point results use tag 0x10 and raw values with 12 fractional bits. Vector expressions read the context vector at +0x34 and write the tagged result at +0x2c/+0x30. Keep the existing four-entry call stack, evaluation order and native unchecked offsets visible when designing the portable bytecode API. The no-op opcode handlers participate in this protocol; replacing their table entries with NULL would change dispatch.

## Effect tasks and entry sources

The constructor and dispatchers prove the following separate prefixes. The source review includes the exact EU stores in `CreateEffectTask` at 020acf1a/1e/22; private labels that place cleanup at task +0x24 are misleading.

| Owner | Offset | Proven operation |
| --- | --- | --- |
| ScriptTask | 0x20 | Release owned source resources, called by ReleaseMemberResources. |
| ScriptTask | 0x24 | Update(container, task, fx32 step), called by InvokeMemberUpdateCallbacks. |
| ScriptTask | 0x28 | Draw(container, task), called by InvokeMemberDrawCallbacks. |
| ScriptTask | 0x30 | Stop/reset notification, called by InvokeMemberCleanupCallbacks. |
| EntryPool/source | 0x1c | Update source entries with the supplied step. |
| EntryPool/source | 0x20 | Draw source entries. |
| EntryPool/source | 0x24 | Release source allocations. |

Release entrypoints describe the allocations their bodies release, not automatic destruction of the enclosing owner. The individual records below identify the actual dispatch targets and retained fields. Callback return values and unused native register slots need their registration/dispatcher contract before becoming a portable API.

## Input and character sound cues

The field-button record stores its owner entry index at +0x14, direction-active state at +6 and repeat-pending state at +0x17. Initialization clears the identified fields rather than the whole record. The getter that polls the current submode has that side effect even when the result is used as a predicate.

The character sound cue loader reads `ba/ch/se.p2`. Its groups contain timed sound choices consumed by `PlayCueGroupSounds`; the old PathGraph/PathPoint labels do not establish pathfinding data. The callback at cue-table +0x18 returns a borrowed actor-position pointer used to update a sound handle. It is not a volume getter. Resource lookup, active-handle replacement and owned cue-table allocation are described separately below.

## Camera dispatcher and view queries

The active submode selects an overlay-specific camera work owner. `GetActiveSubModeCameraWork` does not establish a universal camera structure. The culling-origin getter returns a borrowed vector subtracted from the tested point or shape center; a rendered-eye meaning is not proven for every backend.

The plane-normal getter provides four contiguous VecFx32 normals for demonstrated modes 0, 2 and 3. Mode 1 uses separate X/Y bounds checks. The native getter retains a case-1 branch to overlay043 ARM address 020bd0ac; the same address is inside Thumb code in overlay042. The normal mode-1 culling path avoids that getter. Preserve this precondition and bank identity rather than inventing normals to make a uniform interface. The source review saved both bank listings and ROM hashes.

Mode 2 first performs a negative-world-Z distance check, then a four-plane test. Query margin/threshold arguments are not plane counts. The earlier mode-2 binding collision at 020bd20c has already been repaired: the logical target belongs to overlay043 (`IsShapeInViewDepth`), not overlay039's input dispatcher. The byte-exact name work does not normalize backend clipping rules or repair the legacy unreachable getter branch.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov021:020a7480` | THUMB | `func_ov021_020a7480` | `InitFieldButtonForEntryIndex` | [eu/src/overlays/ov021/auto/InitFieldButtonForEntryIndex.c](../src/overlays/ov021/auto/InitFieldButtonForEntryIndex.c) |
| `ov021:020a7510` | THUMB | `func_ov021_020a7510` | `ClearFieldButtonInput` | [eu/src/overlays/ov021/calls/ClearFieldButtonInput.c](../src/overlays/ov021/calls/ClearFieldButtonInput.c) |
| `ov021:020a7524` | THUMB | `func_ov021_020a7524` | `GetFieldDirectionActiveAndPollSubMode` | [eu/src/overlays/ov021/calls/GetFieldDirectionActiveAndPollSubMode.c](../src/overlays/ov021/calls/GetFieldDirectionActiveAndPollSubMode.c) |
| `ov021:020a7530` | THUMB | `func_ov021_020a7530` | `GetFieldDirectionActive` | [eu/src/overlays/ov021/calls/GetFieldDirectionActive.c](../src/overlays/ov021/calls/GetFieldDirectionActive.c) |
| `ov021:020a755c` | THUMB | `func_ov021_020a755c` | `GetFieldShortcutInjectionFlag` | [eu/src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c](../src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c) |
| `ov021:020a7564` | THUMB | `func_ov021_020a7564` | `GetSummedFieldDirectionAngle` | [eu/src/overlays/ov021/auto/GetSummedFieldDirectionAngle.c](../src/overlays/ov021/auto/GetSummedFieldDirectionAngle.c) |
| `ov021:020a7ca8` | THUMB | `func_ov021_020a7ca8` | `GetCueOwnerPosition` | [eu/src/overlays/ov021/calls/GetCueOwnerPosition.c](../src/overlays/ov021/calls/GetCueOwnerPosition.c) |
| `ov021:020a7cb0` | THUMB | `func_ov021_020a7cb0` | `OpenCharacterSoundCueArchive` | [eu/src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c](../src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c) |
| `ov021:020a7ce8` | THUMB | `LoadPathGraph` | `LoadCharacterSoundCueTable` | [eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c](../src/overlays/ov021/calls/LoadCharacterSoundCueTable.c) |
| `ov021:020a81d8` | THUMB | `func_ov021_020a81d8` | `ReplaceActiveCueHandle` | [eu/src/overlays/ov021/calls/ReplaceActiveCueHandle.c](../src/overlays/ov021/calls/ReplaceActiveCueHandle.c) |
| `ov021:020aafe4` | THUMB | `func_ov021_020aafe4` | `UpdateEntrySource` | [eu/src/overlays/ov021/calls/UpdateEntrySource.c](../src/overlays/ov021/calls/UpdateEntrySource.c) |
| `ov021:020aaff4` | THUMB | `func_ov021_020aaff4` | `DrawEntrySource` | [eu/src/overlays/ov021/calls/DrawEntrySource.c](../src/overlays/ov021/calls/DrawEntrySource.c) |
| `ov021:020ac168` | THUMB | `func_ov021_020ac168` | `InitHitResultHeader` | [eu/src/overlays/ov021/auto/InitHitResultHeader.c](../src/overlays/ov021/auto/InitHitResultHeader.c) |
| `ov021:020ad064` | THUMB | `func_ov021_020ad064` | `ReleaseEffectTaskSource` | [eu/src/overlays/ov021/calls/ReleaseEffectTaskSource.c](../src/overlays/ov021/calls/ReleaseEffectTaskSource.c) |
| `ov021:020ad078` | THUMB | `func_ov021_020ad078` | `DispatchEffectTaskSourceKind` | [eu/src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c](../src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c) |
| `ov021:020ad4b4` | THUMB | `func_ov021_020ad4b4` | `ResetCurrentScriptTaskSlots` | [eu/src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c](../src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c) |
| `ov021:020adca0` | THUMB | `func_ov021_020adca0` | `UpdateEffectTaskSource` | [eu/src/overlays/ov021/calls/UpdateEffectTaskSource.c](../src/overlays/ov021/calls/UpdateEffectTaskSource.c) |
| `ov021:020adcac` | THUMB | `func_ov021_020adcac` | `DrawEffectTaskSource` | [eu/src/overlays/ov021/calls/DrawEffectTaskSource.c](../src/overlays/ov021/calls/DrawEffectTaskSource.c) |
| `ov021:020adfd8` | THUMB | `func_ov021_020adfd8` | `ReleaseScriptedEffectTaskExtraResources` | [eu/src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c](../src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c) |
| `ov021:020ae738` | THUMB | `func_ov021_020ae738` | `UpdateEffectEntrySourceAdapter` | [eu/src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c](../src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c) |
| `ov021:020ae740` | THUMB | `func_ov021_020ae740` | `DrawEffectEntrySourceAdapter` | [eu/src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c](../src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c) |
| `ov021:020ae8ac` | THUMB | `func_ov021_020ae8ac` | `DrawModelOutsideCameraProximity` | [eu/src/overlays/ov021/calls/DrawModelOutsideCameraProximity.c](../src/overlays/ov021/calls/DrawModelOutsideCameraProximity.c) |
| `ov021:020ae944` | THUMB | `func_ov021_020ae944` | `SetModelPolygonIdAndDrawOutsideCameraProximity` | [eu/src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c](../src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c) |
| `ov021:020af3a0` | THUMB | `func_ov021_020af3a0` | `ReleaseActiveSubModeOverlay` | [eu/src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c](../src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c) |
| `ov021:020af408` | THUMB | `func_ov021_020af408` | `GetActiveSubMode` | [eu/src/overlays/ov021/calls/GetActiveSubMode.c](../src/overlays/ov021/calls/GetActiveSubMode.c) |
| `ov021:020af528` | THUMB | `func_ov021_020af528` | `UpdateActiveSubModeCamera` | [eu/src/overlays/ov021/calls/UpdateActiveSubModeCamera.c](../src/overlays/ov021/calls/UpdateActiveSubModeCamera.c) |
| `ov021:020af5d4` | THUMB | `func_ov021_020af5d4` | `GetActiveCameraCullingOrigin` | [eu/src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c](../src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c) |
| `ov021:020af614` | THUMB | `func_ov021_020af614` | `GetActiveSubModeCameraWork` | [eu/src/overlays/ov021/calls/GetActiveSubModeCameraWork.c](../src/overlays/ov021/calls/GetActiveSubModeCameraWork.c) |
| `ov021:020af71c` | THUMB | `func_ov021_020af71c` | `GetActiveCameraViewPlaneNormals` | [eu/src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c](../src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c) |
| `ov021:020af798` | THUMB | `func_ov021_020af798` | `IsPointWithinActiveCameraView` | [eu/src/overlays/ov021/calls/IsPointWithinActiveCameraView.c](../src/overlays/ov021/calls/IsPointWithinActiveCameraView.c) |
| `ov021:020af830` | THUMB | `func_ov021_020af830` | `HasDefaultSubModeCameraChangePending` | [eu/src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c](../src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c) |
| `ov021:020b0370` | THUMB | `func_ov021_020b0370` | `GetStageScriptOpcode` | [eu/src/overlays/ov021/calls/GetStageScriptOpcode.c](../src/overlays/ov021/calls/GetStageScriptOpcode.c) |
| `ov021:020b037c` | THUMB | `func_ov021_020b037c` | `GetStageScriptOperands` | [eu/src/overlays/ov021/calls/GetStageScriptOperands.c](../src/overlays/ov021/calls/GetStageScriptOperands.c) |
| `ov021:020b038c` | THUMB | `func_ov021_020b038c` | `ResolveStageScriptDataOffset` | [eu/src/overlays/ov021/auto/ResolveStageScriptDataOffset.c](../src/overlays/ov021/auto/ResolveStageScriptDataOffset.c) |
| `ov021:020b0a68` | THUMB | `func_ov021_020b0a68` | `StageExpr_FindFarthestFreeSlot` | [eu/src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c](../src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c) |
| `ov021:020b0b74` | THUMB | `func_ov021_020b0b74` | `StageScriptExpr_TestSessionFlag3713` | [eu/src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c](../src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c) |
| `ov021:020b0cfc` | THUMB | `func_ov021_020b0cfc` | `StageExpr_FindNearestFreeSlot` | [eu/src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c](../src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c) |
| `ov021:020b0d8c` | THUMB | `func_ov021_020b0d8c` | `StageExpr_FindFarthestFreeSlotAtOrAboveHeight` | [eu/src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c](../src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c) |
| `ov021:020b0fd4` | THUMB | `func_ov021_020b0fd4` | `StageExpr_GetSelectedCommandEntryId` | [eu/src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c](../src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c) |
| `ov021:020b111c` | THUMB | `func_ov021_020b111c` | `StageScriptExpr_GetVectorZ` | [eu/src/overlays/ov021/auto/StageScriptExpr_GetVectorZ.c](../src/overlays/ov021/auto/StageScriptExpr_GetVectorZ.c) |
| `ov021:020b1128` | THUMB | `func_ov021_020b1128` | `StageScriptExpr_GetVectorY` | [eu/src/overlays/ov021/auto/StageScriptExpr_GetVectorY.c](../src/overlays/ov021/auto/StageScriptExpr_GetVectorY.c) |
| `ov021:020b1134` | THUMB | `func_ov021_020b1134` | `StageScriptExpr_GetVectorX` | [eu/src/overlays/ov021/auto/StageScriptExpr_GetVectorX.c](../src/overlays/ov021/auto/StageScriptExpr_GetVectorX.c) |
| `ov021:020b1250` | THUMB | `func_ov021_020b1250` | `StageScriptExpr_GetSequenceId` | [eu/src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c](../src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c) |
| `ov021:020b1af4` | THUMB | `func_ov021_020b1af4` | `StageCmd_StoreCurrentMotionGridCellCenter` | [eu/src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c](../src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c) |
| `ov021:020b1c04` | THUMB | `func_ov021_020b1c04` | `StageScriptVec_GetActorNodePosition` | [eu/src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c](../src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c) |
| `ov021:020b1f54` | THUMB | `func_ov021_020b1f54` | `StageScriptVec_AddRandomHorizontalOffset` | [eu/src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c](../src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c) |
| `ov021:020b230c` | THUMB | `func_ov021_020b230c` | `StageScriptCmd_ScaleStageVector` | [eu/src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c](../src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c) |
| `ov021:020b23a0` | THUMB | `func_ov021_020b23a0` | `StageScriptExpr_StageVectorMagnitude` | [eu/src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c](../src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c) |
| `ov021:020b23fc` | THUMB | `func_ov021_020b23fc` | `StageScriptOp_End` | [eu/src/overlays/ov021/auto/StageScriptOp_End.c](../src/overlays/ov021/auto/StageScriptOp_End.c) |
| `ov021:020b245c` | THUMB | `func_ov021_020b245c` | `StageScriptOp_Call` | [eu/src/overlays/ov021/auto/StageScriptOp_Call.c](../src/overlays/ov021/auto/StageScriptOp_Call.c) |
| `ov021:020b2464` | THUMB | `func_ov021_020b2464` | `StageScriptOp_StoreJumpValueAndYield` | [eu/src/overlays/ov021/auto/StageScriptOp_StoreJumpValueAndYield.c](../src/overlays/ov021/auto/StageScriptOp_StoreJumpValueAndYield.c) |
| `ov021:020b246c` | THUMB | `func_ov021_020b246c` | `StageScriptOp_NoOp` | [eu/src/overlays/ov021/auto/StageScriptOp_NoOp.c](../src/overlays/ov021/auto/StageScriptOp_NoOp.c) |
| `ov021:020b2880` | THUMB | `func_ov021_020b2880` | `StageCmd_AttachActorToNamedStageNode` | [eu/src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c](../src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c) |
| `ov021:020b349c` | THUMB | `func_ov021_020b349c` | `StageScriptOp_JumpAndYield` | [eu/src/overlays/ov021/auto/StageScriptOp_JumpAndYield.c](../src/overlays/ov021/auto/StageScriptOp_JumpAndYield.c) |
| `ov021:020b34c8` | THUMB | `func_ov021_020b34c8` | `StageScriptOp_Jump` | [eu/src/overlays/ov021/auto/StageScriptOp_Jump.c](../src/overlays/ov021/auto/StageScriptOp_Jump.c) |
| `ov021:020b366c` | THUMB | `func_ov021_020b366c` | `StageScriptCmd_BeginActorWalkerMove` | [eu/src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c](../src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c) |
| `ov021:020b3750` | THUMB | `func_ov021_020b3750` | `StageScriptCmd_PlayActorAnimationSlot` | [eu/src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c](../src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c) |
| `ov021:020b38f4` | THUMB | `func_ov021_020b38f4` | `StageScriptCmd_TriggerSessionEffectKind1` | [eu/src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c](../src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c) |
| `ov021:020b48a0` | THUMB | `func_ov021_020b48a0` | `StageScriptOp_DefaultNoOp` | [eu/src/overlays/ov021/auto/StageScriptOp_DefaultNoOp.c](../src/overlays/ov021/auto/StageScriptOp_DefaultNoOp.c) |
| `ov021:020b4ac4` | THUMB | `func_ov021_020b4ac4` | `ResolveStageScriptCommandDataOffset` | [eu/src/overlays/ov021/auto/ResolveStageScriptCommandDataOffset.c](../src/overlays/ov021/auto/ResolveStageScriptCommandDataOffset.c) |

## InitFieldButtonForEntryIndex

Identity: `ov021:020a7480`, THUMB, native extent 10 bytes (including any configured pool). Previous symbol: `func_ov021_020a7480`.

EU entrypoint: [eu/src/overlays/ov021/auto/InitFieldButtonForEntryIndex.c](../src/overlays/ov021/auto/InitFieldButtonForEntryIndex.c).

```c
u32 InitFieldButtonForEntryIndex(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores the owner entry index at +0x14 and clears direction-active +6 and repeat-pending +0x17. Source: [src/ov021/leaf_research/func_ov021_020a7460.c:1-8](../../src/ov021/leaf_research/func_ov021_020a7460.c).
- Initializes each party entry tracker with its exact party-entry index. Source: [eu/src/overlays/ov001/calls/InitPartyState.c:1-89](../src/overlays/ov001/calls/InitPartyState.c).
- Identifies direction-active +6 and repeat-pending +0x17 in the same input prefix. Source: [src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c:1-64](../../src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c).

Contract limits:

- Does not clear the full input record.

## ClearFieldButtonInput

Identity: `ov021:020a7510`, THUMB, native extent 18 bytes (including any configured pool). Previous symbol: `func_ov021_020a7510`.

EU entrypoint: [eu/src/overlays/ov021/calls/ClearFieldButtonInput.c](../src/overlays/ov021/calls/ClearFieldButtonInput.c).

```c
u32 ClearFieldButtonInput(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Clears held/pressed/command/subcommand, flags, active byte and action-state byte while preserving entry index and angles. Source: [eu/src/overlays/ov021/calls/ClearFieldButtonInput.c:1-12](../src/overlays/ov021/calls/ClearFieldButtonInput.c).
- Uses this reset for a nonactive party entry before collecting alternate AI input. Source: [src/ov021/unclassified_helpers/UpdateFieldButton_020a746c.c:1-48](../../src/ov021/unclassified_helpers/UpdateFieldButton_020a746c.c).
- The input view identifies flags+8,pressed+0xc,held+0xe,command+0x10,subcommand+0x12,action state+0x15. Source: [src/ov021/unclassified_helpers/UpdateFieldButtonInput_020a70a8.c:1-240](../../src/ov021/unclassified_helpers/UpdateFieldButtonInput_020a70a8.c).

Contract limits:

- Does not reset timers/angle history or entry index; not a full struct initialization.

## GetFieldDirectionActiveAndPollSubMode

Identity: `ov021:020a7524`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020a7524`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetFieldDirectionActiveAndPollSubMode.c](../src/overlays/ov021/calls/GetFieldDirectionActiveAndPollSubMode.c).

```c
void GetFieldDirectionActiveAndPollSubMode(void * arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Calls the shared input-state helper with update=1, returning input active byte unless an idle submode completion poll suppresses it. Source: [src/ov021/library_nns_snd/AlarmCallback_020a7504.c:1-12](../../src/ov021/library_nns_snd/AlarmCallback_020a7504.c).
- Reads owner+6; when update is true and owner+0x14 is zero, a successful UpdateSubModeResult forces returned value zero. Source: [src/ov021/sub_mode/GetSubModeState_020a6ec0.c:1-19](../../src/ov021/sub_mode/GetSubModeState_020a6ec0.c).
- The same prefix identifies byte+6 as direction active. Source: [src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c:1-64](../../src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c).

Contract limits:

- The poll may have side effects; this is not a pure getter.
- The helper does not overwrite the stored active byte when suppressing the result.

## GetFieldDirectionActive

Identity: `ov021:020a7530`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020a7530`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetFieldDirectionActive.c](../src/overlays/ov021/calls/GetFieldDirectionActive.c).

```c
void GetFieldDirectionActive(void *list);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Calls the shared state helper with update=0. Source: [src/ov021/library_nitro_nns/NNS_FndInitListWithOffset0_020a7510.c:1-6](../../src/ov021/library_nitro_nns/NNS_FndInitListWithOffset0_020a7510.c).
- With update false, returns owner byte+6 without calling UpdateSubModeResult. Source: [src/ov021/sub_mode/GetSubModeState_020a6ec0.c:1-19](../../src/ov021/sub_mode/GetSubModeState_020a6ec0.c).
- The shared prefix identifies byte+6 as direction-active state. Source: [src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c:1-64](../../src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c).

Contract limits:

- Only returns the stored byte; no submode progress is polled.

## GetFieldShortcutInjectionFlag

Identity: `ov021:020a755c`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020a755c`.

EU entrypoint: [eu/src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c](../src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c).

```c
u32 GetFieldShortcutInjectionFlag(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns raw bit0 of field input flags+8. Source: [eu/src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c:1-2](../src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c).
- Shared body selected by exact EU aliases. Source: [src/ov021/leaf_research/func_ov021_020a753c.c:1-7](../../src/ov021/leaf_research/func_ov021_020a753c.c).
- EU wrapper selects field input handler. Source: [eu/src/overlays/ov021/calls/UpdateFieldButtonInput.c:1-12](../src/overlays/ov021/calls/UpdateFieldButtonInput.c).
- Sets bit0 exactly when shortcut selection injects pressed key0x400. Source: [src/ov021/unclassified_helpers/UpdateFieldButtonInput_020a70a8.c:1-240](../../src/ov021/unclassified_helpers/UpdateFieldButtonInput_020a70a8.c).
- Refresh clears bit0 before ordinary input processing. Source: [src/ov021/unclassified_helpers/RefreshInputState_020a6edc.c:1-44](../../src/ov021/unclassified_helpers/RefreshInputState_020a6edc.c).

Contract limits:

- Returns0or1. It does not itself report physical key state.

## GetSummedFieldDirectionAngle

Identity: `ov021:020a7564`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020a7564`.

EU entrypoint: [eu/src/overlays/ov021/auto/GetSummedFieldDirectionAngle.c](../src/overlays/ov021/auto/GetSummedFieldDirectionAngle.c).

```c
u32 GetSummedFieldDirectionAngle(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns the low16 sum of the input angle at +0 and camera-relative status/angle at +4. Source: [src/ov021/leaf_research/func_ov021_020a7544.c:1-9](../../src/ov021/leaf_research/func_ov021_020a7544.c).
- Defines angle+0 and status+4; updates them from direction buttons and the submode heading query. Source: [src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c:1-64](../../src/ov021/unclassified_helpers/UpdateDirectionInput_020a6f34.c).
- Consumes the returned value shifted by4 as a sine/cosine lookup index. Source: [eu/src/overlays/ov052/calls/TryLedgeClimb.c:1-506](../src/overlays/ov052/calls/TryLedgeClimb.c).

Contract limits:

- Wraps at16bits; no clamping or normalization beyond the low-halfword result.

## GetCueOwnerPosition

Identity: `ov021:020a7ca8`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020a7ca8`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetCueOwnerPosition.c](../src/overlays/ov021/calls/GetCueOwnerPosition.c).

```c
void * GetCueOwnerPosition();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Thin adapter forwards actor index to GetManagedActorPosition. Source: [eu/src/overlays/ov021/calls/GetCueOwnerPosition.c:1-3](../src/overlays/ov021/calls/GetCueOwnerPosition.c).
- Shared body selected by exact EU aliases. Source: [src/ov021/library_nitro_pxi/PXI_Init_020a7c88.c:1-5](../../src/ov021/library_nitro_pxi/PXI_Init_020a7c88.c).
- Loader installs this callback as owner position getter at cue-table+0x18. Source: [eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c:1-12](../src/overlays/ov021/calls/LoadCharacterSoundCueTable.c).
- Same cue-table field+0x18 is passed to the live sound-handle payload update. Private getVolume labels are not sufficient to infer scalar volume. Source: [src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c:1-139](../../src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c).

Contract limits:

- Real result is the managed actor position pointer, despite legacy void* spelling.

## OpenCharacterSoundCueArchive

Identity: `ov021:020a7cb0`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov021_020a7cb0`.

EU entrypoint: [eu/src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c](../src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c).

```c
void OpenCharacterSoundCueArchive(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Opens ba/ch/se.p2 container with resource kind0x11 and stores its handle for cue-table loading. Source: [eu/src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c:1-9](../src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c).
- Loads selection-specific data through this archive handle. Source: [eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c:1-12](../src/overlays/ov021/calls/LoadCharacterSoundCueTable.c).
- The loaded table layout is consumed as groups of timed sound cues. Source: [src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c:1-139](../../src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c).

Contract limits:

- The ba path component is retained literally; no expansion into an unproven story/battle concept.

## LoadCharacterSoundCueTable

Identity: `ov021:020a7ce8`, THUMB, native extent 568 bytes (including any configured pool). Previous symbol: `LoadPathGraph`.

EU entrypoint: [eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c](../src/overlays/ov021/calls/LoadCharacterSoundCueTable.c).

```c
void LoadCharacterSoundCueTable(PathGraph *graph, u32 kind, u32 selection);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- EU aliases bind shared archive and owner callbacks. Source: [eu/src/overlays/ov021/calls/LoadCharacterSoundCueTable.c:1-12](../src/overlays/ov021/calls/LoadCharacterSoundCueTable.c).
- Builds groups of linked timed entries with packed sound/volume records; installs playback callback14 and actor-position callback18. Source: [src/ov021/object_state/LoadPathGraph_020a7cc8.c:1-170](../../src/ov021/object_state/LoadPathGraph_020a7cc8.c).
- Exact loaded prefix is interpreted as CueTable(groups4,current24,etc), CueGroup(count2,items4), CueItem(time0,handle4,sounds8,modec,rangeD,channelE,flagsF), CueSound(soundId0,volume2). Source: [src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c:1-139](../../src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c).

Contract limits:

- Private PathGraph/PathPoint labels are misleading: file integer pairs narrow into soundID/volume halfwords. No geometric path role should be inferred.

## ReplaceActiveCueHandle

Identity: `ov021:020a81d8`, THUMB, native extent 42 bytes (including any configured pool). Previous symbol: `func_ov021_020a81d8`.

EU entrypoint: [eu/src/overlays/ov021/calls/ReplaceActiveCueHandle.c](../src/overlays/ov021/calls/ReplaceActiveCueHandle.c).

```c
unsigned int ReplaceActiveCueHandle(int work,unsigned int value,unsigned int *resultSlot);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Stops previous current sound handle if one exists, invokes cue playback callback with owner/selected ID/value/flags0, stores returned handle through resultSlot and retains that slot pointer as current. Source: [eu/src/overlays/ov021/calls/ReplaceActiveCueHandle.c:1-18](../src/overlays/ov021/calls/ReplaceActiveCueHandle.c).
- Native CueTable identifies owner1c,play14,current24,exclusiveId28. Source: [src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c:1-139](../../src/ov021/shared_engine/PlayCueGroupSounds_020a7fa4.c).

## UpdateEntrySource

Identity: `ov021:020aafe4`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov021_020aafe4`.

EU entrypoint: [eu/src/overlays/ov021/calls/UpdateEntrySource.c](../src/overlays/ov021/calls/UpdateEntrySource.c).

```c
void UpdateEntrySource(int entry,unsigned int value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If source and its callback+0x1c exist, invokes(source,step). Source: [eu/src/overlays/ov021/calls/UpdateEntrySource.c:1-9](../src/overlays/ov021/calls/UpdateEntrySource.c).
- Pool constructor installs DispatchEntryKindHandlers at+0x1c. Source: [eu/src/overlays/ov021/calls/InitEntryPool.c:1-11](../src/overlays/ov021/calls/InitEntryPool.c).
- Native EntryPool stores dispatch at1c and ProcessActiveEntries at20. Source: [src/ov021/object_state/InitEntryPool_020aa9c4.c:1-60](../../src/ov021/object_state/InitEntryPool_020aa9c4.c).

Contract limits:

- This owner is an EntryPool/source prefix, not a ScriptTask prefix.

## DrawEntrySource

Identity: `ov021:020aaff4`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov021_020aaff4`.

EU entrypoint: [eu/src/overlays/ov021/calls/DrawEntrySource.c](../src/overlays/ov021/calls/DrawEntrySource.c).

```c
void DrawEntrySource(int entry);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If source and its callback+0x20 exist invokes(source). Source: [eu/src/overlays/ov021/calls/DrawEntrySource.c:1-9](../src/overlays/ov021/calls/DrawEntrySource.c).
- Pool constructor binds ProcessActiveEntries at+0x20. Source: [eu/src/overlays/ov021/calls/InitEntryPool.c:1-11](../src/overlays/ov021/calls/InitEntryPool.c).
- The processor invokes per-entry draw handlers, including oriented models. Source: [src/ov021/unclassified_helpers/ProcessActiveEntries_020aaee0.c:1-26](../../src/ov021/unclassified_helpers/ProcessActiveEntries_020aaee0.c).

Contract limits:

- The callback role is proven from constructor+dispatcher, not offset analogy.

## InitHitResultHeader

Identity: `ov021:020ac168`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020ac168`.

EU entrypoint: [eu/src/overlays/ov021/auto/InitHitResultHeader.c](../src/overlays/ov021/auto/InitHitResultHeader.c).

```c
u32 InitHitResultHeader(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Clears flags at +0 and kind at +8. Source: [src/ov021/leaf_research/func_ov021_020ac148.c:1-7](../../src/ov021/leaf_research/func_ov021_020ac148.c).
- The typed result view identifies these fields and initializes them through this helper before writing contact data. Source: [src/ov021/object_state/BuildHitResult_020abb50.c:1-88](../../src/ov021/object_state/BuildHitResult_020abb50.c).

Contract limits:

- Does not clear unknown word+4, contact position, node or trailing payload.

## ReleaseEffectTaskSource

Identity: `ov021:020ad064`, THUMB, native extent 18 bytes (including any configured pool). Previous symbol: `func_ov021_020ad064`.

EU entrypoint: [eu/src/overlays/ov021/calls/ReleaseEffectTaskSource.c](../src/overlays/ov021/calls/ReleaseEffectTaskSource.c).

```c
void ReleaseEffectTaskSource(int self);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Releases source owned at task+0x50 according to its kind, then frees that source allocation. Source: [eu/src/overlays/ov021/calls/ReleaseEffectTaskSource.c:1-10](../src/overlays/ov021/calls/ReleaseEffectTaskSource.c).
- Constructor installs this function in task+0x20, the member release slot. Source: [eu/src/overlays/ov021/calls/CreateEffectTask.c:1-122](../src/overlays/ov021/calls/CreateEffectTask.c).
- Dispatcher invokes task+0x20 before freeing task resource arrays. Source: [src/ov021/object_state/ReleaseMemberResources_020acd8c.c:1-17](../../src/ov021/object_state/ReleaseMemberResources_020acd8c.c).

Contract limits:

- Task itself remains allocated; source pointer is not cleared.

## DispatchEffectTaskSourceKind

Identity: `ov021:020ad078`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020ad078`.

EU entrypoint: [eu/src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c](../src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c).

```c
void DispatchEffectTaskSourceKind(unsigned int unused,int entry);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Callback dispatches the task-owned source through the kind-specific handler table. Source: [eu/src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c:1-9](../src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c).
- Factory installs callback in task+0x30. Source: [eu/src/overlays/ov021/calls/CreateEffectTask.c:1-122](../src/overlays/ov021/calls/CreateEffectTask.c).
- Member stop/reset dispatcher invokes task+0x30(container,task). Source: [src/ov021/object_state/InvokeMemberCleanupCallbacks_020ad908.c:1-28](../../src/ov021/object_state/InvokeMemberCleanupCallbacks_020ad908.c).
- Exact target selects handler by source signed kind+0x3d. Source: [src/ov056/unclassified_helpers/DispatchSourceKindHandler_020d7d54.c:1-22](../../src/ov056/unclassified_helpers/DispatchSourceKindHandler_020d7d54.c).

Contract limits:

- Do not call this destructor: source release is task+0x20.

## ResetCurrentScriptTaskSlots

Identity: `ov021:020ad4b4`, THUMB, native extent 14 bytes (including any configured pool). Previous symbol: `func_ov021_020ad4b4`.

EU entrypoint: [eu/src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c](../src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c).

```c
void ResetCurrentScriptTaskSlots(void *actor,void *owner);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Only when container+8 is the supplied script task, resets that task's slots and sounds. Source: [eu/src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c:1-9](../src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c).
- EU wrapper selects slot and sound reset operation. Source: [eu/src/overlays/ov021/calls/ResetObjectSlots.c:1-3](../src/overlays/ov021/calls/ResetObjectSlots.c).
- Clears eight task slots, zeroes active count and stops entry sounds. Source: [src/ov021/object_state/ResetObjectSlots_020ad470.c:1-25](../../src/ov021/object_state/ResetObjectSlots_020ad470.c).
- Container+8 is current member state and is cleared after member callbacks. Source: [src/ov021/object_state/InvokeMemberCleanupCallbacks_020ad908.c:1-28](../../src/ov021/object_state/InvokeMemberCleanupCallbacks_020ad908.c).

Contract limits:

- Legacy actor/owner parameter names conceal that the second argument is the task whose slots are reset.

## UpdateEffectTaskSource

Identity: `ov021:020adca0`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020adca0`.

EU entrypoint: [eu/src/overlays/ov021/calls/UpdateEffectTaskSource.c](../src/overlays/ov021/calls/UpdateEffectTaskSource.c).

```c
void UpdateEffectTaskSource(unsigned int unused,int entry,unsigned int value);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads source at task+0x50 and forwards incoming step to source update adapter. Source: [eu/src/overlays/ov021/calls/UpdateEffectTaskSource.c:1-9](../src/overlays/ov021/calls/UpdateEffectTaskSource.c).
- Factory installs this callback at task+0x24. Source: [eu/src/overlays/ov021/calls/CreateEffectTask.c:1-122](../src/overlays/ov021/calls/CreateEffectTask.c).
- Invokes task+0x24(container,task,step). Source: [src/ov021/object_state/InvokeMemberUpdateCallbacks_020ad6dc.c:1-24](../../src/ov021/object_state/InvokeMemberUpdateCallbacks_020ad6dc.c).
- Intermediate adapter routes to UpdateEntrySource(+1c callback). Source: [eu/src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c:1-3](../src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c).

Contract limits:

- The old draw field label is incorrect; this callback receives timestep.

## DrawEffectTaskSource

Identity: `ov021:020adcac`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020adcac`.

EU entrypoint: [eu/src/overlays/ov021/calls/DrawEffectTaskSource.c](../src/overlays/ov021/calls/DrawEffectTaskSource.c).

```c
void DrawEffectTaskSource(unsigned int unused,int entry);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Reads source at task+0x50 and forwards to source draw adapter. Source: [eu/src/overlays/ov021/calls/DrawEffectTaskSource.c:1-9](../src/overlays/ov021/calls/DrawEffectTaskSource.c).
- Factory installs this callback at task+0x28. Source: [eu/src/overlays/ov021/calls/CreateEffectTask.c:1-122](../src/overlays/ov021/calls/CreateEffectTask.c).
- Draw dispatcher invokes task+0x28(container,task). Source: [src/ov021/object_state/InvokeMemberDrawCallbacks_020ad714.c:1-21](../../src/ov021/object_state/InvokeMemberDrawCallbacks_020ad714.c).
- Intermediate adapter routes to DrawEntrySource(+20 callback). Source: [eu/src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c:1-3](../src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c).

Contract limits:

- The old cleanup field label is incorrect.

## ReleaseScriptedEffectTaskExtraResources

Identity: `ov021:020adfd8`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov021_020adfd8`.

EU entrypoint: [eu/src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c](../src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c).

```c
void ReleaseScriptedEffectTaskExtraResources(int self);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Releases ordinary scripted-effect resources, releases callback-owned object at+0x84 and frees that extra object allocation. Source: [eu/src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c:1-12](../src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c).
- For IDs0x8f/0x90 factory allocates extra object+84 and installs this function at task+20 release slot. Source: [eu/src/overlays/ov021/calls/CreateScriptedEffectTask.c:1-41](../src/overlays/ov021/calls/CreateScriptedEffectTask.c).
- Task release dispatcher invokes+20. Source: [src/ov021/object_state/ReleaseMemberResources_020acd8c.c:1-17](../../src/ov021/object_state/ReleaseMemberResources_020acd8c.c).

Contract limits:

- Callback-owned extra uses its own+24 destructor prefix; that does not alter ScriptTask+24 timestep contract.

## UpdateEffectEntrySourceAdapter

Identity: `ov021:020ae738`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020ae738`.

EU entrypoint: [eu/src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c](../src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c).

```c
void * UpdateEffectEntrySourceAdapter();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Forwards unchanged source/step to UpdateEntrySource. Source: [eu/src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c:1-3](../src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c).
- Shared body selected by exact EU aliases. Source: [src/ov021/library_nitro_pxi/PXI_Init_020ae718.c:1-5](../../src/ov021/library_nitro_pxi/PXI_Init_020ae718.c).
- Exact target invokes source update callback+1c. Source: [eu/src/overlays/ov021/calls/UpdateEntrySource.c:1-9](../src/overlays/ov021/calls/UpdateEntrySource.c).

Additional native ABI observations:

- Legacy no-parameter declarations preserve incoming ARM arguments; repair prototypes only with match checks.

## DrawEffectEntrySourceAdapter

Identity: `ov021:020ae740`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020ae740`.

EU entrypoint: [eu/src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c](../src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c).

```c
void * DrawEffectEntrySourceAdapter();
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Forwards source to DrawEntrySource. Source: [eu/src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c:1-3](../src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c).
- Shared body selected by exact EU aliases. Source: [src/ov021/library_nitro_pxi/PXI_Init_020ae720.c:1-5](../../src/ov021/library_nitro_pxi/PXI_Init_020ae720.c).
- Exact target invokes source draw callback+20. Source: [eu/src/overlays/ov021/calls/DrawEntrySource.c:1-9](../src/overlays/ov021/calls/DrawEntrySource.c).

Additional native ABI observations:

- Legacy adapter return type is void* though callback is void. Keep return-flow and ABI explicit during signature repair.

## DrawModelOutsideCameraProximity

Identity: `ov021:020ae8ac`, THUMB, native extent 96 bytes (including any configured pool). Previous symbol: `func_ov021_020ae8ac`.

EU entrypoint: [eu/src/overlays/ov021/calls/DrawModelOutsideCameraProximity.c](../src/overlays/ov021/calls/DrawModelOutsideCameraProximity.c).

```c
void DrawModelOutsideCameraProximity(unsigned short *param_1, int param_2, int param_3, int param_4);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Compares model translation against global camera position in XZ; suppresses drawing only if horizontal distance<0xccd and absolute Y difference<0x8000, otherwise draws SceneNode. Source: [src/ov021/shared_engine/func_ov021_020ae88c.c:1-31](../../src/ov021/shared_engine/func_ov021_020ae88c.c).
- The model matrix starts at+0x80 and translation occupies+0xa4, matching the position read by this helper. Source: [eu/src/calls/SceneNode_Draw.c:1-96](../src/calls/SceneNode_Draw.c).

Contract limits:

- Boundary comparisons are strict.
- This proximity suppression is not a frustum test; the model is not drawn inside the small camera-adjacent region.

## SetModelPolygonIdAndDrawOutsideCameraProximity

Identity: `ov021:020ae944`, THUMB, native extent 18 bytes (including any configured pool). Previous symbol: `func_ov021_020ae944`.

EU entrypoint: [eu/src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c](../src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c).

```c
void SetModelPolygonIdAndDrawOutsideCameraProximity(int work,LayoutU32 materialIndex,int polygonId);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Sets the chosen model material polygon ID then invokes the proximity-filtered draw helper. Source: [eu/src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c:1-51](../src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c).

Contract limits:

- Mutates material state before the draw can be suppressed.

## ReleaseActiveSubModeOverlay

Identity: `ov021:020af3a0`, THUMB, native extent 104 bytes (including any configured pool). Previous symbol: `func_ov021_020af3a0`.

EU entrypoint: [eu/src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c](../src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c).

```c
void ReleaseActiveSubModeOverlay(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Dispatches mode-specific cleanup, unloads the selected submode overlay, sets mode -1 and frees the expanded-heap work block. Source: [eu/src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c:1-31](../src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c).
- The complementary submode setup selects overlay ID and owns the shared mode/work storage. Source: [eu/src/overlays/ov021/calls/BeginSubModeTask.c:1-4](../src/overlays/ov021/calls/BeginSubModeTask.c).

Contract limits:

- Only clears the work pointer; the shared owner/heap reference itself is retained.
- Preserve the distinct cleanup entrypoint for each mode.

## GetActiveSubMode

Identity: `ov021:020af408`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020af408`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetActiveSubMode.c](../src/overlays/ov021/calls/GetActiveSubMode.c).

```c
int GetActiveSubMode(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns the first word of the exact shared submode state owner. Source: [eu/src/overlays/ov021/calls/GetActiveSubMode.c:1-5](../src/overlays/ov021/calls/GetActiveSubMode.c).
- Mode is stored in this first word during setup and selects the loaded overlay. Source: [eu/src/overlays/ov021/calls/BeginSubModeTask.c:1-4](../src/overlays/ov021/calls/BeginSubModeTask.c).

Contract limits:

- Returns the raw mode, including -1 after teardown.

## UpdateActiveSubModeCamera

Identity: `ov021:020af528`, THUMB, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov021_020af528`.

EU entrypoint: [eu/src/overlays/ov021/calls/UpdateActiveSubModeCamera.c](../src/overlays/ov021/calls/UpdateActiveSubModeCamera.c).

```c
void UpdateActiveSubModeCamera(int value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Dispatches camera update/commit to overlays046,042,043,044 according to active mode, forwarding the caller flag only to modes2/3. Source: [eu/src/overlays/ov021/calls/UpdateActiveSubModeCamera.c:1-23](../src/overlays/ov021/calls/UpdateActiveSubModeCamera.c).
- The mode3 target updates listener state and commits camera projection/view axes when its lock flag allows it. Source: [eu/src/overlays/ov044/calls/CommitPanelCameraFrame.c:1-22](../src/overlays/ov044/calls/CommitPanelCameraFrame.c).

Contract limits:

- Modes0/1 ignore the wrapper flag because their underlying interfaces take no logical argument.
- Does not select or load a different camera overlay.

## GetActiveCameraCullingOrigin

Identity: `ov021:020af5d4`, THUMB, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov021_020af5d4`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c](../src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c).

```c
int GetActiveCameraCullingOrigin(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Dispatches origin getter by active camera mode; returns a VecFx32 pointer consumed as culling origin. Source: [eu/src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c:1-27](../src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c).
- EU aliases map these two dispatchers into actual shape culling consumer. Source: [eu/src/calls/IsWithinPlaneSet.c:1-10](../src/calls/IsWithinPlaneSet.c).
- Subtracts culling origin from shape center, then tests four dot products with the returned normal array and projected radius/margin. Source: [src/arm9/spatial_queries/IsWithinPlaneSet_0203e958.c:1-66](../../src/arm9/spatial_queries/IsWithinPlaneSet_0203e958.c).
- EU point-query variant aliases the same two dispatchers. Source: [eu/src/calls/IsWithinPlaneSet_0203ebdc.c:1-6](../src/calls/IsWithinPlaneSet_0203ebdc.c).
- Subtracts culling origin from a point and tests four normal dot products. Source: [src/arm9/spatial_queries/IsWithinPlaneSet_0203ebc8.c:1-31](../../src/arm9/spatial_queries/IsWithinPlaneSet_0203ebc8.c).

Contract limits:

- Borrowed pointer; do not free or retain across camera backend changes.
- Culling origin is the demonstrated role; it is not proven to be the rendered eye position for every backend.

Additional native ABI observations:

- Existing u32/int return declaration carries a borrowed pointer in R0. Repair type only with ABI/match validation.

## GetActiveSubModeCameraWork

Identity: `ov021:020af614`, THUMB, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov021_020af614`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetActiveSubModeCameraWork.c](../src/overlays/ov021/calls/GetActiveSubModeCameraWork.c).

```c
int GetActiveSubModeCameraWork(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns the active camera work owner from the corresponding mode-specific getter, or0 for unsupported modes. Source: [eu/src/overlays/ov021/calls/GetActiveSubModeCameraWork.c:1-27](../src/overlays/ov021/calls/GetActiveSubModeCameraWork.c).
- Mode0 returns gCameraManager. Source: [eu/src/overlays/ov046/calls/GetCameraManagerWork.c:1-6](../src/overlays/ov046/calls/GetCameraManagerWork.c).
- Mode1 returns its exact camera state global. Source: [eu/src/overlays/ov042/calls/Ov042Camera_GetState.c:1-7](../src/overlays/ov042/calls/Ov042Camera_GetState.c).
- Mode3 returns its exact panel camera state global. Source: [eu/src/overlays/ov044/calls/GetPanelCameraState.c:1-5](../src/overlays/ov044/calls/GetPanelCameraState.c).

Contract limits:

- The returned owner types differ by mode; no unified complete layout is inferred.
- Borrowed pointer, no allocation or destruction.

## GetActiveCameraViewPlaneNormals

Identity: `ov021:020af71c`, THUMB, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov021_020af71c`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c](../src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c).

```c
unsigned int GetActiveCameraViewPlaneNormals(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- For camera modes0,2and3 dispatches a borrowed array of four VecFx32 view-plane normals. Case1 retains the same overlay043 target as case2, with no valid overlay042 getter contract. Source: [eu/src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c:1-25](../src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c).
- EU aliases map these two dispatchers into actual shape culling consumer. Source: [eu/src/calls/IsWithinPlaneSet.c:1-10](../src/calls/IsWithinPlaneSet.c).
- Subtracts culling origin from shape center, then tests four dot products with the returned normal array and projected radius/margin. Source: [src/arm9/spatial_queries/IsWithinPlaneSet_0203e958.c:1-66](../../src/arm9/spatial_queries/IsWithinPlaneSet_0203e958.c).
- EU point-query variant aliases the same two dispatchers. Source: [eu/src/calls/IsWithinPlaneSet_0203ebdc.c:1-6](../src/calls/IsWithinPlaneSet_0203ebdc.c).
- Subtracts culling origin from a point and tests four normal dot products. Source: [src/arm9/spatial_queries/IsWithinPlaneSet_0203ebc8.c:1-31](../../src/arm9/spatial_queries/IsWithinPlaneSet_0203ebc8.c).
- CommitCameraFrame Thumb starts020bd070 size0x84, so020bd0ac is inside this function, not an ARM getter. Source: [eu/config/arm9/overlays/ov042/symbols.txt:1-3](../config/arm9/overlays/ov042/symbols.txt).
- Overlay043 does have an ARM getter at020bd0ac. Source: [eu/config/arm9/overlays/ov043/symbols.txt:1-30](../config/arm9/overlays/ov043/symbols.txt).

Contract limits:

- Borrowed pointer; do not free or retain across camera backend changes.
- Array has four side planes. No near/far plane pair or six-plane frustum is inferred.
- Valid normal-array contract demonstrated only for modes0,2and3. In mode1 the dispatcher retains a fixed overlay043 ARM address that falls inside overlay042 Thumb CommitCameraFrame; normal mode1 culling avoids this getter and uses bounds instead. Preserve the bytes and document the precondition.

Additional native ABI observations:

- Existing u32/int return declaration carries a borrowed pointer in R0. Repair type only with ABI/match validation.

## IsPointWithinActiveCameraView

Identity: `ov021:020af798`, THUMB, native extent 64 bytes (including any configured pool). Previous symbol: `func_ov021_020af798`.

EU entrypoint: [eu/src/overlays/ov021/calls/IsPointWithinActiveCameraView.c](../src/overlays/ov021/calls/IsPointWithinActiveCameraView.c).

```c
int IsPointWithinActiveCameraView(void *point,int planes);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Dispatches visibility predicate by active camera mode and returns false for unsupported mode. Source: [eu/src/overlays/ov021/calls/IsPointWithinActiveCameraView.c:1-27](../src/overlays/ov021/calls/IsPointWithinActiveCameraView.c).
- Modes0/3 use four view-plane normal dot-product tests. Source: [src/arm9/spatial_queries/IsWithinPlaneSet_0203ebc8.c:1-31](../../src/arm9/spatial_queries/IsWithinPlaneSet_0203ebc8.c).
- Mode1 checks view-space X/Y extents, adding projected shape radius when applicable. Source: [src/arm9/spatial_queries/IsPointInViewBounds_0203ec44.c:1-47](../../src/arm9/spatial_queries/IsPointInViewBounds_0203ec44.c).
- Mode2 first clips negative worldZ using scene depth distance, then uses the four-plane test. Source: [src/ov043/camera/IsPointInViewDepth_020bd284.c:1-12](../../src/ov043/camera/IsPointInViewDepth_020bd284.c).
- Call destinations identify MAIN and overlay043 implementations; bd20c is ambiguous in symbol database because overlay039 shares that address. Source: [eu/config/arm9/overlays/ov021/relocs.txt:1-2389](../config/arm9/overlays/ov021/relocs.txt).

Contract limits:

- Second parameter is fx32 margin/threshold, not a plane count.
- Names describe the active backend criteria; do not infer a universal six-plane 3D frustum.

Additional native ABI observations:

- Legacy no-parameter declarations in branches preserve live R0/R1; real signature is shape/point pointer plus fx32 margin. Verify compiled ABI before fixing prototypes.

## HasDefaultSubModeCameraChangePending

Identity: `ov021:020af830`, THUMB, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov021_020af830`.

EU entrypoint: [eu/src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c](../src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c).

```c
unsigned int HasDefaultSubModeCameraChangePending(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Only mode0 delegates Camera_HasPendingModeChange; all other/unsupported modes return0. Source: [eu/src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c:1-22](../src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c).

Contract limits:

- Does not query pending changes in modes1..3.

## GetStageScriptOpcode

Identity: `ov021:020b0370`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020b0370`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetStageScriptOpcode.c](../src/overlays/ov021/calls/GetStageScriptOpcode.c).

```c
u32 GetStageScriptOpcode(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns script code base(+8) plus PC(+0x1c) plus code-section offset(+0x18). Source: [eu/src/overlays/ov021/calls/GetStageScriptOpcode.c:1-9](../src/overlays/ov021/calls/GetStageScriptOpcode.c).
- Uses the result as ScriptOpcode with handler byte and length halfword before dispatch. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Pointer is borrowed; no bounds or alignment validation.

## GetStageScriptOperands

Identity: `ov021:020b037c`, THUMB, native extent 14 bytes (including any configured pool). Previous symbol: `func_ov021_020b037c`.

EU entrypoint: [eu/src/overlays/ov021/calls/GetStageScriptOperands.c](../src/overlays/ov021/calls/GetStageScriptOperands.c).

```c
u32 GetStageScriptOperands(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns the current opcode pointer plus its four-byte header. Source: [eu/src/overlays/ov021/calls/GetStageScriptOperands.c:1-10](../src/overlays/ov021/calls/GetStageScriptOperands.c).
- Uses this pointer as the handler operand area when opcode length>=4. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Does not validate operand count or tagged types.

## ResolveStageScriptDataOffset

Identity: `ov021:020b038c`, THUMB, native extent 6 bytes (including any configured pool). Previous symbol: `func_ov021_020b038c`.

EU entrypoint: [eu/src/overlays/ov021/auto/ResolveStageScriptDataOffset.c](../src/overlays/ov021/auto/ResolveStageScriptDataOffset.c).

```c
s32 ResolveStageScriptDataOffset(int self, s32 offset);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Adds the supplied offset to the script data buffer at context+0x0c. Source: [src/ov021/leaf_research/func_ov021_020b036c.c:1-6](../../src/ov021/leaf_research/func_ov021_020b036c.c).
- The operand resolver uses this function to resolve relative data references. Source: [eu/src/overlays/ov021/calls/ResolveTaggedValueRef.c:1-3](../src/overlays/ov021/calls/ResolveTaggedValueRef.c).

Contract limits:

- Offset is raw signed32 arithmetic, with no range check.

## StageExpr_FindFarthestFreeSlot

Identity: `ov021:020b0a68`, THUMB, native extent 72 bytes (including any configured pool). Previous symbol: `func_ov021_020b0a68`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c](../src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c).

```c
u32 StageExpr_FindFarthestFreeSlot(int self, int args);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- On an active event and valid record, resolves height operand and calls free-slot search with heightSign=0, distanceSign=1; stores returned index as tagged integer. Source: [eu/src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c:1-28](../src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c).
- Search skips in-use entries; positive distanceSign retains greater XZ distance, negative retains smaller; positive heightSign requires entryY>=height. Origin comes from managed entry1. Source: [src/ov008/unclassified_helpers/SlotTable_FindNearestFree_020a1280.c:1-59](../../src/ov008/unclassified_helpers/SlotTable_FindNearestFree_020a1280.c).
- EU wrapper identifies stage record pool lookup. Source: [eu/src/overlays/ov001/calls/GetStageMotionRecord.c:1-4](../src/overlays/ov001/calls/GetStageMotionRecord.c).
- Returns record by ID from stage manager table, orNULL when absent. Source: [src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c:1-20](../../src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c).

Contract limits:

- Absent event/record leaves prior tagged result untouched. The returned index may be-1. Record layout must agree with the active subsystem; no universal Motion struct is inferred.

## StageScriptExpr_TestSessionFlag3713

Identity: `ov021:020b0b74`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov021_020b0b74`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c](../src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c).

```c
u32 StageScriptExpr_TestSessionFlag3713(int self);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Sets integer result tag1 and stores IsSessionFlagSet(0x3713). Source: [eu/src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c:1-13](../src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c).

Contract limits:

- The meaning of session flag0x3713 is not inferred.

## StageExpr_FindNearestFreeSlot

Identity: `ov021:020b0cfc`, THUMB, native extent 72 bytes (including any configured pool). Previous symbol: `func_ov021_020b0cfc`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c](../src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c).

```c
u32 StageExpr_FindNearestFreeSlot(int self, int args);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- On an active event and valid record, resolves height operand and calls free-slot search with heightSign=0, distanceSign=-1; stores returned index as tagged integer. Source: [eu/src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c:1-28](../src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c).
- Search skips in-use entries; positive distanceSign retains greater XZ distance, negative retains smaller; positive heightSign requires entryY>=height. Origin comes from managed entry1. Source: [src/ov008/unclassified_helpers/SlotTable_FindNearestFree_020a1280.c:1-59](../../src/ov008/unclassified_helpers/SlotTable_FindNearestFree_020a1280.c).
- EU wrapper identifies stage record pool lookup. Source: [eu/src/overlays/ov001/calls/GetStageMotionRecord.c:1-4](../src/overlays/ov001/calls/GetStageMotionRecord.c).
- Returns record by ID from stage manager table, orNULL when absent. Source: [src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c:1-20](../../src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c).

Contract limits:

- Absent event/record leaves prior tagged result untouched. The returned index may be-1. Record layout must agree with the active subsystem; no universal Motion struct is inferred.

## StageExpr_FindFarthestFreeSlotAtOrAboveHeight

Identity: `ov021:020b0d8c`, THUMB, native extent 72 bytes (including any configured pool). Previous symbol: `func_ov021_020b0d8c`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c](../src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c).

```c
u32 StageExpr_FindFarthestFreeSlotAtOrAboveHeight(int self, int args);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- On an active event and valid record, resolves height operand and calls free-slot search with heightSign=1, distanceSign=1; stores returned index as tagged integer. Source: [eu/src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c:1-28](../src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c).
- Search skips in-use entries; positive distanceSign retains greater XZ distance, negative retains smaller; positive heightSign requires entryY>=height. Origin comes from managed entry1. Source: [src/ov008/unclassified_helpers/SlotTable_FindNearestFree_020a1280.c:1-59](../../src/ov008/unclassified_helpers/SlotTable_FindNearestFree_020a1280.c).
- EU wrapper identifies stage record pool lookup. Source: [eu/src/overlays/ov001/calls/GetStageMotionRecord.c:1-4](../src/overlays/ov001/calls/GetStageMotionRecord.c).
- Returns record by ID from stage manager table, orNULL when absent. Source: [src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c:1-20](../../src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c).

Contract limits:

- Absent event/record leaves prior tagged result untouched. The returned index may be-1. Record layout must agree with the active subsystem; no universal Motion struct is inferred.

## StageExpr_GetSelectedCommandEntryId

Identity: `ov021:020b0fd4`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov021_020b0fd4`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c](../src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c).

```c
u32 StageExpr_GetSelectedCommandEntryId(int self);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Stores stage-manager halfword+0x18ed2 as tagged integer. Source: [eu/src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c:1-13](../src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c).
- Native nearestCommand halfword lies at18ed2. Setting it to zero resolves through FindNearestCommandEntry(event,1); otherwise it retains the explicit selected entry ID. Source: [eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c:1-888](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c).

Contract limits:

- Name covers explicit selection and automatic nearest-entry resolution. No story or gameplay category is inferred.

## StageScriptExpr_GetVectorZ

Identity: `ov021:020b111c`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020b111c`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptExpr_GetVectorZ.c](../src/overlays/ov021/auto/StageScriptExpr_GetVectorZ.c).

```c
u32 StageScriptExpr_GetVectorZ(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Sets result tag0x10 and copies context vector Z at+0x3c to result word+0x30. Source: [src/ov021/leaf_research/func_ov021_020b10fc.c:1-9](../../src/ov021/leaf_research/func_ov021_020b10fc.c).
- The script vector operation stores the VecFx32 result beginning at+0x34. Source: [eu/src/overlays/ov021/calls/SetScriptContextVector.c:1-4](../src/overlays/ov021/calls/SetScriptContextVector.c).
- Tag0x10 represents an unshifted12-fraction-bit fixed-point value. Source: [src/ov021/leaf_research/TaggedValueToFixed_020b03b0.c:1-12](../../src/ov021/leaf_research/TaggedValueToFixed_020b03b0.c).

Contract limits:

- Result type and value are written; does not mutate the source vector.

## StageScriptExpr_GetVectorY

Identity: `ov021:020b1128`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020b1128`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptExpr_GetVectorY.c](../src/overlays/ov021/auto/StageScriptExpr_GetVectorY.c).

```c
u32 StageScriptExpr_GetVectorY(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Sets result tag0x10 and copies context vector Y at+0x38 to result word+0x30. Source: [src/ov021/leaf_research/func_ov021_020b1108.c:1-9](../../src/ov021/leaf_research/func_ov021_020b1108.c).
- The vector output begins at+0x34. Source: [eu/src/overlays/ov021/calls/SetScriptContextVector.c:1-4](../src/overlays/ov021/calls/SetScriptContextVector.c).

Contract limits:

- Fixed-point raw word is preserved.

## StageScriptExpr_GetVectorX

Identity: `ov021:020b1134`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov021_020b1134`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptExpr_GetVectorX.c](../src/overlays/ov021/auto/StageScriptExpr_GetVectorX.c).

```c
u32 StageScriptExpr_GetVectorX(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Sets result tag0x10 and copies context vector X at+0x34 to result word+0x30. Source: [src/ov021/leaf_research/func_ov021_020b1114.c:1-9](../../src/ov021/leaf_research/func_ov021_020b1114.c).
- The vector output begins at+0x34. Source: [eu/src/overlays/ov021/calls/SetScriptContextVector.c:1-4](../src/overlays/ov021/calls/SetScriptContextVector.c).

Contract limits:

- Fixed-point raw word is preserved.

## StageScriptExpr_GetSequenceId

Identity: `ov021:020b1250`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov021_020b1250`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c](../src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c).

```c
u32 StageScriptExpr_GetSequenceId(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Sets integer result tag1 and returns sequencer ID halfword+0xa0. Source: [eu/src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c:1-11](../src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c).
- Initializes ID+0xa0 from header[2]. Source: [src/ov021/unclassified_helpers/InitSequencer_020b4aac.c:1-63](../../src/ov021/unclassified_helpers/InitSequencer_020b4aac.c).

Contract limits:

- Returns the raw sequence ID without table lookup.

## StageCmd_StoreCurrentMotionGridCellCenter

Identity: `ov021:020b1af4`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov021_020b1af4`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c](../src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c).

```c
u32 StageCmd_StoreCurrentMotionGridCellCenter(int self);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- If active event motion record resolves, reads its current cell index through pointer+0x20 and writes grid cell center into thread vector+0x34. Source: [eu/src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c:1-16](../src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c).
- EU alias selects grid cell center helper. Source: [eu/src/overlays/ov006/calls/GetGridCellCenter.c:1-4](../src/overlays/ov006/calls/GetGridCellCenter.c).
- Divides cell index by column count into row/column and calls the cell-position helper. Source: [src/ov006/grid/GetGridCellCenter_020a1370.c:1-21](../../src/ov006/grid/GetGridCellCenter_020a1370.c).
- Resolves record by active event motionId. Source: [src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c:1-20](../../src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c).

Contract limits:

- No absent-active-event guard is added. Record data is interpreted according to its current grid subsystem; no universal motion layout is inferred.

## StageScriptVec_GetActorNodePosition

Identity: `ov021:020b1c04`, THUMB, native extent 76 bytes (including any configured pool). Previous symbol: `func_ov021_020b1c04`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c](../src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c).

```c
u32 StageScriptVec_GetActorNodePosition(int self, int args);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Resolves target actor and a node-name data offset, finds its node index and writes the node position to context vector+0x34. Source: [eu/src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c:1-27](../src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c).

Contract limits:

- Returns without changing vector when actor resolution fails.
- The node-name pointer is relative to script data.

## StageScriptVec_AddRandomHorizontalOffset

Identity: `ov021:020b1f54`, THUMB, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov021_020b1f54`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c](../src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c).

```c
unsigned int StageScriptVec_AddRandomHorizontalOffset(int entry);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Chooses an unsigned16 angle, forms XZ sine/cosine offset of radius2 fixed-point units, and adds it to context vector. Source: [eu/src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c:1-18](../src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c).
- Installed in the vector-operation table. Source: [eu/src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c:1-292](../src/overlays/ov021/data/tables/PointerTables_ov021_020b52d4.c).

Contract limits:

- Preserves Y.
- Uses the shared RNG; no separate random state is created.

## StageScriptCmd_ScaleStageVector

Identity: `ov021:020b230c`, THUMB, native extent 148 bytes (including any configured pool). Previous symbol: `func_ov021_020b230c`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c](../src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c).

```c
u32 StageScriptCmd_ScaleStageVector(u32 self, int args);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Resolves a vector index and fixed factor, then independently FX_Mul-scales the three words at stageManager+0x18e60+12*index. Source: [eu/src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c:1-28](../src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c).

Contract limits:

- Keeps three per-component rounded multiplies.
- No bounds check is added for vector index.

## StageScriptExpr_StageVectorMagnitude

Identity: `ov021:020b23a0`, THUMB, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov021_020b23a0`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c](../src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c).

```c
u32 StageScriptExpr_StageVectorMagnitude(int self);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Sets fixed result tag0x10 and stores VEC_Mag of the indexed stage vector at+0x18e60. Source: [eu/src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c:1-19](../src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c).

Contract limits:

- Reads a stage vector, not the local context result vector.

## StageScriptOp_End

Identity: `ov021:020b23fc`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov021_020b23fc`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_End.c](../src/overlays/ov021/auto/StageScriptOp_End.c).

```c
int StageScriptOp_End(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns opcode result4. Source: [src/ov021/library_nitro_fs/FSi_EmptyArchiveProc_020b23dc.c:1-1](../../src/ov021/library_nitro_fs/FSi_EmptyArchiveProc_020b23dc.c).
- Result4 clears registerIndex and stops the interpreter loop. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Does not free the script allocation.

## StageScriptOp_Call

Identity: `ov021:020b245c`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020b245c`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_Call.c](../src/overlays/ov021/auto/StageScriptOp_Call.c).

```c
u32 StageScriptOp_Call(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores operand value at context.jumpTarget+0x24 and returns6. Source: [src/ov021/leaf_research/func_ov021_020b243c.c:1-7](../../src/ov021/leaf_research/func_ov021_020b243c.c).
- Result6 advances to the next opcode, pushes return PC and jumps to jumpTarget. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Uses the existing four-entry call stack without adding a bounds check.

## StageScriptOp_StoreJumpValueAndYield

Identity: `ov021:020b2464`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020b2464`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_StoreJumpValueAndYield.c](../src/overlays/ov021/auto/StageScriptOp_StoreJumpValueAndYield.c).

```c
u32 StageScriptOp_StoreJumpValueAndYield(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores operand value to jumpTarget and returns7. Source: [src/ov021/leaf_research/func_ov021_020b2444.c:1-7](../../src/ov021/leaf_research/func_ov021_020b2444.c).
- Result7 stores jumpTarget in the selected register, resets registerIndex and yields without changing PC. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Does not perform a normal PC jump despite the use of jumpTarget storage.

## StageScriptOp_NoOp

Identity: `ov021:020b246c`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov021_020b246c`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_NoOp.c](../src/overlays/ov021/auto/StageScriptOp_NoOp.c).

```c
int StageScriptOp_NoOp(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns opcode result0 without state mutation. Source: [src/ov021/library_nitro_fs/FSi_CloseFileCommand_020b244c.c:1-1](../../src/ov021/library_nitro_fs/FSi_CloseFileCommand_020b244c.c).
- Installed as an explicit opcode handler. Source: [eu/src/overlays/ov021/calls/InitScriptHandlerTable.c:1-70](../src/overlays/ov021/calls/InitScriptHandlerTable.c).
- Result0 advances by the opcode byte length. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Operand evaluation is absent in this helper.

## StageCmd_AttachActorToNamedStageNode

Identity: `ov021:020b2880`, THUMB, native extent 102 bytes (including any configured pool). Previous symbol: `func_ov021_020b2880`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c](../src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c).

```c
u32 StageCmd_AttachActorToNamedStageNode(u32 self, int args);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Resolves source and target actors, obtains target's1-based stage actor index, resolves node name from script data, and attaches source with align0. Source: [eu/src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c:1-32](../src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c).
- Converts supplied record pointer to1-based actor index by (ptr-largeRecords)/0x3c8+1. Source: [src/ov001/shared_engine/GetLargeRecordIndex_0209c26c.c:1-14](../../src/ov001/shared_engine/GetLargeRecordIndex_0209c26c.c).
- Looks up target actor, resolves nodeName, stores attachment actor/node IDs, sets motion flag0x40 and obtains node position. Source: [src/ov001/actor_animation/AttachActorToStageNode_020911b4.c:1-43](../../src/ov001/actor_animation/AttachActorToStageNode_020911b4.c).
- Data helper computes script data buffer+offset for nodeName. Source: [src/ov021/leaf_research/func_ov021_020b4aa4.c:1-7](../../src/ov021/leaf_research/func_ov021_020b4aa4.c).

Contract limits:

- A failed actor resolution leaves attachments unchanged. Alignment argument remains0.

Additional native ABI observations:

- GetLargeRecordIndex() currently has no declared input at this call site; real callee uses live R0=resolved target actor. This dependency must be expressed when porting, after ABI/match validation.

## StageScriptOp_JumpAndYield

Identity: `ov021:020b349c`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020b349c`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_JumpAndYield.c](../src/overlays/ov021/auto/StageScriptOp_JumpAndYield.c).

```c
u32 StageScriptOp_JumpAndYield(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores the raw target word in context+0x24 and returns1. Source: [src/ov021/leaf_research/func_ov021_020b347c.c:1-7](../../src/ov021/leaf_research/func_ov021_020b347c.c).
- Result1 sets PC to jumpTarget then exits the interpreter loop. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Does not evaluate a TaggedValue inside this helper.

## StageScriptOp_Jump

Identity: `ov021:020b34c8`, THUMB, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov021_020b34c8`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_Jump.c](../src/overlays/ov021/auto/StageScriptOp_Jump.c).

```c
u32 StageScriptOp_Jump(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Stores the raw target word in context+0x24 and returns2. Source: [src/ov021/leaf_research/func_ov021_020b34a8.c:1-7](../../src/ov021/leaf_research/func_ov021_020b34a8.c).
- Result2 sets PC to jumpTarget and continues execution in the same update. Source: [eu/src/overlays/ov021/calls/RunScriptThread.c:1-136](../src/overlays/ov021/calls/RunScriptThread.c).

Contract limits:

- Distinct from the jump-and-yield entrypoint.

## StageScriptCmd_BeginActorWalkerMove

Identity: `ov021:020b366c`, THUMB, native extent 96 bytes (including any configured pool). Previous symbol: `func_ov021_020b366c`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c](../src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c).

```c
u32 StageScriptCmd_BeginActorWalkerMove(u32 context, s32 operands, u32 unusedArg, u32 extraArg);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Resolves actor, vector and two fixed-point values, then invokes BeginWalkerMove. Source: [eu/src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c:1-30](../src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c).

Contract limits:

- Does not resolve the vector if actor lookup fails.
- The two fixed values retain their existing opaque roles; no speed/time units are invented.

## StageScriptCmd_PlayActorAnimationSlot

Identity: `ov021:020b3750`, THUMB, native extent 112 bytes (including any configured pool). Previous symbol: `func_ov021_020b3750`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c](../src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c).

```c
u32 StageScriptCmd_PlayActorAnimationSlot(u32 context, s32 operands);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Resolves five operands, finds actor, then plays the selected animation slot with explicit16-bit truncation/sign extension and two raw option words. Source: [eu/src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c:1-28](../src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c).

Contract limits:

- Missing actor returns without an animation change.
- Preserve the signed16 second value and unsigned16 first value.

## StageScriptCmd_TriggerSessionEffectKind1

Identity: `ov021:020b38f4`, THUMB, native extent 34 bytes (including any configured pool). Previous symbol: `func_ov021_020b38f4`.

EU entrypoint: [eu/src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c](../src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c).

```c
u32 StageScriptCmd_TriggerSessionEffectKind1(u32 context, s32 operands);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Resolves two operands, then calls HandleSessionEffectEvent(1, firstValue). Source: [eu/src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c:1-15](../src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c).

Contract limits:

- Second resolution still occurs though its result is discarded.
- The effect kind remains numeric; no sound/visual identity is inferred.

## StageScriptOp_DefaultNoOp

Identity: `ov021:020b48a0`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov021_020b48a0`.

EU entrypoint: [eu/src/overlays/ov021/auto/StageScriptOp_DefaultNoOp.c](../src/overlays/ov021/auto/StageScriptOp_DefaultNoOp.c).

```c
int StageScriptOp_DefaultNoOp(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns0 with no side effects. Source: [src/ov021/library_nitro_fs/FSi_CloseFileCommand_020b4880.c:1-1](../../src/ov021/library_nitro_fs/FSi_CloseFileCommand_020b4880.c).
- The script table initializer uses this function as its default handler before specific assignments. Source: [src/ov021/script_ops/InitScriptHandlerTable_020b4884.c:1-143](../../src/ov021/script_ops/InitScriptHandlerTable_020b4884.c).

Contract limits:

- Preserve its separate entrypoint despite the explicit no-op opcode having the same behavior.

## ResolveStageScriptCommandDataOffset

Identity: `ov021:020b4ac4`, THUMB, native extent 6 bytes (including any configured pool). Previous symbol: `func_ov021_020b4ac4`.

EU entrypoint: [eu/src/overlays/ov021/auto/ResolveStageScriptCommandDataOffset.c](../src/overlays/ov021/auto/ResolveStageScriptCommandDataOffset.c).

```c
s32 ResolveStageScriptCommandDataOffset(s32 base, s32 offset);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Adds an offset to the same context data buffer at+0x0c, via a distinct entrypoint. Source: [src/ov021/leaf_research/func_ov021_020b4aa4.c:1-7](../../src/ov021/leaf_research/func_ov021_020b4aa4.c).
- Property handlers resolve embedded data, including actor name and spawn name through this function. Source: [eu/src/overlays/ov021/calls/ScriptCmd_SetProperty.c:1-888](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c).
- Vector/position resolution also uses this entrypoint, so it is not only a string resolver. Source: [eu/src/overlays/ov021/calls/ResolveOffsetPosition.c:1-13](../src/overlays/ov021/calls/ResolveOffsetPosition.c).

Contract limits:

- Preserve the separate address even though its arithmetic duplicates the operand resolver.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/auto/InitFieldButtonForEntryIndex.c InitFieldButtonForEntryIndex --thumb
python tools/verify_idx.py src/overlays/ov021/calls/ClearFieldButtonInput.c ClearFieldButtonInput --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetFieldDirectionActiveAndPollSubMode.c GetFieldDirectionActiveAndPollSubMode --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetFieldDirectionActive.c GetFieldDirectionActive --thumb
python tools/verify_idx.py src/overlays/ov021/auto/GetFieldShortcutInjectionFlag.c GetFieldShortcutInjectionFlag --thumb
python tools/verify_idx.py src/overlays/ov021/auto/GetSummedFieldDirectionAngle.c GetSummedFieldDirectionAngle --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetCueOwnerPosition.c GetCueOwnerPosition --thumb
python tools/verify_idx.py src/overlays/ov021/calls/OpenCharacterSoundCueArchive.c OpenCharacterSoundCueArchive --thumb
python tools/verify_idx.py src/overlays/ov021/calls/LoadCharacterSoundCueTable.c LoadCharacterSoundCueTable --thumb
python tools/verify_idx.py src/overlays/ov021/calls/ReplaceActiveCueHandle.c ReplaceActiveCueHandle --thumb
python tools/verify_idx.py src/overlays/ov021/calls/UpdateEntrySource.c UpdateEntrySource --thumb
python tools/verify_idx.py src/overlays/ov021/calls/DrawEntrySource.c DrawEntrySource --thumb
python tools/verify_idx.py src/overlays/ov021/auto/InitHitResultHeader.c InitHitResultHeader --thumb
python tools/verify_idx.py src/overlays/ov021/calls/ReleaseEffectTaskSource.c ReleaseEffectTaskSource --thumb
python tools/verify_idx.py src/overlays/ov021/calls/DispatchEffectTaskSourceKind.c DispatchEffectTaskSourceKind --thumb
python tools/verify_idx.py src/overlays/ov021/calls/ResetCurrentScriptTaskSlots.c ResetCurrentScriptTaskSlots --thumb
python tools/verify_idx.py src/overlays/ov021/calls/UpdateEffectTaskSource.c UpdateEffectTaskSource --thumb
python tools/verify_idx.py src/overlays/ov021/calls/DrawEffectTaskSource.c DrawEffectTaskSource --thumb
python tools/verify_idx.py src/overlays/ov021/calls/ReleaseScriptedEffectTaskExtraResources.c ReleaseScriptedEffectTaskExtraResources --thumb
python tools/verify_idx.py src/overlays/ov021/calls/UpdateEffectEntrySourceAdapter.c UpdateEffectEntrySourceAdapter --thumb
python tools/verify_idx.py src/overlays/ov021/calls/DrawEffectEntrySourceAdapter.c DrawEffectEntrySourceAdapter --thumb
python tools/verify_idx.py src/overlays/ov021/calls/DrawModelOutsideCameraProximity.c DrawModelOutsideCameraProximity --thumb
python tools/verify_idx.py src/overlays/ov021/calls/SetModelPolygonIdAndDrawOutsideCameraProximity.c SetModelPolygonIdAndDrawOutsideCameraProximity --thumb
python tools/verify_idx.py src/overlays/ov021/calls/ReleaseActiveSubModeOverlay.c ReleaseActiveSubModeOverlay --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetActiveSubMode.c GetActiveSubMode --thumb
python tools/verify_idx.py src/overlays/ov021/calls/UpdateActiveSubModeCamera.c UpdateActiveSubModeCamera --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetActiveCameraCullingOrigin.c GetActiveCameraCullingOrigin --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetActiveSubModeCameraWork.c GetActiveSubModeCameraWork --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetActiveCameraViewPlaneNormals.c GetActiveCameraViewPlaneNormals --thumb
python tools/verify_idx.py src/overlays/ov021/calls/IsPointWithinActiveCameraView.c IsPointWithinActiveCameraView --thumb
python tools/verify_idx.py src/overlays/ov021/calls/HasDefaultSubModeCameraChangePending.c HasDefaultSubModeCameraChangePending --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetStageScriptOpcode.c GetStageScriptOpcode --thumb
python tools/verify_idx.py src/overlays/ov021/calls/GetStageScriptOperands.c GetStageScriptOperands --thumb
python tools/verify_idx.py src/overlays/ov021/auto/ResolveStageScriptDataOffset.c ResolveStageScriptDataOffset --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlot.c StageExpr_FindFarthestFreeSlot --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_TestSessionFlag3713.c StageScriptExpr_TestSessionFlag3713 --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageExpr_FindNearestFreeSlot.c StageExpr_FindNearestFreeSlot --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageExpr_FindFarthestFreeSlotAtOrAboveHeight.c StageExpr_FindFarthestFreeSlotAtOrAboveHeight --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageExpr_GetSelectedCommandEntryId.c StageExpr_GetSelectedCommandEntryId --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptExpr_GetVectorZ.c StageScriptExpr_GetVectorZ --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptExpr_GetVectorY.c StageScriptExpr_GetVectorY --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptExpr_GetVectorX.c StageScriptExpr_GetVectorX --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetSequenceId.c StageScriptExpr_GetSequenceId --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageCmd_StoreCurrentMotionGridCellCenter.c StageCmd_StoreCurrentMotionGridCellCenter --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptVec_GetActorNodePosition.c StageScriptVec_GetActorNodePosition --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptVec_AddRandomHorizontalOffset.c StageScriptVec_AddRandomHorizontalOffset --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptCmd_ScaleStageVector.c StageScriptCmd_ScaleStageVector --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_StageVectorMagnitude.c StageScriptExpr_StageVectorMagnitude --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_End.c StageScriptOp_End --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_Call.c StageScriptOp_Call --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_StoreJumpValueAndYield.c StageScriptOp_StoreJumpValueAndYield --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_NoOp.c StageScriptOp_NoOp --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageCmd_AttachActorToNamedStageNode.c StageCmd_AttachActorToNamedStageNode --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_JumpAndYield.c StageScriptOp_JumpAndYield --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_Jump.c StageScriptOp_Jump --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptCmd_BeginActorWalkerMove.c StageScriptCmd_BeginActorWalkerMove --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptCmd_PlayActorAnimationSlot.c StageScriptCmd_PlayActorAnimationSlot --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptCmd_TriggerSessionEffectKind1.c StageScriptCmd_TriggerSessionEffectKind1 --thumb
python tools/verify_idx.py src/overlays/ov021/auto/StageScriptOp_DefaultNoOp.c StageScriptOp_DefaultNoOp --thumb
python tools/verify_idx.py src/overlays/ov021/auto/ResolveStageScriptCommandDataOffset.c ResolveStageScriptCommandDataOffset --thumb
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The
combined106-entrypoint block passes the fresh108-module gate; affected function
bytes, resolved relocation targets/types and addends, and all module hashes
match the preserved pre-rename baseline. No algorithm, signature or native
matching-policy change is included. Verified-library receipts remain current.
