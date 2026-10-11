#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionShape {
    const CollisionSphere *sphere;
} CollisionShape;

typedef struct CollisionHit {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 kind;
} CollisionHit;

extern BOOL TestSphereAgainstPoint(const VecFx32 *point,
    const CollisionSphere *sphere, CollisionHit *hit, u32 flags);

/* Sphere overlap is a center-point test against the sum of the radii. */
BOOL TestSphereAgainstSphere(const CollisionShape *firstShape,
    const CollisionShape *secondShape, CollisionHit *hit, u32 flags)
{
    const CollisionSphere *first = firstShape->sphere;
    CollisionSphere expanded = *secondShape->sphere;
    expanded.radius += first->radius;
    return TestSphereAgainstPoint(&first->center, &expanded, hit, flags);
}
