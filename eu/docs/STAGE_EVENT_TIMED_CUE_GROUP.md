# Stage-event timed-cue group selector

`ScriptCmd_SelectStageEventCueGroup` is EU ov021:020b37c0. Its unchanged native declaration is `u32 ScriptCmd_SelectStageEventCueGroup(u32 context, s32 operands)`; it returns opcode status0.

The command resolves a StageEvent reference, evaluates a value operand and computes `(value + 1U) & 0xffff`. Event byte+0x1b4 selects a1-based group from entry-file section16; zero disables processing. Byte+0x1b5 is the cursor within that group's section10 timed cues. The command clears the cursor only when the full computed16-bit value differs from the old8-bit selector, then writes the low8 bits. Preserve this comparison before truncation: values with nonzero upper8 bits can reset the cursor even when the final low byte is unchanged. Preserve the absence of NULL/index checks.

The missing consumer is `UpdateStageEvent` in overlay001. When actor/body gates permit, it reads section16[group-1], then section10[group.first+cursor]. A cue runs once the actor's frame counter reaches the cue frame. Type1 calls PlayActorSound; type2 sets the grid cell and behavior mask0x200; type3 clears walker state and that mask. After the frame test, the cursor increments even for an unrecognized type. At most one cue is consumed per update. Abort/reset paths also clear both bytes.

This timed event-cue group is separate from `ProcessStageCues`, which selects section14/8 collision-cue data and does not read these two event bytes. The StageEvent owns the selector/cursor; they are not the StageActor animation track fields. InitScriptHandlerTable installs this command at runtime opcode slot46, with original pointer0x020b37c1 in overlay021 pool020b4a00.

Current sources are `eu/src/overlays/ov021/calls/ScriptCmd_SelectStageEventCueGroup.c`, `eu/src/overlays/ov001/calls/UpdateStageEvent.c` and the resolver/registration/reset sources listed with exact lines and hashes in STAGE_EVENT_CUE_GROUP1_REVIEW_V1.json. The active named command path is `eu/src/overlays/ov021/calls/ScriptCmd_SelectStageEventCueGroup.c`. No body, prototype, field layout or DATA allocation change is made.

Direct original BK9P extraction confirms the complete 66-byte command and eight related native functions against the unmasked index.

## Byte-exact validation

All 14 official affected function checks pass. All 21 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Native bodies, prototypes and shared ROOT sources are preserved. Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov021/calls/ScriptCmd_SelectStageEventCueGroup.c ScriptCmd_SelectStageEventCueGroup --thumb
bash tools/gate.sh
```
