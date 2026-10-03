#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct JumpPhase {
    s32 length;
    s32 actionAnim;
    s32 effectAnim;
} JumpPhase;

typedef struct JumpPlan {
    u8 pad_00[0xc];
    fx32 speed;
    JumpPhase phases[3];
} JumpPlan;

typedef struct ActorModel {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorModel;

typedef struct ActionSlot {
    s16 anim;
    u8 pad_02[0x2a];
} ActionSlot;

typedef struct JumpActor {
    u8 pad_000[0x5fc];
    ActionSlot slots[6];
    u8 pad_704[0x818 - 0x704];
    fx32 jumpHeight;
    s32 jumpSide;
    u8 pad_820[0x860 - 0x820];
    JumpPlan jump;
    u8 render[0xd14 - 0x894];
    s32 pendingAction;
    ActorModel **model;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
    u8 pad_ef8[4];
    s32 facing;
} JumpActor;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern u16 FixedPointAtan2_020062bc(int y, int x);
extern int abs_0202198c(int x);
extern BOOL func_ov001_020645c8(u32 value);
extern void SetActorAnimSlot_0208a54c(JumpActor *actor, int name, int animId, int slot, u32 param);
extern void BindActorAnimation_02089060(void *render, int animationId, int blendIndex);
extern void ActivateFreeSlotEntry_0208a674(JumpActor *actor, int name, int animId, int slot, int arg4, int arg5);
extern void AssignFreeEffectSlot_020890c8(JumpActor *actor, int name, int animId, int slot, int arg4, int arg5);

void PlanActorJump_0208aab4(JumpActor *actor, const VecFx32 *target, int name, int blendIndex)
{
    JumpPlan *jump = &actor->jump;
    VecFx32 delta = (*actor->model)->position;
    fx32 distance;
    fx32 reach;
    int repeat = 0;
    int phase;
    int i;

    VEC_Subtract_01ff9e3c(target, &delta, &delta);
    delta.y = 0;
    distance = VEC_Mag_01ff9f28(&delta);
    actor->facing = (u16)(0x13fff - FixedPointAtan2_020062bc(delta.z, delta.x));
    actor->jumpHeight = 0x5000;
    actor->jumpSide = -1;
    if (func_ov001_020645c8(0x362a)) {
        actor->jumpHeight = 0xa000;
        if (actor->facing >= 0x8000) {
            actor->jumpSide = 1;
        }
    }
    reach = jump->phases[0].length + jump->phases[2].length;
    jump->speed = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&delta), reach);
    if (distance - reach < 0) {
        int middle = jump->phases[1].length;

        if (middle > 0) {
            fx32 skipSpeed = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&delta), middle + jump->phases[2].length);
            int start = jump->phases[0].length;

            if (start > 0 && abs_0202198c(0x1000 - jump->speed) > abs_0202198c(0x1000 - skipSpeed)) {
                reach -= start;
                jump->phases[0].length = 0;
                jump->speed = skipSpeed;
                if (skipSpeed >= 0x99a) {
                    goto plan;
                }
                if (jump->phases[2].length <= 0) {
                    goto plan;
                }
                jump->phases[1].length = 0;
                jump->speed = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&delta), jump->phases[2].length);
            } else {
                jump->phases[1].length = 0;
                if (jump->speed >= 0x99a) {
                    goto plan;
                }
                start = jump->phases[0].length;
                if (start <= 0) {
                    goto plan;
                }
                if (jump->phases[2].length <= 0) {
                    goto plan;
                }
                reach -= start;
                jump->phases[0].length = 0;
                jump->speed = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&delta), reach);
            }
        }
    }
plan:
    if (jump->phases[1].length > 0) {
        fx32 fewerSpeed;
        int fixedCount;

        repeat = (distance - reach) / jump->phases[1].length + 1;
        jump->speed = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&delta), reach + jump->phases[1].length * repeat);
        if (repeat > 1) {
            fewerSpeed = FX_Div_01ff9c84(VEC_Mag_01ff9f28(&delta), reach + jump->phases[1].length * (repeat - 1));
            if (abs_0202198c(0x1000 - jump->speed) > abs_0202198c(0x1000 - fewerSpeed)) {
                jump->speed = fewerSpeed;
                repeat--;
            }
        }
        fixedCount = 0;
        if (jump->phases[0].length > 0) {
            fixedCount++;
        }
        if (jump->phases[2].length > 0) {
            fixedCount++;
        }
        if (repeat > 6 - fixedCount) {
            repeat = 6 - fixedCount;
        }
    }
    for (i = 0; i < 3; i++) {
        if (jump->phases[i].length > 0) {
            phase = i;
            break;
        }
    }
    SetActorAnimSlot_0208a54c(actor, name, jump->phases[phase].actionAnim, 0, 5);
    if (phase == 1) {
        repeat--;
    }
    BindActorAnimation_02089060(actor->render, blendIndex, jump->phases[phase].effectAnim);
    for (i = 0; i < 6; i++) {
        actor->slots[i].anim = -1;
    }
    while (phase != 2) {
        switch (phase) {
        case 0:
            phase = 1;
            break;
        case 1:
            if (repeat == 0) {
                phase = 2;
                if (jump->phases[2].length > 0) {
                    ActivateFreeSlotEntry_0208a674(actor, name, jump->phases[2].actionAnim, 0, 0, 0);
                    AssignFreeEffectSlot_020890c8(actor, name, jump->phases[2].effectAnim, 0, 0, 0);
                }
            } else {
                ActivateFreeSlotEntry_0208a674(actor, name, jump->phases[phase].actionAnim, 0, 0, 0);
                AssignFreeEffectSlot_020890c8(actor, name, jump->phases[phase].effectAnim, 0, 0, 0);
                repeat--;
            }
            break;
        }
    }
    actor->pendingAction = 0;
    actor->flags |= 0x40;
}
