#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    VecFx32 up;
} CameraView;

typedef struct CameraTrackingFlags {
    int unk_0 : 1;
    int turning : 1;
} CameraTrackingFlags;

typedef struct CameraTracking {
    BOOL active;
    int state;
    int heading;
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    VecFx32 prevTarget;
    VecFx32 direction;
    VecFx32 prevDirection;
    VecFx32 unk_6C;
    fx32 prevHeight;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
    VecFx32 unk_A4;
    int unk_B0;
    int unk_B4;
    u16 unk_B8;
    u16 unk_BA;
    fx32 unk_BC;
    fx32 unk_C0;
    fx32 unk_C4;
    fx32 unk_C8;
    fx32 unk_CC;
    int unk_D0;
    int unk_D4;
    int unk_D8;
    int unk_DC;
    int unk_E0;
    int unk_E4;
    int unk_E8;
    int unk_EC;
    int unk_F0;
    int unk_F4;
    int turnTimer;
    fx32 turnSpeed;
    u8 pad_100[0x4];
    int unk_104;
    int unk_108;
    int unk_10C;
    int unk_110;
    u8 pad_114[0x6];
    u16 unk_11A;
    u8 pad_11C[0xc];
    int unk_128;
    CameraTrackingFlags trackFlags;
    int unk_130;
} CameraTracking;

typedef struct CameraBox {
    VecFx32 max;
    VecFx32 min;
} CameraBox;

typedef struct CameraManagerFlags {
    u32 unk_0 : 1;
} CameraManagerFlags;

typedef struct CameraManager {
    CameraView view;
    VecFx32 eye;
    VecFx32 unk_44;
    u8 pad_50[0x94];
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    u8 pad_F4[0x4];
    CameraBox bounds;
    u8 pad_110[0x18];
    CameraManagerFlags extraFlags;
    u8 pad_12C[0x10];
    CameraTracking tracking;
} CameraManager;

typedef struct CameraPreset {
    int value;
    int unk_04;
    int unk_08;
} CameraPreset;

extern CameraManager *data_ov046_020c3500;
extern CameraPreset data_ov047_020c72a8[];
extern fx32 func_ov046_020c1a10(int mode);

void Camera_SetTrackingMode(int trackingMode, void *arg)
{
    CameraManager *camera = data_ov046_020c3500;
    CameraTracking *tracking = &camera->tracking;

    if (trackingMode != 3 && trackingMode != 4 && trackingMode != 9 && tracking->active == trackingMode) {
        return;
    }
    switch (trackingMode) {
    case 0:
    case 8:
        if (tracking->active == 1) {
            camera->flags &= ~0x800;
            camera->flags |= 0x1000;
        } else if (tracking->active == 3) {
            tracking->unk_DC = 0;
            tracking->unk_D8 = 0;
        }
        tracking->unk_18 = func_ov046_020c1a10(camera->mode);
        camera->flags &= 0x57ffbeff;
        break;
    case 6:
        camera->flags |= 0x8000;
        break;
    case 10:
        camera->flags |= 0x20000000;
        break;
    case 1:
        camera->flags &= ~0x1000;
        camera->flags |= 0x800;
        break;
    case 2:
        tracking->unk_18 = func_ov046_020c1a10(camera->mode) - 0x1a00;
        break;
    case 3:
        tracking->unk_E8 = (int)arg;
        tracking->unk_DC = 0;
        tracking->unk_E0 = 0;
        tracking->unk_D8 = data_ov047_020c72a8[tracking->unk_E8].value;
        tracking->unk_E4 = data_ov047_020c72a8[tracking->unk_E8].value;
        break;
    case 9:
        camera->flags |= 0x8000000;
    case 4:
        if (arg == NULL) {
            return;
        }
        tracking->unk_A4 = *(VecFx32 *)arg;
        break;
    case 5:
        tracking->active = 0;
        camera->flags |= 0x4000;
        break;
    }
    tracking->active = trackingMode;
}
