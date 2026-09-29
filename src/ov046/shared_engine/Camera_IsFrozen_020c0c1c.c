#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x84];
    u32 flags;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

BOOL Camera_IsFrozen_020c0c1c(void)
{
    return (g_cameraManager_020c34e0->flags & 1) != 0;
}
