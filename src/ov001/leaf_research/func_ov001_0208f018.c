#include "nitro/types.h"

s32 func_ov001_0208f018(u8 *ctx, int index)
{
    u8 *entries = *(u8 **)(ctx + 8);
    int depth = *(s32 *)(ctx + 4);
    s32 *data = *(s32 **)(entries + (depth + -1) * 0x10 + 0xc);
    return data[index + -1];
}
