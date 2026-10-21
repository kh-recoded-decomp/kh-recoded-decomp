#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void EnterPendingPanelState(fx32 duration);

/* Ends a running panel transition, moving the panels to their pending state. */
void FinishStagePanelTransition(fx32 duration)
{
    StageWork *work = gMovieContextState->stageWork;

    if (work->flags & STAGE_WORK_FAST_PANELS) {
        duration = FX_Div(duration, 0x100);
    }
    if (work->flags & STAGE_WORK_PANEL_MOVING) {
        EnterPendingPanelState(duration);
        work->flags &= ~STAGE_WORK_PANEL_MOVING;
    }
}
