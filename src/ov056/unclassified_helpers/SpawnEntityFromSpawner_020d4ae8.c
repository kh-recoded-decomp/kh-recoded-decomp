#include "nitro/types.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2C];
    s32 unk_34;
    u8 pad_38[0x1C];
    s32 unk_54;
    u8 pad_58[8];
} SpawnParams;

typedef struct {
    s32 unk_00;
    s32 ownerId;
    u8 pad_08[0xC];
    s32 unk_14;
} Spawner;

typedef struct {
    u8 pad_000[0x1C];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[0x1A];
    u8 unk_3E;
    u8 pad_03F[0x139];
    s32 unk_178;
    s32 unk_17C;
    u8 pad_180[4];
    s32 unk_184;
    u16 unk_188;
    u8 pad_18A[2];
    s32 unk_18C;
    u8 pad_190[4];
    s32 unk_194;
    u8 pad_198[0xC];
    void *applyCallback;
} SpawnedEntity;

extern SpawnedEntity *AllocEntity_020ae844(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24_020aec8c(Spawner *spawner, SpawnParams *params);
extern void func_ov056_020d4c80(void);
extern void func_ov021_020aeacc(void);
extern void NotifyOwnerThenApplyScaledValue_020d4dfc(void);
extern void ComputeAndApplyLevelScaledValue_020d4d5c(void);
extern void func_ov021_020aee14(SpawnedEntity *entity, s32 arg, u32 kind);

SpawnedEntity *SpawnEntityFromSpawner_020d4ae8(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedEntity *entity;
    SpawnParams params;

    entity = AllocEntity_020ae844(spawner->ownerId, -1, sizeof(SpawnedEntity), kind);
    entity->unk_3E = spawner->unk_14;
    entity->unk_188 = value;
    CopyWordArray24_020aec8c(spawner, &params);
    entity->unk_178 = params.unk_00;
    entity->unk_184 = params.unk_34;
    entity->unk_17C = params.unk_04;
    entity->updateCallback = func_ov056_020d4c80;
    entity->drawCallback = func_ov021_020aeacc;
    entity->unk_18C = 0;
    entity->unk_194 = 0;
    if (params.unk_54 == 1) {
        entity->applyCallback = NotifyOwnerThenApplyScaledValue_020d4dfc;
    } else {
        entity->applyCallback = ComputeAndApplyLevelScaledValue_020d4d5c;
    }
    func_ov021_020aee14(entity, spawner->unk_00, kind);
    return entity;
}
