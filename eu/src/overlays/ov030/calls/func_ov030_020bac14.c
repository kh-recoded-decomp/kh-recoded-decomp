#include "nitro/types.h"

extern u32 data_ov030_020bd020;

void func_ov030_020bac14(u8 value)
{
    *(u8 *)(data_ov030_020bd020 + 8) = value;
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 0x4000;
}
