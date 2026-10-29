#include "src/collision/CollisionGeometry.h"

typedef void (*ShapeBoundsFunc)(CollisionShape *shape, CollisionBounds *bounds);

extern const ShapeBoundsFunc gCollisionBoundsDispatch[];

static inline void SetShapeCenter(CollisionShape *shape, const VecFx32 *center)
{
    ((CollisionSphere *)shape->geometry)->center = *center;
}

void MakeSphereShape(CollisionShape *shape, CollisionSphere *sphere, const VecFx32 *center, fx32 radius)
{
    shape->geometry = sphere;
    sphere->radius = radius;
    shape->kind = 0;
    SetShapeCenter(shape, center);
    gCollisionBoundsDispatch[0](shape, &shape->bounds);
}
