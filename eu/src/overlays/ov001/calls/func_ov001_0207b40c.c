#include "nitro/types.h"

extern u32 func_ov001_0207a8fc();
extern void PrepareMenuScreenEntry(u32 x, u32 y);

extern u32 data_ov001_020a04e8;

void func_ov001_0207b40c(u32 x, u32 y)
{
    s32 panel;
    u32 ready;

    panel = data_ov001_020a04e8;
    *(u32 *)(data_ov001_020a04e8 + 0x50) = x;
    *(u32 *)(panel + 0x54) = y;
    ready = func_ov001_0207a8fc();
    if (ready != 0) {
        PrepareMenuScreenEntry(x, y);
    }
}
