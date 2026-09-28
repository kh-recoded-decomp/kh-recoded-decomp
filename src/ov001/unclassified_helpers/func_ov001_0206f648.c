#include "nitro/types.h"

extern void func_020014f0(u32 context);
extern void func_0202a1c4(u32 handle);
extern void func_0205206c(u32 context, u32 count);

void func_ov001_0206f648(u32 context)
{
    s32 index;

    func_020014f0(context + 0x18c);
    func_020014f0(context + 0x1c0);
    func_0202a1c4(*(u32 *)(context + 500));
    index = 0;
    do {
        func_0202a1c4(*(u32 *)(context + index * 4 + 0xb34));
        index = index + 1;
    } while (index < 0x200);
    func_0205206c(context + 0x1338, 0xe);
}
