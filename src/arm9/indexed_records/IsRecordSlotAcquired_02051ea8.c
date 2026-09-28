#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 refCounts[1];
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

/* Checks whether a record slot is in use. */
BOOL IsRecordSlotAcquired_02051ea8(s32 slot)
{
    RecordManager *manager = g_recordManager_020613d0;

    if (manager == 0 || manager->refCounts[slot] == 0) {
        return FALSE;
    }
    return TRUE;
}
