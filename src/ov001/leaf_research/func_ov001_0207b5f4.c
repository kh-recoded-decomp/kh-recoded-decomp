#include "nitro/types.h"

extern u32 g_activePanel_020a04c8;

u32 func_ov001_0207b5f4(void)
{
    if (*(u32 *)(g_activePanel_020a04c8 + 0x30) == 6) {
        return 1;
    }
    return 0;
}
