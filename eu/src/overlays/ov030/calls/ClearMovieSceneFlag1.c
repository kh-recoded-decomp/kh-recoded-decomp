#include "nitro/types.h"

extern u32 data_ov030_020bd020;

u32 ClearMovieSceneFlag1(u32 argument0, u32 argument1, u32 argument2, u32 argument3)
{
    u32 value0 = (u32)&data_ov030_020bd020;
    u32 value1 = *(const u32 *)value0;
    u32 value2 = 0xfffd;
    u32 value3 = *(const u16 *)(value1 + 6);
    u32 value4 = value2 & value3;

    *(u16 *)(value1 + 6) = value4;
    return value4;
}
