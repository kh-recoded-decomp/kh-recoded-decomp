#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;

u8 *GetStagePartySlot_0209c1d4(u32 slot)
{
    if (g_stageManager_020a0508 == 0) {
        return 0;
    }
    if (slot < 3) {
        return g_stageManager_020a0508 + 0x18af4 + slot * 0x2c;
    }
    return 0;
}
