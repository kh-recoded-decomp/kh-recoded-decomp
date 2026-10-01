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
    u8 pad_83[0x79];
    s32 activeCount;
} FieldObjectClass;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern s32 func_ov001_02063a38(void);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_02082070();
extern void func_ov001_0207f1e8();
extern void func_ov001_020822d8();
extern void func_ov001_0207f244();
extern void func_ov001_020822f8();
extern void func_ov001_0208232c();
extern void func_ov001_02082330();
extern void func_ov001_020823a0();

FieldObjectClass *CreateFieldObjectClassType11_020825e0(int count)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0x498, 0x78, count);
    s32 range;

    objectClass->param = 0;
    objectClass->shapeKind = 2;
    if (func_ov001_02063a38() == 4) {
        range = 0x867;
    } else {
        range = 0x59a;
    }
    objectClass->values[0] = range;
    objectClass->values[1] = 0;
    objectClass->values[2] = 0;
    objectClass->actorKind = 0;
    objectClass->unk_82 = 0xff;
    objectClass->scale = -1;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov001_02082070;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_020822d8;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_020822f8;
    objectClass->hooks[10] = func_ov001_0208232c;
    objectClass->hooks[9] = func_ov001_02082330;
    objectClass->hooks[11] = NULL;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = NULL;
    objectClass->hooks[13] = NULL;
    objectClass->hooks[15] = func_ov001_020823a0;
    objectClass->classType = 0xb;
    objectClass->activeCount = 0;
    return objectClass;
}
