#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void InitEventTriggerScene();
extern void func_ov001_02068ff4();

StageManagerTaskDescriptor gEventTriggerTaskDescriptor = {
    0x00020008,
    (void *)InitEventTriggerScene,
    (void *)func_ov001_02068ff4,
    0x38,
    NULL
};
