#include "nitro/types.h"

extern void SetSessionFlag(s32 param);
extern void ClearSessionPackedBit(s32 param);

void func_ov001_0206943c(s32 index, s32 useSecondSet, s32 useAltCall)
{
    if (useSecondSet != 0) {
        index = index + 0xf8;
    }
    if (useAltCall != 0) {
        ClearSessionPackedBit(index * 2 + 0x331f);
        return;
    }
    SetSessionFlag(index * 2 + 0x331f);
}
