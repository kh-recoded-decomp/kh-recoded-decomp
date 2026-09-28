#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;

void func_ov030_020bb440(BOOL enable)
{
    if (enable != 0) {
        *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 4;
        return;
    }
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 0xfffb;
}
