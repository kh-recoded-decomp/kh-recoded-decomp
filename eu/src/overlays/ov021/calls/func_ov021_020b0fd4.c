#include "nitro/types.h"

extern u32 GetStageManager();

u32 func_ov021_020b0fd4(int self)
{
    s32 state;

    state = GetStageManager();
    *(u16 *)(self + 0x2c) = 1;
    *(u32 *)(self + 0x30) = (u32)*(u16 *)(state + 0x18ed2);
    return 0;
}
