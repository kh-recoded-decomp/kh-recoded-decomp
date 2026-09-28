#include "nitro/types.h"

extern u32 VEC_Mag_01ff9f28();
extern u32 func_ov001_0209c3c0();
extern u32 func_ov021_020b0374();

u32 func_ov021_020b2380(int self)
{
    s32 base;
    s32 state;
    u32 magnitude;

    base = func_ov021_020b0374();
    state = func_ov001_0209c3c0();
    *(u16 *)(self + 0x2c) = 0x10;
    magnitude = VEC_Mag_01ff9f28(state + 0x18e60 + *(s32 *)(base + 4) * 0xc);
    *(u32 *)(self + 0x30) = magnitude;
    return 0;
}
