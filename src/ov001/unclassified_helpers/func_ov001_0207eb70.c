#include "nitro/types.h"

extern u32 data_ov001_020a04d4;

BOOL func_ov001_0207eb70(void)
{
    if (data_ov001_020a04d4 != 0 && *(s32 *)(data_ov001_020a04d4 + 0x20) != 0) {
        return 1;
    }
    return 0;
}
