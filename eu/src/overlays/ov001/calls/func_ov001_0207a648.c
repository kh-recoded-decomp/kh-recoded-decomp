#include "nitro/types.h"

extern u32 data_ov001_020a04e4;

u32 func_ov001_0207a648(void)
{
    switch (*(u32 *)(data_ov001_020a04e4 + 0xc)) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
        return 1;
    case 4:
        return 2;
    case 5:
    case 6:
        return 3;
    case 7:
        return 4;
    default:
        return 0;
    }
}
