#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 lift;
    u8 pad_1c[0x24 - 0x1c];
    VecFx32 lookAt;
    VecFx32 target;
    u8 pad_3c[0x7c - 0x3c];
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedLift;
    u8 pad_a4[0x128 - 0xa4];
    int unk_128;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0xe4];
    s32 followPreset;
    u8 pad_e8[0xf0 - 0xe8];
    u32 stateFlags;
    u8 pad_f4[0x13c - 0xf4];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern fx32 Camera_ComputeFollowDistance_020c1a70(int preset);
extern fx32 func_ov046_020c1a48(int preset);
extern fx32 func_ov046_020c19f0(int preset);
extern BOOL Camera_UpdateTracking_020c631c(BOOL snap);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void Camera_RestoreSavedTracking_020c6d34(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = (CameraTracking *)camera->controllerData;
    VecFx32 *focus = Camera_GetFocusPosition_020c1780();

    tracking->savedDistance = Camera_ComputeFollowDistance_020c1a70(camera->followPreset);
    tracking->savedHeight = func_ov046_020c1a48(camera->followPreset);
    tracking->savedLift = func_ov046_020c19f0(camera->followPreset);
    tracking->lookAt = tracking->savedLookAt;
    tracking->distance = tracking->savedDistance;
    tracking->angle = tracking->savedAngle;
    tracking->height = tracking->savedHeight;
    tracking->lift = tracking->savedLift;
    SetVec(&tracking->target, focus->x, focus->y + tracking->lift, focus->z);
    tracking->savedTarget = tracking->target;
    camera->stateFlags &= ~0x4000000;
    tracking->unk_128 = -1;
    Camera_UpdateTracking_020c631c(TRUE);
}
