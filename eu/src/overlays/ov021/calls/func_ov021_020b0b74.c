#include "nitro/types.h"

extern u32 IsSessionFlagSet();

u32 func_ov021_020b0b74(int self)
{
    u32 value;

    *(u16 *)(self + 0x2c) = 1;
    value = IsSessionFlagSet(0x3713);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
