#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct OrientedBox {
    VecFx32 center;
    VecFx32 halfExtents;
} OrientedBox;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct CollisionObject {
    u8 pad_00[0xc];
    u8 flags;
    u8 hasSweep;
    u8 pad_0e[0xa];
    VecFx32 position;
    CollisionShape shape;
    VecFx32 sweepDelta;
    Box sweptBounds;
    u8 pad_68[0x20];
} CollisionObject;

extern void func_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z) {
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void SetCollisionObjectPosition_02033f48(CollisionObject *object, const VecFx32 *position) {
    object->position = *position;
    object->flags |= 1;
    if (object->shape.kind == 1) {
        if (!object->hasSweep) {
            VecFx32 center = MakeVec(position->x, position->y + ((OrientedBox *)object->shape.data)->halfExtents.y, position->z);
            func_0203afa0(&object->shape, &center);
        } else {
            VecFx32 center = MakeVec(position->x, position->y + ((OrientedBox *)object->shape.data)->halfExtents.y, position->z);
            func_0203afa0(&object->shape, &center);
            OffsetBoxByDelta_0203ac70(&object->shape.bounds, &object->sweptBounds, &object->sweepDelta);
        }
    } else {
        if (!object->hasSweep) {
            func_0203afa0(&object->shape, position);
        } else {
            func_0203afa0(&object->shape, position);
            OffsetBoxByDelta_0203ac70(&object->shape.bounds, &object->sweptBounds, &object->sweepDelta);
        }
    }
}
