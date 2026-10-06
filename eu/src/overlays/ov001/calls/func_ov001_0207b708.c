#include "nitro/types.h"

extern u32 data_ov001_020a04e8;

u32 func_ov001_0207b708(s32 index)
{
    return *(u32 *)(*(s32 *)(data_ov001_020a04e8 + 0x110) + index * 4);
}
