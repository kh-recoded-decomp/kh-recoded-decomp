#include "nitro/types.h"

extern void UpdateScrollTextScreensWrapper(void); /* PXI_Init */
extern void UpdateScrollTextFrame_020622f0(void);
extern void UpdateScrollTextFadeOut(void); /* UpdateScrollTextFadeOut */
extern void ScrollText_Mode3FrameNoop(void);

void (*gScrollTextHandlers[4])(void) = {
    UpdateScrollTextScreensWrapper, /* PXI_Init */
    UpdateScrollTextFrame_020622f0,
    UpdateScrollTextFadeOut, /* UpdateScrollTextFadeOut */
    ScrollText_Mode3FrameNoop,
};
