#include "nitro/types.h"
void G2x_SetBlendBrightness_0200686c(u32 regAddr, int plane, int brightness)
{
    if (brightness < 0) {
        *((vu16 *)regAddr + 0) = (u16)(plane | 0xc0);
        *((vu16 *)regAddr + 2) = (u16)-brightness;
    } else {
        *((vu16 *)regAddr + 0) = (u16)(plane | 0x80);
        *((vu16 *)regAddr + 2) = (u16)brightness;
    }
}
