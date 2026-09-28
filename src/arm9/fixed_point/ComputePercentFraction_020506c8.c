#include "nitro/types.h"

extern s32 func_02023dbc(s32 numerator, s32 denominator);

void ComputePercentFraction_020506c8(u8 *obj)
{
    func_02023dbc((u32)*(u8 *)(obj + 0x2c63) << 0xc, 100);
}
