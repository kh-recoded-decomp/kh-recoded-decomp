#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x12c];
    fx32 followDistance;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_SetFollowDistance_020c0dc4(fx32 distance)
{
    g_cameraManager_020c34e0->followDistance = distance;
}
