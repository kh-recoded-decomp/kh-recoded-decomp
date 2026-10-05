#include "nitro/types.h"

extern void SetSessionStateBit_02068cfc(BOOL enable, u32 bit);

void ReleaseSessionSlotBit_02068e18(int index)
{
    SetSessionStateBit_02068cfc(0, index + 4);
}
