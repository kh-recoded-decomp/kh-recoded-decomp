#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32_0204aa40(VecFx32 *vec);

void NegateVecFx32Out_02047fc8(VecFx32 *out, const VecFx32 *src)
{
    VecFx32 tmp = *src;
    NegateVecFx32_0204aa40(&tmp);
    *out = tmp;
}
