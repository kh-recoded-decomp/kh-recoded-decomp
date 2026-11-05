#include "src/overlays/ov042/Ov042CameraState.h"

fx32 GetCameraFrustumExtent(void)
{
    return gOv042CameraState->frustumBounds[2];
}
