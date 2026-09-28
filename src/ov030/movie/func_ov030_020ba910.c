#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_0206a814(void);

u32 func_ov030_020ba910(void)
{
    s32 ready;

    ready = func_ov001_0206a814();
    if (ready != 0) {
        *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 0xffbf;
        *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x80;
        return 7;
    }
    return 0xffffffff;
}
