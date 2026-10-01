#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 kind;
    u8 box[0x1c];
    VecFx32 delta;
    u8 sweptBox[0x18];
} CollisionShape;

typedef struct {
    u8 pad_000[0x140];
    CollisionShape shape;
} FieldObjectWork;

typedef struct {
    u8 pad_00[0xc];
    FieldObjectWork *work;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} FieldObject;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *actor, const VecFx32 *position);
extern void SetShapePosition_0203afa0(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);

void FieldObject_SetActorPosition_02082bd8(FieldObject *object, const VecFx32 *position)
{
    VecFx32 shapePos;
    VecFx32 raised;
    CollisionShape *shape;

    object->position = *position;
    Obj_SetPosition_0203569c(func_02036240(object->actorId), &object->position);
    raised.x = object->position.x;
    raised.y = object->position.y + 0xccd;
    raised.z = object->position.z;
    shapePos = raised;
    shape = &object->work->shape;
    SetShapePosition_0203afa0(shape, &shapePos);
    OffsetBoxByDelta_0203ac70(shape->box, shape->sweptBox, &shape->delta);
}
