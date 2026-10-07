#include "src/overlays/ov043/Ov043CameraState.h"

void Ov043Camera_SetFlags(u32 value)
{
    gOv043CameraState->flags = value;
}
