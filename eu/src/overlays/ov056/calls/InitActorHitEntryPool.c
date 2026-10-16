#include "src/overlays/ov056/HitEntryPool.h"

#pragma opt_propagation off
void InitActorHitEntryPool(void *unused, HitActor *actor)
{
    /* Initializes one hit-entry slot using resource records 42 and 43. */
    EntryDesc desc;
    HitRecord *record = &actor->context->records[actor->context->recordIndex];
    u32 first;
    u32 second;

    ResetMotionState(&desc);
    desc.flags = 0x1006;
    desc.mode = 2;
    desc.value10 = 0x800;
    desc.value0c = 0x5000;
    desc.lifetime = -0x1000;
    desc.index5a = desc.lifetime >> 12;
    desc.index58 = desc.index5a;
    SetEntryVector(&desc.vector40, 0, record->value18, record->value14);
    int entryCount = 1;
    desc.value30 = 0;
    desc.value3c = 1;
    desc.group = entryCount;
    first = GetResourceArchiveId(3);
    second = GetResourceArchiveId(3);
    SetupOwnerAndEntries(actor->entries,
                         (((first + 0x8000) & 0x00fffffc) << 7) | 0x8000002a,
                         (((second + 0x8000) & 0x00fffffc) << 7) | 0x8000002b,
                         &desc, entryCount, entryCount);
    actor->entries->move = AdvanceHitUnit;
    actor->entries->onHit = SpawnEventHitMarker;
}
