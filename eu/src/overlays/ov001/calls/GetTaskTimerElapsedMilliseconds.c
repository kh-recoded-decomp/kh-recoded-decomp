#include "nitro/types.h"

extern u32 data_ov001_020a0494;

u32 GetTaskTimerElapsedMilliseconds(s32 index)
{
    return *(u32 *)(data_ov001_020a0494 + (index + 4) * 4);
}
