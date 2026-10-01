#include "nitro/types.h"

extern void ClearPackedBit_0202d474(int *bitWords, int bitIndex);
extern u8 *data_ov095_020c28c0;

void ClearEntryFlag_020c137c(int useSecondSet, int bitIndex)
{
    u8 *base = data_ov095_020c28c0;
    if (useSecondSet == 0) {
        base += 0x124;
    } else {
        base += 0x144;
    }
    ClearPackedBit_0202d474((int *)(base + 0x11000), bitIndex);
}
