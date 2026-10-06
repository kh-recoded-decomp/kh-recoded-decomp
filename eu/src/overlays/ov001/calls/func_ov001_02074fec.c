#include "nitro/types.h"

extern u32 data_ov001_020a04cc;

u16 func_ov001_02074fec(s32 index)
{
    if (data_ov001_020a04cc == 0) {
        return 0;
    }
    return *(u16 *)(data_ov001_020a04cc + index * 6 + 0xb4);
}
