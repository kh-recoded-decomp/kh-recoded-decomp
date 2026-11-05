#include "src/overlays/ov042/Ov042CameraState.h"

/* Borrowed native state view; no allocation or ownership transfer. */
Ov042CameraState *Ov042Camera_GetState(void)
{
    return gOv042CameraState;
}
