#include "src/overlays/ov046/CameraManager.h"

void *Camera_GetEventWork(void)
{
    return gCameraManager->controllerData;
}
