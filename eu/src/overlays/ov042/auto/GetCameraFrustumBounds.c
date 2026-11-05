#include "src/overlays/ov042/Ov042CameraState.h"

/* Borrowed four-word bounds view; valid only while the camera state lives. */
fx32 *GetCameraFrustumBounds(void)
{
    return gOv042CameraState->frustumBounds;
}
