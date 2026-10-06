#include "nitro/types.h"

extern u32 data_ov001_020a0494;
extern s32 FindFreeMaskBit(s32 param1, s32 param2);
extern void func_ov001_02068ed0(u32 value, s32 index);
extern void SetSessionStateBit(u32 param1, s32 param2);

s32 func_ov001_02068d8c(s32 index)
{
    u32 ctx;
    s32 slot;

    ctx = data_ov001_020a0494;
    slot = index + 3;
    if (index < 0) {
        slot = FindFreeMaskBit(3, 1);
    }
    if (slot < 0) {
        return -1;
    }
    func_ov001_02068ed0(0, slot - 3);
    SetSessionStateBit(1, slot);
    *(u16 *)(ctx + 0x22) = 0x1000;
    return slot - 3;
}
