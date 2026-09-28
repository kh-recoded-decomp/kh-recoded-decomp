#include "nitro/types.h"

extern u16 data_ov001_0209e0cc[][4];
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);

u32 ReadPackedRecord_0207ebac(int row, int column)
{
    return ReadGlobalPackedBits_02027348(data_ov001_0209e0cc[row][column], 0x14);
}
