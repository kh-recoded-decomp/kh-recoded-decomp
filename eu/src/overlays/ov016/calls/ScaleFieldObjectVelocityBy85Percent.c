#include "nitro/types.h"

extern s32 _s32_div_f(s32 numerator, s32 denominator);

void ScaleFieldObjectVelocityBy85Percent(s32 *vector)
{
    vector[0] = _s32_div_f(vector[0] * 0x55, 100);
    vector[1] = _s32_div_f(vector[1] * 0x55, 100);
    vector[2] = _s32_div_f(vector[2] * 0x55, 100);
}
