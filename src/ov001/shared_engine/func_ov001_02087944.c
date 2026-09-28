#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern s32 func_ov001_0209c99c(s32 startIndex);

s32 func_ov001_02087944(s32 startIndex)
{
    if (g_activeService_0209f2c8 != -1) {
        return func_ov001_0209c99c(startIndex);
    }
    return 0;
}
