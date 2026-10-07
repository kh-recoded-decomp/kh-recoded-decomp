#include "nitro/types.h"

#pragma explicit_zero_data on

extern void AttachEffectToEntry(void);
extern void InitSlotOwnerFromDesc(void);
extern void InitSlotOwnerWithOrigin(void);
extern void SpawnEffectParticle(void);
extern void SpawnEmitterSound(void);
extern void SpawnEntryProjectile(void);
extern void SpawnIndexedProjectile(void);
extern void SpawnRecordedProjectile(void);
extern void SpawnSlotProjectile(void);
extern void SpawnSlotRequestProjectile(void);
extern void SpawnTrailProjectile(void);
extern void SpawnUnitProjectile(void);
extern void StartGaugeRewardEffect(void);
extern void func_ov030_020bcec0(void);

void *data_ov056_020d80d0[20] = {
    (void *)SpawnUnitProjectile,
    (void *)SpawnUnitProjectile,
    (void *)SpawnUnitProjectile,
    (void *)StartGaugeRewardEffect,
    (void *)SpawnEffectParticle,
    (void *)SpawnSlotRequestProjectile,
    (void *)InitSlotOwnerFromDesc,
    (void *)InitSlotOwnerFromDesc,
    (void *)InitSlotOwnerFromDesc,
    (void *)SpawnIndexedProjectile,
    (void *)SpawnIndexedProjectile,
    (void *)SpawnTrailProjectile,
    (void *)SpawnRecordedProjectile,
    (void *)SpawnEffectParticle,
    (void *)InitSlotOwnerWithOrigin,
    (void *)SpawnSlotProjectile,
    (void *)SpawnEntryProjectile,
    (void *)SpawnEmitterSound,
    (void *)AttachEffectToEntry,
    (void *)func_ov030_020bcec0,
};
