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

extern BOOL TestSphereAgainstPoint_0203d3d0(const VecFx32 *point,
    const CollisionSphere *sphere, CollisionHit *hit, u32 flags);


BOOL TestSphereAgainstSphere_0203b6b4(const CollisionShape *firstShape,
    const CollisionShape *secondShape, CollisionHit *hit, u32 flags)
{
    const CollisionSphere *first = firstShape->sphere;
    CollisionSphere expanded = *secondShape->sphere;
    expanded.radius += first->radius;
    return TestSphereAgainstPoint_0203d3d0(&first->center, &expanded, hit, flags);
}
