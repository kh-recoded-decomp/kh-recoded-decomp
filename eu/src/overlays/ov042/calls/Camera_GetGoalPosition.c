#include "src/overlays/ov042/Ov042CameraState.h"

VecFx32 *Camera_GetGoalPosition(void)
{
    return &gOv042CameraState->goalPosition;
}
