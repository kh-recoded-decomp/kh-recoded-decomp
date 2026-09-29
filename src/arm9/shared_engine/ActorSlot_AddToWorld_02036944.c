#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorRegistry ActorRegistry;

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[6];
    u8 entity[0xa8];
    VecFx32 position;
} ActorSlot;

extern void func_02035580(ActorRegistry *registry, void *entity, VecFx32 *position);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_AddToWorld_02036944(ActorSlot *slot)
{
    func_02035580(g_actorRegistry_0206083c, slot->entity, &slot->position);
    slot->flags |= 0x100;
}
