#include "nitro/types.h"

extern u32 data_ov001_020a04ac;

u16 func_ov001_02074fec(s32 index)
{
    if (data_ov001_020a04ac == 0) {
        return 0;
    }
    return *(u16 *)(data_ov001_020a04ac + index * 6 + 0xb4);
}
