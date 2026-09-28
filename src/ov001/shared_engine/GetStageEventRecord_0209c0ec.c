#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;

u8 *GetStageEventRecord_0209c0ec(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (g_stageManager_020a0508 == 0) {
        return 0;
    }
    if (index < *(u16 *)(g_stageManager_020a0508 + 0x18de4)) {
        return *(u8 **)(g_stageManager_020a0508 + 0x210) + index * 0x1c8;
    }
    return 0;
}
