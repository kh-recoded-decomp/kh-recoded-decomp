#include "nitro/types.h"

extern u32 data_ov021_020b56c4;
extern s32 ResolveTaggedValueRef();
extern u32 GetEntryScaledValue();

u32 func_ov021_020b0df0(int self, int args)
{
    s32 entry;
    s32 resolved;
    u32 value;

    resolved = ResolveTaggedValueRef(self, args + 8);
    entry = data_ov021_020b56c4;
    if (data_ov021_020b56c4 == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 0x10;
    value = GetEntryScaledValue(entry, *(s32 *)(resolved + 4) + 1U & 0xffff);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
