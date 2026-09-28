#include "nitro/types.h"

extern u32 func_ov001_02075248();

u32 func_ov021_020b0aec(int self)
{
    u32 value;

    *(u16 *)(self + 0x2c) = 1;
    value = func_ov001_02075248(0);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
