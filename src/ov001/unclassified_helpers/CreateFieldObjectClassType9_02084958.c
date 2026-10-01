#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    s32 scale;
    s32 unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    u8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
} FieldObjectClass;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_02083730();
extern void func_ov001_0207f1e8();
extern void func_ov001_02083a88();
extern void func_ov001_02083a4c();
extern void func_ov001_02083b38();
extern void func_ov001_02083c00();
extern void func_ov001_02083c04();
extern void func_ov001_02083c2c();
extern void func_ov001_02084690();
extern void func_ov001_02083c34();
extern void func_ov001_02084794();
extern void func_ov001_020848a0();

FieldObjectClass *CreateFieldObjectClassType9_02084958(int count)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0x84, 0x1bc, count);

    objectClass->unk_50 = 0;
    objectClass->shapeKind = 2;
    objectClass->unk_70 = 0x266;
    objectClass->unk_74 = 0;
    objectClass->unk_78 = 0;
    objectClass->actorKind = 0x7b;
    objectClass->unk_82 = 2;
    objectClass->scale = 0x2000;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov001_02083730;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_02083a88;
    objectClass->hooks[6] = func_ov001_02083a4c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov001_02083b38;
    objectClass->hooks[10] = func_ov001_02083c00;
    objectClass->hooks[9] = func_ov001_02083c04;
    objectClass->hooks[11] = func_ov001_02083c2c;
    objectClass->hooks[14] = func_ov001_02084690;
    objectClass->hooks[12] = func_ov001_02083c34;
    objectClass->hooks[13] = func_ov001_02084794;
    objectClass->hooks[15] = func_ov001_020848a0;
    objectClass->classType = 9;
    return objectClass;
}
