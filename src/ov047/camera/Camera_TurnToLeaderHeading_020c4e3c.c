#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    u8 pad_2C[0xc];
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
    u8 pad_A4[0x14];
    u16 unk_B8;
    u16 unk_BA;
    fx32 unk_BC;
    u8 pad_C0[0x4];
    fx32 unk_C4;
    u8 pad_C8[0x4];
    fx32 unk_CC;
    u8 pad_D0[0x28];
    int turnTimer;
    fx32 turnSpeed;
    u8 pad_100[0x2c];
    CameraTrackingFlags trackFlags;
} CameraTracking;

typedef struct CameraBox {
    VecFx32 max;
    VecFx32 min;
} CameraBox;

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
    u8 pad_110[0x2c];
    CameraTracking tracking;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;



typedef struct SaveFlags {
    u32 unk_0 : 9;
    u32 swapTurn : 1;
    u32 freeHeading : 1;
} SaveFlags;

typedef void (*CameraUpdateFn)(void);

extern u8 *data_0205fe0c;
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern BOOL Camera_IsFrozen_020c0c1c(void);
extern BOOL IsLeaderFlag3Active_0206e198(void);
extern fx32 func_ov046_020c1a48(int mode);
extern fx32 func_ov046_020c19f0(int mode);
extern BOOL func_ov047_020c3ad8(CameraTracking *tracking, CameraManager *camera, u32 flags);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern int FX_Div_01ff9c84(int numer, int denom);
extern u32 func_ov001_0206c2c8(void);
extern BOOL IsHeldEntryFlag2Active_0206e33c(void);
extern BOOL Camera_UpdateTracking_020c631c(void *context);
extern void func_ov047_020c4768(void);

CameraUpdateFn Camera_TurnToLeaderHeading_020c4e3c(CameraTracking *tracking, CameraManager *camera)
{
    CameraUpdateFn next = NULL;
    int step;
    int remaining;

    Camera_GetFocusPosition_020c1780();
    if (Camera_IsFrozen_020c0c1c()) {
        return next;
    }
    if (!IsLeaderFlag3Active_0206e198()) {
        return next;
    }
    if (tracking->trackFlags.turning) {
        tracking->active = FALSE;
    finish:
        next = func_ov047_020c4768;
        camera->flags &= ~8;
    } else {
        if (!(camera->flags & 0x4000)) {
            tracking->savedHeight = func_ov046_020c1a48(camera->mode);
        }
        tracking->savedUnk18 = func_ov046_020c19f0(camera->mode);
        if (func_ov047_020c3ad8(tracking, camera, camera->flags)) {
            s16 heading;
            fx32 speed;

            if (((SaveFlags *)(data_0205fe0c + 0x2878))->freeHeading == 0) {
                heading = ((s64)GetBiasAdjustedField_0206dc80(0) + 0x1000) / 0x2000 * 0x2000;
            } else {
                heading = GetBiasAdjustedField_0206dc80(0);
            }
            tracking->heading = heading;
            tracking->turnSpeed = speed = FX_Div_01ff9c84((s64)(s16)(heading - tracking->angle) * 0x6488 / 0x10000, 0x3000);
            if ((speed < 0 ? -speed : speed) < 2) {
                tracking->turnSpeed = (s16)(tracking->heading - tracking->angle) > 0 ? 2 : -2;
            }
            tracking->savedAngle = tracking->angle;
        }
        step = (s16)((((s64)tracking->turnSpeed << 16) / 0x6488) & 0xffff);
        if (step < 0) {
            step = -step;
        }
        remaining = (s16)(tracking->heading - tracking->savedAngle);
        if (remaining < 0) {
            remaining = -remaining;
        }
        if (remaining <= step || func_ov001_0206c2c8() || IsHeldEntryFlag2Active_0206e33c()) {
            tracking->savedAngle = tracking->heading;
            tracking->savedAngle = (u16)tracking->savedAngle;
            tracking->active = FALSE;
            goto finish;
        }
        tracking->savedAngle += (s16)((((s64)tracking->turnSpeed << 16) / 0x6488) & 0xffff);
        tracking->savedAngle = (u16)tracking->savedAngle;
    }
    Camera_UpdateTracking_020c631c(NULL);
    return next;
}




