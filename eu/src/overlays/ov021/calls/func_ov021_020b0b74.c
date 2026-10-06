#include "nitro/types.h"

extern u32 func_ov001_020645c8();

u32 func_ov021_020b0b74(int self)
{
    u32 value;

    *(u16 *)(self + 0x2c) = 1;
    value = func_ov001_020645c8(0x3713);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
