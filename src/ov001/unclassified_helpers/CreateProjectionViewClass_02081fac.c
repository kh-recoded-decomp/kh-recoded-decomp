#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)();

typedef struct FieldObjectClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0x24];
    s16 actorKind;
    u8 pad_66[0x16];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    s8 unk_82;
    u8 pad_83[0x1];
    u32 projection[14];
    fx32 halfWidth;
    fx32 halfDepth;
} FieldObjectClass;

extern FieldObjectClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov001_02081ea8();
extern void func_ov001_0207f1e8();
extern void func_ov001_0207f20c();
extern void func_ov001_0207f244();
extern void func_ov001_02081f84();
extern void LoadDefaultProjectionValues_0202a7b4(u32 *projection);

FieldObjectClass *CreateProjectionViewClass_02081fac(int count, u16 actorKind, fx32 width, fx32 depth)
{
    FieldObjectClass *objectClass = func_ov001_0207f380(0xc4, 0x58, count);

    objectClass->shapeKind = -1;
    objectClass->actorKind = actorKind;
    objectClass->unk_82 = 0;
    objectClass->hooks[15] = func_ov001_02081f84;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov001_02081ea8;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_0207f20c;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->classType = 13;
    objectClass->halfWidth = width >> 1;
    objectClass->halfDepth = depth >> 1;
    LoadDefaultProjectionValues_0202a7b4(objectClass->projection);
    return objectClass;
}
