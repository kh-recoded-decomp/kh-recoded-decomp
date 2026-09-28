#include "nitro/types.h"

extern u32 data_020b56a4;
extern u32 func_ov001_0209c18c();
extern u32 func_ov008_020a1280();
extern u32 func_ov021_020b0374();
extern u32 TaggedValueToFixed_020b03b0();

u32 func_ov021_020b0a48(int self, int args)
{
    u32 resolved;
    s32 member;
    u32 value;

    resolved = func_ov021_020b0374(self, args + 8);
    if (data_020b56a4 == 0) {
        return 0;
    }
    member = func_ov001_0209c18c(*(u16 *)(data_020b56a4 + 0x16));
    if (member == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    value = TaggedValueToFixed_020b03b0(resolved);
    value = func_ov008_020a1280(member, value, 0, 1);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
