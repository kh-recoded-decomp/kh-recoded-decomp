#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 attackRate;
    u16 hpRate;
    u16 modifierRate;
    u16 statRate;
    u16 speed;
    u16 unk_0A;
} StatTableEntry;

typedef struct {
    u8 pad_00[0xc];
    StatTableEntry *data;
} FileSection;

typedef struct {
    u8 pad_00[8];
    FileSection *sections;
} StatFile;

typedef struct {
    u8 pad_00[8];
    s32 value;
    u8 pad_0C[0x13];
    u8 levelScaled;
} StatModifier;

typedef struct {
    s32 hp;
    s32 stats[8];
    u8 pad_24[0xc];
    s32 attack;
    u8 pad_34[0xe];
    u8 fixedHp;
} BaseStats;

typedef struct {
    u8 level;
    u8 pad_01[3];
    s32 maxHp;
    s32 hp;
    s32 stats[8];
    fx32 speed;
    s32 attack;
    StatModifier modifiers[8];
} ActorStats;

extern char data_ov001_020a044c[];
extern void func_01ff8830(void *dst, int value, u32 size);
extern StatFile *func_0202c478(const char *path, u32 heapId);
extern void func_ov001_0208efcc(StatFile *file);
extern fx32 FixedPointMultiply12_02006450(fx32 left, fx32 right);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ComputeLevelStats_0209d29c(ActorStats *out, BaseStats *base, StatModifier *modifiers, u8 level, s16 attackScale, fx32 hpScale)
{
    StatFile *file;
    StatTableEntry *table;
    StatTableEntry *entry;
    u16 i;
    fx32 bonus;

    func_01ff8830(out, 0, sizeof(ActorStats));
    file = func_0202c478(data_ov001_020a044c, 0xb);
    if (file == NULL) {
        return;
    }
    func_ov001_0208efcc(file);
    table = file->sections->data;
    out->level = level;
    if (base->fixedHp) {
        out->hp = base->hp;
    } else {
        out->hp = base->hp * table[level].hpRate;
    }
    base->hp = out->maxHp = out->hp = FixedPointMultiply12_02006450(out->hp, hpScale);
    out->maxHp = out->hp;
    entry = &table[level];
    out->speed = entry->speed << 12;
    out->attack = (base->attack * table[level].attackRate) >> 12;
    out->attack = (out->attack * attackScale) >> 12;
    for (i = 0; i < 8; i++) {
        out->stats[i] = base->stats[i] * table[level].statRate;
    }
    if (out->hp <= 0) {
        out->maxHp = out->hp = 1;
    }
    for (i = 0; i < 8; i++) {
        bonus = 0;
        if (modifiers[i].levelScaled) {
            bonus = entry->modifierRate << 6;
            bonus = FixedPointMultiply12_02006450(bonus, bonus);
            bonus = FixedPointMultiply12_02006450(bonus + 0x10000, 0x100) - 0x1000;
        }
        out->modifiers[i] = modifiers[i];
        out->modifiers[i].value = entry->modifierRate * (bonus + modifiers[i].value);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}
