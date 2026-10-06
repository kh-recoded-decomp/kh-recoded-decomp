#include "nitro/types.h"

extern u32 data_ov001_020a048c;

void func_ov001_020681b0(u8 byteValue, u32 wordValue)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a048c;
    ctx[0x10c0] = byteValue;
    *(u32 *)(ctx + 0x10c4) = wordValue;
}
