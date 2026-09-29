#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[6];
    u32 actorFlags;
    u16 nodeFlags;
    u8 pad_16[0x7a];
    u16 anchorValue;
    u8 pad_92[0x134];
    s8 warmupTimer;
} ActorSlot;

typedef struct {
    u8 pad_00[0xc];
    ActorSlot *secondaryHead;
    ActorSlot *secondaryTail;
    ActorSlot *primaryHead;
    ActorSlot *primaryTail;
} ActorRegistry;

extern int ProjectPositionDownward_020352e0(void *cont, int p3, void *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_02035580(ActorRegistry *registry, void *actor, const VecFx32 *position);
extern int CollModel_GetEntryField14_0203537c(void *model, void *key);
extern void ActorSlot_InsertSortedByDepth_020356cc(ActorSlot *slot, ActorSlot **head, ActorSlot **tail);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_PlaceAndLink_02035a18(ActorSlot *slot, int anchor, const VecFx32 *offset)
{
    ActorRegistry *registry = g_actorRegistry_0206083c;
    VecFx32 position;

    if (anchor != 0 && ProjectPositionDownward_020352e0(registry, anchor, &position)) {
        if (offset != NULL) {
            VEC_Add_01ff9e0c(&position, offset, &position);
        }
        func_02035580(registry, &slot->actorFlags, &position);
        {
            int value = CollModel_GetEntryField14_0203537c(registry, (void *)anchor);
            if ((slot->actorFlags & 0x20) == 0) {
                slot->anchorValue = value;
                slot->nodeFlags |= 0x20;
            }
        }
    } else {
        func_02035580(registry, &slot->actorFlags, offset);
    }
    slot->flags |= 0x10a;
    slot->warmupTimer = 0;
    if (slot->flags & 0x20) {
        ActorSlot_InsertSortedByDepth_020356cc(slot, &g_actorRegistry_0206083c->secondaryHead, &g_actorRegistry_0206083c->secondaryTail);
    } else {
        ActorSlot_InsertSortedByDepth_020356cc(slot, &g_actorRegistry_0206083c->primaryHead, &g_actorRegistry_0206083c->primaryTail);
    }
}
