#include "nitro/types.h"

typedef struct {
    u8 data[0x40];
} RecordD;

typedef struct {
    u8 pad_00[0x64];
    RecordD *tableD;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

/* Gets a record table D entry. */
RecordD *GetRecordTableDEntry_02052280(s32 index)
{
    RecordManager *manager = g_recordManager_020613d0;

    if (manager == 0) {
        return 0;
    }
    if (manager->tableD == 0) {
        return 0;
    }
    return manager->tableD + index;
}
