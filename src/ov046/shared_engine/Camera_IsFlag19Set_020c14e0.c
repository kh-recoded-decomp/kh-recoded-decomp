#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 settingFlags;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

BOOL Camera_IsFlag19Set_020c14e0(void)
{
    if (g_cameraManager_020c34e0->settingFlags & 0x80000) {
        return TRUE;
    }
    return FALSE;
}
