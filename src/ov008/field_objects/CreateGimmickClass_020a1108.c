#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct GimmickClass {
    FieldObjectHook hooks[15];
    u8 pad_3c[0x10];
    int linkId;
    int unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    int unk_70;
    int unk_74;
    int unk_78;
    s8 shapeKind;
    u8 classType;
    u8 pad_7e[0x4];
    u8 unk_82;
} GimmickClass;

extern GimmickClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov008_020a0c64();
extern void func_ov001_0207f1e8();
extern void func_ov001_0207f20c();
extern void func_ov001_0207f244();
extern void func_ov008_020a0d50();
extern void func_ov008_020a0d54();
extern void SetFieldObjectPosition_020a0d58();
extern void func_ov008_020a0d80();
extern void func_ov008_020a0d88();

GimmickClass *CreateGimmickClass_020a1108(int count)
{
    GimmickClass *objectClass = func_ov001_0207f380(0x84, 0x78, count);

    objectClass->unk_50 = 0;
    objectClass->shapeKind = -1;
    objectClass->unk_70 = 0;
    objectClass->unk_74 = 0;
    objectClass->unk_78 = 0;
    objectClass->actorKind = 0x7e;
    objectClass->unk_82 = 0xff;
    objectClass->linkId = -1;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov008_020a0c64;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_0207f20c;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov008_020a0d50;
    objectClass->hooks[10] = func_ov008_020a0d54;
    objectClass->hooks[9] = SetFieldObjectPosition_020a0d58;
    objectClass->hooks[11] = func_ov008_020a0d80;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov008_020a0d88;
    objectClass->hooks[13] = NULL;
    objectClass->classType = 8;
    return objectClass;
}
