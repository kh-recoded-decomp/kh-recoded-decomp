#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x10c];
    u8 collision[4];
} FieldActor;

typedef struct {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} FieldObject;

extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *actor, const VecFx32 *position);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetCollisionObjectPosition_02033f48(void *collision, const VecFx32 *position);

void FieldObject_PlaceActor_02082330(FieldObject *object, const VecFx32 *position)
{
    VecFx32 collisionPos;
    VecFx32 raise;
    VecFx32 offset;
    VecFx32 sum;
    FieldActor *actor = func_02036240(object->actorId);

    object->position = *position;
    Obj_SetPosition_0203569c(actor, &object->position);
    offset.x = 0;
    offset.y = 0xa66;
    offset.z = 0;
    raise = offset;
    VEC_Add_01ff9e0c(&object->position, &raise, &sum);
    collisionPos = sum;
    SetCollisionObjectPosition_02033f48(actor->collision, &collisionPos);
}
