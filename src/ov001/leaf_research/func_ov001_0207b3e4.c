#include "nitro/types.h"

extern u32 func_ov001_0207a8fc();
extern void func_ov023_020b6c48(u32 x, u32 y);

extern u32 g_activePanel_020a04c8;

void func_ov001_0207b3e4(u32 x, u32 y)
{
    s32 panel;
    u32 ready;

    panel = g_activePanel_020a04c8;
    *(u32 *)(g_activePanel_020a04c8 + 0x50) = x;
    *(u32 *)(panel + 0x54) = y;
    ready = func_ov001_0207a8fc();
    if (ready != 0) {
        func_ov023_020b6c48(x, y);
    }
}
