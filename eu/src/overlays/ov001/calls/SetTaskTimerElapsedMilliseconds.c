#include "nitro/types.h"

extern u32 data_ov001_020a0494;

void SetTaskTimerElapsedMilliseconds(u32 value, s32 index)
{
    *(u32 *)(data_ov001_020a0494 + (index + 4) * 4) = value;
}
