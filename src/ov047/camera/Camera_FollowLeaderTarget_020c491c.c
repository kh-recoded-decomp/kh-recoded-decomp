#include "nitro/types.h"
#include "nitro/fx_types.h"

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
    VecFx32 anchor;
    u8 pad_B0[0x18];
    fx32 heightSpeed;
    u8 pad_CC[0x64];
    fx32 settleTimer;
} CameraTracking;

typedef struct CameraManager {
    u8 pad_00[0xe4];
    int mode;
    u8 pad_E8[0x8];
    u32 flags;
} CameraManager;

typedef void (*CameraUpdateFn)(void);

extern u16 data_02060500;
extern VecFx32 data_0205ab3c;
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern fx32 func_ov046_020c1a70(int mode);
extern fx32 func_ov046_020c1a48(int mode);
extern fx32 func_ov046_020c19f0(int mode);
extern int FX_Div_01ff9c84(int numer, int denom);
extern BOOL Camera_IsFrozen_020c0c1c(void);
extern BOOL IsLeaderFlag3Active_0206e198(void);
extern u32 func_ov001_0206c2c8(void);
extern BOOL IsHeldEntryFlag2Active_0206e33c(void);
extern VecFx32 *func_ov001_0206c284(void);
extern BOOL Camera_GetScreenEdgeMask_020c28d0(u32 *edgeMask, const VecFx32 *position, int marginX, int marginY);
extern BOOL IsAngleDifferenceLarge_020c4804(int from, int to);
extern u16 ApproachAngle_020c4824(int from, int to);
extern int FixedPointMultiply12(int left, int right);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern u16 FixedPointAtan2_020062bc(int vertical, int horizontal);
extern int ProjectWorldPositionToScreen_02019f84(const VecFx32 *position, int *screenX, int *screenY);
extern int BuildPickingRay_0201a10c(int px, int py, VecFx32 *pNear, VecFx32 *pFar);
extern u16 Math_AcosIdx_0202ab20(int cosine);
extern BOOL Camera_UpdateTracking_020c631c(void *context);
extern void func_ov047_020c4768(void);

CameraUpdateFn Camera_FollowLeaderTarget_020c491c(CameraTracking *tracking, CameraManager *camera)
{
    VecFx32 toFocus;
    VecFx32 nearPoint;
    VecFx32 edgePoint;
    VecFx32 origin;
    VecFx32 edgeDir;
    VecFx32 nearDir;
    u32 mask;
    int screenX;
    int screenY;
    fx32 limit;
    CameraUpdateFn next = NULL;
    VecFx32 *focus = Camera_GetFocusPosition_020c1780();
    fx32 ratio = FX_Div_01ff9c84(func_ov046_020c1a70(camera->mode), func_ov046_020c1a70(0));
    fx32 oldHeight = tracking->savedHeight;
    BOOL blocked;
    VecFx32 *target;
    fx32 rate;
    u16 heading;
    u32 angle;
    fx32 dot;

    if (Camera_IsFrozen_020c0c1c()) {
        return next;
    }
    if (!IsLeaderFlag3Active_0206e198()) {
        return next;
    }
    if (func_ov001_0206c2c8()) {
        camera->flags &= ~0x100;
    }
    if ((!func_ov001_0206c2c8() && !(camera->flags & 0x100) && !(camera->flags & 0x80000000)) || focus == NULL ||
        IsHeldEntryFlag2Active_0206e33c() || (camera->flags & 0x8000) || (camera->flags & 0x20000000)) {
        camera->flags &= ~0x20;
        tracking->savedHeight = func_ov046_020c1a48(camera->mode);
        tracking->savedUnk18 = func_ov046_020c19f0(camera->mode);
        if (data_02060500 & 4) {
            camera->flags |= 0x2000;
            camera->flags |= 0x800;
        }
        next = func_ov047_020c4768;
        goto settle;
    }
    if ((camera->flags & 0x40) || (camera->flags & 0x80)) {
        if (camera->flags & 0x100) {
            target = &tracking->anchor;
        } else {
            target = func_ov001_0206c284();
        }
        if (target == NULL) {
            goto settle;
        }
        blocked = FALSE;
        if (!Camera_GetScreenEdgeMask_020c28d0(&mask, target, 0, 0x28)) {
            if (!IsAngleDifferenceLarge_020c4804(tracking->angle, tracking->savedAngle)) {
                rate = FX_Div_01ff9c84(tracking->savedHeight, 0xa000);
                if (rate < 0) {
                    rate = -rate;
                }
                if ((mask & 4) && FixedPointMultiply12(-0x2000, ratio) < tracking->savedHeight) {
                    tracking->savedHeight -= FixedPointMultiply12(tracking->heightSpeed + rate, 0x2800);
                }
                if (mask & 8) {
                    limit = FixedPointMultiply12(func_ov046_020c1a70(camera->mode), 0xd9a);
                    if (tracking->savedHeight < limit) {
                        tracking->savedHeight += FixedPointMultiply12(tracking->heightSpeed + rate, 0x2800);
                        if (tracking->savedHeight > limit) {
                            tracking->savedHeight = limit;
                        }
                    }
                }
            }
        } else {
            blocked = TRUE;
        }
        VEC_Subtract_01ff9e3c(focus, target, &toFocus);
        toFocus.y = 0;
        VEC_Normalize_01ffaff4(&toFocus, &toFocus);
        heading = FixedPointAtan2_020062bc(toFocus.x, toFocus.z);
        tracking->savedAngle = ApproachAngle_020c4824(tracking->savedAngle, heading);
        if (!(camera->flags & 0x100)) {
            if (!IsAngleDifferenceLarge_020c4804(tracking->angle, heading) || Camera_GetScreenEdgeMask_020c28d0(&mask, target, 0x50, 0)) {
                if (blocked) {
                    camera->flags &= ~0x40;
                    camera->flags &= ~0x80;
                }
            }
        }
        Camera_UpdateTracking_020c631c(NULL);
    } else {
        target = func_ov001_0206c284();
        if (target == NULL) {
            goto settle;
        }
        if (!Camera_GetScreenEdgeMask_020c28d0(&mask, target, 0, 0x28)) {
            rate = FX_Div_01ff9c84(tracking->savedHeight, 0xa000);
            if (rate < 0) {
                rate = -rate;
            }
            if ((mask & 4) && FixedPointMultiply12(-0x2000, ratio) < tracking->savedHeight) {
                tracking->savedHeight -= FixedPointMultiply12(tracking->heightSpeed + rate, 0x300);
            }
            if (mask & 8) {
                limit = FixedPointMultiply12(func_ov046_020c1a70(camera->mode), 0xd9a);
                if (tracking->savedHeight < limit) {
                    tracking->savedHeight += FixedPointMultiply12(tracking->heightSpeed + rate, 0x300);
                    if (tracking->savedHeight > limit) {
                        tracking->savedHeight = limit;
                    }
                }
            }
        } else if (Camera_GetScreenEdgeMask_020c28d0(&mask, target, 0, 0x50)) {
            fx32 delta = FixedPointMultiply12(func_ov046_020c1a48(camera->mode) - tracking->savedHeight, 0xc0);

            if ((delta < 0 ? -delta : delta) < 0x10) {
                tracking->savedHeight = func_ov046_020c1a48(camera->mode);
            } else {
                tracking->savedHeight += delta;
            }
            tracking->savedUnk18 = func_ov046_020c19f0(camera->mode);
        }
        if (!Camera_GetScreenEdgeMask_020c28d0(&mask, target, 0x50, 0)) {
            angle = tracking->angle;
            ProjectWorldPositionToScreen_02019f84(target, &screenX, &screenY);
            BuildPickingRay_0201a10c(screenX, screenY, &nearPoint, NULL);
            if (mask & 2) {
                screenX = 0xaf;
            }
            if (mask & 1) {
                screenX = 0x50;
            }
            screenY = 0;
            BuildPickingRay_0201a10c(screenX, 0, &edgePoint, NULL);
            origin = data_0205ab3c;
            VEC_Subtract_01ff9e3c(&edgePoint, &origin, &edgeDir);
            edgeDir.y = 0;
            VEC_NormalizeUnchecked_01ff9f88(&edgeDir, &edgeDir);
            VEC_Subtract_01ff9e3c(&nearPoint, &origin, &nearDir);
            nearDir.y = 0;
            VEC_NormalizeUnchecked_01ff9f88(&nearDir, &nearDir);
            dot = VEC_DotProduct_01ff9e6c(&edgeDir, &nearDir);
            if (mask & 2) {
                angle = (u16)(tracking->angle - Math_AcosIdx_0202ab20(dot));
            }
            if (mask & 1) {
                angle = (u16)(tracking->angle + Math_AcosIdx_0202ab20(dot));
            }
            tracking->savedAngle = angle;
            if (!Camera_GetScreenEdgeMask_020c28d0(&mask, target, 0x20, 0x20)) {
                camera->flags |= 0x80;
            }
        }
        Camera_UpdateTracking_020c631c(NULL);
    }
settle:
    if (oldHeight == tracking->savedHeight) {
        fx32 goal = func_ov046_020c1a48(camera->mode);

        if (tracking->savedHeight != goal) {
            tracking->settleTimer += 0x1000;
            if (tracking->settleTimer > 0x1e000) {
                fx32 diff = goal - tracking->savedHeight;
                int sign;
                fx32 step;

                if (diff >= 0) {
                    sign = 1;
                } else {
                    sign = -1;
                }
                step = FixedPointMultiply12(diff, 0xcd);
                step += sign * 0x80;
                if ((diff < 0 ? -diff : diff) < (step < 0 ? -step : step)) {
                    tracking->savedHeight = goal;
                    tracking->settleTimer = 0;
                } else {
                    tracking->savedHeight += step;
                }
            }
        } else {
            tracking->settleTimer = 0;
        }
    } else {
        tracking->settleTimer = 0;
    }
    return next;
}
