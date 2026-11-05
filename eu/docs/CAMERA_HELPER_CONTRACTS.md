# Camera state, frustum and controller helper contracts

The names below follow the matched bodies, their callers and overlay-qualified
ROM references. They describe operations, not original source symbol spellings.
The helpers remain distinct entrypoints at their original overlay addresses.

| Previous name | Current name | Bytes (Thumb) |
|---|---|---:|
| `func_ov042_020bd110` | `Ov042Camera_GetState` | 12 |
| `func_ov042_020bd11c` | `SetCameraColliderRegistrationMode` | 112 |
| `func_ov042_020bd18c` | `GetCameraColliderRegistrationMode` | 12 |
| `func_ov042_020bd39c` | `GetCameraColliderOffsetMagnitude` | 24 |
| `func_ov042_020bd5a4` | `GetCameraFrustumExtent` | 12 |
| `func_ov042_020bd5b0` | `GetCameraFrustumBounds` | 12 |
| `func_ov042_020bd5bc` | `SetCameraFrustumExtent` | 56 |
| `func_ov046_020c0a1c` | `ReleaseCameraLayerResources` | 40 |
| `func_ov046_020c1608` | `GetCameraManagerWork` | 12 |
| `func_ov046_020c1a68` | `Camera_GetPresetHeight` | 40 |
| `func_ov046_020c2c18` | `ComputeCameraFollowPointWithDefaultHeading` | 16 |
| `func_ov047_020c6d44` | `RestoreCameraTrackingAndUpdate` | 14 |
| `func_ov048_020c3530` | `UpdateOrbitCameraInputFollowAndDrift` | 30 |
| `func_ov048_020c37ac` | `UpdateOrbitCameraFollowPoint` | 14 |
| `func_ov050_020c3530` | `UpdatePathCameraTrackingAndDrift` | 38 |
| `func_ov041_020be088` | `LoadHudLayersAndRecordTextWrapper` | 8 |
| `func_ov041_020be090` | `UnloadHudLayersAndRecordTextWrapper` | 8 |
| `func_ov048_020c3864` | `Ov048Camera_GetControllerData` | 8 |
| `func_ov049_020c4240` | `Ov049Camera_GetControllerData` | 8 |
| `func_ov050_020c3bbc` | `Ov050Camera_GetControllerData` | 8 |

## Overlay042 state and collision registration

`Ov042Camera_GetState` returns the existing state pointer. The recovered
`Ov042CameraState` header describes a **partial native DS view**, not the complete
allocation. The getter and bounds getter return borrowed pointers: neither
allocates nor extends the owner's lifetime. Existing shared callers still use
some 32-bit integer pointer views; those are DS adapters, not host pointer APIs.

| Offset in overlay042 state | Proven field or operation |
|---|---|
| 0x40 | Collider registration mode. |
| 0x44 | Previous value of the registration mode. |
| 0x50 | Existing separate `modeStatus`; not the registration mode. |
| 0x54..0x60 | Four fx32 bounds, in native order. |
| 0x110 | Existing goal position vector. |
| 0x11c | Existing collider offset vector. |

The header checks the important offsets during compilation. It deliberately
leaves the intervening bytes opaque. The collider records at 0x40c, 0x494 and
0x51c lie beyond this view; their complete structure is not inferred from the
registration calls.

`SetCameraColliderRegistrationMode(newMode)` saves the old 0x40 word at 0x44,
stores the new word, then removes all three embedded colliders from the actor
registry's tree. It reinserts all three **only when the stored mode equals 1**.
Other values still remove the colliders. This is not a general gameplay camera
mode setter and provides no null-state or arbitrary-mode validation.
`GetCameraColliderRegistrationMode` returns exactly that 0x40 word.

`GetCameraColliderOffsetMagnitude` returns `VEC_Mag(&state->colliderOffset)`.
Its old void declaration hid a real result: the field-script handler at
ov001:020656d4 calls it and compares returned r0 against zero in mode 4. That
caller/ROM evidence supports the recovered fx32 return; the Ghidra pseudocode
alone inherited the old void declaration. No offset normalization is added.

## Frustum extent and bounds

`SetCameraFrustumExtent(extent)` clamps its signed input to at least 0x1000.
It stores extent at +0x5c and its negative at +0x60. It first writes -extent and
+extent at +0x54/+0x58, then scales each of those two words separately with
`FX_Mul` using the existing word at +8, in the original call order. Finally it
calls `BuildCameraFrustumColliders`. There is no upper clamp here.

`GetCameraFrustumExtent` returns the +0x5c word.
`GetCameraFrustumBounds` returns the address of all four words at +0x54, without
copying them. Their order is retained for `IsPointInViewBounds`,
`IsShapeInViewBounds` and the carried-object consumers. A port must retain the
per-product fixed-point rounding and four-word order. These names do not assert
that extent is a field of view angle, far-plane distance or the manager's
separate `viewDistance`, and this setter does not directly update a rendering
projection beyond its actual collider-builder call.

## Manager lifetime and controller views

`GetCameraManagerWork` returns the borrowed `gCameraManager` pointer using the
existing `CameraManager` declaration (native size 0x414).
`ReleaseCameraLayerResources` frees the manager's data buffers at +0xf8, then
calls the existing overlay-unload helper for the layer ID selected by manager
mode +0x80. It does not free the manager itself or validate the mode index.
The current dependency `func_02029fac` is the geometry-wait/unload wrapper; the
name of its old source is not a reason to drop the synchronization step.

`Camera_GetPresetHeight(index)` reads the first word of a 12-byte preset row,
adding 0x2000 when the manager's state word at +0xf0 has bit 0x80000 set.
`Camera_RestoreSavedTracking` assigns the result to the saved height, providing
the height evidence. The getter has no index check; the state bit's further
meaning and the other preset words are not inferred here.

The three `Ov048/049/050Camera_GetControllerData` entrypoints delegate to
`Camera_GetEmbeddedView`, `Camera_GetEventWork` and `Camera_GetTopDownView`
respectively. Those established helpers return the same controller-specific
storage at manager +0x13c. The pointer is borrowed and its interpretation depends
on the active controller. Identical addresses do not establish identical full
controller types or permission to hold the view across controller replacement.
The separate overlay symbols and their Thumb targets are preserved.

## Follow-point operations and update order

`ComputeCameraFollowPointWithDefaultHeading(direction, out)` calls
`Camera_ComputeFollowPoint(NULL, 0, direction, out)`. The old names of these two
arguments were reversed. The actual worker uses the supplied direction with the
manager's follow distance and player-0 position. Its heading-offset helper uses
the default vector (0, 0x1333, 0) when offsetSource is NULL, with the existing
player heading rotation. The unused mode slot remains zero; no extra logical
input is invented.

`UpdateOrbitCameraFollowPoint(camera, mode)` calls that same worker with
`(camera, mode, camera+0x18, camera)`. The last argument is output and aliases
the beginning of the native controller view. Preserve the worker's operation
order and this aliasing; a host port should introduce explicit controller types
only after recovering their complete layouts.

`UpdateOrbitCameraInputFollowAndDrift` calls orbit input update, follow-point
update and drift in that order, then returns integer 0.
`UpdatePathCameraTrackingAndDrift` calls collision update, player direction
tracking, up-vector clamping and drift in that order, then returns integer 0.
The two native controller words are retained; their general names do not imply
a complete callback ABI. `RestoreCameraTrackingAndUpdate` restores tracking and
then calls `Camera_Update(1)`; the latter can still exit early when frozen.

## HUD forwarding wrappers

The two overlay041 HUD wrappers target `LoadHudLayersAndRecordText` and
`UnloadHudLayersAndRecordText`. Their shared source filenames mention PXI, but
the actual targets handle HUD layers/text, not a FIFO. The pointer-return legacy
template does not establish a returned allocation or ownership transfer. These
names describe the delegates without assigning a movie-only role to the HUD.

## Evidence and verification

The production files listed above, `Ov042CameraState.h`, `CameraManager.h`,
`BuildCameraFrustumColliders`, `Camera_ComputeFollowPoint`,
`Camera_ComputeHeadingOffset`, `Camera_RestoreSavedTracking` and their actual
callers provide the source evidence. Ghidra reads use `program=recoded.nds` and
the correct `arm9_ovNNN` space; return-register instructions are checked where
existing decompiler prototypes disagree.

From `eu/`, examples for the recovered returns and pointer views:

```sh
python tools/verify_idx.py src/overlays/ov042/calls/Ov042Camera_GetState.c Ov042Camera_GetState --thumb
python tools/verify_idx.py src/overlays/ov042/calls/GetCameraColliderOffsetMagnitude.c GetCameraColliderOffsetMagnitude --thumb
python tools/verify_idx.py src/overlays/ov042/auto/GetCameraFrustumBounds.c GetCameraFrustumBounds --thumb
python tools/verify_idx.py src/overlays/ov046/calls/GetCameraManagerWork.c GetCameraManagerWork --thumb
python tools/verify_idx.py src/overlays/ov046/calls/ComputeCameraFollowPointWithDefaultHeading.c ComputeCameraFollowPointWithDefaultHeading --thumb
bash tools/gate.sh
```

The official per-function checks cover all 20 renamed entrypoints. Integration
also compares affected production texts, resolved relocation targets/types and
addends with the preserved baseline, followed by the full 108-module gate.
