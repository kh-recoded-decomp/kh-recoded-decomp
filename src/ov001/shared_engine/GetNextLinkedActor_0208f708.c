#include "nitro/types.h"

typedef struct LinkedActor {
    u8 pad_000[0xa2];
    u16 nextLinkId;
} LinkedActor;

extern void *func_ov001_0209c168(u16 id);

void *GetNextLinkedActor_0208f708(LinkedActor *actor)
{
    if (actor == NULL) {
        return NULL;
    }
    if (actor->nextLinkId == 0) {
        return NULL;
    }
    return func_ov001_0209c168(actor->nextLinkId);
}
