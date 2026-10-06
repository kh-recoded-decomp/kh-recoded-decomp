#include "nitro/types.h"

extern u32 data_ov030_020bd020;

void func_ov030_020bb460(BOOL enable)
{
    if (enable != 0) {
        *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) | 4;
        return;
    }
    *(u16 *)(data_ov030_020bd020 + 6) = *(u16 *)(data_ov030_020bd020 + 6) & 0xfffb;
}
