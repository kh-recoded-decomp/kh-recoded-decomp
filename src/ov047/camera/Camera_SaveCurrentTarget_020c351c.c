#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x20];
    VecFx32 target;
    u8 pad_2c[0x258 - 0x2c];
    VecFx32 savedTarget;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_SaveCurrentTarget_020c351c(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    camera->savedTarget = camera->target;
}
