# Current stage-script override ID

[StageScriptExpr_GetCurrentOverrideId](../src/overlays/ov021/calls/StageScriptExpr_GetCurrentOverrideId.c), EU ov021:020b10b0, is a16-byte Thumb expression registered in gScriptQueryHandlers slot23. It copies the unsigned halfword at sequence context `+0xa2` into integer tag1/value `+0x30` and returns opcode status0.

The native declaration retains four u32 arguments: `u32 StageScriptExpr_GetCurrentOverrideId(u32 argument0, u32 argument1, u32 argument2, u32 argument3)`. The latter three are synthetic unused register slots in the recovered C. They are preserved for matching and do not constitute a finalized host API.

The writer/lifetime is [RunOverrideTrack](../../src/ov021/unclassified_helpers/RunOverrideTrack_020b4b9c.c), with [EU aliases](../src/overlays/ov021/calls/RunOverrideTrack.c). It stores the supplied override ID at `+0xa2`, runs track10 through [SelectSequenceTrack](../../src/ov021/unclassified_helpers/SelectSequenceTrack_020b4bdc.c) and [RunScriptThread](../src/overlays/ov021/calls/RunScriptThread.c) using the same context, restores the normal track/timer/cursor/frame and clears the ID to0. The getter therefore exposes the current override while its script executes; it does not return a persistent selected-animation ID.

[InitSequencer](../../src/ov021/unclassified_helpers/InitSequencer_020b4aac.c) hides this field in private padding but clears it through whole0xa8-byte initialization. That padding declaration is not the only writer. The override ID is separate from the sequence/header ID at `+0xa0`.

Preserve unsigned extension, raw code values and absence of guards. Do not normalize the result to BOOL, invent an override enum or use this as a persistent animation-selection getter.



## Byte-exact validation

All 14 affected official function checks pass. All 16 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Bodies, prototypes, numeric constants and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/StageScriptExpr_GetCurrentOverrideId.c StageScriptExpr_GetCurrentOverrideId --thumb
bash tools/gate.sh
```
