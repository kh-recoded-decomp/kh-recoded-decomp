#include "nitro/types.h"

extern void SetSessionFlag(u32 param1, u32 param2);
extern void ClearSessionPackedBit(u32 param1, u32 param2);

void func_ov001_020869a0(u32 param1, u32 param2, int useAlt) {
    if (useAlt != 0) {
        SetSessionFlag(param1, param2);
        return;
    }
    ClearSessionPackedBit(param1, param2);
}
