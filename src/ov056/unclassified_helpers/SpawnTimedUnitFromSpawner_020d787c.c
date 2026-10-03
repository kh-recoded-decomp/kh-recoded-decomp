#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    s32 lifetime;
    u8 pad_58[8];
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x58];
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
    u8 pad_024[8];
    void *hitCallback;
    u8 pad_030[0xe];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    u8 pad_18a[2];
    s32 lifetime;
    u8 pad_190[4];
    s32 timer;
    s32 phase;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity_020ae844(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24_020aec8c(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters_020aeca4(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries_020ab010(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern void func_ov056_020d7bcc(void);
extern void func_ov056_020d7ad0(void);
extern void func_ov056_020d7c4c(void);
extern void LoadUnitSharedRecords_020aee14(SpawnedUnit *unit, u32 baseId, u32 kind);

SpawnedUnit *SpawnTimedUnitFromSpawner_020d787c(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    SpawnParams spawn;
    UnitParams params;

    unit = AllocEntity_020ae844(spawner->ownerId, -1, 0x1a8, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24_020aec8c(spawner, &spawn);
    InitializeUnitParameters_020aeca4(unit, &spawn, &params);
    params.mode = 0x1006;
    params.flags = 2;
    SetupOwnerAndEntries_020ab010(unit,
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (spawner->baseId & 0x1ff),
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | ((spawner->baseId + 2) & 0x1ff),
        &params, 1, spawner->team);
    unit->drawCallback = func_ov056_020d7bcc;
    unit->updateCallback = func_ov056_020d7ad0;
    unit->hitCallback = func_ov056_020d7c4c;
    unit->lifetime = spawn.lifetime;
    unit->phase = 0;
    unit->timer = 0;
    LoadUnitSharedRecords_020aee14(unit, spawner->baseId, kind);
    return unit;
}
