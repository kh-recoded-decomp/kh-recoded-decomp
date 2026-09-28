#include "nitro/types.h"

extern s32 func_ov001_0207b3cc(void);
extern s32 func_ov001_0207b5e8(void);
extern u32 func_ov025_020b62a8(u32 value);

u32 func_ov001_0207b660(u32 value)
{
    u32 result;

    result = 0xffff;
    if (func_ov001_0207b3cc() == 2 && func_ov001_0207b5e8() != 0) {
        result = func_ov025_020b62a8(value);
    }
    return result;
}
