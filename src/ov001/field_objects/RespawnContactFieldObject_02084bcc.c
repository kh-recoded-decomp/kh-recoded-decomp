#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct EntryGroupDesc {
    void *source;
    s32 countA;
    s32 countB;
    s32 flags;
    s32 pad_10;
} EntryGroupDesc;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    s32 recordParamA;
    s32 recordParamB;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[9];
    s16 entryGroup;
} FieldObjectDef;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    void *entry;
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
    u8 pad_54[4];
    s32 visible;
    u8 pad_5c[0x44];
    u8 dataBuffers[0x18];
    void *dataBuffer;
} FieldObject;

typedef struct ContactHandler {
    void (*callback)(void);
    FieldObject *owner;
} ContactHandler;

typedef struct CollisionShape {
    u32 kind;
    u8 box[0x18];
    s32 shapeType;
    VecFx32 delta;
    u8 sweptBox[0x18];
} CollisionShape;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
    u8 pad_082[0x97];
    u8 contactEnabled;
    u8 pad_11a[0x16];
    CollisionShape shape;
    u8 pad_174[0x10];
    ContactHandler handler;
} FieldActor;

extern BOOL SpawnFieldActor_0208078c(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void func_020369c8(int index, int a1, int a2);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL IsObjectFlagClear_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int a1, int a2);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern u16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern void Obj_AllocDataBuffers_02034f74(void *buffers, int count, int a2, int a3, int a4);
extern void func_ov001_02085798(void);
extern const VecFx32 data_02053438;
extern void (*data_020559c0[])(CollisionShape *shape, void *box);
extern char data_ov001_0209f168[];

void RespawnContactFieldObject_02084bcc(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;
    ContactHandler handler;
    EntryGroupDesc desc;
    CollisionShape *collision;

    SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = func_02036240(object->actorId);
    Obj_SetPosition_0203569c(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    actor->contactEnabled = 1;
    handler.callback = func_ov001_02085798;
    handler.owner = object;
    actor->handler = handler;
    actor->shape.delta = data_02053438;
    collision = &actor->shape;
    data_020559c0[actor->shape.shapeType](collision, collision->box);
    OffsetBoxByDelta_0203ac70(actor->shape.box, actor->shape.sweptBox, &actor->shape.delta);
    func_020369c8(object->actorId, 0, 0x12);
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 0);
    func_0202f4e8(&actor->animFlags);
    if (IsObjectFlagClear_0207f7a4(object)) {
        func_020359f8(object->actorId, 0, 0);
        if (object->visible == 0) {
            ActorSlot_SetFlag8ByIndex_02036120(object->actorId, 0);
        }
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, 0);
    }
    if (def->entryGroup == -1) {
        ZeroBytes0x14_020a8adc(&desc);
        desc.countA = 1;
        desc.countB = 1;
        desc.flags = 0;
        desc.source = data_ov001_0209f168;
        def->entryGroup = func_ov021_020a89a8(&desc);
    }
    if (object->dataBuffer == NULL) {
        Obj_AllocDataBuffers_02034f74(object->dataBuffers, 8, 1, 1, 0);
    }
}
