#include "nitro/types.h"

extern u16 data_ov001_0209e0cc[][4];
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

void WritePackedRecord_0207ebd0(int row, int column, u32 value)
{
    WriteGlobalPackedBits_02027360(data_ov001_0209e0cc[row][column], 0x14, value);
}
