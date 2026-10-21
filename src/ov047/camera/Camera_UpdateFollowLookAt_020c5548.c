#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTrackingFlags {
    int unk_0 : 1;
    int turning : 1;
} CameraTrackingFlags;

typedef struct CameraTracking {
    int state;
    u8 pad_04[0x8];
    fx32 distance;
    int angle;
    fx32 height;
    u8 pad_18[0xc];
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    VecFx32 prevTarget;
    VecFx32 direction;
    VecFx32 prevDirection;
    VecFx32 prevSavedLookAt;
    fx32 prevHeight;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    int savedAngle;
    u8 pad_9C[0x24];
    fx32 followSpeed;
    u8 pad_C4[0x14];
    fx32 shakeOffset;
    int shakeTimer;
    BOOL shakeRising;
    fx32 shakeTarget;
    int shakeStep;
    u8 pad_EC[0x3c];
    int holdTimer;
    CameraTrackingFlags trackFlags;
    u8 pad_130[0xc4];
    VecFx32 surfaceNormal;
    VecFx32 surfaceAxis;
    u8 pad_20C[0xa8];
    u8 constraintMode;
} CameraTracking;

typedef struct CameraManagerFlags {
    int unk_0 : 1;
} CameraManagerFlags;

typedef struct CameraManager {
    u8 pad_00[0xe4];
    int mode;
    u8 pad_E8[0x8];
    u32 flags;
    u8 pad_F4[0x34];
    CameraManagerFlags extraFlags;
} CameraManager;

typedef struct FxPair {
    fx32 x;
    fx32 y;
} FxPair;

typedef struct SinCos {
    fx32 cos;
    fx32 sin;
} SinCos;

typedef struct ShakeStep {
    fx32 amount;
    fx32 value;
    int duration;
} ShakeStep;

extern const s16 data_0205356c[];
extern const s16 data_02053aac[];
extern ShakeStep data_ov047_020c7284[];
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern fx32 Camera_ComputeFollowDistance_020c1a70(int mode);
extern void Camera_PlaceTrackingEye_020c4880(VecFx32 *target, VecFx32 *eye, fx32 *distance, const VecFx32 *focus, int angle, fx32 followDistance, fx32 currentDistance);
extern unsigned int func_ov046_020c2ab8(CameraManager *camera);
extern BOOL Camera_ResolveLookAtCollision_020c6758(CameraManager *camera, CameraTracking *tracking);
extern void Camera_SweepLookAt_020c6594(CameraTracking *tracking, fx32 radius);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern int FX_Div_01ff9c84(int numer, int denom);
extern int FX_Sqrt_01ff9cfc(int value);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern u16 Math_AsinIdx_0202aaa8(int sine);
extern fx32 ComputeOneMinusSquareFraction_02049d6c(fx32 value);
extern fx32 DotFx32Xy_0204a390(const FxPair *a, const FxPair *b);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 GetUnitRejectionFromAxis_0204aea8(const VecFx32 *vec, const VecFx32 *axis);

#define FX_MUL64(a, b) ((fx32)(((s64)(a) * (b) + 0x800LL) >> 12))

static inline SinCos GetSinCos(int index)
{
    SinCos result;
    result.cos = data_0205356c[(0x400 - index) & 0xfff];
    result.sin = data_0205356c[index];
    return result;
}

static inline fx32 AbsFx(fx32 value)
{
    return value < 0 ? -value : value;
}

static inline VecFx32 Sub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 Add(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 NormalizedDiff(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 input;
    VecFx32 diff;
    VecFx32 result;

    VEC_Subtract_01ff9e3c(a, b, &diff);
    input = diff;
    VEC_NormalizeUnchecked_01ff9f88(&input, &result);
    return result;
}

static inline VecFx32 ScaledVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;

    ScaleVecFx32InPlace_0204a5e4(&result, scale);
    return result;
}

static inline VecFx32 *NormalizedCrossPtr(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 input;
    VecFx32 cross;
    VecFx32 result;

    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    input = cross;
    VEC_NormalizeUnchecked_01ff9f88(&input, &result);
    return &result;
}

static inline VecFx32 ProjectOnto(const VecFx32 *vec, const VecFx32 *axis, VecFx32 *axisOut)
{
    VecFx32 scaled;
    VecFx32 axisCopy = *axis;
    fx32 dot;

    *axisOut = axisCopy;
    dot = VEC_DotProduct_01ff9e6c(vec, axisOut);
    scaled = axisCopy;
    ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
    return scaled;
}

static inline VecFx32 Reject(const VecFx32 *vec, VecFx32 axis, fx32 dot)
{
    VecFx32 projection;
    VecFx32 scaled;
    VecFx32 result;

    scaled = axis;
    ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
    projection = scaled;
    VEC_Subtract_01ff9e3c(vec, &projection, &result);
    return result;
}

static inline VecFx32 FlatRight(SinCos sc)
{
    VecFx32 sideCopy;
    VecFx32 upCopy;
    VecFx32 side;
    VecFx32 up;
    VecFx32 result;

    up.x = 0;
    up.y = 0x1000;
    up.z = 0;
    upCopy = up;
    side.x = -sc.sin;
    side.y = 0;
    side.z = -sc.cos;
    sideCopy = side;
    result.x = -FX_MUL64(sideCopy.z, upCopy.y);
    result.y = 0;
    result.z = FX_MUL64(sideCopy.x, upCopy.y);
    return result;
}

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline FxPair MakePair(fx32 x, fx32 y)
{
    FxPair pair;
    pair.x = x;
    pair.y = y;
    return pair;
}

void Camera_UpdateFollowLookAt_020c5548(CameraTracking *tracking, CameraManager *camera, BOOL reset)
{
    BOOL moved = FALSE;
    VecFx32 delta;
    VecFx32 dir;
    VecFx32 offset;
    VecFx32 normal;
    VecFx32 right;
    VecFx32 flat;
    VecFx32 unit;
    VecFx32 sway;
    VecFx32 predicted;
    VecFx32 rejected;
    FxPair heading;
    FxPair facing;
    fx32 mag;
    VecFx32 *focus;

    focus = Camera_GetFocusPosition_020c1780();
    Camera_PlaceTrackingEye_020c4880(&tracking->savedTarget, &tracking->savedLookAt, &tracking->savedDistance, focus,
                                     tracking->angle, Camera_ComputeFollowDistance_020c1a70(camera->mode), tracking->savedDistance);
    if (reset) {
        tracking->savedAngle = tracking->angle;
        tracking->trackFlags.turning = 0;
    }
    delta = Sub(&tracking->savedLookAt, &tracking->lookAt);
    mag = VEC_Mag_01ff9f28(&delta);
    if (mag != 0) {
        if (reset) {
            tracking->lookAt = tracking->savedLookAt;
        } else {
            fx32 lookAtDist = func_01ffa0f4(&tracking->lookAt, &tracking->target);
            fx32 savedDist = func_01ffa0f4(&tracking->savedLookAt, &tracking->target);
            fx32 ratio;
            int pitch;

            dir = NormalizedDiff(&tracking->prevTarget, &tracking->savedLookAt);
            offset = Sub(&tracking->target, &tracking->prevTarget);
            ratio = tracking->height - tracking->prevHeight;
            if (ratio < 0) {
                ratio = -ratio;
            }
            ratio = FX_Div_01ff9c84(ratio, Camera_ComputeFollowDistance_020c1a70(camera->mode));
            if (ratio > 0x1000) {
                ratio = 0x1000;
            }
            pitch = Math_AsinIdx_0202aaa8(ratio);
            if (tracking->constraintMode != 0 &&
                ((lookAtDist >= savedDist && mag > 0x2000) ||
                 (!camera->extraFlags.unk_0 &&
                  VEC_DotProduct_01ff9e6c(&dir, &tracking->prevDirection) < data_0205356c[(0x400 - ((pitch + 0xe38) >> 4)) & 0xfff])) &&
                !(camera->flags & 0x4000000) && !func_ov046_020c2ab8(camera)) {
                if (tracking->holdTimer == -1) {
                    tracking->holdTimer = 0;
                } else {
                    tracking->holdTimer += 0x1000;
                    if (tracking->holdTimer >= 0x1e000) {
                        tracking->holdTimer = -1;
                        camera->flags |= 0x4000000;
                    }
                }
            } else if (lookAtDist < savedDist || tracking->constraintMode == 0) {
                camera->flags &= ~0x4000000;
                tracking->holdTimer = -1;
            }
            if (tracking->holdTimer == -1) {
                predicted = Add(&tracking->prevSavedLookAt, &offset);
                if (func_01ffa0f4(&predicted, &tracking->savedLookAt) > 0x333) {
                    fx32 speed;
                    fx32 limit;

                    if ((tracking->constraintMode != 0 && lookAtDist + 0x333 < savedDist) ||
                        (!(camera->flags & 0x2000) && (limit = data_02053aac[10], FX_Div_01ff9c84(AbsFx(delta.y), mag) > limit))) {
                        speed = 0x266;
                    } else if (VEC_Mag_01ff9f28(&offset) > 0x400) {
                        speed = 0x99a;
                    } else {
                        speed = 0x4cd;
                    }
                    tracking->followSpeed = speed;
                }
                if (tracking->constraintMode != 0) {
                    if (tracking->constraintMode != 1 && AbsDotProduct_0204a96c(&tracking->surfaceNormal, &tracking->surfaceAxis) < 0xff0) {
                        offset = ProjectOnto(&offset, NormalizedCrossPtr(&tracking->surfaceNormal, &tracking->surfaceAxis), &normal);
                    } else {
                        offset = Reject(&offset, tracking->surfaceNormal, VEC_DotProduct_01ff9e6c(&offset, &tracking->surfaceNormal));
                    }
                }
                VEC_Subtract_01ff9e3c(&delta, &offset, &delta);
                ScaleVecFx32InPlace_0204a5e4(&delta, tracking->followSpeed);
                VEC_Add_01ff9e0c(&delta, &offset, &delta);
            } else {
                delta = offset;
            }
            VEC_Add_01ff9e0c(&tracking->lookAt, &delta, &tracking->lookAt);
            moved = TRUE;
        }
    } else {
        camera->flags &= ~0x4000000;
        tracking->holdTimer = -1;
    }
    flat = FlatRight(GetSinCos((u16)tracking->angle >> 4));
    right = flat;
    VEC_Subtract_01ff9e3c(&tracking->target, &tracking->lookAt, &tracking->target);
    tracking->target = Reject(&tracking->target, flat, VEC_DotProduct_01ff9e6c(&tracking->target, &right));
    VEC_Add_01ff9e0c(&tracking->target, &tracking->lookAt, &tracking->target);
    tracking->direction = NormalizedDiff(&tracking->target, &tracking->lookAt);
    rejected = GetUnitRejectionFromAxis_0204aea8(&tracking->direction, &right);
    tracking->direction = rejected;
    heading = MakePair(tracking->direction.x, tracking->direction.z);
    facing = MakePair(-data_0205356c[tracking->angle >> 4], -data_0205356c[(0x400 - (tracking->angle >> 4)) & 0xfff]);
    if (DotFx32Xy_0204a390(&heading, &facing) < 0) {
        tracking->direction.x = -tracking->direction.x;
        tracking->direction.z = -tracking->direction.z;
    }
    if (!camera->extraFlags.unk_0) {
        fx32 limit = FX_Div_01ff9c84(tracking->height, tracking->distance);

        if (-tracking->direction.y > limit) {
            fx32 horizontal = ComputeOneMinusSquareFraction_02049d6c(limit);

            tracking->direction.y = -limit;
            tracking->direction.x = -FixedPointMultiply12(data_0205356c[tracking->angle >> 4], horizontal);
            tracking->direction.z = -FixedPointMultiply12(data_0205356c[(0x400 - (tracking->angle >> 4)) & 0xfff], horizontal);
            VEC_Subtract_01ff9e3c(&tracking->lookAt, &tracking->target, &tracking->lookAt);
            tracking->lookAt = ScaledVec(&tracking->direction, VEC_DotProduct_01ff9e6c(&tracking->lookAt, &tracking->direction));
            VEC_Add_01ff9e0c(&tracking->lookAt, &tracking->target, &tracking->lookAt);
        }
    }
    if (moved && !func_ov046_020c2ab8(camera)) {
        if (tracking->holdTimer == -1 && !(camera->flags & 0x4000000)) {
            if (tracking->savedDistance == 0xc00) {
                VEC_MultAdd_01ffa09c(-tracking->savedDistance, &tracking->direction, &tracking->target, &tracking->lookAt);
                tracking->followSpeed = 0x4cd;
            } else if (Camera_ResolveLookAtCollision_020c6758(camera, tracking) && tracking->constraintMode != 0 && !camera->extraFlags.unk_0) {
                Camera_SweepLookAt_020c6594(tracking, 0x4cd);
            }
        } else if (Camera_ResolveLookAtCollision_020c6758(camera, tracking) && tracking->holdTimer == -1 &&
                   !(camera->flags & 0x4000000) && !camera->extraFlags.unk_0) {
            Camera_SweepLookAt_020c6594(tracking, 0x666);
        }
        if (tracking->followSpeed != 0x4cd && func_01ffa0f4(&tracking->savedLookAt, &tracking->lookAt) < 0x10) {
            tracking->followSpeed = 0x4cd;
        }
    }
    if (tracking->state == 3) {
        fx32 step;
        fx32 x;
        fx32 z;
        fx32 lengthSq;

        if (tracking->shakeRising) {
            step = tracking->shakeTarget - tracking->shakeOffset;
        } else {
            step = -(tracking->shakeTarget + tracking->shakeOffset);
        }
        tracking->shakeOffset += FixedPointMultiply12(step, 0x800);
        if (data_ov047_020c7284[tracking->shakeStep].duration < tracking->shakeTimer) {
            tracking->shakeRising = !tracking->shakeRising;
            tracking->shakeTimer = 0;
            tracking->shakeTarget -= data_ov047_020c7284[tracking->shakeStep].amount;
        }
        tracking->shakeTimer += 0x89;
        VEC_Subtract_01ff9e3c(&tracking->lookAt, &tracking->target, &unit);
        VEC_Normalize_01ffaff4(&unit, &unit);
        x = unit.x;
        z = unit.z;
        lengthSq = FixedPointMultiply12(x, x) + FixedPointMultiply12(z, z);
        if (lengthSq != 0) {
            fx32 sideX = FX_Sqrt_01ff9cfc(FX_Div_01ff9c84(FixedPointMultiply12(unit.z, unit.z), lengthSq));
            fx32 sideZ = FX_Sqrt_01ff9cfc(FX_Div_01ff9c84(FixedPointMultiply12(unit.x, unit.x), lengthSq));

            SetVec(&sway, sideX, 0, -sideZ);
            VEC_MultAdd_01ffa09c(tracking->shakeOffset, &sway, &tracking->lookAt, &tracking->lookAt);
            VEC_MultAdd_01ffa09c(tracking->shakeOffset, &sway, &tracking->target, &tracking->target);
        }
        if (tracking->shakeTarget < 0x29) {
            tracking->shakeOffset = 0;
            tracking->shakeTimer = 0;
            tracking->state = 0;
        }
    }
}
