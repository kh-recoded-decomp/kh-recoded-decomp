#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20c];
    void **handles;
} StageManager;

extern StageManager *g_stageManager_020a0508;

void *GetStageObjectHandle_0209c0c4(u32 id)
{
    u32 index = (id - 1) & 0xffff;
    void *handle;

    if (g_stageManager_020a0508 == 0) {
        return 0;
    }
    handle = g_stageManager_020a0508->handles[index];
    if (handle == 0) {
        return 0;
    }
    return handle;
}
