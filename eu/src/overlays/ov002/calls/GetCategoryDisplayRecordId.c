#pragma opt_propagation off

#include "src/overlays/ov002/MenuRecordCategories.h"

extern u8 *GetRecordFlagBits(void);

int GetCategoryDisplayRecordId(int category, int oneBasedIndex, int includeLocked)
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
    if (oneBasedIndex >= gMenuRecordCategoryCounts[category])
        return 0;
    if (!includeLocked) {
        bitIndex = oneBasedIndex + gMenuRecordCategoryFlagBitOffsets[category];
        byteIndex = bitIndex >> 3;
        bit = (u8)(bitIndex - (byteIndex << 3));
        mask = (u8)(1 << bit);
        if (!(GetRecordFlagBits()[bitIndex >> 3] & mask))
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
