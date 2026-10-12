#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void func_ov001_0207dc68(void);
extern void func_ov001_0207dcbc(void);

StageManagerTaskDescriptor gFieldHudExtraTaskDescriptor = {
    0x000e0013,
    (void *)func_ov001_0207dc68,
    (void *)func_ov001_0207dcbc,
    0x4c,
    NULL,
};
