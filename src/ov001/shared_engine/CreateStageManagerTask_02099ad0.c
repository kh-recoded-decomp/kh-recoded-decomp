#include "nitro/types.h"

typedef struct StageManager {
    u8 pad_00[4];
    void *task;
} StageManager;

extern u8 data_ov001_020a0340[];
extern StageManager *g_stageManager_020a0508;
extern void *func_0202a448(void *descriptor, void *userData);

BOOL CreateStageManagerTask_02099ad0(void *userData)
{
    g_stageManager_020a0508->task = func_0202a448(data_ov001_020a0340, userData);
    return TRUE;
}
