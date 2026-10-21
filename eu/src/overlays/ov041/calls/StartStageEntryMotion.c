#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void StartStageMotion(VecFx32 *position, StageMotion *motion, const VecFx32 *start, const VecFx32 *end,
                             fx32 duration, int profile);

/* Starts moving an entry from start to end. */
void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration, int profile)
{
    StartStageMotion(&entry->slot.node.position, &entry->motion, start, end, duration, profile);
}
