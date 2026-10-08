#include "nitro/types.h"

extern void CleanupHandlersAndSetPhase5(void);
extern void InitThenDispatchTwoHandlers(void);
extern void LoadSelectedHandlerAndStart(void);
extern void UpdateExitSequence(void);
extern void UpdateSubOverlayHandlers(void);
extern void func_ov039_020bb2d0(void);
extern void func_ov039_020bb4c8(void);
extern void func_ov039_020bb518(void);
extern void ShutdownHandlersAndExit(void);

void *const data_ov039_020be7bc[10] = {
    NULL,
    (void *)UpdateSubOverlayHandlers,
    (void *)func_ov039_020bb2d0,
    (void *)InitThenDispatchTwoHandlers,
    (void *)UpdateExitSequence,
    (void *)LoadSelectedHandlerAndStart,
    (void *)func_ov039_020bb4c8,
    (void *)func_ov039_020bb518,
    (void *)CleanupHandlersAndSetPhase5,
    (void *)ShutdownHandlersAndExit,
};

const u32 data_ov039_020be7a0[7] = {
    0x00000009, 0x0000000A, 0x0000000B, 0x00000018,
    0x00000019, 0x0000001A, 0x0000001B,
};
