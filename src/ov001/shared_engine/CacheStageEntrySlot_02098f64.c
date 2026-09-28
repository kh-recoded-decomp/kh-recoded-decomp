#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;
extern u32 func_ov001_02099248(u32 index);

void CacheStageEntrySlot_02098f64(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (g_stageManager_020a0508 == 0) {
        return;
    }
    *(u32 *)(g_stageManager_020a0508 + index * 0x20 + 0x18a94) = func_ov001_02099248(index);
    *(u32 *)(g_stageManager_020a0508 + index * 0x20 + 0x18ab0) = 0x99a;
}
