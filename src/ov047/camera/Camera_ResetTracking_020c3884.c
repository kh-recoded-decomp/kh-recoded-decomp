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
    u8 pad_E0[0xc];
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


typedef void (*CameraUpdateFn)(void);

extern const VecFx32 data_02053438;
extern fx32 func_ov046_020c1a70(int mode);
extern fx32 func_ov046_020c1a48(int mode);
extern fx32 func_ov046_020c19f0(int mode);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *v, VecFx32 *out);
extern void func_ov047_020c4768(void);

CameraUpdateFn Camera_ResetTracking_020c3884(CameraTracking *tracking, CameraManager *camera)
{
    VecFx32 normal;
    VecFx32 diff;
    VecFx32 offset;

    tracking->unk_B4 = 0;
    tracking->unk_BC = 0;
    tracking->unk_C0 = 0x4cd;
    tracking->unk_C4 = 0;
    tracking->unk_C8 = 0;
    tracking->unk_CC = 0;
    tracking->state = 0;
    tracking->active = FALSE;
    tracking->angle = 0;
    tracking->unk_110 = 0;
    tracking->unk_11A = 3;
    tracking->unk_104 = 0;
    tracking->unk_108 = 0;
    tracking->unk_10C = 0;
    tracking->savedAngle = 0;
    tracking->savedDistance = func_ov046_020c1a70(camera->mode);
    tracking->savedHeight = func_ov046_020c1a48(camera->mode);
    tracking->savedUnk18 = func_ov046_020c19f0(camera->mode);
    tracking->unk_A4 = data_02053438;
    tracking->unk_B0 = 0x7fffffff;
    tracking->unk_EC = 0;
    tracking->unk_F0 = 0;
    tracking->unk_F4 = 0;
    tracking->turnTimer = 0;
    tracking->unk_D8 = 0;
    tracking->unk_DC = 0;
    tracking->unk_D4 = 0x1f;
    tracking->unk_D0 = 0x1f;
    tracking->distance = func_ov046_020c1a70(camera->mode);
    tracking->height = func_ov046_020c1a48(camera->mode);
    tracking->unk_18 = func_ov046_020c19f0(camera->mode);
    tracking->prevHeight = tracking->height;
    tracking->unk_B8 = 0x1555;
    tracking->unk_BA = 0x1555;
    tracking->unk_128 = -1;
    tracking->trackFlags.unk_0 = 0;
    tracking->unk_130 = 0;
    camera->extraFlags.unk_0 = 0;
    camera->eye = camera->view.lookAt;
    tracking->savedLookAt = camera->eye;
    tracking->unk_6C = tracking->savedLookAt;
    camera->unk_44 = camera->view.position;
    tracking->savedTarget = camera->unk_44;
    camera->view.up.y = 0x1000;
    camera->view.up.x = 0;
    camera->view.up.z = 0;
    VEC_Subtract_01ff9e3c(&camera->unk_44, &camera->eye, &diff);
    offset = diff;
    func_01ff9f88(&offset, &normal);
    tracking->direction = normal;
    tracking->prevDirection = tracking->direction;
    camera->flags &= 0xfffbfff7;
    return func_ov047_020c4768;
}

