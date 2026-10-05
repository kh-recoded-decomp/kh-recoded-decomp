#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*StateHandler)(Actor *actor);
typedef void (*ModeFunc)(Actor *actor, int mode, int arg);
typedef void (*NotifyFunc)(Actor *actor, int arg);
typedef void (*TurnFunc)(Actor *actor, int angle);
typedef void (*MotionFunc)(Actor *actor, int a, int b, int c);
typedef BOOL (*FootFunc)(Actor *actor, VecFx32 *out);
typedef int (*StateGetter)(Actor *actor);

typedef struct {
    StateHandler handler;
    int state;
    int aux;
} StateCtl;

typedef struct {
    u16 flags;
    u16 frames;
} AnimInfo;

typedef struct {
    u8 pad_00[0x7c];
    void *model;
} BodyModel;

typedef struct {
    u8 pad_0[2];
    u8 kind;
} HandleTarget;

typedef struct {
    int flags;
    u8 pad_04[0x5c];
    HandleTarget **target;
} ObjHandle;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[2];
    u16 angle;
    u8 pad_14[0x10];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 effectId;
} MarkerRequest;

typedef struct {
    VecFx32 position;
    u8 pad_0c[0xc4 - 0xc];
    int timer;
    u16 angle;
} DashState;

struct Actor {
    u8 pad_0000[0x1d4];
    AnimInfo *anim;
    u8 pad_01d8[4];
    int state;
    u8 pad_01e0[0x1f0 - 0x1e0];
    MotionFunc onMotion;
    u8 pad_01f4[4];
    ModeFunc onMode;
    NotifyFunc onNotify;
    NotifyFunc onScale;
    u8 pad_0204[0x210 - 0x204];
    TurnFunc onTurn;
    u8 pad_0214[0x228 - 0x214];
    FootFunc getFootPosition;
    StateGetter getState;
    BodyModel *body;
    u32 modelFlags;
    u8 pad_0238[0x25c - 0x238];
    int hitDirection;
    u8 pad_0260[0x75c - 0x260];
    int mode;
    u8 pad_0760[0x9ac - 0x760];
    u64 flags;
    u8 player;
    u8 pad_09b5[0x9bc - 0x9b5];
    StateCtl ctl;
    VecFx32 velocity;
    u8 pad_09d4[0x9e0 - 0x9d4];
    VecFx32 knockback;
    u8 pad_09ec[0x9f0 - 0x9ec];
    fx32 landScale;
    u8 pad_09f4[0xa10 - 0x9f4];
    u8 camera[0xa54 - 0xa10];
    DashState dash;
    u8 pad_0b20[0xfc8 - 0xb20];
    ObjHandle handle;
    u8 pad_102c[0x1030 - 0x102c];
    int menuTimer;
    s8 slotA;
    u8 pad_1035;
    s8 slotB;
    u8 pad_1037[0x1070 - 0x1037];
    u8 members[0x1104 - 0x1070];
    int marker;
};

extern s16 data_02053580[];
extern const VecFx32 data_0205344c;
extern void *func_ov001_0206db78(int player);
extern BOOL ExitActorState(Actor *actor, int nextState, BOOL force);
extern void ConfigureCameraMode(void *camera, Actor *actor, int previous, u32 kind);
extern void func_ov052_020ceb80(Actor *actor, VecFx32 *position);
extern BOOL func_ov021_020a7530(void *unit);
extern BOOL func_ov021_020a7524(void *unit);
extern int func_ov021_020a7564(void *unit);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern int GetPlayerEntryCount(int player, u32 id);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void ExtendIfGreater(Actor *actor, fx32 value);
extern void ApplyTimeScaledSpeed(Actor *actor, fx32 speed);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern void NNS_G3dMdlSetMdlCullModeAll(void *model, int cullMode);
extern void PlayDirectionalHitReaction(Actor *actor);
extern void AddSessionCounter(int index, int amount);
extern BOOL HasSlotAAndBit2Set(ObjHandle *handle);
extern BOOL IsFlag10Set(ObjHandle *handle);
extern int GetSubObjectValue(HandleTarget *target, BOOL mirrored, int arg);
extern int func_ov001_02063a38(void);
extern StateHandler SelectMenuMember(void *members, int index, int *result);
extern void DeactivateCurrentMember(void *members);
extern void SetManagerEnabled(u32 enabled);
extern BOOL SelectFallStateHandler(Actor *actor, int *state);
extern void SetActorPaused(Actor *actor, int paused);

extern void func_ov052_020ca938(Actor *actor);
extern void UpdateGlideState(Actor *actor);
extern void UpdateAnchoredMovement(Actor *actor);
extern void UpdateWallSlide(Actor *actor);
extern void ApplyRootMotion(Actor *actor);
extern void UpdateGlideLanding(Actor *actor);
extern void UpdateLandingRecovery(Actor *actor);
extern void UpdateEndOfAction(Actor *actor);
extern void FinishLockedAction(Actor *actor);
extern void AdvanceChargeState(Actor *actor);
extern void UpdateTargetSlotsAndMode(Actor *actor);
extern void ChooseHandleFollowupMode(Actor *actor);
extern void ResolvePendingModeChange(Actor *actor);
extern void CachePositionAndFlushScale(Actor *actor);
extern void SpawnSceneMarker(Actor *actor);
extern void UpdateRewardMenuClose(Actor *actor);
extern void ApplyPendingFlagReward(Actor *actor);
extern void func_ov052_020cb928(Actor *actor);
extern void UpdateGlideSteering(Actor *actor);
extern void UpdateAirDashMode(Actor *actor);
extern void ExtendFieldAndNotifyCallback(Actor *actor);
extern void func_ov030_020bc130(Actor *actor);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

static inline void TurnActor(Actor *actor, int angle)
{
    if (actor->onTurn != NULL) {
        actor->onTurn(actor, angle);
    }
}

static inline void ChangeMode(Actor *actor, int mode)
{
    if (actor->onMode != NULL) {
        actor->onMode(actor, mode, -1);
    }
}

static inline BOOL IsVecNonZero(const VecFx32 *v)
{
    return v->x != 0 || v->y != 0 || v->z != 0;
}

static inline void ResetMotion(Actor *actor)
{
    actor->velocity.x = actor->velocity.y = actor->velocity.z = 0;
    actor->knockback.x = actor->knockback.y = actor->knockback.z = 0;
}

int EnterActorState(Actor *actor, u32 nextState)
{
    VecFx32 footPos;
    VecFx32 diff;
    MarkerRequest request;
    VecFx32 push;
    int result;
    int fallState;
    int slot;
    u16 pushAngle;
    void *unit;
    ObjHandle *handle;
    int angle;
    StateCtl *ctl;
    BOOL idle;
    BOOL found;
    int value;
    StateHandler handler;

    unit = func_ov001_0206db78(actor->player);
    ctl = &actor->ctl;
    result = nextState;
    if (ExitActorState(actor, nextState, FALSE)) {
        return ctl->state;
    }
    ctl->aux = 0;
    switch (nextState) {
    case 1:
        ctl->handler = func_ov052_020ca938;
        actor->flags &= ~0x100ULL;
        actor->flags &= ~0x2000000ULL;
        actor->flags &= ~0x8008000ULL;
        break;
    case 2:
    case 13:
    case 18:
        result = 2;
        ctl->handler = UpdateGlideState;
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0xb, -1);
        }
        actor->flags &= ~0x1000ULL;
        break;
    case 3:
        result = 2;
        ctl->handler = UpdateGlideState;
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0xb, -1);
        }
        if (actor->onNotify != NULL) {
            actor->onNotify(actor, 0x1000);
        }
        break;
    case 4:
        result = 2;
        ctl->handler = UpdateGlideState;
        if (actor->mode != 0xc) {
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0xc, -1);
            }
            if (actor->onNotify != NULL) {
                actor->onNotify(actor, 0xf000);
            }
        }
        break;
    case 5:
        result = 2;
        ctl->handler = UpdateGlideState;
        if (actor->onMode != NULL) {
            actor->onMode(actor, 2, -1);
        }
        actor->flags &= ~0x100ULL;
        break;
    case 6:
    case 16: {
        DashState *dash = &actor->dash;
        if (nextState == 6) {
            ctl->handler = UpdateAnchoredMovement;
            if (actor->onMode != NULL) {
                actor->onMode(actor, 3, -1);
            }
        } else {
            ctl->handler = UpdateWallSlide;
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0x17, -1);
            }
            dash->timer = 0x9000;
            actor->flags &= ~0x40ULL;
            actor->velocity.x = data_0205344c.x;
            actor->velocity.y = data_0205344c.y;
            actor->velocity.z = data_0205344c.z;
            if (actor->onMotion != NULL) {
                actor->onMotion(actor, 0, 0x1c, 0);
            }
        }
        actor->flags |= 1;
        func_ov052_020ceb80(actor, &dash->position);
        TurnActor(actor, dash->angle);
        actor->flags &= ~0x100ULL;
        actor->flags &= ~0x8008000ULL;
        actor->velocity.y = 0;
        break;
    }
    case 7:
        result = 6;
        ctl->handler = ApplyRootMotion;
        actor->flags |= 1;
        if (actor->onMode != NULL) {
            actor->onMode(actor, 5, -1);
        }
        break;
    case 8: {
        fx32 extend;
        fx32 speed;
        ctl->handler = UpdateGlideLanding;
        if (func_ov021_020a7530(unit)) {
            angle = func_ov021_020a7564(unit);
        } else {
            angle = GetLinkedAngleOffset(actor);
        }
        extend = 0x6000;
        speed = 0x1000;
        if ((u32)GetPlayerEntryCount(actor->player, 0xa) > 1) {
            extend = 0xa000;
            speed = 0x1333;
        }
        ExtendIfGreater(actor, extend);
        ApplyTimeScaledSpeed(actor, speed);
        actor->flags &= ~0x40000cULL;
        actor->flags &= ~2ULL;
        actor->flags &= ~0x80ULL;
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, angle);
        }
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0xd, -1);
        }
        break;
    }
    case 9: {
        actor->flags |= 0x40;
        actor->flags &= ~0x100ULL;
        if (IsVecNonZero(&actor->knockback)) {
            pushAngle = FX_Atan2Idx(actor->knockback.x, actor->knockback.z);
        } else {
            pushAngle = GetLinkedAngleOffset(actor);
            if (actor->mode != 0x14) {
                if (actor->getFootPosition != NULL) {
                    found = actor->getFootPosition(actor, &footPos);
                } else {
                    found = FALSE;
                }
                if (found) {
                    VEC_Subtract(&footPos, func_ov052_020ceb74(actor), &diff);
                    pushAngle = FX_Atan2Idx(diff.x, diff.z) + 0x8000;
                }
            }
        }
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, pushAngle);
        }
        if (!(actor->flags & 8)) {
            ctl->handler = UpdateLandingRecovery;
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0x13, -1);
            }
        } else {
            ctl->handler = UpdateEndOfAction;
            if (actor->mode != 0x14) {
                if (actor->onMode != NULL) {
                    actor->onMode(actor, 0x14, -1);
                }
            } else if (actor->onNotify != NULL) {
                actor->onNotify(actor, 0);
            }
            if (actor->marker < 0) {
                ResetAnimationTrackState(&request);
                request.id = actor->player;
                request.layer = 0;
                request.hidden = 0;
                request.position = *func_ov052_020ceb74(actor);
                request.position.y += 0xf00;
                request.angle = pushAngle + 0x8000;
                request.soundId = 0;
                if (actor->flags & 4) {
                    request.effectId = 0x1b;
                } else {
                    request.effectId = 0x1a;
                }
                actor->marker = func_ov021_020a8cc0(&request, func_ov001_0206db8c(0));
            }
        }
        actor->flags &= ~0x40000cULL;
        actor->flags &= ~0x80ULL;
        break;
    }
    case 10: {
        idle = FALSE;
        if (actor->anim->frames == 0) {
            idle = TRUE;
        }
        actor->flags |= 0x40;
        actor->flags &= ~0x40000cULL;
        actor->flags &= ~0x80ULL;
        actor->flags &= ~0x100ULL;
        if (actor->flags & 0x200000) {
            NNS_G3dMdlSetMdlCullModeAll(actor->body->model, 3);
            actor->flags &= ~0x200000ULL;
        }
        actor->slotA = -1;
        actor->slotB = -1;
        if ((actor->modelFlags & 4) || idle) {
            if ((actor->knockback.y <= 0 && actor->hitDirection == (int)0x80000000) || idle) {
                ctl->handler = FinishLockedAction;
            } else {
                ctl->handler = AdvanceChargeState;
            }
        } else {
            if (GetActorState(actor) != 4) {
                if (actor->hitDirection >= 0 && actor->knockback.y <= 0x400) {
                    actor->knockback.y = 0x400;
                }
                actor->velocity.y = 0;
            }
            ctl->handler = AdvanceChargeState;
        }
        PlayDirectionalHitReaction(actor);
        break;
    }
    case 11: {
        HandleTarget *target;
        handle = &actor->handle;
        actor->flags |= 0x40;
        AddSessionCounter(0xc, 1);
        target = *handle->target;
        ChangeMode(actor, target->kind + 0x2d);
        if (!HasSlotAAndBit2Set(handle)) {
            value = GetSubObjectValue(target, IsFlag10Set(handle), 0);
            if (value > 0) {
                if (actor->onNotify != NULL) {
                    actor->onNotify(actor, value);
                }
            } else if (actor->onNotify != NULL) {
                actor->onNotify(actor, 0);
            }
        }
        if (IsPlayerEntryFlagSet(actor->player, 0x2f)) {
            ApplyTimeScaledSpeed(actor, 0x1666);
        }
        actor->menuTimer = 0;
        result = 0xb;
        ctl->handler = UpdateTargetSlotsAndMode;
        break;
    }
    case 12:
        ctl->handler = ChooseHandleFollowupMode;
        break;
    case 14: {
        u16 heading = GetLinkedAngleOffset(actor);
        actor->flags |= 0x100;
        push.y = 0;
        push.x = data_02053580[heading >> 4];
        push.z = data_02053580[(0x400 - (heading >> 4)) & 0xfff];
        func_01ffafb4(0x400, &push, &push);
        VEC_Add(&actor->knockback, &push, &actor->knockback);
        if (actor->modelFlags & 4) {
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0x15, -1);
            }
        } else {
            actor->velocity.y = 0x300;
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0x16, -1);
            }
        }
        ctl->handler = ResolvePendingModeChange;
        break;
    }
    case 15:
        actor->flags &= ~0x240010ULL;
        actor->flags |= 0x800;
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0xa, -1);
        }
        if (actor->onScale != NULL) {
            actor->onScale(actor, 0);
        }
        ResetMotion(actor);
        actor->velocity.y = 0;
        if (actor->onMotion != NULL) {
            actor->onMotion(actor, 0, 0x12, 0);
        }
        if (func_ov001_02063a38() != 4) {
            ApplyTimeScaledSpeed(actor, 0xa0);
            ctl->handler = CachePositionAndFlushScale;
        } else {
            ctl->handler = SpawnSceneMarker;
        }
        break;
    case 21:
    case 24:
        slot = actor->slotA;
        actor->flags &= ~0x100ULL;
        actor->slotA = -1;
        actor->menuTimer = 0;
        *(int *)actor->camera = 0;
        handler = SelectMenuMember(actor->members, slot, &result);
        if (handler == NULL) {
            result = 1;
            handler = func_ov052_020ca938;
            DeactivateCurrentMember(actor->members);
        }
        ctl->handler = handler;
        if (result == 0x18) {
            actor->flags |= 0x1000000;
            SetManagerEnabled(1);
            actor->landScale = 0x1000;
        }
        break;
    case 23:
        actor->menuTimer = 0;
        if (SelectFallStateHandler(actor, &fallState)) {
            ctl->handler = UpdateRewardMenuClose;
            result = fallState;
            ctl->state = fallState;
            ctl->aux = 0;
        } else {
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0x1e, -1);
            }
            result = 0x17;
            ctl->handler = ApplyPendingFlagReward;
        }
        break;
    case 27:
        SetActorPaused(actor, 1);
        actor->flags &= ~0x10ULL;
        ctl->handler = func_ov052_020cb928;
        break;
    case 17:
        if (func_ov021_020a7530(unit)) {
            if (actor->onMode != NULL) {
                actor->onMode(actor, 0xf, -1);
            }
        } else if (actor->onMode != NULL) {
            actor->onMode(actor, 0xe, -1);
        }
        ctl->handler = UpdateGlideSteering;
        break;
    case 19:
        if (func_ov021_020a7524(unit)) {
            int heading = func_ov021_020a7564(unit);
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, heading);
            }
        }
        actor->flags &= ~0x100ULL;
        ctl->handler = UpdateAirDashMode;
        break;
    case 20: {
        int mode;
        actor->flags &= ~0x100ULL;
        mode = 0x11;
        switch (actor->mode) {
        case 8:
        case 9:
            mode = 0x12;
            break;
        }
        if (actor->onMode != NULL) {
            actor->onMode(actor, mode, -1);
        }
        ExtendIfGreater(actor, 0x6000);
        ResetMotion(actor);
        actor->velocity.y = 0x400;
        ctl->handler = ExtendFieldAndNotifyCallback;
        break;
    }
    case 29:
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0xc, -1);
        }
        if (actor->onNotify != NULL) {
            actor->onNotify(actor, 0xf000);
        }
        ctl->handler = func_ov030_020bc130;
        break;
    }
    ConfigureCameraMode(actor->camera, actor, ctl->state, nextState);
    return ctl->state = result;
}
