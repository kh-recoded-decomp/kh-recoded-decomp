#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    s16 *shortTable;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

/* Reads a short table entry, or default. */
s32 GetShortTableValueOrDefault_020521dc(s32 index)
{
    RecordManager *manager = g_recordManager_020613d0;
    s32 value;

    value = manager->shortTable[index + 1];
    if (value < 0) {
        value = 0x28;
    }
    return value;
}
