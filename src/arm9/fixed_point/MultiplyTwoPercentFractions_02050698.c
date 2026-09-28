#include "nitro/types.h"

extern s32 FixedPointMultiply12(s32 left, s32 right);
extern s32 func_02023dbc(s32 numerator, s32 denominator);

void MultiplyTwoPercentFractions_02050698(u8 *obj)
{
    s32 inverseFrac = func_02023dbc((100 - (u32)*(u8 *)(obj + 0x2c65)) * 0x1000, 100);
    s32 directFrac = func_02023dbc((u32)*(u8 *)(obj + 0x2c63) << 0xc, 100);
    FixedPointMultiply12(inverseFrac, directFrac);
}
