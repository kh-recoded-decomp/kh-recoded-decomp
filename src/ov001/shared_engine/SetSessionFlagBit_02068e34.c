#include "nitro/types.h"

extern void SetSessionStateBit_02068cfc(BOOL enable, u32 bit);

void SetSessionFlagBit_02068e34(int index)
{
    SetSessionStateBit_02068cfc(1, index + 3);
}
