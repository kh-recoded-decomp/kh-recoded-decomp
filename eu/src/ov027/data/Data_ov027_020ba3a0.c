#include "src/overlays/ov027/CapturedTouch.h"

#pragma explicit_zero_data on

extern void func_ov027_020ba060(void);
extern void ClearOverlayLoadQueues(void);

void *data_ov027_020ba3b4[11] = {
    (void *)0x000E0012,
    (void *)func_ov027_020ba060,
    (void *)ClearOverlayLoadQueues,
    (void *)0x00000018,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

CapturedTouchTaskDescriptor gCapturedTouchTaskDescriptor = {
    0x0011, 0x000e,
    InitCapturedTouchTask,
    ShutdownCapturedTouchTask,
    sizeof(CapturedTouchRecord),
    NULL,
};
