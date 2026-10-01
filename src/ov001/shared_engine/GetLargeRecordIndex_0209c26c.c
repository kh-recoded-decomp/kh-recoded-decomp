#include "nitro/types.h"

typedef struct StageLayout {
    u8 pad_000[0x4b14];
    u8 largeRecords[1];
} StageLayout;

extern StageLayout *data_ov001_020a0508;
extern u32 UnsignedDivide_02023fc8(u32 numerator, u32 denominator);

u16 GetLargeRecordIndex_0209c26c(u8 *record)
{
    return UnsignedDivide_02023fc8(record - data_ov001_020a0508->largeRecords, 0x3c8) + 1;
}
