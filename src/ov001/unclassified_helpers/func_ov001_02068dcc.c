#include "nitro/types.h"

extern s32 func_ov001_02068d28(s32 param1, s32 param2);
extern void func_ov001_02068ee0(u32 value, s32 index);
extern void func_ov001_02068cfc(u32 param1, s32 param2);

s32 func_ov001_02068dcc(s32 index)
{
    s32 slot;

    slot = index + 4;
    if (index < 0) {
        slot = func_ov001_02068d28(4, 4);
    }
    if (slot < 0) {
        return -1;
    }
    func_ov001_02068ee0(0, slot - 4);
    func_ov001_02068cfc(1, slot);
    return slot - 4;
}
