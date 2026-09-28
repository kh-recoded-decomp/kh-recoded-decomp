#include "nitro/types.h"

extern void func_020014f0(u32 context);

void func_ov001_0206f464(u32 context)
{
    s32 offset;
    s32 index;

    func_020014f0(context + 0xa8);
    index = 0;
    do {
        offset = index * 8;
        index = index + 1;
        *(u32 *)(context + offset + 0xdc) = 0;
    } while (index < 0x16);
}
