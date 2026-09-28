#include "nitro/types.h"

extern u32 g_ov038ObjHandle_020bbd80;
extern s32 func_0202a78c(u32 handle);

BOOL HasOv038ObjectField28_020ba694(void)
{
    s32 result;

    result = func_0202a78c(g_ov038ObjHandle_020bbd80);
    return result != 0;
}
