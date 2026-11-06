# Actor jump-step override hook

`Actor_TryOverrideJumpStepNoop` at EU `ov059:020c99ec` is a 16-byte Thumb helper. Its current source is `eu/src/overlays/ov059/calls/Actor_TryOverrideJumpStepNoop.c`; the API remains `BOOL Actor_TryOverrideJumpStepNoop(Actor *actor)`.

The helper reads the actor's player index at +0x930, calls `GetPlayerControlState`, discards that record, and explicitly returns `FALSE`. The lookup remains part of the native behavior. “Noop” describes declining to override the jump step; the function is not an empty `BX LR` body.

## Caller contract

`Actor_UpdateJump` passes its embedded jump block at actor +0x970 to `Actor_UpdateJumpCommandInput`. The latter calls this helper only for signed jump phase 1 or 2, except when actor state +0x944 equals 8. It then performs its separate charge-command update and forwards the helper result.

A `TRUE` result makes `Actor_UpdateJump` skip the remainder of the current jump step. `FALSE` continues gravity, velocity and phase processing. This helper always selects that continuation. The branch establishes no phase transition by itself; no ability, particular button, double jump or deliberately disabled feature is identified.

The private `HitEvent.kind` label in `Actor_UpdateJumpCommandInput` is misleading for this path. The actual argument is the embedded jump block, whose `airTime` is at +0x20 and signed `phase` at +0x24, equivalent to actor +0x994. These are jump phases rather than a demonstrated external hit-event kind. The existing prototype and code remain unchanged.

## Native evidence

- 0x020c99ee–0x020c99f2 construct offset 0x930 and load the actor's player index. The call at 0x020c99f4 resolves to `GetPlayerControlState`; `MOVS R0,#0` at 0x020c99f8 establishes the canonical `FALSE` return.
- 0x020ca360–0x020ca366 construct actor +0x970. At 0x020ca36a that pointer becomes R1 for the call to `Actor_UpdateJumpCommandInput` at 0x020ca36e.
- 0x020ca338–0x020ca342 read the signed phase at argument +0x24 and select phases 1 and 2. The helper call is at 0x020ca34a; its result is saved in R7, survives the charge-command call at 0x020ca354, and returns in R0 at 0x020ca358.
- 0x020ca372 compares the result with zero. The zero branch continues at 0x020ca378; the nonzero branch at 0x020ca376 jumps to the epilogue at 0x020ca5d8.

Source evidence:

- `eu/src/overlays/ov059/calls/Actor_TryOverrideJumpStepNoop.c:14`: returns `FALSE` after the lookup.
- `eu/src/overlays/ov059/calls/Actor_UpdateJumpCommandInput.c:29`: selects and forwards the helper result.
- `src/ov059/unclassified_helpers/Actor_UpdateJump_020ca33c.c:62`: obtains the actor's embedded jump block.
- `src/ov059/unclassified_helpers/Actor_UpdateJump_020ca33c.c:71`: skips the step for a nonzero result.
- `eu/src/overlays/ov059/calls/Actor_UpdateJump.c:4`: binds the shared source's callee to `Actor_UpdateJumpCommandInput`.

## Native provenance

The original `eu/recoded.nds` BK9P overlay-table entry 59 selects FAT range 0x10dc00..0x11551c. Decompression yields 35648 bytes at 0x020c7480, byte-identical to `eu/dsd_extract/arm9_overlays/ov059.bin`, SHA-256 `f33ed95586de5fa319353c235ebcc73c01e7e80b7fa8c082f070c809be1f5c36`. The instruction evidence comes from this original module.

## Name history

`func_ov059_020c99ec` is the previous symbol for `Actor_TryOverrideJumpStepNoop`.

## Validation

The official gate passed. All 14 individual byte-exact checks passed, all 21 complete objects retained their allocated sections, symbol layouts and relocation targets/types/addends, and all 108 module hashes remained unchanged. These counts cover the combined integration block containing these callbacks, the two stage-expression names and three existing DATA aliases.
