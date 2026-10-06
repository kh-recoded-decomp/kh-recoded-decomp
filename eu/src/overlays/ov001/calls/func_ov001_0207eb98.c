#include "nitro/types.h"

extern u32 data_ov001_020a04f4;

BOOL func_ov001_0207eb98(void)
{
    if (data_ov001_020a04f4 != 0 && *(s32 *)(data_ov001_020a04f4 + 0x20) != 0) {
        return 1;
    }
    return 0;
}
