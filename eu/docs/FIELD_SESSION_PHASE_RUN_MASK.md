# Field-session phase and script run mask

| EU identity | Name | Native declaration |
|---|---|---|
| ov001:02063a4c | `GetFieldSessionPhase` | int(void) |
| ov001:02063620 | `GetSessionScriptRunMask` | u32(void) |

GetFieldSessionPhase reads the full integer at session +0x1c. StartFieldSession initializes that word to 0 and installs RunFieldPhases as its continuation. The dispatcher calls gSessionScriptStateHandlers[phase], replaces the phase only for a nonnegative handler result and may run another phase in the same update. Its resulting phase 13 returns -2 after dispatch; the handler table itself has entries 0 through 12. Preserve that ordering and the absence of a bounds guard. This field is distinct from GetFieldSessionState, which reads the byte at +0x2808, and from the script binding indices at +0x18/+0x19.

GetSessionScriptRunMask reads session byte +0x2738 and returns its masked value 0x81. The script instance begins at +0x1f10, placing this run-flags byte at script +0x828. RunSessionScriptFrame sets bit 0 before calling the VM and clears the byte when VM execution completes. TryRaiseSessionScriptFlags sets bit 7 after its pending-entry and readiness gates; its EU signed constant -0x80 produces the same stored bit pattern0x80. SelectNextSessionState tests that bit and chooses phase 8. Menu-opening and idle checks use it for their own gates.

The aggregate result can be 0, 1, 128 or 129. It is not a Boolean, a complete idle predicate or every flag owned by the VM. Preserve the signed byte load followed by the mask, the raw u32 result and the absence of a session guard. No new enum, flag normalization, structure or host API layout is introduced.

FIELD_SESSION_PHASE_CAMERA5_REVIEW_V1.json records the exact source paths, writer and dispatcher lines, source hashes and complete original BK9P NDS function comparisons. The naming plan changes only symbols and basenames, keeping native bodies and declarations intact.




## Active EU sources

- [GetSessionScriptRunMask](../src/overlays/ov001/calls/GetSessionScriptRunMask.c).
- [GetFieldSessionPhase](../src/overlays/ov001/calls/GetFieldSessionPhase.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/GetSessionScriptRunMask.c GetSessionScriptRunMask --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldSessionPhase.c GetFieldSessionPhase --thumb
bash tools/gate.sh
```
