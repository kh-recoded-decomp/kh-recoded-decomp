# Conditional script wait for the camera collider offset

`ScriptCmd_WaitForState4CameraOffsetToClear` is ov001:020656d4, Thumb, 88 bytes, with the unchanged native declaration BOOL(void). Its EU source is src/overlays/ov001/calls/ScriptCmd_WaitForState4CameraOffsetToClear.c. The ROOT body remains src/ov001/unclassified_helpers/func_ov001_020656d4.c.

The same native pointer occupies the run and resume entries for handler group 2, opcode 0x2e. It decodes no operands. VM return 0 keeps the wait active, and return 1 advances the command. The name describes that operational protocol, not an inferred gameplay purpose or an identified asset-script intention.

The camera getter and writers use the same gCameraSceneGlobalStorage allocation. Ov042CameraState asserts colliderOffset at +0x11c. GetCameraColliderOffsetMagnitude passes the address of that exact vector to VEC_Mag. OffsetCameraColliders writes its supplied delta there and applies the same delta to three colliders. UpdateCameraScene writes its combined camera translation delta there after moving the collider shapes. This is not a separate normalized vector or a value borrowed from another owner.

If FieldSessionState is not 4, the command completes immediately even when the camera vector is nonzero. In state 4, it waits only while the signed magnitude is greater than zero. Only inside that wait branch, zero primary actor HP clears packed bit 0x3525, clears session byte +0x27b6 mask 0x10 and sets packed bit 0x3637. Both HP branches still return 0; zero HP does not itself complete the wait.

Preserve the exact state and magnitude tests, the primary actor and HP dereferences without added guards, and every flag side effect. State 4 receives no invented gameplay name. The operation is not a general camera-completion, idle or mission-failure predicate, and the value is not converted to host time or distance units.

RESULTS_TRANSITION_SCROLL5_REVIEW_V1.json records source paths and hashes, numbered writer/consumer evidence, exact script-table words and complete original BK9P NDS function comparisons. Native declarations and bodies remain unchanged.




## Active EU sources

- [ScriptCmd_WaitForState4CameraOffsetToClear](../src/overlays/ov001/calls/ScriptCmd_WaitForState4CameraOffsetToClear.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_WaitForState4CameraOffsetToClear.c ScriptCmd_WaitForState4CameraOffsetToClear --thumb
bash tools/gate.sh
```
