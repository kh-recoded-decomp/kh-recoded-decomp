#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern s32 func_ov001_0209c914(s32 first, s32 second, u16 *outResult);

s32 func_ov001_020878c4(s32 first, s32 second, u16 *outResult)
{
    if (data_ov001_0209f2e8 != -1) {
        return func_ov001_0209c914(first, second, outResult);
    }
    return 0;
}
