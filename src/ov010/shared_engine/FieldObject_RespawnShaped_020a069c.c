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
    u8 pad_50[3];
    s8 blendIndex;
} FieldObject;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7A];
    u16 angle;
    u8 pad_82[0x8a];
    u8 quadNode[4];
} FieldActor;

typedef struct World {
    u8 pad_00[4];
    void **quadTree;
} World;

extern BOOL SpawnFieldActor_0208078c(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern void func_02036ab8(void *entry, void *callback);
extern void Actor_UpdateQuadTreeLink_020a0814(void);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL func_ov001_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int a1, int a2);
extern World *func_02036230(void);
extern void QuadTree_RemoveObject_02033c60(void *tree, void *node);

void FieldObject_RespawnShaped_020a069c(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;

    SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    func_02036ab8(object->entry, Actor_UpdateQuadTreeLink_020a0814);
    actor = func_02036240(object->actorId);
    Obj_SetPosition_0203569c(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 0);
    func_0202f4e8(&actor->animFlags);
    if (func_ov001_0207f7a4(object)) {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
        func_020359f8(object->actorId, 0, 0);
        QuadTree_RemoveObject_02033c60(*func_02036230()->quadTree, actor->quadNode);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, FALSE);
    }
}
