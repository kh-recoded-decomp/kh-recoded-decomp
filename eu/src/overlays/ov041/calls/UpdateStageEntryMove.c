#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);

/* Runs an entry's move (out, pause, back to its grid place); TRUE when it has none or it just ended. */
BOOL UpdateStageEntryMove(StageEntry *entry, fx32 step)
{
    StageEntryMove *move = &entry->move;
    BOOL done = FALSE;
    VecFx32 from;
    VecFx32 to;

    if (move->phase == STAGE_MOVE_IDLE) {
        return TRUE;
    }
    switch (move->phase) {
    case STAGE_MOVE_OUT:
        if (!StepEntryMotion(entry, step)) {
            break;
        }
        move->motion.elapsed = 0;
        move->phase = STAGE_MOVE_PAUSE;
    case STAGE_MOVE_PAUSE:
        if (move->motion.elapsed < move->pause) {
            move->motion.elapsed += FX32_ONE;
            break;
        }
        GetEntryPosition(&from, entry);
        GetStageGridPosition(&to, entry->row, entry->column);
        StartStageEntryMotion(entry, &from, &to, move->duration, STAGE_MOTION_STEADY);
        move->phase = STAGE_MOVE_BACK;
    case STAGE_MOVE_BACK:
        if (StepEntryMotion(entry, step)) {
            move->phase = STAGE_MOVE_IDLE;
            done = TRUE;
        }
        break;
    }
    return done;
}
