#include "nitro/types.h"

extern u32 func_0202a78c();
extern u32 g_ov029ObjHandle_020bab60;

BOOL HasOv029ObjectField28_020baa40(void)
{
    u32 value;

    value = func_0202a78c(g_ov029ObjHandle_020bab60);
    return value != 0;
}
