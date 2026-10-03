#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorNode {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct Actor {
    u8 pad_000[0x840];
    VecFx32 target;
    u8 pad_84c[0x0c];
    s32 moveSpeed;
    s32 arrivalSlot;
    u8 pad_860[0xd18 - 0x860];
    ActorNode **node;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
} Actor;

extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern int FX_Div_01ff9c84(int numer, int denom);
extern void Actor_SetVelocity_0208a268(Actor *actor, const VecFx32 *velocity);
extern BOOL Actor_IsNearProjectedPoint_02089a4c(Actor *actor, const VecFx32 *origin, const VecFx32 *direction, fx32 distance);
extern void ActivateFreeSlotEntry_0208a674(Actor *actor, s32 arg1, s32 arg2, s32 slot, s32 arg4, s32 arg5);

void Actor_StepTowardTarget_02089aa8(Actor *actor)
{
    VecFx32 position = (*actor->node)->position;
    int speed = actor->moveSpeed / 30;
    VecFx32 delta;
    fx32 distance;

    VEC_Subtract_01ff9e3c(&actor->target, &position, &delta);
    if (actor->flags & 0x10) {
        delta.y = 0;
    }
    distance = VEC_Mag_01ff9f28(&delta);
    if (distance < 0x19a) {
        Actor_SetVelocity_0208a268(actor, NULL);
        actor->moveSpeed = 0;
        actor->target.z = 0;
        actor->target.y = 0;
        actor->target.x = 0;
        if (actor->arrivalSlot != -1) {
            ActivateFreeSlotEntry_0208a674(actor, 0, actor->arrivalSlot, 0, 10, 1);
            actor->arrivalSlot = -1;
        }
        return;
    }
    if (distance < speed) {
        speed = distance;
    }
    delta.x = FX_Div_01ff9c84(FixedPointMultiply12(delta.x, speed), distance);
    if (!(actor->flags & 0x10)) {
        delta.y = FX_Div_01ff9c84(FixedPointMultiply12(delta.y, speed), distance);
    }
    delta.z = FX_Div_01ff9c84(FixedPointMultiply12(delta.z, speed), distance);
    Actor_SetVelocity_0208a268(actor, &delta);
    if (actor->arrivalSlot != -1 && Actor_IsNearProjectedPoint_02089a4c(actor, &position, &delta, 0xa000)) {
        ActivateFreeSlotEntry_0208a674(actor, 0, actor->arrivalSlot, 0, 10, 1);
        actor->arrivalSlot = -1;
    }
}
