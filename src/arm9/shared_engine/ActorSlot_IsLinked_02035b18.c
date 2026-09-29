#include "nitro/types.h"

typedef struct ActorSlot ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern BOOL func_02035b38(ActorSlot *slot);
extern ActorRegistry *g_actorRegistry_0206083c;

BOOL ActorSlot_IsLinked_02035b18(int index)
{
    return func_02035b38(g_actorRegistry_0206083c->slots[index]);
}
