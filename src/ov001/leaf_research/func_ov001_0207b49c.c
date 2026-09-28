#include "nitro/types.h"

extern u32 func_ov001_0207a8fc(s32 panel);
extern void func_ov023_020b6e40(u32 a, u32 b, u32 c);

extern u32 g_activePanel_020a04c8;

void func_ov001_0207b49c(u32 a, u32 b, u32 c)
{
    u32 ready;

    ready = func_ov001_0207a8fc(g_activePanel_020a04c8);
    if (ready != 0) {
        func_ov023_020b6e40(a, b, c);
    }
}
