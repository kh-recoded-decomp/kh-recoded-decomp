#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern void WritePackedBits_0202d560(u32 *base, u32 bitOffset, u32 bitCount, u32 value);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value)
{
    if (bitOffset >= 0x3300)
    {
        WritePackedBits_0202d560((u32 *)(data_ov001_020a0460 + 0x28), bitOffset - 0x3300, bitCount, value);
        return;
    }
    WriteGlobalPackedBits_02027360(bitOffset, bitCount, value);
}
