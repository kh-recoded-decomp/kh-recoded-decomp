#include "src/overlays/ov027/CapturedTouch.h"
#include "src/overlays/ov027/FileLoadQueue.h"

#pragma explicit_zero_data on

extern void ClearOverlayLoadQueues(void);

void *gFileLoadQueueTaskDescriptor[11] = {
    (void *)0x000E0012,
    (void *)InitFileLoadQueueTask,
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
