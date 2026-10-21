#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL StepStageMotion(VecFx32 *position, StageMotion *motion, fx32 step);

/* Moves an entry step frames along its motion; TRUE once it is over. */
BOOL StepEntryMotion(StageEntry *entry, fx32 step)
{
    return StepStageMotion(&entry->slot.node.position, &entry->move.motion, step);
}
