#include "src/overlays/ov043/Ov043CameraState.h"

void *Ov043Camera_GetActiveController(void)
{
    return &gOv043CameraState->activeController;
}
