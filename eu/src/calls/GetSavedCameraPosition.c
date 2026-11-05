#include "src/graphics/CameraState.h"

const VecFx32 * GetSavedCameraPosition(void)
{
    return &gSavedCameraState.position;
}
