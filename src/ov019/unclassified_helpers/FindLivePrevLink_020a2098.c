#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x54];
    s16 prevIndex;
} Actor;

extern BOOL IsDestroyed_020a31f8(Actor *self);
extern Actor *func_ov001_0208635c(void *pool, int index);

static inline Actor *GetPrevLink(Actor *actor)
{
    return func_ov001_0208635c(actor->pool, actor->prevIndex);
}

Actor *FindLivePrevLink_020a2098(Actor *actor)
{
    while (actor->prevIndex >= 0) {
        actor = GetPrevLink(actor);
        if (!IsDestroyed_020a31f8(actor)) {
            return actor;
        }
    }
    return NULL;
}
