#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

void func_ov001_0206dc98(void)
{
    if (data_ov001_020a04bc != 0) {
        *(u32 *)(data_ov001_020a04bc + 0xf8) = 0;
    }
}
