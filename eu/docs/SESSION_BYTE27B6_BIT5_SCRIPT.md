# Field script sets session byte 27B6 bit 5

`ScriptCmd_SetSessionByte27B6Bit5` is ov001:02065f04, Thumb, 28 bytes. The
matched definition remains `u32(void)`. It loads the byte at the live field
session's +0x27b6, ORs mask 0x20 and writes that byte back, preserving the
other seven bits. It then returns literal 1 and reads no script operands.
Bit5 is a zero-based bit index; the exact mask is 0x20.

## Exact storage owner and initial clear

The canonical BSS object `gFieldSessionWork` at ov001:020a0480 is a
four-byte pointer slot. It is not the session allocation itself.
`StartFieldSession` stores `GetRunningTaskWork()` into that slot, and
`ShutdownFieldSession` clears it on release.

The native `gFieldSessionClassDescriptor` at 0209e640 supplies constructor
02061469, destructor 02061b55 and workSize 0x29bc. `Obj_Construct`
allocates the descriptor's work size and calls `MI_CpuFill8(work,0,size)`
before invoking its constructor with the task installed as current.
`GetRunningTaskWork` returns that current task's work. Offset 0x27b6
falls inside this zeroed allocation. This proves construction-time zero
initialization of the byte, without claiming a later per-bit reset.

The command requires a live session pointer. It contains no null check;
this review adds no guard or new input.

## Script registration and returned value

`EnterPendingRoom` installs `gFieldScriptCommandHandlers` as group 2 via
`StoreGlobalArrayEntry`. Its opcode 0x58 pair contains run pointer 02065f05
and a null resume. The VM supplies its erased run arguments, but this
handler consumes neither and does not read operands.

For ordinary MAIN execution, run result 1 clears the main resume, advances
by the encoded instruction length and continues. In the auxiliary path,
the nonzero result clears that slot's callback/argument before advancing.
It is not a gameplay-policy success flag and installs no waiting callback.
The current unsigned 32-bit return type and erased table declarations
remain unchanged; no portable callback ABI repair is part of this name.

## Meanings that remain unresolved

The name describes the exact owner, offset and bit operation. It does
not identify why the game sets this bit. No semantic consumer of this
specific byte's mask 0x20 was established in the bounded review.

The session word +0x20 mask 0x20 read by `GetSessionFlagsMask20` is a
different field and width. The mask 0x10 used by the camera-offset command,
`TryRaiseSessionScriptFlags`, menu callbacks and HUD/gauge logic is bit 4
of this byte, not bit 5. The camera-offset command clears only mask 0x10,
preserving mask 0x20. `StoreSessionSpawnPoint` uses bit 0 independently.
Those neighboring uses do not establish this bit's policy, readiness,
input or gameplay meaning. A distinct runtime clearer remains unproved.

Evidence sources:

- `eu/src/overlays/ov001/calls/ScriptCmd_SetSessionByte27B6Bit5.c`
- `eu/src/overlays/ov001/data/bss/Bss_ov001_020a0480.c`
- `eu/src/overlays/ov001/data/tables/gFieldSessionClassData.c`
- `eu/src/overlays/ov001/calls/StartFieldSession.c`
- `eu/src/overlays/ov001/calls/ShutdownFieldSession.c`
- `eu/src/calls/Obj_Construct.c`
- `eu/libs/nitro/nns/calls/GetRunningTaskWork.c`
- `eu/src/overlays/ov001/data/tables/gFieldScriptCommandHandlers.c`
- `eu/src/overlays/ov001/calls/EnterPendingRoom.c`
- `eu/src/calls/StoreGlobalArrayEntry.c`
- `eu/src/calls/ScriptVm_RunFrame.c`
- `eu/src/overlays/ov001/auto/GetSessionFlagsMask20.c`
- `eu/src/overlays/ov001/calls/ScriptCmd_WaitForState4CameraOffsetToClear.c`
- `eu/src/overlays/ov001/calls/TryRaiseSessionScriptFlags.c`
- `eu/src/overlays/ov001/calls/StoreSessionSpawnPoint.c`
- `eu/src/overlays/ov001/calls/RunMenuEntryCallbacks.c`

Fourteen complete original function extents and the native descriptor and
handler-table words were compared with the extracted EU ROM. An explicit
bank-qualified Ghidra read independently corroborates the byte operation.
No candidate was compiled; official configured-path checks and the full
byte-exact gate remain integration work.


## Active EU sources

- [ScriptCmd_SetSessionByte27B6Bit5](../src/overlays/ov001/calls/ScriptCmd_SetSessionByte27B6Bit5.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetSessionByte27B6Bit5.c ScriptCmd_SetSessionByte27B6Bit5 --thumb
bash tools/gate.sh
```
