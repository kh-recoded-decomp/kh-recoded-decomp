#include "nitro/types.h"

extern u32 GetFieldObjectClassAtIndex();

void
SetFieldObjectClassActivationFlagBit(u32 unused, u8 value)
{
    int context = GetFieldObjectClassAtIndex();
    *(u8 *)(context + 0x81) = value;
}
