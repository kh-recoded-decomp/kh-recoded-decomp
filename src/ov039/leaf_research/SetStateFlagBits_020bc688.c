#include "nitro/types.h"

extern int data_ov039_020bea00;

void SetStateFlagBits_020bc688(u8 clearMask, u8 setBits)
{
    int base = data_ov039_020bea00;

    *(u8 *)(base + 0xca22) = setBits | (*(u8 *)(base + 0xca22) & ~clearMask);
}
