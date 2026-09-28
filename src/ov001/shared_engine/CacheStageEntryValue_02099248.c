#include "nitro/types.h"

extern u8 *g_stageManager_020a0508;
extern s32 func_ov001_0206dc38(u32 scaledIndex);
extern u32 func_ov001_0206db5c(u32 index);

u32 CacheStageEntryValue_02099248(u32 id)
{
    u32 scaled = (id - 1) * 0x10000;
    u32 index = scaled >> 16;

    if (g_stageManager_020a0508 == 0) {
        return 0;
    }
    if ((s32)index < func_ov001_0206dc38(scaled)) {
        *(u32 *)(g_stageManager_020a0508 + index * 0x20 + 0x18a94) = func_ov001_0206db5c(index);
        return *(u32 *)(g_stageManager_020a0508 + index * 0x20 + 0x18a94);
    }
    return 0;
}
