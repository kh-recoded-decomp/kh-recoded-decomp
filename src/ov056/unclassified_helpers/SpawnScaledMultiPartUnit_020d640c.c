#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    s32 x;
    s32 y;
    s32 z;
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x30];
    s32 field_38;
    u8 pad_3c[0x10];
    s32 field_4c;
    u8 pad_50[0x10];
} UnitParams;

typedef struct {
    u32 baseId;
    s32 ownerId;
    u8 pad_08[0xc];
    s32 team;
} Spawner;

typedef struct {
    u8 data[0x84];
} PartRecord;

typedef struct {
    u8 pad_000[0x150];
    PartRecord *record;
} UnitPart;

typedef struct {
    u8 pad_000[0x8];
    UnitPart *parts;
    u8 pad_00c[0x9];
    u8 partCount;
    u8 pad_016[0x6];
    void *updateCallback;
    void *drawCallback;
    u8 pad_024[4];
    void *callback_28;
    u8 pad_02c[8];
    void *callback_34;
    void *callback_38;
    u8 pad_03c[2];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    s32 scaleSq;
    s32 y;
    s32 z;
    s32 scale;
    PartRecord *records;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity_020ae844(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24_020aec8c(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters_020aeca4(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries_020ab010(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern s32 FixedPointMultiply12(s32 a, s32 b);
extern void func_ov056_020d6634(void);
extern void func_ov021_020aeacc(void);
extern void func_ov021_020ae73c(void);
extern void func_ov056_020d6718(void);
extern void func_ov021_020aec08(void);
extern void LoadUnitSharedRecords_020aee14(SpawnedUnit *unit, u32 baseId, u32 kind);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);

SpawnedUnit *SpawnScaledMultiPartUnit_020d640c(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    int i;
    SpawnParams spawn;
    UnitParams params;

    unit = AllocEntity_020ae844(spawner->ownerId, -1, 0x1a0, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24_020aec8c(spawner, &spawn);
    InitializeUnitParameters_020aeca4(unit, &spawn, &params);
    params.mode = 0x800;
    params.field_38 = 9;
    params.field_4c = 2;
    i = 0;
    params.flags = 0;
    unit->scaleSq = FixedPointMultiply12(spawn.x, spawn.x);
    unit->y = spawn.y;
    unit->z = spawn.z;
    unit->scale = 0x1000;
    SetupOwnerAndEntries_020ab010(unit,
        ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (spawner->baseId & 0x1ff),
        ((spawner->baseId + 2) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        &params, 1, spawner->team);
    unit->updateCallback = func_ov056_020d6634;
    unit->drawCallback = func_ov021_020aeacc;
    unit->callback_28 = func_ov021_020ae73c;
    unit->callback_38 = func_ov056_020d6718;
    unit->callback_34 = func_ov021_020aec08;
    LoadUnitSharedRecords_020aee14(unit, spawner->baseId, kind);
    unit->records = NNSi_FndAllocFromDefaultHeap_0202a178(unit->partCount * sizeof(PartRecord));
    for (; i < unit->partCount; i++) {
        unit->parts[i].record = &unit->records[i];
    }
    return unit;
}
