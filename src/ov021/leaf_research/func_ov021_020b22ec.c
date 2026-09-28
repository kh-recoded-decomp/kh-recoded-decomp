#include "nitro/types.h"

extern u32 FixedPointMultiply12();
extern u32 func_ov001_0209c3c0();
extern u32 func_ov021_020b0374();
extern u32 TaggedValueToFixed_020b03b0();

u32 func_ov021_020b22ec(u32 self, int args)
{
    s32 base;
    u32 factor;
    s32 state;
    u32 scaled;

    base = func_ov021_020b0374();
    factor = func_ov021_020b0374(self, args + 8);
    state = func_ov001_0209c3c0();
    scaled = TaggedValueToFixed_020b03b0(factor);
    scaled = FixedPointMultiply12(*(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e60), scaled);
    *(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e60) = scaled;
    scaled = TaggedValueToFixed_020b03b0(factor);
    scaled = FixedPointMultiply12(*(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e64), scaled);
    *(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e64) = scaled;
    factor = TaggedValueToFixed_020b03b0(factor);
    factor = FixedPointMultiply12(*(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e68), factor);
    *(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e68) = factor;
    return 0;
}
