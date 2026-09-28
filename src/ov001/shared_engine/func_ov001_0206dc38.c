#include "nitro/types.h"

extern u32 g_manager_020a049c;

u32 func_ov001_0206dc38(void)
{
    if (g_manager_020a049c == 0) {
        return 0;
    }
    return *(u32 *)(g_manager_020a049c + 0x7c);
}
