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

extern s16 data_02053580[];
extern u16 *GetPlayerControlState(int pool);
extern BOOL func_ov021_020a7524(u16 *self);
extern BOOL HasFlagsAt0xc(u16 *holder, u16 mask);
extern int func_0202a9e4(u32 range);
extern int FX_Mul(int left, int right);

static inline void AddScaledDrift(DriftActor *actor, fx32 z, fx32 x)
{
    fx32 dx = FX_Mul(x, 0x133);
    fx32 dz = FX_Mul(z, 0x133);
    actor->velocity.x += dx;
    actor->velocity.z += dz;
}

static inline void AddDriftForAngle(DriftActor *actor, u16 angle)
{
    int index = angle >> 4;
    AddScaledDrift(actor, -data_02053580[(0x400 - index) & 0xfff], -data_02053580[index]);
}

void UpdateDriftState(DriftActor *actor)
{
    u16 *self = GetPlayerControlState(actor->pool);
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
    if (func_ov021_020a7524(self)) {
        if (self[1] != self[0]) {
            active = TRUE;
        }
    } else if (HasFlagsAt0xc(self, 0xc03)) {
        active = TRUE;
    }
    if (active) {
        drift->counter++;
        if (!(drift->flags & 8)) {
            angle = func_0202a9e4(0xffff);
        }
    }
    if (active && angle != -1) {
        drift->flags |= 8;
        drift->angle = angle + 0x8000;
    } else if (drift->flags & 8) {
        drift->flags &= 0xf7;
        angle = drift->angle;
    }
    if (angle >= 0) {
        AddDriftForAngle(actor, angle);
    }
}

