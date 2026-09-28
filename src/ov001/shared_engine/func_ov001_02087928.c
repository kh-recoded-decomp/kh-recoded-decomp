#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern s32 func_ov001_0209c940(void);

s32 func_ov001_02087928(void)
{
    s32 result;

    if (g_activeService_0209f2c8 != -1) {
        result = func_ov001_0209c940();
        return result;
    }
    return 0;
}
