#include "src/overlays/ov056/HitEntryPool.h"

#pragma opt_propagation off
void InitHomingProjectilePool(void *unused, HitActor *actor)
{
    /* Configures three homing slots using resource records 70 and 71. */
    EntryDesc desc;
    u32 first;
    u32 second;

    ResetMotionState(&desc);
    desc.flags = 2;
    desc.mode = 0;
    desc.turnRate = 0x333;
    desc.value0c = 0x800;
    desc.range = 12 << 12;
    desc.value20 = 0x1000;
    desc.speed = 0x99a;
    desc.lifetime = 45 << 12;
    desc.value24 = 0x1000;
    desc.value50 = 0;
    desc.value54 = 0x1000;
    desc.homingDelay = 6 << 12;
    desc.value4c = 2;
    desc.index58 = actor->id;
    desc.index5a = 1;
    SetEntryVector(&desc.vector40, 0x100, 0, 0x100);
    int entryCount = 1;
    int slotCount = 3;
    desc.value30 = 0;
    desc.group = slotCount;
    first = GetResourceArchiveId(3);
    second = GetResourceArchiveId(3);
    SetupOwnerAndEntries(actor->entries,
                         (((first + 0x8000) & 0x00fffffc) << 7) | 0x80000046,
                         (((second + 0x8000) & 0x00fffffc) << 7) | 0x80000047,
                         &desc, entryCount, slotCount);
    actor->entries->move = UpdateHomingProjectile;
    actor->entries->onHit = SpawnEventHitMarker;
}
