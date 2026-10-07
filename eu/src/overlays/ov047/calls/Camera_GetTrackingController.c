#include "src/overlays/ov047/Ov047CameraState.h"

void *Camera_GetTrackingController(void)
{
    return gOv047CameraState->trackingController;
}
