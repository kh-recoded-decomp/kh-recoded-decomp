#include "src/collision/CollisionGeometry.h"

extern void Vec3AddScalar(VecFx32 *value, fx32 amount);
extern void Vec3SubScalar(VecFx32 *value, fx32 amount);

void SphereToBounds(CollisionShape *shape, CollisionBounds *bounds)
{
    CollisionSphere *sphere = shape->geometry;

    bounds->max = sphere->center;
    bounds->min = bounds->max;
    Vec3AddScalar(&bounds->max, sphere->radius);
    Vec3SubScalar(&bounds->min, sphere->radius);
}
