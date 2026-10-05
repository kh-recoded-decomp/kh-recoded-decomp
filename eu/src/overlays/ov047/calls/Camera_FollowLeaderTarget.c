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
extern VecFx32 NNS_G3dGlb_camPos;
extern VecFx32 *Camera_GetFocusPosition(void);
extern fx32 Camera_ComputeFollowDistance(int mode);
extern fx32 func_ov046_020c1a68(int mode);
extern fx32 func_ov046_020c1a10(int mode);
extern int FX_Div(int numer, int denom);
extern BOOL Camera_IsFrozen(void);
extern BOOL IsLeaderFlag3Active(void);
extern u32 func_ov001_0206c2c8(void);
extern BOOL IsHeldEntryFlag2Active(void);
extern VecFx32 *func_ov001_0206c284(void);
extern BOOL Camera_GetScreenEdgeMask(u32 *edgeMask, const VecFx32 *position, int marginX, int marginY);
extern BOOL IsAngleDifferenceLarge(int from, int to);
extern u16 ApproachAngle(int from, int to);
extern int FX_Mul(int left, int right);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern u16 FX_Atan2Idx(int vertical, int horizontal);
extern int NNS_G3dWorldPosToScrPos(const VecFx32 *position, int *screenX, int *screenY);
extern int NNS_G3dScrPosToWorldLine(int px, int py, VecFx32 *pNear, VecFx32 *pFar);
extern u16 Math_AcosIdx(int cosine);
extern BOOL Camera_UpdateTracking(void *context);
extern void Camera_FollowControllerUpdate(void);

CameraUpdateFn Camera_FollowLeaderTarget(CameraTracking *tracking, CameraManager *camera)
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
    VecFx32 *focus = Camera_GetFocusPosition();
    fx32 ratio = FX_Div(Camera_ComputeFollowDistance(camera->mode), Camera_ComputeFollowDistance(0));
    fx32 oldHeight = tracking->savedHeight;
    BOOL blocked;
    VecFx32 *target;
    fx32 rate;
    u16 heading;
    u32 angle;
    fx32 dot;

    if (Camera_IsFrozen()) {
        return next;
    }
    if (!IsLeaderFlag3Active()) {
        return next;
    }
    if (func_ov001_0206c2c8()) {
        camera->flags &= ~0x100;
    }
    if ((!func_ov001_0206c2c8() && !(camera->flags & 0x100) && !(camera->flags & 0x80000000)) || focus == NULL ||
        IsHeldEntryFlag2Active() || (camera->flags & 0x8000) || (camera->flags & 0x20000000)) {
        camera->flags &= ~0x20;
        tracking->savedHeight = func_ov046_020c1a68(camera->mode);
        tracking->savedUnk18 = func_ov046_020c1a10(camera->mode);
        if (data_02060500 & 4) {
            camera->flags |= 0x2000;
            camera->flags |= 0x800;
        }
        next = Camera_FollowControllerUpdate;
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
        if (!Camera_GetScreenEdgeMask(&mask, target, 0, 0x28)) {
            if (!IsAngleDifferenceLarge(tracking->angle, tracking->savedAngle)) {
                rate = FX_Div(tracking->savedHeight, 0xa000);
                if (rate < 0) {
                    rate = -rate;
                }
                if ((mask & 4) && FX_Mul(-0x2000, ratio) < tracking->savedHeight) {
                    tracking->savedHeight -= FX_Mul(tracking->heightSpeed + rate, 0x2800);
                }
                if (mask & 8) {
                    limit = FX_Mul(Camera_ComputeFollowDistance(camera->mode), 0xd9a);
                    if (tracking->savedHeight < limit) {
                        tracking->savedHeight += FX_Mul(tracking->heightSpeed + rate, 0x2800);
                        if (tracking->savedHeight > limit) {
                            tracking->savedHeight = limit;
                        }
                    }
                }
            }
        } else {
            blocked = TRUE;
        }
        VEC_Subtract(focus, target, &toFocus);
        toFocus.y = 0;
        func_01ffaff4(&toFocus, &toFocus);
        heading = FX_Atan2Idx(toFocus.x, toFocus.z);
        tracking->savedAngle = ApproachAngle(tracking->savedAngle, heading);
        if (!(camera->flags & 0x100)) {
            if (!IsAngleDifferenceLarge(tracking->angle, heading) || Camera_GetScreenEdgeMask(&mask, target, 0x50, 0)) {
                if (blocked) {
                    camera->flags &= ~0x40;
                    camera->flags &= ~0x80;
                }
            }
        }
        Camera_UpdateTracking(NULL);
    } else {
        target = func_ov001_0206c284();
        if (target == NULL) {
            goto settle;
        }
        if (!Camera_GetScreenEdgeMask(&mask, target, 0, 0x28)) {
            rate = FX_Div(tracking->savedHeight, 0xa000);
            if (rate < 0) {
                rate = -rate;
            }
            if ((mask & 4) && FX_Mul(-0x2000, ratio) < tracking->savedHeight) {
                tracking->savedHeight -= FX_Mul(tracking->heightSpeed + rate, 0x300);
            }
            if (mask & 8) {
                limit = FX_Mul(Camera_ComputeFollowDistance(camera->mode), 0xd9a);
                if (tracking->savedHeight < limit) {
                    tracking->savedHeight += FX_Mul(tracking->heightSpeed + rate, 0x300);
                    if (tracking->savedHeight > limit) {
                        tracking->savedHeight = limit;
                    }
                }
            }
        } else if (Camera_GetScreenEdgeMask(&mask, target, 0, 0x50)) {
            fx32 delta = FX_Mul(func_ov046_020c1a68(camera->mode) - tracking->savedHeight, 0xc0);

            if ((delta < 0 ? -delta : delta) < 0x10) {
                tracking->savedHeight = func_ov046_020c1a68(camera->mode);
            } else {
                tracking->savedHeight += delta;
            }
            tracking->savedUnk18 = func_ov046_020c1a10(camera->mode);
        }
        if (!Camera_GetScreenEdgeMask(&mask, target, 0x50, 0)) {
            angle = tracking->angle;
            NNS_G3dWorldPosToScrPos(target, &screenX, &screenY);
            NNS_G3dScrPosToWorldLine(screenX, screenY, &nearPoint, NULL);
            if (mask & 2) {
                screenX = 0xaf;
            }
            if (mask & 1) {
                screenX = 0x50;
            }
            screenY = 0;
            NNS_G3dScrPosToWorldLine(screenX, 0, &edgePoint, NULL);
            origin = NNS_G3dGlb_camPos;
            VEC_Subtract(&edgePoint, &origin, &edgeDir);
            edgeDir.y = 0;
            VEC_Normalize(&edgeDir, &edgeDir);
            VEC_Subtract(&nearPoint, &origin, &nearDir);
            nearDir.y = 0;
            VEC_Normalize(&nearDir, &nearDir);
            dot = VEC_DotProduct(&edgeDir, &nearDir);
            if (mask & 2) {
                angle = (u16)(tracking->angle - Math_AcosIdx(dot));
            }
            if (mask & 1) {
                angle = (u16)(tracking->angle + Math_AcosIdx(dot));
            }
            tracking->savedAngle = angle;
            if (!Camera_GetScreenEdgeMask(&mask, target, 0x20, 0x20)) {
                camera->flags |= 0x80;
            }
        }
        Camera_UpdateTracking(NULL);
    }
settle:
    if (oldHeight == tracking->savedHeight) {
        fx32 goal = func_ov046_020c1a68(camera->mode);

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
                step = FX_Mul(diff, 0xcd);
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
