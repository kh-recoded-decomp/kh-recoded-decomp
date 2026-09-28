#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern void func_ov001_0206a72c(s32 arg);

u32 func_ov030_020ba854(void)
{
    u32 ctx;

    ctx = g_moviePlayerCtx_020bd000;
    func_ov001_0206a72c((s32)*(s8 *)(g_moviePlayerCtx_020bd000 + 8));
    *(u16 *)(ctx + 6) = *(u16 *)(ctx + 6) | 0x20;
    return 10;
}
