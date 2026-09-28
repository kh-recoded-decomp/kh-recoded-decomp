#include "nitro/types.h"

extern u32 data_020b56a4;
extern u32 func_ov001_0209c18c();

u32 func_ov021_020b0ebc(int self)
{
    s32 member;

    if (data_020b56a4 == 0) {
        return 0;
    }
    member = func_ov001_0209c18c(*(u16 *)(data_020b56a4 + 0x16));
    if (member == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = *(u32 *)(member + 0x18);
    return 0;
}
