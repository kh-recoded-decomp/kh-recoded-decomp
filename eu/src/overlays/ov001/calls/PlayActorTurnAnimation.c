#pragma opt_common_subs off

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorTurnAnimation {
    s32 animationId;
    s32 blendIndex;
} ActorTurnAnimation;

typedef struct ActorTurnSettings {
    fx32 speed;
    u32 reserved04;
    ActorTurnAnimation animations[4];
} ActorTurnSettings;

typedef struct ActorTurnModel {
    u32 flags;
    u16 animationFlags;
} ActorTurnModel;

typedef struct TurningActor {
    u8 reserved00[0x818];
    ActorTurnSettings turn;
    u8 reserved840[0xd18 - 0x840];
    ActorTurnModel **model;
    u8 reservedd1c[0xef8 - 0xd1c];
    u32 angle;
    u32 targetAngle;
} TurningActor;

typedef char ActorTurnAnimationSizeCheck[sizeof(ActorTurnAnimation) == 8 ? 1 : -1];
typedef char ActorTurnSettingsOffsetCheck[
    (u32)&((TurningActor *)0)->turn == 0x818 ? 1 : -1];
typedef char ActorTurnAngleOffsetCheck[
    (u32)&((TurningActor *)0)->angle == 0xef8 ? 1 : -1];
typedef char ActorTurnTargetAngleOffsetCheck[
    (u32)&((TurningActor *)0)->targetAngle == 0xefc ? 1 : -1];

extern void SetActorAnimSlot(TurningActor *actor, const char *name, int animationId,
                             int slot, u32 parameter);
extern void UpdateActorTurn(TurningActor *actor);
extern fx32 func_0202f4cc(u16 *state, int index);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern void StartActorAnimState(TurningActor *actor, const char *name, int blendIndex);

static inline const ActorTurnAnimation *GetTurnAnimation(const ActorTurnSettings *turn,
                                                        int byteOffset)
{
    return (const ActorTurnAnimation *)((const u8 *)&turn->animations[0] + byteOffset);
}

void PlayActorTurnAnimation(TurningActor *actor, u32 angle, const char *name,
                            const char *followAnimation)
{
    ActorTurnSettings *turn = &actor->turn;
    int difference = (u16)(angle - actor->angle);
    int frameCount = 0;
    int animationOffset;
    int slot;
    u32 previousAngle;

    if (difference < 0x1554 || difference > 0xea9c) {
        return;
    }
    actor->targetAngle = angle;
    if (difference < 0x7ff8) {
        if (turn->animations[2].animationId != -1 && difference > 0x1554 * 4) {
            slot = 2;
        } else {
            if (turn->animations[0].animationId == -1) {
                return;
            }
            slot = 0;
        }
    } else {
        if (turn->animations[3].animationId != -1 && difference < 0x1554 * 8) {
            slot = 3;
        } else {
            if (turn->animations[1].animationId == -1) {
                return;
            }
            slot = 1;
        }
    }
    animationOffset = slot * sizeof(ActorTurnAnimation);
    SetActorAnimSlot(actor, name, GetTurnAnimation(turn, animationOffset)->animationId, 0, 10);
    previousAngle = actor->angle;
    turn->speed = 0x1000;
    while (actor->targetAngle != actor->angle) {
        UpdateActorTurn(actor);
        frameCount++;
    }
    actor->angle = previousAngle;
    turn->speed = FX_Div(frameCount << 12, func_0202f4cc(&(*actor->model)->animationFlags, 0));
    if (followAnimation != NULL && GetTurnAnimation(turn, animationOffset)->blendIndex > 0) {
        StartActorAnimState(actor, followAnimation, GetTurnAnimation(turn, animationOffset)->blendIndex);
    }
}
