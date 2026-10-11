#pragma opt_propagation off

#include "nitro/types.h"

extern const u8 gMenuRecordCategoryCounts_0206ada0[20];

extern const u16 gMenuRecordCategoryFlagBitOffsets_0206adb4[21];

int GetCategoryDisplayRecordId_02068498(int category, int oneBasedIndex, int includeLocked);

extern u8 *GetRecordFlagBits_02066fb0(void);

int GetCategoryDisplayRecordId_02068498(int category, int oneBasedIndex, int includeLocked)
{
    int bitIndex;
    int byteIndex;
    int bit;
    u8 mask;
    int base;
    if (category >= 20)
        return 0;
    oneBasedIndex--;
    if (oneBasedIndex < 0)
        return 0;
    if (oneBasedIndex >= gMenuRecordCategoryCounts_0206ada0[category])
        return 0;
    if (!includeLocked) {
        bitIndex = oneBasedIndex + gMenuRecordCategoryFlagBitOffsets_0206adb4[category];
        byteIndex = bitIndex >> 3;
        bit = (u8)(bitIndex - (byteIndex << 3));
        mask = (u8)(1 << bit);
        if (!(GetRecordFlagBits_02066fb0()[bitIndex >> 3] & mask))
            return 0;
    }
    if (category != 19)
        base = (category + 1) * 10000;
    else
        base = 200000;
    if (category == 5)
        oneBasedIndex++;
    return base + oneBasedIndex;
}
