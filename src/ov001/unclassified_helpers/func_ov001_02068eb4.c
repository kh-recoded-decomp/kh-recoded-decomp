#include "nitro/types.h"

extern u32 data_ov001_020a0474;

u32 func_ov001_02068eb4(s32 index)
{
    return *(u32 *)(data_ov001_020a0474 + (index + 4) * 4);
}
