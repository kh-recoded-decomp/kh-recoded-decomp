#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern StageStateFunc data_ov041_020cf8e0[];

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
        data_ov041_020cf8e0[work->state]();
    }
}
