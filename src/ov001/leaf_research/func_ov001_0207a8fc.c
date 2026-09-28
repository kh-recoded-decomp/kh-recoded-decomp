#include "nitro/types.h"

extern u32 func_ov001_0207b3cc(void);

u32 func_ov001_0207a8fc(s32 panel)
{
    s32 mode;
    u32 result;

    result = 0;
    mode = func_ov001_0207b3cc();
    if ((mode == 0) &&
        (((mode = *(s32 *)(panel + 0x30), mode == 4 || (mode == 6)) || (mode == 3)))) {
        result = 1;
    }
    return result;
}
