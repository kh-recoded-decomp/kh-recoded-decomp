#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    s32 recordParamA;
    s32 recordParamB;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct ShapeBase {
    void *data;
    s32 bounds[6];
    s32 kind;
} ShapeBase;

typedef struct CollisionShape {
    ShapeBase base;
    VecFx32 delta;
    s32 sweptBounds[6];
} CollisionShape;

typedef struct ActorBody {
    u8 pad_000[0x140];
    CollisionShape shape;
} ActorBody;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    ActorBody *body;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[0x03];
    s8 blendIndex;
    u8 pad_54[0x13];
    u8 lowBits : 2;
    u8 alpha : 6;
    s32 timer68;
    u8 pad_6c[0x0c];
    s32 timer78;
} FieldObject;

typedef struct ContactHandler {
    void (*callback)(void);
    FieldObject *owner;
} ContactHandler;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x76];
    void *model;
    u16 angle;
    u8 pad_082[0xfa];
    ContactHandler handler;
} FieldActor;

extern BOOL SpawnFieldActor_0208078c(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void InitCapsuleShape_0203ae34(ShapeBase *shape, void *capsule, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void func_020369c8(int index, void *owner, int a2);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL IsObjectFlagClear_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int a1, int a2);
extern void func_ov001_0208330c(void);
extern const VecFx32 data_02053438;

void RespawnCapsuleFieldObject_020828f0(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams params;
    FieldActor *actor;
    u16 angle;
    VecFx32 bottomCopy;
    VecFx32 topCopy;
    VecFx32 bottom;
    VecFx32 top;
    VecFx32 axis;
    VecFx32 diff;
    void *capsule;
    ShapeBase base;
    CollisionShape shape;
    ContactHandler handler;

    SpawnFieldActor_0208078c(object->body, object->group, object->index, object->actorId, &params, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = func_02036240(object->actorId);
    Obj_SetPosition_0203569c(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    top.x = object->position.x;
    top.y = object->position.y + 0x2333;
    top.z = object->position.z;
    topCopy = top;
    bottom.x = object->position.x;
    bottom.y = object->position.y + 0xccd;
    bottom.z = object->position.z;
    bottomCopy = bottom;
    capsule = object->body->shape.base.data;
    VEC_Subtract_01ff9e3c(&topCopy, &bottomCopy, &diff);
    axis = diff;
    InitCapsuleShape_0203ae34(&base, capsule, &bottomCopy, &topCopy, &axis, func_01ffaff4(&axis, &axis), 0xccd);
    shape.base = base;
    shape.delta = data_02053438;
    OffsetBoxByDelta_0203ac70(shape.base.bounds, shape.sweptBounds, &shape.delta);
    object->body->shape = shape;
    handler.callback = func_ov001_0208330c;
    handler.owner = object;
    actor->handler = handler;
    func_020369c8(object->actorId, object, 0x15);
    object->timer68 = 0;
    object->alpha = 0;
    object->timer78 = 0;
    Model_SetAllMaterialAlpha_0201a900(actor->model, object->alpha);
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 0);
    func_0202f4e8(&actor->animFlags);
    if (IsObjectFlagClear_0207f7a4(object)) {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, 1);
        func_020359f8(object->actorId, 0, 0);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, 0);
    }
}
