#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 BlendVectorsBySqrtComplement_0204b59c(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out);

void BlendVectorsBySqrtComplementPositive_02048bbc(VecFx32 *a, const VecFx32 *b, fx32 t, VecFx32 *out)
{
    BlendVectorsBySqrtComplement_0204b59c(a, b, t, 1, out);
}
