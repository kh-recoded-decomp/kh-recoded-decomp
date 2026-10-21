#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorFunc)(Actor *actor);
typedef void (*ActorNotifyFunc)(Actor *actor, int arg1, int arg2, int arg3);
typedef void (*ActorActionEndFunc)(Actor *actor, int result, int arg);
typedef void (*ActorScaleFunc)(Actor *actor, fx32 scale);
typedef void (*ActorToggleFunc)(Actor *actor, int enabled);
typedef void (*ActorTurnFunc)(Actor *actor, u16 angle);
typedef BOOL (*ActorTargetFunc)(Actor *actor, VecFx32 *target);
typedef s32 (*ActorStanceFunc)(Actor *actor);

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[2];
    s16 angle;
    fx32 scale;
    u8 pad_18[0xc];
    u8 flag24;
    u8 flag25;
    u16 flag26;
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct ArcVec {
    fx32 x;
    fx32 y;
} ArcVec;

typedef struct TiltConfig {
    u8 pad_00[0x3e];
    s16 threshold;
} TiltConfig;

typedef struct StateMachine {
    ActorFunc update;
    s32 mode;
    s32 timer;
} StateMachine;

struct Actor {
    u8 pad_0000[0x1dc];
    s32 stance;
    u8 pad_01e0[0x1f0 - 0x1e0];
    ActorNotifyFunc onNotify;
    u8 pad_01f4[4];
    ActorActionEndFunc onActionEnd;
    ActorScaleFunc onLand;
    ActorToggleFunc onStop;
    u8 pad_0204[0x210 - 0x204];
    ActorTurnFunc onTurn;
    u8 pad_0214[0x228 - 0x214];
    ActorTargetFunc getTarget;
    ActorStanceFunc getStance;
    u8 pad_0230[0x234 - 0x230];
    u32 modelFlags;
    u8 pad_0238[0x25c - 0x238];
    s32 groundHeight;
    u8 pad_0260[0x75c - 0x260];
    s32 action;
    u8 pad_0760[0x928 - 0x760];
    u64 stateFlags;
    u8 playerIndex;
    u8 pad_0931[0x940 - 0x931];
    StateMachine sm;
    VecFx32 guardPoint;
    u8 pad_0958[0x962 - 0x958];
    u16 heading;
    u8 pad_0964[0x970 - 0x964];
    VecFx32 velocity;
    VecFx32 drift;
    u8 pad_0988[0x170c - 0x988];
    s32 commandTypes[1];
    u8 commandCount;
    s8 commandIndex;
    u8 pad_1712[0x1724 - 0x1712];
    s32 finisherKind;
    u8 pad_1728[0x1800 - 0x1728];
    s32 actionTimer;
    u8 pad_1804[0x1820 - 0x1804];
    s32 haltEffectSlot;
};

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];
extern const TiltConfig data_02053b2c;

extern void *func_ov001_0206db78(u32 playerIndex);
extern int func_ov001_0206db8c(int index);
extern s32 GetFieldAt0x12_020a7560(void *input);
extern void func_ov021_020a8ab4(TrackState *state);
extern s32 func_ov021_020a8ca0(TrackState *state, int group);
extern u32 func_ov031_020bc040(void);
extern u32 GetField28_020bbff4(void);
extern u32 GetPlayerEntryCount_02050050(int player, u32 id);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern int FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Actor_SetTimeScale_020c7d88(Actor *actor, fx32 scale);
extern void Actor_SetPaused_020c7e5c(Actor *actor, int paused);
extern void Actor_ExtendCountdown_020c89fc(Actor *actor, fx32 duration);
extern void Actor_PlayHitReaction_020c9144(Actor *actor);
extern void func_ov059_020c9374(VecFx32 *target, Actor *actor, s32 oldMode, s32 state);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern u16 GetLinkedAngleOffset_020cd0e4(Actor *actor);

extern void Actor_UpdateGroundMove_020c93d8(Actor *actor);
extern void func_ov059_020c9728(Actor *actor);
extern void Actor_UpdateHaltedState_020ca5f0(Actor *actor);
extern void Actor_UpdateTimedHaltedState_020ca66c(Actor *actor);
extern void func_ov059_020ca754(Actor *actor);
extern void Actor_UpdateFinisher_020ca794(Actor *actor);
extern void func_ov059_020cad40(Actor *actor);
extern void func_ov059_020cb3f8(Actor *actor);
extern void func_ov059_020cb4f0(Actor *actor);
extern void func_ov059_020cb5a8(Actor *actor);
extern void func_ov059_020cb680(Actor *actor);
extern void Actor_UpdateDrift_020cb754(Actor *actor);

static inline s32 Actor_GetStance(Actor *actor)
{
    if (actor->getStance != NULL) {
        return actor->getStance(actor);
    }
    return actor->stance;
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline BOOL IsZeroVec(const VecFx32 *vec)
{
    return vec->x == 0 && vec->y == 0 && vec->z == 0;
}

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

s32 Actor_ChangeState_020cbff8(Actor *actor, s32 state)
{
    TrackState haltTrack;
    VecFx32 chargeTarget;
    VecFx32 chargeOffset;
    VecFx32 lockTarget;
    VecFx32 lockOffset;
    TrackState breakTrack;
    ArcVec launchDir;
    ArcVec arcVec;
    void *input = func_ov001_0206db78(actor->playerIndex);
    StateMachine *sm = &actor->sm;
    BOOL blocked = FALSE;
    s32 result = state;

    if (state == 2 && Actor_GetStance(actor) == 6) {
        blocked = TRUE;
    }
    if (blocked) {
        return sm->mode;
    }
    switch (sm->mode) {
    case 5:
        actor->stateFlags &= ~(u64)2;
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, 0);
        }
        Actor_SetTimeScale_020c7d88(actor, 0x1000);
        break;
    case 8:
        actor->guardPoint.z = 0;
        actor->guardPoint.y = 0;
        actor->guardPoint.x = 0;
        break;
    case 7:
    case 0x11:
        actor->stateFlags &= ~(u64)0x4000;
        actor->stateFlags &= ~(u64)0x2000;
        break;
    case 0xc:
        sm->mode = 0;
        actor->stateFlags &= ~(u64)0x2000;
        break;
    case 0x12:
        Actor_SetPaused_020c7e5c(actor, 0);
        break;
    }
    switch (state) {
    case 1:
        sm->update = Actor_UpdateGroundMove_020c93d8;
        actor->stateFlags &= ~(u64)0x100;
        if (!(actor->modelFlags & 4)) {
            state = 3;
            goto fall;
        }
        if (func_ov031_020bc040() - GetField28_020bbff4() == 0 && actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 1, -1);
        }
        break;
    case 2:
        result = 2;
        sm->update = Actor_UpdateGroundMove_020c93d8;
        actor->stateFlags &= ~(u64)0x1000;
        if (state != 2) {
            actor->stateFlags |= 0x1000;
        }
        break;
    case 3:
    fall:
        result = 2;
        sm->update = Actor_UpdateGroundMove_020c93d8;
        if (actor->action != 3) {
            if (actor->onActionEnd != NULL) {
                actor->onActionEnd(actor, 3, -1);
            }
            if (actor->onLand != NULL) {
                actor->onLand(actor, 0xf000);
            }
        }
        break;
    case 4:
        result = 2;
        sm->update = Actor_UpdateGroundMove_020c93d8;
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 1, -1);
        }
        actor->stateFlags &= ~(u64)0x100;
        break;
    case 5: {
        fx32 countdown;

        sm->update = func_ov059_020c9728;
        countdown = 0x6000;
        if (GetPlayerEntryCount_02050050(actor->playerIndex, 10) > 1) {
            countdown = 0xa000;
        }
        Actor_ExtendCountdown_020c89fc(actor, countdown);
        if (data_0205356c[actor->heading >> 4] < data_02053b2c.threshold) {
            fx32 dist = GetField28_020bbff4();
            fx32 rest = 0x5c2 - FxMul(dist, dist);
            fx32 horiz;
            int angle;

            if (rest < 0) {
                rest = 0;
            }
            horiz = FX_Sqrt_01ff9cfc(rest);
            arcVec.y = FX_Sqrt_01ff9cfc(0x5c2 - FxMul(horiz, horiz));
            arcVec.x = horiz;
            launchDir = arcVec;
            angle = FixedPointAtan2_020062bc(launchDir.y, launchDir.x * Sign(data_0205356c[(0x400 - (actor->heading >> 4)) & 0xfff]));
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, angle - 0x3fff);
            }
        }
        Actor_SetTimeScale_020c7d88(actor, 0x1800);
        actor->stateFlags &= ~(u64)2;
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 0xd, -1);
        }
        break;
    }
    case 6: {
        u16 angle;

        actor->stateFlags |= 0x40;
        actor->stateFlags &= ~(u64)0x100;
        if (IsZeroVec(&actor->guardPoint)) {
            angle = GetLinkedAngleOffset_020cd0e4(actor);
        } else {
            angle = FixedPointAtan2_020062bc(actor->guardPoint.x, actor->guardPoint.z);
        }
        if (!(actor->stateFlags & 8)) {
            sm->update = Actor_UpdateHaltedState_020ca5f0;
            if (actor->onActionEnd != NULL) {
                actor->onActionEnd(actor, 0xe, -1);
            }
        } else {
            sm->update = Actor_UpdateTimedHaltedState_020ca66c;
            if (actor->action != 0xf) {
                if (actor->onActionEnd != NULL) {
                    actor->onActionEnd(actor, 0xf, -1);
                }
            } else if (actor->onLand != NULL) {
                actor->onLand(actor, 0);
            }
            if (actor->haltEffectSlot < 0) {
                func_ov021_020a8ab4(&haltTrack);
                haltTrack.id = actor->playerIndex;
                haltTrack.flag25 = 0;
                haltTrack.flag24 = 0;
                haltTrack.position = *Actor_GetModelPosition_020cd0d8(actor);
                haltTrack.position.y += 0xf00;
                haltTrack.angle = angle + 0x8000;
                haltTrack.prevIndex = 0;
                if (actor->stateFlags & 4) {
                    haltTrack.index = 0x1b;
                } else {
                    haltTrack.index = 0x1a;
                }
                actor->haltEffectSlot = func_ov021_020a8ca0(&haltTrack, func_ov001_0206db8c(0));
            }
        }
        actor->stateFlags &= ~(u64)0x40000c;
        break;
    }
    case 8:
        actor->stateFlags |= 0x40;
        actor->stateFlags &= ~(u64)0x40000c;
        actor->stateFlags &= ~(u64)0x100;
        actor->velocity = data_02053438;
        if (actor->modelFlags & 4) {
            if (actor->guardPoint.y <= 0 && actor->groundHeight == (s32)0x80000000) {
                sm->update = func_ov059_020cb4f0;
            } else {
                sm->update = func_ov059_020cb5a8;
            }
        } else {
            if (actor->guardPoint.y <= 0x400) {
                actor->guardPoint.y = 0x400;
            }
            actor->velocity.y = 0;
            sm->update = func_ov059_020cb5a8;
        }
        Actor_PlayHitReaction_020c9144(actor);
        break;
    case 0xd:
        actor->stateFlags |= 0x800;
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 9, -1);
        }
        if (actor->onStop != NULL) {
            actor->onStop(actor, 0);
        }
        actor->velocity.z = 0;
        actor->velocity.y = 0;
        actor->velocity.x = 0;
        actor->drift.z = 0;
        actor->drift.y = 0;
        actor->drift.x = 0;
        actor->guardPoint.z = 0;
        actor->guardPoint.y = 0;
        actor->guardPoint.x = 0;
        actor->velocity.y = 0;
        Actor_SetTimeScale_020c7d88(actor, 0xa0);
        if (actor->onNotify != NULL) {
            actor->onNotify(actor, 0, 0x12, 0);
        }
        sm->update = func_ov059_020cb680;
        break;
    case 7:
        actor->actionTimer = 0xdd;
        actor->finisherKind = actor->commandTypes[actor->commandIndex];
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 10, -1);
        }
        sm->update = Actor_UpdateFinisher_020ca794;
        break;
    case 0x11: {
        BOOL found;

        actor->actionTimer = GetFieldAt0x12_020a7560(input);
        actor->stateFlags |= 0x40;
        found = FALSE;
        if (actor->getTarget != NULL) {
            found = actor->getTarget(actor, &chargeTarget);
        }
        if (found) {
            VEC_Subtract_01ff9e3c(&chargeTarget, Actor_GetModelPosition_020cd0d8(actor), &chargeOffset);
        }
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 0xc, -1);
        }
        sm->update = func_ov059_020cad40;
        break;
    }
    case 0xc: {
        BOOL found;

        actor->actionTimer = GetFieldAt0x12_020a7560(input);
        actor->stateFlags |= 0x40;
        found = FALSE;
        if (actor->getTarget != NULL) {
            found = actor->getTarget(actor, &lockTarget);
        }
        if (found) {
            VEC_Subtract_01ff9e3c(&lockTarget, Actor_GetModelPosition_020cd0d8(actor), &lockOffset);
        }
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, 0xb, -1);
        }
        sm->update = func_ov059_020cb3f8;
        break;
    }
    case 0x12:
        Actor_SetPaused_020c7e5c(actor, 1);
        actor->stateFlags &= ~(u64)0x10;
        sm->update = Actor_UpdateDrift_020cb754;
        break;
    case 0xe: {
        int action;

        actor->stateFlags &= ~(u64)0x100;
        action = 0x10;
        switch (actor->action) {
        case 7:
        case 8:
            action = 0x11;
            break;
        }
        if (actor->onActionEnd != NULL) {
            actor->onActionEnd(actor, action, -1);
        }
        func_ov021_020a8ab4(&breakTrack);
        breakTrack.id = actor->playerIndex;
        breakTrack.flag25 = 1;
        breakTrack.flag26 = 1;
        breakTrack.flag24 = 0;
        breakTrack.angle = GetLinkedAngleOffset_020cd0e4(actor) + 0x8000;
        func_ov021_020a8ca0(&breakTrack, func_ov001_0206db8c(3));
        Actor_ExtendCountdown_020c89fc(actor, 0x6000);
        actor->velocity.z = 0;
        actor->velocity.y = 0;
        actor->velocity.x = 0;
        actor->drift.z = 0;
        actor->drift.y = 0;
        actor->drift.x = 0;
        actor->guardPoint.z = 0;
        actor->guardPoint.y = 0;
        actor->guardPoint.x = 0;
        actor->velocity.y = 0x266;
        sm->update = func_ov059_020ca754;
        break;
    }
    }
    func_ov059_020c9374(&actor->velocity, actor, sm->mode, state);
    sm->mode = result;
    sm->timer = 0;
    return result;
}
