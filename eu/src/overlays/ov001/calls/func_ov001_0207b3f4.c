#include "nitro/types.h"

extern u32 data_ov001_020a04e8;

u32 func_ov001_0207b3f4(void)
{
    if (data_ov001_020a04e8 == 0) {
        return 0xffffffff;
    }
    return *(u32 *)(data_ov001_020a04e8 + 0xdc);
}
