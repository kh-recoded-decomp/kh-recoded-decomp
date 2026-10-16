#ifndef RECODED_HIT_ENTRY_POOL_H
#define RECODED_HIT_ENTRY_POOL_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EntryDesc {
    u32 flags;
    s32 mode;
    s16 turnRate;
    u16 unknown0a;
    fx32 value0c;
    fx32 value10;
    fx32 speed;
    fx32 range;
    fx32 lifetime;
    fx32 value20;
    fx32 value24;
    fx32 homingDelay;
    u32 unknown2c;
    s32 value30;
    u8 unknown34[8];
    s32 value3c;
    VecFx32 vector40;
    s32 value4c;
    s32 value50;
    fx32 value54;
    s16 index58;
    s16 index5a;
    s8 group;
    u8 modeLow : 4;
    u8 modeHigh : 4;
    u16 unknown5e;
} EntryDesc;

typedef struct HitUnit HitUnit;
typedef struct HitEvent HitEvent;
typedef struct EntryOwner {
    u8 unknown00[0x2c];
    BOOL (*move)(void *attacker, HitUnit *unit, fx32 step);
    u8 unknown30[8];
    void (*onHit)(s32 *entryIndex, HitUnit *unit, HitEvent *event);
} EntryOwner;

typedef struct HitRecord {
    u8 unknown00[0x14];
    s32 value14;
    s32 value18;
    u8 unknown1c[0x54 - 0x1c];
} HitRecord;

typedef struct HitContext {
    u8 unknown00[0x40];
    s16 recordIndex;
    u16 unknown42;
    HitRecord *records;
} HitContext;

typedef struct HitActor {
    u8 unknown00[8];
    s32 id;
    u8 unknown0c[0x6c - 0xc];
    HitContext *context;
    u8 unknown70[0x14];
    EntryOwner *entries;
} HitActor;

typedef char EntryDescSize[sizeof(EntryDesc) == 0x60 ? 1 : -1];
typedef char HitRecordSize[sizeof(HitRecord) == 0x54 ? 1 : -1];

extern void ResetMotionState(EntryDesc *desc);
extern u32 GetResourceArchiveId(u32 index);
extern void SetupOwnerAndEntries(void *owner, int first, int second,
                                 EntryDesc *descs, int descCount, int slotCount);
extern BOOL AdvanceHitUnit(void *attacker, HitUnit *unit, fx32 step);
extern BOOL UpdateHomingProjectile(void *attacker, HitUnit *unit, fx32 step);
extern void SpawnEventHitMarker(s32 *entryIndex, HitUnit *unit, HitEvent *event);

static inline void SetEntryVector(VecFx32 *vector, fx32 x, fx32 y, fx32 z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

#endif
