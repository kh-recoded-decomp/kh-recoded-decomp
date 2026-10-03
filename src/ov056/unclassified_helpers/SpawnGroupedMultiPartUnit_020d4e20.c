#include "nitro/types.h"

#define ARCHIVE_FILE_KEY(id) (0x80000000 | (((func_ov001_0206dba0(0) + 0x8000) & 0xFFFFFC) << 7) | ((id) & 0x1ff))

typedef struct {
    u8 pad_00[0x54];
    s32 x;
    s32 y;
    s32 z;
} SpawnParams;

typedef struct {
    s32 mode;
    s32 flags;
    u8 pad_08[0x2c];
    s32 field_34;
    u8 pad_38[0x28];
} UnitParams;

typedef struct {
    s32 resourceId;
    u32 animationKey;
    s32 slotCount;
    u32 modelKey;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u32 baseId;
    s32 ownerId;
    u8 pad_08[0xc];
    s32 team;
} Spawner;

typedef struct {
    u8 pad_000[0x22c];
    u32 marker;
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
    u8 pad_024[8];
    void *hitCallback;
    u8 pad_030[0xe];
    u8 team;
    u8 pad_03f[0x188 - 0x3f];
    u16 value;
    s32 x;
    PartRecord *records;
    s16 groupId;
} SpawnedUnit;

extern SpawnedUnit *AllocEntity_020ae844(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24_020aec8c(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters_020aeca4(SpawnedUnit *unit, SpawnParams *params, UnitParams *out);
extern s32 func_ov001_0206dba0(s32 arg);
extern void SetupOwnerAndEntries_020ab010(SpawnedUnit *unit, u32 first, u32 second, UnitParams *params, s32 x, s32 y);
extern void func_ov021_020aeb84(void);
extern void func_ov021_020aeacc(void);
extern void func_ov056_020d54dc(void);
extern void LoadUnitSharedRecords_020aee14(SpawnedUnit *unit, u32 baseId, u32 kind);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern int func_ov021_020a89a8(EntryGroupDesc *desc);

SpawnedUnit *SpawnGroupedMultiPartUnit_020d4e20(Spawner *spawner, u16 value, u32 kind)
{
    SpawnedUnit *unit;
    int i;
    PartRecord *record;
    SpawnParams spawn;
    UnitParams params;
    EntryGroupDesc desc;

    unit = AllocEntity_020ae844(spawner->ownerId, -1, 0x198, kind);
    unit->team = spawner->team;
    unit->value = value;
    CopyWordArray24_020aec8c(spawner, &spawn);
    InitializeUnitParameters_020aeca4(unit, &spawn, &params);
    params.mode = 0x20;
    params.field_34 = 9;
    unit->x = spawn.x;
    i = 0;
    SetupOwnerAndEntries_020ab010(unit,
        (spawner->baseId & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        ((spawner->baseId + 2) & 0x1ff) | ((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000),
        &params, 1, spawner->team);
    unit->updateCallback = func_ov021_020aeb84;
    unit->drawCallback = func_ov021_020aeacc;
    unit->hitCallback = func_ov056_020d54dc;
    LoadUnitSharedRecords_020aee14(unit, spawner->baseId, kind);
    unit->records = NNSi_FndAllocFromDefaultHeap_0202a178(unit->partCount * sizeof(PartRecord));
    for (; i < unit->partCount; i++) {
        record = &unit->records[i];
        unit->parts[i].record = record;
        record->marker &= 0xffff;
    }
    ZeroBytes0x14_020a8adc(&desc);
    desc.modelKey = ARCHIVE_FILE_KEY(spawner->baseId + 3);
    desc.animationKey = ARCHIVE_FILE_KEY(spawner->baseId + 4);
    desc.slotCount = 8;
    unit->groupId = func_ov021_020a89a8(&desc);
    return unit;
}
