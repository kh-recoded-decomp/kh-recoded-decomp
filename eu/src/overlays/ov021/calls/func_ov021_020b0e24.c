#include "nitro/types.h"

extern u32 data_ov021_020b56c4;

u32 func_ov021_020b0e24(int self)
{
    s32 entry;

    entry = data_ov021_020b56c4;
    if (data_ov021_020b56c4 == 0) {
        return 0;
    }
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = (u32)*(u16 *)(entry + 0x1e);
    return 0;
}
