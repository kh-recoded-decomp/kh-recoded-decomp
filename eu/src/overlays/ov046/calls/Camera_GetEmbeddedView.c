#include "src/overlays/ov046/CameraManager.h"

void *Camera_GetEmbeddedView(void)
{
    return gCameraManager->controllerData;
}
