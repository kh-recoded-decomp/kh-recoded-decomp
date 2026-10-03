#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldEntry {
    u8 pad_00[8];
    u16 flags;
} FieldEntry;

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
    FieldEntry *entry;
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
    u8 pad_54[4];
    int state;
} FieldObject;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0xa2];
    VecFx32 position;
} FieldActor;

extern BOOL SpawnFieldActor_0208078c(FieldEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern FieldActor *func_02036240(u32 actorId);
extern void func_020369c8(u32 id, void *source, int mask);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL func_ov001_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern BOOL func_02035b38(FieldEntry *entry);
extern void func_020359f8(int index, int a1, int a2);
extern void *func_02036230(void);
extern void Obj_PlaceInWorld_02035580(void *world, FieldActor *actor, const VecFx32 *position);
extern void FieldObject_SetLiftedPosition_020a08f4(FieldObject *object, const VecFx32 *position);
extern u16 FieldObject_GetSavedValue_0207f9a8(FieldObject *object);
extern void FieldObject_SetSwitchState_020a0634(FieldObject *object, int state);

void FieldObject_RespawnSwitch_020a0778(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;

    SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = func_02036240(object->actorId);
    func_020369c8(object->actorId, object, 0x1f);
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 1);
    func_0202f4e8(&actor->animFlags);
    if (func_ov001_0207f7a4(object)) {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
        if (!func_02035b38(object->entry) && !(object->entry->flags & 0x100)) {
            func_020359f8(object->actorId, 0, 0);
        }
        if (!(actor->flags & 8)) {
            Obj_PlaceInWorld_02035580(func_02036230(), actor, &actor->position);
        }
        if (object->state != 1) {
            object->stateFlags |= 0x10;
        }
        object->stateFlags |= 0x20;
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, FALSE);
        object->stateFlags &= ~0x10;
        object->stateFlags &= ~0x20;
    }
    FieldObject_SetLiftedPosition_020a08f4(object, &object->position);
    if (FieldObject_GetSavedValue_0207f9a8(object) & 1) {
        FieldObject_SetSwitchState_020a0634(object, 2);
    } else if (object->state == 2) {
        FieldObject_SetSwitchState_020a0634(object, 0);
    } else {
        FieldObject_SetSwitchState_020a0634(object, object->state);
    }
}
