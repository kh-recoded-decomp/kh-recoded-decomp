#include "nitro/types.h"

extern u32 gSessionTimerWork;

u32 GetTaskTimerElapsedMilliseconds(s32 index)
{
    return *(u32 *)(gSessionTimerWork + (index + 4) * 4);
}
