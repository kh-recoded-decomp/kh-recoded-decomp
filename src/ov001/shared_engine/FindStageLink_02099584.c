#include "nitro/types.h"

typedef struct StageLink {
    u16 id;
    u8 pad_02[6];
} StageLink;

typedef struct StageManager {
    u8 pad_00000[0x8];
    StageLink links[1];
    u8 pad_00010[0x18dec - 0x10];
    u16 linkCount;
} StageManager;

extern StageManager *g_stageManager_020a0508;

StageLink *FindStageLink_02099584(u32 id)
{
    u16 index;

    for (index = 0; index < g_stageManager_020a0508->linkCount; index++) {
        if (id == g_stageManager_020a0508->links[index].id) {
            return &g_stageManager_020a0508->links[index];
        }
    }
    return NULL;
}
