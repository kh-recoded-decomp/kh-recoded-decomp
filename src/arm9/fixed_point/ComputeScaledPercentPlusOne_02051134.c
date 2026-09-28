#include "nitro/types.h"

extern u8 *data_0205fe0c;
extern s32 func_02023dbc(s32 numerator, s32 denominator);

int ComputeScaledPercentPlusOne_02051134(void)
{
    s32 result = func_02023dbc((u32)*(u8 *)(data_0205fe0c + 0x2c65) * 0xf000, 0x5a);
    return result + 0x1000;
}
