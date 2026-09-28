#include "nitro/types.h"

extern u32 data_ov001_020a0470;

u8 func_ov001_02068918(s32 *output)
{
    u8 *ctx;
    s32 i;
    u32 value;

    ctx = (u8 *)data_ov001_020a0470;
    i = 0;
    do {
        value = ctx[i + 0x10a];
        if (value == 0xff) {
            value = 0xffffffff;
        }
        output[i] = value;
        i = i + 1;
    } while (i < 0x16);
    return ctx[0x109];
}
