#include "nitro/types.h"

extern void SetSessionStateBit(BOOL enable, u32 bit);

void SetSessionFlagBit(int index)
{
    SetSessionStateBit(1, index + 3);
}
