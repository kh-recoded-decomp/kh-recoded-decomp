#include "src/overlays/ov042/Ov042CameraState.h"

VecFx32 *Camera_GetColliderOffset(void)
{
    return &gOv042CameraState->colliderOffset;
}
