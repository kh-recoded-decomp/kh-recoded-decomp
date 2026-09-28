#include "nitro/types.h"

extern u32 g_activePanel_020a04c8;

u32 func_ov001_0207b3cc(void)
{
    if (g_activePanel_020a04c8 == 0) {
        return 0xffffffff;
    }
    return *(u32 *)(g_activePanel_020a04c8 + 0xdc);
}
