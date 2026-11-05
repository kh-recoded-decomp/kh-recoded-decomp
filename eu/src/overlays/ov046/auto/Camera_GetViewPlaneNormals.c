#include "nitro/types.h"

extern u8 *gCameraManager;

void *Camera_GetViewPlaneNormals(void)
{
    return gCameraManager + 0x50;
}
