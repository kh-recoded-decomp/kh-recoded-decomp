#include "nitro/types.h"

extern s32 func_02023dbc(s32 numerator, s32 denominator);

void func_ov016_020a34c8(s32 *vector)
{
    vector[0] = func_02023dbc(vector[0] * 0x55, 100);
    vector[1] = func_02023dbc(vector[1] * 0x55, 100);
    vector[2] = func_02023dbc(vector[2] * 0x55, 100);
}
