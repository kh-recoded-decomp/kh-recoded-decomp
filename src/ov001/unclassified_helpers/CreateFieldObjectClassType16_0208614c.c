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
} FieldObjectClass;

typedef struct {
    s16 actorKind;
    s8 variant;
} FieldObjectKindDesc;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_02085f3c();
extern void func_ov001_0207f1e8();
extern void ReleaseOwnerResource_0207f20c();
extern void func_ov001_0207f244();
extern void func_ov001_02086060();
extern void func_ov001_02086064();
extern void func_ov001_02086068();
extern void func_ov001_020860a4();
extern void func_ov001_020860ac();
extern void func_ov001_020860b0();

FieldObjectClass *CreateFieldObjectClassType16_0208614c(int count, const FieldObjectKindDesc *desc)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0x88, 0x58, count);

    objectClass->variant = desc->variant;
    objectClass->param = 0x10;
    objectClass->shapeKind = -1;
    objectClass->values[0] = 0;
    objectClass->values[1] = 0;
    objectClass->values[2] = 0;
    objectClass->actorKind = desc->actorKind;
    objectClass->unk_82 = 0xff;
    objectClass->scale = -1;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov001_02085f3c;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = ReleaseOwnerResource_0207f20c;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_02086060;
    objectClass->hooks[10] = func_ov001_02086064;
    objectClass->hooks[9] = func_ov001_02086068;
    objectClass->hooks[11] = func_ov001_020860a4;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov001_020860ac;
    objectClass->hooks[13] = NULL;
    objectClass->hooks[15] = func_ov001_020860b0;
    objectClass->classType = 0x10;
    return objectClass;
}
