#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32_0204aa40(VecFx32 *vec);

void NegateVecFx32Into_0203f9b0(VecFx32 *dest, const VecFx32 *src)
{
    VecFx32 tmp = *src;
    NegateVecFx32_0204aa40(&tmp);
    *dest = tmp;
}
