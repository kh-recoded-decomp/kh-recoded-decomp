#include "nitro/types.h"

extern void UpdateHudSlideTween(void); /* UpdateHudSlideTween */
extern void AdvanceFieldMessageAndCloseWhenDone(void);
extern void CheckSceneTimeout(void); /* CheckSceneTimeout */
extern u16 gEmptyModeCaption[2];

void (*gHudSlideStateHandlers[5])(void) = {
    NULL,
    UpdateHudSlideTween, /* UpdateHudSlideTween */
    AdvanceFieldMessageAndCloseWhenDone,
    CheckSceneTimeout, /* CheckSceneTimeout */
    UpdateHudSlideTween, /* UpdateHudSlideTween */
};

void *gHudSlideData[2] = {
    gEmptyModeCaption,
    gEmptyModeCaption,
};
