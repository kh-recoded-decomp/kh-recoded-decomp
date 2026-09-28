#include "nitro/types.h"

extern void func_ov058_020d87c0(void);
extern void func_ov052_020ce7a0(u32 target, s32 type, s32 subType);

void func_ov054_020d24ec(u32 target, s32 type, s32 subType)
{
    if (type == 2 && subType == 0) {
        func_ov058_020d87c0();
    }
    func_ov052_020ce7a0(target, type, subType);
}
