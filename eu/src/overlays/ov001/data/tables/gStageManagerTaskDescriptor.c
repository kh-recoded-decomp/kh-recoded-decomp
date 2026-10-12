#include "src/overlays/ov001/StageActorTables.h"

extern void CreateStageManager();
extern void DestroyStageManager(void);

StageManagerTaskDescriptor gStageManagerTaskDescriptor = {
    0x000b000d,
    (void *)CreateStageManager,
    (void *)DestroyStageManager,
    0x18f60,
    NULL
};
