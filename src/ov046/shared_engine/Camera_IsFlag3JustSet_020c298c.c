#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xec];
    u32 previousSettingFlags;
    u32 settingFlags;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

BOOL Camera_IsFlag3JustSet_020c298c(void)
{
    if ((g_cameraManager_020c34e0->settingFlags & 8) != 0 &&
        (g_cameraManager_020c34e0->previousSettingFlags & 8) == 0) {
        return TRUE;
    }
    return FALSE;
}
