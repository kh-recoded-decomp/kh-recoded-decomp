#include "nitro/types.h"

extern s32 func_020273a8(void);
extern s32 func_020273c0(void);

s32 func_020275c8(void)
{
    if (func_020273a8() == 0 && func_020273c0() >= 0x50) {
        return 2;
    }
    return 1;
}
