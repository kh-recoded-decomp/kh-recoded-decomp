#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_0207ed2c(void);
extern void func_ov001_02087178(void);

u32 func_ov030_020ba5c8(void)
{
    s32 ready;

    ready = func_ov001_0207ed2c();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_02087178();
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x8000;
    return 3;
}
