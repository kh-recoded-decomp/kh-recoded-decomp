#include "nitro/types.h"

extern u32 gSessionTimerWork;

u32 GetFieldTimerCounterMilliseconds(s32 index)
{
    return *(u32 *)(gSessionTimerWork + (index + 3) * 4);
}
