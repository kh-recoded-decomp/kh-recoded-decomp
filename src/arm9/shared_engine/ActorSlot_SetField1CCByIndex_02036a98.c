#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern ActorSlot *func_02036ab8(ActorSlot *slot, u32 value);
extern ActorRegistry *g_actorRegistry_0206083c;

ActorSlot *ActorSlot_SetField1CCByIndex_02036a98(int index, u32 value)
{
    return func_02036ab8(g_actorRegistry_0206083c->slots[index], value);
}
