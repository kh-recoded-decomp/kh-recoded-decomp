#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 unk_00_2 : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SaveFlags {
    u8 low : 4;
    u8 high : 4;
} SaveFlags;

typedef struct StarterRecords {
    int categories[2];
    RecordEntry entries[2];
} StarterRecords;

typedef struct SlotRef {
    u16 recordId;
    u16 pad_02;
} SlotRef;

typedef struct SaveSlots {
    u8 pad_0000[0x2d84];
    SlotRef slots[2];
} SaveSlots;

extern u8 *data_0205fe0c;
extern s16 func_02029300(const RecordEntry *source);
extern void SetGlobalPackedBit(int bitIndex);
extern void SetFlagAndBumpCounter(u8 *flag);

void GrantStarterRecordPair(int firstCategory, int secondCategory)
{
    StarterRecords starters;
    int i;

    starters.categories[0] = firstCategory;
    starters.categories[1] = secondCategory;
    for (i = 0; i < 2; i++) {
        RecordEntry *entry = &starters.entries[i];
        int category;

        entry->active = 1;
        entry->level = 0;
        entry->kind = 0;
        entry->unk_00_2 = 0;
        entry->levelProgress = 0;
        category = starters.categories[i];
        entry->category = (u8)category;
        ((SaveSlots *)data_0205fe0c)->slots[i].recordId =
            (u16)func_02029300(entry) + 0x200;
        category = starters.categories[i];
        SetGlobalPackedBit(category);
        SetFlagAndBumpCounter(data_0205fe0c + 0x28d8 + category);
    }
    ((SaveFlags *)(data_0205fe0c + 0x28d7))->low = 0;
    ((SaveFlags *)(data_0205fe0c + 0x28d7))->high = 0;
}
