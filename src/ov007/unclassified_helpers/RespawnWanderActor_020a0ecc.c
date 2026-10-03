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

typedef struct WanderObject {
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
    u8 pad_54[0x5b];
    s8 state;
    u8 pad_b0[0x2];
    s8 mode;
    u8 pad_b3;
    u16 waitId;
} WanderObject;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
} FieldActor;

extern BOOL SpawnFieldActor_0208078c(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern int thumbStep_0206888c(u16 id);
extern BOOL IsObjectFlagClear_0207f7a4(WanderObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int a1, int a2);

void RespawnWanderActor_020a0ecc(WanderObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    VecFx32 position;
    FieldActor *actor;
    BOOL visible;
    u16 angle;

    SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = func_02036240(object->actorId);
    position = object->position;
    position.y -= 0x800;
    Obj_SetPosition_0203569c(actor, &position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 0);
    func_0202f4e8(&actor->animFlags);
    if (object->mode == 2 && !thumbStep_0206888c(object->waitId)) {
        object->mode = 4;
    }
    visible = IsObjectFlagClear_0207f7a4(object);
    if (object->state & 1) {
        visible = FALSE;
    }
    func_020359f8(object->actorId, 0, 0);
    if (visible) {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, FALSE);
    }
}
