# Overlay030 field scene lifecycle

This document records 19 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The field-scene TaskObject descriptor and this owner's state dispatcher establish these functions' roles. State handlers return a native word interpreted as a signed status: -1 retains the current state, a nonnegative result selects the next state, and flag 0x8000 requests another dispatch immediately. Update/draw enable bits are separate; flag 0x4 specifically guards this owner's draw callback.

Startup bit 0x1 clears after panel readiness, and the readiness predicate checks that exact writer/reader pair. The scene's raw lock byte at +9 controls camera enable through its setter; the getter preserves the byte rather than normalizing it to BOOL. Exit requests store the mode byte at +8 and set 0x4000; the state consumer pauses field entries and enters state 14 before the later fade uses the stored mode.

The record-byte transition copies signed bytes +1/+3 into the two session u8 fields at +0x2744/+0x2745. No destination-ID role is assigned. The transition callback installed in session slot 10 returns a raw mask from 0x60; values are not collapsed to true. Session slot 10 is read by `InvokeSessionCheckCallbackOrDefault`, whose result can suppress the normal HUD sound path.

Carried-actor escape configuration is a separate supplied object. Clearing it zeroes its first four words and returns that pointer; the marker index at +0x10 remains unchanged. The four cleared words retain opaque meanings. Likewise the group/model-slot draw helper's owner is specific to its +0x18c list, not a universal field-scene or movie layout.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov030:020ba588` | THUMB | `func_ov030_020ba588` | `Ov030SceneState_PushVramWhenIdle` | [eu/src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c](../src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c) |
| `ov030:020ba5e8` | THUMB | `func_ov030_020ba5e8` | `Ov030SceneState_WaitForListNodes` | [eu/src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c](../src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c) |
| `ov030:020ba62c` | THUMB | `func_ov030_020ba62c` | `Ov030SceneState_FinishMenuResourceLoad` | [eu/src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c](../src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c) |
| `ov030:020ba774` | THUMB | `func_ov030_020ba774` | `Ov030SceneState_FinishStartupWhenPanelReady` | [eu/src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c](../src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c) |
| `ov030:020ba844` | THUMB | `func_ov030_020ba844` | `Ov030SceneState_StoreEventRecordBytes` | [eu/src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c](../src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c) |
| `ov030:020ba874` | THUMB | `func_ov030_020ba874` | `Ov030SceneState_BeginScreenModeTransition` | [eu/src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c](../src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c) |
| `ov030:020ba930` | THUMB | `func_ov030_020ba930` | `Ov030SceneState_FinishSlowdownTransition` | [eu/src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c](../src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c) |
| `ov030:020ba964` | THUMB | `func_ov030_020ba964` | `Ov030SceneState_StartIdleObjects` | [eu/src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c](../src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c) |
| `ov030:020ba98c` | THUMB | `func_ov030_020ba98c` | `Ov030SceneState_BeginFadeOutWhenIdle` | [eu/src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c](../src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c) |
| `ov030:020ba9c8` | THUMB | `func_ov030_020ba9c8` | `Ov030SceneState_WaitFadeOut` | [eu/src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c](../src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c) |
| `ov030:020baab8` | THUMB | `func_ov030_020baab8` | `DrawOv030FieldScene` | [eu/src/overlays/ov030/calls/DrawOv030FieldScene.c](../src/overlays/ov030/calls/DrawOv030FieldScene.c) |
| `ov030:020babc8` | THUMB | `func_ov030_020babc8` | `CreateOv030FieldSceneTask` | [eu/src/overlays/ov030/calls/CreateOv030FieldSceneTask.c](../src/overlays/ov030/calls/CreateOv030FieldSceneTask.c) |
| `ov030:020babe0` | THUMB | `func_ov030_020babe0` | `IsOv030SceneStartupComplete` | [eu/src/overlays/ov030/calls/IsOv030SceneStartupComplete.c](../src/overlays/ov030/calls/IsOv030SceneStartupComplete.c) |
| `ov030:020bac14` | THUMB | `func_ov030_020bac14` | `RequestOv030SceneExit` | [eu/src/overlays/ov030/calls/RequestOv030SceneExit.c](../src/overlays/ov030/calls/RequestOv030SceneExit.c) |
| `ov030:020bb230` | THUMB | `func_ov030_020bb230` | `GetOv030FieldTransitionFlags` | [eu/src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c](../src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c) |
| `ov030:020bb388` | THUMB | `func_ov030_020bb388` | `GetOv030SceneLock` | [eu/src/overlays/ov030/auto/GetOv030SceneLock.c](../src/overlays/ov030/auto/GetOv030SceneLock.c) |
| `ov030:020bb460` | THUMB | `func_ov030_020bb460` | `SetOv030SceneDrawEnabled` | [eu/src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c](../src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c) |
| `ov030:020bb488` | THUMB | `func_ov030_020bb488` | `ClearCarriedActorEscapeConfig` | [eu/src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c](../src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c) |
| `ov030:020bcb3c` | THUMB | `func_ov030_020bcb3c` | `UpdateSceneGroupsAndDrawModelSlots` | [eu/src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c](../src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c) |

## Ov030SceneState_PushVramWhenIdle

Identity: `ov030:020ba588`, THUMB, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov030_020ba588`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c](../src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c).

```c
u32 Ov030SceneState_PushVramWhenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns -1 while external busy predicate is nonzero; otherwise pushes VRAM state, requests immediate dispatch and returns state1. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c:1-18](../src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c:1-18](../src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

## Ov030SceneState_WaitForListNodes

Identity: `ov030:020ba5e8`, THUMB, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov030_020ba5e8`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c](../src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c).

```c
u32 Ov030SceneState_WaitForListNodes(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits until all list nodes are ready, invokes completion hook and immediately advances to state3. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c:1-18](../src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c:1-18](../src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

## Ov030SceneState_FinishMenuResourceLoad

Identity: `ov030:020ba62c`, THUMB, native extent 108 bytes (including any configured pool). Previous symbol: `func_ov030_020ba62c`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c](../src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c).

```c
u32 Ov030SceneState_FinishMenuResourceLoad(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- After menu resource readiness, applies scene/list completion hooks, sound parameters, area archives and panel header; immediately advances to state5. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c:1-47](../src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c:1-47](../src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

Contract limits:

- Do not inherit pointer/text types from synthetic GetSceneEntryResourceId aliases without checking their real definitions.

## Ov030SceneState_FinishStartupWhenPanelReady

Identity: `ov030:020ba774`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov030_020ba774`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c](../src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c).

```c
u32 Ov030SceneState_FinishStartupWhenPanelReady(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for panel ready, clears startup flag0x1, stores external field value0 and returns state7. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c:1-20](../src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c:1-20](../src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

## Ov030SceneState_StoreEventRecordBytes

Identity: `ov030:020ba844`, THUMB, native extent 48 bytes (including any configured pool). Previous symbol: `func_ov030_020ba844`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c](../src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c).

```c
u32 Ov030SceneState_StoreEventRecordBytes(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Obtains current event-context record; copies its signed bytes1and3 into the session transition-byte pair, sets scene flag2 and returns state7. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c:1-22](../src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c).
- Returns current EventContext+0xe8 pointer, or0 for absent owner. Source: [GetPendingWorldEntryData.c](../src/overlays/ov001/calls/GetPendingWorldEntryData.c).
- EU wrapper identifies signed byte1 getter. Source: [eu/src/overlays/ov001/auto/GetSignedByteAt1.c:1-2](../src/overlays/ov001/auto/GetSignedByteAt1.c).
- Reads signed byte at input+1. Source: [src/ov001/shared_engine/GetSignedByteAt1_02067f9c.c:1-4](../../src/ov001/shared_engine/GetSignedByteAt1_02067f9c.c).
- Reads signed byte at input+3. Source: [src/ov001/shared_engine/GetSignedByteAt3_02067f8c.c:1-4](../../src/ov001/shared_engine/GetSignedByteAt3_02067f8c.c).
- Destination helper only stores u8 values at SessionState+0x2744/+0x2745. Source: [eu/src/overlays/ov001/calls/StoreFieldSessionEntryPayloadPair.c:1-9](../src/overlays/ov001/calls/StoreFieldSessionEntryPayloadPair.c).

Contract limits:

- No area/scene destination IDs inferred from the byte pair. Signed values narrow back to bytes.

Additional native ABI observations:

- Existing GetSignedByteAt1(void) declaration omits the live R0 pointer argument; verify ARM call flow before repairing signatures.

## Ov030SceneState_BeginScreenModeTransition

Identity: `ov030:020ba874`, THUMB, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov030_020ba874`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c](../src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c).

```c
u32 Ov030SceneState_BeginScreenModeTransition(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Passes signed scene mode byte+8 to the screen mode transition helper, sets flag0x20 and returns state10. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c:1-14](../src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c:1-14](../src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

Contract limits:

- The mode byte is not a position coordinate.

## Ov030SceneState_FinishSlowdownTransition

Identity: `ov030:020ba930`, THUMB, native extent 52 bytes (including any configured pool). Previous symbol: `func_ov030_020ba930`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c](../src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c).

```c
u32 Ov030SceneState_FinishSlowdownTransition(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen idle, clears flag0x40, sets flag0x80 and returns state7. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c:1-17](../src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c:1-17](../src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

Contract limits:

- Do not infer purpose of new flag0x80 solely from its offset.

## Ov030SceneState_StartIdleObjects

Identity: `ov030:020ba964`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov030_020ba964`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c](../src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c).

```c
u32 Ov030SceneState_StartIdleObjects(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Sets flag0x20; unless flag0x10 is set starts idle scene objects and invokes companion hook with1; returns state15. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c:1-18](../src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c:1-18](../src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

## Ov030SceneState_BeginFadeOutWhenIdle

Identity: `ov030:020ba98c`, THUMB, native extent 60 bytes (including any configured pool). Previous symbol: `func_ov030_020ba98c`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c](../src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c).

```c
u32 Ov030SceneState_BeginFadeOutWhenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Unless flag0x10 bypasses the busy gate, waits for the external activity to clear; once screen is idle begins fade-out with the scene mode and returns state16. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c:1-24](../src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c:1-24](../src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

## Ov030SceneState_WaitFadeOut

Identity: `ov030:020ba9c8`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov030_020ba9c8`.

EU entrypoint: [eu/src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c](../src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c).

```c
u32 Ov030SceneState_WaitFadeOut(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Waits for screen idle, sets immediate-dispatch flag and returns state17. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c:1-16](../src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c:1-16](../src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

Contract limits:

- Only the screen-idle completion predicate is tested.

## DrawOv030FieldScene

Identity: `ov030:020baab8`, THUMB, native extent 26 bytes (including any configured pool). Previous symbol: `func_ov030_020baab8`.

EU entrypoint: [eu/src/overlays/ov030/calls/DrawOv030FieldScene.c](../src/overlays/ov030/calls/DrawOv030FieldScene.c).

```c
void DrawOv030FieldScene(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates active camera mode with argument1, draws visible scene slots and event callbacks, updates actor billboards and invokes the final field draw hook. Source: [eu/src/overlays/ov030/calls/DrawOv030FieldScene.c:1-16](../src/overlays/ov030/calls/DrawOv030FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/DrawOv030FieldScene.c:1-16](../src/overlays/ov030/calls/DrawOv030FieldScene.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).

## CreateOv030FieldSceneTask

Identity: `ov030:020babc8`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov030_020babc8`.

EU entrypoint: [eu/src/overlays/ov030/calls/CreateOv030FieldSceneTask.c](../src/overlays/ov030/calls/CreateOv030FieldSceneTask.c).

```c
void CreateOv030FieldSceneTask(int arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates this overlay's own scene TaskObject descriptor and stores the returned task handle. Source: [eu/src/overlays/ov030/calls/CreateOv030FieldSceneTask.c:1-5](../src/overlays/ov030/calls/CreateOv030FieldSceneTask.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [src/ov030/shared_engine/MobiClip_SrcOpen_020baba8.c:1-7](../../src/ov030/shared_engine/MobiClip_SrcOpen_020baba8.c).

Contract limits:

- This is field scene task creation; the inherited MobiClip source filename does not establish video behavior.

## IsOv030SceneStartupComplete

Identity: `ov030:020babe0`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov030_020babe0`.

EU entrypoint: [eu/src/overlays/ov030/calls/IsOv030SceneStartupComplete.c](../src/overlays/ov030/calls/IsOv030SceneStartupComplete.c).

```c
BOOL IsOv030SceneStartupComplete(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false for absent work, otherwise true when flag0x1 has cleared. Source: [eu/src/overlays/ov030/calls/IsOv030SceneStartupComplete.c:1-10](../src/overlays/ov030/calls/IsOv030SceneStartupComplete.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/IsOv030SceneStartupComplete.c:1-10](../src/overlays/ov030/calls/IsOv030SceneStartupComplete.c).
- Startup completion state waits for panel readiness, clears flag0x1 and advances to running state7. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c:1-20](../src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c).

## RequestOv030SceneExit

Identity: `ov030:020bac14`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov030_020bac14`.

EU entrypoint: [eu/src/overlays/ov030/calls/RequestOv030SceneExit.c](../src/overlays/ov030/calls/RequestOv030SceneExit.c).

```c
void RequestOv030SceneExit(u8 value);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Stores exit mode byte+8 and sets request flag0x4000. Source: [eu/src/overlays/ov030/calls/RequestOv030SceneExit.c:1-9](../src/overlays/ov030/calls/RequestOv030SceneExit.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/RequestOv030SceneExit.c:1-9](../src/overlays/ov030/calls/RequestOv030SceneExit.c).
- Consumer of exactly flag0x4000 pauses field entries and requests state14; subsequent fade-out uses the mode byte+8. Source: [eu/src/overlays/ov030/calls/ResolveMovieSceneAction.c:1-45](../src/overlays/ov030/calls/ResolveMovieSceneAction.c).

## GetOv030FieldTransitionFlags

Identity: `ov030:020bb230`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov030_020bb230`.

EU entrypoint: [eu/src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c](../src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c).

```c
u32 GetOv030FieldTransitionFlags(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns raw field transition mask0x60. Source: [eu/src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c:1-8](../src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c).
- Installs this function at callback index10 (offset0x28). Source: [eu/src/overlays/ov030/calls/InstallSceneHandlers_020bb288.c:1-14](../src/overlays/ov030/calls/InstallSceneHandlers_020bb288.c).
- Reads installed callback from Session+2834=overlayWork280c+10*4 and forwards its raw value. Source: [eu/src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c:1-15](../src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c).
- Equivalent established field-mode interface returns transition mask0x60. Source: [eu/src/overlays/ov028/calls/GetFieldTransitionFlags.c:1-6](../src/overlays/ov028/calls/GetFieldTransitionFlags.c).
- Uses nonzero transition callback result to block normal HUD sound progression, not as a flag-bit index. Source: [eu/src/overlays/ov001/calls/UpdateHudGauges.c:1-157](../src/overlays/ov001/calls/UpdateHudGauges.c).
- Starting scene parameters resets flags and sets0x20; explicit screen transition command also sets this bit. Source: [src/ov030/movie/ApplyMovieStartParams_020bac48.c:1-51](../../src/ov030/movie/ApplyMovieStartParams_020bac48.c).
- Starts screen-mode transition then sets0x20. Source: [eu/src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c:1-14](../src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c).

Contract limits:

- Raw mask is retained; do not normalize0x20/0x60 into1.
- Callback exposes only these transition flags, not all scene phase state.
- Exact bit meanings remain in the owner-specific phase code; no universal mode/timer layout is introduced.

## GetOv030SceneLock

Identity: `ov030:020bb388`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov030_020bb388`.

EU entrypoint: [eu/src/overlays/ov030/auto/GetOv030SceneLock.c](../src/overlays/ov030/auto/GetOv030SceneLock.c).

```c
u8 GetOv030SceneLock(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns raw scene lock byte+9. Source: [eu/src/overlays/ov030/auto/GetOv030SceneLock.c:1-8](../src/overlays/ov030/auto/GetOv030SceneLock.c).
- EU wrapper binds native lock setter to same scene owner. Source: [eu/src/overlays/ov030/calls/SetSceneLock.c:1-4](../src/overlays/ov030/calls/SetSceneLock.c).
- Setter writes byte+9 and enables the camera only when zero. Source: [src/ov030/shared_engine/SetSceneLock_020bb374.c:1-15](../../src/ov030/shared_engine/SetSceneLock_020bb374.c).

Contract limits:

- Raw byte is not normalized to BOOL.

## SetOv030SceneDrawEnabled

Identity: `ov030:020bb460`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `func_ov030_020bb460`.

EU entrypoint: [eu/src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c](../src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c).

```c
void SetOv030SceneDrawEnabled(BOOL enable);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Sets or clears scene flags bit0x4. Source: [eu/src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c:1-12](../src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c:1-12](../src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c).
- EU wrapper maps own state dispatcher and draw callback. Source: [eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c:1-6](../src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c).
- Exactly bit0x4 guards the draw callback. Source: [src/ov030/shared_engine/RunSceneStateMachine_020ba4c0.c:1-33](../../src/ov030/shared_engine/RunSceneStateMachine_020ba4c0.c).

## ClearCarriedActorEscapeConfig

Identity: `ov030:020bb488`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov030_020bb488`.

EU entrypoint: [eu/src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c](../src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c).

```c
u32 ClearCarriedActorEscapeConfig(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Zeroes the first four words of the supplied escape/reset configuration and returns its pointer. Source: [eu/src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c:1-2](../src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c).
- Shared C body included with exact EU aliases. Source: [src/ov030/leaf_research/func_ov030_020bb468.c:1-9](../../src/ov030/leaf_research/func_ov030_020bb468.c).
- EU wrapper binds this helper into carried-actor escape logic. Source: [eu/src/overlays/ov030/calls/CheckCarriedActorEscape.c:1-16](../src/overlays/ov030/calls/CheckCarriedActorEscape.c).
- On escape with remaining lives, calls this helper with g_markerReset before setting actor escape flags and state0x1d. Source: [src/ov030/shared_engine/CheckCarriedActorEscape_020bbf78.c:1-133](../../src/ov030/shared_engine/CheckCarriedActorEscape_020bbf78.c).

Contract limits:

- The marker index at+0x10 is deliberately not cleared; four individual cleared word meanings remain unknown.

## UpdateSceneGroupsAndDrawModelSlots

Identity: `ov030:020bcb3c`, THUMB, native extent 20 bytes (including any configured pool). Previous symbol: `func_ov030_020bcb3c`.

EU entrypoint: [eu/src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c](../src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c).

```c
void UpdateSceneGroupsAndDrawModelSlots(u32 base);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates scene group nodes then draws the model slot list at owner+0x18c. Source: [eu/src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c:1-10](../src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c:1-10](../src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c).

Contract limits:

- Owner layout is specific to this helper; no movie role is inferred.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c Ov030SceneState_PushVramWhenIdle --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c Ov030SceneState_WaitForListNodes --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c Ov030SceneState_FinishMenuResourceLoad --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c Ov030SceneState_FinishStartupWhenPanelReady --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c Ov030SceneState_StoreEventRecordBytes --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c Ov030SceneState_BeginScreenModeTransition --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c Ov030SceneState_FinishSlowdownTransition --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c Ov030SceneState_StartIdleObjects --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c Ov030SceneState_BeginFadeOutWhenIdle --thumb
python tools/verify_idx.py src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c Ov030SceneState_WaitFadeOut --thumb
python tools/verify_idx.py src/overlays/ov030/calls/DrawOv030FieldScene.c DrawOv030FieldScene --thumb
python tools/verify_idx.py src/overlays/ov030/calls/CreateOv030FieldSceneTask.c CreateOv030FieldSceneTask --thumb
python tools/verify_idx.py src/overlays/ov030/calls/IsOv030SceneStartupComplete.c IsOv030SceneStartupComplete --thumb
python tools/verify_idx.py src/overlays/ov030/calls/RequestOv030SceneExit.c RequestOv030SceneExit --thumb
python tools/verify_idx.py src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c GetOv030FieldTransitionFlags --thumb
python tools/verify_idx.py src/overlays/ov030/auto/GetOv030SceneLock.c GetOv030SceneLock --thumb
python tools/verify_idx.py src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c SetOv030SceneDrawEnabled --thumb
python tools/verify_idx.py src/overlays/ov030/auto/ClearCarriedActorEscapeConfig.c ClearCarriedActorEscapeConfig --thumb
python tools/verify_idx.py src/overlays/ov030/calls/UpdateSceneGroupsAndDrawModelSlots.c UpdateSceneGroupsAndDrawModelSlots --thumb
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
