#include "nitro/types.h"

extern u32 gSessionTimerWork;

void SetFieldTimerCounterMilliseconds(u32 value, s32 index)
{
    *(u32 *)(gSessionTimerWork + (index + 3) * 4) = value;
}
