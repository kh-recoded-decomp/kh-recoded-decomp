#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x56];
    s16 nextIndex;
} Actor;

extern BOOL IsDestroyed_020a31f8(Actor *self);
extern Actor *func_ov001_0208635c(void *pool, int index);

static inline Actor *GetNextLink(Actor *actor)
{
    return func_ov001_0208635c(actor->pool, actor->nextIndex);
}

Actor *FindLiveNextLink_020a20e0(Actor *actor)
{
    while (actor->nextIndex >= 0) {
        actor = GetNextLink(actor);
        if (!IsDestroyed_020a31f8(actor)) {
            return actor;
        }
    }
    return NULL;
}
