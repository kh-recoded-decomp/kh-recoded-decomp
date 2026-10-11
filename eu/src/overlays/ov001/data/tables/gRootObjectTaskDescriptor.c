#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void SubScene9_Create_02068c0c();
extern void func_ov001_02068c3c();

StageManagerTaskDescriptor gRootObjectTaskDescriptor = {
    0x00020008,
    (void *)SubScene9_Create_02068c0c,
    (void *)func_ov001_02068c3c,
    0x2c,
    NULL
};
