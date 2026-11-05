#include "nitro/types.h"

extern u8 *data_ov001_020a0494;

u32 GetPostIntroElapsedMilliseconds(void)
{
    return *(const u32 *)(data_ov001_020a0494 + 0x8);
}
