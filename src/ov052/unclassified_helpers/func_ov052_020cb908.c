#include "nitro/types.h"
#include "nitro/fx_types.h"

#pragma opt_propagation off

typedef struct DriftActor DriftActor;
typedef void (*ActorEventFunc)(DriftActor *actor, int event);
typedef int (*GetModeFunc)(DriftActor *actor);

typedef struct {
    u8 pad_00[4];
    int counter;
    u8 flags;
    u8 pad_09[3];
    u16 angle;
} DriftState;

struct DriftActor {
    u8 pad_000[0x1dc];
    int mode;
    u8 pad_1e0[0x22c - 0x1e0];
    GetModeFunc getMode;
    u8 pad_230[4];
    u32 modelFlags;
    u8 pad_238[0x9b4 - 0x238];
    u8 pool;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 velocity;
    u8 pad_9d4[0x105c - 0x9d4];
    DriftState drift;
    u8 pad_106c[0x10ec - 0x106c];
    ActorEventFunc onEvent;
};

extern s16 data_0205356c[];
extern u16 *func_ov001_0206db78(int pool);
extern BOOL AlarmCallback_020a7504(u16 *self);
extern BOOL HasFlagsAt0xc_020a751c(u16 *holder, u16 mask);
extern int func_0202a9d0(u32 range);
extern int FixedPointMultiply12(int left, int right);

static inline void AddScaledDrift(DriftActor *actor, fx32 z, fx32 x)
{
    fx32 dx = FixedPointMultiply12(x, 0x133);
    fx32 dz = FixedPointMultiply12(z, 0x133);
    actor->velocity.x += dx;
    actor->velocity.z += dz;
}

static inline void AddDriftForAngle(DriftActor *actor, u16 angle)
{
    int index = angle >> 4;
    AddScaledDrift(actor, -data_0205356c[(0x400 - index) & 0xfff], -data_0205356c[index]);
}

void func_ov052_020cb908(DriftActor *actor)
{
    u16 *self = func_ov001_0206db78(actor->pool);
    DriftState *drift = &actor->drift;
    u32 grounded = actor->modelFlags & 4;
    int mode;
    BOOL active;
    int angle;

    if (actor->getMode != NULL) {
        mode = actor->getMode(actor);
    } else {
        mode = actor->mode;
    }
    if (mode != 2) {
        actor->onEvent(actor, 10);
        return;
    }
    if (grounded == 0) {
        return;
    }
    active = FALSE;
    angle = -1;
    if (AlarmCallback_020a7504(self)) {
        if (self[1] != self[0]) {
            active = TRUE;
        }
    } else if (HasFlagsAt0xc_020a751c(self, 0xc03)) {
        active = TRUE;
    }
    if (active) {
        drift->counter++;
        if (!(drift->flags & 8)) {
            angle = func_0202a9d0(0xffff);
        }
    }
    if (active && angle != -1) {
        drift->flags |= 8;
        drift->angle = angle + 0x8000;
    } else if (drift->flags & 8) {
        drift->flags &= ~8;
        angle = drift->angle;
    }
    if (angle >= 0) {
        AddDriftForAngle(actor, angle);
    }
}
