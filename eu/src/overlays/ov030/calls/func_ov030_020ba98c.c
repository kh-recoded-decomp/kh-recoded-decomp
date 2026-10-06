#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern s32 func_ov001_0206685c(void);
extern s32 IsScreenModeIdle(void);
extern void BeginScreenFadeOut(s32 arg);

u32 func_ov030_020ba98c(void)
{
    u32 ctx;
    s32 ready;

    ctx = data_ov030_020bd020;
    if (((*(u16 *)(data_ov030_020bd020 + 6) & 0x10) == 0) &&
        (ready = func_ov001_0206685c(), ready != 0)) {
        return 0xffffffff;
    }
    ready = IsScreenModeIdle();
    if (ready == 0) {
        return 0xffffffff;
    }
    BeginScreenFadeOut((s32)*(s8 *)(ctx + 8));
    return 0x10;
}
