#include "nitro/types.h"

extern void GetFadeInRemainingLevel(void);
extern void FadeOutBrightness(void);

void (*gTitleScreenTransitionHandlers[2])(void) = {
    GetFadeInRemainingLevel,
    FadeOutBrightness,
};
