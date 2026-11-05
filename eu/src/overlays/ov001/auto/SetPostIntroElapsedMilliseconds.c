#include "nitro/types.h"

extern u8 *data_ov001_020a0494;

void SetPostIntroElapsedMilliseconds(u32 value)
{
    *(u32 *)(data_ov001_020a0494 + 0x8) = value;
}
