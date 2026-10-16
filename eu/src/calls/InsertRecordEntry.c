#pragma opt_dead_assignments off
#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    union {
        u16 flags;
        struct {
            u16 active : 1;
            u16 level : 7;
            u16 category : 8;
        };
    };
} RecordEntry;

typedef struct RecordSaveData {
    u8 unknown0000[0x28d8];
    u8 ownedCategoryFlags[0x200];
    u8 unknown2ad8[0x2e00 - 0x2ad8];
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
typedef char RecordFlagsOffset[(u32)&((RecordEntry *)0)->flags == 2 ? 1 : -1];
typedef char OwnedCategoryFlagsOffset[(u32)&((RecordSaveData *)0)->ownedCategoryFlags == 0x28d8 ? 1 : -1];
typedef char RecordsOffset[(u32)&((RecordSaveData *)0)->records == 0x2e00 ? 1 : -1];
typedef char TotalRecordCountOffset[(u32)&((RecordCounterState *)0)->totalCount == 0x100 ? 1 : -1];
typedef char RecordCapacityOffset[(u32)&((RecordCounterState *)0)->capacity == 0x102 ? 1 : -1];
typedef char RecordCounterViewIs260Bytes[sizeof(RecordCounterStorage) == 0x104 ? 1 : -1];

extern RecordSaveData *data_0205fe0c;
extern RecordCounterStorage data_0205fec4;
extern void SetFlagAndBumpCounter(u8 *flag);
extern void func_02028dd8(u16 *destination, const void *source);

/* Mark the category as owned and initialize the first inactive record slot. */
s16 InsertRecordEntry(const RecordEntry *source)
{
    u16 category = source->category;
    RecordSaveData *save = data_0205fe0c;
    u16 *totalCounter = data_0205fec4.words;
    totalCounter += 0x80;
    RecordEntry *entry = save->records;
    u16 *categoryCounter = (u16 *)((u8 *)&data_0205fec4 + category * sizeof(u16));
    RecordEntry *end = entry + 600;

    u8 *ownedFlag = &save->ownedCategoryFlags[(u8)category];
    u16 index = 0;

    SetFlagAndBumpCounter(ownedFlag);
    if (data_0205fec4.fields.totalCount >= data_0205fec4.fields.capacity) {
        return 0;
    }
    do {
        if (!entry->active) {
            func_02028dd8((u16 *)entry, source);
            break;
        }
        ++index;
        ++entry;
    } while (entry < end);
    ++*totalCounter;
    ++*categoryCounter;
    return (s16)index;
}
