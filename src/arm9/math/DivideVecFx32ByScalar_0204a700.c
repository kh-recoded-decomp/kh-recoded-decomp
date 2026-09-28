#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s32 func_02023dbc(s32 numerator, s32 denominator);

void DivideVecFx32ByScalar_0204a700(VecFx32 *vec, s32 divisor)
{
    vec->x = func_02023dbc(vec->x, divisor);
    vec->y = func_02023dbc(vec->y, divisor);
    vec->z = func_02023dbc(vec->z, divisor);
}
