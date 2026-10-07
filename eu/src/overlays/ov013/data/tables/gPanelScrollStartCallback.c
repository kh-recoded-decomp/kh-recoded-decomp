#include "nitro/types.h"

extern void SetPanelScrollUpDirection(void);

void (*gPanelScrollStartCallback[1])(void) = {
    SetPanelScrollUpDirection,
};
