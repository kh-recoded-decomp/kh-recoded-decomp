#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorBody {
    u8 pad_00[6];
    s16 group;
    u8 pad_08[0x9c - 0x08];
    VecFx32 forward;
    u8 pad_a8[0xce - 0xa8];
    s16 animId;
    u8 pad_d0[0xd8 - 0xd0];
    fx32 animLength;
    s16 animActive;
    u8 pad_de[2];
} ActorBody;

typedef struct Actor {
    u8 pad_000[8];
    u16 drawFlags;
    u8 pad_00a[6];
    ActorBody body;
    u8 pad_0f0[0x1d0 - 0xf0];
    u8 sequencer[0x26c - 0x1d0];
    u32 behaviorFlags : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x27c - 0x270];
    u16 active;
    u8 pad_27e[0x282 - 0x27e];
    u8 linkFlagsA;
    u8 linkFlagsB;
    u8 pad_284[4];
    u16 unk_288_0 : 8;
    u16 spinYaw : 1;
    u16 followLink : 1;
    u16 unk_288_10 : 1;
    u16 keepDirection : 1;
    u16 unk_288_12 : 2;
    u16 waitForTurn : 1;
    u16 highlight : 1;
    u16 moveMode : 2;
    u16 snapMode : 3;
    u16 unk_28a_5 : 4;
    u16 frozen : 1;
    u16 unk_28a_10 : 4;
    u16 syncGroup : 1;
    u16 unk_28a_15 : 1;
    u16 layer : 3;
    u16 unk_28c_3 : 13;
    u8 pad_28e[0x2ac - 0x28e];
    fx32 turnSpeed;
    u8 pad_2b0[8];
    fx32 turnScale;
    u8 pad_2bc[4];
    VecFx32 position;
    VecFx32 target;
    VecFx32 nextTarget;
    u8 animGroup;
    u8 pad_2e5;
    u16 yaw;
    u16 targetYaw;
    u16 pitch;
    u16 targetPitch;
    u8 pad_2ee[0x380 - 0x2ee];
    VecFx32 direction;
    u8 pad_38c[0x3a4 - 0x38c];
    u16 targetActorA;
    u16 targetPointA;
    u16 targetActorB;
    u16 targetPointB;
    u16 linkId;
} Actor;

extern fx32 ApplyActorScaleFactors(Actor *actor);
extern void TickSequenceCountdown(void *sequencer, s32 step);
extern void GetTargetActorPointPosition(Actor *actor, u16 targetId, u16 pointId, VecFx32 *out);
extern u32 func_ov001_0209c5ac(u32 mask);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void ApplyActorDisplayParams(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *source, VecFx32 *dest);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VecToYawPitch(VecFx32 *dir, s16 *pitch, u16 *yaw);
extern void AdvanceActorJumpArc(Actor *actor, VecFx32 *position);
extern void ApplyActorMoveSpeed(Actor *actor, const VecFx32 *direction, fx32 stopDistance, VecFx32 *position);
extern void AddActorSideOffset(Actor *actor, VecFx32 *position, const VecFx32 *direction);
extern void func_ov001_0208fc90(Actor *actor, VecFx32 *position);
extern void ApplyActorMovementCollision(Actor *actor, VecFx32 *position);
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern void UpdateActorAttachedEffects(Actor *actor);
extern void UpdateStageActorBody(Actor *actor);
extern Actor *GetStageActor(int id);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void PlayActorAnimationSlot(Actor *actor, int slot, u32 anim, int frames, BOOL loop);

static inline fx32 AngleGapToDegrees(u16 target, u16 current)
{
    int gap = target - current;

    if (gap < 0) {
        gap = -gap;
    }
    if (gap > 0x7fff) {
        gap -= 0x7fff;
    }
    return (fx32)(((s64)gap * 0x1680000 + 0x80000) >> 20);
}

static inline void StepAngleToward(u16 *angle, u16 *target, fx32 speed)
{
    int current = *angle;
    int step = (u16)(((s64)speed * 0xb60b60b60bLL + 0x80000000000LL) >> 44);
    int delta = *target - current;
    int result;

    if (delta < 0) {
        delta += 0x10000;
    }
    if (delta < 0x8000) {
        if (delta < step) {
            step = delta;
        }
        result = step + current;
        if (result > 0xffff) {
            result -= 0x10000;
        }
    } else {
        if (delta > 0x10000 - step) {
            step = 0x10000 - delta;
        }
        result = current - step;
        if (result < 0) {
            result += 0x10000;
        }
    }
    *angle = result;
}

static inline void TurnActor(Actor *actor)
{
    fx32 speed = FX_Mul(actor->turnSpeed, ApplyActorScaleFactors(actor));
    fx32 scale = actor->turnScale;

    if (scale != 0) {
        speed = FX_Mul(AngleGapToDegrees(actor->targetYaw, actor->yaw), scale);
    }
    if (!actor->spinYaw) {
        StepAngleToward(&actor->yaw, &actor->targetYaw, speed);
    } else {
        actor->yaw = (actor->yaw + speed) % 0xffff;
    }
    scale = actor->turnScale;
    if (scale != 0) {
        speed = FX_Mul(AngleGapToDegrees(actor->targetPitch, actor->pitch), scale);
    }
    StepAngleToward(&actor->pitch, &actor->targetPitch, speed);
    ApplyActorDisplayParams(actor);
}

static inline int GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

void UpdateFieldActorMovement(Actor *actor)
{
    ActorBody *body;
    VecFx32 diff;
    VecFx32 dir;
    VecFx32 facing;
    VecFx32 pos;
    VecFx32 move;
    fx32 speed = ApplyActorScaleFactors(actor);
    u32 frozen;
    Actor *target;
    ActorBody *targetBody;
    u16 anim;
    s16 *activeFlag;
    int frames;
    u8 keptFlags;
    fx32 dist;

    if (actor->active == 0) {
        return;
    }
    frozen = actor->frozen;
    if (!frozen) {
        frozen = actor->behaviorFlags & 0x102;
    }
    body = &actor->body;
    pos = actor->position;
    TickSequenceCountdown(actor->sequencer, speed);
    if (!frozen) {
        GetTargetActorPointPosition(actor, actor->targetActorB, actor->targetPointB, &actor->nextTarget);
        GetTargetActorPointPosition(actor, actor->targetActorA, actor->targetPointA, &actor->target);
    }
    if (actor->highlight) {
        actor->drawFlags |= 0x200;
    } else {
        actor->drawFlags &= 0xfdff;
    }
    if (!func_ov001_0209c5ac(0x20) && actor->linkId == 0) {
        if (!func_ov001_0209c5ac(0x10)) {
            switch (actor->moveMode) {
            case 0:
            case 2:
                TurnActor(actor);
                VEC_Subtract(&actor->target, &pos, &diff);
                dist = func_01ffaff4(&diff, &dir);
                if (actor->moveMode == 2) {
                    dir.x = actor->body.forward.x;
                    dir.y = actor->body.forward.y;
                    dir.z = actor->body.forward.z;
                }
                facing.x = actor->body.forward.x;
                facing.y = actor->body.forward.y;
                facing.z = actor->body.forward.z;
                break;
            case 1:
                if (!frozen) {
                    VEC_Subtract(&actor->nextTarget, &pos, &diff);
                    dist = func_01ffaff4(&diff, &facing);
                    if (dist != 0) {
                        VecToYawPitch(&facing, (s16 *)&actor->targetPitch, &actor->targetYaw);
                    }
                }
                actor->target = actor->nextTarget;
                TurnActor(actor);
                if (actor->keepDirection && (actor->frozen || dist <= 0)) {
                    func_01ffaff4(&actor->direction, &dir);
                } else {
                    dir.x = actor->body.forward.x;
                    dir.y = actor->body.forward.y;
                    dir.z = actor->body.forward.z;
                }
                if (!(actor->snapMode & 2)) {
                    dir.y = 0;
                    func_01ffaff4(&dir, &dir);
                }
                VEC_Subtract(&actor->target, &pos, &diff);
                if (!(actor->snapMode & 2)) {
                    diff.y = 0;
                }
                dist = func_01ffaff4(&diff, &diff);
                break;
            }
        }
        if (!actor->waitForTurn || actor->yaw == actor->targetYaw) {
            AdvanceActorJumpArc(actor, &pos);
            ApplyActorMoveSpeed(actor, &dir, dist, &pos);
            AddActorSideOffset(actor, &pos, &facing);
            func_ov001_0208fc90(actor, &pos);
        }
        ApplyActorMovementCollision(actor, &pos);
    }
    if (!actor->keepDirection) {
        VEC_Subtract(&pos, &actor->position, &actor->direction);
    } else {
        VEC_Subtract(&pos, &actor->position, &move);
        if (VEC_Mag(&move) != 0) {
            actor->direction = move;
        }
    }
    if (GetSessionMode() == 4 && actor->layer == 0) {
        pos.z = 0;
    }
    actor->position = pos;
    UpdateActorAttachedEffects(actor);
    UpdateStageActorBody(actor);
    if (!actor->followLink) {
        return;
    }
    if (actor->linkId == 0) {
        return;
    }
    target = GetStageActor((s16)actor->linkId);
    if (target == NULL) {
        return;
    }
    targetBody = &target->body;
    if (targetBody == NULL) {
        return;
    }
    activeFlag = &body->animActive;
    anim = 0xffff;
    if (!actor->syncGroup) {
        s16 id;

        if (*activeFlag == 0) {
            return;
        }
        if (!target->syncGroup) {
            id = targetBody->animId;
            if (id >= 0) {
                anim = id;
            } else if ((id = targetBody->group) != body->group) {
                anim = id;
            }
        } else if (actor->animGroup != target->animGroup) {
            anim = target->animGroup;
        }
        if (anim == 0xffff) {
            return;
        }
        frames = FX_Div(0x1000, targetBody->animLength + 2) >> 12;
        PlayActorAnimationSlot(actor, 0, (s16)anim, frames, FALSE);
    } else if (actor->animGroup != target->animGroup) {
        PlayActorAnimationSlot(actor, 0, target->animGroup, 0, FALSE);
    }
    keptFlags = actor->linkFlagsB & ~1;
    actor->linkFlagsA = (u8)(actor->linkFlagsA & ~1) | (target->linkFlagsA & 1);
    actor->linkFlagsB = keptFlags | (target->linkFlagsB & 1);
}
