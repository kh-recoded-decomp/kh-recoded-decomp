#include "nitro/types.h"

extern u32 gSessionTimerWork;

void SetTaskTimerElapsedMilliseconds(u32 value, s32 index)
{
    *(u32 *)(gSessionTimerWork + (index + 4) * 4) = value;
}
