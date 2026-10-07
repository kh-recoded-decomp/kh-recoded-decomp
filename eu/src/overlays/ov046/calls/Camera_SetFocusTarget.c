#include "src/overlays/ov046/CameraManager.h"

void Camera_SetFocusTarget(void *target)
{
    data_ov046_020c3500->focusTarget = target;
}
