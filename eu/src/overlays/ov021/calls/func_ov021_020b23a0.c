#include "nitro/types.h"

extern u32 VEC_Mag();
extern u32 func_ov001_0209c3e8();
extern u32 ResolveTaggedValueRef();

u32 func_ov021_020b23a0(int self)
{
    s32 base;
    s32 state;
    u32 magnitude;

    base = ResolveTaggedValueRef();
    state = func_ov001_0209c3e8();
    *(u16 *)(self + 0x2c) = 0x10;
    magnitude = VEC_Mag(state + 0x18e60 + *(s32 *)(base + 4) * 0xc);
    *(u32 *)(self + 0x30) = magnitude;
    return 0;
}
