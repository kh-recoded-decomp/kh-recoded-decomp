#include "nitro/types.h"

extern u32 data_020b56a4;

u32 func_ov021_020b1298(int self)
{
    s32 entry;

    entry = data_020b56a4;
    if (data_020b56a4 == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 0x10;
    *(u32 *)(self + 0x30) = *(u32 *)(entry + 0x1a0);
    return 0;
}
