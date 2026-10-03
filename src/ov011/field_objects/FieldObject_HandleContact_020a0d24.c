#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitVolume {
    u8 pad_00[0x1c];
    s32 shape;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} HitVolume;

typedef struct Collider {
    u8 pad_00[4];
    VecFx32 max;
    VecFx32 min;
    s32 shape;
} Collider;

typedef struct ActorBody {
    u8 pad_00[0x130];
    Collider collider;
} ActorBody;

typedef struct FieldObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x1f];
    s32 state;
} FieldObject;

typedef int (*TouchFunc)(Collider *collider, HitVolume *volume, void *context, int flags);
typedef int (*PushFunc)(Collider *collider, HitVolume *volume, void *context, int flags, VecFx32 *push);

extern ActorBody *func_02036240(int actorId);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern TouchFunc data_020558a0[][6];
extern PushFunc data_02055930[][6];

int FieldObject_HandleContact_020a0d24(FieldObject *object, HitVolume *volume, void *context)
{
    ActorBody *body = func_02036240(object->actorId);
    VecFx32 reverse;
    VecFx32 push;
    int result;

    if (object->state == 0) {
        if (body->collider.max.x >= volume->min.x && body->collider.min.x <= volume->max.x &&
            body->collider.max.z >= volume->min.z && body->collider.min.z <= volume->max.z &&
            body->collider.max.y >= volume->min.y && body->collider.min.y <= volume->max.y) {
            if (volume->velocity.x == 0 && volume->velocity.y == 0 && volume->velocity.z == 0) {
                result = 2;
            } else {
                reverse = volume->velocity;
                NegateVecFx32_0204aa40(&reverse);
                push = reverse;
                result = 1;
            }
        } else {
            result = 0;
        }
        if (result != 0) {
            if (result == 2) {
                int flags = 2;
                if (volume->shape != 2) {
                    flags = 0;
                }
                return data_020558a0[body->collider.shape][volume->shape](&body->collider, volume, context, flags | 8);
            }
            return data_02055930[body->collider.shape][volume->shape](&body->collider, volume, context, 8, &push);
        }
        return 0;
    }
    return 0;
}
