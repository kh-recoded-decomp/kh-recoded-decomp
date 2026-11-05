#include "src/overlays/ov027/CapturedTouch.h"

int UpdateCapturedTouchTask(void)
{
    CaptureLatestOnScreenTouch();
    return 0;
}
