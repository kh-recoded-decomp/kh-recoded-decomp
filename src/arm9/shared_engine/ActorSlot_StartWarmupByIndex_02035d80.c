#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[0x1bc];
    s8 warmupTimer;
} ActorSlot;

typedef struct {
    u8 pad_00[0x20];
    ActorSlot *slots[1];
} ActorRegistry;

extern u32 func_0202a9d0(u32 range);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_StartWarmupByIndex_02035d80(int index)
{
    g_actorRegistry_0206083c->slots[index]->flags |= 0x1000;
    g_actorRegistry_0206083c->slots[index]->warmupTimer = -(s8)func_0202a9d0(5);
}
