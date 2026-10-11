#include "src/overlays/ov001/StageActorTables.h"

extern void CreateStageManager();
extern void func_ov001_02099904();

StageManagerTaskDescriptor gStageManagerTaskDescriptor = {
    0x000b000d,
    (void *)CreateStageManager,
    (void *)func_ov001_02099904,
    0x18f60,
    NULL
};
