#include "nitro/types.h"

extern u32 func_ov001_0209c3c0();

u32 func_ov021_020b0fb4(int self)
{
    s32 state;

    state = func_ov001_0209c3c0();
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = (u32)*(u16 *)(state + 0x18ed2);
    return 0;
}
