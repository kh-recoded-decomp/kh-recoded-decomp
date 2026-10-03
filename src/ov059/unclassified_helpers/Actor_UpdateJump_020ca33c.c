#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorActionEndFunc)(Actor *actor, int result, int arg);
typedef void (*ActorScaleFunc)(Actor *actor, fx32 scale);
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

typedef struct JumpState {
    VecFx32 velocity;
    u8 pad_0c[0x20 - 0xc];
    fx32 airTime;
    s8 phase;
} JumpState;

typedef struct GameSettings {
    u8 pad_0000[0x2878];
    u32 lowFlags : 11;
    u32 invertTilt : 1;
    u32 highFlags : 20;
} GameSettings;

struct Actor {
    u8 pad_0000[0x1f8];
    ActorActionEndFunc onActionEnd;
    ActorScaleFunc onLand;
    u8 pad_0200[0x234 - 0x200];
    u32 modelFlags;
    u8 pad_0238[0x75c - 0x238];
    s32 action;
    u8 pad_0760[0x768 - 0x760];
    s32 actionDone;
    u8 pad_076c[0x930 - 0x76c];
    u8 playerIndex;
    u8 pad_0931[3];
    s32 hitState : 8;
    s32 hitFlags : 24;
    u8 pad_0938[0x944 - 0x938];
    s32 mode;
    u8 pad_0948[0x958 - 0x948];
    fx32 timeScale;
    u8 pad_095c[0x970 - 0x95c];
    JumpState jump;
    u8 pad_0998[0x1808 - 0x998];
    ActorChangeStateFunc changeState;
};

extern const s16 data_0205356c[];
extern GameSettings *data_0205fe0c;

extern BOOL func_ov059_020ca2fc(Actor *actor, JumpState *jump);
extern void *func_ov001_0206db78(u32 playerIndex);
extern BOOL HasFlagsAt0xe_020a752c(void *input, u16 mask);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL IsPlayerEntryFlagSet_02050014(u8 playerIndex, int flag);

void Actor_UpdateJump_020ca33c(Actor *actor, BOOL tilted, int angle)
{
    JumpState *jump = &actor->jump;
    VecFx32 direction;
    VecFx32 drag;
    VecFx32 normal;
    VecFx32 scaled;
    VecFx32 result;
    fx32 gravity;
    fx32 launch;

    if (func_ov059_020ca2fc(actor, jump)) {
        return;
    }
    gravity = 0x7b;
    if (actor->mode == 8) {
        gravity = 0x52;
    } else {
        if (actor->mode == 2 || actor->mode == 3 || actor->mode == 12) {
            if (tilted) {
                fx32 sine = data_0205356c[angle >> 4];
                fx32 limit = data_0205356c[0xff];

                if (jump->phase == 2 && sine > limit) {
                    gravity = 0x14;
                } else if (sine < -limit) {
                    gravity = 0x19a;
                }
            }
            if (gravity == 0x7b && jump->phase == 2 &&
                HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->playerIndex), 2)) {
                gravity = 0x14;
            }
        }
        if (jump->phase == 1 && gravity == 0x7b &&
            !HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->playerIndex), 2)) {
            if (!data_0205fe0c->invertTilt) {
                if (tilted) {
                    if (data_0205356c[angle >> 4] <= data_0205356c[0xff]) {
                        gravity = 0x19a;
                    }
                } else {
                    gravity = 0x19a;
                }
            } else {
                gravity = 0x19a;
            }
        }
    }
    jump->velocity.y -= gravity;
    if (jump->velocity.y < -0x666) {
        jump->velocity.y = -0x666;
    }
    gravity = func_01ffaff4(&jump->velocity, &normal);
    *(VecFx32 *)&direction = *(VecFx32 *)&normal;
    gravity = FixedPointMultiply12(gravity, 0x52);
    *(VecFx32 *)&scaled = *(VecFx32 *)&direction;
    ScaleVecFx32InPlace_0204a5e4(&scaled, gravity);
    *(VecFx32 *)&drag = *(VecFx32 *)&scaled;
    VEC_Subtract_01ff9e3c(&jump->velocity, &drag, &result);
    jump->velocity = result;
    switch (jump->phase) {
    case 0:
        launch = IsPlayerEntryFlagSet_02050014(actor->playerIndex, 12) ? 0x96d : 0x726;
        jump->phase = 1;
        actor->jump.velocity.y = launch;
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 2, -1);
        }
        if (actor->hitState == 4) {
            actor->hitState = 0;
        }
        break;
    case 1:
        if (actor->action == 2 && actor->actionDone && actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 3, -1);
        }
        if (actor->jump.velocity.y < 0) {
            jump->phase = 2;
            if (actor->action == 2 && actor->onActionEnd != NULL) {
                actor->onActionEnd(actor, 3, -1);
            }
        }
        break;
    case 2:
        if (actor->mode != 12) {
            if (jump->phase == 2) {
                jump->airTime += actor->timeScale;
            }
            if (actor->actionDone && actor->action == 3 && actor->onLand != NULL) {
                actor->onLand(actor, 0x10000);
            }
        }
        if (actor->modelFlags & 4) {
            if (actor->mode != 12) {
                actor->changeState(actor, 4);
            } else {
                jump->phase = 3;
                jump->velocity.y = 0;
            }
        }
        break;
    case 3:
        actor->modelFlags |= 0x40;
        if (actor->mode != 12) {
            actor->changeState(actor, 1);
        } else {
            jump->phase = -1;
        }
        break;
    }
}
