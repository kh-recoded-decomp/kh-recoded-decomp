#include "nitro/types.h"

extern s32 func_ov001_0207b3f4(void);
extern s32 func_ov001_0207b610(void);
extern u32 LookupChannelEntry_020b62c8(u32 value);

u32 func_ov001_0207b688(u32 value)
{
    u32 result;

    result = 0xffff;
    if (func_ov001_0207b3f4() == 2 && func_ov001_0207b610() != 0) {
        result = LookupChannelEntry_020b62c8(value);
    }
    return result;
}
