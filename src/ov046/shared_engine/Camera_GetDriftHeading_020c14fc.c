#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x2c];
    VecFx32 defaultDirection;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void GetParticleDriftDirection_020af9a4(CameraManager *camera, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);

u16 Camera_GetDriftHeading_020c14fc(void)
{
    VecFx32 direction;
    fx32 height;

    GetParticleDriftDirection_020af9a4(g_cameraManager_020c34e0, &direction);
    height = direction.y;
    if (height < 0) {
        height = -height;
    }
    if (height < g_cameraManager_020c34e0->defaultDirection.y) {
        return FixedPointAtan2_020062bc(-direction.x, -direction.z);
    }
    return FixedPointAtan2_020062bc(-g_cameraManager_020c34e0->defaultDirection.x, -g_cameraManager_020c34e0->defaultDirection.z);
}
