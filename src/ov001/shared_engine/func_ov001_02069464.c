#include "nitro/types.h"

extern u8 func_ov001_02068dcc(u32 mask);

BOOL func_ov001_02069464(u32 *slot)
{
    u8 result;

    if (*(char *)(slot + 4) == 1) {
        if (0 < (int)slot[3]) {
            result = func_ov001_02068dcc(0xffffffff);
            *(u8 *)((int)slot + 0x11) = result;
            *slot = 0x2069401;
            return 0;
        }
        *slot = 0x2069435;
    }
    return 1;
}
