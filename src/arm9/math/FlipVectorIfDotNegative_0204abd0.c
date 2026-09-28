#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);

fx32 FlipVectorIfDotNegative_0204abd0(VecFx32 *a, const VecFx32 *b)
{
    fx32 dot = VEC_DotProduct_01ff9e6c(a, b);
    if (dot < 0) {
        NegateVecFx32_0204aa40(a);
    }
    return dot;
}
