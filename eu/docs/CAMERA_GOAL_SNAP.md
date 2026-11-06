# Camera goal direct-apply control

`SetCameraGoalSnapEnabled` (ov042:020be4bc, Thumb, 16 bytes) stores its raw
`u32` input in the camera singleton's word +0x144. It does not clamp or
canonicalize the input. Its matched definition remains `void(u32)`.

The exact reader is `StepCameraGoalTowardTarget` (ov042:020be408). The
private source layout places `locked` at +0x144; the native instructions
read this same word. Before reading it, the helper clears it whenever
`GetFieldSessionPhase()` is neither 7 nor 8. No gameplay label is assigned
to those two phase values.

A nonzero word bypasses the proportional approach and calls
`SetCameraGoalTarget` directly with the vector at camera+0x88. With a zero
word, the helper measures the vector from camera+0x70 to camera+0x94.
For distance above 0x10 it translates by `FX_Mul(distance,0x300)`, clamped
to [0, distance]. On arrival it applies the saved target at +0x88. Zero
distance returns without that application. The helper returns TRUE in
all of these paths; this is separate from the setter's void contract.

`SetCameraGoalTarget` derives a translation from the input to camera+0x64,
updates the paired goal vectors through `TranslateCameraGoal`, and copies
the resulting vectors into the current camera fields at +0x14/+0x20 and
+0x110. The name describes this specific direct-apply branch. It does not
claim to stop every camera interpolator or the separate followFlags at
+0x140.

`InitCameraScene` initializes the word to 0. The exact ov030
`ClearSceneEntry` clears the selected scene entry's ID and calls this
setter with 1. That trigger is preserved; it does not identify phase 7/8
or establish a wider reset/dirty-state meaning.

Evidence sources:

- `eu/src/overlays/ov042/calls/SetCameraGoalSnapEnabled.c`
- `eu/src/overlays/ov042/calls/StepCameraGoalTowardTarget.c`
- `src/ov042/camera/StepCameraGoalTowardTarget_020be3e8.c`
- `eu/src/overlays/ov042/calls/SetCameraGoalTarget.c`
- `eu/src/overlays/ov042/calls/TranslateCameraGoal.c`
- `eu/src/overlays/ov042/calls/InitCameraScene.c`
- `eu/src/overlays/ov042/calls/UpdateCameraScene.c`
- `eu/src/overlays/ov030/calls/ClearSceneEntry.c`
- `src/ov030/shared_engine/ClearSceneEntry_020bb424.c`

Eight complete original functions were compared to the extracted EU ROM.
The reader was independently recovered through a bank-qualified Ghidra
read-only decompilation. Official verification of any renamed source
remains an integration check. No prototype, layout or source body change
is proposed.


## Active EU sources

- [SetCameraGoalSnapEnabled](../src/overlays/ov042/calls/SetCameraGoalSnapEnabled.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov042/calls/SetCameraGoalSnapEnabled.c SetCameraGoalSnapEnabled --thumb
bash tools/gate.sh
```
