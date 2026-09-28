#include "nitro/types.h"

extern u32 g_manager_020a049c;

int func_ov001_0206db8c(int index)
{
    return (int)*(short *)(g_manager_020a049c + index * 2 + 0xa0);
}
