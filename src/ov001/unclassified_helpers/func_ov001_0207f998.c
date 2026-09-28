#include "nitro/types.h"

extern u32 func_ov001_0207f028();

void
func_ov001_0207f998(u32 unused, u8 value)
{
    int context = func_ov001_0207f028();
    *(u8 *)(context + 0x81) = value;
}
