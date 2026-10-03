#include "nitro/fx_types.h"

extern void VEC_Normalize_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

fx32 CosAngleXZ_020bc634(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 flatA;
    VecFx32 flatB;

    flatA.x = a->x;
    flatA.y = 0;
    flatA.z = a->z;
    flatB.x = b->x;
    flatB.y = 0;
    flatB.z = b->z;
    if (flatA.x == 0 && flatA.y == 0 && flatA.z == 0) {
        return -0x1000;
    }
    if (flatB.x == 0 && flatB.y == 0 && flatB.z == 0) {
        return -0x1000;
    }
    VEC_Normalize_01ff9f88(&flatA, &flatA);
    VEC_Normalize_01ff9f88(&flatB, &flatB);
    return VEC_DotProduct_01ff9e6c(&flatA, &flatB);
}
