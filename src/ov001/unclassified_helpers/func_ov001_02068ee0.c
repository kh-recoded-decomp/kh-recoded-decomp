#include "nitro/types.h"

extern u32 data_ov001_020a0474;

void func_ov001_02068ee0(u32 value, s32 index)
{
    *(u32 *)(data_ov001_020a0474 + (index + 4) * 4) = value;
}
