#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00;
    u8 level;
    u16 health;
    u8 pad_04[8];
    u16 luck;
} PlayerStats;

typedef struct {
    u8 pad_000[0x1d4];
    PlayerStats *stats;
} PlayerEntry;

typedef struct {
    u8 pad_00[4];
    fx32 gaugePoints;
    fx32 critChance;
    fx32 bonus;
    u8 type;
    u8 element;
    u8 hasBonus;
    u8 pad_13[0x11];
    u16 attr0 : 1;
    u16 attr1 : 1;
    u16 attr2 : 1;
    u16 attr3 : 1;
    u16 attr4 : 1;
    u16 isSpecial : 1;
    u16 attr6 : 1;
    u16 attr7 : 1;
    u16 attr8 : 3;
    u16 noScale : 1;
} HitTarget;

typedef struct {
    s32 id;
    s32 power;
    s32 player;
    VecFx32 start;
    VecFx32 end;
    u32 result;
} PathSegment;

typedef struct {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct {
    fx32 rates[3];
} ScaleTable;

typedef struct {
    VecFx32 position;
    fx32 damage;
    u8 pad_10[8];
    fx32 critDamage;
    fx32 bonus;
    fx32 points;
    u8 element;
    u8 hasBonus;
    u8 pad_26[2];
    u16 unk_0 : 1;
    u16 copyAttr0 : 1;
    u16 unk_2 : 1;
    u16 guarded : 1;
    u16 unk_4 : 2;
    u16 ability3b : 1;
    u16 ability39 : 1;
    u16 unk_8 : 1;
    u16 copyAttr6 : 1;
    u16 unk_10 : 1;
    u16 physical : 1;
    u16 magical : 1;
    u16 copyAttr4 : 1;
    u16 scaled : 1;
    u16 unk_15 : 1;

    u16 power;
    u16 pad_2c;
    u16 player;
    u16 level;
    u16 pad_32;
    VecFx32 start;
    fx32 drain;
    u32 blocked : 1;
    u32 reflected : 1;
} HitInfo;

extern const ScaleTable data_ov021_020b4fd8;

extern PlayerEntry *GetBoundedEntryField_0206db5c(int player);
extern void func_01ff8830(void *dst, int value, u32 size);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern fx32 ComputeAttackDamage_020ac6cc(int player, HitTarget *target);
extern BOOL func_ov001_02075248(int player);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern s32 GetClampedPaletteSlot_02073598(void);
extern int DispatchStageEventArg_020878d4(u32 id, HitInfo *hit);
extern fx32 ScaleValueByPercentField_020a7650(PlayerEntry *obj, s32 value);
extern BOOL AddClampedHealth_020a75ec(PlayerEntry *obj, s16 delta);
extern void func_ov001_0206dfbc(fx32 points);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern void AddSessionCounter_02063a80(int index, int amount);
extern void AwardPartyGaugePoints_0206ded8(int index, int points);

#define CLAMP_SLOT(x) ((x) > 2 ? 2 : ((x) < 0 ? 0 : (x)))

BOOL ApplyHitToTarget_020ac33c(HitTarget *target, PathSegment *segment)
{
    PlayerEntry *entry;
    BOOL critical;
    BOOL canScale;
    PlayerStats *stats;
    ScaleTable scales;
    EventTargetInfo info;
    HitInfo hit;
    u32 result;
    fx32 chance;
    BOOL defeated;
    fx32 cost;
    fx32 points;

    entry = GetBoundedEntryField_0206db5c(segment->player);
    stats = entry->stats;
    result = 0;
    critical = FALSE;
    canScale = TRUE;
    func_01ff8830(&hit, 0, sizeof(HitInfo));
    hit.player = segment->player;
    hit.level = entry->stats->level;
    hit.start = segment->start;
    hit.position = segment->end;
    hit.power = segment->power;
    hit.copyAttr0 = target->attr0;
    hit.guarded = target->attr2;
    hit.copyAttr6 = target->attr6;
    hit.scaled = target->attr7;
    hit.copyAttr4 = target->attr4;
    if (hit.guarded) {
        hit.scaled = 1;
        canScale = FALSE;
    }
    if (target->noScale) {
        canScale = FALSE;
    }
    if (!target->isSpecial) {
        switch (target->type) {
        case 0:
            hit.physical = 1;
            break;
        case 1:
            hit.magical = 1;
            break;
        }
    }
    if (target->isSpecial) {
        if (IsPlayerEntryFlagSet_02050014(segment->player, 0x39)) {
            hit.ability39 = 1;
        }
        if (IsPlayerEntryFlagSet_02050014(segment->player, 0x3b)) {
            hit.ability3b = 1;
        }
    }
    hit.damage = ComputeAttackDamage_020ac6cc(segment->player, target);
    hit.element = target->element;
    hit.critDamage = 0;
    chance = target->critChance;
    if (chance > 0) {
        if (IsPlayerEntryFlagSet_02050014(segment->player, 0x31)) {
            chance = 0x64000;
        } else {
            if (func_ov001_02075248(segment->player) && IsPlayerEntryFlagSet_02050014(segment->player, 0x1f)) {
                chance += FixedPointMultiply12(chance, 0x1000);
            }
            if (IsPlayerEntryFlagSet_02050014(segment->player, 0x32)) {
                chance -= FixedPointMultiply12(chance, 0x600);
            }
        }
        chance += FixedPointMultiply12(chance, stats->luck * 0x52);
        if (random_next_scaled_0202aa04(0x64000) <= chance) {
            hit.critDamage = FixedPointMultiply12(hit.damage, 0x280);
            if (IsPlayerEntryFlagSet_02050014(segment->player, 0x32)) {
                hit.critDamage += FixedPointMultiply12(hit.critDamage, 0x1000);
            }
            critical = TRUE;
        }
    }
    hit.hasBonus = target->hasBonus;
    if (hit.hasBonus) {
        fx32 bonus = target->bonus;
        hit.bonus = bonus + FixedPointMultiply12(bonus, stats->luck * 0x52);
    }
    if (hit.scaled && canScale) {
        scales = data_ov021_020b4fd8;
        hit.damage = FixedPointMultiply12(hit.damage, scales.rates[CLAMP_SLOT(GetClampedPaletteSlot_02073598() - 1)]);
    }
    if (DispatchStageEventArg_020878d4((u16)segment->id, &hit)) {
        defeated = FALSE;
        if (hit.blocked) {
            result |= 1;
        } else if (target->type == 0) {
            if (IsPlayerEntryFlagSet_02050014(segment->player, 0x4f)) {
                cost = ScaleValueByPercentField_020a7650(entry, 0x3200);
                if (cost < 0x1000) {
                    cost = 0x1000;
                }
                if (entry->stats->health <= cost >> 12) {
                    cost = (entry->stats->health - 1) << 12;
                }
                if (cost >> 12 > 0) {
                    AddClampedHealth_020a75ec(entry, -(cost >> 12));
                }
            }
            if (IsPlayerEntryFlagSet_02050014(segment->player, 0x3c)) {
                AddClampedHealth_020a75ec(entry, FixedPointMultiply12(hit.drain, 0x400) >> 12);
            }
        }
        if (hit.reflected) {
            result |= 2;
        }
        if (hit.points > 0) {
            if (IsPlayerEntryFlagSet_02050014(segment->player, 0x4c)) {
                hit.points += hit.points * 0x800 >> 12;
            }
            func_ov001_0206dfbc(hit.points);
        }
        if (GetStageEventTargetInfo_02087960((u16)segment->id, &info) && info.width <= 0) {
            result |= 0x40000000;
            if (GetClampedPaletteSlot_02073598() == 3) {
                AddSessionCounter_02063a80(0x11, 1);
            }
            defeated = TRUE;
        }
        points = target->gaugePoints;
        if (defeated) {
            points = FixedPointMultiply12(points, 0x1800);
        }
        if (!hit.blocked) {
            AwardPartyGaugePoints_0206ded8(segment->player, points >> 12);
        }
    } else {
        result = 0x80000000;
        critical = FALSE;
    }
    segment->result = result;
    return critical;
}
