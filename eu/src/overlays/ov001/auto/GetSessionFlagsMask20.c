#include "nitro/types.h"

extern u8 *gFieldSessionWork;

u32 GetSessionFlagsMask20(void)
{
    return *(const u32 *)(gFieldSessionWork + 0x20) & 0x20;
}
