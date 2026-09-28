#include "nitro/types.h"

extern s32 func_0202a9d0(s32 range);
extern void func_ov001_0207e1c0(u8 *context);

void func_ov001_0207e244(u8 *context, s32 flag)
{
    s32 random;

    random = func_0202a9d0(4);
    *(s16 *)(context + 0x24) =
        (s16)((s32)(random * 0x10000 + ((u32)(random * 0x10000 >> 1) >> 0x1e)) >> 2);
    *(u16 *)(context + 0x26) = 1;
    *(u16 *)(context + 0x28) = 0x400;
    if (flag != 0) {
        func_ov001_0207e1c0(context);
    }
}
