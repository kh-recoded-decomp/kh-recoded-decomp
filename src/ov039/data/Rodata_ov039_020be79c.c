#include "nitro/types.h"

extern void CleanupHandlersAndSetPhase5_020bb680(void);
extern void InitThenDispatchTwoHandlers_020bb308(void);
extern void LoadSelectedHandlerAndStart_020bb40c(void);
extern void ShutdownHandlersAndExit_020bb540(void);
extern void UpdateExitSequence_020bb33c(void);
extern void UpdateSubOverlayHandlers_020bb148(void);
extern void func_ov039_020bb2b0(void);
extern void func_ov039_020bb4a8(void);
extern void func_ov039_020bb4f8(void);

void (*const data_ov039_020be79c[10])(void) = {
    NULL,
    UpdateSubOverlayHandlers_020bb148,
    func_ov039_020bb2b0,
    InitThenDispatchTwoHandlers_020bb308,
    UpdateExitSequence_020bb33c,
    LoadSelectedHandlerAndStart_020bb40c,
    func_ov039_020bb4a8,
    func_ov039_020bb4f8,
    CleanupHandlersAndSetPhase5_020bb680,
    ShutdownHandlersAndExit_020bb540,
};
