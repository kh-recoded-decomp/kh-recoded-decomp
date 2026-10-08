#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc];
    u16 value0c;
    u8 pad_0e[0x14];
    u8 colors[6];
    u8 pad_28[0x10];
} SlotItem;

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
    s16 current;
    s16 limit;
    s16 currentDisplay;
    s16 currentTarget;
    u16 attack;
    u16 defense;
    u8 pad_e8[2];
    u16 value28;
    u16 value2a;
    u8 pad_ee[2];
    u32 value0c;
    u32 value10;
    u16 value2c;
    u16 lastSlot;
    u8 pad_fc[2];
    u8 value3f;
    u8 value40;
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
    u16 value4b0;
    u8 abilities;
    u8 pad_4b3;
} SceneEntry;

typedef struct {
    u8 pad_000[0x14];
    SceneEntry *entries;
    u8 pad_018[0x22fc];
    u8 *file;
} Work;

typedef struct {
    u32 id : 18;
    u32 extra : 14;
} AbilityEntry;

typedef struct {
    u8 pad_000[6];
    u16 attack;
    u16 value4b0;
    u16 defense;
    u8 pad_00c[4];
    u8 colorBase;
    u8 pad_011[0x12b];
    AbilityEntry *abilityList;
    u8 abilityCount;
} SelectionRecord;

#define ROUND_FX32(x) ((fx32)(((x) > 0) ? (0.5f + (float)((x) << 12)) : ((float)((x) << 12) - 0.5f)))

extern int data_ov035_020bc4e0;
extern u32 data_ov041_020cf4ac[];
extern u32 data_ov041_020cf4f4[];
extern u32 data_ov041_020cf4a0[];
extern u32 data_ov041_020cf488[];
extern VecFx32 data_ov041_020cf560[];
extern u8 data_ov041_020cf500[][5];
extern u32 data_ov041_020cf4b8[];
extern u8 data_ov041_020cf474[];
extern u8 data_ov041_020cf47c[];
extern u8 data_ov041_020cf45c[];
extern u8 data_ov041_020cf468[];
extern u8 data_ov041_020cf464[];
extern u8 data_ov041_020cf46c[];
extern u8 data_ov041_020cf478[];
extern u8 data_ov041_020cf470[];
extern u8 data_ov041_020cf460[];
extern u16 data_ov041_020cf480[];
extern u8 data_ov041_020cf510[][6];
extern u8 data_ov041_020cf524[][6];
extern fx32 data_ov041_020cf4dc[];
extern fx32 data_ov041_020cf4e8[];
extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern int GetMovieCounterLimit_020bafc4(int which);
extern int LoadMovieCounter_020bb054(int which);
extern int FixedPointMultiply12(int left, int right);
extern void QueueSoundCommandForArc_0204d670(u32 seqArcNo);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(int value, void *dst, u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);

void InitSpecialStageEntry_020c0ef0(u8 index, int kind) {
    SceneEntry *entry;
    int row;
    SelectionRecord *record;
    Work *work;
    SceneEntry *entries;
    int i;

    work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    entries = work->entries;
    entry = &entries[index];
    record = GetOverlaySelectionRecord(0);
    row = 0xff - kind;
    entries[index].kind = kind;
    entry->index = index;
    entry->state04 = 0;
    entry->state05 = 0;
    entry->state06 = 0;
    entry->active = 0;
    entry->target = -1;
    entry->marker = 0xff;
    entry->owner = index;
    entry->slots[0] = 0;
    entry->slots[2] = 2;
    entry->slots[1] = 1;
    entry->slots[3] = 3;
    entry->slots[4] = 4;
    entry->limit = GetMovieCounterLimit_020bafc4(row);
    entry->current = LoadMovieCounter_020bb054(row);
    if (entry->current < 0) {
        entry->current = 1;
    }
    if (entry->current > entry->limit) {
        entry->current = entry->limit;
    }
    entry->currentDisplay = entry->current;
    entry->currentTarget = entry->current;
    entry->attack = record->attack;
    entry->defense = record->defense;
    entry->value4b0 = record->value4b0;
    entry->value28 = data_ov041_020cf4ac[row];
    entry->value2a = data_ov041_020cf4f4[row];
    entry->value24 = data_ov041_020cf4a0[row];
    entry->value14 = data_ov041_020cf488[row];
    entry->position = data_ov041_020cf560[row];
    entry->slots[0] = data_ov041_020cf500[row][0];
    entry->slots[1] = data_ov041_020cf500[row][1];
    entry->slots[2] = data_ov041_020cf500[row][2];
    entry->slots[3] = data_ov041_020cf500[row][3];
    entry->slots[4] = data_ov041_020cf500[row][4];
    entry->value0c = data_ov041_020cf4b8[row];
    entry->value10 = 0;
    entry->value2c = 0;
    entry->lastSlot = 0;
    entry->value3f = 0;
    entry->value40 = 0;
    entry->stats[0] = data_ov041_020cf474[row];
    entry->stats[1] = data_ov041_020cf47c[row];
    entry->stats[2] = data_ov041_020cf45c[row];
    entry->stats[3] = data_ov041_020cf468[row];
    entry->stats[4] = data_ov041_020cf464[row];
    entry->stats[5] = data_ov041_020cf46c[row];
    entry->stats[6] = data_ov041_020cf478[row];
    entry->stats[7] = data_ov041_020cf470[row];
    entry->flagCount = 0;
    for (i = 0; i < 11; i++) {
        entry->flags[i] = 0;
    }
    entry->itemCount = data_ov041_020cf460[row];
    entry->items = NNSi_FndAllocFromDefaultHeap_0202a178(entry->itemCount * sizeof(SlotItem));
    func_01ff8740(0, entry->items, entry->itemCount * sizeof(SlotItem));
    switch (kind) {
    case 0xff:
        func_01ff878c(work->file + 0x4, &entry->items[0], sizeof(SlotItem));
        func_01ff878c(work->file + 0x3c, &entry->items[1], sizeof(SlotItem));
        break;
    case 0xfe:
        func_01ff878c(work->file + 0x74, &entry->items[0], sizeof(SlotItem));
        func_01ff878c(work->file + 0xac, &entry->items[1], sizeof(SlotItem));
        break;
    case 0xfd:
        func_01ff878c(work->file + 0xe4, &entry->items[0], sizeof(SlotItem));
        func_01ff878c(work->file + 0x11c, &entry->items[1], sizeof(SlotItem));
        break;
    }
    entry->items[0].value0c = 1000;
    entry->items[1].value0c = data_ov041_020cf480[row];
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
    entry->attack = FixedPointMultiply12(data_ov041_020cf4dc[row], ROUND_FX32(entry->attack)) >> 12;
    entry->defense = FixedPointMultiply12(data_ov041_020cf4e8[row], ROUND_FX32(entry->defense)) >> 12;
    if (kind == 0xff) {
        entry->items[0].colors[1] = GetOverlaySelectionRecord(0)->colorBase + 0x33;
        entry->items[1].colors[1] = GetOverlaySelectionRecord(0)->colorBase + 0x33;
    }
    switch (kind) {
    case 0xff:
        entry->active &= ~1;
        entry->row = 5;
        entry->column = 1;
        entry->cell = 1;
        for (i = 0; i < record->abilityCount; i++) {
            switch (record->abilityList[i].id) {
            case 0x1b:
                entry->abilities |= 0x1;
                break;
            case 0x1c:
                entry->abilities |= 0x2;
                break;
            case 0x1d:
                entry->abilities |= 0x4;
                break;
            case 0x1e:
                entry->abilities |= 0x8;
                break;
            case 0x1f:
                entry->abilities |= 0x10;
                break;
            case 0x22:
                entry->abilities |= 0x20;
                break;
            case 0x23:
                entry->abilities |= 0x40;
                break;
            }
        }
        break;
    case 0xfe:
        entry->active &= ~1;
        entry->row = 5;
        entry->column = 0;
        entry->cell = 0;
        break;
    case 0xfd:
        entry->active &= ~1;
        entry->row = 5;
        entry->column = 2;
        entry->cell = 2;
        break;
    }
    switch (kind) {
    case 0xff:
        QueueSoundCommandForArc_0204d670(0x30);
        QueueSoundCommandForArc_0204d670(0x35);
        entry->soundId = 0x30;
        entry->order[0] = 5;
        entry->order[1] = 6;
        entry->order[2] = 0xff;
        entry->order[3] = 0xff;
        entry->order[4] = 0xff;
        break;
    case 0xfe:
        QueueSoundCommandForArc_0204d670(0x42);
        entry->soundId = 0x42;
        entry->order[0] = 3;
        entry->order[1] = 4;
        entry->order[2] = 0xff;
        entry->order[3] = 0xff;
        entry->order[4] = 4;
        break;
    case 0xfd:
        QueueSoundCommandForArc_0204d670(0x43);
        entry->soundId = 0x43;
        entry->order[0] = 3;
        entry->order[1] = 4;
        entry->order[2] = 0xff;
        entry->order[3] = 0xff;
        entry->order[4] = 4;
        break;
    }
}
