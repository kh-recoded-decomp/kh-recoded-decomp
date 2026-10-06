#include "nitro/types.h"

extern void SetSessionStateBit(BOOL enable, u32 bit);

void ReleaseSessionSlotBit(int index)
{
    SetSessionStateBit(0, index + 4);
}
