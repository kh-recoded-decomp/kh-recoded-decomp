#include "src/graphics/CameraState.h"

int ProjectWorldPositionWithSavedCameraWrapper(const VecFx32 *worldPosition,
                                               int *screenX, int *screenY)
{
    return ProjectWorldPositionWithSavedCamera(worldPosition, screenX, screenY);
}
