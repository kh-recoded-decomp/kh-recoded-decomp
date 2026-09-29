#include "nitro/types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[6];
    u8 actor[4];
    u8 node[4];
} ActorSlot;

typedef struct {
    u8 pad_00[0xc];
    ActorSlot *secondaryHead;
    ActorSlot *secondaryTail;
    ActorSlot *primaryHead;
    ActorSlot *primaryTail;
} ActorRegistry;

extern void attach_child_object_0202f500(void *child, void *parent, void *initializationData);
extern void Obj_RemoveFromQuadTree_020355f4(void *entity);
extern ActorRegistry *g_actorRegistry_0206083c;

static inline void RemoveFromList(ActorSlot *slot, ActorSlot **head, ActorSlot **tail)
{
    if (slot->next != NULL) {
        slot->next->prev = slot->prev;
    }
    if (slot->prev != NULL) {
        slot->prev->next = slot->next;
    }
    if (*head == slot) {
        *head = slot->next;
    }
    if (*tail == slot) {
        *tail = slot->prev;
    }
    slot->prev = NULL;
    slot->next = NULL;
}

void ActorSlot_Unlink_02035c48(ActorSlot *slot)
{
    if ((slot->flags & 2) == 0) {
        return;
    }
    if (slot->flags & 4) {
        attach_child_object_0202f500(slot->node, NULL, NULL);
    }
    Obj_RemoveFromQuadTree_020355f4(slot->actor);
    if (slot->flags & 0x20) {
        RemoveFromList(slot, &g_actorRegistry_0206083c->secondaryHead, &g_actorRegistry_0206083c->secondaryTail);
    } else {
        RemoveFromList(slot, &g_actorRegistry_0206083c->primaryHead, &g_actorRegistry_0206083c->primaryTail);
    }
    slot->flags &= 0xfef5;
}
