#include "nitro/types.h"

extern u32 data_ov001_020a0494;

void func_ov001_02068ed0(u32 value, s32 index)
{
    *(u32 *)(data_ov001_020a0494 + (index + 3) * 4) = value;
}
