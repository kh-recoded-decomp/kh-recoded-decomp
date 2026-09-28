#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern s32 func_ov001_0206a814(void);

u32 func_ov028_020bac3c(void)
{
    s32 ready = func_ov001_0206a814();

    if (ready != 0) {
        *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) & 0xffbf;
        return 7;
    }
    return 0xffffffff;
}
