#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 stateFlags;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_SetStateFlag18_020c2a84(BOOL enable)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    if (enable) {
        camera->stateFlags |= 0x40000;
        return;
    }
    camera->stateFlags &= ~0x40000;
}
