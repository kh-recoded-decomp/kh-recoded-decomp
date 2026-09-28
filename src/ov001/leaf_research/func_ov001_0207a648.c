#include "nitro/types.h"

extern u32 g_activeContext_020a04c4;

u32 func_ov001_0207a648(void)
{
    switch (*(u32 *)(g_activeContext_020a04c4 + 0xc)) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
    case 6:
        return 3;
    case 7:
        return 4;
    default:
        return 0;
    }
}
