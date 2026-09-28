#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b)
{
    fx32 dot = VEC_DotProduct_01ff9e6c(a, b);
    if (dot < 0) {
        dot = -dot;
    }
    return dot;
}
