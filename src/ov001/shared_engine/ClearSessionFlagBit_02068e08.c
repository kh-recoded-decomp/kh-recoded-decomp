#include "nitro/types.h"

extern void SetSessionStateBit_02068cfc(BOOL enable, u32 bit);

void ClearSessionFlagBit_02068e08(int index)
{
    SetSessionStateBit_02068cfc(0, index + 3);
}
