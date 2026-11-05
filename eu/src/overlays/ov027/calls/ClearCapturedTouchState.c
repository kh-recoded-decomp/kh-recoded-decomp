#include "src/overlays/ov027/CapturedTouch.h"

void ClearCapturedTouchState(void)
{
    gCapturedTouchRecord->touch = 0;
}
