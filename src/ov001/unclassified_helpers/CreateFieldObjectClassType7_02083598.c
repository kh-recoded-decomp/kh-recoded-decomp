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
    u8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
    u8 pad_83;
    s32 activeCount;
    s32 unk_88;
} FieldObjectClass;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_020828f0();
extern void func_ov001_0207f1e8();
extern void func_ov001_02082ae0();
extern void func_ov001_0207f244();
extern void SetActorRaisedCollision_02082b28();
extern void func_ov001_02082bd4();
extern void func_ov001_02082bd8();
extern void func_ov001_02082c44();
extern void func_ov001_02082c4c();

FieldObjectClass *CreateFieldObjectClassType7_02083598(int count)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0x8c, 0x7c, count);

    objectClass->param = 0;
    objectClass->shapeKind = 1;
    objectClass->values[0] = 0xccd;
    objectClass->values[1] = 0x3000;
    objectClass->values[2] = 0;
    objectClass->actorKind = 0x81;
    objectClass->unk_82 = 0xff;
    objectClass->scale = 0;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov001_020828f0;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_02082ae0;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = SetActorRaisedCollision_02082b28;
    objectClass->hooks[10] = func_ov001_02082bd4;
    objectClass->hooks[9] = func_ov001_02082bd8;
    objectClass->hooks[11] = func_ov001_02082c44;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov001_02082c4c;
    objectClass->hooks[13] = NULL;
    objectClass->classType = 7;
    objectClass->activeCount = 0;
    objectClass->unk_88 = 0;
    return objectClass;
}
