#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void ActorSlot_Unlink_02035c48(ActorSlot *slot);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_UnlinkByIndex_02035c28(int index)
{
    ActorSlot_Unlink_02035c48(g_actorRegistry_0206083c->slots[index]);
}
