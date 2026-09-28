#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern s32 func_ov001_0207ed2c(void);
extern void func_ov001_02087178(s32 value);

u32 func_ov028_020ba700(void)
{
    s32 value = func_ov001_0207ed2c();

    if (value != 0) {
        func_ov001_02087178(value);
        *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) | 0x8000;
        return 3;
    }
    return 0xffffffff;
}
