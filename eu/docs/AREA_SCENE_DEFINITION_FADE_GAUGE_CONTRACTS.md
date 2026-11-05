# Area scene definitions, material fades and gauge resources

This document records 28 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

This is the area-scene TaskObject and its child resource systems. The `rpg.z` loader selects definitionIndex -1, copies the selected record and relocates nested offsets. Scene +0x1e is the signed definition selector; +0x46/+0x48 are halfword parameters later read as signed inputs to material-fade construction. Their private width/height labels are unproven. The tracker embedded at +0x40 contains objectListId at +3 and currentArea at +0x22, so negative signed sentinel values remain meaningful.

The state dispatcher retains state for signed -1, stores nonnegative handler results and repeats immediately for flag 0x8000. Its resource states start/end overlays 40 and 41 with the explicit numeric modes in the inventory. Active overlay-41 phase is represented by raw mask 0x40, set/cleared by that phase's load/unload paths. Draw enable is mask 0x4. The session transition callback at slot 10 returns raw mask 0x20, not BOOL or a complete phase value. None of these numeric modes is assigned a human-facing role from the old Movie/Caption labels.

Persistent selection uses session flags and a 10-bit saved value: absent flag 0x379b it chooses a table value, saves the low 10 bits at 0x3791 and marks it persistent. Session flags 0x3700/0x3701 form the documented two-bit pair; these numeric flags receive no story labels. Kind-0 entry counting retains that numeric category.

Material-fade work owns its entry allocation and optional embedded model resource. Releasing the model clears its loaded marker; freeing the work also frees the entries but leaves the global pointer uncleared. A fade entry sets alpha/polygon ID 40 and changes culling according to the previous/new alpha. The callback preserves signed material-index reads and byte alpha values.

Gauge task work owns four distinct buffers (source, upload buffer, frame file and cell buffer). Its release helper frees those buffers and clears the current-work global; it does not free the task-owned work itself. Tag-sequence 1 and active record 5 retain those explicit IDs: the helpers arm sequence 1 when gauge level equals 100 or disarm it and invoke record 5's callback. Their narrative purpose is unproven.

Sound queuing preserves archive requests, arc command 0x10 and the explicit status/flag hooks. The private stopSeq label does not establish start/stop semantics for command 0x1a0, command 0x10 or status 2. The inert cleanup hook is separate from the caller that actually releases scene resources.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov035:020ba594` | THUMB | `func_ov035_020ba594` | `AreaSceneState_LoadInitialResources` | [eu/src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c](../src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c) |
| `ov035:020ba5e4` | THUMB | `func_ov035_020ba5e4` | `AreaSceneState_WaitForListNodes` | [eu/src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c](../src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c) |
| `ov035:020ba610` | THUMB | `func_ov035_020ba610` | `AreaSceneState_StartOverlay40AfterLoad` | [eu/src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c](../src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c) |
| `ov035:020ba6c0` | THUMB | `func_ov035_020ba6c0` | `AreaSceneState_EndOverlay41WhenReady` | [eu/src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c](../src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c) |
| `ov035:020ba6d8` | THUMB | `func_ov035_020ba6d8` | `AreaSceneState_StartOverlay40Mode0` | [eu/src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c](../src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c) |
| `ov035:020ba6e4` | THUMB | `func_ov035_020ba6e4` | `AreaSceneState_ReleaseResourcesAndExit` | [eu/src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c](../src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c) |
| `ov035:020ba960` | THUMB | `func_ov035_020ba960` | `CreateAreaSceneTask` | [eu/src/overlays/ov035/calls/CreateAreaSceneTask.c](../src/overlays/ov035/calls/CreateAreaSceneTask.c) |
| `ov035:020baa38` | THUMB | `func_ov035_020baa38` | `GetAreaSceneTransitionFlag` | [eu/src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c](../src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c) |
| `ov035:020baa48` | THUMB | `LoadMovieClipHeader` | `LoadAreaSceneDefinition` | [eu/src/overlays/ov035/calls/LoadAreaSceneDefinition.c](../src/overlays/ov035/calls/LoadAreaSceneDefinition.c) |
| `ov035:020bac90` | THUMB | `func_ov035_020bac90` | `AreaSceneCleanupNoOp` | [eu/src/overlays/ov035/auto/AreaSceneCleanupNoOp.c](../src/overlays/ov035/auto/AreaSceneCleanupNoOp.c) |
| `ov035:020bae68` | THUMB | `func_ov035_020bae68` | `SetAreaSceneDefinitionParams` | [eu/src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c](../src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c) |
| `ov035:020bae84` | THUMB | `func_ov035_020bae84` | `GetCurrentAreaIndex` | [eu/src/overlays/ov035/calls/GetCurrentAreaIndex.c](../src/overlays/ov035/calls/GetCurrentAreaIndex.c) |
| `ov035:020bae94` | THUMB | `func_ov035_020bae94` | `GetOverlay41PhaseActiveFlag` | [eu/src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c](../src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c) |
| `ov035:020baf30` | THUMB | `func_ov035_020baf30` | `SelectPersistentAreaSceneTableValue` | [eu/src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c](../src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c) |
| `ov035:020bafa8` | THUMB | `ShowMovieMessage3700` | `IsSessionFlag3700Set` | [eu/src/overlays/ov035/calls/IsSessionFlag3700Set.c](../src/overlays/ov035/calls/IsSessionFlag3700Set.c) |
| `ov035:020bafc4` | THUMB | `func_ov035_020bafc4` | `GetAreaSceneDefinitionIndex` | [eu/src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c](../src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c) |
| `ov035:020bafd4` | THUMB | `func_ov035_020bafd4` | `GetAreaObjectListId` | [eu/src/overlays/ov035/calls/GetAreaObjectListId.c](../src/overlays/ov035/calls/GetAreaObjectListId.c) |
| `ov035:020bb110` | THUMB | `func_ov035_020bb110` | `GetAreaSceneSessionFlagPair` | [eu/src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c](../src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c) |
| `ov035:020bb28c` | THUMB | `func_ov035_020bb28c` | `ResetAreaSceneSelectionFlags` | [eu/src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c](../src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c) |
| `ov035:020bb2c0` | THUMB | `func_ov035_020bb2c0` | `CountAreaEntriesOfKind0` | [eu/src/overlays/ov035/calls/CountAreaEntriesOfKind0.c](../src/overlays/ov035/calls/CountAreaEntriesOfKind0.c) |
| `ov035:020bb2f4` | THUMB | `func_ov035_020bb2f4` | `SetAreaSceneDrawEnabled` | [eu/src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c](../src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c) |
| `ov035:020bb354` | THUMB | `func_ov035_020bb354` | `QueueAreaSceneSoundState` | [eu/src/overlays/ov035/calls/QueueAreaSceneSoundState.c](../src/overlays/ov035/calls/QueueAreaSceneSoundState.c) |
| `ov035:020bb468` | THUMB | `func_ov035_020bb468` | `ApplyAreaMaterialFadeEntry` | [eu/src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c](../src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c) |
| `ov035:020bb66c` | THUMB | `func_ov035_020bb66c` | `ReleaseAreaFadeModelIfLoaded` | [eu/src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c](../src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c) |
| `ov035:020bb7a8` | THUMB | `func_ov035_020bb7a8` | `FreeAreaMaterialFadeWork` | [eu/src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c](../src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c) |
| `ov035:020bc0e4` | THUMB | `func_ov035_020bc0e4` | `ReleaseAreaGaugeBuffers` | [eu/src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c](../src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c) |
| `ov035:020bc3ac` | THUMB | `func_ov035_020bc3ac` | `DisarmAreaSequence1AndInvokeRecord5Callback` | [eu/src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c](../src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c) |
| `ov035:020bc3d8` | THUMB | `func_ov035_020bc3d8` | `ArmAreaSequence1AtGaugeMax` | [eu/src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c](../src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c) |

## AreaSceneState_LoadInitialResources

Identity: `ov035:020ba594`, THUMB, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov035_020ba594`.

EU entrypoint: [eu/src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c](../src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c).

```c
u32 AreaSceneState_LoadInitialResources(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits until the external busy predicate clears, pushes VRAM state, loads the rpg.z scene definition, creates event groups and material fade work, then advances to state 1. Source: [eu/src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c:1-22](../src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c).
- These functions occupy state slots 0,2,3,6,7,8 of the same scene transition handler table. Source: [eu/src/overlays/ov035/data/tables/gMovieSkipHandlers.c:1-25](../src/overlays/ov035/data/tables/gMovieSkipHandlers.c).
- Handler nonnegative returns replace work.state; flag 0x8000 immediately dispatches the next state. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).

Contract limits:

- The two signed arguments at work+0x46/+0x48 are not proven pixel dimensions.

## AreaSceneState_WaitForListNodes

Identity: `ov035:020ba5e4`, THUMB, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov035_020ba5e4`.

EU entrypoint: [eu/src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c](../src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c).

```c
u32 AreaSceneState_WaitForListNodes(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns -1 until AreAllListNodesReady succeeds, then performs the completion hook and advances immediately to state 3. Source: [eu/src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c:1-14](../src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c).
- These functions occupy state slots 0,2,3,6,7,8 of the same scene transition handler table. Source: [eu/src/overlays/ov035/data/tables/gMovieSkipHandlers.c:1-25](../src/overlays/ov035/data/tables/gMovieSkipHandlers.c).
- Handler nonnegative returns replace work.state; flag 0x8000 immediately dispatches the next state. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).

## AreaSceneState_StartOverlay40AfterLoad

Identity: `ov035:020ba610`, THUMB, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov035_020ba610`.

EU entrypoint: [eu/src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c](../src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c).

```c
u32 AreaSceneState_StartOverlay40AfterLoad(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for resource-slot loading; invokes scene/list completion hooks, starts overlay 40 with argument 1 and advances to state 4. Source: [eu/src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c:1-20](../src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c).
- These functions occupy state slots 0,2,3,6,7,8 of the same scene transition handler table. Source: [eu/src/overlays/ov035/data/tables/gMovieSkipHandlers.c:1-25](../src/overlays/ov035/data/tables/gMovieSkipHandlers.c).
- Handler nonnegative returns replace work.state; flag 0x8000 immediately dispatches the next state. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).

Contract limits:

- Argument 1 is retained as an opaque mode value.

## AreaSceneState_EndOverlay41WhenReady

Identity: `ov035:020ba6c0`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov035_020ba6c0`.

EU entrypoint: [eu/src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c](../src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c).

```c
u32 AreaSceneState_EndOverlay41WhenReady(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Polls UpdateStageFrame; on completion ends overlay 41 and advances to state 7, otherwise returns -1. Source: [eu/src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c:1-12](../src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c).
- These functions occupy state slots 0,2,3,6,7,8 of the same scene transition handler table. Source: [eu/src/overlays/ov035/data/tables/gMovieSkipHandlers.c:1-25](../src/overlays/ov035/data/tables/gMovieSkipHandlers.c).
- Handler nonnegative returns replace work.state; flag 0x8000 immediately dispatches the next state. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).

## AreaSceneState_StartOverlay40Mode0

Identity: `ov035:020ba6d8`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov035_020ba6d8`.

EU entrypoint: [eu/src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c](../src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c).

```c
u32 AreaSceneState_StartOverlay40Mode0(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Starts overlay 40 with argument 0 and returns next state 4. Source: [eu/src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c:1-3](../src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c).
- Shared C body selected by the EU wrapper; wrapper aliases establish the EU owner and callees. Source: [src/ov035/unclassified_helpers/func_ov035_020ba6b8.c:1-8](../../src/ov035/unclassified_helpers/func_ov035_020ba6b8.c).
- These functions occupy state slots 0,2,3,6,7,8 of the same scene transition handler table. Source: [eu/src/overlays/ov035/data/tables/gMovieSkipHandlers.c:1-25](../src/overlays/ov035/data/tables/gMovieSkipHandlers.c).
- Handler nonnegative returns replace work.state; flag 0x8000 immediately dispatches the next state. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).

## AreaSceneState_ReleaseResourcesAndExit

Identity: `ov035:020ba6e4`, THUMB, native extent 124 bytes (including any configured pool). Previous symbol: `func_ov035_020ba6e4`.

EU entrypoint: [eu/src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c](../src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c).

```c
unsigned int AreaSceneState_ReleaseResourcesAndExit(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Releases scene slot/character/resource and fade allocations, disables update/draw flags, destroys the child TaskObject if present, restores VRAM and heap state, then immediately advances to state 9. Source: [eu/src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c:1-42](../src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c).
- These functions occupy state slots 0,2,3,6,7,8 of the same scene transition handler table. Source: [eu/src/overlays/ov035/data/tables/gMovieSkipHandlers.c:1-25](../src/overlays/ov035/data/tables/gMovieSkipHandlers.c).
- Handler nonnegative returns replace work.state; flag 0x8000 immediately dispatches the next state. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).

Contract limits:

- The semantic meaning of the final scene phase is not inferred from the old Movie label.

## CreateAreaSceneTask

Identity: `ov035:020ba960`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov035_020ba960`.

EU entrypoint: [eu/src/overlays/ov035/calls/CreateAreaSceneTask.c](../src/overlays/ov035/calls/CreateAreaSceneTask.c).

```c
void CreateAreaSceneTask(int arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates the descriptor whose construct callback is InitMovieSceneWork and stores its TaskObject handle. Source: [eu/src/overlays/ov035/calls/CreateAreaSceneTask.c:1-5](../src/overlays/ov035/calls/CreateAreaSceneTask.c).
- Shared C body selected by the EU wrapper; wrapper aliases establish the EU owner and callees. Source: [src/ov035/shared_engine/MobiClip_SrcOpen_020ba940.c:1-7](../../src/ov035/shared_engine/MobiClip_SrcOpen_020ba940.c).
- Descriptor resolves to the constructor/update/destructor of the area-scene TaskObject. Source: [eu/src/overlays/ov035/data/gMovieSourceClassDescriptor.c:1-14](../src/overlays/ov035/data/gMovieSourceClassDescriptor.c).
- Constructor uses current TaskObject work, creates field/session context and returns the scene state dispatcher. Source: [src/ov035/shared_engine/InitMovieSceneWork_020ba3e0.c:1-59](../../src/ov035/shared_engine/InitMovieSceneWork_020ba3e0.c).

## GetAreaSceneTransitionFlag

Identity: `ov035:020baa38`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov035_020baa38`.

EU entrypoint: [eu/src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c](../src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c).

```c
u32 GetAreaSceneTransitionFlag(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns raw field transition mask0x20. Source: [eu/src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c:1-8](../src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c).
- Installs this function at callback index10 (offset0x28). Source: [eu/src/overlays/ov035/calls/InitMovieSourceOps.c:1-13](../src/overlays/ov035/calls/InitMovieSourceOps.c).
- Reads installed callback from Session+2834=overlayWork280c+10*4 and forwards its raw value. Source: [eu/src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c:1-15](../src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c).
- Equivalent established field-mode interface returns transition mask0x60. Source: [eu/src/overlays/ov028/calls/GetFieldTransitionFlags.c:1-6](../src/overlays/ov028/calls/GetFieldTransitionFlags.c).
- Uses nonzero transition callback result to block normal HUD sound progression, not as a flag-bit index. Source: [eu/src/overlays/ov001/calls/UpdateHudGauges.c:1-157](../src/overlays/ov001/calls/UpdateHudGauges.c).
- Actual scene-restart parameter handler sets flags3|0x20 and resets state counter; private Caption field labels are misleading. Source: [src/ov035/unclassified_helpers/BeginMovieCaption_020ba9d8.c:1-31](../../src/ov035/unclassified_helpers/BeginMovieCaption_020ba9d8.c).

Contract limits:

- Raw mask is retained; do not normalize0x20/0x60 into1.
- Callback exposes only these transition flags, not all scene phase state.
- Exact bit meanings remain in the owner-specific phase code; no universal mode/timer layout is introduced.

## LoadAreaSceneDefinition

Identity: `ov035:020baa48`, THUMB, native extent 156 bytes (including any configured pool). Previous symbol: `LoadMovieClipHeader`.

EU entrypoint: [eu/src/overlays/ov035/calls/LoadAreaSceneDefinition.c](../src/overlays/ov035/calls/LoadAreaSceneDefinition.c).

```c
void LoadAreaSceneDefinition(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- EU wrapper selects the rpg.z scene-record loader, not a movie decoder. Source: [eu/src/overlays/ov035/calls/LoadAreaSceneDefinition.c:1-10](../src/overlays/ov035/calls/LoadAreaSceneDefinition.c).
- Loads rpg.z, selects definition index minus one, copies the record and relocates its nested offsets. Source: [src/ov035/shared_engine/LoadMovieClipHeader_020baa28.c:1-64](../../src/ov035/shared_engine/LoadMovieClipHeader_020baa28.c).

## AreaSceneCleanupNoOp

Identity: `ov035:020bac90`, THUMB, native extent 2 bytes (including any configured pool). Previous symbol: `func_ov035_020bac90`.

EU entrypoint: [eu/src/overlays/ov035/auto/AreaSceneCleanupNoOp.c](../src/overlays/ov035/auto/AreaSceneCleanupNoOp.c).

```c
void AreaSceneCleanupNoOp(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Empty function is called by the area-scene resource release state. Source: [eu/src/overlays/ov035/auto/AreaSceneCleanupNoOp.c:1-2](../src/overlays/ov035/auto/AreaSceneCleanupNoOp.c).
- Shared C body selected by the EU wrapper; wrapper aliases establish the EU owner and callees. Source: [src/ov035/library_msl_c/_fp_init_020bac70.c:1-1](../../src/ov035/library_msl_c/_fp_init_020bac70.c).
- Cleanup state invokes this empty hook before releasing owned resources. Source: [eu/src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c:1-42](../src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c).

## SetAreaSceneDefinitionParams

Identity: `ov035:020bae68`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov035_020bae68`.

EU entrypoint: [eu/src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c](../src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c).

```c
void SetAreaSceneDefinitionParams(u8 mode, u16 width, u16 height);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores definition index byte at +0x1e and two halfword parameters at +0x46/+0x48. Source: [eu/src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c:1-12](../src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c).
- Definition index is used minus one to select the rpg.z record. Source: [src/ov035/shared_engine/LoadMovieClipHeader_020baa28.c:1-64](../../src/ov035/shared_engine/LoadMovieClipHeader_020baa28.c).
- The halfwords are passed as signed values to CreateMaterialFadeWork. Source: [eu/src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c:1-22](../src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c).

Contract limits:

- Preserve the signed reads used later by material fade construction; width/height labels are unproven.

## GetCurrentAreaIndex

Identity: `ov035:020bae84`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov035_020bae84`.

EU entrypoint: [eu/src/overlays/ov035/calls/GetCurrentAreaIndex.c](../src/overlays/ov035/calls/GetCurrentAreaIndex.c).

```c
int GetCurrentAreaIndex(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns signed byte at scene work+0x62. Source: [eu/src/overlays/ov035/calls/GetCurrentAreaIndex.c:1-7](../src/overlays/ov035/calls/GetCurrentAreaIndex.c).
- FieldState.tracker starts at +0x40 and currentArea is +0x22; this indexes the active area definition. Source: [src/ov040/unclassified_helpers/SwitchAreaObjects_020bc650.c:1-78](../../src/ov040/unclassified_helpers/SwitchAreaObjects_020bc650.c).

Contract limits:

- Can return negative sentinel.

## GetOverlay41PhaseActiveFlag

Identity: `ov035:020bae94`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov035_020bae94`.

EU entrypoint: [eu/src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c](../src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c).

```c
u32 GetOverlay41PhaseActiveFlag(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns the raw mask 0x40 from scene flags. Source: [eu/src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c:1-8](../src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c).
- Loading overlay 41 sets flag 0x40 and initializes its embedded work at +0xb8. Source: [src/ov035/unclassified_helpers/StartOverlay41Phase_020bad08.c:1-28](../../src/ov035/unclassified_helpers/StartOverlay41Phase_020bad08.c).
- Tearing down and unloading overlay 41 clears flag 0x40. Source: [src/ov035/unclassified_helpers/EndOverlay41Phase_020bad64.c:1-23](../../src/ov035/unclassified_helpers/EndOverlay41Phase_020bad64.c).

Contract limits:

- Raw mask result is 0 or 0x40, not normalized BOOL.

## SelectPersistentAreaSceneTableValue

Identity: `ov035:020baf30`, THUMB, native extent 120 bytes (including any configured pool). Previous symbol: `func_ov035_020baf30`.

EU entrypoint: [eu/src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c](../src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c).

```c
void SelectPersistentAreaSceneTableValue(u32 scale, s16 *table, u8 a, u8 b);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If flag 0x379b is clear chooses table[random_next_scaled(count)], saves its low 10 bits at 0x3791 and marks the choice persistent; restores that selection at work+0x30 and applies flag 0x3702 to the encoded field object. Source: [eu/src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c:1-31](../src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c).

Contract limits:

- The table values and two object-selector bytes retain their numeric meaning; no reward/item role is inferred.

## IsSessionFlag3700Set

Identity: `ov035:020bafa8`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `ShowMovieMessage3700`.

EU entrypoint: [eu/src/overlays/ov035/calls/IsSessionFlag3700Set.c](../src/overlays/ov035/calls/IsSessionFlag3700Set.c).

```c
void IsSessionFlag3700Set(void);
```

The native void declaration hides the predicate result consumed by the caller in R0. Its semantic input is the fixed numeric session flag 0x3700.

Demonstrated behavior and evidence:

- EU wrapper aliases callee to IsSessionFlagSet. Source: [eu/src/overlays/ov035/calls/IsSessionFlag3700Set.c:1-3](../src/overlays/ov035/calls/IsSessionFlag3700Set.c).
- Tail-call passes numeric flag 0x3700; no message operation. Source: [src/ov035/unclassified_helpers/ShowMovieMessage3700_020baf88.c:1-8](../../src/ov035/unclassified_helpers/ShowMovieMessage3700_020baf88.c).
- Caller consumes R0 as a boolean and folds it into bit zero. Source: [eu/src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c:1-17](../src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c).

Additional native ABI observations:

- Shared source declares void, but tail-call returns the flag predicate result and the EU caller consumes it as int. Correct the return prototype only with matching ABI verification.

## GetAreaSceneDefinitionIndex

Identity: `ov035:020bafc4`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov035_020bafc4`.

EU entrypoint: [eu/src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c](../src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c).

```c
int GetAreaSceneDefinitionIndex(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns signed definition selector byte at work+0x1e. Source: [eu/src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c:1-7](../src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c).
- This selector minus one chooses the scene data record in rpg.z. Source: [src/ov035/shared_engine/LoadMovieClipHeader_020baa28.c:1-64](../../src/ov035/shared_engine/LoadMovieClipHeader_020baa28.c).

## GetAreaObjectListId

Identity: `ov035:020bafd4`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov035_020bafd4`.

EU entrypoint: [eu/src/overlays/ov035/calls/GetAreaObjectListId.c](../src/overlays/ov035/calls/GetAreaObjectListId.c).

```c
int GetAreaObjectListId(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns signed byte at scene work+0x43. Source: [eu/src/overlays/ov035/calls/GetAreaObjectListId.c:1-7](../src/overlays/ov035/calls/GetAreaObjectListId.c).
- FieldState.tracker starts at +0x40; its objectListId byte at +3 gates area object switching. Source: [src/ov040/unclassified_helpers/SwitchAreaObjects_020bc650.c:1-78](../../src/ov040/unclassified_helpers/SwitchAreaObjects_020bc650.c).

## GetAreaSceneSessionFlagPair

Identity: `ov035:020bb110`, THUMB, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov035_020bb110`.

EU entrypoint: [eu/src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c](../src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c).

```c
u8 GetAreaSceneSessionFlagPair(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns (flag 0x3701 ? 2 : 0) | (flag 0x3700 ? 1 : 0). Source: [eu/src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c:1-17](../src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c).
- EU wrapper aliases the called function to IsSessionFlagSet; no message is displayed. Source: [eu/src/overlays/ov035/calls/IsSessionFlag3700Set.c:1-3](../src/overlays/ov035/calls/IsSessionFlag3700Set.c).
- Wrapper tail-calls the session flag predicate for 0x3700. Source: [src/ov035/unclassified_helpers/ShowMovieMessage3700_020baf88.c:1-8](../../src/ov035/unclassified_helpers/ShowMovieMessage3700_020baf88.c).

Contract limits:

- Neither bit is assigned a story label.

## ResetAreaSceneSelectionFlags

Identity: `ov035:020bb28c`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov035_020bb28c`.

EU entrypoint: [eu/src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c](../src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c).

```c
void ResetAreaSceneSelectionFlags(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Clears flags 0x3702,0x379b,0x3723,0x3724 and writes zero to 10-bit selection 0x3791. Source: [eu/src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c:1-12](../src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c).

Contract limits:

- Numeric session meanings remain explicit.

## CountAreaEntriesOfKind0

Identity: `ov035:020bb2c0`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov035_020bb2c0`.

EU entrypoint: [eu/src/overlays/ov035/calls/CountAreaEntriesOfKind0.c](../src/overlays/ov035/calls/CountAreaEntriesOfKind0.c).

```c
int CountAreaEntriesOfKind0(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Counts entries below scene work+0x42 whose seven-bit kind is zero. Source: [eu/src/overlays/ov035/calls/CountAreaEntriesOfKind0.c:1-23](../src/overlays/ov035/calls/CountAreaEntriesOfKind0.c).
- Getter reads seven-bit kind at entry+1; out-of-range returns 0xff. Source: [src/ov035/unclassified_helpers/GetMovieEntryKind_020badf0.c:1-31](../../src/ov035/unclassified_helpers/GetMovieEntryKind_020badf0.c).

Contract limits:

- Kind 0 is kept numeric; no unproven human category assigned.

## SetAreaSceneDrawEnabled

Identity: `ov035:020bb2f4`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov035_020bb2f4`.

EU entrypoint: [eu/src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c](../src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c).

```c
void SetAreaSceneDrawEnabled(int enable);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Sets or clears scene flags bit 0x4. Source: [eu/src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c:1-11](../src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c).
- The frame dispatcher invokes func_ov035_020ba75c exactly when flags&4. Source: [src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c:1-75](../../src/ov035/shared_engine/RunMovieSceneFrame_020ba458.c).
- The referenced callback dispatches scene draw paths, camera update and reward model rendering. Source: [src/ov035/reviewed_helpers/func_ov035_020ba75c.c:1-48](../../src/ov035/reviewed_helpers/func_ov035_020ba75c.c).
- EU equivalent of that callback establishes the scene draw operation. Source: [eu/src/overlays/ov035/calls/DispatchSceneDrawCallbacks.c:1-50](../src/overlays/ov035/calls/DispatchSceneDrawCallbacks.c).

## QueueAreaSceneSoundState

Identity: `ov035:020bb354`, THUMB, native extent 68 bytes (including any configured pool). Previous symbol: `func_ov035_020bb354`.

EU entrypoint: [eu/src/overlays/ov035/calls/QueueAreaSceneSoundState.c](../src/overlays/ov035/calls/QueueAreaSceneSoundState.c).

```c
void QueueAreaSceneSoundState(int stopSeq);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Queues the area sound archives and arc command 0x10; optional sequence status 2 and flag-0x360c hooks are preserved. Source: [eu/src/overlays/ov035/calls/QueueAreaSceneSoundState.c:1-23](../src/overlays/ov035/calls/QueueAreaSceneSoundState.c).

Contract limits:

- Commands 0x1a0,0x10 and status 2 are not renamed as stop/start without the sound dispatcher contract.

## ApplyAreaMaterialFadeEntry

Identity: `ov035:020bb468`, THUMB, native extent 92 bytes (including any configured pool). Previous symbol: `func_ov035_020bb468`.

EU entrypoint: [eu/src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c](../src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c).

```c
void ApplyAreaMaterialFadeEntry(int index);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Reads 4-byte material fade entry, sets material alpha and polygon ID 40, disables culling when alpha is zero and sets cull mode 2 when transitioning from zero. Source: [eu/src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c:1-74](../src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c).

Contract limits:

- The signed material index and plain-byte alpha preserve original signedness.

## ReleaseAreaFadeModelIfLoaded

Identity: `ov035:020bb66c`, THUMB, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov035_020bb66c`.

EU entrypoint: [eu/src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c](../src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c).

```c
void ReleaseAreaFadeModelIfLoaded(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If fade work+0x10b is nonzero releases the embedded model resource and clears its loaded marker. Source: [eu/src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c:1-14](../src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c).
- The global points to dedicated material fade work. Source: [eu/src/overlays/ov035/calls/CreateMaterialFadeWork.c:1-6](../src/overlays/ov035/calls/CreateMaterialFadeWork.c).

Contract limits:

- Owner is this fade-work global only.

## FreeAreaMaterialFadeWork

Identity: `ov035:020bb7a8`, THUMB, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov035_020bb7a8`.

EU entrypoint: [eu/src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c](../src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c).

```c
void FreeAreaMaterialFadeWork(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Releases the fade model if loaded, then frees the entries pointer at +0x10c and the fade work allocation. Source: [eu/src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c:1-11](../src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c).

Contract limits:

- The global pointer is not cleared by this function.

## ReleaseAreaGaugeBuffers

Identity: `ov035:020bc0e4`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov035_020bc0e4`.

EU entrypoint: [eu/src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c](../src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c).

```c
void ReleaseAreaGaugeBuffers(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Frees gauge source, upload buffer, frame file and cell buffer; clears the global current work pointer. Source: [eu/src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c:1-17](../src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c).
- Constructor uses current TaskObject work and fills these four separately allocated buffers. Source: [src/ov035/unclassified_helpers/InitBarGauge_020bc00c.c:1-68](../../src/ov035/unclassified_helpers/InitBarGauge_020bc00c.c).

Contract limits:

- Task-owned work itself is not freed here.

## DisarmAreaSequence1AndInvokeRecord5Callback

Identity: `ov035:020bc3ac`, THUMB, native extent 42 bytes (including any configured pool). Previous symbol: `func_ov035_020bc3ac`.

EU entrypoint: [eu/src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c](../src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c).

```c
void DisarmAreaSequence1AndInvokeRecord5Callback(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Disarms tag sequence 1 and invokes callback +0x40 of active record 5 using the scene tag tracker. Source: [eu/src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c:1-18](../src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c).

Contract limits:

- IDs and callback slot are retained operationally; no narrative event name inferred.

## ArmAreaSequence1AtGaugeMax

Identity: `ov035:020bc3d8`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov035_020bc3d8`.

EU entrypoint: [eu/src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c](../src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c).

```c
void ArmAreaSequence1AtGaugeMax(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- If current area gauge level at +0x18 equals 100, arms tag sequence 1. Source: [eu/src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c:1-20](../src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c).
- Gauge level setter uses the same max-100 rule to arm sequence 1 and reverses it when leaving 100. Source: [src/ov035/unclassified_helpers/SetGaugeLevel_020bbef0.c:1-43](../../src/ov035/unclassified_helpers/SetGaugeLevel_020bbef0.c).

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov035/calls/AreaSceneState_LoadInitialResources.c AreaSceneState_LoadInitialResources --thumb
python tools/verify_idx.py src/overlays/ov035/calls/AreaSceneState_WaitForListNodes.c AreaSceneState_WaitForListNodes --thumb
python tools/verify_idx.py src/overlays/ov035/calls/AreaSceneState_StartOverlay40AfterLoad.c AreaSceneState_StartOverlay40AfterLoad --thumb
python tools/verify_idx.py src/overlays/ov035/calls/AreaSceneState_EndOverlay41WhenReady.c AreaSceneState_EndOverlay41WhenReady --thumb
python tools/verify_idx.py src/overlays/ov035/auto/AreaSceneState_StartOverlay40Mode0.c AreaSceneState_StartOverlay40Mode0 --thumb
python tools/verify_idx.py src/overlays/ov035/calls/AreaSceneState_ReleaseResourcesAndExit.c AreaSceneState_ReleaseResourcesAndExit --thumb
python tools/verify_idx.py src/overlays/ov035/calls/CreateAreaSceneTask.c CreateAreaSceneTask --thumb
python tools/verify_idx.py src/overlays/ov035/auto/GetAreaSceneTransitionFlag.c GetAreaSceneTransitionFlag --thumb
python tools/verify_idx.py src/overlays/ov035/calls/LoadAreaSceneDefinition.c LoadAreaSceneDefinition --thumb
python tools/verify_idx.py src/overlays/ov035/auto/AreaSceneCleanupNoOp.c AreaSceneCleanupNoOp --thumb
python tools/verify_idx.py src/overlays/ov035/calls/SetAreaSceneDefinitionParams.c SetAreaSceneDefinitionParams --thumb
python tools/verify_idx.py src/overlays/ov035/calls/GetCurrentAreaIndex.c GetCurrentAreaIndex --thumb
python tools/verify_idx.py src/overlays/ov035/auto/GetOverlay41PhaseActiveFlag.c GetOverlay41PhaseActiveFlag --thumb
python tools/verify_idx.py src/overlays/ov035/calls/SelectPersistentAreaSceneTableValue.c SelectPersistentAreaSceneTableValue --thumb
python tools/verify_idx.py src/overlays/ov035/calls/IsSessionFlag3700Set.c IsSessionFlag3700Set --thumb
python tools/verify_idx.py src/overlays/ov035/calls/GetAreaSceneDefinitionIndex.c GetAreaSceneDefinitionIndex --thumb
python tools/verify_idx.py src/overlays/ov035/calls/GetAreaObjectListId.c GetAreaObjectListId --thumb
python tools/verify_idx.py src/overlays/ov035/calls/GetAreaSceneSessionFlagPair.c GetAreaSceneSessionFlagPair --thumb
python tools/verify_idx.py src/overlays/ov035/calls/ResetAreaSceneSelectionFlags.c ResetAreaSceneSelectionFlags --thumb
python tools/verify_idx.py src/overlays/ov035/calls/CountAreaEntriesOfKind0.c CountAreaEntriesOfKind0 --thumb
python tools/verify_idx.py src/overlays/ov035/calls/SetAreaSceneDrawEnabled.c SetAreaSceneDrawEnabled --thumb
python tools/verify_idx.py src/overlays/ov035/calls/QueueAreaSceneSoundState.c QueueAreaSceneSoundState --thumb
python tools/verify_idx.py src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c ApplyAreaMaterialFadeEntry --thumb
python tools/verify_idx.py src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c ReleaseAreaFadeModelIfLoaded --thumb
python tools/verify_idx.py src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c FreeAreaMaterialFadeWork --thumb
python tools/verify_idx.py src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c ReleaseAreaGaugeBuffers --thumb
python tools/verify_idx.py src/overlays/ov035/calls/DisarmAreaSequence1AndInvokeRecord5Callback.c DisarmAreaSequence1AndInvokeRecord5Callback --thumb
python tools/verify_idx.py src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c ArmAreaSequence1AtGaugeMax --thumb
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
