#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_0206685c(void);
extern s32 func_ov001_0206a814(void);
extern void func_ov001_0206a7c0(s32 arg);

u32 func_ov030_020ba96c(void)
{
    u32 ctx;
    s32 ready;

    ctx = g_moviePlayerCtx_020bd000;
    if (((*(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 0x10) == 0) &&
        (ready = func_ov001_0206685c(), ready != 0)) {
        return 0xffffffff;
    }
    ready = func_ov001_0206a814();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_0206a7c0((s32)*(s8 *)(ctx + 8));
    return 0x10;
}
