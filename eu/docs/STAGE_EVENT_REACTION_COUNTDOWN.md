# Stage-event reaction argument and countdown

These expressions describe demonstrated lifecycles while leaving unresolved gameplay meanings explicit.

| EU identity | Expression and current source | Native size | Result |
|---|---|---:|---|
| ov021:020b0e24, Thumb | [StageScriptExpr_GetHitReactionArgument](../src/overlays/ov021/calls/StageScriptExpr_GetHitReactionArgument.c) | 28 | Integer tag1; zero-extended event halfword+0x1e |
| ov021:020b12b8, Thumb | [StageScriptExpr_GetEventCountdown](../src/overlays/ov021/calls/StageScriptExpr_GetEventCountdown.c) | 32 | Fixed-point tag0x10; raw event word+0x1a0 |

Both declarations remain `u32 ...(int self)` and return opcode status0. With no active event they leave their own result fields untouched; indexed dispatch initializes its default separately.

The reaction argument has an explicit writer and completion path. [ApplyHitToEnemyGroup](../../src/ov001/shared_engine/ApplyHitToEnemyGroup_020958f4.c) clears the halfword, then on a stagger reaction copies hit-message `+0x2e` into event `+0x1e` just before selecting handler state5. [gStageScriptStateHandlers](../src/overlays/ov001/data/tables/gStageScriptStateHandlers.c) maps state5 to [WaitStageActorScript](../../src/ov001/shared_engine/WaitStageActorScript_020938d4.c). That handler runs actor script track6 and, on its normal completion path, clears the halfword. Keep its existing special-kind branches and early returns.

This proves an argument delivered to the hit reaction. Its units and individual values remain opaque: the private `stunTime` and signed `timer` labels do not prove frames, seconds or an enum. The getter deliberately zero-extends the unsigned halfword; a port must not infer signedness from the completion view.

The countdown has an explicit producer in [UpdateStageEvent](../src/overlays/ov001/calls/UpdateStageEvent.c). When configuration word `+0x64` or `+0x68` is nonzero, it subtracts the current actor scale from `+0x1a0` and clamps nonpositive results to0. Otherwise it writes `0x7fffffff`. Preserve that raw sentinel and fixed-point tagged representation; no host-time or BOOL conversion is implied.

The private `moveA`, `moveB` and `idleTimer` labels are not evidence for movement or idleness. [InitializeActorStats](../../src/ov001/shared_engine/InitializeActorStats_02093c70.c) obtains words64/68 through [LoadScaledOffsetPair](../src/overlays/ov001/calls/LoadScaledOffsetPair.c), which reads signed pairs from `En/Pa/UP.bin` and scales them. Their gameplay role, and all positive countdown initializers, remain unresolved. The expression name identifies the proven countdown operation without inventing those meanings.



## Byte-exact validation

All 14 affected official function checks pass. All 16 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Bodies, prototypes, numeric constants and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetHitReactionArgument.c StageScriptExpr_GetHitReactionArgument --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetEventCountdown.c StageScriptExpr_GetEventCountdown --thumb
bash tools/gate.sh
```
