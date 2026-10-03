#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)();

typedef struct SpawnerClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    int linkId;
    int unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 classType;
    u8 pad_7e[0x4];
    u8 unk_82;
    u8 pad_83;
    u8 unk_84;
} SpawnerClass;

extern SpawnerClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov008_020a06dc();
extern void func_ov001_0207f1e8();
extern void ReleaseChildObjects_020a0ab4();
extern void func_ov001_0207f244();
extern void func_ov008_020a0928();
extern void SetFieldObjectPosition_020a092c();
extern void func_ov008_020a0954();
extern void func_ov008_020a0958();
extern void func_ov008_020a0a08();

SpawnerClass *CreateChildSpawnerClass_020a0b18(int count, int actorKind)
{
    SpawnerClass *objectClass = func_ov001_0207f380(0x88, 0x2a8, count);

    objectClass->unk_84 = 0;
    objectClass->unk_50 = 1;
    objectClass->shapeKind = 3;
    objectClass->sizeX = 0x7800;
    objectClass->sizeY = 0x1800;
    objectClass->sizeZ = 0x7800;
    objectClass->actorKind = actorKind;
    objectClass->unk_82 = 0xff;
    objectClass->linkId = -1;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov008_020a06dc;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = ReleaseChildObjects_020a0ab4;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[10] = func_ov008_020a0928;
    objectClass->hooks[9] = SetFieldObjectPosition_020a092c;
    objectClass->hooks[11] = func_ov008_020a0954;
    objectClass->hooks[12] = func_ov008_020a0958;
    objectClass->hooks[15] = func_ov008_020a0a08;
    objectClass->classType = 12;
    return objectClass;
}
