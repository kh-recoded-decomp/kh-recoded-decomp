#include "nitro/types.h"

extern u32 g_activePanel_020a04c8;

u8 func_ov001_0207b45c(void)
{
    if (g_activePanel_020a04c8 == 0) {
        return 0;
    }
    return *(u8 *)(g_activePanel_020a04c8 + 0x103);
}
