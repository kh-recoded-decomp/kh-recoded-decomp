#include "nitro/types.h"

#define HW_VBLANK_COUNT_BUF 0x02fffc3c

static inline u32 OS_GetVBlankCount(void)
{
    return *(vu32 *)HW_VBLANK_COUNT_BUF;
}

void PMi_WaitVBlank_02010220(void)
{
    vu32 vcount = OS_GetVBlankCount();

    while (vcount == OS_GetVBlankCount()) {
    }
}
