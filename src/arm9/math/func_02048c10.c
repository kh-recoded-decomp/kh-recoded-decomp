#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32IfNegative_0204a6ac(VecFx32 *vec, s32 sign);

void func_02048c10(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    NegateVecFx32IfNegative_0204a6ac(&tmp, sign);
    *out = tmp;
}
