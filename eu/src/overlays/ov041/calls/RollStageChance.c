#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern u32 func_0202a9e4(u32 range);

/* A one-in-five roll, never won while either skip flag is set. */
BOOL RollStageChance(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL won = FALSE;

    if (func_0202a9e4(100) < 20) {
        won = TRUE;
    }
    if (work->flags & STAGE_WORK_SKIP_CHANCE_B) {
        won = FALSE;
    }
    if (work->flags & STAGE_WORK_SKIP_CHANCE_A) {
        won = FALSE;
    }
    return won;
}
