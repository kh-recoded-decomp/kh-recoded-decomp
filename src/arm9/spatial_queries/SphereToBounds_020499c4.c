#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

extern void Vec3AddScalar_0204a534(VecFx32 *v, fx32 amount);
extern void Vec3SubScalar_0204a55c(VecFx32 *v, fx32 amount);

void SphereToBounds_020499c4(Sphere **spherePtr, VecFx32 *bounds)
{
    Sphere *sphere = *spherePtr;

    bounds[0] = sphere->center;
    bounds[1] = bounds[0];
    Vec3AddScalar_0204a534(&bounds[0], sphere->radius);
    Vec3SubScalar_0204a55c(&bounds[1], sphere->radius);
}
