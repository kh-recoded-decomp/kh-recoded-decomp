#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void func_0203f4fc(VecFx32 *out, const VecFx32 *v, fx32 scale);
extern void func_0203f4a8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

void ComputeVectorRejection_02040aec(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    fx32 dot = VEC_DotProduct_01ff9e6c(a, b);
    VecFx32 result;
    VecFx32 scaled;

    func_0203f4fc(&scaled, b, dot);
    func_0203f4a8(&result, a, &scaled);
    *out = result;
}
