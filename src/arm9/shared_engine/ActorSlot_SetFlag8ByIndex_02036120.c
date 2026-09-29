#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void ActorSlot_SetFlag8_02036140(ActorSlot *slot, BOOL enable);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable)
{
    ActorSlot_SetFlag8_02036140(g_actorRegistry_0206083c->slots[index], enable);
}
