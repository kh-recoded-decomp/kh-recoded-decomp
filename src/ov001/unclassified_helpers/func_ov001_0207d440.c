#include "nitro/types.h"

extern u32 data_ov001_020a04cc;

BOOL func_ov001_0207d440(u32 value)
{
    u32 context;

    context = data_ov001_020a04cc;
    if (data_ov001_020a04cc != 0) {
        *(u32 *)(data_ov001_020a04cc + 0xf8) = value;
    }
    return context != 0;
}
