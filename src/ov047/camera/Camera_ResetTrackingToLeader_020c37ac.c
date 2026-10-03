#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 pad_00[0x94];
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
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
extern BOOL Camera_IsFrozen_020c0c1c(void);
extern void Camera_SetFrozen_020c0bec(BOOL frozen);
extern fx32 Camera_ComputeFollowDistance_020c1a70(int preset);
extern fx32 func_ov046_020c1a48(int preset);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void Camera_SetTrackingAngle_020c381c(int angle);

void Camera_ResetTrackingToLeader_020c37ac(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = (CameraTracking *)camera->controllerData;
    BOOL wasFrozen = Camera_IsFrozen_020c0c1c();

    camera->stateFlags &= ~0x80000;
    tracking->savedDistance = Camera_ComputeFollowDistance_020c1a70(camera->followPreset);
    tracking->savedHeight = func_ov046_020c1a48(camera->followPreset);
    Camera_SetFrozen_020c0bec(FALSE);
    Camera_SetTrackingAngle_020c381c(GetBiasAdjustedField_0206dc80(0));
    Camera_SetFrozen_020c0bec(wasFrozen);
}
