#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void MultAddOut_02048c48(VecFx32 *dst, fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 tmp;
    VEC_MultAdd_01ffa09c(scale, v, add, &tmp);
    *dst = tmp;
}
