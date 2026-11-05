#include "src/overlays/ov042/Ov042CameraState.h"

extern fx32 VEC_Mag(const VecFx32 *vector);

fx32 GetCameraColliderOffsetMagnitude(void)
{
    return VEC_Mag(&gOv042CameraState->colliderOffset);
}
