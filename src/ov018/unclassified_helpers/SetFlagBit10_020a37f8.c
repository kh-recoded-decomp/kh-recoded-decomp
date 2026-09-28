#include "nitro/types.h"

void SetFlagBit10_020a37f8(int object)
{
    *(u16 *)(object + 0x50) |= 0x400;
}
