#include "nitro/types.h"

extern u32 func_ov001_0207f028();

void
func_ov001_0207f9fc(u32 unused, u16 field66, u32 field68, u32 field6c)
{
    int context = func_ov001_0207f028();
    *(u16 *)(context + 0x66) = field66;
    *(u32 *)(context + 0x68) = field68;
    *(u32 *)(context + 0x6c) = field6c;
}
