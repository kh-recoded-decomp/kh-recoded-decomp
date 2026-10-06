#include "nitro/types.h"

extern void BlitNibbleRunPadded(u32 param1, u32 param2, u32 param3, u32 param4,
                                 u32 param5, u32 param6, u32 param7);

void func_ov001_020738b8(u32 param1, u32 param2, u32 param3)
{
    BlitNibbleRunPadded(param1, param2, 6, 0x30, 0, 2, param3);
}
