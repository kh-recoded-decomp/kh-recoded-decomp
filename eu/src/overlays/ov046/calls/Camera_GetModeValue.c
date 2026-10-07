#include "src/overlays/ov046/CameraManager.h"

s32 Camera_GetModeValue(void)
{
    return data_ov046_020c3500->mode;
}
