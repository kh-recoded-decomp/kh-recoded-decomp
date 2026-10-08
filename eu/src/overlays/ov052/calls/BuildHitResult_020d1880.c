#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 ability;
    int element;
} AbilityElement;

typedef struct {
    AbilityElement entries[5];
} AbilityElementTable;

typedef struct {
    int damage;
    int stun;
    int knockback;
    int duration;
    u8 hitType;
    u8 reaction;
    u8 element;
    u8 pad_13[0x11];
    u16 isPrimary : 1;
    u16 isLinked : 1;
    u16 isCritical : 1;
    u16 reserved3 : 1;
    u16 isMirrored : 1;
    u16 isForced : 1;
    u16 isPiercing : 1;
    u16 isOwned : 1;
    u16 reserved8 : 1;
    u16 isGuarded : 1;
    u16 isFinisher : 1;
} HitResult;

typedef struct {
    u8 pad_00[8];
    fx32 scale;
    u8 pad_0c[0xc];
    u16 reserved0 : 4;
    u16 primary : 1;
    u16 linked : 1;
    u16 critical : 1;
    u16 mirrored : 1;
    u16 forced : 1;
    u16 piercing : 1;
    u16 owned : 1;
    u16 guarded : 1;
    u16 finisher : 1;
    u8 hitType;
    u8 reaction;
    s8 bonusPercent;
    s8 bonusFlags;
} SlotEntry;

typedef struct {
    int damage;
    int stun;
    int knockback;
    u8 pad_0c[0x10];
    int duration;
    u8 element;
} AttackData;

typedef struct {
    u8 pad_0000[0x9b4];
    u8 player;
} Actor;

extern const AbilityElementTable data_ov052_020d2134;
extern int FX_Mul(int left, int right);
extern int _s32_div_f(int value, int scale);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);

void BuildHitResult_020d1880(HitResult *out, Actor *actor, AttackData *attack, SlotEntry *entry)
{
    AbilityElementTable table;
    int damage = attack->damage;
    int i;

    out->damage = damage;
    if (!entry->forced) {
        out->damage = out->damage + _s32_div_f(FX_Mul(entry->scale, damage * entry->bonusPercent), 100);
    } else if (entry->critical) {
        out->damage = FX_Mul(damage, 0x1333);
    }
    out->hitType = entry->hitType;
    out->reaction = entry->reaction;
    out->element = attack->element;
    out->duration = attack->duration;
    if (entry->forced && out->element == 0) {
        table = data_ov052_020d2134;
        for (i = 0; i < 5; i++) {
            if (IsPlayerEntryFlagSet(actor->player, table.entries[i].ability)) {
                out->element = table.entries[i].element;
                out->duration = 0x32000;
                break;
            }
        }
    }
    out->stun = attack->stun;
    if (entry->bonusFlags & 1) {
        out->stun += _s32_div_f(attack->stun * entry->bonusPercent, 100);
    }
    out->knockback = attack->knockback;
    out->isPrimary = entry->primary;
    out->isForced = entry->forced;
    out->isCritical = entry->critical;
    out->isMirrored = entry->mirrored;
    out->isGuarded = entry->guarded;
    out->isPiercing = entry->piercing;
    out->isLinked = entry->linked;
    out->isOwned = entry->owned;
    out->isFinisher = entry->finisher;
}
