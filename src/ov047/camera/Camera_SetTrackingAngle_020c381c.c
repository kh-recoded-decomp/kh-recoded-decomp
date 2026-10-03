#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 distance;
    u32 angle;
    fx32 height;
    u8 pad_18[0x30 - 0x18];
    VecFx32 target;
    u8 pad_3c[0x7c - 0x3c];
    VecFx32 savedLookAt;
    u8 pad_88[0x98 - 0x88];
    int savedAngle;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0x13c];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern const s16 data_0205356c[];
extern int FixedPointMultiply12(int left, int right);
extern void func_ov047_020c6d34(void);
extern void Camera_Update_020c0b6c(BOOL force);

void Camera_SetTrackingAngle_020c381c(int angle)
{
    CameraTracking *tracking = (CameraTracking *)g_cameraManager_020c34e0->controllerData;
    fx32 y;
    fx32 z;
    int index;

    tracking->savedAngle = angle;
    index = tracking->savedAngle >> 4;
    z = tracking->target.z + FixedPointMultiply12(data_0205356c[(0x400 - index) & 0xfff], tracking->distance);
    y = tracking->target.y + tracking->height;
    tracking->savedLookAt.x = tracking->target.x + FixedPointMultiply12(data_0205356c[index], tracking->distance);
    tracking->savedLookAt.y = y;
    tracking->savedLookAt.z = z;
    func_ov047_020c6d34();
    Camera_Update_020c0b6c(TRUE);
}




