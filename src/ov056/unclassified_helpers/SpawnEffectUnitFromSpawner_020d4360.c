#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5c];
    s32 lifetime;
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x44];
    s32 layer;
    u8 pad_50[0x10];
} UnitParams;

typedef struct {
    u32 baseId;
    s32 ownerId;
    u8 pad_08[0xc];
    s32 team;
} Spawner;

typedef struct {
    u8 pad_000[0x1c];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[0x10];
    void *hitCallback;
    void *eventCallback;
    u8 pad_03c[2];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    u8 pad_18a[2];
    u8 effects[8];
    s32 lifetime;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity_020ae844(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24_020aec8c(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters_020aeca4(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries_020ab010(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern void DrawWithVariantMaterialsHidden_020d4470(void);
extern void func_ov056_020d4458(void);
extern void SpawnEffectOnEvent_020d44fc(void);
extern void func_ov021_020aec08(void);
extern void func_ov056_020d7de8(void *effects, u32 baseId, s32 count, u32 kind);
extern void LoadUnitSharedRecords_020aee14(SpawnedUnit *unit, u32 baseId, u32 kind);

SpawnedUnit *SpawnEffectUnitFromSpawner_020d4360(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    SpawnParams spawn;
    UnitParams params;

    unit = AllocEntity_020ae844(spawner->ownerId, -1, 0x198, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24_020aec8c(spawner, &spawn);
    InitializeUnitParameters_020aeca4(unit, &spawn, &params);
    params.mode = 6;
    params.flags = 0;
    params.layer = 2;
    SetupOwnerAndEntries_020ab010(unit,
        (spawner->baseId & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        ((spawner->baseId + 2) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        &params, 1, spawner->team);
    unit->drawCallback = DrawWithVariantMaterialsHidden_020d4470;
    unit->updateCallback = func_ov056_020d4458;
    unit->eventCallback = SpawnEffectOnEvent_020d44fc;
    unit->hitCallback = func_ov021_020aec08;
    func_ov056_020d7de8(unit->effects, spawner->baseId, 6, kind);
    unit->lifetime = spawn.lifetime;
    LoadUnitSharedRecords_020aee14(unit, spawner->baseId, kind);
    return unit;
}
