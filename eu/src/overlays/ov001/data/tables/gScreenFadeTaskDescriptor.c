#include "src/overlays/ov001/SceneTaskTables.h"

/* Only callback addresses are stored; their signatures are task-specific. */
extern void InitScreenFadeContext();
extern void ReleaseFieldScreenTransitionWork();

StageManagerTaskDescriptor gScreenFadeTaskDescriptor = {
    0x0002001c,
    (void *)InitScreenFadeContext,
    (void *)ReleaseFieldScreenTransitionWork,
    0x68,
    NULL
};
