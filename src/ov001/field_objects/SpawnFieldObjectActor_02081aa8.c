#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    u16 *spawnCounter;
    s32 recordParamB;
    u8 pad_5c[0x8];
    s16 saveIndex;
    u8 pad_66[0xa];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 pad_7d[0x13];
    fx32 baseHeight;
    u8 pad_94[0x18];
    fx32 topHeight;
    u8 pad_b0[0xc];
    s8 spawnedIndex;
} FieldObjectDef;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7A];
    u16 angle;
} FieldActor;

typedef struct ActorEntry {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[6];
    FieldActor actor;
} ActorEntry;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    ActorEntry *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x11];
    u16 angle;
    u16 stateFlags;
} FieldObject;

extern BOOL SpawnFieldActor_0208078c(ActorEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern BOOL func_02035930(ActorEntry *entry, u16 *param2, s32 param3, u32 param4);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL IsObjectFlagClear_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8_02036140(ActorEntry *slot, BOOL enable);
extern void ActorSlot_PlaceAndLink_02035a18(ActorEntry *slot, int anchor, const VecFx32 *offset);

void SpawnFieldObjectActor_02081aa8(FieldObject *object) {
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    ActorEntry *entry;
    FieldActor *actor;

    if (def->saveIndex >= 0) {
        if (def->spawnedIndex < 0) {
            def->spawnedIndex = object->index;
            SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape,
                                     def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle,
                                     !(object->stateFlags & 8), TRUE);
            func_02035930(object->entry, def->spawnCounter, def->recordParamB, 3);
            entry = object->entry;
            {
                VecFx32 offset = {0, 0, 0};
                actor = &entry->actor;
                offset.z = def->topHeight - def->baseHeight - FX32_ONE;
                Obj_SetPosition_0203569c(actor, &offset);
            }
            if (!(entry->actor.flags & 0x20)) {
                actor->angle = 0;
                actor->animFlags |= 0x20;
            }
            RebindAnimTracks_020809d0(&actor->animFlags, 0, 0);
            func_0202f4e8(&actor->animFlags);
            if (IsObjectFlagClear_0207f7a4(object)) {
                ActorSlot_SetFlag8_02036140(object->entry, TRUE);
                ActorSlot_PlaceAndLink_02035a18(object->entry, 0, NULL);
                object->entry->flags |= 0x200;
            } else {
                ActorSlot_SetFlag8_02036140(object->entry, FALSE);
            }
            return;
        }
        (*def->spawnCounter)--;
    }
}
