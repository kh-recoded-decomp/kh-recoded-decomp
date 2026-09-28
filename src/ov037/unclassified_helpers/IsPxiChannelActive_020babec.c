#include "nitro/types.h"

extern u32 g_pxiChannel_020bb6a0;
extern s32 func_0202a78c(u32 handle);

BOOL IsPxiChannelActive_020babec(void)
{
    s32 result;

    result = func_0202a78c(g_pxiChannel_020bb6a0);
    return result != 0;
}
