#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void SubScene9_Create_02066c80();
extern void ClearSubScene9WorkOnDestroy();

StageManagerTaskDescriptor gSubScene9TaskDescriptor = {
    0x00020008,
    (void *)SubScene9_Create_02066c80,
    (void *)ClearSubScene9WorkOnDestroy,
    0x24,
    NULL
};
