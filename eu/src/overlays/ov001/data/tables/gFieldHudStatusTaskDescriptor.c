#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void func_ov001_0207b818(void);
extern void func_ov001_0207b868(void);

StageManagerTaskDescriptor gFieldHudStatusTaskDescriptor = {
    0x000e0016,
    (void *)func_ov001_0207b818,
    (void *)func_ov001_0207b868,
    0x910,
    NULL,
};
