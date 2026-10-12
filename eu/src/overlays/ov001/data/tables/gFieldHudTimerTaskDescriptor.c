#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitModeHandlerContext(void);
extern void func_ov001_0207a4a0(void);

StageManagerTaskDescriptor gFieldHudTimerTaskDescriptor = {
    0x000e0014,
    (void *)InitModeHandlerContext,
    (void *)func_ov001_0207a4a0,
    0xfc,
    NULL,
};
