#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"
#include "src/overlays/ov041/StageOrbs.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void UpdateStageOrb(StageOrb *orb, StageOrbPool *pool, StageEntry *collector, const VecFx32 *target);
extern void SetStageOrbPhase(StageOrb *orb, int phase);

/* Moves a burst's orbs towards their collector, dropping the ones collected; 20 frames in, the rest start
 * homing. The burst stays active while any orb flies. */
void UpdateStageOrbBurst(StageOrbBurst *burst, StageOrbPool *pool)
{
    VecFx32 target;
    VecFx32 sum;
    BOOL active;
    int count;
    int i;

    VEC_Add(&burst->collector->slot.node.position, &burst->collector->overheadOffset, &sum);
    target = sum;
    active = FALSE;
    count = burst->count;
    for (i = 0; i < count; i++) {
        if (burst->orbs[i] != -1) {
            UpdateStageOrb(&pool->orbs[burst->orbs[i]], pool, burst->collector, &target);
            if (pool->orbs[burst->orbs[i]].phase != STAGE_ORB_FREE) {
                active = TRUE;
            } else {
                burst->orbs[i] = -1;
            }
        }
    }
    if (burst->timer < (20 << FX32_SHIFT)) {
        burst->timer += FX32_ONE;
        if (burst->timer >= (20 << FX32_SHIFT)) {
            for (i = 0; i < count; i++) {
                if (burst->orbs[i] != -1) {
                    SetStageOrbPhase(&pool->orbs[burst->orbs[i]], STAGE_ORB_HOMING);
                }
            }
        }
    }
    burst->active = active;
}
