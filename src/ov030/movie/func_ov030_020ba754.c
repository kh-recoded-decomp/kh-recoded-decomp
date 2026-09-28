#include "nitro/types.h"

extern u32 g_moviePlayerCtx_020bd000;
extern s32 func_ov001_0207b688(void);
extern void StoreToGlobalPtr4Field28_0202a778(u32 value);

u32 func_ov030_020ba754(void)
{
    s32 ready;

    ready = func_ov001_0207b688();
    if (ready == 0) {
        return 0xffffffff;
    }
    if ((*(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 1) != 0) {
        *(u16 *)(g_moviePlayerCtx_020bd000 + 6) = *(u16 *)(g_moviePlayerCtx_020bd000 + 6) & 0xfffe;
    }
    StoreToGlobalPtr4Field28_0202a778(0);
    return 7;
}
