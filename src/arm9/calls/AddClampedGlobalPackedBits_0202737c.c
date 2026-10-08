#include "nitro/types.h"

extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

BOOL AddClampedGlobalPackedBits_0202737c(u32 bitOffset, u32 bitCount, u32 amount, u32 maximum)
{
    BOOL wasClamped;
    u32 value;

    value = ReadGlobalPackedBits_02027348(bitOffset, bitCount);
    wasClamped = FALSE;
    value += amount;

    if (maximum < value) {
        wasClamped = TRUE;
    } else {
        maximum = value;
    }
    WriteGlobalPackedBits_02027360(bitOffset, bitCount, maximum);
    return wasClamped;
}
