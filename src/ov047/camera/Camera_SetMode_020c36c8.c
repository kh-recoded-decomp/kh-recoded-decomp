#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    u8 pad_2C[0xc];
} CameraView;

typedef struct CameraTracking {
    u8 pad_00[0xc];
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    u8 pad_48[0xc];
    VecFx32 unk_54;
    VecFx32 unk_60;
    VecFx32 unk_6C;
    u32 unk_78;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
} CameraTracking;

typedef struct CameraManager {
    CameraView view;
    VecFx32 eye;
    u8 pad_44[0xa0];
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    u8 pad_F4[0x48];
    CameraTracking tracking;
} CameraManager;

typedef struct CameraViewState {
    CameraView view;
    u32 angle;
    fx32 distance;
    fx32 unk_40;
    fx32 unk_44;
} CameraViewState;

extern CameraManager *g_cameraManager_020c34e0;

extern fx32 func_ov046_020c1a70(int mode);
extern fx32 func_ov046_020c1a48(int mode);
extern fx32 func_ov046_020c19f0(int mode);
extern BOOL Camera_UpdateTracking_020c631c(void *context);

void Camera_SetMode_020c36c8(int mode)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = &camera->tracking;

    camera->prevMode = camera->mode;
    camera->mode = mode;
    tracking->distance = func_ov046_020c1a70(camera->mode);
    tracking->height = func_ov046_020c1a48(camera->mode);
    tracking->unk_18 = func_ov046_020c19f0(camera->mode);
    tracking->savedDistance = func_ov046_020c1a70(camera->mode);
    tracking->savedHeight = func_ov046_020c1a48(camera->mode);
    tracking->savedUnk18 = func_ov046_020c19f0(camera->mode);
    if (mode == 0x13 || mode == 0x15) {
        tracking->angle = 0;
        tracking->savedAngle = 0;
        camera->flags &= 0xfff7ffff;
        tracking->savedDistance = func_ov046_020c1a70(camera->mode);
        tracking->savedHeight = func_ov046_020c1a48(camera->mode);
    }
    Camera_UpdateTracking_020c631c(NULL);
    tracking->lookAt = tracking->savedLookAt;
    tracking->target = tracking->savedTarget;
}
