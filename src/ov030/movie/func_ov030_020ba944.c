#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern void func_ov001_02066810(void);
extern void func_ov001_02087628(u32 arg);

u32 func_ov030_020ba944(void)
{
    u32 ctx;

    ctx = g_moviePlayerCtx_020bd000;
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x20;
    if ((*(u16 *)(ctx + 6) & 0x10) == 0) {
        func_ov001_02066810();
        func_ov001_02087628(1);
    }
    return 0xf;
}
