#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void StartScaledPanelTransition(const VecFx32 *target, fx32 distance, fx32 duration);

/* Starts the panel transition (16 times as fast in the fast mode) and marks it as running. */
void StartStagePanelTransition(const VecFx32 *target, fx32 distance, fx32 duration)
{
    StageWork *work = gMovieContextState->stageWork;

    if (work->flags & STAGE_WORK_FAST_PANELS) {
        duration = FX_Div(duration, 0x100);
    }
    StartScaledPanelTransition(target, distance, duration);
    work->flags |= STAGE_WORK_PANEL_MOVING;
}
