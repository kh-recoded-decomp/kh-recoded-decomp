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

extern CameraManager *data_ov046_020c3500;
extern BOOL Camera_IsFrozen(void);
extern void Camera_SetFrozen(BOOL frozen);
extern fx32 Camera_ComputeFollowDistance(int preset);
extern fx32 func_ov046_020c1a68(int preset);
extern u16 GetBiasAdjustedField(int index);
extern void Camera_SetTrackingAngle(int angle);

void Camera_ResetTrackingToLeader(void)
{
    CameraManager *camera = data_ov046_020c3500;
    CameraTracking *tracking = (CameraTracking *)camera->controllerData;
    BOOL wasFrozen = Camera_IsFrozen();

    camera->stateFlags &= ~0x80000;
    tracking->savedDistance = Camera_ComputeFollowDistance(camera->followPreset);
    tracking->savedHeight = func_ov046_020c1a68(camera->followPreset);
    Camera_SetFrozen(FALSE);
    Camera_SetTrackingAngle(GetBiasAdjustedField(0));
    Camera_SetFrozen(wasFrozen);
}
