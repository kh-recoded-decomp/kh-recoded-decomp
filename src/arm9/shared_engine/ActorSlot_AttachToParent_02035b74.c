#include "nitro/types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[2];
    s8 depth;
    u8 pad_0d[7];
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
extern void ActorSlot_InsertSortedByDepth_020356cc(ActorSlot *slot, ActorSlot **head, ActorSlot **tail);
extern ActorRegistry *g_actorRegistry_0206083c;

void ActorSlot_AttachToParent_02035b74(ActorSlot *child, ActorSlot *parent, void *initializationData)
{
    attach_child_object_0202f500(child->node, parent->node, initializationData);
    child->flags |= 0xb;
    if (parent->flags & 0x20) {
        child->flags |= 0x20;
        if (child->depth < parent->depth) {
            child->depth = parent->depth + 1;
        }
        ActorSlot_InsertSortedByDepth_020356cc(child, &g_actorRegistry_0206083c->secondaryHead, &g_actorRegistry_0206083c->secondaryTail);
    } else {
        child->flags &= ~0x20;
        if (child->depth < parent->depth) {
            child->depth = parent->depth + 1;
        }
        ActorSlot_InsertSortedByDepth_020356cc(child, &g_actorRegistry_0206083c->primaryHead, &g_actorRegistry_0206083c->primaryTail);
    }
}
