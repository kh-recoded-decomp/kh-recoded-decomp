#include "nitro/types.h"

extern u32 data_020b56a4;
extern s32 func_ov021_020b0374();
extern u32 func_ov001_02096ba4();

u32 func_ov021_020b0dd0(int self, int args)
{
    s32 entry;
    s32 resolved;
    u32 value;

    resolved = func_ov021_020b0374(self, args + 8);
    entry = data_020b56a4;
    if (data_020b56a4 == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 0x10;
    value = func_ov001_02096ba4(entry, *(s32 *)(resolved + 4) + 1U & 0xffff);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
