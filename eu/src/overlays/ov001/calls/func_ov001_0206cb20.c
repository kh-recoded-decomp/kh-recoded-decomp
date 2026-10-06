#include "nitro/types.h"

extern u32 data_ov001_020a04b8;

BOOL func_ov001_0206cb20(void)
{
    if (*(char *)(data_ov001_020a04b8 + 0x15) == 1) {
        return 1;
    }
    return 0;
}
