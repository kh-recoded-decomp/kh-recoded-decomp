#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern s32 func_ov001_0209c900(s32 eventIndex, s32 first, s32 second, u16 *outResult);

s32 func_ov001_020878b8(s32 eventIndex, s32 first, s32 second, u16 *outResult)
{
    if (g_activeService_0209f2c8 != -1) {
        return func_ov001_0209c900(eventIndex, first, second, outResult);
    }
    return 0;
}
