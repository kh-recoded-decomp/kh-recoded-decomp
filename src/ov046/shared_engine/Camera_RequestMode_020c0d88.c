#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
    u8 pad_84[0x60];
    int mode;
    int previousMode;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void Camera_SetMode_020c36c8(int mode, int arg);

void Camera_RequestMode_020c0d88(int mode, int arg)
{
    if (g_cameraManager_020c34e0->type != 0) {
        g_cameraManager_020c34e0->previousMode = g_cameraManager_020c34e0->mode;
        g_cameraManager_020c34e0->mode = mode;
    } else {
        Camera_SetMode_020c36c8(mode, arg);
    }
}
