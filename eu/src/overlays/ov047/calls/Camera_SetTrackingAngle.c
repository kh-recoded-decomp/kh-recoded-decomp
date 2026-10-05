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

extern CameraManager *data_ov046_020c3500;
extern const s16 data_02053580[];
extern int FX_Mul(int left, int right);
extern void Camera_RestoreSavedTracking(void);
extern void Camera_Update(BOOL force);

void Camera_SetTrackingAngle(int angle)
{
    CameraTracking *tracking = (CameraTracking *)data_ov046_020c3500->controllerData;
    fx32 y;
    fx32 z;
    int index;

    tracking->savedAngle = angle;
    index = tracking->savedAngle >> 4;
    z = tracking->target.z + FX_Mul(data_02053580[(0x400 - index) & 0xfff], tracking->distance);
    y = tracking->target.y + tracking->height;
    tracking->savedLookAt.x = tracking->target.x + FX_Mul(data_02053580[index], tracking->distance);
    tracking->savedLookAt.y = y;
    tracking->savedLookAt.z = z;
    Camera_RestoreSavedTracking();
    Camera_Update(TRUE);
}
