#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern void func_ov001_0206a72c(s32 value);

u32 func_ov028_020bab68(void)
{
    u32 context = data_ov028_020bb3a0;

    func_ov001_0206a72c((s32)*(s8 *)(data_ov028_020bb3a0 + 8));
    *(u16 *)(context + 6) = *(u16 *)(context + 6) | 0x20;
    return 10;
}
