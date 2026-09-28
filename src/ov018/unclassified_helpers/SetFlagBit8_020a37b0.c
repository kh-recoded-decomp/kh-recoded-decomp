#include "nitro/types.h"

void SetFlagBit8_020a37b0(int object)
{
    *(u16 *)(object + 0x50) |= 0x100;
}
