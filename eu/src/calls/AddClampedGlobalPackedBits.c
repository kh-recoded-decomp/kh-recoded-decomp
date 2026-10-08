#include "nitro/types.h"

extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

BOOL AddClampedGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 amount, u32 maximum)
{
    BOOL wasClamped;
    u32 value;

    value = ReadGlobalPackedBits(bitOffset, bitCount);
    wasClamped = FALSE;
    value += amount;

    if (maximum < value) {
        wasClamped = TRUE;
    } else {
        maximum = value;
    }
    WriteGlobalPackedBits(bitOffset, bitCount, maximum);
    return wasClamped;
}
