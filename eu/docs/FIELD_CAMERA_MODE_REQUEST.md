# Stored field camera-mode request

| EU identity | Name | Native declaration |
|---|---|---|
| ov001:02063a58 | `SetFieldCameraModeRequest` | void(u8 value) |
| ov001:02063a6c | `GetFieldCameraModeRequest` | s32(void) |
| ov001:02065460 | `ScriptCmd_SetFieldCameraModeRequest` | int(int arg0, int arg1) |

The setter stores a byte at field session +0x27b4. The getter reads that byte with signed extension; 0xff therefore returns -1. The script command decodes an integer, narrows it to a signed byte, forwards its low bits to the setter and returns 1. The command is registered in engine handler group 2 at opcode 0x1a, with no resume entry. MAIN VM run result 1 advances the command cursor. Preserve this protocol and the existing native argument slots.

The stored value is a request for later application, not an immediate call or a read of the live camera state. The scene load/resume paths in overlays 028, 029, 032 and 040 pass it as the first argument to ForwardSubModePairB, with second argument 0. HandleSessionScriptResult resets the stored request to 0 during its transition cleanup.

The exact forwarder backends establish the camera role. Mode 0 calls overlay 046 Camera_RequestMode, which stores a mode and previous mode or delegates to Camera_SetMode. Mode 1 calls overlay 042 SetCameraColliderRegistrationMode, which removes its three camera colliders and reinserts them only for value 1. Mode 2 calls the overlay 043 no-op; mode 3 also does nothing. The same byte therefore has backend-specific effects. Do not export a guessed common mode enum, reinterpret it as an audio handle or promise that setting it changes a camera immediately.

Preserve the byte store, signed getter, script narrowing, reset and deferred application. No guard, range clamp, camera-state synchronization or callback ABI cleanup is included. FIELD_SESSION_PHASE_CAMERA5_REVIEW_V1.json gives current source paths, exact native instructions, bank-qualified function identities, descriptor pointer and source hashes.




## Active EU sources

- [SetFieldCameraModeRequest](../src/overlays/ov001/calls/SetFieldCameraModeRequest.c).
- [GetFieldCameraModeRequest](../src/overlays/ov001/calls/GetFieldCameraModeRequest.c).
- [ScriptCmd_SetFieldCameraModeRequest](../src/overlays/ov001/calls/ScriptCmd_SetFieldCameraModeRequest.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldCameraModeRequest.c SetFieldCameraModeRequest --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldCameraModeRequest.c GetFieldCameraModeRequest --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetFieldCameraModeRequest.c ScriptCmd_SetFieldCameraModeRequest --thumb
bash tools/gate.sh
```
