#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole count as fx32, rounded the way the converter of the original tools did. */
#define INT_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))
#define F32_TO_FX32(x) ((fx32)((x) > 0 ? 4096.0f * (x) + 0.5f : 4096.0f * (x) - 0.5f))

#define STAGE_HIT_MAX (9999 * FX32_ONE)

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAbility(StageEntry *entry, int ability);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern u32 GetPlayerEntryCount(int player, u32 id);

/*
 * Fills an entry's hit for its action: the amount is its strength (magic for kind 12 actions, with the player's
 * element bonus) times the action's power, boosted by abilities 1 and 2; accuracy and the critical chance come
 * from the action (critical doubled by ability 16) and the effects to show from its hit effects. Some kinds
 * set a fixed amount or none of accuracy and critical; a kind 0 action is weakened unless the stage says not.
 */
void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit)
{
    StageEntryAction *action;
    fx32 power;
    fx32 strengthScale;
    f32 bonus;
    fx32 magicScale;
    f32 criticalScale;
    StageWork *work;

    work = gMovieContextState->stageWork;
    action = GetEntryAction(entry);
    strengthScale = FX32_ONE;
    magicScale = FX32_ONE;
    criticalScale = 1.0f;
    if (GetEntryAbility(entry, 1)) {
        strengthScale = 0x1280;
    }
    if (GetEntryAbility(entry, 2)) {
        magicScale = 0x1280;
    }
    if (GetEntryAbility(entry, 0x10)) {
        criticalScale = 2.0f;
    }
    if (action->kind == 0xc) {
        power = FX_Mul(INT_TO_FX32(entry->magic), magicScale);
        if (entry->kind == 0xff && IsPlayerEntryFlagSet(0, action->element - 1)) {
            bonus = (100.0f + GetPlayerEntryCount(0, action->element - 1)) / 100.0f;
            power = FX_Mul(power, F32_TO_FX32(bonus));
        }
    } else {
        power = FX_Mul(INT_TO_FX32(entry->strength), strengthScale);
    }
    hit->amount = FX_Mul(power, action->power);
    hit->accuracy = action->accuracy;
    hit->critical = action->critical;
    hit->source = entry;
    hit->unk0a = entry->unkf0 >> FX32_SHIFT;
    hit->element = action->element;
    hit->effect.category = action->hitEffectCategory;
    hit->effect.index = action->hitEffectIndex;
    hit->effect.animation = action->hitEffectAnimation;
    hit->altEffect.category = action->altEffectCategory;
    hit->altEffect.index = action->altEffectIndex;
    hit->altEffect.animation = action->altEffectAnimation;
    hit->critical = hit->critical * criticalScale;
    switch (action->kind) {
    case 0xc:
        switch (action->effect) {
        case 0xb7:
            hit->amount = 30 * FX32_ONE;
            hit->unk0d = 2;
            break;
        case 0xb8:
            hit->amount = 50 * FX32_ONE;
            hit->unk0d = 2;
            break;
        case 0xeb:
            hit->unk0d = 1;
            break;
        default:
            hit->unk0d = 0;
            break;
        }
        break;
    case 8:
        hit->unk0d = 2;
        hit->amount = F32_TO_FX32((f32)(work->entries[entry->mainTarget].maxHp / 5));
        break;
    default:
        hit->unk0d = 0;
        break;
    }
    switch (action->kind) {
    case 5:
        if (entry->flags & STAGE_ENTRY_ENEMY) {
            break;
        }
    case 3:
    case 4:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
        hit->accuracy = 500;
        hit->critical = 0;
        break;
    }
    if (action->kind == 0 && data_ov041_020cff48.unk02 != 1) {
        hit->amount = FX_Mul(hit->amount, 0xe66);
    }
    hit->amount = hit->amount > STAGE_HIT_MAX ? STAGE_HIT_MAX : (hit->amount < 0 ? 0 : hit->amount);
}
