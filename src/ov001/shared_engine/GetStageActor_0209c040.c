#include "nitro/types.h"

typedef struct {
    u8 data[0x3c8];
} StageActor;

typedef struct {
    u8 pad_00[0x4b14];
    StageActor actors[64];
} StageManager;

extern StageManager *g_stageManager_020a0508;

StageActor *GetStageActor_0209c040(int id)
{
    int index = id - 1;

    if (g_stageManager_020a0508 == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (index < 64) {
        return &g_stageManager_020a0508->actors[index];
    }
    return 0;
}
