#include "nitro/types.h"

typedef struct {
    u32 count;
    u32 offset[0];
} NNSSndArcOffsetTable;

extern u8 data_02053118[];

inline void *GetPtrOrNull(void *base, u32 offset)
{
    if (offset == 0) return NULL;
    return (u8 *)base + offset;
}

void *GetOffsetTableEntryOrDefault_0201ef40(const NNSSndArcOffsetTable *table, int index, void *base)
{
    u32 offset;

    if (index < 0) return data_02053118;
    if ((u32)index >= table->count) return data_02053118;

    offset = table->offset[index];
    if (offset == 0) return data_02053118;

    return GetPtrOrNull(base, offset);
}
