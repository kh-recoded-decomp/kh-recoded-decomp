#include "nitro/types.h"

typedef unsigned int UNDEF4;

extern s32 func_ov001_02097a84(s32 service, UNDEF4 arg1, UNDEF4 arg2);
extern s32 func_ov001_0209c0ec(void);

s32 func_ov001_020880b4(UNDEF4 unusedArg, UNDEF4 arg1, UNDEF4 arg2)
{
    s32 service;
    s32 result;

    service = func_ov001_0209c0ec();
    if (service != 0) {
        result = func_ov001_02097a84(service, arg1, arg2);
        return result;
    }
    return 0;
}
