#include "nitro/types.h"

extern void func_0202a1c4(u32 handle);
extern void func_ov027_020b7dfc(u32 context);
extern void func_ov027_020b9a60(u32 context);

void func_ov001_0206f174(u32 context)
{
    func_ov027_020b7dfc(context + 0x1c);
    func_ov027_020b9a60(context);
    func_0202a1c4(*(u32 *)(context + 0x470));
    func_0202a1c4(*(u32 *)(context + 0x614));
    *(u32 *)(context + 0x614) = 0;
}
