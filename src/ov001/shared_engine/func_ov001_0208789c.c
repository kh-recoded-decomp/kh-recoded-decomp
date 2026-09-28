#include "nitro/types.h"

extern s32 g_activeService_0209f2c8;
extern s32 func_ov001_0209c8ec(s32 first, s32 second, u16 *outResult);

s32 func_ov001_0208789c(s32 first, s32 second, u16 *outResult)
{
    if (g_activeService_0209f2c8 != -1) {
        return func_ov001_0209c8ec(first, second, outResult);
    }
    return 0;
}
