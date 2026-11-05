#include "nitro/types.h"

extern u32 GetFieldObjectClassAtIndex();

void
func_ov001_0207f9c0(u32 unused, u8 value)
{
    int context = GetFieldObjectClassAtIndex();
    *(u8 *)(context + 0x81) = value;
}
