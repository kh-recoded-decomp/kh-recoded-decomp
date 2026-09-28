#include "nitro/types.h"

void GX_SetVCountEqVal_020065d0(int line)
{
    vu16 *displayStatus = (vu16 *)0x04000004;

    *displayStatus = (u16)((*displayStatus & 0x3f) | ((line & 0xff) << 8) | ((line & 0x100) >> 1));
}
