#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitModeHandlerContext(void);
extern void ReleaseMessageWindowWork(void);

StageManagerTaskDescriptor gFieldHudTimerTaskDescriptor = {
    0x000e0014,
    (void *)InitModeHandlerContext,
    (void *)ReleaseMessageWindowWork,
    0xfc,
    NULL,
};
