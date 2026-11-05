#include "nitro/types.h"

extern s32 FindFreeMaskBit(s32 param1, s32 param2);
extern void SetTaskTimerElapsedMilliseconds(u32 value, s32 index);
extern void SetSessionStateBit(u32 param1, s32 param2);

s32 AllocateTaskTimerSlot(s32 index)
{
    s32 slot;

    slot = index + 4;
    if (index < 0) {
        slot = FindFreeMaskBit(4, 4);
    }
    if (slot < 0) {
        return -1;
    }
    SetTaskTimerElapsedMilliseconds(0, slot - 4);
    SetSessionStateBit(1, slot);
    return slot - 4;
}
