#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern s32 func_ov001_0209c758(s32 mode, s32 filterId);

s32 func_ov001_02087868(s32 mode)
{
    if (g_activeService_0209f2c8 != -1) {
        return func_ov001_0209c758(mode, -1);
    }
    return 0;
}
