#include "nitro/types.h"

extern u32 data_ov030_020bd020;

u32 func_ov030_020bb374(void)
{
    if (data_ov030_020bd020 != 0) {
        return data_ov030_020bd020 + 0x24;
    }
    return 0;
}
