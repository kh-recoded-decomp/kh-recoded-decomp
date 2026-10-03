#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);

int CountUnlockedTiers_020c4988(void)
{
    int count;

    for (count = 0; count < 8; count++) {
        if (!IsGlobalPackedBitSet_02027304(count + 0xa0b)) {
            break;
        }
    }
    return count;
}