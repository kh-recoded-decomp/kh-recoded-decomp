#include "nitro/types.h"

typedef void (*FieldObjectHook)(void);

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
    u8 pad_7e[0x4];
    u8 unk_82;
    u8 pad_83;
    int pathCount;
    void *paths;
} WanderActorClass;

extern WanderActorClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClear32(u32 value, void *dest, u32 size);
extern void DrawWanderMotionModels(void);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void RespawnWanderActor(void);
extern void func_ov001_0207f210(void);
extern void ReleaseOwnerResource(void);
extern void func_ov001_0207f26c(void);
extern void FreeEntryArray(void);
extern void func_ov007_020a100c(void);
extern void TryLaunchWanderActor(void);
extern void GetRaisedOwnerPosition(void);

WanderActorClass *CreateWanderActorClass(int count, int actorKind, int param, int pathCount)
{
    WanderActorClass *objectClass = CreateByteGrid(0xb0, 0xb8, count);

    if (pathCount > 0) {
        u32 size = pathCount * 8;
        objectClass->paths = NNSi_FndAllocFromDefaultHeap(size);
        MIi_CpuClear32(0, objectClass->paths, size);
    }
    objectClass->pathCount = pathCount;
    objectClass->unk_50 = 0x10;
    objectClass->shapeKind = -1;
    objectClass->actorKind = actorKind;
    objectClass->param = param;
    objectClass->hooks[15] = DrawWanderMotionModels;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = RespawnWanderActor;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = FreeEntryArray;
    objectClass->hooks[10] = func_ov007_020a100c;
    objectClass->hooks[11] = NULL;
    objectClass->hooks[14] = TryLaunchWanderActor;
    objectClass->hooks[12] = NULL;
    objectClass->hooks[13] = GetRaisedOwnerPosition;
    objectClass->unk_82 = 1;
    objectClass->classType = 5;
    return objectClass;
}
