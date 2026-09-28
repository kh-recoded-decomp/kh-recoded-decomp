#include "nitro/types.h"

extern u32 data_ov001_020a04c8;

u32 func_ov001_0207b6e0(s32 index)
{
    return *(u32 *)(*(s32 *)(data_ov001_020a04c8 + 0x110) + index * 4);
}
