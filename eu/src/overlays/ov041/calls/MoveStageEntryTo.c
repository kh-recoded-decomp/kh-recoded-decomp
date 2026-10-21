#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);

/* Starts moving an entry at a steady speed to a destination, to pause there and come back (UpdateStageEntryMove). */
void MoveStageEntryTo(StageEntry *entry, const VecFx32 *destination, fx32 duration, fx32 pause)
{
    StageEntryMove *move = &entry->move;
    VecFx32 position;

    move->phase = STAGE_MOVE_OUT;
    move->pause = pause;
    move->duration = duration;
    GetEntryPosition(&position, entry);
    StartStageEntryMotion(entry, &position, destination, move->duration, STAGE_MOTION_STEADY);
}
