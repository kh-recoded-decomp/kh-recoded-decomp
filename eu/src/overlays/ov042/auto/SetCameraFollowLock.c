#include "nitro/types.h"

extern u8 *data_ov042_020be5e0;

void SetCameraFollowLock(u32 value)
{
    *(u32 *)(data_ov042_020be5e0 + 0x48) = value;
}
