#include "nitro/types.h"

extern void Ov101List_HandleState0Noop(void);
extern void RunListScreenStep(void);

void (*const gOv101Callbacks[2])(void) = {
    Ov101List_HandleState0Noop,
    RunListScreenStep,
};
