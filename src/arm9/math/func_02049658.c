#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32IfNegative_0204abf4(VecFx32 *vec, s32 sign);

void func_02049658(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    NegateVecFx32IfNegative_0204abf4(&tmp, sign);
    *out = tmp;
}
