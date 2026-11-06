#include "nitro/types.h"

extern u32 gCounterHudWork;

BOOL SetCounterHudFadeEnabled(u32 value)
{
    u32 context;

    context = gCounterHudWork;
    if (gCounterHudWork != 0) {
        *(u32 *)(gCounterHudWork + 0xf8) = value;
    }
    return context != 0;
}
