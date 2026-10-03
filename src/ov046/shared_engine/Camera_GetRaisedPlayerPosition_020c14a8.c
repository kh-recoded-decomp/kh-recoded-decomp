#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x130];
    fx32 heightOffset;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);

void Camera_GetRaisedPlayerPosition_020c14a8(VecFx32 *out)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    VecFx32 *position = func_ov001_0206dc4c(0);
    VecFx32 result;

    result.x = position->x;
    result.y = position->y + camera->heightOffset;
    result.z = position->z;
    *out = result;
}
