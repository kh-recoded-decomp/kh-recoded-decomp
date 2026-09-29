#include "nitro/types.h"

typedef struct {
    u8 data[0x124];
} StageObjectRecord;

typedef struct {
    u8 pad_00[0x214];
    StageObjectRecord records[1];
} StageManager;

extern StageManager *g_stageManager_020a0508;

StageObjectRecord *GetStageObjectRecord_0209c0a0(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (g_stageManager_020a0508 != 0) {
        return &g_stageManager_020a0508->records[index];
    }
    return 0;
}
