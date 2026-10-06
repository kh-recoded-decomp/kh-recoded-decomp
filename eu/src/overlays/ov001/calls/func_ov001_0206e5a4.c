#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

void func_ov001_0206e5a4(u32 value)
{
    if (data_ov001_020a04bc != 0) {
        *(u32 *)(data_ov001_020a04bc + 0x8c) = value;
    }
}
