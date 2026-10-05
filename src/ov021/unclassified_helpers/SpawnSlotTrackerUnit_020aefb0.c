#include "nitro/types.h"

typedef struct UnitSetup {
    int kind;
    int unk04;
    u8 pad08[0x52];
    u16 unk5a;
    u8 pad5c[4];
} UnitSetup;

typedef struct SpawnParams {
    u8 pad00[8];
    int unk08;
    u8 pad0c[4];
    int unk10;
    u8 pad14[0x40];
    int mode;
    int unk58;
    int unk5c;
} SpawnParams;

typedef struct Spawner {
    u32 entryId;
    s32 ownerId;
    u8 pad08[0xc];
    s32 slotCount;
} Spawner;

typedef struct TrackerSlot {
    s8 id;
    u8 pad01[0x1f];
    int target;
} TrackerSlot;

typedef struct TrackerUnit {
    u8 pad000[0x1c];
    void *updateCallback;
    void *drawCallback;
    u8 pad024[8];
    void *callback2c;
    u8 pad030[0xe];
    s8 slotCount;
    u8 pad03f[0x149];
    u16 value;
    u8 pad18a[2];
    TrackerSlot *slots;
    u8 mode;
    s8 unk191;
    u8 pad192[2];
    int unk194;
    int unk198;
    int unk19c;
    u8 pad1a0[4];
} TrackerUnit;

extern TrackerUnit *AllocEntity_020ae844(s32 ownerId, s32 entityId, u32 size, u32 kind);
extern void CopyWordArray24_020aec8c(Spawner *spawner, SpawnParams *params);
extern void InitializeUnitParameters_020aeca4(TrackerUnit *unit, SpawnParams *params, UnitSetup *setup);
extern u32 func_ov001_0206dba0(int index);
extern void SetupOwnerAndEntries_020ab010(TrackerUnit *unit, u32 first, u32 second, UnitSetup *setup, int mode, int value);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_ov021_020ae0a4(void);
extern void func_ov021_020adfd4(void);
extern void func_ov021_020ae658(void);
extern void LoadUnitSharedRecords_020aee14(TrackerUnit *unit, u32 entryId, u32 kind);

#define MAKE_ENTRY_KEY(entryId) (((((func_ov001_0206dba0(0) + 0x8000) & 0xfffffc) << 7) | 0x80000000) | ((entryId) & 0x1ff))

TrackerUnit *SpawnSlotTrackerUnit_020aefb0(Spawner *spawner, u16 value, u32 kind)
{
    TrackerUnit *unit;
    SpawnParams params;
    UnitSetup setup;
    int interval;
    int i;

    unit = AllocEntity_020ae844(spawner->ownerId, -1, sizeof(TrackerUnit), kind);
    unit->slotCount = spawner->slotCount;
    unit->value = value;
    CopyWordArray24_020aec8c(spawner, &params);
    InitializeUnitParameters_020aeca4(unit, &params, &setup);
    setup.kind = 0x1006;
    setup.unk04 = 2;
    if (params.mode != 3) {
        setup.unk5a = 1;
    }
    switch (params.mode) {
    case 1:
        interval = 5;
        break;
    case 2:
        interval = 15;
        break;
    default:
        interval = 10;
        break;
    }
    i = 0;
    SetupOwnerAndEntries_020ab010(unit, MAKE_ENTRY_KEY(spawner->entryId), MAKE_ENTRY_KEY(spawner->entryId + 2), &setup, 1, interval);
    unit->drawCallback = func_ov021_020ae0a4;
    unit->updateCallback = func_ov021_020adfd4;
    unit->callback2c = func_ov021_020ae658;
    unit->slots = NNSi_FndAllocFromDefaultHeap_0202a178(unit->slotCount * sizeof(TrackerSlot));
    for (; i < unit->slotCount; i++) {
        TrackerSlot *slots = unit->slots;
        slots[i].id = -1;
        slots[i].target = 0;
    }
    unit->mode = params.mode;
    unit->unk198 = params.unk10;
    unit->unk191 = params.unk58;
    unit->unk194 = params.unk5c;
    unit->unk19c = params.unk08;
    LoadUnitSharedRecords_020aee14(unit, spawner->entryId, kind);
    return unit;
}
