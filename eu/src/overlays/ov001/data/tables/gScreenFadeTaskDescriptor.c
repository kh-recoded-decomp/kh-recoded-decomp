#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void InitScreenFadeContext();
extern void func_ov001_0206a118();

StageManagerTaskDescriptor gScreenFadeTaskDescriptor = {
    0x0002001c,
    (void *)InitScreenFadeContext,
    (void *)func_ov001_0206a118,
    0x68,
    NULL
};
