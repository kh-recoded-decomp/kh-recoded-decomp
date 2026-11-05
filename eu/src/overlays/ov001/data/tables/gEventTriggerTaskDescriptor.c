#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void InitEventTriggerScene();
extern void ReleaseFieldTaskManagerWork();

StageManagerTaskDescriptor gEventTriggerTaskDescriptor = {
    0x00020008,
    (void *)InitEventTriggerScene,
    (void *)ReleaseFieldTaskManagerWork,
    0x38,
    NULL
};
