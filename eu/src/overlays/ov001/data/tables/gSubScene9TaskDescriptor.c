#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void SubScene9_Create_02066c80();
extern void func_ov001_02066ca0();

StageManagerTaskDescriptor gSubScene9TaskDescriptor = {
    0x00020008,
    (void *)SubScene9_Create_02066c80,
    (void *)func_ov001_02066ca0,
    0x24,
    NULL
};
