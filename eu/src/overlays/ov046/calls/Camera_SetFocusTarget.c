#include "src/overlays/ov046/CameraManager.h"

void Camera_SetFocusTarget(void *target)
{
    gCameraManager->focusTarget = target;
}
