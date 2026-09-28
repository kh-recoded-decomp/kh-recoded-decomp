#include "nitro/types.h"

extern u32 g_obj_020a0498;

BOOL func_ov001_0206cb20(void)
{
    if (*(char *)(g_obj_020a0498 + 0x15) == 1) {
        return 1;
    }
    return 0;
}
