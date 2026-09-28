#include "nitro/types.h"

extern u32 data_ov001_020a04cc;

u32 func_ov001_0207d4bc(void)
{
    if (data_ov001_020a04cc != 0) {
        return *(u32 *)(data_ov001_020a04cc + 4);
    }
    return 0;
}
