#ifndef KH_RECODED_COLLISION_GEOMETRY_H
#define KH_RECODED_COLLISION_GEOMETRY_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

/* The ROM stores maximum first: SphereToBounds writes center +/- radius. */
typedef struct CollisionBounds {
    VecFx32 max;
    VecFx32 min;
} CollisionBounds;

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionShape {
    void *geometry;
    CollisionBounds bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptCollisionShape {
    CollisionShape shape;
    VecFx32 delta;
    CollisionBounds sweptBounds;
} SweptCollisionShape;

typedef char CollisionBoundsSizeCheck[sizeof(CollisionBounds) == 0x18 ? 1 : -1];
typedef char CollisionSphereSizeCheck[sizeof(CollisionSphere) == 0x10 ? 1 : -1];
typedef char CollisionShapeSizeCheck[sizeof(CollisionShape) == 0x20 ? 1 : -1];
typedef char SweptCollisionShapeSizeCheck[sizeof(SweptCollisionShape) == 0x44 ? 1 : -1];

extern void MakeSphereShape(CollisionShape *shape, CollisionSphere *sphere,
                           const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const CollisionBounds *source, CollisionBounds *out,
                             const VecFx32 *delta);

#endif
