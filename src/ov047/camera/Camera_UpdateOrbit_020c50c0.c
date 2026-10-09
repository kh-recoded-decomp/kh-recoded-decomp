#pragma opt_propagation off
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
    int angle;
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
    int unk_F4;
    CameraBox bounds;
    u8 pad_110[0x18];
    CameraManagerFlags extraFlags;
    u8 pad_12C[0x10];
    CameraTracking tracking;
} CameraManager;

typedef struct FxPair {
    fx32 x;
    fx32 y;
} FxPair;

extern const s16 data_0205356c[];
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern fx32 Camera_ComputeFollowDistance_020c1a70(int preset);
extern int FX_Div_01ff9c84(int numer, int denom);
extern u16 Math_AsinIdx_0202aaa8(int sine);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *target, fx32 angle);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern void ScalePairInPlace_0204a350(FxPair *pair, fx32 scale);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *input, VecFx32 *output);
extern void Camera_RefreshCollisionBounds_020c60e8(CameraTracking *tracking, CameraManager *camera);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void Camera_UpdateOrbit_020c50c0(CameraTracking *tracking, CameraManager *camera, BOOL snap)
{
    VecFx32 upAxis;
    VecFx32 pitchAxis;
    FxPair scaled;
    FxPair pair;
    fx32 goal = tracking->savedHeight;
    fx32 oldHeight = tracking->height;
    fx32 distance;
    fx32 oldSine;
    fx32 newSine;
    s32 pitchDelta;
    s16 prevAngle;
    s32 rate;
    fx32 horizontal;
    fx32 boostedRate;

    if (oldHeight != goal) {
        if (snap) {
            tracking->height = goal;
        } else {
            fx32 diff = goal - oldHeight;
            fx32 absDiff = diff < 0 ? -diff : diff;

            if (absDiff <= 0x100) {
                tracking->height = goal;
            } else {
                tracking->height += FixedPointMultiply12(diff, 0x600);
            }
        }
        distance = Camera_ComputeFollowDistance_020c1a70(camera->mode);
        oldSine = FX_Div_01ff9c84(oldHeight, distance);
        if (oldSine > 0x1000) {
            oldSine = 0x1000;
        } else if (oldSine < -0x1000) {
            oldSine = -0x1000;
        }
        newSine = FX_Div_01ff9c84(tracking->height, distance);
        if (newSine > 0x1000) {
            newSine = 0x1000;
        } else if (newSine < -0x1000) {
            newSine = -0x1000;
        }
        pitchDelta = (s64)(s16)(Math_AsinIdx_0202aaa8(newSine) - Math_AsinIdx_0202aaa8(oldSine)) * 0x6488 / 0x10000;
        if ((pitchDelta > 0 && tracking->direction.y <= oldSine + 0x10) ||
            (pitchDelta < 0 && tracking->direction.y >= oldSine - 0x10)) {
            VEC_Subtract_01ff9e3c(&tracking->lookAt, &tracking->target, &tracking->lookAt);
            pitchAxis = MakeVec(0, 0x1000, 0);
            RotateVecTowardVec_0204b0ac(&tracking->lookAt, &pitchAxis, pitchDelta);
            VEC_Add_01ff9e0c(&tracking->lookAt, &tracking->target, &tracking->lookAt);
        }
    }
    if (tracking->angle != tracking->savedAngle) {
        prevAngle = tracking->angle;
        if (snap) {
            tracking->angle = tracking->savedAngle;
        } else {
            fx32 step;

            rate = 0x800;
            if (camera->flags & 0x20) {
                rate = 0x400;
            }
            if (tracking->state == 4) {
                rate = 0xd00;
            }
            if (!(camera->flags & 0x20008000)) {
                int timer = tracking->turnTimer;

                if (timer > 0x333) {
                    rate = 0x200;
                    boostedRate = rate + FixedPointMultiply12(0x600, FX_Div_01ff9c84(timer - 0x333, 0xccd));
                    if (boostedRate > 0x800) {
                        rate = 0x800;
                    } else if (boostedRate >= 0x200) {
                        rate = boostedRate;
                    }
                } else if (timer > 0) {
                    rate = 0x200;
                }
            }
            step = FixedPointMultiply12((s16)(tracking->savedAngle - tracking->angle), rate);
            tracking->angle = step == 0 ? tracking->savedAngle : (u16)(tracking->angle + step);
        }
        {
            s32 turn = (s64)(s16)-(s16)(tracking->angle - prevAngle) * 0x6488 / 0x10000;

            upAxis = MakeVec(0, 0x1000, 0);
            VEC_Subtract_01ff9e3c(&tracking->lookAt, &tracking->target, &tracking->lookAt);
            RotateVectorAroundAxis_0204b34c(&camera->view.up, &upAxis, turn);
            RotateVectorAroundAxis_0204b34c(&tracking->lookAt, &upAxis, turn);
            VEC_Add_01ff9e0c(&tracking->lookAt, &tracking->target, &tracking->lookAt);
        }
    }
    if (tracking->angle == tracking->savedAngle) {
        tracking->trackFlags.turning = 0;
    }
    {
        s64 radius = Camera_ComputeFollowDistance_020c1a70(camera->mode);
        s64 height = tracking->height;
        int index;

        horizontal = (fx32)((radius * radius + 0x800) >> 12) - (fx32)((height * height + 0x800) >> 12);
        if (horizontal < 0x80) {
            horizontal = 0x80;
        }
        horizontal = FX_Sqrt_01ff9cfc(horizontal);
        index = (u16)tracking->angle >> 4;
        pair.x = data_0205356c[(0x400 - index) & 0xfff];
        pair.y = data_0205356c[index];
        scaled = pair;
        ScalePairInPlace_0204a350(&scaled, horizontal);
        {
            fx32 negZ = -scaled.x;
            fx32 negY = -tracking->height;

            tracking->direction.x = -scaled.y;
            tracking->direction.y = negY;
            tracking->direction.z = negZ;
        }
    }
    VEC_NormalizeUnchecked_01ff9f88(&tracking->direction, &tracking->direction);
    Camera_RefreshCollisionBounds_020c60e8(tracking, camera);
}













