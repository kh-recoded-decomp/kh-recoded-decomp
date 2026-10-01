#include "nitro/types.h"

extern void SetPackedBit_0202d44c(int *bitWords, int bitIndex);
extern u8 *data_ov095_020c28c0;

void SetEntryFlag_020c1354(int useSecondSet, int bitIndex)
{
    u8 *base = data_ov095_020c28c0;
    if (useSecondSet == 0) {
        base += 0x124;
    } else {
        base += 0x144;
    }
    SetPackedBit_0202d44c((int *)(base + 0x11000), bitIndex);
}
