#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u32 ReadPackedBitField_0202d4c4(u32 *words, u32 startBit, u32 fieldWidth);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);

u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount)
{
    if (bitOffset >= 0x3300) {
        return ReadPackedBitField_0202d4c4((u32 *)(data_ov001_020a0460 + 0x28), bitOffset - 0x3300, bitCount);
    }
    return ReadGlobalPackedBits_02027348(bitOffset, bitCount);
}
