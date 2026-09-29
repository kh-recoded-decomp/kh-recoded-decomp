#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern void ActorSlot_AttachToParent_02035b74(ActorSlot *child, ActorSlot *parent, void *initializationData);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_AttachToParentByIndex_02035b4c(int childIndex, int parentIndex, void *initializationData)
{
    ActorSlot_AttachToParent_02035b74(g_actorRegistry_0206083c->slots[childIndex],
                                      g_actorRegistry_0206083c->slots[parentIndex], initializationData);
}
