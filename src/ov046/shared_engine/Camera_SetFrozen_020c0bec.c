#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x84];
    u32 flags;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_SetFrozen_020c0bec(BOOL frozen)
{
    if (frozen) {
        g_cameraManager_020c34e0->flags |= 1;
        return;
    }
    g_cameraManager_020c34e0->flags &= ~1;
}
