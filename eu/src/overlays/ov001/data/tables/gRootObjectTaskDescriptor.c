#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void SubScene9_Create_02068c0c();
extern void ClearSessionTimerStatePointer();

StageManagerTaskDescriptor gRootObjectTaskDescriptor = {
    0x00020008,
    (void *)SubScene9_Create_02068c0c,
    (void *)ClearSessionTimerStatePointer,
    0x2c,
    NULL
};
