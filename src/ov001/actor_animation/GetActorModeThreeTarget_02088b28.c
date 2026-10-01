#include "nitro/types.h"

typedef struct ActorTarget {
    u8 pad_00[0x24];
    void *target;
} ActorTarget;

typedef struct ActorState {
    u8 pad_00[0x24];
    ActorTarget *link;
    u8 pad_28[0x18];
    int mode;
} ActorState;

typedef struct Actor {
    u8 pad_000[0x10c];
    ActorState state;
} Actor;

extern Actor *func_02036240(u16 id);

void *GetActorModeThreeTarget_02088b28(int id)
{
    ActorState *state = &func_02036240(id)->state;
    void *target = NULL;

    if (state->mode == 3) {
        target = state->link->target;
    }
    return target;
}
