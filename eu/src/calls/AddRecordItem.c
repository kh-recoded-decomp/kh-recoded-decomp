#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct RecordSaveData {
    u8 unknown0000[0x28d8];
    u8 itemCounts[0x390];
    u8 extraSlotCount;
    u8 unknown2c69[0x2e00 - 0x2c69];
    RecordEntry records[600];
} RecordSaveData;

typedef struct RecordCounterState {
    u16 categoryCounts[0x80];
    u16 totalCount;
    u16 capacity;
} RecordCounterState;

typedef union RecordCounterStorage {
    RecordCounterState fields;
    u16 words[0x82];
} RecordCounterStorage;

typedef char RecordEntryIsFourBytes[sizeof(RecordEntry) == 4 ? 1 : -1];
typedef char RecordItemsOffset[(u32)&((RecordSaveData *)0)->itemCounts == 0x28d8 ? 1 : -1];
typedef char RecordsOffset[(u32)&((RecordSaveData *)0)->records == 0x2e00 ? 1 : -1];
typedef char TotalRecordCountOffset[(u32)&((RecordCounterState *)0)->totalCount == 0x100 ? 1 : -1];
typedef char RecordCapacityOffset[(u32)&((RecordCounterState *)0)->capacity == 0x102 ? 1 : -1];
typedef char RecordCounterViewIs260Bytes[sizeof(RecordCounterStorage) == 0x104 ? 1 : -1];

extern RecordSaveData *data_0205fe0c;
extern RecordCounterStorage data_0205fec4;
extern void SetFlagAndBumpCounter(u8 *flag);
extern void func_02028dd8(u16 *destination, const void *source);

/* Add a primary record or increment a secondary item stack, returning its count. */
int AddRecordItem(int category, const RecordEntry *source)
{
    RecordSaveData *save = data_0205fe0c;
    u8 *itemCounts = save->itemCounts;
    u8 *counter = &itemCounts[category];

    if (category >= 0 && category <= 0x7f) {
        u8 recordCategory = (u8)category;
        u32 categoryByteOffset = recordCategory * sizeof(u16);
        RecordEntry *entry = save->records;
        u16 *counts = data_0205fec4.words;
        RecordEntry *end = entry + 600;

        SetFlagAndBumpCounter(counter);
        if (data_0205fec4.fields.totalCount >= data_0205fec4.fields.capacity) {
            return 0;
        }
        do {
            if (!entry->active) {
                func_02028dd8((u16 *)entry, source);
                entry->category = recordCategory;
                break;
            }
            ++entry;
        } while (entry < end);
        ++counts[0x80];
        u16 *categoryCounter = (u16 *)((u8 *)counts + categoryByteOffset);
        ++*categoryCounter;
        return *categoryCounter;
    }
    if (*counter >= 99) {
        return 0;
    }
    ++*counter;
    return *counter;
}
