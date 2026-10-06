#include "nitro/types.h"

extern void StepPanelFadeIn(void);
extern void SwitchPanelState(void);
extern void StepPanelFadeOut_020631d8(void);
extern void GetFadeProgressLevel(void);
extern void GetFadeOutLevel(void);

void (*gTitleScreenOptionHandlers[4])(void) = {
    StepPanelFadeIn,
    SwitchPanelState,
    StepPanelFadeOut_020631d8,
    NULL,
};

void (*gTitleScreenInputHandlers[2])(void) = {
    GetFadeProgressLevel,
    GetFadeOutLevel,
};
