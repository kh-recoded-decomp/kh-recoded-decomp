#include "nitro/types.h"
#include "src/overlays/ov001/FieldProgressState.h"
#include "src/overlays/ov041/StageWork.h"

extern FieldProgressState *gFieldSessionWork;
extern s32 IsScreenModeIdle(void);
extern void Panel_CaptureBrightness(void);
extern void SetPanelEnabled(int value);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 4: once the screen is idle, turns the panel back on and moves on to state 5. */
void StageStateWaitScreenIdle(void)
{
    if (IsScreenModeIdle()) {
        gFieldSessionWork->sceneFlags &= ~0x40000;
        Panel_CaptureBrightness();
        SetPanelEnabled(1);
        gMovieContextState->flags &= (u16)~0x20;
        SetStageState(5, FALSE);
    }
}
