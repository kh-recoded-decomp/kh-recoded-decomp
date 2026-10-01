#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraBaseParams {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    u8 pad_2C[0xc];
} CameraBaseParams;

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 unk_0C;
    u32 angle;
    u8 pad_14[0x10];
    VecFx32 lookAt;
    VecFx32 target;
    u8 pad_3C[0x5c];
    u32 targetAngle;
    u8 pad_9C[0x1c];
    u16 unk_B8;
    u16 unk_BA;
} CameraTracking;

typedef struct CameraManager {
    CameraBaseParams base;
    u8 pad_38[0xb8];
    u32 flags;
    u8 pad_F4[0x48];
    CameraTracking tracking;
} CameraManager;

typedef struct CameraViewState {
    CameraBaseParams base;
    u32 angle;
    fx32 unk_3C;
} CameraViewState;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_ApplyViewState_020c6ca4(CameraViewState *state)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = &camera->tracking;

    tracking->target = state->base.position;
    tracking->lookAt = state->base.lookAt;
    tracking->targetAngle = tracking->angle = (u16)state->angle;
    camera->flags &= 0xffbfd7ff;
    camera->flags |= 0x1000;
    tracking->unk_BA = 0x1555;
    tracking->unk_B8 = tracking->unk_BA;
}
