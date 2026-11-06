# Primary actor health restoration: three naming corrections

The previously retained pair ov001:02063c94 / 0206550c restores the primary
managed actor's current HP to its maximum. The dependency previously called
SetClampedCursor is the health setter in overlay 021. Native owner, writers,
combat behavior and final HUD consumers now close the earlier field-role gap.
The names now reflect that demonstrated role. Source bodies, private typedefs,
signatures, compiler profiles and shared ROOT implementations are preserved.

| EU identity | Previous name | Name | EU source |
|---|---|---|---|---|
| ov001:0x02063c94 (Thumb, 22 B) | `func_ov001_02063c94` | `RestorePrimaryActorHealth` | `eu/src/overlays/ov001/calls/RestorePrimaryActorHealth.c` |
| ov001:0x0206550c (Thumb, 10 B) | `func_ov001_0206550c` | `ScriptCmd_RestorePrimaryActorHealth` | `eu/src/overlays/ov001/calls/ScriptCmd_RestorePrimaryActorHealth.c` |
| ov021:0x020a75f8 (Thumb, 18 B) | `SetClampedCursor` | `SetActorHealthClamped` | `eu/src/overlays/ov021/calls/SetActorHealthClamped.c` |

## The demonstrated fields and their owner

The native setter entry is ov021:020a75f8, 18 bytes, not the historical ROOT
filename suffix 020a75d8. It loads the pointer at actor+0x1d4, reads an unsigned
halfword at record+4, compares the input against that maximum and stores the
chosen halfword at record+2. Its existing definition is
`void SetActorHealthClamped(CursorOwner *owner, u16 value)`. Private CursorRange
spelling does not establish a cursor domain.

`InitializeSharedOverlayObject` calls MAIN `GetOverlaySelectionRecord(index)`
and stores its return at actor+0x1d4. The getter computes
`gOverlaySelectionRecords + index*0x144`. Its existing physical owner in
`eu/src/data/bss/Bss_main_020608e4.c` is 243 words: three 0x144-byte records.
This ties the pointer to a real named DATA owner, not merely similar structs.

`SetupAllSelectionRecords` computes record 0 through `ComputePlayerStats`,
which writes the resulting health capacity at +4. `ApplySelectionStatScaling`
preserves the current halfword at +2, scales the maximum at +4 and clamps the
preserved current value to that maximum. No new complete record layout is
needed to establish these two fields; the other record fields stay outside
this naming change.

`AddClampedHealth` loads the same actor+0x1d4 pointer and the same +2/+4 unsigned
halfwords. It adds a signed delta to current HP, clamps 0..max HP and writes +2.
A positive delta can spawn its heal effect; zero current HP returns TRUE.
`Actor_HandleFallOut` calculates a negative 20-percent amount from +4, passes it
to that updater, and follows its respawn/reposition branch only if +2 is nonzero.
These operations connect the fields to damage, healing and remaining life,
independently of the old health/cursor labels.

The final display path is native `UpdatePartyState`: actor stats+4 is loaded
at 0206cc60 into the capacity passed in R1; stats+2 is loaded at 0206cc76 into
value R2; the call at 0206cc78 reaches `SetFieldHudGaugeRange`. It forwards through
`UpdateSlotRangeDefaultEnd` to `SetHudGaugeRange`, which stores the maximum and
current gauge values. `SetGaugeValues`/`SetHudGaugeValue` scale current/max by
`gHudGaugeTable` cell counts and redraw the gauge. The later current-value
update uses +2 too. Private level/characterId names in UpdatePartyState are
therefore misleading for these same halfwords.

The recently corrected `SetRecordPanelProgress` belongs to overlay 002's
separate packed-field command path. Its 0..100 clamp does not describe this
actor record or its maximum. Here the actor's own u16 capacity is the bound.

## Restore helper and script command

`RestorePrimaryActorHealth` keeps the existing `void name(void)` definition.
Native code requests `GetBoundedEntryField(0)`, loads its record pointer and
u16 maximum+4, then calls the real overlay 021 setter. Since the requested
value equals that same maximum, current HP becomes max HP. It performs no NULL
check; primary actor and record must already exist. It neither changes the
maximum nor adds a signed delta, resets the actor, consumes an item or calls
the positive-delta heal-effect helper.

`ScriptCmd_RestorePrimaryActorHealth` is run entry 0x1f of group 2 in
`gFieldScriptCommandHandlers`: flat pointer index 62, followed by NULL resume.
The actual native table word is 0206550d. The command calls the restore helper
and returns 1 immediately, consuming no operand descriptor and yielding no
resume operation. The group registration and eight-byte run/resume protocol
are documented in [FIELD_SCRIPT_EXTENSIONS.md](FIELD_SCRIPT_EXTENSIONS.md).

The matched source still declares an unused `void *p` and forwards R0 through
a legacy one-pointer declaration of the child. The real child consumes no
logical input. The erased table's `void(void)` declaration is another legacy
view, not evidence for a portable uniform callback type. Retain the matched
C declarations in this rename block; do not add an operand or rewrite ABI.

The setter's actual C value type and stored fields are u16. Preserve existing
call-site narrowing and declarations. Native callee code compares R1 directly
with the loaded u16 maximum; it has no explicit argument-narrowing instruction.
The present restore call loads its argument with LDRH. Do not use this naming
change to assert behavior for arbitrary untyped 32-bit arguments or silently
repair the differing legacy caller prototypes.

No existing common header for this exact actor/record view was found in the
directed EU/ROOT header check. Its definitions are private C views. The s16
maxHp in StageEntryRender.h belongs to a different owner and supplies no
layout proof here. This naming block introduces no header, struct, packing or field.

## Related pending field predicate

The still-numeric ov001:020656d4 also reads this current-HP halfword. Under
field state 4 and a positive overlay-042 getter, zero HP triggers packed-bit
updates and clears session+0x27b6 bit 4, whose mask is 0x10. The earlier
inventory incorrectly described that mask as 0x4. The native MOVS #0x10 and
BICS at 02065704/02065708 agree with the source's bit4 assignment.

This helper returns 0 under the outer condition for both zero and nonzero HP;
it returns 1 outside that condition. It is therefore not simply an actor-dead
predicate. The [exact script gate](FIELD_HP_CAMERA_SCRIPT_GATE.md) identifies
run/resume group 2/0x2e and VEC_Mag(camera+0x11c). Its intended state-4
wait/completion role remains open in the [pending inventory](EU_PENDING_FIELD_FUNCTIONS.md).

## Source and ROM evidence

The review compares 15 complete native function ranges with the original EU
ROM and identifies nine unique current callers of the setter. Historical
index aliases are not counted as additional callers. Native banks, offsets,
mode and compiler profiles establish each identity; the review receipt has
SHA-256 `529909d05c448da117758bab48aad73b407b39272b4e224cfcafae92f7c88c59`.

- [InitializeSharedOverlayObject](../src/overlays/ov021/calls/InitializeSharedOverlayObject.c).
- [GetOverlaySelectionRecord](../src/calls/GetOverlaySelectionRecord.c).
- [ComputePlayerStats](../src/calls/ComputePlayerStats.c).
- [ApplySelectionStatScaling](../src/calls/ApplySelectionStatScaling.c).
- [AddClampedHealth](../src/overlays/ov021/calls/AddClampedHealth.c).
- [Actor_HandleFallOut](../src/overlays/ov059/calls/Actor_HandleFallOut.c).
- [UpdatePartyState](../src/overlays/ov001/calls/UpdatePartyState.c).
- [gFieldScriptCommandHandlers](../src/overlays/ov001/data/tables/gFieldScriptCommandHandlers.c).

## Byte-exact validation

All 11 official function checks pass, including the setter and all nine
current callers. The 12 complete affected objects preserve allocated bytes
and alignment, symbol offsets/sizes and relocation targets/types/addends.
The script table preserves its native words. A fresh gate passes all 108
linked modules with every hash unchanged. Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/RestorePrimaryActorHealth.c RestorePrimaryActorHealth --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_RestorePrimaryActorHealth.c ScriptCmd_RestorePrimaryActorHealth --thumb
python tools/verify_idx.py src/overlays/ov021/calls/SetActorHealthClamped.c SetActorHealthClamped --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FieldObject_UpdateZoneTrigger.c FieldObject_UpdateZoneTrigger --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FlushPendingEntryRefresh.c FlushPendingEntryRefresh --thumb
python tools/verify_idx.py src/overlays/ov040/calls/InitAreaRewardScene.c InitAreaRewardScene --thumb
python tools/verify_idx.py src/overlays/ov040/calls/SetupAreaFieldState.c SetupAreaFieldState --thumb
python tools/verify_idx.py src/overlays/ov052/calls/UpdateActorFrame.c UpdateActorFrame --thumb
python tools/verify_idx.py src/overlays/ov058/calls/FinishEnemyRecovery.c FinishEnemyRecovery
python tools/verify_idx.py src/overlays/ov058/calls/RestoreEnemyHealthAndReset.c RestoreEnemyHealthAndReset
python tools/verify_idx.py src/overlays/ov059/calls/Actor_ResetMovementState.c Actor_ResetMovementState --thumb
bash tools/gate.sh
```
