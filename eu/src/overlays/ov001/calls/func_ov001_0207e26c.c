#include "nitro/types.h"

extern s32 func_0202a9e4(s32 range);
extern void BindHudNodeOffsets(u8 *context);

void func_ov001_0207e26c(u8 *context, s32 flag)
{
    s32 random;

    random = func_0202a9e4(4);
    *(s16 *)(context + 0x24) =
        (s16)((s32)(random * 0x10000 + ((u32)(random * 0x10000 >> 1) >> 0x1e)) >> 2);
    *(u16 *)(context + 0x26) = 1;
    *(u16 *)(context + 0x28) = 0x400;
    if (flag != 0) {
        BindHudNodeOffsets(context);
    }
}
