#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpawnCommand {
    s32 type;
    union {
        u16 eventId;
        s8 effectId;
        struct {
            u8 group;
            u8 index;
        } object;
    } target;
    s8 fallbackEffectId;
} SpawnCommand;

typedef struct SpawnOwner {
    u8 pad_00[0x40];
    VecFx32 position;
} SpawnOwner;

typedef struct StageEventRecord {
    u8 pad_00[0x10];
    u16 actorId;
} StageEventRecord;

typedef struct ObjectClass {
    u8 pad_00[0x64];
    s16 kind;
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectClass *objectClass;
    u8 pad_0C[0x42];
    u16 flags;
    u8 pad_50[0x8];
    fx32 minDistance;
    fx32 maxDistance;
    u8 pad_60[0x4];
    VecFx32 direction;
    u8 pad_70[0xd];
    u8 category;
} FieldObject;

extern void RollRewardOrbDrop(int effectId, VecFx32 *position);
extern void func_ov001_02087e24(u16 eventId);
extern void func_ov001_020688d4(u32 value, s32 hasValue, s32 flag);
extern void SetStageObjectPosition(u16 eventId, VecFx32 *position);
extern u16 func_ov001_02087784(int objectIndex, u32 entryIndex);
extern StageEventRecord *GetStageEventRecord(u32 id);
extern void *GetStageActor(int id);
extern void WarpWalkerTo(void *actor, VecFx32 *position);
extern void SpawnSoundSlot(int soundId, int flag, VecFx32 *position, int extra);
extern FieldObject *func_ov001_0207f060(u32 group, u32 index);
extern void FieldObject_SetEnabled(FieldObject *object, BOOL enabled);
extern void CallFieldObjectHook24(FieldObject *object, VecFx32 *position);
extern int func_ov001_0207f040(void);
extern FieldObject *func_ov001_0207f050(int index);
extern FieldObject *GetStridedBufferEntry(FieldObject *object, u32 index);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_NormalizeLength(VecFx32 *src, VecFx32 *dst);
extern int func_ov011_020a09d0(SpawnOwner *owner);
extern void SetPanelActorState(FieldObject *object, int value);
extern void *func_ov001_0208724c(u32 group, u32 index);
extern void CacheEntry_SetActive(void *entry, BOOL active);
extern void SetFieldUnitPosition(void *entry, VecFx32 *position);

static inline void SetVector(VecFx32 *vector, fx32 x, fx32 y, fx32 z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void RunSpawnCommand(SpawnCommand *command, SpawnOwner *owner)
{
    FieldObject *object;

    switch (command->type) {
    case 0:
        RollRewardOrbDrop(command->target.effectId, &owner->position);
        return;
    case 1: {
        StageEventRecord *record;
        void *actor;
        VecFx32 position;

        func_ov001_02087e24(command->target.eventId);
        func_ov001_020688d4(command->target.eventId, 1, 0);
        position = owner->position;
        SetStageObjectPosition(command->target.eventId, &position);
        record = GetStageEventRecord(func_ov001_02087784(command->target.eventId, 0));
        if (record->actorId != 0) {
            actor = GetStageActor((s16)record->actorId);
            position = owner->position;
            WarpWalkerTo(actor, &position);
            SpawnSoundSlot(0x1a7, 1, &owner->position, 0);
            return;
        }
        RollRewardOrbDrop(command->fallbackEffectId, &owner->position);
        return;
    }
    case 2:
        object = func_ov001_0207f060(command->target.object.group, command->target.object.index);
        FieldObject_SetEnabled(object, TRUE);
        CallFieldObjectHook24(object, &owner->position);
        return;
    case 3:
        object = func_ov001_0207f060(command->target.object.group, command->target.object.index);
        if (object->objectClass->kind == 0x7b) {
            int count = func_ov001_0207f040();
            int i;

            for (i = 0; i < count; i++) {
                FieldObject *entry = func_ov001_0207f050(i);

                if (entry->category == 9) {
                    FieldObject *target = GetStridedBufferEntry(entry, 0);
                    VecFx32 *destination = func_ov001_0206dc4c(0);
                    VecFx32 position;
                    VecFx32 raised;

                    FieldObject_SetEnabled(target, TRUE);
                    raised.x = owner->position.x;
                    raised.y = owner->position.y + 0x800;
                    raised.z = owner->position.z;
                    position = raised;
                    CallFieldObjectHook24(target, &position);
                    SetVector(&target->direction, destination->x - owner->position.x, 0, destination->z - owner->position.z);
                    VEC_NormalizeLength(&target->direction, &target->direction);
                    if (target->direction.x == 0 && target->direction.y == 0 && target->direction.z == 0) {
                        target->direction.x = 0;
                        target->direction.y = 0;
                        target->direction.z = 0x1000;
                    }
                    target->minDistance = 0;
                    target->maxDistance = 0x7fffffff;
                    target->flags &= ~0x10;
                    break;
                }
            }
        } else {
            FieldObject_SetEnabled(object, TRUE);
            CallFieldObjectHook24(object, &owner->position);
        }
        SpawnSoundSlot(0x1a7, 0, &owner->position, 0);
        return;
    case 4:
        object = func_ov001_0207f060(command->target.object.group, command->target.object.index);
        FieldObject_SetEnabled(object, TRUE);
        CallFieldObjectHook24(object, &owner->position);
        SetPanelActorState(object, func_ov011_020a09d0(owner));
        SpawnSoundSlot(0x1a7, 0, &owner->position, 0);
        return;
    case 5: {
        void *entry = func_ov001_0208724c(command->target.object.group, command->target.object.index);

        CacheEntry_SetActive(entry, TRUE);
        SetFieldUnitPosition(entry, &owner->position);
        return;
    }
    }
}
