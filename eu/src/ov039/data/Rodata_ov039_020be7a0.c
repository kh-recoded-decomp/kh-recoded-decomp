#include "nitro/types.h"

extern void CleanupHandlersAndSetPhase5(void);
extern void InitThenDispatchTwoHandlers(void);
extern void LoadSelectedHandlerAndStart(void);
extern void UpdateExitSequence(void);
extern void UpdateSubOverlayHandlers(void);
extern void WaitMenuFadeInThenEnableInput(void);
extern void WaitSubMenuFadeInThenEnableButtons(void);
extern void WaitMenuFadeOutThenEnterShutdown(void);
extern void ShutdownHandlersAndExit(void);

void *const gMenuRuntimeStateHandlers[10] = {
    NULL,
    (void *)UpdateSubOverlayHandlers,
    (void *)WaitMenuFadeInThenEnableInput,
    (void *)InitThenDispatchTwoHandlers,
    (void *)UpdateExitSequence,
    (void *)LoadSelectedHandlerAndStart,
    (void *)WaitSubMenuFadeInThenEnableButtons,
    (void *)WaitMenuFadeOutThenEnterShutdown,
    (void *)CleanupHandlersAndSetPhase5,
    (void *)ShutdownHandlersAndExit,
};

const u32 gMenuTileTableLayerIds[7] = {
    0x00000009, 0x0000000A, 0x0000000B, 0x00000018,
    0x00000019, 0x0000001A, 0x0000001B,
};
