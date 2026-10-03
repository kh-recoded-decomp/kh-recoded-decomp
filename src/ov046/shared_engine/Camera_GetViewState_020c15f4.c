#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraBaseParams {
    u8 pad_00[0x14];
    VecFx32 position;
    u8 pad_20[0x18];
} CameraBaseParams;

typedef struct CameraManager {
    CameraBaseParams base;
    VecFx32 eye;
    VecFx32 target;
    u8 pad_50[0x30];
    int type;
} CameraManager;

typedef struct CameraViewState {
    CameraBaseParams base;
    u32 angle;
    fx32 distance;
} CameraViewState;

extern CameraManager *g_cameraManager_020c34e0;
extern void Camera_CopyViewState_020c6ba4(CameraViewState *state);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

void Camera_GetViewState_020c15f4(CameraViewState *state)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    switch (camera->type) {
    case 0:
        Camera_CopyViewState_020c6ba4(state);
        break;
    case 1:
    case 2:
    case 3:
        state->base = camera->base;
        state->base.position = camera->target;
        state->angle = FixedPointAtan2_020062bc(camera->eye.x - camera->target.x, camera->eye.z - camera->target.z);
        state->distance = func_01ffa0f4(&g_cameraManager_020c34e0->eye, &g_cameraManager_020c34e0->target);
        break;
    }
}
