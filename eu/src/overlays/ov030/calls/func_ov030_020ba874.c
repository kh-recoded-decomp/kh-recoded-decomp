#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern void BeginFieldScreenModeTransition(s32 arg);

u32 func_ov030_020ba874(void)
{
    u32 ctx;

    ctx = data_ov030_020bd020;
    BeginFieldScreenModeTransition((s32)*(s8 *)(data_ov030_020bd020 + 8));
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 0x20;
    return 10;
}
