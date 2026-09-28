#include "nitro/types.h"

extern void func_020014f0(u32 context);
extern void func_0202a1c4(u32 handle);
extern void func_ov027_020ba294(u32 context);

void func_ov001_0206f2f8(u32 context)
{
    func_ov027_020ba294(context + 0x50c);
    func_0202a1c4(*(u32 *)(context + 0x5c0));
    *(u32 *)(context + 0x5c0) = 0;
    func_020014f0(context + 0x584);
}
