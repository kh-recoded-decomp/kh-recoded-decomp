# Overlay029 field scene lifecycle

This document records 8 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

These entrypoints use overlay029's own descriptor, work and lifecycle writers. They are field-scene task operations despite inherited MobiClip filenames. State handlers preserve the current state for signed -1; nonnegative results select the next state. The separate frame dispatcher uses flag 8 for update and flag 4 for draw. Normal update time steps are 0x1000 in 12-fraction-bit fixed point.

Startup completion is false for absent work and otherwise means startup bit 0x1 has cleared. That transition is demonstrated by this owner's startup writer, rather than inferred from a similar offset in another scene. The draw path updates the active camera, scene slots, event callbacks and billboards; a nonzero update mode suppresses a subset of field-scene updates while party and actor callbacks still run.

Two session callbacks have different contracts. Slot 7 at SessionState +0x2828 returns literal 1 to grant scene consent, but the aggregate session gate can still block on actor-entry flag 2. This is separate from slot 1 startup readiness. Slot 10 at +0x2834 supplies a raw transition mask; overlay029 deliberately returns zero. Zero here does not imply the whole scene never changes phase. The session table begins at +0x280c and occupies 48 bytes; equal offsets in other owners are not this table.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov029:020ba588` | ARM | `func_ov029_020ba588` | `Ov029SceneState_PushVramWhenIdle` | [eu/src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c](../src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c) |
| `ov029:020ba5e8` | ARM | `func_ov029_020ba5e8` | `Ov029SceneState_ResetSlotsAndLoadShadow` | [eu/src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c](../src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c) |
| `ov029:020ba86c` | ARM | `func_ov029_020ba86c` | `DrawOv029FieldScene` | [eu/src/overlays/ov029/calls/DrawOv029FieldScene.c](../src/overlays/ov029/calls/DrawOv029FieldScene.c) |
| `ov029:020ba88c` | ARM | `func_ov029_020ba88c` | `UpdateOv029FieldScene` | [eu/src/overlays/ov029/calls/UpdateOv029FieldScene.c](../src/overlays/ov029/calls/UpdateOv029FieldScene.c) |
| `ov029:020ba9d0` | ARM | `func_ov029_020ba9d0` | `CreateOv029FieldSceneTask` | [eu/src/overlays/ov029/calls/CreateOv029FieldSceneTask.c](../src/overlays/ov029/calls/CreateOv029FieldSceneTask.c) |
| `ov029:020ba9f4` | ARM | `func_ov029_020ba9f4` | `IsOv029SceneStartupComplete` | [eu/src/overlays/ov029/calls/IsOv029SceneStartupComplete.c](../src/overlays/ov029/calls/IsOv029SceneStartupComplete.c) |
| `ov029:020baaec` | ARM | `func_ov029_020baaec` | `CanOv029SceneAdvanceSession` | [eu/src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c](../src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c) |
| `ov029:020baaf4` | ARM | `func_ov029_020baaf4` | `GetOv029FieldTransitionFlags` | [eu/src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c](../src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c) |

## Ov029SceneState_PushVramWhenIdle

Identity: `ov029:020ba588`, ARM, native extent 56 bytes (including any configured pool). Previous symbol: `func_ov029_020ba588`.

EU entrypoint: [eu/src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c](../src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c).

```c
u32 Ov029SceneState_PushVramWhenIdle(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns -1 while external busy predicate is nonzero; otherwise pushes VRAM state, requests immediate dispatch and returns state1. Source: [eu/src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c:1-17](../src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c:1-17](../src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c).
- Own scene state dispatcher uses these callbacks for update and draw under flags 8 and4. Source: [eu/src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c:1-33](../src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c).

## Ov029SceneState_ResetSlotsAndLoadShadow

Identity: `ov029:020ba5e8`, ARM, native extent 20 bytes (including any configured pool). Previous symbol: `func_ov029_020ba5e8`.

EU entrypoint: [eu/src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c](../src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c).

```c
int Ov029SceneState_ResetSlotsAndLoadShadow(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Resets scene slots, loads the shadow model and returns state3. Source: [eu/src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c:1-9](../src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c:1-9](../src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c).
- Own scene state dispatcher uses these callbacks for update and draw under flags 8 and4. Source: [eu/src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c:1-33](../src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c).

## DrawOv029FieldScene

Identity: `ov029:020ba86c`, ARM, native extent 32 bytes (including any configured pool). Previous symbol: `func_ov029_020ba86c`.

EU entrypoint: [eu/src/overlays/ov029/calls/DrawOv029FieldScene.c](../src/overlays/ov029/calls/DrawOv029FieldScene.c).

```c
void DrawOv029FieldScene(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Updates active camera mode with argument1, draws visible scene slots and event callbacks, updates actor billboards and invokes the final field draw hook. Source: [eu/src/overlays/ov029/calls/DrawOv029FieldScene.c:1-14](../src/overlays/ov029/calls/DrawOv029FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov029/calls/DrawOv029FieldScene.c:1-14](../src/overlays/ov029/calls/DrawOv029FieldScene.c).
- Own scene state dispatcher uses these callbacks for update and draw under flags 8 and4. Source: [eu/src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c:1-33](../src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c).

## UpdateOv029FieldScene

Identity: `ov029:020ba88c`, ARM, native extent 76 bytes (including any configured pool). Previous symbol: `func_ov029_020ba88c`.

EU entrypoint: [eu/src/overlays/ov029/calls/UpdateOv029FieldScene.c](../src/overlays/ov029/calls/UpdateOv029FieldScene.c).

```c
void UpdateOv029FieldScene(int mode);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Always updates party entries and actor callbacks. When mode is zero also updates scene animation, field objects, stage and prize orbs. Source: [eu/src/overlays/ov029/calls/UpdateOv029FieldScene.c:1-20](../src/overlays/ov029/calls/UpdateOv029FieldScene.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov029/calls/UpdateOv029FieldScene.c:1-20](../src/overlays/ov029/calls/UpdateOv029FieldScene.c).

Contract limits:

- The fixed timestep is0x1000 (one fx32 unit), not a channel mask.

## CreateOv029FieldSceneTask

Identity: `ov029:020ba9d0`, ARM, native extent 36 bytes (including any configured pool). Previous symbol: `func_ov029_020ba9d0`.

EU entrypoint: [eu/src/overlays/ov029/calls/CreateOv029FieldSceneTask.c](../src/overlays/ov029/calls/CreateOv029FieldSceneTask.c).

```c
void CreateOv029FieldSceneTask(int arg0);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates this overlay's own scene TaskObject descriptor and stores the returned task handle. Source: [eu/src/overlays/ov029/calls/CreateOv029FieldSceneTask.c:1-5](../src/overlays/ov029/calls/CreateOv029FieldSceneTask.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [src/ov029/reviewed_helpers/func_ov029_020ba9b0.c:1-7](../../src/ov029/reviewed_helpers/func_ov029_020ba9b0.c).

Contract limits:

- This is field scene task creation; the inherited MobiClip source filename does not establish video behavior.

## IsOv029SceneStartupComplete

Identity: `ov029:020ba9f4`, ARM, native extent 44 bytes (including any configured pool). Previous symbol: `func_ov029_020ba9f4`.

EU entrypoint: [eu/src/overlays/ov029/calls/IsOv029SceneStartupComplete.c](../src/overlays/ov029/calls/IsOv029SceneStartupComplete.c).

```c
BOOL IsOv029SceneStartupComplete(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false if own work is absent; otherwise returns true when startup flag0x1 is clear. Source: [eu/src/overlays/ov029/calls/IsOv029SceneStartupComplete.c:1-19](../src/overlays/ov029/calls/IsOv029SceneStartupComplete.c).
- This overlay's own startup-completion state clears exactly flag0x1 before entering its running state. Source: [src/ov029/reviewed_helpers/EnableOv029Sound_020ba670.c:1-39](../../src/ov029/reviewed_helpers/EnableOv029Sound_020ba670.c).

Contract limits:

- Evidence is from each own scene, not from matching offsets in other owners.

## CanOv029SceneAdvanceSession

Identity: `ov029:020baaec`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov029_020baaec`.

EU entrypoint: [eu/src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c](../src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c).

```c
u32 CanOv029SceneAdvanceSession(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Constant callback returns1. Source: [eu/src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c:1-2](../src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c).
- Exact constant-return body. Source: [src/ov029/leaf_research/func_ov029_020baacc.c:1-5](../../src/ov029/leaf_research/func_ov029_020baacc.c).
- Registers this function at callback index7. Source: [eu/src/overlays/ov029/calls/InstallOv029SceneHandlers.c:1-12](../src/overlays/ov029/calls/InstallOv029SceneHandlers.c).
- Session progress gate invokes Session+2828 (overlayWork280c+7*4); callback false blocks, then actor-entry flag2 can also block. Source: [eu/src/overlays/ov001/calls/IsSessionScriptEntryReady.c:1-20](../src/overlays/ov001/calls/IsSessionScriptEntryReady.c).
- Only raises session script run flags when aggregate progress gate succeeds. Source: [src/ov001/unclassified_helpers/TryRaiseSessionScriptFlags_02063694.c:1-36](../../src/ov001/unclassified_helpers/TryRaiseSessionScriptFlags_02063694.c).
- Session transition also requires same aggregate gate. Source: [src/ov001/unclassified_helpers/SelectNextSessionState_02062150.c:1-171](../../src/ov001/unclassified_helpers/SelectNextSessionState_02062150.c).

Contract limits:

- Only the scene callback grants consent unconditionally. Other aggregate session conditions may still block progress.
- This is distinct from callback index1 startup readiness.

## GetOv029FieldTransitionFlags

Identity: `ov029:020baaf4`, ARM, native extent 8 bytes (including any configured pool). Previous symbol: `func_ov029_020baaf4`.

EU entrypoint: [eu/src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c](../src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c).

```c
u32 GetOv029FieldTransitionFlags(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns raw field transition mask0x0. Source: [eu/src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c:1-2](../src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c).
- Installs this function at callback index10 (offset0x28). Source: [eu/src/overlays/ov029/calls/InstallOv029SceneHandlers.c:1-12](../src/overlays/ov029/calls/InstallOv029SceneHandlers.c).
- Reads installed callback from Session+2834=overlayWork280c+10*4 and forwards its raw value. Source: [eu/src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c:1-15](../src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c).
- Equivalent established field-mode interface returns transition mask0x60. Source: [eu/src/overlays/ov028/calls/GetFieldTransitionFlags.c:1-6](../src/overlays/ov028/calls/GetFieldTransitionFlags.c).
- Uses nonzero transition callback result to block normal HUD sound progression, not as a flag-bit index. Source: [eu/src/overlays/ov001/calls/UpdateHudGauges.c:1-157](../src/overlays/ov001/calls/UpdateHudGauges.c).
- Exact shared mask/constant body. Source: [src/ov029/leaf_research/func_ov029_020baad4.c:1-5](../../src/ov029/leaf_research/func_ov029_020baad4.c).

Contract limits:

- Raw mask is retained; do not normalize0x20/0x60 into1.
- Callback exposes only these transition flags, not all scene phase state.
- Ov029 intentionally always returns0; this does not prove that its scene never changes phase.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c Ov029SceneState_PushVramWhenIdle
python tools/verify_idx.py src/overlays/ov029/calls/Ov029SceneState_ResetSlotsAndLoadShadow.c Ov029SceneState_ResetSlotsAndLoadShadow
python tools/verify_idx.py src/overlays/ov029/calls/DrawOv029FieldScene.c DrawOv029FieldScene
python tools/verify_idx.py src/overlays/ov029/calls/UpdateOv029FieldScene.c UpdateOv029FieldScene
python tools/verify_idx.py src/overlays/ov029/calls/CreateOv029FieldSceneTask.c CreateOv029FieldSceneTask
python tools/verify_idx.py src/overlays/ov029/calls/IsOv029SceneStartupComplete.c IsOv029SceneStartupComplete
python tools/verify_idx.py src/overlays/ov029/auto/CanOv029SceneAdvanceSession.c CanOv029SceneAdvanceSession
python tools/verify_idx.py src/overlays/ov029/auto/GetOv029FieldTransitionFlags.c GetOv029FieldTransitionFlags
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
