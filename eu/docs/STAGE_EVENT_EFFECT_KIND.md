# Active stage-event effect kind

`StageScriptExpr_GetEventEffectKind` is EU ov021:020b0bec. Keep its native declaration `u32 StageScriptExpr_GetEventEffectKind(int self)`, its instructions and all types unchanged. With an active StageEvent it writes integer tag1 at script-context+0x2c and zero-extends event byte+0x0c into value+0x30. It returns opcode status0. If the event is absent it leaves its own result fields untouched; the ordinary indexed dispatcher separately supplies default tag1/value0.

The owner is exact: RunScriptThread clears the12-byte active FieldContext, stores GetStageEventRecord(ownerId) in word0 for ownerKind1 and invokes script handlers with that active context. The numeric DATA label and gActiveFieldContext are aliases of the same BSS identity; their normalization is separate from this naming proposal.

The missing writer is demonstrated by SetStageEventKind and StartStageEventKind: both write the same+C byte. The start function selects gStageEventKinds[kind], which contains ten action/attachment/object/mirror/duration records, initializes the duration and elapsed fields and applies its actor or visual action. UpdateStageEventTimers switches on the same byte, forwards it into delayed starts and clears it to0 when its effect duration expires. ApplyHitToEnemyGroup passes a hit-effect selector after chance/resistance checks. These operations establish an effect-kind selector without assigning guessed gameplay names to the individual codes.

The field is distinct from StageEvent's handler-state word+0, its actor/resource kind halfword+0x0e and the script query index. Preserve the raw byte result, including unrecognized values. Do not normalize it to BOOL, export a guessed status enum, impose a0..9 guard or convert raw fixed-point durations to seconds.

The expression is installed in gScriptQueryHandlers slot139, at original overlay021 pointer-pool address020b5584 containing020b0bed. Current source is eu/src/overlays/ov021/calls/StageScriptExpr_GetEventEffectKind.c; the active named path is eu/src/overlays/ov021/calls/StageScriptExpr_GetEventEffectKind.c. Exact current source paths, evidence lines and hashes are in STAGE_EVENT_EFFECT_KIND1_REVIEW_V1.json.

Direct original BK9P extraction confirms the complete 28-byte getter and eight related native functions against the unmasked index.

## Byte-exact validation

All 14 official affected function checks pass. All 21 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Native bodies, prototypes and shared ROOT sources are preserved. Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetEventEffectKind.c StageScriptExpr_GetEventEffectKind --thumb
bash tools/gate.sh
```
