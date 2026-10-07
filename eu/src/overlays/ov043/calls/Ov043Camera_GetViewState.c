#include "src/overlays/ov043/Ov043CameraState.h"

void *Ov043Camera_GetViewState(void)
{
    return &gOv043CameraState->viewState;
}
