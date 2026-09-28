#include "nitro/types.h"

extern u32 PMi_SendChannelValueSync_02010448(u32 channel, u32 value, void *reserved);

u32 PM_GetBackLight_020105c8(u32 *top, u32 *bottom)
{
    u16 reg;
    u32 result = PMi_SendChannelValueSync_02010448(0xf, 3, &reg);

    if (result == 0) {
        if (top != NULL) {
            *top = (reg & 8) ? 1 : 0;
        }

        if (bottom != NULL) {
            *bottom = (reg & 4) ? 1 : 0;
        }
    }

    return result;
}
