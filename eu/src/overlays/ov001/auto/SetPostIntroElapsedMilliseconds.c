#include "nitro/types.h"

extern u8 *gSessionTimerWork;

void SetPostIntroElapsedMilliseconds(u32 value)
{
    *(u32 *)(gSessionTimerWork + 0x8) = value;
}
