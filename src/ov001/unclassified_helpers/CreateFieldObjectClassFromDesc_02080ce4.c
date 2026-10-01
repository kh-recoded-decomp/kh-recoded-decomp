#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    s32 scale;
    s32 param;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    s32 values[3];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
    u8 pad_83;
    s8 variant;
    s8 slotIndex;
} FieldObjectClass;

typedef struct FieldObjectDesc {
    s32 param;
    s16 actorKind;
    s8 variant;
    s8 shapeKind;
    s32 values[3];
} FieldObjectDesc;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_02080aa4();
extern void func_ov001_0207f1e8();
extern void func_ov001_0207f20c();
extern void func_ov001_0207f244();
extern void func_ov001_02080b80();
extern void func_ov001_02080b84();
extern void func_ov001_02080b88();
extern void func_ov001_02080bf4();
extern void func_ov001_02080bfc();

FieldObjectClass *CreateFieldObjectClassFromDesc_02080ce4(int count, const FieldObjectDesc *desc)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0x88, 0x5c, count);

    objectClass->variant = desc->variant;
    objectClass->slotIndex = -1;
    objectClass->param = desc->param;
    objectClass->shapeKind = desc->shapeKind;
    objectClass->values[0] = desc->values[0];
    objectClass->values[1] = desc->values[1];
    objectClass->values[2] = desc->values[2];
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_82 = 0xff;
    objectClass->scale = -1;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov001_02080aa4;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_0207f20c;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_02080b80;
    objectClass->hooks[10] = func_ov001_02080b84;
    objectClass->hooks[9] = func_ov001_02080b88;
    objectClass->hooks[11] = func_ov001_02080bf4;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov001_02080bfc;
    objectClass->hooks[13] = NULL;
    objectClass->classType = 0;
    return objectClass;
}
