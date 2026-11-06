# Overlay028 field scene lifecycle

This document records 17 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

These functions belong to this overlay's field-scene task, not the movie decoder. The descriptor constructor uses task-owned work, and creation stores a separate TaskObject handle. Startup readiness returns false without work and otherwise tests that startup flag 0x1 has cleared; its writer clears that flag after panel readiness.

State handlers return a native word interpreted as a signed next-state value. The all-ones -1 result retains the current state; a nonnegative result replaces it. Flag 0x8000 requests immediate repeat dispatch. Update and draw callbacks are separately controlled by flags 8 and 4. A return such as state 7 is a state-machine decision, not a BOOL. Waiters test the predicates named in their individual evidence; they do not promise that unrelated asynchronous activity is complete.

The event-record transition copies signed bytes at record +1/+3 back into two u8 fields at SessionState +0x2744/+0x2745. This proves byte transfer and narrowing, not area or destination-ID meaning. The signed mode byte at scene work +8 is passed to the screen-mode helper; it is not a coordinate.

Normal update steps are 0x1000, one unit in 12-fraction-bit fixed point. In this owner's slowdown path, flag 0x40 selects 0x100 for party/stage updates, one sixteenth of normal. Actor callbacks and scene-object updates retain 0x1000. The update's mode input suppresses the scene-animation/object/stage/prize-orb subset when nonzero, while party and actor-callback updates still run.

The TaskObject +0x28 signal getter normalizes nonzero to true. It neither interprets the signal word nor tests scheduler destruction state. Pointers and work obtained from the task/session remain borrowed; creating a task does not transfer its enclosing work to a caller-owned allocation.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov028:020ba69c` | ARM | `func_ov028_020ba69c` | `Ov028SceneState_PushVramWhenIdle` | [eu/src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c](../src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c) |
| `ov028:020ba6d4` | ARM | `func_ov028_020ba6d4` | `FieldSceneState_RestoreActorsAndLoadShadow` | [eu/src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c](../src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c) |
| `ov028:020ba720` | ARM | `func_ov028_020ba720` | `Ov028SceneState_WaitForListNodes` | [eu/src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c](../src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c) |
| `ov028:020ba758` | ARM | `func_ov028_020ba758` | `FieldSceneState_WaitResourceSlotsAndReset` | [eu/src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c](../src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c) |
| `ov028:020ba778` | ARM | `func_ov028_020ba778` | `Ov028SceneState_FinishMenuResourceLoad` | [eu/src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c](../src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c) |
| `ov028:020bab20` | ARM | `func_ov028_020bab20` | `Ov028SceneState_StoreEventRecordBytes` | [eu/src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c](../src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c) |
| `ov028:020bab68` | ARM | `func_ov028_020bab68` | `Ov028SceneState_BeginScreenModeTransition` | [eu/src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c](../src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c) |
| `ov028:020bac30` | ARM | `func_ov028_020bac30` | `FieldSceneState_ResetFieldValueWhenScreenIdle` | [eu/src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c](../src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c) |
| `ov028:020bac5c` | ARM | `func_ov028_020bac5c` | `FieldSceneState_EndSlowdownWhenScreenIdle` | [eu/src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c](../src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c) |
| `ov028:020bacd0` | ARM | `func_ov028_020bacd0` | `Ov028SceneState_BeginFadeOutWhenIdle` | [eu/src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c](../src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c) |
| `ov028:020bad1c` | ARM | `func_ov028_020bad1c` | `Ov028SceneState_WaitFadeOut` | [eu/src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c](../src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c) |
| `ov028:020bae68` | ARM | `func_ov028_020bae68` | `DrawOv028FieldScene` | [eu/src/overlays/ov028/calls/DrawOv028FieldScene.c](../src/overlays/ov028/calls/DrawOv028FieldScene.c) |
| `ov028:020bae88` | ARM | `func_ov028_020bae88` | `UpdateOv028FieldScene` | [eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c](../src/overlays/ov028/calls/UpdateOv028FieldScene.c) |
| `ov028:020bafe8` | ARM | `func_ov028_020bafe8` | `CreateOv028FieldSceneTask` | [eu/src/overlays/ov028/calls/CreateOv028FieldSceneTask.c](../src/overlays/ov028/calls/CreateOv028FieldSceneTask.c) |
| `ov028:020bb00c` | ARM | `func_ov028_020bb00c` | `IsFieldSceneStartupComplete` | [eu/src/overlays/ov028/calls/IsFieldSceneStartupComplete.c](../src/overlays/ov028/calls/IsFieldSceneStartupComplete.c) |
| `ov028:020bb080` | ARM | `func_ov028_020bb080` | `HasFieldSceneTaskSignal` | [eu/src/overlays/ov028/calls/HasFieldSceneTaskSignal.c](../src/overlays/ov028/calls/HasFieldSceneTaskSignal.c) |
| `ov028:020bb1b4` | ARM | `func_ov028_020bb1b4` | `BeginFieldSceneSlowdownTransition` | [eu/src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c](../src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c) |

## Ov028SceneState_PushVramWhenIdle

Identity: `ov028:020ba69c`, ARM, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov028_020ba69c`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c](../src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c).

```c
u32 Ov028SceneState_PushVramWhenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns -1 while external busy predicate is nonzero; otherwise pushes VRAM state, requests immediate dispatch and returns state1. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c:1-17](../src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c:1-17](../src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

## FieldSceneState_RestoreActorsAndLoadShadow

Identity: `ov028:020ba6d4`, ARM, native extent 76 bytes (including any configured pool). Previous symbol: `func_ov028_020ba6d4`.

EU entrypoint: [eu/src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c](../src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c).

```c
u32 FieldSceneState_RestoreActorsAndLoadShadow(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Restores session actors, conditionally resets the mode byte and loads the common shadow model; requests immediate next state2. Source: [eu/src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c:1-17](../src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c:1-17](../src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

Contract limits:

- Retains the special mode3 exception.

## Ov028SceneState_WaitForListNodes

Identity: `ov028:020ba720`, ARM, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov028_020ba720`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c](../src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c).

```c
u32 Ov028SceneState_WaitForListNodes(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits until all list nodes are ready, invokes completion hook and immediately advances to state3. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c:1-17](../src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c:1-17](../src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

## FieldSceneState_WaitResourceSlotsAndReset

Identity: `ov028:020ba758`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov028_020ba758`.

EU entrypoint: [eu/src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c](../src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c).

```c
u32 FieldSceneState_WaitResourceSlotsAndReset(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for resource slot loading, then resets scene slots and returns state4. Source: [eu/src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c:1-15](../src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c:1-15](../src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

Additional native ABI observations:

- Current declaration passes loading status as an argument to ResetSceneSlots; verify real callee ABI before changing parameters.

## Ov028SceneState_FinishMenuResourceLoad

Identity: `ov028:020ba778`, ARM, native extent 132 bytes (including any configured pool). Previous symbol: `func_ov028_020ba778`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c](../src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c).

```c
u32 Ov028SceneState_FinishMenuResourceLoad(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- After menu resource readiness, applies scene/list completion hooks, sound parameters, area archives and panel header; immediately advances to state5. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c:1-46](../src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c:1-46](../src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

Contract limits:

- Do not inherit pointer/text types from synthetic GetSceneEntryResourceId aliases without checking their real definitions.

## Ov028SceneState_StoreEventRecordBytes

Identity: `ov028:020bab20`, ARM, native extent 72 bytes (including any configured pool). Previous symbol: `func_ov028_020bab20`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c](../src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c).

```c
u32 Ov028SceneState_StoreEventRecordBytes(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Obtains current event-context record; copies its signed bytes1and3 into the session transition-byte pair, sets scene flag2 and returns state7. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c:1-21](../src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c).
- Returns current EventContext+0xe8 pointer, or0 for absent owner. Source: [GetPendingWorldEntryData.c](../src/overlays/ov001/calls/GetPendingWorldEntryData.c).
- EU wrapper identifies signed byte1 getter. Source: [eu/src/overlays/ov001/auto/GetSignedByteAt1.c:1-2](../src/overlays/ov001/auto/GetSignedByteAt1.c).
- Reads signed byte at input+1. Source: [src/ov001/shared_engine/GetSignedByteAt1_02067f9c.c:1-4](../../src/ov001/shared_engine/GetSignedByteAt1_02067f9c.c).
- Reads signed byte at input+3. Source: [src/ov001/shared_engine/GetSignedByteAt3_02067f8c.c:1-4](../../src/ov001/shared_engine/GetSignedByteAt3_02067f8c.c).
- Destination helper only stores u8 values at SessionState+0x2744/+0x2745. Source: [eu/src/overlays/ov001/calls/func_ov001_02063848.c:1-9](../src/overlays/ov001/calls/func_ov001_02063848.c).

Contract limits:

- No area/scene destination IDs inferred from the byte pair. Signed values narrow back to bytes.

Additional native ABI observations:

- Existing GetSignedByteAt1(void) declaration omits the live R0 pointer argument; verify ARM call flow before repairing signatures.

## Ov028SceneState_BeginScreenModeTransition

Identity: `ov028:020bab68`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov028_020bab68`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c](../src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c).

```c
u32 Ov028SceneState_BeginScreenModeTransition(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Passes signed scene mode byte+8 to the screen mode transition helper, sets flag0x20 and returns state10. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c:1-13](../src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c:1-13](../src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

Contract limits:

- The mode byte is not a position coordinate.

## FieldSceneState_ResetFieldValueWhenScreenIdle

Identity: `ov028:020bac30`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov028_020bac30`.

EU entrypoint: [eu/src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c](../src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c).

```c
u32 FieldSceneState_ResetFieldValueWhenScreenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen transition idle, writes (-3,3) to the field state and marks the field value negative, then returns state7. Source: [eu/src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c:1-17](../src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c:1-17](../src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

Contract limits:

- Meaning of the numeric field-state pair remains explicit.

## FieldSceneState_EndSlowdownWhenScreenIdle

Identity: `ov028:020bac5c`, ARM, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov028_020bac5c`.

EU entrypoint: [eu/src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c](../src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c).

```c
u32 FieldSceneState_EndSlowdownWhenScreenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen idle, clears flag0x40 and returns state7. Source: [eu/src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c:1-15](../src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c:1-15](../src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).
- Flag0x40 selects 0x100 instead of0x1000 timestep for party and stage updates. Source: [eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c:1-28](../src/overlays/ov028/calls/UpdateOv028FieldScene.c).

## Ov028SceneState_BeginFadeOutWhenIdle

Identity: `ov028:020bacd0`, ARM, native extent 76 bytes (including any configured pool). Previous symbol: `func_ov028_020bacd0`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c](../src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c).

```c
u32 Ov028SceneState_BeginFadeOutWhenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Unless flag0x10 bypasses the busy gate, waits for the external activity to clear; once screen is idle begins fade-out with the scene mode and returns state16. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c:1-24](../src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c:1-24](../src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

## Ov028SceneState_WaitFadeOut

Identity: `ov028:020bad1c`, ARM, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov028_020bad1c`.

EU entrypoint: [eu/src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c](../src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c).

```c
u32 Ov028SceneState_WaitFadeOut(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen idle, sets immediate-dispatch flag and returns state17. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c:1-15](../src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c:1-15](../src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

Contract limits:

- Only the screen-idle completion predicate is tested.

## DrawOv028FieldScene

Identity: `ov028:020bae68`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov028_020bae68`.

EU entrypoint: [eu/src/overlays/ov028/calls/DrawOv028FieldScene.c](../src/overlays/ov028/calls/DrawOv028FieldScene.c).

```c
void DrawOv028FieldScene(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates active camera mode with argument1, draws visible scene slots and event callbacks, updates actor billboards and invokes the final field draw hook. Source: [eu/src/overlays/ov028/calls/DrawOv028FieldScene.c:1-16](../src/overlays/ov028/calls/DrawOv028FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/DrawOv028FieldScene.c:1-16](../src/overlays/ov028/calls/DrawOv028FieldScene.c).
- State dispatcher stores nonnegative handler results and repeats for flag 0x8000; flags 8 and4 control update/draw callbacks. Source: [eu/src/overlays/ov028/calls/RunSceneStateMachine.c:1-33](../src/overlays/ov028/calls/RunSceneStateMachine.c).

## UpdateOv028FieldScene

Identity: `ov028:020bae88`, ARM, native extent 104 bytes (including any configured pool). Previous symbol: `func_ov028_020bae88`.

EU entrypoint: [eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c](../src/overlays/ov028/calls/UpdateOv028FieldScene.c).

```c
void UpdateOv028FieldScene(s32 mode);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Always updates party entries and actor callbacks. When mode is zero also updates scene animation, field objects, stage and prize orbs. Source: [eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c:1-28](../src/overlays/ov028/calls/UpdateOv028FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c:1-28](../src/overlays/ov028/calls/UpdateOv028FieldScene.c).

Contract limits:

- For ov028 only, flag0x40 changes party/stage timestep from0x1000 to0x100; actor and scene-object steps stay0x1000.

## CreateOv028FieldSceneTask

Identity: `ov028:020bafe8`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov028_020bafe8`.

EU entrypoint: [eu/src/overlays/ov028/calls/CreateOv028FieldSceneTask.c](../src/overlays/ov028/calls/CreateOv028FieldSceneTask.c).

```c
void CreateOv028FieldSceneTask(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates this overlay's own scene TaskObject descriptor and stores the returned task handle. Source: [eu/src/overlays/ov028/calls/CreateOv028FieldSceneTask.c:1-5](../src/overlays/ov028/calls/CreateOv028FieldSceneTask.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [src/ov028/reviewed_helpers/func_ov028_020bafc8.c:1-7](../../src/ov028/reviewed_helpers/func_ov028_020bafc8.c).

Contract limits:

- This is field scene task creation; the inherited MobiClip source filename does not establish video behavior.

## IsFieldSceneStartupComplete

Identity: `ov028:020bb00c`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov028_020bb00c`.

EU entrypoint: [eu/src/overlays/ov028/calls/IsFieldSceneStartupComplete.c](../src/overlays/ov028/calls/IsFieldSceneStartupComplete.c).

```c
BOOL IsFieldSceneStartupComplete(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false for absent work, otherwise true when flag0x1 has cleared. Source: [eu/src/overlays/ov028/calls/IsFieldSceneStartupComplete.c:1-19](../src/overlays/ov028/calls/IsFieldSceneStartupComplete.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/IsFieldSceneStartupComplete.c:1-19](../src/overlays/ov028/calls/IsFieldSceneStartupComplete.c).
- After panel readiness, startup state clears exactly flag0x1 before entering running state7. Source: [eu/src/overlays/ov028/calls/SceneState_WaitPanelReady.c:1-22](../src/overlays/ov028/calls/SceneState_WaitPanelReady.c).

## HasFieldSceneTaskSignal

Identity: `ov028:020bb080`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov028_020bb080`.

EU entrypoint: [eu/src/overlays/ov028/calls/HasFieldSceneTaskSignal.c](../src/overlays/ov028/calls/HasFieldSceneTaskSignal.c).

```c
BOOL HasFieldSceneTaskSignal(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Tests current field TaskObject word+0x28 for nonzero. Source: [eu/src/overlays/ov028/calls/HasFieldSceneTaskSignal.c:1-10](../src/overlays/ov028/calls/HasFieldSceneTaskSignal.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/HasFieldSceneTaskSignal.c:1-10](../src/overlays/ov028/calls/HasFieldSceneTaskSignal.c).

Contract limits:

- Return is a normalized presence predicate; semantic meaning of the signal value itself remains unspecified.

## BeginFieldSceneSlowdownTransition

Identity: `ov028:020bb1b4`, ARM, native extent 108 bytes (including any configured pool). Previous symbol: `func_ov028_020bb1b4`.

EU entrypoint: [eu/src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c](../src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c).

```c
void BeginFieldSceneSlowdownTransition(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Begins screen transition mode2, pauses field entries, invokes actor0 reset callback if set, marks the standard camera and enables flag0x40. Source: [eu/src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c:1-31](../src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c:1-31](../src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c).
- Flag0x40 causes party and stage update step0x100 instead of0x1000. Source: [eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c:1-28](../src/overlays/ov028/calls/UpdateOv028FieldScene.c).

Contract limits:

- Despite nearby half-rate names, the effective selected timestep is1/16 of normal.

Additional native ABI observations:

- FX_Div(0x10000,0x40000) result may feed a live ARM register not represented by the current func_ov001_0206a8c8(void) prototype. Do not erase this computation as unused.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c Ov028SceneState_PushVramWhenIdle
python tools/verify_idx.py src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c FieldSceneState_RestoreActorsAndLoadShadow
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c Ov028SceneState_WaitForListNodes
python tools/verify_idx.py src/overlays/ov028/calls/FieldSceneState_WaitResourceSlotsAndReset.c FieldSceneState_WaitResourceSlotsAndReset
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c Ov028SceneState_FinishMenuResourceLoad
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c Ov028SceneState_StoreEventRecordBytes
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c Ov028SceneState_BeginScreenModeTransition
python tools/verify_idx.py src/overlays/ov028/calls/FieldSceneState_ResetFieldValueWhenScreenIdle.c FieldSceneState_ResetFieldValueWhenScreenIdle
python tools/verify_idx.py src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c FieldSceneState_EndSlowdownWhenScreenIdle
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c Ov028SceneState_BeginFadeOutWhenIdle
python tools/verify_idx.py src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c Ov028SceneState_WaitFadeOut
python tools/verify_idx.py src/overlays/ov028/calls/DrawOv028FieldScene.c DrawOv028FieldScene
python tools/verify_idx.py src/overlays/ov028/calls/UpdateOv028FieldScene.c UpdateOv028FieldScene
python tools/verify_idx.py src/overlays/ov028/calls/CreateOv028FieldSceneTask.c CreateOv028FieldSceneTask
python tools/verify_idx.py src/overlays/ov028/calls/IsFieldSceneStartupComplete.c IsFieldSceneStartupComplete
python tools/verify_idx.py src/overlays/ov028/calls/HasFieldSceneTaskSignal.c HasFieldSceneTaskSignal
python tools/verify_idx.py src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c BeginFieldSceneSlowdownTransition
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
