#include "nitro/types.h"
#include "src/overlays/ov041/StageOrbs.h"

extern void StartStageOrb(StageOrb *orb, StageOrbPool *pool, const VecFx32 *position, fx32 value);

/* Starts the first free orb of the pool; returns its index, or -1 when all are in use. */
int SpawnStageOrb(StageOrbPool *pool, const VecFx32 *position, fx32 value)
{
    int i;

    for (i = 0; i < STAGE_ORB_COUNT; i++) {
        if (pool->orbs[i].phase == STAGE_ORB_FREE) {
            StartStageOrb(&pool->orbs[i], pool, position, value);
            return i;
        }
    }
    return -1;
}
