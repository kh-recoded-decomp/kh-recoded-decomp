#include "nitro/types.h"

extern void EnterMenuIntroState(void);

void (*gMenuStateTable[1])(void) = {
    EnterMenuIntroState,
};
