#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst)
{
    dst->x = FX_MUL(scale, src->x);
    dst->y = FX_MUL(scale, src->y);
    dst->z = FX_MUL(scale, src->z);
}
