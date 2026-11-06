# Advance a stage motion and retrieve its position

[StageScriptVec_AdvanceMotionAndGetPosition](../src/overlays/ov021/calls/StageScriptVec_AdvanceMotionAndGetPosition.c), EU ov021:020b1a9c, is an88-byte Thumb expression. It retains `u32 ...(int self)`, native old-style callback forwarding and opcode status0. It resolves the active event's motionId, obtains a borrowed record from [GetStageMotionRecord](../../src/ov001/shared_engine/GetStageMotionRecord_0209c18c.c), advances it by global scale and requests its current position into script context `+0x34`.

The callback writer is [BeginStageEntries](../../src/ov001/shared_engine/BeginStageEntries_02099aec.c), with [EU aliases](../src/overlays/ov001/calls/BeginStageEntries.c). Its five callback words begin at StageManager `+0x18f4c`. Slot2 (`+0x18f54`) advances the sequence; slot3 (`+0x18f58`) extracts its position.

| Session selector value | Advance callback | Position callback |
|---|---|---|
| 2 | [ov006 AnimSequence_Update](../../src/ov006/animation_sequence/AnimSequence_Update_020a1570.c), EU020a1590 | [ov006 GetStageJointPosition](../../src/ov006/reviewed_helpers/GetStageJointPosition_020a1694.c), EU020a16b4 |
| 6 | [ov010 AnimSequence_Update_020a1b70](../../src/ov010/animation_sequence/AnimSequence_Update_020a1b50.c), EU020a1b70 | [ov010 AnimSequence_GetCurrentPosition](../../src/ov010/animation_sequence/AnimSequence_GetCurrentPosition_020a1c74.c), EU020a1c94 |

The selector remains [func_ov001_02064784](../src/overlays/ov001/calls/GetScriptHandlerSlot7Index.c), a signed read of session byte `+0x18`. These branch values and exact bank-qualified pointer bindings are proven; a broader meaning or enum for that byte is not asserted.

Both update implementations add the supplied step to the sequence frame and handle animation clip/loop progression and accumulated root translation. Both extractors evaluate the current animation/root matrix and write sequence offset plus matrix translation. The result is that computed motion position, not a promise of StageActor world position, collision position or arbitrary joint selection.

Preserve the native edge cases. The active event is dereferenced before any NULL guard. A missing motion record leaves the vector untouched. The manager and the two callbacks are independently optional, and the manager is acquired again before extraction. The first call may change state; a port must not combine the pair, require both callbacks or turn this updating expression into a pure getter. The source does not check backend residency at runtime and no new check is introduced.



## Byte-exact validation

All 14 affected official function checks pass. All 16 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Bodies, prototypes, numeric constants and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptVec_AdvanceMotionAndGetPosition.c StageScriptVec_AdvanceMotionAndGetPosition --thumb
bash tools/gate.sh
```
