#include "nitro/types.h"

extern u32 gCounterHudWork;

u32 GetCounterHudFadeState(void)
{
    if (gCounterHudWork != 0) {
        return *(u32 *)(gCounterHudWork + 4);
    }
    return 0;
}
