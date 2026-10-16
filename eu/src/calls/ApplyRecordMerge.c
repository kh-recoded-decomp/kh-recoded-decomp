#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct RecordMergeResult {
    u16 firstIndex;
    u16 secondIndex;
    RecordEntry result;
} RecordMergeResult;

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

typedef char RecordEntryIsFourBytes[sizeof(RecordEntry) == 4 ? 1 : -1];
typedef char RecordMergeIsEightBytes[sizeof(RecordMergeResult) == 8 ? 1 : -1];
typedef char MergedEntryOffset[(u32)&((RecordMergeResult *)0)->result == 4 ? 1 : -1];
typedef char RecordItemsOffset[(u32)&((RecordSaveData *)0)->itemCounts == 0x28d8 ? 1 : -1];
typedef char RecordsOffset[(u32)&((RecordSaveData *)0)->records == 0x2e00 ? 1 : -1];
typedef char TotalRecordCountOffset[(u32)&((RecordCounterState *)0)->totalCount == 0x100 ? 1 : -1];
typedef char RecordCapacityOffset[(u32)&((RecordCounterState *)0)->capacity == 0x102 ? 1 : -1];
typedef char RecordCounterStateIs260Bytes[sizeof(RecordCounterState) == 0x104 ? 1 : -1];

extern RecordSaveData *data_0205fe0c;
extern RecordCounterState data_0205fec4;
extern void func_02028dd8(u16 *destination, const void *source);
extern void SetFlagAndBumpCounter(u8 *flag);

/* Replace the first input with the merged record and release the second input. */
int ApplyRecordMerge(const RecordMergeResult *merge)
{
    RecordEntry *records = data_0205fe0c->records;
    u16 *counts = data_0205fec4.categoryCounts;
    u32 firstByteOffset = merge->firstIndex * sizeof(RecordEntry);
    RecordEntry *first = (RecordEntry *)((u8 *)records + firstByteOffset);

    --counts[first->category];
    func_02028dd8((u16 *)first, &merge->result);
    first->levelProgress = merge->result.levelProgress;

    ++counts[merge->result.category];
    u16 newCategory = merge->result.category;
    newCategory = (u8)newCategory;
    SetFlagAndBumpCounter(&data_0205fe0c->itemCounts[newCategory]);

    RecordEntry *second = &data_0205fe0c->records[merge->secondIndex];
    --counts[second->category];
    --data_0205fec4.totalCount;
    second->active = 0;
    return merge->firstIndex;
}
