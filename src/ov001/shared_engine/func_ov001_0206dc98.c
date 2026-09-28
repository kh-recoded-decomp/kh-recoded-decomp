#include "nitro/types.h"

extern u32 g_manager_020a049c;

void func_ov001_0206dc98(void)
{
    if (g_manager_020a049c != 0) {
        *(u32 *)(g_manager_020a049c + 0xf8) = 0;
    }
}
