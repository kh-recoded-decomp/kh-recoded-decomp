#include "nitro/types.h"

typedef struct PackedValueBlock {
    u32 savedByte;
    u16 values[3];
} PackedValueBlock;

typedef struct BitOffsetTable {
    u32 offsets[3];
} BitOffsetTable;

extern const BitOffsetTable data_02055a38;
extern u16 data_020608d4[3];
extern PackedValueBlock data_020608d0;
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);

void StoreSelectionPackedValues_020505b4(const u16 *values)
{
    BitOffsetTable table = data_02055a38;
    int i;

    MI_CpuCopy8_01ff89a8(values, data_020608d4, sizeof(data_020608d4));
    for (i = 0; i < 3; i++) {
        WriteGlobalPackedBits_02027360(table.offsets[i], 0x10, data_020608d0.values[i]);
    }
}
