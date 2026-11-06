#include "nitro/types.h"

extern u8 *gSessionTimerWork;

u32 GetPostIntroElapsedMilliseconds(void)
{
    return *(const u32 *)(gSessionTimerWork + 0x8);
}
