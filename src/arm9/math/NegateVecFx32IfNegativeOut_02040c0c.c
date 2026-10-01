#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32IfNegative_02040c44(VecFx32 *vec, s32 sign);

void NegateVecFx32IfNegativeOut_02040c0c(VecFx32 *out, const VecFx32 *v, s32 sign)
{
    VecFx32 tmp = *v;
    NegateVecFx32IfNegative_02040c44(&tmp, sign);
    *out = tmp;
}
