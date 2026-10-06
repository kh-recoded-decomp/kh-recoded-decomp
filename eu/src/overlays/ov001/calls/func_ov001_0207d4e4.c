#include "nitro/types.h"

extern u32 data_ov001_020a04ec;

u32 func_ov001_0207d4e4(void)
{
    if (data_ov001_020a04ec != 0) {
        return *(u32 *)(data_ov001_020a04ec + 4);
    }
    return 0;
}
