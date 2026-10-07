#include "src/overlays/ov046/CameraManager.h"

u32 Camera_GetStateFlags(void)
{
    return data_ov046_020c3500->stateFlags;
}
