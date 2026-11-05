# Overlay031 scene scroll and record contracts

This document records 11 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The old Movie labels in this area refer to a record-driven field-scene task. They do not describe overlay022's decoder. Creation uses this overlay's descriptor and stores its TaskObject handle. Startup completion has its own flag-0x1 writer, and session slot 10 exposes only the raw flag-0x20 transition mask.

| Scene work offset | Proven role |
| --- | --- |
| 0x1c | VecFx32 movement direction; borrowed vector returned by GetSceneScrollDirection. |
| 0x28 | Current scroll speed. |
| 0x2c | Accumulated scroll offset. |
| 0x30 | Target scroll speed. |
| 0x34 | Acceleration per update. |
| 0x38 | Accumulated scroll distance. |
| 0x44 | Current record index; -1 after record release. |
| 0x50 | Record array, stride 0x3c. |
| 0xb8 | Negative-world-Z cull distance, 15 or 30 in fixed point with 12 fractional bits. |
| 0xbc | Scene task update counter, incremented before state dispatch. |

A record's word at +0x14 supplies the next target speed. `BeginNextRecord` compares it with current speed and calls the setter with acceleration 0x52. Its private `position` label is misleading. The acceleration getter returns the signed full acceleration according to target minus current speed; it does not clamp to the remaining difference.

Preserve update order: `UpdateSceneScroll` constructs movement delta from the old current speed, then accelerates toward the target. Groups and listeners receive that precomputed delta, while accumulated scroll and distance use the updated speed. A special camera-flag path moves the player by the negative delta and returns before normal acceleration/accumulation.

The cull distance is consumed by overlay043's camera-mode-2 point/shape checks before four-plane testing. A shape includes its projected Z radius in the allowed distance. It is not a generic camera near/far pair. The frame count measures scene task updates rather than decoded frames.

Record release handles the current record's group objects/items and resets its index. The three completion-category bytes at record +0x38/+0x39/+0x3a retain numeric meanings. It does not establish ownership of the enclosing scene work. Borrowed direction and record pointers remain tied to that work's lifetime.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov031:020bb494` | THUMB | `func_ov031_020bb494` | `CreateOv031FieldSceneTask` | [eu/src/overlays/ov031/calls/CreateOv031FieldSceneTask.c](../src/overlays/ov031/calls/CreateOv031FieldSceneTask.c) |
| `ov031:020bb4ac` | THUMB | `func_ov031_020bb4ac` | `IsOv031SceneStartupComplete` | [eu/src/overlays/ov031/calls/IsOv031SceneStartupComplete.c](../src/overlays/ov031/calls/IsOv031SceneStartupComplete.c) |
| `ov031:020bb5f8` | THUMB | `func_ov031_020bb5f8` | `ReleaseCurrentSceneRecord` | [eu/src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c](../src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c) |
| `ov031:020bbf44` | THUMB | `func_ov031_020bbf44` | `GetOv031FieldTransitionFlag` | [eu/src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c](../src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c) |
| `ov031:020bc000` | THUMB | `GetSubStruct1C` | `GetSceneScrollDirection` | [eu/src/overlays/ov031/calls/GetSceneScrollDirection.c](../src/overlays/ov031/calls/GetSceneScrollDirection.c) |
| `ov031:020bc028` | THUMB | `SetFields30And34` | `SetSceneScrollSpeedTarget` | [eu/src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c](../src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c) |
| `ov031:020bc038` | THUMB | `GetSeekStep` | `GetSceneScrollAccelerationStep` | [eu/src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c](../src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c) |
| `ov031:020bc060` | THUMB | `func_ov031_020bc060` | `GetSceneScrollTargetSpeed` | [eu/src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c](../src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c) |
| `ov031:020bc720` | THUMB | `func_ov031_020bc720` | `GetSceneDepthCullDistance` | [eu/src/overlays/ov031/calls/GetSceneDepthCullDistance.c](../src/overlays/ov031/calls/GetSceneDepthCullDistance.c) |
| `ov031:020bc740` | THUMB | `GetCurrentRecordPosition` | `GetCurrentRecordTargetScrollSpeed` | [eu/src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c](../src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c) |
| `ov031:020bc758` | THUMB | `GetMovieFrameCount` | `GetSceneFrameCount` | [eu/src/overlays/ov031/calls/GetSceneFrameCount.c](../src/overlays/ov031/calls/GetSceneFrameCount.c) |

## CreateOv031FieldSceneTask

Identity: `ov031:020bb494`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov031_020bb494`.

EU entrypoint: [eu/src/overlays/ov031/calls/CreateOv031FieldSceneTask.c](../src/overlays/ov031/calls/CreateOv031FieldSceneTask.c).

```c
void CreateOv031FieldSceneTask(int arg);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Instantiates this overlay's own scene TaskObject descriptor and stores the returned task handle. Source: [eu/src/overlays/ov031/calls/CreateOv031FieldSceneTask.c:1-5](../src/overlays/ov031/calls/CreateOv031FieldSceneTask.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [src/ov031/shared_engine/MobiClip_SrcOpen_020bb474.c:1-7](../../src/ov031/shared_engine/MobiClip_SrcOpen_020bb474.c).

Contract limits:

- This is field scene task creation; the inherited MobiClip source filename does not establish video behavior.

## IsOv031SceneStartupComplete

Identity: `ov031:020bb4ac`, THUMB, native extent 28 bytes (including any configured pool). Previous symbol: `func_ov031_020bb4ac`.

EU entrypoint: [eu/src/overlays/ov031/calls/IsOv031SceneStartupComplete.c](../src/overlays/ov031/calls/IsOv031SceneStartupComplete.c).

```c
BOOL IsOv031SceneStartupComplete(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns false if own work is absent; otherwise returns true when startup flag0x1 is clear. Source: [eu/src/overlays/ov031/calls/IsOv031SceneStartupComplete.c:1-10](../src/overlays/ov031/calls/IsOv031SceneStartupComplete.c).
- This overlay's own startup-completion state clears exactly flag0x1 before entering its running state. Source: [src/ov031/state_machine/TryEnterState7_020ba7c4.c:1-25](../../src/ov031/state_machine/TryEnterState7_020ba7c4.c).

Contract limits:

- Evidence is from each own scene, not from matching offsets in other owners.

## ReleaseCurrentSceneRecord

Identity: `ov031:020bb5f8`, THUMB, native extent 84 bytes (including any configured pool). Previous symbol: `func_ov031_020bb5f8`.

EU entrypoint: [eu/src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c](../src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c).

```c
void ReleaseCurrentSceneRecord(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Increments completion count if any of current record bytes38/39/3a is nonzero; removes its group objects, flags kind6 objects, releases record items, and resets recordIndex to-1. Source: [eu/src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c:1-22](../src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c).
- Shared body included by the EU wrapper with exact EU aliases. Source: [eu/src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c:1-22](../src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c).
- Native struct confirms work44=current record index,50=record array, stride0x3c. Source: [eu/src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c:1-6](../src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c).

Contract limits:

- The three record byte categories retain their numeric representation.

## GetOv031FieldTransitionFlag

Identity: `ov031:020bbf44`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov031_020bbf44`.

EU entrypoint: [eu/src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c](../src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c).

```c
u32 GetOv031FieldTransitionFlag(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns raw field transition mask0x20. Source: [eu/src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c:1-8](../src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c).
- Installs this function at callback index10 (offset0x28). Source: [eu/src/overlays/ov031/calls/InstallMovieSceneHandlers.c:1-14](../src/overlays/ov031/calls/InstallMovieSceneHandlers.c).
- Reads installed callback from Session+2834=overlayWork280c+10*4 and forwards its raw value. Source: [eu/src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c:1-15](../src/overlays/ov001/calls/InvokeSessionCheckCallbackOrDefault.c).
- Equivalent established field-mode interface returns transition mask0x60. Source: [eu/src/overlays/ov028/calls/GetFieldTransitionFlags.c:1-6](../src/overlays/ov028/calls/GetFieldTransitionFlags.c).
- Uses nonzero transition callback result to block normal HUD sound progression, not as a flag-bit index. Source: [eu/src/overlays/ov001/calls/UpdateHudGauges.c:1-157](../src/overlays/ov001/calls/UpdateHudGauges.c).
- EU alias selects own start-parameters initializer. Source: [eu/src/overlays/ov031/calls/ApplyStartParams.c:1-4](../src/overlays/ov031/calls/ApplyStartParams.c).
- Scene start sets flag0x20 and resets current state. Source: [src/ov031/overlay_state/ApplyStartParams_020bb518.c:1-34](../../src/ov031/overlay_state/ApplyStartParams_020bb518.c).

Contract limits:

- Raw mask is retained; do not normalize0x20/0x60 into1.
- Callback exposes only these transition flags, not all scene phase state.
- Exact bit meanings remain in the owner-specific phase code; no universal mode/timer layout is introduced.

## GetSceneScrollDirection

Identity: `ov031:020bc000`, THUMB, native extent 20 bytes (including any configured pool). Previous symbol: `GetSubStruct1C`.

EU entrypoint: [eu/src/overlays/ov031/calls/GetSceneScrollDirection.c](../src/overlays/ov031/calls/GetSceneScrollDirection.c).

```c
int GetSceneScrollDirection(void);
```

The native int result represents a borrowed VecFx32 pointer, or NULL when scene work is absent. Its lifetime follows the scene work; the vector is not guaranteed normalized.

Demonstrated behavior and evidence:

- EU wrapper/body identifies this scene helper. Source: [eu/src/overlays/ov031/calls/GetSceneScrollDirection.c:1-3](../src/overlays/ov031/calls/GetSceneScrollDirection.c).
- Returns borrowed work+0x1c orNULL if work is absent. Source: [src/ov031/unclassified_helpers/GetSubStruct1C_020bbfe0.c:1-11](../../src/ov031/unclassified_helpers/GetSubStruct1C_020bbfe0.c).
- Uses the VecFx32 at+0x1c multiplied by current speed as scene movement delta. Source: [src/ov031/overlay_state/UpdateSceneScroll_020bb054.c:1-214](../../src/ov031/overlay_state/UpdateSceneScroll_020bb054.c).

Contract limits:

- No normalization guarantee is inferred.

## SetSceneScrollSpeedTarget

Identity: `ov031:020bc028`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `SetFields30And34`.

EU entrypoint: [eu/src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c](../src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c).

```c
void SetSceneScrollSpeedTarget(u32 a, u32 b);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- EU wrapper/body identifies this scene helper. Source: [eu/src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c:1-3](../src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c).
- Setter stores speed target+0x30 and per-update acceleration+0x34. Source: [src/ov031/unclassified_helpers/SetFields30And34_020bc008.c:1-15](../../src/ov031/unclassified_helpers/SetFields30And34_020bc008.c).
- Movement update uses those exact target/acceleration values. Source: [src/ov031/overlay_state/UpdateSceneScroll_020bb054.c:1-214](../../src/ov031/overlay_state/UpdateSceneScroll_020bb054.c).

## GetSceneScrollAccelerationStep

Identity: `ov031:020bc038`, THUMB, native extent 40 bytes (including any configured pool). Previous symbol: `GetSeekStep`.

EU entrypoint: [eu/src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c](../src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c).

```c
s32 GetSceneScrollAccelerationStep(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- EU wrapper/body identifies this scene helper. Source: [eu/src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c:1-3](../src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c).
- Returns acceleration+0x34 multiplied by sign(targetSpeed+0x30-currentSpeed+0x28). Source: [src/ov031/overlay_state/GetSeekStep_020bc018.c:1-27](../../src/ov031/overlay_state/GetSeekStep_020bc018.c).
- Demonstrates target/current speed and acceleration fields. Source: [src/ov031/overlay_state/UpdateSceneScroll_020bb054.c:1-214](../../src/ov031/overlay_state/UpdateSceneScroll_020bb054.c).

Contract limits:

- Does not clamp the returned step to remaining speed difference.

## GetSceneScrollTargetSpeed

Identity: `ov031:020bc060`, THUMB, native extent 12 bytes (including any configured pool). Previous symbol: `func_ov031_020bc060`.

EU entrypoint: [eu/src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c](../src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c).

```c
u32 GetSceneScrollTargetSpeed(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Returns scene work+0x30. Source: [eu/src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c:1-8](../src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c).
- At+0x30 is targetSpeed; update accelerates speed+0x28 toward it by acceleration+0x34, moves objects by direction+0x1c scaled by speed, and accumulates scroll+0x2c/distance+0x38. Source: [src/ov031/overlay_state/UpdateSceneScroll_020bb054.c:1-214](../../src/ov031/overlay_state/UpdateSceneScroll_020bb054.c).

Additional native ABI observations:

- Real quantity is fx32 speed; existing u32 declaration preserves32-bit ABI.

## GetSceneDepthCullDistance

Identity: `ov031:020bc720`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov031_020bc720`.

EU entrypoint: [eu/src/overlays/ov031/calls/GetSceneDepthCullDistance.c](../src/overlays/ov031/calls/GetSceneDepthCullDistance.c).

```c
u32 GetSceneDepthCullDistance(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- EU wrapper identifies getter at current scene work+0xb8. Source: [eu/src/overlays/ov031/calls/GetSceneDepthCullDistance.c:1-3](../src/overlays/ov031/calls/GetSceneDepthCullDistance.c).
- Initializes this value to30<<12 in context mode6 and15<<12 otherwise. Source: [eu/src/overlays/ov031/calls/LoadSceneData.c:1-325](../src/overlays/ov031/calls/LoadSceneData.c).
- EU wrapper aliases this getter into shape depth test. Source: [eu/src/overlays/ov043/calls/IsShapeInViewDepth.c:1-6](../src/overlays/ov043/calls/IsShapeInViewDepth.c).
- Allows centerZ>=-(margin+distance+projectedZradius) before plane tests. Source: [src/ov043/camera/IsShapeInViewDepth_020bd1ec.c:1-28](../../src/ov043/camera/IsShapeInViewDepth_020bd1ec.c).
- Rejects pointZ<-(threshold+distance). Source: [src/ov043/camera/IsPointInViewDepth_020bd284.c:1-12](../../src/ov043/camera/IsPointInViewDepth_020bd284.c).

Contract limits:

- This is the negative-world-Z cull distance used by camera mode2; no generic camera near/far meaning inferred.

Additional native ABI observations:

- Actual role is fx32; existing u32 return preserves the same32-bit ABI.

## GetCurrentRecordTargetScrollSpeed

Identity: `ov031:020bc740`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `GetCurrentRecordPosition`.

EU entrypoint: [eu/src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c](../src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c).

```c
u32 GetCurrentRecordTargetScrollSpeed(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- EU wrapper/body identifies this scene helper. Source: [eu/src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c:1-6](../src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c).
- When beginning record, compares record+0x14 against current speed+0x28 and passes it to the speed target setter with acceleration0x52. Source: [src/ov031/overlay_state/BeginNextRecord_020bb62c.c:1-86](../../src/ov031/overlay_state/BeginNextRecord_020bb62c.c).
- Speed and target roles follow from the actual movement loop. Source: [src/ov031/overlay_state/UpdateSceneScroll_020bb054.c:1-214](../../src/ov031/overlay_state/UpdateSceneScroll_020bb054.c).

Contract limits:

- Private record field label position is misleading; it is the next scroll speed target.

## GetSceneFrameCount

Identity: `ov031:020bc758`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `GetMovieFrameCount`.

EU entrypoint: [eu/src/overlays/ov031/calls/GetSceneFrameCount.c](../src/overlays/ov031/calls/GetSceneFrameCount.c).

```c
u32 GetSceneFrameCount(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- EU wrapper/body identifies this scene helper. Source: [eu/src/overlays/ov031/calls/GetSceneFrameCount.c:1-6](../src/overlays/ov031/calls/GetSceneFrameCount.c).
- Increments work+0xbc once per task update, before state dispatch and independently of update/draw flags. Source: [src/ov031/state_machine/RunStateMachine_020ba4b4.c:1-38](../../src/ov031/state_machine/RunStateMachine_020ba4b4.c).

Contract limits:

- Counts scene task updates. No video-decoder frame is involved.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov031/calls/CreateOv031FieldSceneTask.c CreateOv031FieldSceneTask --thumb
python tools/verify_idx.py src/overlays/ov031/calls/IsOv031SceneStartupComplete.c IsOv031SceneStartupComplete --thumb
python tools/verify_idx.py src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c ReleaseCurrentSceneRecord --thumb
python tools/verify_idx.py src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c GetOv031FieldTransitionFlag --thumb
python tools/verify_idx.py src/overlays/ov031/calls/GetSceneScrollDirection.c GetSceneScrollDirection --thumb
python tools/verify_idx.py src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c SetSceneScrollSpeedTarget --thumb
python tools/verify_idx.py src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c GetSceneScrollAccelerationStep --thumb
python tools/verify_idx.py src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c GetSceneScrollTargetSpeed --thumb
python tools/verify_idx.py src/overlays/ov031/calls/GetSceneDepthCullDistance.c GetSceneDepthCullDistance --thumb
python tools/verify_idx.py src/overlays/ov031/calls/GetCurrentRecordTargetScrollSpeed.c GetCurrentRecordTargetScrollSpeed --thumb
python tools/verify_idx.py src/overlays/ov031/calls/GetSceneFrameCount.c GetSceneFrameCount --thumb
bash tools/gate.sh
```

All entrypoints in this document pass the official function check. The combined
112-entrypoint block passes the fresh108-module gate. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved baseline. No signature or algorithm is changed; library receipts
remain current.
