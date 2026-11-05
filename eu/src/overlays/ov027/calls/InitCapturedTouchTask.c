#include "src/overlays/ov027/CapturedTouch.h"

/* Legacy name: returns the current task work, without allocating it. */
extern void *NNSi_FndGetCurrentRootHeap(void);

CapturedTouchStep InitCapturedTouchTask(void *userData)
{
    (void)userData; /* Obj_Construct supplies it; this initializer does not use it. */
    gCapturedTouchRecord = NNSi_FndGetCurrentRootHeap();
    return UpdateCapturedTouchTask;
}
