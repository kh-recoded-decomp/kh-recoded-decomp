#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} SmallRecord;

typedef struct {
    u8 count;
    u8 pad_01[3];
    SmallRecord *entries;
} SmallRecordTable;

typedef struct {
    u8 pad_00[0x18df8];
    SmallRecordTable *table;
} OverlayState;

extern OverlayState *g_ov001State_020a0508;

SmallRecord *GetSmallTableEntry_0209c340(int index)
{
    SmallRecordTable *table;

    if (g_ov001State_020a0508 == 0) {
        return 0;
    }
    table = g_ov001State_020a0508->table;
    if (table == 0) {
        return 0;
    }
    if (index < table->count) {
        return table->entries + index;
    }
    return 0;
}
