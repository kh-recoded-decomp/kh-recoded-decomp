#include "nitro/types.h"

extern u32 func_ov001_0207f050();

void
func_ov001_0207fa24(u32 unused, u16 field66, u32 field68, u32 field6c)
{
    int context = func_ov001_0207f050();
    *(u16 *)(context + 0x66) = field66;
    *(u32 *)(context + 0x68) = field68;
    *(u32 *)(context + 0x6c) = field6c;
}
