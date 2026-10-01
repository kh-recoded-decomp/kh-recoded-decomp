#include "nitro/types.h"

extern int GetPackedBitMask_0202d4a0(int *bitWords, int bitIndex);
extern u8 *data_ov095_020c28c0;

BOOL IsEntryFlagSet_020c1320(int useSecondSet, int bitIndex)
{
    u8 *base = data_ov095_020c28c0;
    if (useSecondSet == 0) {
        base += 0x124;
    } else {
        base += 0x144;
    }
    return GetPackedBitMask_0202d4a0((int *)(base + 0x11000), bitIndex) != 0;
}
