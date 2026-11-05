# Saved camera and world-to-screen projection

This block identifies the existing camera snapshot, temporary orthographic setup
and screen projection. Names come from the matched bodies and their callers;
older `PXI` labels in these paths did not describe communication routines.
`CameraState.h` is the common EU interface for these operations.

## Names and direct evidence

| Previous symbol | Current name | Evidence |
|---|---|---|
| `func_01ff9b70` | `BuildCameraLookAtMatrix` | Normalizes position minus target, constructs right/up with cross products, and stores the basis and negative position dot products in a 4x3 matrix. |
| `func_020289c0` | `GetOrthographicCameraBeginCallback` | Returns the address of `BeginOrthographicCamera`; it does not call it. |
| `func_02028b30` | `GetSavedCameraRestoreCallback` | Returns the address of the saved-camera restore function. |
| `func_02028c20` | `GetSavedCameraPosition` | Returns the saved position vector at backup `+0x0c`. |
| `func_02028c2c` | `GetSavedCameraTarget` | Returns the saved target vector at backup `+0x00`. |
| `func_02028c38` | `ProjectWorldPositionWithSavedCamera` | Transforms through the saved view/projection matrices, divides by W and converts to current viewport coordinates. |
| `func_ov001_02088ab0` | `ProjectWorldPositionWithSavedCameraWrapper` | Forwards the world position and both output pointers to that projector. Speech-balloon and actor-order callers supply all three arguments. |
| `ResetCameraToDefaults` | `RestoreSavedCamera` | Restores saved projection and camera vectors, then rebuilds the view matrix. It does not load fixed defaults. |
| `PXI_Init_02028dc0` | `BeginOrthographicCameraWrapper` | Calls `BeginOrthographicCamera` and forwards its result. |
| `PXI_Init_02028dcc` | `RestoreSavedCameraWrapper` | Calls the restore function and forwards its result. |

The projector is moved from `libs/nitro/nns/calls` to `src/calls`: its body
operates on the game's camera backup and uses SDK math/viewport helpers.
This source classification does not add reconstruction credit or claim a
recovered original development-time symbol.

## Snapshot layout and lifetime

`gSavedCameraState` owns one 148-byte `CameraBackup` in BSS:

| DS byte offset | Type | Field |
|---|---|---|
| `0x00` | `VecFx32` | Target |
| `0x0c` | `VecFx32` | Position |
| `0x18` | `VecFx32` | Up vector |
| `0x24` | `MtxFx44` | Projection matrix |
| `0x64` | `MtxFx43` | View matrix |

`BeginOrthographicCamera` copies these five values from the active SDK state
before installing a temporary camera. The saved position/target getters return
borrowed pointers into this same object, with a read-only interface. They do
not allocate or copy. A later begin operation overwrites their contents.

There is one backup, not a stack of camera scopes. Repeated/nested begin calls
overwrite it; restoring does not recover an earlier snapshot after that. A port
must preserve or deliberately replace this shared lifetime contract. The backup
is not a full SDK state save: it contains no viewport or dirty-flag snapshot.
The existing `CameraGlobalState` is only the recovered view of fields used here,
not a claim that all SDK object fields have been identified.

## Begin and restore

The temporary projection uses `MTX_OrthoW` with top/bottom `192/0`, left/right
`0/256`, near/far `0/3` and W scale `1024`, all in fx32. The camera position is
`(0, 0, 1024)`, up is `(0, 1, 0)` and target is `(0, 0, 0)`. The routine clears
SDK flag masks `0x50` and `0xe8` around the corresponding state updates and
returns zero. These numeric masks are established; this block does not invent
per-bit names.

`RestoreSavedCamera` copies the saved projection and restores position, up and
target. It **rebuilds** the SDK view matrix from those vectors, rather than
copying the saved view matrix verbatim. It clears the same flag masks and
returns zero. The separate saved view matrix remains the one used by the
projector. Preserve this distinction if matrices can be modified independently
of camera vectors.

`BuildCameraLookAtMatrix` forms look = normalize(position - target),
right = normalize(up cross look), and corrected up = look cross right.
It stores the three basis vectors in the observed matrix columns and the
three negative position dot products in its translation row. It delegates
normalization and fixed-point dot/cross behavior to the existing vector helpers;
there is no added zero-length/parallel-up fallback.

The two callback getters now return `CameraStateCallback` (`int (*)(void)`),
not an integer containing a function address. Descriptor A/B keep their existing
five-word storage and erased entries; this evidence establishes their getter
references, not a complete descriptor/class schema or the other entry meanings.

## Projection and return contract

`ProjectWorldPositionWithSavedCamera` takes a world `VecFx32` and two required
`int *` outputs. The matrices come from the **saved** camera. The viewport comes
from the **current** `NNS_G3dGlbGetViewPort` call, so changing the viewport after
the snapshot affects the result. Begin/restore do not save or restore it.

The path is:

1. Transform the world vector using the saved 4x3 view matrix.
2. Form clip X, Y and W using the saved 4x4 projection. The summed products
   shift right by 12 before adding their translation terms.
3. Start the existing asynchronous fixed-point reciprocal for W. Multiply X/Y
   by its fx64c result with the existing `+0x80000000` / `>>32` rounding.
4. Convert each result with `(value + 0x1000) / 2`. Signed division and the
   integer rounding stages remain part of the native behavior.
5. Return `0` if both converted values are in inclusive `[0, 0x1000]`, otherwise
   return `-1`. Regardless of this result, write both screen coordinates.

For those converted values `nx`, `ny`, the final native arithmetic is:

```c
width = right - left;
height = bottom - top;
*screenX = left + ((nx * width + 0x800) >> 12);
*screenY = 191 - top - ((ny * height + 0x800) >> 12);
```

There is no `+1` in the viewport dimensions. Y is inverted around the DS screen
constant 191. The return value tests normalized X/Y only; there is no depth,
near/far or W-sign rejection. There is no local W-zero guard or null-output
validation. Negative/outside results are still written and callers may use them.
The reciprocal helper's behavior and shared divider state are not replaced by
host floating-point division in the matching code.

`ProjectWorldToScreenFacing` is a separate consumer. It ignores the projection
status, uses saved target minus saved position and world minus saved position,
and normalizes those vectors only after both squared lengths test nonzero.
When their normalized dot product is negative it mirrors the outputs as
`255 - x`, `191 - y`. This extra behavior does not belong to the projector's
return contract. `PlaceSlotPanelAtWorldPosition` also intentionally ignores the
status before converting pixels to its panel coordinates.

## Native interfaces and port boundary

The common header now declares typed vector getters, callback getters, begin,
restore, projection and wrappers. `ProjectWorldToScreenFacing` and
`PlaceSlotPanelAtWorldPosition` use it directly. The projection wrapper declares
its three real arguments and `int` result instead of an empty parameter list
and pointer result. Function addresses are no longer truncated to `int` by the
callback getters.

Remaining included US caller templates still have their original declarations
and EU aliases; some erase a result or represent a DS address as `u32`. Those
legacy views are not a complete host API. Before porting them, normalize each
caller to the common prototype, retaining whether it uses or ignores the result.
The descriptor entries still explicitly erase callback types into DS word
storage and need a recovered host representation separately.

Keep 32-bit fx32 arithmetic, the order of rounding, viewport edges and the
191/255 conventions explicit when adapting to another renderer. The existing
layout checks describe DS storage; they do not make SDK globals or serialized
pointer-sized fields a portable host object layout. No claim of thread safety,
reentrancy, complete clipping or restored renderer state is established here.

## Reproduction

From `eu/`:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/calls/BuildCameraLookAtMatrix.c BuildCameraLookAtMatrix
python tools/verify_idx.py src/calls/GetOrthographicCameraBeginCallback.c GetOrthographicCameraBeginCallback --thumb
python tools/verify_idx.py src/calls/GetSavedCameraRestoreCallback.c GetSavedCameraRestoreCallback --thumb
python tools/verify_idx.py src/calls/GetSavedCameraPosition.c GetSavedCameraPosition
python tools/verify_idx.py src/calls/GetSavedCameraTarget.c GetSavedCameraTarget
python tools/verify_idx.py src/calls/ProjectWorldPositionWithSavedCamera.c ProjectWorldPositionWithSavedCamera
python tools/verify_idx.py src/calls/BeginOrthographicCamera.c BeginOrthographicCamera
python tools/verify_idx.py src/calls/RestoreSavedCamera.c RestoreSavedCamera
python tools/verify_idx.py src/calls/BeginOrthographicCameraWrapper.c BeginOrthographicCameraWrapper
python tools/verify_idx.py src/calls/RestoreSavedCameraWrapper.c RestoreSavedCameraWrapper
python tools/verify_idx.py src/overlays/ov001/calls/ProjectWorldPositionWithSavedCameraWrapper.c ProjectWorldPositionWithSavedCameraWrapper --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ProjectWorldToScreenFacing.c ProjectWorldToScreenFacing --thumb
python tools/verify_idx.py src/overlays/ov001/calls/PlaceSlotPanelAtWorldPosition.c PlaceSlotPanelAtWorldPosition --thumb
bash tools/gate.sh
```

The ten renamed functions retain respectively 276, 8, 8, 12, 12, 392, 8,
164, 12 and 12 bytes in the table's order. Verification also covers the begin
operation, native consumers, other camera setup callers and descriptor storage
through the full linked gate. The direct index check for `RefreshResultsScreen`
has an inherited limitation: its ROM entry lists eight local branch relocations
that the compiler resolves internally. The saved baseline and updated object
retain identical instructions, resolved external targets and addends. That
caller is therefore checked by object equivalence and the official linked
module gate; the index and verifier are not changed to suppress the discrepancy.
Naming and interface recovery do not increase C or DATA reconstruction credit.
