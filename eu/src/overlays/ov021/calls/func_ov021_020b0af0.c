#include "nitro/types.h"

extern u32 func_ov001_0209c3e8();

u32 func_ov021_020b0af0(int self)
{
    s32 state;

    state = func_ov001_0209c3e8();
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = *(u32 *)(state + 0x18e78);
    return 0;
}
