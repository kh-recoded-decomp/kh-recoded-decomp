#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"
#include "src/overlays/ov041/StageOrbs.h"

extern const fx32 gStageOrbValues[3];
extern int GetScaleLevel(fx32 value);
extern int SpawnStageOrb(StageOrbPool *pool, const VecFx32 *position, fx32 value);

/* Throws out orbs worth amount hp in total (each as big as what is left allows) at position, all to be
 * collected by collector. */
void StartStageOrbBurst(StageOrbBurst *burst, StageOrbPool *pool, StageEntry *collector, const VecFx32 *position,
                         fx32 amount)
{
    fx32 value;
    int i;

    burst->count = 0;
    while (amount > 0) {
        value = gStageOrbValues[GetScaleLevel(amount)];
        burst->orbs[burst->count] = SpawnStageOrb(pool, position, value);
        amount -= value;
        burst->count++;
    }
    for (i = burst->count; i < STAGE_ORB_BURST_MAX; i++) {
        burst->orbs[i] = -1;
    }
    burst->collector = collector;
    burst->timer = 0;
    burst->active = TRUE;
}
