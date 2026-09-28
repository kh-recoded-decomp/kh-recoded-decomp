#include "nitro/types.h"

extern u32 data_020b56a4;
extern u32 func_ov001_0209c18c();
extern u32 func_ov006_020a1370();

u32 func_ov021_020b1ad4(int self)
{
    s32 member;

    member = func_ov001_0209c18c(*(u16 *)(data_020b56a4 + 0x16));
    if (member != 0) {
        func_ov006_020a1370(member, **(u32 **)(member + 0x20), self + 0x34);
    }
    return 0;
}
