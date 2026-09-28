#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;

u32 func_ov030_020bb354(void)
{
    if (g_moviePlayerCtx_020bd000 != 0) {
        return g_moviePlayerCtx_020bd000 + 0x24;
    }
    return 0;
}
