#include "nitro/types.h"

extern void func_ov001_020645dc(s32 param);
extern void func_ov001_020645e8(s32 param);

void func_ov001_0206943c(s32 index, s32 useSecondSet, s32 useAltCall)
{
    if (useSecondSet != 0) {
        index = index + 0xf8;
    }
    if (useAltCall != 0) {
        func_ov001_020645e8(index * 2 + 0x331f);
        return;
    }
    func_ov001_020645dc(index * 2 + 0x331f);
}
