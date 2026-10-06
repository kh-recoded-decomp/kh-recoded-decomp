#include "nitro/types.h"

extern u32 data_ov001_020a04e8;

u8 func_ov001_0207b484(void)
{
    if (data_ov001_020a04e8 == 0) {
        return 0;
    }
    return *(u8 *)(data_ov001_020a04e8 + 0x103);
}
