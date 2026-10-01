#include "nitro/types.h"

typedef struct StageLayout {
    u8 pad_000[0x210];
    int baseOffset;
} StageLayout;

extern StageLayout *data_ov001_020a0508;
extern u32 UnsignedDivide_02023fc8(u32 numerator, u32 denominator);

u16 GetStageRowIndex_0209c228(int offset)
{
    return UnsignedDivide_02023fc8(offset - data_ov001_020a0508->baseOffset, 0x1c8) + 1;
}
