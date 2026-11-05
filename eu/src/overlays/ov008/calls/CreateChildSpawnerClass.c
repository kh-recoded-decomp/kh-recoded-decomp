#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*FieldObjectHook)(void);

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

extern SpawnerClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void FieldObject_RespawnSegmented(void);
extern void FreeFieldObjectClassAnimationBuffers(void);
extern void ReleaseChildObjects(void);
extern void FreeFieldObjectShapeStorage(void);
extern void ChildSpawner_GetPosition(void);
extern void SetFieldObjectPosition(void);
extern void ChildSpawner_ApplyHitTrue(void);
extern void ChildSpawner_QueryHitFalse(void);
extern void DrawChildSpawner(void);

SpawnerClass *CreateChildSpawnerClass(int count, int actorKind)
{
    SpawnerClass *objectClass = CreateByteGrid(0x88, 0x2a8, count);

    objectClass->unk_84 = 0;
    objectClass->unk_50 = 1;
    objectClass->shapeKind = 3;
    objectClass->sizeX = 0x7800;
    objectClass->sizeY = 0x1800;
    objectClass->sizeZ = 0x7800;
    objectClass->actorKind = actorKind;
    objectClass->unk_82 = 0xff;
    objectClass->linkId = -1;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = FieldObject_RespawnSegmented;
    objectClass->hooks[3] = FreeFieldObjectClassAnimationBuffers;
    objectClass->hooks[4] = ReleaseChildObjects;
    objectClass->hooks[6] = FreeFieldObjectShapeStorage;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[10] = ChildSpawner_GetPosition;
    objectClass->hooks[9] = SetFieldObjectPosition;
    objectClass->hooks[11] = ChildSpawner_ApplyHitTrue;
    objectClass->hooks[12] = ChildSpawner_QueryHitFalse;
    objectClass->hooks[15] = DrawChildSpawner;
    objectClass->classType = 12;
    return objectClass;
}
