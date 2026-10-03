#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0xe0];
    u32 inputFlags;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern fx32 FixedPointMultiply12(fx32 left, fx32 right);

fx32 Camera_GetSpeedScaledStep_020c19b4(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    fx32 scale = 0x1000;

    if (camera->inputFlags & 2) {
        scale = 0xa66;
    }
    if (camera->inputFlags & 4) {
        scale = 0x1f33;
    }
    return FixedPointMultiply12(0x4cd, scale);
}
