#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)(void);

typedef struct ElevatorDesc {
    VecFx32 position;
    fx32 scale;
    s16 linkId;
    s16 actorKind;
    s16 stopA;
    s16 stopB;
    s16 stopC;
    s8 shapeKind;
    s8 group;
    s8 index;
} ElevatorDesc;

typedef struct ElevatorClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    fx32 scale;
    u8 pad_50[0x14];
    s16 actorKind;
    u8 pad_66[0xa];
    VecFx32 position;
    u8 shapeKind;
    u8 classType;
    u8 pad_7e[4];
    u8 unk_82;
    u8 pad_83;
    s8 group;
    s8 index;
    s16 linkId;
    s16 stopA;
    s16 stopB;
    s16 stopC;
    u8 pad_8e[2];
    s32 activeStop;
} ElevatorClass;

extern ElevatorClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void RespawnElevatorObject(void);
extern void func_ov001_0207f210(void);
extern void func_ov001_0207f26c(void);
extern void func_ov006_020a0a58(void);
extern void TryActivateElevatorSlot(void);
extern void func_ov006_020a0b24(void);
extern void func_ov006_020a0c0c(void);
extern void ReleaseOwnerResource(void);

ElevatorClass *CreateElevatorObjectClass(int count, const ElevatorDesc *desc)
{
    ElevatorClass *objectClass = CreateByteGrid(0xd4, 0x74, count);

    objectClass->group = desc->group;
    objectClass->index = desc->index;
    objectClass->linkId = desc->linkId;
    objectClass->shapeKind = desc->shapeKind;
    objectClass->position.x = desc->position.x;
    objectClass->position.y = desc->position.y;
    objectClass->position.z = desc->position.z;
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_82 = 0;
    objectClass->scale = desc->scale;
    objectClass->stopA = desc->stopA;
    objectClass->stopB = desc->stopB;
    objectClass->stopC = desc->stopC;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = RespawnElevatorObject;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[10] = func_ov006_020a0a58;
    objectClass->hooks[11] = TryActivateElevatorSlot;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov006_020a0b24;
    objectClass->hooks[13] = func_ov006_020a0c0c;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->classType = 4;
    objectClass->activeStop = -1;
    return objectClass;
}
