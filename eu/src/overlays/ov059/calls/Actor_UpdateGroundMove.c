#include "nitro/types.h"
#include "nitro/fx_types.h"

#pragma opt_propagation off

typedef struct Actor Actor;
typedef void (*ActorActionEndFunc)(Actor *actor, int result, int arg);
typedef s32 (*ActorChangeStateFunc)(Actor *actor, s32 state);
typedef void (*ActorResetFunc)(Actor *actor);

typedef struct JumpState {
    fx32 velX;
    fx32 velY;
    fx32 velZ;
    VecFx32 drift;
    fx32 speed;
    s16 heading;
    u8 pad_1e[0x24 - 0x1e];
    s8 phase;
} JumpState;

typedef struct GameSettings {
    u8 pad_0000[0x2878];
    u32 lowFlags : 11;
    u32 invertTilt : 1;
    u32 highFlags : 20;
} GameSettings;

typedef struct TiltConfig {
    u8 pad_00[0x3e];
    u16 threshold;
} TiltConfig;

struct Actor {
    u8 pad_0000[0x1f8];
    ActorActionEndFunc onActionEnd;
    u8 pad_01fc[0x234 - 0x1fc];
    u32 modelFlags;
    u8 pad_0238[0x930 - 0x238];
    u8 playerIndex;
    u8 prevTilt;
    u8 pad_0932[0x940 - 0x932];
    ActorResetFunc onReset;
    s32 mode;
    u8 pad_0948[0x958 - 0x948];
    fx32 timeScale;
    u8 pad_095c[0x970 - 0x95c];
    JumpState jump;
    u8 pad_0998[0x1808 - 0x998];
    ActorChangeStateFunc changeState;
};

extern const s16 data_02053580[];
extern const s16 data_02053780[];
extern const TiltConfig data_02053740;
extern GameSettings *data_0205fe0c;
extern const VecFx32 data_0205344c;

extern void *GetPlayerControlState(u32 playerIndex);
extern BOOL func_ov021_020a7524(void *input);
extern s32 Actor_SelectInputState(Actor *actor, JumpState *jump);
extern s32 func_ov059_020c98a0(Actor *actor);
extern u16 QuantizeSummedAngle(void *input);
extern u16 QuantizeFieldAngle(void *input);
extern VecFx32 *GetSubStruct1C(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov059_020ca35c(Actor *actor, BOOL tilted, int angle);

static inline int Sign(int value)
{
    if (value == 0) {
        return 0;
    }
    if (value > 0) {
        return 1;
    }
    return -1;
}

static inline fx32 StickScale(s16 cosine, BOOL airborne)
{
    int magnitude = cosine;
    s16 limit;
    if ((magnitude < 0 ? -magnitude : magnitude) < 0x10) {
        return 0;
    }
    if (airborne) {
        return cosine;
    }
    limit = data_02053780[1];
    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude > limit) {
        return Sign(cosine) << 12;
    }
    return 0;
}

void Actor_UpdateGroundMove(Actor *actor)
{
    void *input = GetPlayerControlState(actor->playerIndex);
    BOOL tilted = func_ov021_020a7524(input);
    s32 state;
    s8 phase = actor->jump.phase;
    BOOL airborne = phase != -1;
    int angle;
    int fieldAngle;
    BOOL landed;
    int index;
    fx32 scale;
    VecFx32 dir;
    VecFx32 move;
    VecFx32 scaled;
    VecFx32 *scaledPtr;

    landed = FALSE;
    if (phase == -1) {
        if (!(actor->modelFlags & 4)) {
            if (actor->mode != 0xc) {
                state = actor->changeState(actor, 3);
            } else {
                actor->jump.phase = 2;
            }
        } else {
            state = Actor_SelectInputState(actor, &actor->jump);
            switch (state) {
            case 2:
                landed = TRUE;
                break;
            case 5:
            case 6:
            case 7:
            case 9:
            case 0x11:
                actor->jump.drift = data_0205344c;
                actor->onReset(actor);
                return;
            }
        }
    } else {
        if (func_ov059_020c98a0(actor) && actor->mode != 0xc) {
            actor->jump.drift = data_0205344c;
            actor->onReset(actor);
            return;
        }
        state = 2;
        if ((u8)actor->jump.phase > 1) {
            state = 3;
        }
    }
    if (tilted) {
        angle = QuantizeSummedAngle(input);
        fieldAngle = QuantizeFieldAngle(input);
        dir = *GetSubStruct1C();
        {
            fx32 x = dir.x;
            dir.x = dir.z;
            dir.z = x;
            dir.z *= -1;
        }
        index = angle >> 4;
        scale = FX_Mul(StickScale(data_02053580[(0x400 - index) & 0xfff], airborne), actor->jump.speed);
        scaled = dir;
        scaledPtr = &scaled;
        ScaleVecFx32InPlace(scaledPtr, scale);
        move = *scaledPtr;
        if (airborne) {
            fx32 length;
            actor->jump.velX += FX_Mul(move.x, 0x333);
            actor->jump.velZ += FX_Mul(move.z, 0x333);
            length = FX_Sqrt((fx32)(((s64)actor->jump.velX * actor->jump.velX + (s64)actor->jump.velZ * actor->jump.velZ) >> 12));
            if (length > actor->jump.speed) {
                fx32 ratio = FX_Div(actor->jump.speed, length);
                actor->jump.velX = FX_Mul(actor->jump.velX, ratio);
                actor->jump.velZ = FX_Mul(actor->jump.velZ, ratio);
            }
        } else {
            actor->jump.velX = move.x;
            actor->jump.velZ = move.z;
        }
        if (!airborne) {
            if (!data_0205fe0c->invertTilt && data_02053580[index] > data_02053740.threshold
                && (!actor->prevTilt || data_02053580[fieldAngle >> 4] <= data_02053740.threshold)) {
                landed = TRUE;
            }
            if (!landed && actor->mode != 0xc && actor->onActionEnd != NULL) {
                actor->onActionEnd(actor, 1, -1);
            }
        } else if (state == 3 && actor->mode != 0xc && actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 3, -1);
        }
    } else if (!airborne && !landed) {
        JumpState *jump = &actor->jump;
        jump->velX = 0;
        jump->velZ = 0;
        jump->heading += (s16)actor->timeScale;
    }
    if (landed) {
        actor->changeState(actor, 2);
        airborne = TRUE;
    }
    if (airborne) {
        func_ov059_020ca35c(actor, tilted, angle);
    }
    actor->prevTilt = tilted;
}
