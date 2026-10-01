#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[17];
    u8 pad_44[0x20];
    s16 actorKind;
    u8 pad_66[0x16];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    s8 unk_82;
    u8 pad_83[0x1];
    u32 projection[14];
    s8 targetIndex;
} FieldObjectClass;

typedef struct TargetViewDesc {
    int actorKind;
} TargetViewDesc;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_02081aa8();
extern void func_ov001_0207f1e8();
extern void FieldObject_ClearMatchingTarget_02081d24();
extern void func_ov001_0207f244();
extern void SetSessionMarkerActive_02081d6c();
extern void GetFieldOffset40_02081bbc();
extern void FieldObject_DrawTargetView_02081cbc();
extern void func_ov001_02081d44();
extern void LoadDefaultProjectionValues_0202a7b4(u32 *projection);

FieldObjectClass *CreateTargetViewClass_02081da8(int count, const TargetViewDesc *desc)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0xc0, 0x5c, count);

    objectClass->shapeKind = -1;
    objectClass->actorKind = -1;
    objectClass->unk_82 = 0;
    objectClass->hooks[15] = FieldObject_DrawTargetView_02081cbc;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = FieldObject_ClearMatchingTarget_02081d24;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[8] = SetSessionMarkerActive_02081d6c;
    objectClass->hooks[10] = GetFieldOffset40_02081bbc;
    objectClass->hooks[16] = func_ov001_02081d44;
    objectClass->classType = 3;
    objectClass->targetIndex = -1;
    objectClass->actorKind = desc->actorKind;
    if (objectClass->actorKind >= 0) {
        objectClass->hooks[2] = func_ov001_02081aa8;
    } else {
        objectClass->hooks[2] = NULL;
    }
    LoadDefaultProjectionValues_0202a7b4(objectClass->projection);
    return objectClass;
}
