#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

typedef float f32;

/* A whole frame count as fx32, rounded the way the converter of the original tools did. */
#define FRAME_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))

extern u8 GetFarthestEnemyRow(void);
extern void ReleaseEntryStatusItem(u8 entryIndex);
extern void SetEntryState(StageEntry *entry, int state);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern void UpdateEntryStatusItem(u8 entryIndex);

static inline VecFx32 GroundPosition(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    return position;
}

static inline VecFx32 GridPosition(u8 row, u8 column)
{
    VecFx32 position;

    GetStageGridPosition(&position, row, column);
    return position;
}

/*
 * Entry state handler for an entry too far from the enemies: walks it forward to three rows off the farthest
 * enemy row (12 frames a row), then back to idle and to the state it came from.
 */
void StageEntryStateAdvance(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    u8 row = entry->row;
    u8 distance = row - GetFarthestEnemyRow();

    switch (entry->stateStep) {
    case 0:
        ReleaseEntryStatusItem(entry->index);
        if (distance > 3) {
            entry->stateStep++;
        } else {
            SetEntryState(entry, entry->previousState);
            entry->stateStep = 3;
            return;
        }
    case 1: {
        u8 rows = distance - 3;
        u8 frames = rows * 12;
        VecFx32 start = GroundPosition(entry);
        VecFx32 end = GridPosition(entry->row - rows, entry->column);

        StartStageEntryMotion(entry, &start, &end, FRAME_TO_FX32(frames), STAGE_MOTION_STEADY);
        SetSceneEntryAnimation(entry, entry->stepAnimation, 1, 0);
        entry->stateStep++;
    }
    case 2:
        if (StepEntryMotion(entry, work->frameStep)) {
            entry->row -= (s8)(distance - 3);
            SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
            SetEntryState(entry, entry->previousState);
            UpdateEntryStatusItem(entry->index);
        }
        break;
    default:
        return;
    }
}
