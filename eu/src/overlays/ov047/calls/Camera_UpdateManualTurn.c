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
    u8 pad_A4[0x20];
    fx32 unk_C4;
    u8 pad_C8[0x30];
    int turnTimer;
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

extern CameraManager *data_ov046_020c3500;

typedef struct SaveFlags {
    u32 unk_0 : 9;
    u32 swapTurn : 1;
} SaveFlags;

extern u16 data_020604fc;
extern u8 *data_0205fe0c;
extern u32 func_ov046_020c2ad8(CameraManager *camera);
extern fx32 Camera_ComputeFollowDistance(int mode);
extern fx32 func_ov046_020c1a68(int mode);
extern fx32 func_ov046_020c1a10(int mode);
extern fx32 Camera_GetSpeedScaledStep(void);

void Camera_UpdateManualTurn(void)
{
    CameraManager *camera = data_ov046_020c3500;
    CameraTracking *tracking = &camera->tracking;

    if (func_ov046_020c2ad8(camera) == 0 &&
        ((data_020604fc & 0x40) || (data_020604fc & 0x80) || (data_020604fc & 0x20) || (data_020604fc & 0x10))) {
        u32 left;
        int timer;
        u32 angle;

        tracking->savedHeight = func_ov046_020c1a68(camera->mode);
        tracking->savedUnk18 = func_ov046_020c1a10(camera->mode);
        tracking->savedDistance = Camera_ComputeFollowDistance(camera->mode);
        tracking->unk_C4 = Camera_GetSpeedScaledStep();
        if (camera->flags & 0x10000000) {
            return;
        }
        if (((SaveFlags *)(data_0205fe0c + 0x2878))->swapTurn == 1 && (data_020604fc & 0x200)) {
            return;
        }
        left = data_020604fc & 0x20;
        if (left == 0 && !(data_020604fc & 0x10)) {
            return;
        }
        timer = tracking->turnTimer + 0x89;
        if (timer < 0) {
            timer = 0;
        }
        tracking->turnTimer = timer;
        if (tracking->turnTimer > 0x333) {
            angle = tracking->angle;
            if (left) {
                tracking->savedAngle = (u16)(angle + 0x300);
            } else {
                tracking->savedAngle = (u16)(angle - 0x300);
            }
        }
    } else {
        tracking->turnTimer = 0;
    }
}
