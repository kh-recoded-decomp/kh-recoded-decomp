#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

u32 func_ov001_0206db44(void)
{
    if (data_ov001_020a04bc == 0) {
        return 0x1000;
    }
    return *(u32 *)(data_ov001_020a04bc + 0x9c);
}
