#include "nitro/types.h"

typedef struct StageLayout {
    u8 pad_000[0x13d14];
    u8 smallRecords[1];
} StageLayout;

extern StageLayout *data_ov001_020a0508;
extern u32 UnsignedDivide_02023fc8(u32 numerator, u32 denominator);

u16 GetSmallRecordIndex_0209c248(u8 *record)
{
    return UnsignedDivide_02023fc8(record - data_ov001_020a0508->smallRecords, 0x1c) + 1;
}
