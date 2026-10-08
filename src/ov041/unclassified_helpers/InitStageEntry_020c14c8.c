#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[8];
    u32 value08;
    u16 value0c;
    u16 value0e;
    u16 value10;
    u8 pad_12[6];
    u16 value18;
    u8 pad_1a[8];
    u8 colors[6];
    u8 pad_28[0x10];
} SlotItem;

typedef struct {
    fx32 hp;
    fx32 attack;
    fx32 defense;
    u32 value0c;
    u32 value10;
    u32 value14;
    VecFx32 position;
    u32 value24;
    u16 value28;
    u16 value2a;
    u16 value2c;
    u8 pad_2e[2];
    u8 value30;
    u8 value31;
    u8 stats[8];
    s8 slots[4];
    s8 value3e;
    s8 value3f;
    s8 value40;
    s8 itemCount;
    SlotItem *items;
} MemberData;

typedef struct {
    u8 kind;
    u8 index;
    u8 row;
    u8 column;
    u8 state04;
    u8 state05;
    u8 state06;
    u8 pad_07;
    u32 active;
    u8 pad_0c[4];
    s8 target;
    u8 owner;
    u8 pad_12[0xca];
    s16 maxHp;
    s16 hp;
    s16 hpDisplay;
    s16 hpTarget;
    s16 attack;
    s16 defense;
    u8 pad_e8[2];
    u16 value28;
    u16 value2a;
    u8 pad_ee[2];
    u32 value0c;
    u32 value10;
    u16 value2c;
    u16 lastSlot;
    u8 value30;
    u8 value31;
    s8 value3f;
    s8 value40;
    u8 stats[8];
    s8 itemCount;
    u8 pad_109[3];
    SlotItem *items;
    u8 flags[11];
    u8 flagCount;
    u8 pad_11c[8];
    u8 marker;
    u8 cell;
    u8 pad_126[2];
    u32 value24;
    u32 value14;
    VecFx32 position;
    u8 slots[5];
    u8 order[5];
    u8 pad_146[0x366];
    u32 soundId;
    u8 pad_4b0[4];
} SceneEntry;

typedef struct {
    u8 pad_000[8];
    u32 flags;
    u8 pad_00c[8];
    SceneEntry *entries;
    u8 pad_018[0x22fc];
    u8 *file;
} Work;

typedef struct {
    u8 pad_00[10];
    u8 slots[5];
} DefaultSlots;

extern int data_ov035_020bc4e0;
extern u8 data_ov041_020cf510[][6];
extern u8 data_ov041_020cf524[][6];
extern DefaultSlots data_ov041_020cf500;
extern u8 GetStageKindMusicId_020bce20(int stageKind);
extern int GetStageKindSoundId_020bcd70(int stageKind);
extern int ArmObject_0205116c(void);
extern int FixedPointMultiply12(int left, int right);
extern void QueueSoundCommandForArc_0204d670(u32 seqArcNo);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(int value, void *dst, u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);

void InitStageEntry_020c14c8(u8 index, const MemberData *member, u8 position) {
    Work *work;
    SceneEntry *entry;
    int i;
    int hp;
    int row;
    SlotItem *source;

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    entry = &work->entries[index];
    entry->kind = member->value3e;
    entry->index = index;
    entry->state04 = 0;
    entry->state05 = 0;
    entry->state06 = 0;
    entry->active = 1;
    entry->marker = 0xff;
    entry->target = -1;
    entry->owner = index;
    for (i = 0; i < 4; i++) {
        entry->slots[i] = member->slots[i];
    }
    entry->slots[3] = 0xff;
    for (i = 0; i < 5; i++) {
        entry->order[i] = i;
    }
    entry->order[4] = GetStageKindMusicId_020bce20(entry->kind);
    if (work->flags & 0x20) {
        hp = member->hp;
    } else {
        hp = FixedPointMultiply12(member->hp, ArmObject_0205116c());
    }
    entry->hp = hp >> 12;
    if (entry->hp < 1) {
        entry->hp = 1;
    }
    entry->maxHp = entry->hp;
    entry->hpDisplay = entry->maxHp;
    entry->hpTarget = entry->maxHp;
    entry->attack = member->attack >> 12;
    entry->defense = member->defense >> 12;
    entry->value28 = member->value28;
    entry->value2a = member->value2a;
    entry->value24 = member->value24;
    entry->value14 = member->value14;
    entry->position = member->position;
    entry->value0c = member->value0c;
    entry->value10 = member->value10;
    entry->value2c = member->value2c;
    entry->lastSlot = entry->slots[3];
    entry->value31 = member->value31;
    entry->value30 = member->value30;
    entry->value3f = member->value3f;
    entry->value40 = member->value40;
    entry->stats[0] = member->stats[0];
    entry->stats[1] = member->stats[1];
    entry->stats[2] = member->stats[2];
    entry->stats[3] = member->stats[3];
    entry->stats[4] = member->stats[4];
    entry->stats[5] = member->stats[5];
    entry->stats[6] = member->stats[6];
    entry->stats[7] = member->stats[7];
    entry->flagCount = 0;
    for (i = 0; i < 11; i++) {
        entry->flags[i] = 0;
    }
    entry->soundId = GetStageKindSoundId_020bcd70(entry->kind);
    QueueSoundCommandForArc_0204d670(entry->soundId);
    if (entry->kind == 0x17) {
        QueueSoundCommandForArc_0204d670(0x44);
    }
    entry->itemCount = member->itemCount;
    entry->items = NNSi_FndAllocFromDefaultHeap_0202a178(entry->itemCount * sizeof(SlotItem));
    func_01ff8740(0, entry->items, entry->itemCount * sizeof(SlotItem));
    for (i = 0; i < entry->itemCount; i++) {
        entry->items[i] = member->items[i];
    }
    if (entry->kind == 0xfd) {
        row = 0xff - entry->kind;
        func_01ff878c(work->file + 0xe4, &entry->items[0], sizeof(SlotItem));
        func_01ff878c(work->file + 0x11c, &entry->items[1], sizeof(SlotItem));
        source = member->items;
        entry->items[0].value0c = source[0].value0c;
        entry->items[1].value0c = source[1].value0c;
        entry->items[0].value08 = source[0].value08;
        entry->items[1].value08 = source[1].value08;
        entry->items[0].value0e = source[0].value0e;
        entry->items[1].value0e = source[1].value0e;
        entry->items[0].value10 = source[0].value10;
        entry->items[1].value10 = source[1].value10;
        entry->items[0].value18 = source[0].value18;
        entry->items[1].value18 = source[1].value18;
        entry->items[0].colors[0] = data_ov041_020cf510[row][0];
        entry->items[0].colors[1] = data_ov041_020cf510[row][1];
        entry->items[0].colors[2] = data_ov041_020cf510[row][2];
        entry->items[0].colors[3] = data_ov041_020cf510[row][3];
        entry->items[0].colors[4] = data_ov041_020cf510[row][4];
        entry->items[0].colors[5] = data_ov041_020cf510[row][5];
        entry->items[1].colors[0] = data_ov041_020cf524[row][0];
        entry->items[1].colors[1] = data_ov041_020cf524[row][1];
        entry->items[1].colors[2] = data_ov041_020cf524[row][2];
        entry->items[1].colors[3] = data_ov041_020cf524[row][3];
        entry->items[1].colors[4] = data_ov041_020cf524[row][4];
        entry->items[1].colors[5] = data_ov041_020cf524[row][5];
        for (i = 0; i < 5; i++) {
            entry->slots[i] = data_ov041_020cf500.slots[i];
        }
        entry->order[0] = 3;
        entry->order[1] = 4;
        entry->order[2] = 0xff;
        entry->order[3] = 0xff;
        entry->order[4] = 4;
    }
    entry->row = 2 - position / 3;
    entry->column = position % 3;
    entry->cell = position + 3;
}
