#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void func_02048b30(VecFx32 *out, const VecFx32 *v, fx32 scale);

void ScaleAxisByDot_02048af0(VecFx32 *out, const VecFx32 *vec, const VecFx32 *axis)
{
    VecFx32 result;

    func_02048b30(&result, axis, VEC_DotProduct_01ff9e6c(vec, axis));
    *out = result;
}
