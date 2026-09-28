#include "nitro/fx_types.h"

void Vec3SubScalar_0204a55c(VecFx32 *v, fx32 amount)
{
    v->x = v->x - amount;
    v->y = v->y - amount;
    v->z = v->z - amount;
}
