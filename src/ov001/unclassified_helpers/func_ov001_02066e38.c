#include "nitro/types.h"

extern u32 data_ov001_0209e9fc;

BOOL func_ov001_02066e38(void)
{
    if (data_ov001_0209e9fc != -1) {
        return 1;
    }
    return 0;
}
