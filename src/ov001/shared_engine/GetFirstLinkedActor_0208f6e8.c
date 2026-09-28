#include "nitro/types.h"

typedef struct LinkedActor {
    u8 pad_000[0x284];
    u16 firstLinkId;
} LinkedActor;

extern void *func_ov001_0209c168(u16 id);

void *GetFirstLinkedActor_0208f6e8(LinkedActor *actor)
{
    if (actor == NULL) {
        return NULL;
    }
    if (actor->firstLinkId == 0) {
        return NULL;
    }
    return func_ov001_0209c168(actor->firstLinkId);
}
