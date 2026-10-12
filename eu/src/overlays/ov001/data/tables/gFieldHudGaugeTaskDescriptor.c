#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void *CreateTimedSceneState(int parameters);
extern void DestroyFieldHudGaugeState(void);

StageManagerTaskDescriptor gFieldHudGaugeTaskDescriptor = {
    0x000e0015,
    (void *)CreateTimedSceneState,
    (void *)DestroyFieldHudGaugeState,
    0x158,
    NULL,
};
