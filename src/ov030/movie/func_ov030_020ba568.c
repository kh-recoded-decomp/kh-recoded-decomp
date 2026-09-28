#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_02063620(void);
extern void func_020365a4(void);

u32 func_ov030_020ba568(void)
{
    s32 ready;

    ready = func_ov001_02063620();
    if (ready != 0) {
        return 0xffffffff;
    }
    func_020365a4();
    *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) | 0x8000;
    return 1;
}
