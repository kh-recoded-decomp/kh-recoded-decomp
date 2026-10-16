#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    u8 unknown00[0x1c];
    s32 kind;
    VecFx32 velocity;
    VecFx32 maximum;
    VecFx32 minimum;
} CollisionShape;

typedef struct ElevatorCollisionBody {
    u8 unknown00[0x18];
    u8 shapeData[4];
    VecFx32 maximum;
    VecFx32 minimum;
    s32 kind;
} ElevatorCollisionBody;

typedef int (*CollisionTest)(void *shapeData, CollisionShape *other,
                             void *result, u32 flags);
typedef int (*CollisionSweep)(void *shapeData, CollisionShape *other,
                              void *result, u32 flags, VecFx32 *push);

extern CollisionTest const gCollisionTestDispatch[][6];
extern CollisionSweep const gCollisionSweepDispatch[][6];
extern void NegateVecFx32(VecFx32 *vector);

#pragma optimization_level 2
BOOL CollideElevatorWithShape(ElevatorCollisionBody *body, CollisionShape *other,
                             void *result)
{
    VecFx32 reversed;
    VecFx32 push;
    int overlap;
    int hit;
    u32 flags;

    if (body->kind >= 0) {
        if (body->maximum.x >= other->minimum.x && body->minimum.x <= other->maximum.x &&
            body->maximum.z >= other->minimum.z && body->minimum.z <= other->maximum.z &&
            body->maximum.y >= other->minimum.y && body->minimum.y <= other->maximum.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                overlap = 2;
            } else {
                reversed = other->velocity;
                NegateVecFx32(&reversed);
                push = reversed;
                overlap = 1;
            }
        } else {
            overlap = 0;
        }
        if (overlap != 0) {
            if (overlap == 2) {
                flags = 2;
                if (other->kind != 2) {
                    flags = 0;
                }
                hit = gCollisionTestDispatch[body->kind][other->kind](
                    body->shapeData, other, result, flags | 8);
            } else {
                hit = gCollisionSweepDispatch[body->kind][other->kind](
                    body->shapeData, other, result, 8, &push);
            }
        } else {
            hit = 0;
        }
        if (hit != 0) {
            return TRUE;
        }
    }
    return FALSE;
}
