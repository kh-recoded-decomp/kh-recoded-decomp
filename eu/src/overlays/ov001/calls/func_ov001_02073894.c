#include "nitro/types.h"

extern void BlitNibbleRunPadded(u32 tileBase, u32 row, u32 width, u32 height,
                                u32 rowOffset, u32 column, const u8 *pixels);

extern const u8 data_ov001_0209de06[][4];

void func_ov001_02073894(u32 tileBase, u32 row, s32 patternIndex)
{
    BlitNibbleRunPadded(tileBase, row, 4, 0x30, 0, 3, data_ov001_0209de06[patternIndex]);
}
