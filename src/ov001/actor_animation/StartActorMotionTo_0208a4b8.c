#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelHolder {
    u16 flags;
} ModelHolder;

typedef struct Model {
    u32 unk_00;
    ModelHolder holder;
} Model;

typedef struct ActorMotion {
    VecFx32 current;
    VecFx32 start;
    int resource;
    int remaining;
    int duration;
    int extra;
} ActorMotion;

typedef struct Actor {
    u8 pad_000[0x700];
    ActorMotion motions[8];
    u8 pad_840[0x4d8];
    Model **model;
    u8 pad_D1C[0x1d8];
    u32 flags;
} Actor;

extern int FindModelResourceIndexByName_0208950c(ModelHolder *holder, const char *name);
extern int Actor_FindSlotOrFree_0208954c(Actor *actor, int id);
extern void Actor_InstallNodeStateCallback_02089844(Actor *actor);

void StartActorMotionTo_0208a4b8(Actor *actor, const char *name, const VecFx32 *target, int duration, int extra)
{
    int resource = FindModelResourceIndexByName_0208950c(&(*actor->model)->holder, name);
    ActorMotion *motion = &actor->motions[Actor_FindSlotOrFree_0208954c(actor, resource)];

    motion->resource = resource;
    motion->duration = duration;
    motion->remaining = duration;
    motion->extra = extra;
    motion->start = motion->current;
    motion->current = *target;
    actor->flags |= 0x400;
    (*actor->model)->holder.flags |= 0x80;
    Actor_InstallNodeStateCallback_02089844(actor);
}
