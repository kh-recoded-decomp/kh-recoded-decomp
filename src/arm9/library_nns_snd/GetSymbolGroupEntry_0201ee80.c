#include "nitro/types.h"

typedef struct {
    u32 count;
    struct {
        u32 unused;
        u32 offset;
    } entry[0];
} EntryTable;

typedef struct {
    u32 count;
    u32 offset[0];
} OffsetTable;

typedef struct {
    u8 pad_00[0x94];
    u8 *symbolData;
} SndArcHandle;

extern SndArcHandle *data_0205e2e4;
extern u8 data_02053118[];
extern void *GetOffsetTableEntryOrDefault_0201ef40(const OffsetTable *table, int index, void *base);

inline void *GetPtrOrNull(void *base, u32 offset)
{
    if (offset == 0) return NULL;
    return (u8 *)base + offset;
}

void *GetSymbolGroupEntry_0201ee80(int groupNo, int index)
{
    u8 *base;
    EntryTable *table;
    void *ptr;

    base = data_0205e2e4->symbolData;
    if (base == NULL) return data_02053118;

    table = (EntryTable *)GetPtrOrNull(base, *(u32 *)(base + 0xc));
    if (table == NULL) return data_02053118;

    if (groupNo < 0) return data_02053118;
    if ((u32)groupNo >= table->count) return data_02053118;

    ptr = GetPtrOrNull(base, table->entry[groupNo].offset);
    if (ptr == NULL) return data_02053118;

    return GetOffsetTableEntryOrDefault_0201ef40((OffsetTable *)ptr, index, base);
}
