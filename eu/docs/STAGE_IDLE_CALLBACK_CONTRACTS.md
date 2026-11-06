# Stage task continuation and stage-event idle state

These callbacks have the same four-byte Thumb body, `movs r0,#0; bx lr`, but
operate in different dispatch protocols. Both keep their existing int(void)
definitions and shared implementations; neither receives a new parameter.

## StageManager_IdleTaskUpdate

The native gStageManagerTaskDescriptor at ov001:020a0360 contains initializer
02099651, shutdown 02099905 and work size 0x18f60. CreateStageManagerTask passes
that descriptor to CreateTaskObject. Obj_Construct loads descriptor+4 and BLX
calls it at 0202a594; it stores the returned R0 at current task+0x14 at 0202a59c.

CreateStageManager publishes the current task work as gStageManager and returns
Thumb callback 02099af5: LDR at 02099878 loads that word from pool 020998d0.
The callback itself is ov001:02099af4. Obj_UpdateAll invokes task+0x14 at
0202a6dc and replaces it only when the returned value is nonzero
(0202a6ec..0202a6f4). Zero therefore retains this idle task update. It is not
constructor failure, task suspension or task destruction. Incidental entry
R0 contains a callback address, not a demonstrated logical input.

## StageEventState_Idle

The independent gStageScriptStateHandlers table at ov001:020a0298 stores
02093605 in slot 1. UpdateStageEvent loads the event's word 0 as the table
index at 02094a0c, supplies the event pointer, and invokes that entry at
02094a32. A zero result skips SetStageEventHandlerState and retains the current
handler state. InitializeActorStats explicitly passes state 1 to that setter
at 02093e38..02093e3a, closing the initialization side of the contract.

The ov001:02093604 callback thus represents the idle handler state. This does
not stop all event/actor work: UpdateStageEvent performs its separate state-1
flag clearing and later motion/attachment updates. Keep that distinction in a
port. The table still erases callback prototypes; the real int(void) leaf reads
no arguments, and this name does not certify a uniform portable function type.

## Evidence

Ten full function ranges were compared unmasked with the extracted native
modules, together with the descriptor and state-table words. Exact basic
blocks establish the invocation/result rules; inline Thumb literal pools are
not treated as executed instructions. Receipt SHA-256:
`66bf4d40317532db4db4b484c3ff2b266ed5c094f1c5825f85b93218917fc42e`.

- [Idle task callback](../src/overlays/ov001/auto/StageManager_IdleTaskUpdate.c).
- [Idle event state](../src/overlays/ov001/auto/StageEventState_Idle.c).
- [Manager constructor](../src/overlays/ov001/calls/CreateStageManager.c).
- [Task descriptor](../src/overlays/ov001/data/tables/gStageManagerTaskDescriptor.c).
- [Event dispatcher](../src/overlays/ov001/calls/UpdateStageEvent.c).
- [State table](../src/overlays/ov001/data/tables/gStageScriptStateHandlers.c).

## Byte-exact validation

All ten affected official function checks pass. All 12 complete objects preserve allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Source bodies, signatures and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/StageManager_IdleTaskUpdate.c StageManager_IdleTaskUpdate --thumb
python tools/verify_idx.py src/overlays/ov001/auto/StageEventState_Idle.c StageEventState_Idle --thumb
bash tools/gate.sh
```
