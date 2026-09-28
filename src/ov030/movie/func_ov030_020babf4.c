#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;

void func_ov030_020babf4(u8 value)
{
    *(u8 *)(g_moviePlayerCtx_020bd000 + 8) = value;
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x4000;
}
