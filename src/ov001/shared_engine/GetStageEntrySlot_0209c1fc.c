#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;

u8 *GetStageEntrySlot_0209c1fc(u32 id)
{
    u32 index = (id - 1) & 0xffff;

    if (g_stageManager_020a0508 == 0) {
        return 0;
    }
    if (index < 0x40) {
        return g_stageManager_020a0508 + 0x18b78 + index * 8;
    }
    return 0;
}
