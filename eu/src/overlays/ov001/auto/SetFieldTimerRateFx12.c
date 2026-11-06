#include "nitro/types.h"

extern u8 *gSessionTimerWork;

void SetFieldTimerRateFx12(u16 value)
{
    *(u16 *)(gSessionTimerWork + 0x22) = value;
}
