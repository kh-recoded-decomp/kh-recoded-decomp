#include "nitro/types.h"

extern u32 FX_Mul();
extern u32 func_ov001_0209c3e8();
extern u32 ResolveTaggedValueRef();
extern u32 TaggedValueToFixed();

u32 func_ov021_020b230c(u32 self, int args)
{
    s32 base;
    u32 factor;
    s32 state;
    u32 scaled;

    base = ResolveTaggedValueRef();
    factor = ResolveTaggedValueRef(self, args + 8);
    state = func_ov001_0209c3e8();
    scaled = TaggedValueToFixed(factor);
    scaled = FX_Mul(*(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e60), scaled);
    *(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e60) = scaled;
    scaled = TaggedValueToFixed(factor);
    scaled = FX_Mul(*(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e64), scaled);
    *(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e64) = scaled;
    factor = TaggedValueToFixed(factor);
    factor = FX_Mul(*(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e68), factor);
    *(u32 *)(state + *(s32 *)(base + 4) * 0xc + 0x18e68) = factor;
    return 0;
}
