#include "nitro/types.h"
#include "nitro/fx_types.h"

#define UNSET 0x7fffffff

typedef struct {
    u8 pad_00[4];
    fx32 minX;
    u8 pad_08[0x20];
    int triggerCount;
} TriggerConfig;

typedef struct {
    u16 insideX : 1;
    u16 insideY : 1;
} TriggerBits;

typedef struct {
    u16 state;
    union {
        u16 raw;
        TriggerBits bits;
    } flags;
    fx32 triggerX;
    fx32 triggerY;
    int anchorKind;
    fx32 delay;
    fx32 timer;
    int orbitDegrees;
    fx32 orbitLength;
    fx32 orbitDuration;
    int orbitEase;
    fx32 zoomTarget;
    fx32 zoomDuration;
    int zoomEase;
    int cameraMode;
    fx32 heightTarget;
    fx32 heightDuration;
    int heightEase;
    u32 paramA;
    u32 paramB;
    u32 paramC;
} CameraTrigger;

typedef struct {
    u8 pad_00[0x30];
    TriggerConfig *config;
    CameraTrigger *triggers;
    VecFx32 playerPos;
    VecFx32 partnerPos;
    int activeIndex;
    VecFx32 cameraOffset;
    fx32 zoom;
    fx32 height;
} CameraTriggerCtx;

extern CameraTriggerCtx *data_ov030_020bd000;
extern u32 func_ov042_020bd6ec(void);
extern void func_ov001_0207b49c(u32 a, u32 b, u32 c);
extern u32 func_ov030_020bb368(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
typedef struct {
    u8 pad_00[0x14];
    VecFx32 pos;
} PartnerActor;

extern PartnerActor *func_ov021_020af5f4(void);
extern VecFx32 *func_ov042_020bd324(void);
extern fx32 func_ov042_020bd584(void);
extern VecFx32 *func_ov042_020bd290(void);
extern void func_ov042_020bd394(int degrees);
extern void MoveCameraAlongAxis_020bd334(fx32 distance);
extern void PushFromCameraTarget_020bd1c0(const VecFx32 *pos);
extern void func_ov042_020bd5e0(u32 value);
extern void SetCameraParameterC4(u32 value);
extern void SetCameraParameterC8(u32 value);
extern void func_ov042_020bd7a8(u32 firstValue, int secondValue);
extern void func_ov042_020bd59c(int extent);
extern void SetCameraMode_020bd660(u32 mode);
extern void GetOrbitOffsetDegrees_020bd474(VecFx32 *out, int degrees);
extern void OffsetCameraColliders_020bd2a0(const VecFx32 *delta);
extern fx32 EaseProgress_0204a174(fx32 elapsed, fx32 duration, int mode);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void LerpVecFx32Q27InPlace_0204be6c(VecFx32 *current, const VecFx32 *target, s32 t);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *input, VecFx32 *output);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z) {
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

static inline VecFx32 NormalizeVec(const VecFx32 *v) {
    VecFx32 out;
    VEC_NormalizeUnchecked_01ff9f88(v, &out);
    return out;
}

static inline VecFx32 ScaleVec(VecFx32 v, fx32 scale) {
    ScaleVecFx32InPlace_0204a5e4(&v, scale);
    return v;
}

static inline VecFx32 LerpVec(const VecFx32 *from, const VecFx32 *to, s32 t) {
    VecFx32 out = *from;
    LerpVecFx32Q27InPlace_0204be6c(&out, to, t);
    return out;
}

static inline fx32 MulFx(fx32 a, fx32 b) {
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

void UpdateCameraTriggers_020baccc(void)
{
    int j;
    CameraTriggerCtx *ctx;
    int count;
    int i;
    fx32 maxX;
    fx32 value;
    CameraTrigger *trigger;
    BOOL activate;
    VecFx32 *cam;
    VecFx32 dir;
    VecFx32 heightPos;
    VecFx32 blendPos;
    VecFx32 *anchorB;
    VecFx32 *anchorA;
    fx32 progress;
    fx32 length;
    BOOL finished;

    ctx = data_ov030_020bd000;
    count = ctx->config->triggerCount;
    for (i = 0; i < count && ctx->triggers[i].triggerX != UNSET; i++) {
    }
    if ((func_ov042_020bd6ec() & 1) && i <= 1) {
        func_ov001_0207b49c(0, 0x1000, 0x1000);
    } else {
        maxX = 0x80000000;
        for (i = 0; i < count; i++) {
            value = data_ov030_020bd000->triggers[i].triggerX;
            if (maxX < value && value != UNSET) {
                maxX = value;
            }
        }
        ctx = data_ov030_020bd000;
        value = ctx->partnerPos.x;
        func_ov001_0207b49c(ctx->config->minX, maxX,
                            value > maxX ? maxX : value < ctx->config->minX ? ctx->config->minX : value);
    }
    if (func_ov030_020bb368() == 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        trigger = &data_ov030_020bd000->triggers[i];
        if (trigger->state == 3) {
            continue;
        }
        activate = FALSE;
        if (trigger->state != 2) {
            if (trigger->state == 1) {
                trigger->timer += 0x1000;
                if (trigger->timer >= trigger->delay) {
                    activate = TRUE;
                }
            } else {
                if (trigger->triggerX == UNSET && trigger->triggerY == UNSET) {
                    trigger->flags.raw = 3;
                } else {
                    switch (trigger->anchorKind) {
                    case 0:
                        anchorB = func_ov001_0206dc4c(0);
                        anchorA = &data_ov030_020bd000->playerPos;
                        break;
                    case 1:
                        anchorB = &func_ov021_020af5f4()->pos;
                        anchorA = &data_ov030_020bd000->partnerPos;
                        break;
                    }
                    if (trigger->triggerX == UNSET) {
                        trigger->flags.bits.insideX = 1;
                    } else if ((trigger->triggerX < anchorA->x) != (trigger->triggerX <= anchorB->x)) {
                        trigger->flags.bits.insideX = !trigger->flags.bits.insideX;
                    }
                    if (trigger->triggerY == UNSET) {
                        trigger->flags.raw |= 2;
                    } else if ((trigger->triggerY < anchorA->y) != (trigger->triggerY <= anchorB->y)) {
                        trigger->flags.bits.insideY = !trigger->flags.bits.insideY;
                    }
                }
                if (trigger->flags.raw == 3) {
                    activate = TRUE;
                }
                if (activate && trigger->delay != UNSET) {
                    trigger->state = 1;
                    activate = FALSE;
                    trigger->timer = 0;
                }
            }
            if (activate) {
                ctx = data_ov030_020bd000;
                if (ctx->activeIndex != -1) {
                    for (j = 0; j < count; j++) {
                        if (j != i && ctx->triggers[j].state == 2) {
                            ctx->triggers[j].state = 3;
                            break;
                        }
                    }
                }
                trigger->state = 2;
                data_ov030_020bd000->activeIndex = i;
                trigger->timer = 0;
                data_ov030_020bd000->cameraOffset = *func_ov042_020bd324();
                data_ov030_020bd000->zoom = func_ov042_020bd584();
                data_ov030_020bd000->height = func_ov042_020bd290()->y;
                if ((trigger->orbitDegrees != UNSET || trigger->orbitLength != UNSET) &&
                    trigger->orbitDuration == UNSET) {
                    func_ov042_020bd394(trigger->orbitDegrees);
                    MoveCameraAlongAxis_020bd334(trigger->orbitLength);
                    trigger->orbitDegrees = UNSET;
                    trigger->orbitLength = UNSET;
                }
                if (trigger->zoomTarget != UNSET && trigger->zoomDuration == UNSET) {
                    func_ov042_020bd394(trigger->zoomTarget);
                    trigger->zoomTarget = UNSET;
                }
                if (trigger->heightTarget != UNSET && trigger->heightDuration == UNSET) {
                    cam = func_ov042_020bd290();
                    heightPos = MakeVec(cam->x, trigger->heightTarget, cam->z);
                    PushFromCameraTarget_020bd1c0(&heightPos);
                    trigger->heightTarget = UNSET;
                }
                if (trigger->paramA != UNSET) {
                    func_ov042_020bd5e0(trigger->paramA);
                }
                if (trigger->paramB != UNSET) {
                    SetCameraParameterC4(trigger->paramB);
                }
                if (trigger->paramC != UNSET) {
                    SetCameraParameterC8(trigger->paramC);
                }
                if (trigger->paramB == UNSET && trigger->paramC == UNSET) {
                    func_ov042_020bd7a8(0x80000000, UNSET);
                }
            }
        }
        if (trigger->state == 2) {
            finished = TRUE;
            trigger->timer += 0x1000;
            if ((trigger->orbitDegrees != UNSET || trigger->orbitLength != UNSET) &&
                trigger->orbitDuration != UNSET) {
                progress = EaseProgress_0204a174(trigger->timer, trigger->orbitDuration, trigger->orbitEase);
                if (trigger->orbitDegrees != UNSET) {
                    GetOrbitOffsetDegrees_020bd474(&dir, trigger->orbitDegrees);
                    if (trigger->orbitLength != UNSET) {
                        ScaleVecFx32InPlace_0204a5e4(&dir, trigger->orbitLength);
                    } else {
                        ScaleVecFx32InPlace_0204a5e4(&dir, VEC_Mag_01ff9f28(&data_ov030_020bd000->cameraOffset));
                    }
                } else {
                    length = trigger->orbitLength;
                    dir = ScaleVec(NormalizeVec(&data_ov030_020bd000->cameraOffset), length);
                }
                dir = LerpVec(&data_ov030_020bd000->cameraOffset, &dir, progress << 15);
                OffsetCameraColliders_020bd2a0(&dir);
                if (trigger->timer < trigger->orbitDuration) {
                    finished = FALSE;
                } else {
                    trigger->orbitDegrees = UNSET;
                    trigger->orbitLength = UNSET;
                    trigger->orbitDuration = UNSET;
                }
            }
            if (trigger->zoomTarget != UNSET && trigger->zoomDuration != UNSET) {
                progress = EaseProgress_0204a174(trigger->timer, trigger->zoomDuration, trigger->zoomEase);
                func_ov042_020bd59c(MulFx(data_ov030_020bd000->zoom, 0x1000 - progress) +
                                    MulFx(trigger->zoomTarget, progress));
                if (trigger->timer < trigger->zoomDuration) {
                    finished = FALSE;
                } else {
                    trigger->zoomTarget = UNSET;
                    trigger->zoomDuration = UNSET;
                }
            }
            if (trigger->heightTarget != UNSET && trigger->heightDuration != UNSET) {
                progress = EaseProgress_0204a174(trigger->timer, trigger->heightDuration, trigger->heightEase);
                value = MulFx(data_ov030_020bd000->height, 0x1000 - progress) +
                        MulFx(trigger->heightTarget, progress);
                cam = func_ov042_020bd290();
                blendPos = MakeVec(cam->x, value, cam->z);
                PushFromCameraTarget_020bd1c0(&blendPos);
                if (trigger->timer < trigger->heightDuration) {
                    finished = FALSE;
                } else {
                    trigger->heightTarget = UNSET;
                    trigger->heightDuration = UNSET;
                }
            }
            if (finished) {
                trigger->state = 3;
                data_ov030_020bd000->activeIndex = -1;
                if (trigger->cameraMode != -1) {
                    SetCameraMode_020bd660(trigger->cameraMode);
                }
            }
        }
    }
    data_ov030_020bd000->playerPos = *func_ov001_0206dc4c(0);
    data_ov030_020bd000->partnerPos = func_ov021_020af5f4()->pos;
}
