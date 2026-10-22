#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole count as fx32, rounded half away from zero (converted once, after the rounding). */
#define COUNT_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

/* What the function returns. */
#define HIT_LANDED 1
#define HIT_CRITICAL 2
#define HIT_DEFEATED 4
#define HIT_GUARDED 8
#define HIT_HEALED 0x10

#define ACTION_KIND_FLURRY 5

extern int func_0202a9e4(u16 range);
extern int GetEntryAbility(StageEntry *entry, int ability);
extern void SetEntryState(StageEntry *entry, int state);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageMarker *ShowStageMarker(int listIndex, const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern int GetSessionStateFlags2Bit(void);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern u32 GetPlayerEntryCount(int player, u32 id);
extern int GetFlagTableValue(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void CheckEntryHpThresholds(StageEntry *entry);
extern u8 CountActiveStageEntries(BOOL primary);
extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetStageKindSoundArc(int kind);
extern BOOL PlaySoundChecked(int seqArcNo, int index);
extern void StartStageFadeOut(void);

/*
 * Applies an entry's hit to a target and returns what happened (HIT_*). A healing hit restores hp, and a reviving
 * one stands a primary target that was out back up. Otherwise the hit is critical for a finished combo, status 8 or
 * by its critical chance, guarded when a player-kind target guarded, and lands when critical, sure (accuracy 500),
 * on a target already down or by the accuracy roll against the target's hit rate; a miss shows the miss marker.
 * The damage grows with the hit's power over the target's defense along the difficulty's curve, is scaled by the
 * element, the critical, the guard, statuses and abilities, and is at least the hit's minimum. A target that drops
 * to 0 hp goes out unless it endures; the stage ends when that was its decisive enemy or the leader.
 */
u32 ResolveEntryHit(StageEntry *entry, StageEntry *target, StageEntryHit *hit)
{
    u8 heal;
    StageWork *work = gMovieContextState->stageWork;
    VecFx32 position;
    u32 result;
    BOOL landed;
    BOOL critical;
    BOOL guarded;
    s16 hitChance;
    f32 criticalScale; /* 1.5 for a critical */
    f32 guardScale; /* 0.5 when guarded */
    f32 levelScale; /* an enemy's hits grow with StageWork.introValue */
    f32 boostScale; /* 2 while the attacker has status 1 */
    f32 shieldScale; /* 0.5 while the target has status 2 */
    f32 rageScale; /* 3 while the attacker's status 0 is 1 */
    f32 resistScale; /* a primary target's resistance to the element */
    fx32 defenseScale; /* raised for targets with ability 4 */
    f32 halfScale; /* 0.5 for targets with ability 8 */
    f32 enemyScale; /* an enemy's hits scale with the flag table value */
    f32 elementRate; /* percent of the damage the target takes from the hit's element */
    f32 difficulty;
    fx32 base; /* the damage curve: base and growth per point of power over the defense */
    fx32 slopeBelow; /* while the power is below the defense */
    fx32 slopeAbove;
    fx32 power;
    fx32 overDefense;
    int seqArc;
    int index;
    int accuracy;
    u32 element;
    f32 elementScale;
    f32 rate;
    int damage;
    StageEntry *shown;
    f32 scaled;
    s16 amount;
    int level;
    int i;

    result = 0;
    landed = FALSE;
    critical = FALSE;
    guarded = FALSE;
    damage = hit->minDamage;
    criticalScale = 1.0f;
    guardScale = 1.0f;
    levelScale = 1.0f;
    boostScale = 1.0f;
    shieldScale = 1.0f;
    rageScale = 1.0f;
    resistScale = 1.0f;
    defenseScale = FX32_ONE;
    halfScale = 1.0f;
    enemyScale = 1.0f;
    if (GetEntryAbility(target, 4)) {
        defenseScale = 0x1500;
    }
    if (GetEntryAbility(target, 8)) {
        halfScale = 0.5f;
    }
    heal = hit->heal;
    if (heal == STAGE_HEAL_REVIVE || heal == STAGE_HEAL_HP) {
        s16 hp = target->hp;

        target->hp = hp + (s16)(hit->amount >> FX32_SHIFT);
        if (target->hp > target->maxHp) {
            target->hp = target->maxHp;
        }
        if (hit->heal == STAGE_HEAL_REVIVE && hp <= 0 && target->hp > 1) {
            if (!(target->flags & STAGE_ENTRY_ENEMY) && !(target->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
                target->slot.node.yaw = 0xc004;
                target->slot.node.flags |= STAGE_MODEL_USE_YAW;
            }
            SetEntryState(target, 1);
        }
        return HIT_HEALED;
    }
    switch (entry->kind) {
    case 0xfd:
    case 0xfe:
    case 0xff:
        if (entry->flags & STAGE_ENTRY_COMBO_FINISHED) {
            critical = TRUE;
        }
        break;
    }
    if (entry->statuses[8] > 0) {
        critical = TRUE;
    }
    if (!critical && (u32)func_0202a9e4(1000) < hit->critical) {
        critical = TRUE;
    }
    switch (target->kind) {
    case 0xfd:
    case 0xfe:
    case 0xff:
        if (target->flags & STAGE_ENTRY_GUARDED) {
            guarded = TRUE;
        }
        break;
    }
    accuracy = hit->accuracy;
    hitChance = (u16)((f32)accuracy * (f32)target->hitRate / 100.0f);
    if (critical) {
        landed = TRUE;
    } else if (accuracy == 500) {
        landed = TRUE;
    } else if (target->hp <= 0) {
        landed = TRUE;
    } else if (func_0202a9e4(1000) < hitChance * 10) {
        landed = TRUE;
    }
    shown = (entry->flags & STAGE_ENTRY_ENEMY) ? target : entry;
    if (!landed) {
        GetPositionAboveGround(&position, shown);
        position.y += FX32_ONE;
        ShowStageMarker(2, &position, FALSE);
        PlayStageSound(0x1a0, 2, TRUE);
    } else if (guarded) {
        GetPositionAboveGround(&position, shown);
        position.y += FX32_ONE;
        ShowStageMarker(0, &position, FALSE);
        PlayStageSound(0x1a0, 3, TRUE);
    } else if (critical) {
        GetPositionAboveGround(&position, shown);
        position.y += FX32_ONE;
        ShowStageMarker(1, &position, FALSE);
    }
    if (critical) {
        result |= HIT_CRITICAL;
    }
    if (guarded) {
        result |= HIT_GUARDED;
    }
    if (landed) {
        result |= HIT_LANDED;
    }
    if (!landed) {
        target->flags |= STAGE_ENTRY_DODGED;
        return result;
    }
    elementRate = 100.0f;
    difficulty = 1.0f;
    switch (hit->element) {
    case 0:
        elementRate = 100.0f;
        break;
    case 1:
        elementRate = target->elementRates[0];
        break;
    case 2:
        elementRate = target->elementRates[1];
        break;
    case 3:
        elementRate = target->elementRates[2];
        break;
    case 4:
        elementRate = target->elementRates[3];
        break;
    }
    if (elementRate > 200.0f) {
        rate = 200.0f;
    } else if (elementRate < 0.0f) {
        rate = 0.0f;
    } else {
        rate = elementRate;
    }
    elementScale = rate / 100.0f;
    switch (GetSessionStateFlags2Bit()) {
    case 0:
        difficulty = 0.9375f;
        break;
    case 1:
        difficulty = 1.0f;
        break;
    case 2:
        difficulty = 1.0625f;
        break;
    case 3:
        difficulty = 1.125f;
        break;
    }
    element = hit->element;
    if (element != 0) {
        elementScale = elementScale * difficulty;
    }
    if (critical) {
        criticalScale = 1.5f;
    }
    if (guarded) {
        guardScale = 0.5f;
    }
    if ((entry->flags & STAGE_ENTRY_ENEMY) && work->introValue > 1) {
        levelScale = work->introValue;
    }
    if (entry->statuses[1] > 0) {
        boostScale = 2.0f;
    }
    if (target->statuses[2] > 0) {
        shieldScale = 0.5f;
    }
    if (entry->statuses[0] == 1) {
        rageScale = 3.0f;
    }
    if (!(target->flags & STAGE_ENTRY_ENEMY) && element != 0 && element < 5 &&
        IsPlayerEntryFlagSet(0, element + 4)) {
        resistScale = (100.0f - GetPlayerEntryCount(0, hit->element + 4)) / 100.0f;
        if (resistScale < 0.0f) {
            resistScale = 0.0f;
        }
    }
    if (entry->flags & STAGE_ENTRY_ENEMY) {
        enemyScale = GetFlagTableValue() / 4096.0f;
    }
    base = 0;
    slopeBelow = 0;
    slopeAbove = 0;
    power = hit->amount;
    overDefense = FX_Div(power, FX_Mul(COUNT_TO_FX32(target->defense), defenseScale)) - FX32_ONE;
    level = GetSessionStateFlags2Bit();
    if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
        level = 1;
    }
    switch (level) {
    case 0:
        base = 0x1c0;
        slopeBelow = 0x1c0;
        slopeAbove = 0xc0;
        break;
    case 1:
        base = 0x280;
        slopeBelow = 0x280;
        slopeAbove = 0x100;
        break;
    case 2:
        base = 0x380;
        slopeBelow = 0x280;
        slopeAbove = 0x200;
        break;
    case 3:
        base = 0x500;
        slopeBelow = 0x280;
        slopeAbove = 0x300;
        break;
    }
    if (hit->amount >= COUNT_TO_FX32(target->defense)) {
        scaled = (f32)FX_Mul(base + FX_Mul(slopeAbove, overDefense), hit->amount) / 4096.0f;
    } else {
        scaled = (f32)FX_Mul(base + FX_Mul(slopeBelow, overDefense), hit->amount) / 4096.0f;
    }
    scaled = scaled * elementScale;
    scaled = criticalScale * scaled;
    scaled = guardScale * scaled;
    scaled = levelScale * scaled;
    scaled = boostScale * scaled;
    scaled = shieldScale * scaled;
    scaled = rageScale * scaled;
    scaled = halfScale * scaled;
    scaled = resistScale * scaled;
    scaled = enemyScale * scaled;
    amount = (s16)scaled;
    if (amount > 99999) {
        damage = 99999;
    } else if (amount >= damage) {
        damage = amount;
    }
    target->checkedHp = target->hp;
    target->hp -= (s16)damage;
    CheckEntryHpThresholds(target);
    if (landed) {
        target->flags |= STAGE_ENTRY_HURT;
    }
    if (critical) {
        target->flags |= STAGE_ENTRY_ALT_VOICES;
    }
    if ((entry->kind == 0xfd && entry->actions[entry->actionIndex].kind == ACTION_KIND_FLURRY &&
         data_ov041_020cff48.flurryHit != 5 &&
         (CountActiveStageEntries(entry->flags & STAGE_ENTRY_ENEMY) == 1 || data_ov041_020cff48.flurryRound == 2)) ||
        (entry->kind == 0xff && GetEntryAction(entry)->kind == 3 && entry->stateStep == 0xb)) {
        if (target->hp <= 0) {
            target->hp = 0;
        }
    } else {
    if (target->hp <= 0) {
        if (target->flags & STAGE_ENTRY_ENDURE) {
            target->hp = 1;
        } else if (target->checkedHp > 1 && GetEntryAbility(target, 0x40)) {
            target->hp = 1;
        } else {
            target->hp = 0;
            SetEntryState(target, STAGE_ENTRY_OUT);
            result |= HIT_DEFEATED;
            /* the stage's decisive enemy, by the kind its work flags name */
            if (((work->flags & 0x100000) && target->kind == 0xfd) ||
                ((work->flags & 0x200000) && target->kind == 0x16) ||
                ((work->flags & 0x400000) && target->kind == 0x17) ||
                ((work->flags & 0x800000) && target->kind == 0x18) ||
                ((work->flags & 0x1000000) && target->kind == 0x1a) ||
                ((work->flags & 0x2000000) && target->kind == 0x19)) {
                switch (target->kind) {
                case 0x16:
                case 0x18:
                case 0x19:
                case 0x1a:
                case 0xfd:
                    seqArc = GetStageKindSoundArc(target->kind);
                    index = target->downVoice;
                    break;
                case 0x17:
                    seqArc = 0x44;
                    index = 1;
                    break;
                }
                PlayStageSound(seqArc, index, TRUE);
                PlaySoundChecked(0, 0x4e);
                work->flags |= STAGE_WORK_FAST_PANELS;
                work->flags |= STAGE_WORK_WON;
                StartStageFadeOut();
            } else if (target->kind == 0xff && target->statuses[3] == 0) { /* the leader */
                PlayStageSound(target->voiceSeqArc, target->downVoice, TRUE);
                PlayStageSound(0, 0x12, TRUE);
                work->flags |= STAGE_WORK_FAST_PANELS;
                work->flags |= STAGE_WORK_FIELD_OP_DONE;
                StartStageFadeOut();
            }
        }
    }
    if (target->hp >= 1 && GetEntryAbility(target, 0x20)) {
        for (i = 0; i < work->primaryCount; i++) {
            work->entries[i].flags |= STAGE_ENTRY_ENDURE;
        }
    }
    }
    return result;
}
