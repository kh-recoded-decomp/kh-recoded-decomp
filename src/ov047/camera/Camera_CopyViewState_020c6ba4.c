#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraBaseParams {
    u8 pad_00[0x14];
    VecFx32 position;
    u8 pad_20[0x18];
} CameraBaseParams;

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 unk_0C;
    u32 angle;
    u8 pad_14[0x1c];
    VecFx32 target;
} CameraTracking;

typedef struct CameraManager {
    CameraBaseParams base;
    u8 pad_38[0x104];
    CameraTracking tracking;
} CameraManager;

typedef struct CameraViewState {
    CameraBaseParams base;
    u32 angle;
    fx32 unk_3C;
} CameraViewState;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_CopyViewState_020c6ba4(CameraViewState *state)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = &camera->tracking;

    state->base = camera->base;
    state->base.position = tracking->target;
    state->angle = tracking->angle;
    state->unk_3C = tracking->unk_0C;
}
