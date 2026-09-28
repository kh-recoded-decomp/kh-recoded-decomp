#include "nitro/types.h"

extern void func_ov001_02098360(u32 arg);

BOOL HandleCommandKind1_020998cc(s32 kind, u32 arg)
{
    if (kind == 1) {
        func_ov001_02098360(arg);
    }
    return TRUE;
}
