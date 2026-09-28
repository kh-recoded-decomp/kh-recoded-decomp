#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

fx32 BlendVectorsBySqrtComplement_0204b59c(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out)
{
    fx32 sqrtComplement = ComputeOneMinusSquareFraction_02049d6c(t);
    VecFx32 scaled = *a;
    func_0204a5e4(&scaled, t);
    *out = scaled;
    VEC_MultAdd_01ffa09c(sqrtComplement * factor, b, out, out);
    return sqrtComplement;
}
