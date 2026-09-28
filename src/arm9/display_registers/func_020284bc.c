#include "nitro/types.h"

extern void GFXi_EnqueueCommand_02014090(u32 a, u32 b, u32 c, u32 d);

void func_020284bc(u32 context)
{
    u32 sub = *(u32 *)(context + 0x5c);
    GFXi_EnqueueCommand_02014090(0xb, 0, sub + 0xc, *(u32 *)(sub + 8));
}
