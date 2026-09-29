#include "nitro/types.h"

typedef struct StageEntry {
    u8 pad_00[0x1c];
    u32 param;
} StageEntry;

typedef struct StageManager {
    u8 pad_00000[0x18a94];
    StageEntry entries[1];
} StageManager;

extern StageManager *g_stageManager_020a0508;

u32 GetStageEntryParam_02099218(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (g_stageManager_020a0508 != NULL) {
        return g_stageManager_020a0508->entries[index].param;
    }
    return 0;
}
