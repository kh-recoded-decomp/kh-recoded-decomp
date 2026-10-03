#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x44];
    u8 triggered;
} ActionTask;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x234];
    u32 moveFlags;
    u8 pad_238[0x768 - 0x238];
    int finished;
    u8 pad_76c[0x9c4 - 0x76c];
    fx32 height;
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    u8 pad_9d4[0x1078 - 0x9d4];
    ActionTask *task;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern void ComputeRootMotionDelta_020ce9d4(Actor *actor, VecFx32 *out);
extern void ResetGaugeDisplay_020734f8(void);
extern void SetManagerEnabled_0206e160(u32 enabled);

void UpdateRisingFinisherAction_020d819c(Actor *actor)
{
    u32 grounded = actor->moveFlags & 4;
    ActionTask *task = actor->task;
    VecFx32 delta;

    ComputeRootMotionDelta_020ce9d4(actor, &delta);
    actor->posY = delta.y;
    actor->posX += delta.x;
    actor->posZ += delta.z;
    if (!task->triggered && actor->height >= 0x13000) {
        task->triggered = 1;
    }
    if (actor->finished == 0) {
        return;
    }
    ResetGaugeDisplay_020734f8();
    SetManagerEnabled_0206e160(0);
    if (grounded) {
        actor->setMode(actor, 5);
    } else {
        actor->setMode(actor, 4);
    }
}
