#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct FieldObjectDef {
    u8 pad_00[0x64];
    s16 actorKind;
    u8 pad_66[0x0A];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    u8 pad_0c[0x0C];
    CollisionShape shape;
    u8 actorId;
    u8 pad_39[0x07];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
} FieldObject;

extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void BuildCollisionShape_02080834(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);

void FieldObject_SetPosition_02080b88(FieldObject *object, const VecFx32 *position)
{
    FieldObjectDef *def = object->def;

    object->position = *position;
    if ((object->stateFlags & 4) && object->def->actorKind >= 0) {
        Obj_SetPosition_0203569c(func_02036240(object->actorId), &object->position);
        BuildCollisionShape_02080834(&object->shape, &object->position, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, FALSE, 3);
    }
}
