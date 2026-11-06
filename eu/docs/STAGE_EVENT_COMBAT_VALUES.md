# Stage-event health and attack power

The three expressions read combat values from the active StageEvent. Each keeps its native `u32` opcode result, fixed-point tag `0x10` and raw result word at script context `+0x30`.

| EU identity | Expression and current source | Native size | Query slot |
|---|---|---:|---:|
| ov021:020b10c0, Thumb | [StageScriptExpr_GetEventHealth](../src/overlays/ov021/calls/StageScriptExpr_GetEventHealth.c) | 28 | 22 |
| ov021:020b0dd4, Thumb | [StageScriptExpr_GetEventMaxHealth](../src/overlays/ov021/calls/StageScriptExpr_GetEventMaxHealth.c) | 28 | 115 |
| ov021:020b0df0, Thumb | [StageScriptExpr_GetEventAttackPower](../src/overlays/ov021/calls/StageScriptExpr_GetEventAttackPower.c) | 52 | 113 |

[RunScriptThread](../src/overlays/ov021/calls/RunScriptThread.c) establishes word0 of the active field context as `GetStageEventRecord(ownerId)`. A missing event leaves each helper's result fields untouched; ordinary indexed dispatch initializes its own default integer tag1/value0 before calling a query. The query's return status0 is separate from that tagged value.

Current health is event `+0x70`, and maximum/reference health is `+0x74`. The [damage consumer](../../src/ov001/shared_engine/ApplyHitToEnemyGroup_020958f4.c) subtracts computed damage from `+0x70`, handles defeat when it is nonpositive, tests `+0x70 == +0x74` for full health and divides current by reference health for boss-gauge stages. [UpdateStageManager](../src/overlays/ov001/calls/UpdateStageManager.c) restores `+0x70` from `+0x74`. The [stat constructor](../../src/ov001/shared_engine/InitializeActorStats_02093c70.c) and [level scaler](../../src/ov001/unclassified_helpers/ComputeLevelStats_0209d29c.c) initially set both equally.

Some private types in those constructor/scaler sources label the two words in reverse; the [ResetActorMotion shared view](../../src/ov001/actor_animation/ResetActorMotion_02093e28.c) calls them speed/baseSpeed. Those legacy labels do not define the public field contract. The actual damage, restoration and gauge operations establish the order.

[ScriptCmd_SetProperty](../src/overlays/ov021/calls/ScriptCmd_SetProperty.c) retains arbitrary fixed-point health assignment through property `0x16` and pair copying through `0x90`. Kind61 has a special proxy path: a copied positive-to-nonpositive transition sends reference health as an attack packet value, resets current health to1 and invokes damage handling. Preserve that behavior; do not clamp health, remove the proxy or assume every opaque event subtype has a finalized host layout.

The indexed power query evaluates operand `+8` before checking the event, computes `(value + 1U) & 0xffff` and calls [GetEntryScaledValue](../../src/ov001/shared_engine/GetEntryScaledValue_02096ba4.c) with its1-based index. The constructor/scaler fills eight32-byte modifier records at event `+0xa0`, each with its computed value at record `+8`. [ProbeKnockbackStageTarget](../../src/ov001/shared_engine/ProbeKnockbackStageTarget_02096f38.c) forwards the selected value as hit-message attack power into the damage consumer. Preserve unchecked indexing, operand order and the helper's byte `+0x0a == 3` branch with `FX_Mul(value, 0x1000)`; no guessed element enum or algebraic rewrite follows from the name.

The two health declarations remain `u32 ...(int self)`; the power declaration remains `u32 ...(int self, int args)`. Existing pointers/old-style forwarding are native ABI views, not portable host headers.



## Byte-exact validation

All 14 affected official function checks pass. All 16 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Bodies, prototypes, numeric constants and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetEventHealth.c StageScriptExpr_GetEventHealth --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetEventMaxHealth.c StageScriptExpr_GetEventMaxHealth --thumb
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetEventAttackPower.c StageScriptExpr_GetEventAttackPower --thumb
bash tools/gate.sh
```
