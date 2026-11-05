#include "nitro/types.h"

extern u8 *data_ov001_020a04f8;

u32 GetFieldObjectDrawBlockMask(void)
{
    return *(const u8 *)(data_ov001_020a04f8 + 0x14) & 0x1;
}
