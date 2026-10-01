#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Collider {
    u8 pad_00[0x1c];
    int shapeType;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} Collider;

typedef struct Shape {
    u8 pad_00[4];
    VecFx32 max;
    VecFx32 min;
    int shapeType;
} Shape;

typedef struct Actor {
    u8 pad_00[0x10];
    Shape shape;
    u8 pad_30[0x20];
    s8 state;
    u8 pad_51;
    s8 cooldown;
    u8 pad_53;
    u16 flags;
} Actor;

typedef int (*CollideFunc)(Shape *shape, Collider *other, void *result, int flags);
typedef int (*CollideMovingFunc)(Shape *shape, Collider *other, void *result, int flags, VecFx32 *push);

extern CollideFunc data_020558a0[][6];
extern CollideMovingFunc data_02055930[][6];
extern void NegateVecFx32_0204aa40(VecFx32 *vec);

int TryCollideWithCollider_020a2c98(Actor *actor, Collider *other, void *result)
{
    VecFx32 reversed;
    VecFx32 push;
    int overlap;

    if (actor->flags & 8) {
        return 0;
    }
    if (actor->flags & 2) {
        return 0;
    }
    if (actor->cooldown > 0) {
        return 0;
    }
    if (actor->state == 0 && actor->shape.shapeType >= 0) {
        if (actor->shape.max.x >= other->min.x && actor->shape.min.x <= other->max.x &&
            actor->shape.max.z >= other->min.z && actor->shape.min.z <= other->max.z &&
            actor->shape.max.y >= other->min.y && actor->shape.min.y <= other->max.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                overlap = 2;
            } else {
                reversed = other->velocity;
                NegateVecFx32_0204aa40(&reversed);
                push = reversed;
                overlap = 1;
            }
        } else {
            overlap = 0;
        }
        if (overlap != 0) {
            if (overlap == 2) {
                return data_020558a0[actor->shape.shapeType][other->shapeType](&actor->shape, other, result, (other->shapeType == 2 ? 2 : 0) | 8);
            }
            return data_02055930[actor->shape.shapeType][other->shapeType](&actor->shape, other, result, 8, &push);
        }
        return 0;
    }
    return 0;
}
