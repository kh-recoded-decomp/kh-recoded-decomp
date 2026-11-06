#include "nitro/types.h"

#pragma explicit_zero_data on

extern void FreeSlotBuffers(void);
extern void FreeSlotBuffers_020d641c(void);
extern void FreeSlotBuffers_020d6788(void);
extern void FreeSlotBuffers_020d7060(void);
extern void FreeSlotBuffers_020d788c(void);
extern void ReleaseEffectPool(void);
extern void ReleaseEffectPool_020d450c(void);
extern void FreeSlotTrackerUnitSlots(void);
extern void FreeSceneModelSlotArray(void);

void *gEffectSourceKindReleaseHandlers[20] = {
    NULL,
    (void *)ReleaseEffectPool_020d450c,
    NULL,
    NULL,
    (void *)FreeSlotTrackerUnitSlots,
    (void *)FreeSlotBuffers,
    NULL,
    NULL,
    NULL,
    (void *)FreeSlotBuffers_020d641c,
    (void *)FreeSlotBuffers_020d641c,
    (void *)FreeSlotBuffers_020d6788,
    (void *)FreeSceneModelSlotArray,
    (void *)FreeSlotTrackerUnitSlots,
    NULL,
    (void *)FreeSlotBuffers_020d7060,
    NULL,
    (void *)FreeSlotBuffers_020d788c,
    NULL,
    (void *)ReleaseEffectPool,
};
