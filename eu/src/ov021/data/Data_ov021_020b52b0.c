#include "nitro/types.h"

#pragma explicit_zero_data on

extern void BeginSubModeTask(void);
extern void ReleaseActiveSubModeOverlay(void);

void *gSubModeTaskDefinition[5] = {
    (void *)0x00070009,
    (void *)BeginSubModeTask,
    (void *)ReleaseActiveSubModeOverlay,
    (void *)0x00000010,
    NULL,
};

u32 gSubModeOverlayIds[4] = {
    0x0000002E, 0x0000002A, 0x0000002B, 0x0000002C,
};
