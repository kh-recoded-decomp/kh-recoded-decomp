#include "src/graphics/CameraState.h"

const VecFx32 * GetSavedCameraTarget(void)
{
    return &gSavedCameraState.target;
}
