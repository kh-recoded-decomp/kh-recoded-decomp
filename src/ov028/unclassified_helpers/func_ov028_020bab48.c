#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern void func_ov001_0206a72c(s32 value);

u32 func_ov028_020bab48(void)
{
    u32 context = g_fieldContext_020bb380;

    func_ov001_0206a72c((s32)*(s8 *)(g_fieldContext_020bb380 + 8));
    *(u16 *)(context + 6) = *(u16 *)(context + 6) | 0x20;
    return 10;
}
