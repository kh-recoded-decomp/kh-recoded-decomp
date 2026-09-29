#include "nitro/types.h"

extern void func_ov001_02073758(u32 tileBase, u32 row, u32 width, u32 height,
                                u32 rowOffset, u32 column, const u8 *pixels);

extern const u8 data_ov001_0209ddf2[][4];

void func_ov001_02073870(u32 tileBase, u32 row, s32 patternIndex)
{
    func_ov001_02073758(tileBase, row, 4, 0x16, 1, 1, data_ov001_0209ddf2[patternIndex]);
}
