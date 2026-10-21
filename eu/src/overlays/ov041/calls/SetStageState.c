#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern StageStateFunc gStageStateHandlers[];

/* Moves the stage to another state (restarting its step and timer) and, when asked, runs its handler now. */
void SetStageState(int state, BOOL runNow)
{
    StageWork *work = gMovieContextState->stageWork;

    if (state == work->state) {
        return;
    }
    work->state = state;
    work->stateStep = 0;
    work->stateTimer = 0;
    if (runNow) {
        gStageStateHandlers[work->state]();
    }
}
