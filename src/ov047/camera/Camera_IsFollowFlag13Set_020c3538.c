#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 stateFlags;
    u8 pad_f4[0x13c - 0xf4];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

u32 Camera_IsFollowFlag13Set_020c3538(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    if (camera->controllerData != NULL) {
        return camera->stateFlags & 0x2000;
    }
    return 0;
}
