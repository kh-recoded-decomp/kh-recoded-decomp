#include "src/overlays/ov046/CameraManager.h"

void *Camera_GetTopDownView(void)
{
    return gCameraManager->controllerData;
}
