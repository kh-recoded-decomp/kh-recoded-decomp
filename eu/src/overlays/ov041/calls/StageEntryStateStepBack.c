#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ReleaseEntryStatusItem(u8 entryIndex);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);

/*
 * Entry state handler for a player entry stepping back: drops its status effect, and when asked to step back
 * walks 15 units back over 60 frames (or skips it under work flag 0x20) before returning to its idle animation.
 */
void StageEntryStateStepBack(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    VecFx32 start[1];
    VecFx32 end;
    VecFx32 ground;

    if (entry->flags & STAGE_ENTRY_ENEMY) {
        return;
    }
    switch (entry->stateStep) {
    case 0:
        ReleaseEntryStatusItem(entry->index);
        entry->stateStep++;
    case 1:
        if (!(entry->flags & STAGE_ENTRY_STEP_BACK)) {
            break;
        }
        if (work->flags & 0x20) {
            entry->flags &= ~STAGE_ENTRY_STEP_BACK;
            entry->stateStep = 3;
            return;
        }
        GetPositionAboveGround(&ground, entry);
        start[0] = ground;
        end = start[0];
        end.x -= 15 * FX32_ONE;
        StartStageEntryMotion(entry, start, &end, 60 * FX32_ONE, STAGE_MOTION_STEADY);
        SetSceneEntryAnimation(entry, entry->stepAnimation, 1, 0);
        entry->stateStep++;
    case 2:
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->flags &= ~STAGE_ENTRY_STEP_BACK;
        SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
        entry->stateStep++;
        break;
    case 3:
        break;
    }
}
