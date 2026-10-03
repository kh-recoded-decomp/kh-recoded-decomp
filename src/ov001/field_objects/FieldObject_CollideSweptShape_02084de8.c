#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 maxX, maxY, maxZ;
    s32 minX, minY, minZ;
} Box;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct CollisionActor {
    u8 pad_000[0x130];
    SweptShape body;
} CollisionActor;

typedef struct ColliderObject {
    u8 pad_00[0x34];
    s32 slot;
    u8 actorId;
    u8 pad_39[0x1f];
    void *active;
} ColliderObject;

typedef int (*StaticCollideFn)(CollisionShape *a, SweptShape *b, void *result, int flags);
typedef int (*MovingCollideFn)(CollisionShape *a, SweptShape *b, void *result, int flags, VecFx32 *relative);

extern StaticCollideFn data_020558a0[][6];
extern MovingCollideFn data_02055930[][6];
extern CollisionActor *func_02036240(u32 id);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

int FieldObject_CollideSweptShape_02084de8(ColliderObject *object, SweptShape *other, void *result)
{
    CollisionActor *actor = func_02036240(object->actorId);
    VecFx32 diff;
    VecFx32 relative;
    int mode;

    if (object->active == NULL) {
        return 0;
    }
    if (object->slot >= 0) {
        if (actor->body.sweptBounds.maxX >= other->sweptBounds.minX
            && actor->body.sweptBounds.minX <= other->sweptBounds.maxX
            && actor->body.sweptBounds.maxZ >= other->sweptBounds.minZ
            && actor->body.sweptBounds.minZ <= other->sweptBounds.maxZ
            && actor->body.sweptBounds.maxY >= other->sweptBounds.minY
            && actor->body.sweptBounds.minY <= other->sweptBounds.maxY) {
            if (other->delta.x == 0 && other->delta.y == 0 && other->delta.z == 0) {
                if (actor->body.delta.x == 0 && actor->body.delta.y == 0 && actor->body.delta.z == 0) {
                    mode = 2;
                } else {
                    relative = actor->body.delta;
                    mode = 1;
                }
            } else {
                VEC_Subtract_01ff9e3c(&actor->body.delta, &other->delta, &diff);
                relative = diff;
                if (relative.x == 0 && relative.y == 0 && relative.z == 0) {
                    mode = 2;
                } else {
                    mode = 1;
                }
            }
        } else {
            mode = 0;
        }
        if (mode != 0) {
            if (mode == 2) {
                return data_020558a0[actor->body.shape.kind][other->shape.kind](&actor->body.shape, other, result,
                                                                                 0xe);
            }
            return data_02055930[actor->body.shape.kind][other->shape.kind](&actor->body.shape, other, result, 0xc,
                                                                             &relative);
        }
        return 0;
    }
    return 0;
}
