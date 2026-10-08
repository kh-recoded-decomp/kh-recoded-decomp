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

extern BOOL func_ov001_020807b4(FieldEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void ApplyRecordTableEntry2(int index, int a1, int a2, int a3);
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void SetActorExtraPosition(u32 id, void *source, int mask);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern BOOL IsObjectFlagClear(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern BOOL Container_HasFlag1(FieldEntry *entry);
extern void ApplyRecordTableEntry5(int index, int a1, int a2);
extern void *GetActorRegistry(void);
extern void Obj_PlaceInWorld(void *world, FieldActor *actor, const VecFx32 *position);
extern void FieldObject_SetLiftedPosition(FieldObject *object, const VecFx32 *position);
extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void FieldObject_SetSwitchState(FieldObject *object, int state);

void FieldObject_RespawnSwitch(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;

    func_ov001_020807b4(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    ApplyRecordTableEntry2(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    SetActorExtraPosition(object->actorId, object, 0x1f);
    RebindAnimTracks(&actor->animFlags, object->blendIndex, 1);
    Flags16_ClearBit1(&actor->animFlags);
    if (IsObjectFlagClear(object)) {
        ActorSlot_SetFlag8ByIndex(object->actorId, TRUE);
        if (!Container_HasFlag1(object->entry) && !(object->entry->flags & 0x100)) {
            ApplyRecordTableEntry5(object->actorId, 0, 0);
        }
        if (!(actor->flags & 8)) {
            Obj_PlaceInWorld(GetActorRegistry(), actor, &actor->position);
        }
        if (object->state != 1) {
            object->stateFlags |= 0x10;
        }
        object->stateFlags |= 0x20;
    } else {
        ActorSlot_SetFlag8ByIndex(object->actorId, FALSE);
        object->stateFlags &= ~0x10;
        object->stateFlags &= ~0x20;
    }
    FieldObject_SetLiftedPosition(object, &object->position);
    if (FieldObject_GetSavedValue(object) & 1) {
        FieldObject_SetSwitchState(object, 2);
    } else if (object->state == 2) {
        FieldObject_SetSwitchState(object, 0);
    } else {
        FieldObject_SetSwitchState(object, object->state);
    }
}
