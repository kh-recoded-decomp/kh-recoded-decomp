#include "nitro/types.h"

extern u32 GetStageManager();

u32 func_ov021_020b0ad4(int self)
{
    s32 state;

    state = GetStageManager();
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = *(u32 *)(state + 0x18e7c);
    return 0;
}
