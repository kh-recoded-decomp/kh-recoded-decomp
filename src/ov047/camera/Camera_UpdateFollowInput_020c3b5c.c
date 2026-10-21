#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraTrackingFlags {
    int unk_0 : 1;
    int turning : 1;
} CameraTrackingFlags;

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touching;
    u16 invalid;
} TouchSample;

typedef struct CameraTracking {
    int state;
    int unk_04;
    int heading;
    fx32 distance;
    u32 angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    u8 pad_3C[0x58];
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
    u8 pad_A4[0x14];
    u16 pitch;
    u16 pitchAlt;
    fx32 baseStep;
    fx32 unk_C0;
    fx32 turnStep;
    fx32 heightStep;
    u8 pad_CC[0x2c];
    int turnTimer;
    fx32 turnSpeed;
    int holdTimer;
    fx32 prevBaseStep;
    fx32 prevTurnStep;
    fx32 prevHeightStep;
    u32 prevMask;
    TouchSample touch;
    u8 pad_11C[0x10];
    CameraTrackingFlags trackFlags;
} CameraTracking;

typedef struct CameraManager {
    fx32 pitchSin;
    fx32 pitchCos;
    u8 pad_08[0xd4];
    u32 inputFlags;
    u32 invertFlags;
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    u8 pad_F4[0x48];
    CameraTracking tracking;
} CameraManager;

typedef struct SaveFlags {
    u32 unk_0 : 9;
    u32 swapTurn : 1;
    u32 freeHeading : 1;
} SaveFlags;

typedef struct Entry Entry;

struct Entry {
    u8 pad[0x21c];
    u32 (*getFlags)(Entry *entry);
};

typedef void *(*CameraUpdateFn)(CameraTracking *tracking, CameraManager *camera);

extern CameraManager *g_cameraManager_020c34e0;
extern u16 data_020604fc;
extern u8 *data_0205fe0c;
extern const s16 data_0205356c[];
extern void Camera_SetMode_020c36c8(int mode, int arg);
extern fx32 Camera_GetSpeedScaledStep_020c19b4(void);
extern unsigned int func_ov046_020c2ab8(CameraManager *camera);
extern VecFx32 *Camera_GetFocusPosition_020c1780(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern Entry *GetBoundedEntryField_0206db5c(int index);
extern fx32 Camera_ComputeFollowDistance_020c1a70(int mode);
extern fx32 func_ov046_020c1a48(int mode);
extern fx32 Camera_GetModeDistance_020c19f0(int mode);
extern void Camera_ResetFollowState_020c3a78(void);
extern BOOL TryCopySourceBlock_020c6b58(TouchSample *dest);
extern int FX_Div_01ff9c84(int numer, int denom);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern BOOL Camera_ShouldStartManualTurn_020c3ad8(CameraTracking *tracking, CameraManager *camera, u32 flags);
extern BOOL IsHeldEntryFlag2Active_0206e33c(void);
extern void Camera_UpdateManualTurn_020c4668(void);
extern u32 func_ov001_0206c2c8(void);
extern void *Camera_TurnToLeaderHeading_020c4e3c(CameraTracking *tracking, CameraManager *camera);
extern void *Camera_FollowLeaderTarget_020c491c(CameraTracking *tracking, CameraManager *camera);
extern void *Camera_StartFollowTracking_020c5008(CameraTracking *tracking, CameraManager *camera);

static inline u32 GetEntryFlags(Entry *entry)
{
    if (entry->getFlags != NULL) {
        return entry->getFlags(entry);
    }
    return 0;
}

static inline fx32 AbsFx(fx32 value)
{
    return value < 0 ? -value : value;
}

void *Camera_UpdateFollowInput_020c3b5c(CameraUpdateFn *next)
{
    VecFx32 facing;
    VecFx32 view;
    TouchSample touch;
    CameraManager *camera = g_cameraManager_020c34e0;
    u32 mask = 0;
    CameraTracking *tracking = &camera->tracking;
    u32 startFlags = camera->flags;
    int dx;
    int dy;
    fx32 ratio;
    int negX;
    u32 up;
    u32 down;
    u32 entryFlags;
    fx32 stepX;
    fx32 stepY;
    s16 heading;
    int diff;
    BOOL follow;

    if (camera->mode == 0x17) {
        Camera_SetMode_020c36c8(camera->prevMode, 0);
        camera->flags &= ~0x2000;
    }
    tracking->baseStep = Camera_GetSpeedScaledStep_020c19b4();
    tracking->turnStep = Camera_GetSpeedScaledStep_020c19b4();
    tracking->heightStep = Camera_GetSpeedScaledStep_020c19b4();
    if (!func_ov046_020c2ab8(camera)) {
        BOOL reset = FALSE;

        if ((data_020604fc & 0x100) && Camera_GetFocusPosition_020c1780() == func_ov001_0206dc4c(0) &&
            !(GetEntryFlags(GetBoundedEntryField_0206db5c(0)) & 8)) {
            if (!(camera->flags & 0x400000)) {
                camera->flags |= 0x400000;
                tracking->holdTimer = 0;
            } else {
                tracking->holdTimer += 0x1000;
                if (tracking->holdTimer >= 0x5000) {
                    camera->flags |= 0x2000;
                    camera->flags |= 0x800;
                    camera->flags &= ~0x400000;
                }
            }
        } else if (camera->flags & 0x2000) {
            camera->flags &= ~0x2000;
            camera->flags &= ~0x800;
            camera->flags |= 0x1000;
            tracking->savedDistance = Camera_ComputeFollowDistance_020c1a70(camera->mode);
            tracking->savedHeight = func_ov046_020c1a48(camera->mode);
        } else {
            camera->flags &= ~0x400000;
        }
        if (!(camera->flags & 0x2000)) {
            Entry *entry;

            entryFlags = 0;
            entry = GetBoundedEntryField_0206db5c(0);
            if (entry->getFlags != NULL) {
                entryFlags = entry->getFlags(entry);
            }
            if (entryFlags & 8) {
                reset = TRUE;
            }
        }
        if (reset) {
            Camera_ResetFollowState_020c3a78();
        }
        if (camera->flags & 0x2000) {
            u16 keys = data_020604fc;

            if (keys & 0x40) {
                mask |= 2;
            } else if (keys & 0x80) {
                mask |= 1;
            }
            if (keys & 0x20) {
                mask |= 8;
            } else if (keys & 0x10) {
                mask |= 4;
            }
        } else if (TryCopySourceBlock_020c6b58(&touch)) {
            if (tracking->touch.touching == 1 && tracking->touch.invalid == 0 && touch.touching == 1 && touch.invalid == 0) {
                fx32 scaled;

                dx = (touch.x - tracking->touch.x) << 12;
                dy = (touch.y - tracking->touch.y) << 12;
                stepX = Camera_GetSpeedScaledStep_020c19b4();
                stepY = Camera_GetSpeedScaledStep_020c19b4();

                if (dx > 0x3000) {
                    if (!(tracking->prevMask & 8) || ((tracking->prevMask & 8) && dx > 0x6000)) {
                        stepX = Camera_GetSpeedScaledStep_020c19b4();
                        scaled = FixedPointMultiply12(FX_Div_01ff9c84(dx, 0x4000), Camera_GetSpeedScaledStep_020c19b4());
                        if (scaled > 0xa00) {
                            stepX = 0xa00;
                        } else if (scaled >= stepX) {
                            stepX = scaled;
                        }
                        mask |= 4;
                    }
                } else {
                    negX = ~dx;

                    if (negX > 0x3000 && (!(tracking->prevMask & 4) || ((tracking->prevMask & 4) && negX > 0x6000))) {
                        stepX = Camera_GetSpeedScaledStep_020c19b4();
                        scaled = FixedPointMultiply12(FX_Div_01ff9c84(negX, 0x4000), Camera_GetSpeedScaledStep_020c19b4());
                        if (scaled > 0xa00) {
                            stepX = 0xa00;
                        } else if (scaled >= stepX) {
                            stepX = scaled;
                        }
                        mask |= 8;
                    }
                }
                if (mask & tracking->prevMask & 0xc) {
                    if (stepX > tracking->prevTurnStep) {
                        tracking->turnStep = stepX;
                    } else {
                        tracking->turnStep = tracking->prevTurnStep;
                    }
                }
                if (dy > 0x4000) {
                    stepY = Camera_GetSpeedScaledStep_020c19b4();
                    scaled = FixedPointMultiply12(FX_Div_01ff9c84(dy, 0x4000), Camera_GetSpeedScaledStep_020c19b4());
                    if (scaled > 0xa00) {
                        stepY = 0xa00;
                    } else if (scaled >= stepY) {
                        stepY = scaled;
                    }
                    mask |= 1;
                } else {
                    int negY = ~dy;

                    if (negY > 0x4000) {
                        stepY = Camera_GetSpeedScaledStep_020c19b4();
                        scaled = FixedPointMultiply12(FX_Div_01ff9c84(negY, 0x4000), Camera_GetSpeedScaledStep_020c19b4());
                        if (scaled > 0xa00) {
                            stepY = 0xa00;
                        } else if (scaled >= stepY) {
                            stepY = scaled;
                        }
                        mask |= 2;
                    }
                }
                if (camera->flags & 0x10000) {
                    stepY = FixedPointMultiply12(stepY, 1);
                }
                if (mask & tracking->prevMask & 3) {
                    if (stepY > tracking->prevHeightStep) {
                        tracking->heightStep = stepY;
                    } else {
                        tracking->heightStep = tracking->prevHeightStep;
                    }
                }
            }
            tracking->touch = touch;
        } else {
            tracking->touch.invalid = 3;
        }
        camera->flags &= ~0x1000000;
        if (GetEntryFlags(GetBoundedEntryField_0206db5c(0)) & 8) {
            u16 yaw = GetBiasAdjustedField_0206dc80(0);

            facing.y = 0;
            facing.x = -data_0205356c[yaw >> 4];
            facing.z = -data_0205356c[(0x400 - (yaw >> 4)) & 0xfff];
            VEC_NormalizeUnchecked_01ff9f88(&facing, &facing);
            VEC_Subtract_01ff9e3c(&tracking->target, &tracking->lookAt, &view);
            view.y = 0;
            VEC_NormalizeUnchecked_01ff9f88(&view, &view);
            if (VEC_DotProduct_01ff9e6c(&facing, &view) < 0) {
                camera->flags |= 0x1000000;
                tracking->heightStep = 0xa00;
            }
            mask = 0;
        }
        tracking->prevMask = mask;
        tracking->prevBaseStep = tracking->baseStep;
        tracking->prevTurnStep = tracking->turnStep;
        tracking->prevHeightStep = tracking->heightStep;
    }
    if (!func_ov046_020c2ab8(camera)) {
        if (!(camera->flags & 0x200)) {
            if (Camera_ShouldStartManualTurn_020c3ad8(tracking, camera, startFlags)) {
                camera->flags |= 8;
            }
            if (camera->flags & 0x4000) {
                tracking->savedHeight = 0x5000;
                tracking->savedDistance = 0x8000;
                camera->flags &= ~0x4000;
            }
        }
        if (GetEntryFlags(GetBoundedEntryField_0206db5c(0)) & 8) {
            if (!(camera->flags & 0x10)) {
                camera->flags |= 0x10;
                camera->flags |= 8;
                camera->flags &= ~0x200;
            }
            mask = 0;
        } else {
            camera->flags &= ~0x10;
        }
    }
    if (IsHeldEntryFlag2Active_0206e33c()) {
        camera->flags |= 0x400;
    }
    if (camera->flags & 0x800) {
        if ((s32)tracking->pitch >= 0x1333) {
            tracking->pitch -= 0x140;
            tracking->pitchAlt -= 0x140;
            if ((s32)tracking->pitch < 0x1333) {
                tracking->pitch = 0x1333;
                tracking->pitchAlt = 0x1333;
                camera->flags &= ~0x800;
            }
            camera->pitchSin = data_0205356c[tracking->pitch >> 4];
            camera->pitchCos = data_0205356c[(0x400 - (tracking->pitchAlt >> 4)) & 0xfff];
        }
    } else if (camera->flags & 0x1000) {
        tracking->pitch += 0x140;
        tracking->pitchAlt += 0x140;
        if (tracking->pitch > 0x1555) {
            tracking->pitch = 0x1555;
            tracking->pitchAlt = 0x1555;
            camera->flags &= ~0x1000;
        }
        camera->pitchSin = data_0205356c[tracking->pitch >> 4];
        camera->pitchCos = data_0205356c[(0x400 - (tracking->pitchAlt >> 4)) & 0xfff];
    }
    if (!(camera->flags & 0x200)) {
        if (camera->flags & 2) {
            u32 left = mask & 4;
            fx32 climb;

            if ((left && !(camera->invertFlags & 0x10)) || ((mask & 8) && (camera->invertFlags & 0x10))) {
                tracking->savedAngle = (u16)(tracking->savedAngle - tracking->turnStep);
            }
            if (((mask & 8) && !(camera->invertFlags & 0x10)) || (left && (camera->invertFlags & 0x10))) {
                tracking->savedAngle = (u16)(tracking->savedAngle + tracking->turnStep);
            }
            up = mask & 0x10;
            if ((up && !(camera->invertFlags & 0x10)) || ((mask & 0x20) && (camera->invertFlags & 0x10))) {
                int angle = (u16)(tracking->savedAngle - 0x1fff);

                if (angle % 0x1fff != 0) {
                    angle -= angle % 0x1fff;
                }
                tracking->savedAngle = angle;
            }
            if (((mask & 0x20) && !(camera->invertFlags & 0x10)) || (up && (camera->invertFlags & 0x10))) {
                int angle = (u16)(tracking->savedAngle + 0x1fff);

                if (angle % 0x1fff != 0) {
                    angle += angle % 0x1fff;
                }
                tracking->savedAngle = angle;
            }
            ratio = FX_Div_01ff9c84(Camera_ComputeFollowDistance_020c1a70(camera->mode), Camera_ComputeFollowDistance_020c1a70(0));
            climb = FX_Div_01ff9c84(tracking->savedHeight, 0xa000);
            if (climb < 0) {
                climb = -climb;
            }
            down = mask & 1;
            if ((down && !(camera->invertFlags & 8)) || ((mask & 2) && (camera->invertFlags & 8))) {
                fx32 limit = FixedPointMultiply12(Camera_ComputeFollowDistance_020c1a70(camera->mode), 0xd9a);

                if (tracking->savedHeight < limit) {
                    tracking->savedHeight = tracking->savedHeight + (tracking->heightStep + climb);
                    if (tracking->savedHeight > limit) {
                        tracking->savedHeight = limit;
                    }
                }
            }
            if (((mask & 2) && !(camera->invertFlags & 8)) || (down && (camera->invertFlags & 8))) {
                if (FixedPointMultiply12(-0x2000, ratio) < tracking->savedHeight) {
                    tracking->savedHeight = tracking->savedHeight - (tracking->heightStep + climb);
                }
            }
            if (camera->flags & 0x1000000) {
                tracking->savedUnk18 = 0x1829;
            } else {
                tracking->savedUnk18 = Camera_GetModeDistance_020c19f0(camera->mode);
            }
            if (mask == 0) {
                Camera_UpdateManualTurn_020c4668();
            }
        }
        if (((SaveFlags *)(data_0205fe0c + 0x2878))->freeHeading == 0) {
            heading = ((s64)GetBiasAdjustedField_0206dc80(0) + 0x1000) / 0x2000 * 0x2000;
        } else {
            heading = GetBiasAdjustedField_0206dc80(0);
        }
        diff = (s16)(heading - tracking->angle);
        if (camera->flags & 8) {
            if (!(camera->flags & 0x20008000) && diff != 0) {
                *next = Camera_TurnToLeaderHeading_020c4e3c;
                tracking->heading = heading;
                tracking->turnTimer = 0;
                tracking->turnSpeed = FX_Div_01ff9c84((s64)(s16)(tracking->heading - tracking->angle) * 0x6488 / 0x10000, 0x3000);
                if (AbsFx(tracking->turnSpeed) < 2) {
                    if ((s16)(tracking->heading - tracking->angle) > 0) {
                        tracking->turnSpeed = 2;
                    } else {
                        tracking->turnSpeed = -2;
                    }
                }
                tracking->trackFlags.turning = 0;
                if (AbsFx(diff) < 0x4ffe) {
                    camera->flags &= ~8;
                }
            } else {
                camera->flags &= ~8;
            }
        }
        follow = FALSE;
        if (IsHeldEntryFlag2Active_0206e33c() || (camera->flags & 0x2000) || (camera->flags & 0x20008000)) {
            follow = FALSE;
        } else if (func_ov001_0206c2c8()) {
            follow = TRUE;
        } else if (tracking->state == 4) {
            follow = TRUE;
            camera->flags |= 0x100;
            camera->flags |= 0x80000000;
        }
        if (func_ov046_020c2ab8(camera)) {
            follow = FALSE;
        }
        if (follow) {
            *next = Camera_FollowLeaderTarget_020c491c;
            camera->flags |= 0x20;
            camera->flags |= 0x40;
            tracking->trackFlags.turning = 0;
        }
        if (camera->flags & 0x400) {
            camera->mode = camera->prevMode;
            tracking->turnTimer = 0;
            *next = Camera_StartFollowTracking_020c5008;
            camera->flags &= ~0x400;
            tracking->trackFlags.turning = 0;
        }
    }
    return NULL;
}
