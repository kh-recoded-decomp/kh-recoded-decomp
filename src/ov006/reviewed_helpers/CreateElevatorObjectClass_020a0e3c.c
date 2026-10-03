#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)();

typedef struct {
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

typedef struct {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    fx32 scale;
    u8 pad_50[0x14];
    s16 actorKind;
    u8 pad_66[0xa];
    VecFx32 position;
    u8 shapeKind;
    u8 classType;
    u8 pad_7E[4];
    u8 unk_82;
    u8 pad_83;
    s8 group;
    s8 index;
    s16 linkId;
    s16 stopA;
    s16 stopB;
    s16 stopC;
    u8 pad_8E[2];
    s32 activeStop;
} ElevatorClass;

extern ElevatorClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov006_020a07b4();
extern void func_ov001_0207f1e8();
extern void func_ov001_0207f244();
extern void func_ov006_020a0a38();
extern void func_ov006_020a0a3c();
extern void func_ov006_020a0b04();
extern void func_ov006_020a0bec();
extern void func_ov001_0207f20c();

ElevatorClass *CreateElevatorObjectClass_020a0e3c(int count, const ElevatorDesc *desc) {
    ElevatorClass *objectClass = func_ov001_0207f380(0xd4, 0x74, count);

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
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov006_020a07b4;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[10] = func_ov006_020a0a38;
    objectClass->hooks[11] = func_ov006_020a0a3c;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov006_020a0b04;
    objectClass->hooks[13] = func_ov006_020a0bec;
    objectClass->hooks[4] = func_ov001_0207f20c;
    objectClass->classType = 4;
    objectClass->activeStop = -1;
    return objectClass;
}
