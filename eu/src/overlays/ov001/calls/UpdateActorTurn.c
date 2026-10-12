#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorRotationNode {
    u32 flags;
    u16 dirty;
    u8 reserved06[0x7a];
    u16 yaw;
} ActorRotationNode;

typedef struct ActorModel {
    ActorRotationNode *rotation;
} ActorModel;

typedef struct TurningActor {
    u8 reserved00[0x818];
    fx32 turnSpeed;
    s32 turnDirection;
    u8 reserved820[0xd18 - 0x820];
    ActorModel *model;
    u8 reservedd1c[0xef8 - 0xd1c];
    u32 yaw;
    u32 targetYaw;
} TurningActor;
enum {
    ANGLE_FULL_TURN = 0x10000,
    ANGLE_HALF_TURN = 0x8000,
    ANGLE_EIGHTH_TURN = 0x2000,
    TURN_SPEED_TO_ANGLE = 728,
    ROTATION_YAW_LOCKED = 0x20
};

extern fx32 FX_Mul(fx32 a, fx32 b);

void UpdateActorTurn(TurningActor *actor)
{
    s32 delta = actor->yaw;
    s32 step;

    delta = actor->targetYaw - delta;
    if (delta == 0) return;

    /* Unsigned angle subtraction wraps around a complete turn. */
    step = (u16)delta;
    if ((step < ANGLE_HALF_TURN && actor->turnDirection == -1) || actor->turnDirection == 0) {
        if (step > ANGLE_EIGHTH_TURN) {
            step = FX_Mul(actor->turnSpeed, TURN_SPEED_TO_ANGLE);
        } else if (step > FX_Mul(actor->turnSpeed, TURN_SPEED_TO_ANGLE)) {
            step = FX_Mul(actor->turnSpeed, TURN_SPEED_TO_ANGLE);
        }
        step += actor->yaw;
    } else {
        if (step < ANGLE_FULL_TURN - ANGLE_EIGHTH_TURN) {
            step = FX_Mul(actor->turnSpeed, TURN_SPEED_TO_ANGLE);
        } else if (step < ANGLE_FULL_TURN - FX_Mul(actor->turnSpeed, TURN_SPEED_TO_ANGLE)) {
            step = FX_Mul(actor->turnSpeed, TURN_SPEED_TO_ANGLE);
        } else {
            step = ANGLE_FULL_TURN - step;
        }
        step = actor->yaw - step;
    }
    actor->yaw = (u16)step;

    {
        ActorRotationNode *node = actor->model->rotation;
        if (!(node->flags & ROTATION_YAW_LOCKED)) {
            node->yaw = actor->yaw;
            node->dirty |= ROTATION_YAW_LOCKED;
        }
    }
}
