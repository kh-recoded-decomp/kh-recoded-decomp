#include "nitro/types.h"

typedef void (*FieldObjectHook)();

typedef struct WanderActorClass {
    FieldObjectHook hooks[16];
    u8 pad_40[0xc];
    int param;
    int unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0x16];
    s8 shapeKind;
    u8 classType;
    u8 pad_7E[0x4];
    u8 unk_82;
    u8 pad_83[0x1];
    int pathCount;
    void *paths;
} WanderActorClass;

extern WanderActorClass *func_ov001_0207f380(u32 classSize, u32 objectSize, int count);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff86fc(u32 value, void *dest, u32 size);
extern void func_ov001_0207f0d0();
extern void func_ov001_0207f128();
extern void func_ov007_020a0ecc();
extern void func_ov001_0207f1e8();
extern void func_ov001_0207f20c();
extern void func_ov001_0207f244();
extern void FreeEntryArray_020a1720();
extern void func_ov007_020a0fec();
extern void GetRaisedOwnerPosition_020a0ff8();
extern void func_ov007_020a1024();
extern void func_ov007_020a15a8();

WanderActorClass *CreateWanderActorClass_020a1778(int count, int actorKind, int param, int pathCount)
{
    WanderActorClass *objectClass = func_ov001_0207f380(0xb0, 0xb8, count);

    if (pathCount > 0) {
        u32 size = pathCount * 8;
        objectClass->paths = NNSi_FndAllocFromDefaultHeap_0202a178(size);
        func_01ff86fc(0, objectClass->paths, size);
    }
    objectClass->pathCount = pathCount;
    objectClass->unk_50 = 0x10;
    objectClass->shapeKind = -1;
    objectClass->actorKind = actorKind;
    objectClass->param = param;
    objectClass->hooks[15] = func_ov007_020a15a8;
    objectClass->hooks[0] = func_ov001_0207f0d0;
    objectClass->hooks[1] = func_ov001_0207f128;
    objectClass->hooks[2] = func_ov007_020a0ecc;
    objectClass->hooks[3] = func_ov001_0207f1e8;
    objectClass->hooks[4] = func_ov001_0207f20c;
    objectClass->hooks[6] = func_ov001_0207f244;
    objectClass->hooks[7] = FreeEntryArray_020a1720;
    objectClass->hooks[10] = func_ov007_020a0fec;
    objectClass->hooks[11] = NULL;
    objectClass->hooks[14] = func_ov007_020a1024;
    objectClass->hooks[12] = NULL;
    objectClass->hooks[13] = GetRaisedOwnerPosition_020a0ff8;
    objectClass->unk_82 = 1;
    objectClass->classType = 5;
    return objectClass;
}
