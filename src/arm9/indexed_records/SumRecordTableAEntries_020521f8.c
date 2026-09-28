#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    u16 *tableA;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

/* Sums record table A entries. */
u16 SumRecordTableAEntries_020521f8(int count)
{
    RecordManager *manager = g_recordManager_020613d0;
    int i;
    u16 sum = 0;

    for (i = 0; i < count; i++) {
        sum = sum + manager->tableA[i];
    }
    return sum;
}
