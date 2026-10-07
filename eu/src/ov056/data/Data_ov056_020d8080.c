#include "nitro/types.h"

#pragma explicit_zero_data on

extern void SpawnArcUnitFromSpawner(void);
extern void SpawnBounceShooterUnit(void);
extern void SpawnEffectUnitFromSpawner(void);
extern void SpawnEntityFromSpawner(void);
extern void SpawnGroupedAttackUnit(void);
extern void SpawnGroupedMultiPartUnit(void);
extern void SpawnGroupedTrackerUnit(void);
extern void SpawnMultiPartUnit(void);
extern void SpawnPairedEntryUnit(void);
extern void SpawnPartRecordUnit(void);
extern void SpawnScaledMultiPartUnit(void);
extern void SpawnSlotTrackerUnit(void);
extern void SpawnSpiralProjectile(void);
extern void SpawnTimedUnitFromSpawner(void);
extern void SpawnUnitFromSpawner(void);

void *data_ov056_020d8080[20] = {
    (void *)SpawnPairedEntryUnit,
    (void *)SpawnEffectUnitFromSpawner,
    (void *)SpawnPairedEntryUnit,
    (void *)SpawnEntityFromSpawner,
    (void *)SpawnSlotTrackerUnit,
    (void *)SpawnGroupedMultiPartUnit,
    (void *)SpawnGroupedTrackerUnit,
    (void *)SpawnGroupedTrackerUnit,
    (void *)SpawnGroupedTrackerUnit,
    (void *)SpawnGroupedAttackUnit,
    (void *)SpawnGroupedAttackUnit,
    (void *)SpawnScaledMultiPartUnit,
    (void *)SpawnBounceShooterUnit,
    (void *)SpawnSlotTrackerUnit,
    (void *)SpawnArcUnitFromSpawner,
    (void *)SpawnPartRecordUnit,
    (void *)SpawnUnitFromSpawner,
    (void *)SpawnMultiPartUnit,
    (void *)SpawnTimedUnitFromSpawner,
    (void *)SpawnSpiralProjectile,
};
