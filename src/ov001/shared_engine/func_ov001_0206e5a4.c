#include "nitro/types.h"

extern u32 g_manager_020a049c;

void func_ov001_0206e5a4(u32 value)
{
    if (g_manager_020a049c != 0) {
        *(u32 *)(g_manager_020a049c + 0x8c) = value;
    }
}
