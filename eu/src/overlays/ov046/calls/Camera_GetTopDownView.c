#include "src/overlays/ov046/CameraManager.h"

void *Camera_GetTopDownView(void)
{
    return data_ov046_020c3500->embeddedView;
}
