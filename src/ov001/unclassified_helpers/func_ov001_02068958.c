#include "nitro/types.h"

extern u32 data_ov001_020a0470;

void func_ov001_02068958(void)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a0470;
    *(s8 *)(ctx + 6) = -1;
}
