#include "nitro/types.h"

u32 func_ov010_020a0a70(int cmd)
{
    int arc = *(int *)(cmd + 8);
    return *(u32 *)(arc + 0x50);
}
