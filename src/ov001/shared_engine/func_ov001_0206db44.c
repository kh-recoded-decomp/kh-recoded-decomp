#include "nitro/types.h"

extern u32 g_manager_020a049c;

u32 func_ov001_0206db44(void)
{
    if (g_manager_020a049c == 0) {
        return 0x1000;
    }
    return *(u32 *)(g_manager_020a049c + 0x9c);
}
