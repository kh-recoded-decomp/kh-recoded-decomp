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

extern int FixedPointMultiply12(int left, int right);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void Camera_StepFollowTarget_020c53b4(CameraTracking *tracking, CameraManager *camera, BOOL snap)
{
    fx32 move;
    volatile fx32 rate;
    VecFx32 delta;
    fx32 speed;
    fx32 dy;
    fx32 length;
    fx32 step;
    fx32 diff;
    fx32 riseRate;

    speed = FixedPointMultiply12(0x800, 0x10000);
    if (tracking->unk_18 != tracking->savedUnk18) {
        if (snap) {
            tracking->unk_18 = tracking->savedUnk18;
        } else {
            diff = tracking->savedUnk18 - tracking->unk_18;
            if ((diff < 0 ? -diff : diff) <= 0x100) {
                tracking->unk_18 = tracking->savedUnk18;
            } else {
                tracking->unk_18 += FixedPointMultiply12(diff, 0x600);
            }
        }
    }
    if (camera->flags & 0x20) {
        speed = FixedPointMultiply12(speed, 0x4000);
    }
    if (tracking->unk_BC > speed) {
        speed = 0x800;
    }
    tracking->prevTarget = tracking->target;
    if (snap || (camera->flags & 0x10000) || tracking->state == 4) {
        tracking->target = tracking->savedTarget;
        return;
    }
    if (camera->flags & 0x2000000) {
        rate = tracking->unk_CC;
    } else {
        rate = 0x4cd;
    }
    if (speed - 0x200 < tracking->unk_BC) {
        rate = speed - 0x200;
    }
    VEC_Subtract_01ff9e3c(&tracking->savedTarget, &tracking->target, &delta);
    dy = delta.y;
    delta.y = move = 0;
    length = VEC_Mag_01ff9f28(&delta);
    if (length > 0x10) {
        step = FixedPointMultiply12(length, rate);
        if (step <= length) {
            if (step >= 0) {
                move = step;
            }
            length = move;
        }
        VEC_NormalizeUnchecked_01ff9f88(&delta, &delta);
        VEC_MultAdd_01ffa09c(length, &delta, &tracking->target, &tracking->target);
    } else {
        tracking->target.x = tracking->savedTarget.x;
        tracking->target.z = tracking->savedTarget.z;
    }
    if ((dy < 0 ? -dy : dy) > 0x10) {
        if (camera->flags & 0x2000000) {
            riseRate = 0x60;
        } else {
            riseRate = 0x4cd;
        }
        if (dy > 0) {
            step = FixedPointMultiply12(dy, riseRate);
            if (step <= dy) {
                dy = step < 0 ? 0 : step;
            }
        } else {
            step = FixedPointMultiply12(dy, riseRate);
            if (step > 0) {
                dy = 0;
            } else if (step >= dy) {
                dy = step;
            }
        }
        tracking->target.y += dy;
    } else {
        tracking->target.y = tracking->savedTarget.y;
    }
}
