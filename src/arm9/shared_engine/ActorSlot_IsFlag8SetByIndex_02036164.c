#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern BOOL func_02036184(ActorSlot *slot);
extern ActorRegistry *g_actorRegistry_0206083c;

BOOL ActorSlot_IsFlag8SetByIndex_02036164(int index)
{
    return func_02036184(g_actorRegistry_0206083c->slots[index]);
}
