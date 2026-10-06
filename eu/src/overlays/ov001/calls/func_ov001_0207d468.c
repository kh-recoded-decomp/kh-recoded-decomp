#include "nitro/types.h"

extern u32 data_ov001_020a04ec;

BOOL func_ov001_0207d468(u32 value)
{
    u32 context;

    context = data_ov001_020a04ec;
    if (data_ov001_020a04ec != 0) {
        *(u32 *)(data_ov001_020a04ec + 0xf8) = value;
    }
    return context != 0;
}
